#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <sys/file.h>
int dev_open(int num)
{
    uint8_t path[14] = {0};
    sprintf(path, "/dev/ttyACM%d", num);
    int fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK); //

    if (fd < 0)
    {
        fprintf(stderr, "open port %d failed :%d\n", num, strerror(errno));

        exit(EXIT_FAILURE);
    }
    else
        fprintf(stdout, "connect to %s\n", path);
    struct stat st;
    stat(path, &st);
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    tty.c_cflag &= ~PARENB;        // Clear parity bit, disabling parity (most common)
    tty.c_cflag |= PARENB;         // Set parity bit, enabling parity
    tty.c_cflag &= ~CSTOPB;        // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CSTOPB;         // Set stop field, two stop bits used in communication
    tty.c_cflag &= ~CSIZE;         // Clear all the size bits, then use one of the statements below
    tty.c_cflag |= CS8;            // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS;       // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CRTSCTS;        // Enable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;                                                        // Disable echo
    tty.c_lflag &= ~ECHOE;                                                       // Disable erasure
    tty.c_lflag &= ~ECHONL;                                                      // Disable new-line echo
    tty.c_lflag &= ~ISIG;                                                        // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST;                                                       // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR;                                                       // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT IN LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT IN LINUX)
    tty.c_cc[VTIME] = 0; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;
    cfsetspeed(&tty, B115200);
    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        fprintf(stderr, "Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
    if (flock(fd, LOCK_EX | LOCK_NB) == -1)
    {
        fprintf(stderr, "Serial port with file descriptor %d is already locked by another process.", fd);
    }
    fprintf(stdout, "ID of containing device:  [%jx,%jx]\n",
            (uintmax_t)major(st.st_dev),
            (uintmax_t)minor(st.st_dev));
    return fd;
}
void dev_close(int fd)
{
    int rts = TIOCM_RTS | TIOCM_DTR;
    ioctl(fd, TIOCMBIC, &rts);
    close(fd);
}
int main()
{
    uint8_t buf[100] = {0};

    // FILE *ffd=fopen(path,)

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    int fd = dev_open(0);
    // int fd1 = dev_open(1);
    uint8_t state = 'n';
    uint8_t out[25] = {0};
    short i = 0;

    while (1)
    {
        sprintf(out, "%2d\n", i);
        i++;
        // fprintf(stdout, "%s\n", out);
        int num = write(fd, out, 4);
        // tcflush(0, TCIFLUSH);
        // if (num < 0)
        // {
        //     write(STDERR_FILENO, "err\n", 10);
        // }
        // write(fd1, out, 20);
        num = read(fd, buf, 100);
        if (num)
        {
            // fprintf(stdout, "i=%d\n",i);
            // write(STDERR_FILENO, "> ", num);
            write(STDOUT_FILENO, buf, num);
        }
        // int num = read(fd1, buf, 100);
        // if (num)
        // {
        //     write(STDOUT_FILENO, "com1\n", num);
        //     write(STDOUT_FILENO, buf, num);
        // }
        if (read(STDIN_FILENO, &state, 1))
            if (state == 'q')
                break;
        usleep(200);
    }
    dev_close(fd);
    exit(EXIT_SUCCESS);
}