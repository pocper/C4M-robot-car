import sys
import cv2
import numpy as np
import serial


# ls /dev/tty*
com = "/dev/ttyACM0"
baudrate = 38400
timeout = 1
write_timeout = 0.1
rtscts = True
try:
    uart = serial.Serial(com, baudrate, timeout=timeout,
                        rtscts=rtscts, write_timeout=write_timeout)
except serial.SerialException as e:
    print(f"[Error] {e}", e)
    sys.exit(1)

def write(str):
    print(str)
    try:
        uart.write(str.encode())
    except Exception as e:
        print(e)


def mask_filter(mask):
    kernel = np.ones([5, 5], np.uint8)
    erode = cv2.erode(mask, kernel, iterations=2)
    dilate = cv2.dilate(erode, kernel, iterations=2)
    return dilate


def find_color_center(frame, contours):
    sum_center_x = 0
    sum_center_y = 0
    num_rectangle = len(contours)
    for c in range(len(contours)):
        area = cv2.contourArea(contours[c])
        M = cv2.moments(contours[c])
        center_x = int(M['m10']/M['m00'])
        center_y = int(M['m01']/M['m00'])
        if area < 500:
            center_x = 0
            center_y = 0
            num_rectangle -= 1

        img = cv2.drawContours(frame, contours, c, (0, 0, 255), 1)
        sum_center_x += center_x
        sum_center_y += center_y

    if num_rectangle > 0:
        COG_x = sum_center_x/num_rectangle
        COG_y = sum_center_y/num_rectangle
        img1 = cv2.circle(
            img, [int(COG_x), int(COG_y)], 3, [0, 0, 255], -1)
        return img1, COG_x

    return frame, 0


def input_color():
    gate_through_color = [0, 0, 0]
    print('Input 1st through gate color')
    gate_through_color[0] = int(input("[0]:cyan [1]:green >"))

    print('Input 2nd through gate color')
    gate_through_color[1] = int(input("[0]:orange [1]:blue >"))

    print('Input 3rd through gate color')
    gate_through_color[2] = int(input("[0]:green [1]:red >"))

    return gate_through_color


def car_direction(frame, center_x):
    pixel_distance = 200
    print("dis = ", frame.shape[1]/2-center_x)
    if (frame.shape[1]/2-center_x) > pixel_distance:  # 3或-3可在調整
        print('A')
        write('A')
    elif (frame.shape[1]/2-center_x) < -pixel_distance:
        print('D')
        write('D')
    else:
        print('W')
        write('W')
    cv2.waitKey(500)


def condition(frame, frame1, lower_upper_hsv):
    hsv = cv2.cvtColor(frame1, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, np.asarray(
        lower_upper_hsv[0]), np.asarray(lower_upper_hsv[1]))
    dilate = mask_filter(mask)
    contours, _ = cv2.findContours(
        dilate, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    global gate

    print('len(contours)=', len(contours))
    if(len(contours) == 0):
        gate += 1
        write('G')
        cv2.waitKey(1000)
        return frame, dilate

    colorgate_center, center_x = find_color_center(frame, contours)
    car_direction(frame, center_x)

    return colorgate_center, dilate


def findRectangle(frame):
    global gate
    Cont_max = FindMarker(frame)  # 呼叫函式，找最大輪廓
    vertex = cv2.approxPolyDP(Cont_max, 1, True)  # 最大輪廓有幾個頂點
    cv2.drawContours(frame, [Cont_max], 0, (0, 0, 255), 2)  # 畫最大輪廓

    print("cv2.contourArea(Cont_max) = ", cv2.contourArea(Cont_max))
    print('vertex=', len(vertex))

    # 當車子接近方塊到一定距離時
    if cv2.contourArea(Cont_max) > 100 and len(vertex) <= 100:
        write("E")  # 車子旋轉
        cv2.waitKey(2200)  # 等它轉
        gate += 1


def findCircle(frame):
    global gate
    Cont_max = FindMarker(frame)  # 呼叫函式，找最大輪廓
    cv2.drawContours(frame, [Cont_max], 0, (0, 0, 255), 2)  # 畫最大輪廓

    if cv2.contourArea(Cont_max) > 100:  # 當車子接近圓形到一定距離時
        gate += 1
        write("G")  # 車子停止
    else:
        write("W")


# def FindMarker(image):
#     gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#     _, thr = cv2.threshold(gray, 180, 255, cv2.THRESH_BINARY_INV)
#     cont, _ = cv2.findContours(thr, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#     cont_max = max(cont, key=cv2.contourArea)
#     return cont_max

def FindMarker(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    ret, binary = cv2.threshold(gray, 5, 255, cv2.THRESH_BINARY_INV)
    cv2.imwrite('bin.jpg', binary)
    contours, _ = cv2.findContours(
        binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours_max = max(contours, key=cv2.contourArea)
    return contours_max


def keyCondition(keypress):
    if keypress == ord("w"):
        write('W')
    if keypress == ord("a"):
        write('A')
    if keypress == ord("s"):
        write('S')
    if keypress == ord("d"):
        write('D')
    if keypress == ord("g"):
        write('G')
    if keypress == ord("e"):
        write('Q')
    if keypress == ord("r"):
        write('E')


hsv_list = [
    # 1st Gate
    [
        # ----Lower----  ----Upper----
        [[95, 90, 145], [108, 255, 255]],   # cyan
        [[36, 50, 110], [75, 255, 210]]     # green
    ],
    # 2rd Gate
    [
        [[7, 100, 170], [20, 255, 255]],    # orange
        [[109, 160, 130], [115, 255, 255]]  # blue
    ],
    # 3nd Gate
    [
        [[70, 135, 130], [95, 255, 255]],   # green
        [[0, 110, 100], [8, 255, 255]]     # red
    ]
]

gate = 0


def main():
    isFirstFixed = True
    gate_through_color = input_color()
    cap = cv2.VideoCapture('/dev/video0')
    # cap = cv2.VideoCapture('record1.avi')

    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    writer_origin = cv2.VideoWriter('origin.avi', fourcc, 5, (width, height))
    writer_erode = cv2.VideoWriter(
        'erode.avi', fourcc, 5, (width, height), False)
    writer_filter = cv2.VideoWriter('filter.avi', fourcc, 5, (width, height))

    while uart != 0:
        ret, frame = cap.read()
        if(ret == False):
            break

        writer_origin.write(frame)
        print(f'Gate={gate}')
        keypress = cv2.waitKey(1)
        if keypress == ord("q"):
            break
        keyCondition(keypress)

        frame1 = frame.copy()
        if (gate == 0 or gate == 2):  # 新增的(過濾地面綠色)
            frame1[int(frame1.shape[0]*7/11):, :, 1] = 0
        if(gate < 3):
            colorgate_center, erode = condition(
                frame, frame1, hsv_list[gate][gate_through_color[gate]])
        if (gate == 3):
            if(isFirstFixed):
                isFirstFixed = False
                write('E')
                cv2.waitKey(500)
                write('W')
                cv2.waitKey(2000)
                write('G')
                cv2.waitKey(300)
            findRectangle(frame)
        if gate == 4:
            findCircle(frame)
        if gate == 5:
            break

        cv2.waitKey(100)
        writer_erode.write(erode)
        writer_filter.write(colorgate_center)

        cv2.imshow("mask", erode)
        cv2.imshow("video", colorgate_center)

    write('G')
    cap.release()
    cv2.destroyAllWindows()
    writer_origin.release()
    writer_erode.release()
    writer_filter.release()


def record():
    cap = cv2.VideoCapture('/dev/video0')
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    writer = cv2.VideoWriter('record9.avi', fourcc, 32, (width, height))
    while True:
        ret, frame = cap.read()
        if(ret == False):
            break

        keypress = cv2.waitKey(1)
        if keypress == ord("q"):
            break
        keyCondition(keypress)

        writer.write(frame)
        cv2.imshow("frame", frame)

    write('G')
    cv2.destroyAllWindows()
    cap.release()
    writer.release()


def test():
    print(uart)
    cap = cv2.VideoCapture('/dev/video0')

    while True:
        ret, frame = cap.read()
        if(ret == False):
            break

        keypress = cv2.waitKey(1)
        if keypress == ord("q"):
            break
        keyCondition(keypress)

        cv2.imshow("frame", frame)

    write('G')
    cv2.destroyAllWindows()
    cap.release()


if __name__ == '__main__':
    main()
    # record()
    # test()
