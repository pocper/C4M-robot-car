# C4M-robot-car

## 目錄
[TOC]

---
## 專案起源與背景
### 專案起源
本專案實作 **2021 東京威力科創機器人大賽-鋼鐵擂台** 之競賽任務，並針對上半場「智慧賽道」的自動化導引進行特化開發。

### 專案背景
本專案 Fork 自原始競賽專案：[void110916/C4M-robot-car](https://github.com/void110916/C4M-robot-car)。
原始專案是由本人、 **void110916** 與另外一位組員 共同協作完成的參賽專案。為了進一步優化 **自動化光學檢測 (AOI)** 與 **精準顏色辨識** 技術，我將原專案進行延伸開發，專門針對「關卡一：直線行走」之挑戰進行演算法特化，並將其獨立為目前這個 Repo。

## 競賽題目：智慧賽道 - 關卡一：直線行走
機器人需利用影像處理技術，自主辨識並通過指定顏色的拱門。
*   **官方規則參考**：[2021 TEL Robot Combat 競賽規則 (PDF)](https://cdn.bountyhunter.co/file/c47dcc6c-9e44-54ce-84c1-6cf93e437aab.pdf)
*   **賽道規格重點**：
    *   總長 **350cm**，寬 **100cm**。
    *   拱門障礙物間距 **95cm**。
    *   色板下緣離地高度 **22cm**。

![關卡一設計規範](./image/course_spec.jpg)
![關卡一布置場地](./image/course.png)

## 硬體規格 | Hardware

### 核心計算平台
*   **Raspberry Pi 4 Model B (8GB RAM)**：執行 OpenCV 影像辨識與 AOI 邏輯。
*   **ASA M128 v3**：底層運動控制核心。
*   **ASA Robot Extension Board**：擴展感測器與馬達控制介面。

### 動力與影像系統
*   **移動系統**：4 組 **麥克納姆輪 ($\phi 60 mm$)** 搭配伺服機，支援全向移動。
*   **影像擷取**：[GC720P-U USB Camera (720p)](https://www.dmatektw.com/tw/product/267)。
*   **配置說明**：
    *   原始競賽專案採用雙鏡頭配置（車身與機械手臂末端各一），本專案因任務特化，僅保留安裝於**車身上**的單一鏡頭以進行路徑導引。
    *   與原始專案相比，本版本已拆卸 **5 軸機械手臂** 與 **貨斗機構**，以大幅減輕車體負擔並確保影像辨識視野無遮蔽。

### 電源系統
*   **Power Board**：自定義電源整合板（LM2596S DC-DC）。
*   **規格**：8.4V 降壓至 5V，可並聯 9 顆 18650 鋰電池並整合訊號接頭至 ASA Bus 40-pin。

| 原始賽事版本 | AOI 課程特化版本 |
| :--- | :--- |
| <img src="./image/car_original.png" height="250"> | <img src="./image/car_aoi_specialized.png" height="250"> |
| **狀態**：完整競賽配置（含手臂與貨斗） | **狀態**：精簡化架構，專注於影像導引 |
---

## 運行環境 | Software
<details>
<summary><b>點擊展開：詳細環境安裝與工具下載步驟</b></summary>

### 相關資源連結
*   [Github - RS232terminal](https://github.com/mickey9910326/RS232terminal)
*   [Official Website - AVR 8-bit Toolchain](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers)
*   [Github - avrdude](https://github.com/avrdudes/avrdude)

### 1. 安裝 avrdude (Windows)
```bash
curl -L -O https://github.com/avrdudes/avrdude/releases/download/v8.1/avrdude-v8.1-windows-x64.zip
mkdir avrdude && tar xvf avrdude-v8.1-windows-x64.zip -C avrdude
set PATH=%PATH%;%CD%\avrdude
```

### 2. 安裝 asaloader
> [!NOTE]
> 如果是 Windows 系統，需額外安裝 `gettext` 才能正確安裝 `asaloader`。

```bash
pip install -r ASA_control/requirements.txt
pip install asaloader --no-build-isolation
# 測試是否安裝成功
asaloader --help
```

### 3. 安裝 RS232terminal
```bash
git clone https://github.com/mickey9910326/RS232terminal.git
make -C RS232terminal/
set PATH=%PATH%;%CD%\RS232terminal
```

### 4. 安裝 AVR 8-bit Toolchain
```bash
curl -L -O https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/avr8-gnu-toolchain-4.0.0.52-win32.any.x86_64.zip
tar xvf avr8-gnu-toolchain-4.0.0.52-win32.any.x86_64.zip
set PATH=%PATH%;%CD%\avr8-gnu-toolchain-win32_x86_64\bin
```
</details>

## 如何運行 | How to Run

### 1. 樹梅派影像辨識 (Raspberry Control)
處理 OpenCV 顏色偵測與自動化導引邏輯：
1.  **連線**：需先透過 **RealVNC** 遠端連入樹梅派桌面環境。
2.  **執行指令**：
```bash
# 環境安裝
sudo apt-get update && sudo apt-get install -y libopencv-dev python3-opencv
pip install -r raspberry_control/requirements.txt

# 啟動辨識程式
python raspberry_control/color.py
```

### 2. ASA 底層控制 (ASA Control)
**編譯函數庫文件：**
```bash
git clone --branch 3.9.0 https://gitlab.com/MVMC-lab/c4mlib/c4mlib.git
make -C c4mlib/c4mlib
```

**燒錄主控 (Master):**
```bash
make -C ASA_control/master
asaloader prog -p COM{num} -f ASA_control/master/master.hex
terminal -p {num} -b 38400
```

**燒錄從屬 (Slave):**
```bash
make -C ASA_control/slave
avrdude -c atmelice_isp -p m328pb -U flash:w:ASA_control/slave/slave.hex:i
```

### 3. 遠端控制端 (Remote Control) - *Legacy*
Visual Studio 僅用於開發與編譯，若僅運行自動化任務則不需安裝。此部分程式碼保留自原始專案，本專案之自動化任務中**並不使用**。
```bash
cp model_Robot/* remote_control/Bluetooth/model_Robot/
dotnet build "remote_control/Bluetooth.sln"
```

---

## 專案結果 | Project Results
[![專案演示影片](https://img.youtube.com/vi/AP3a90r8Y54/0.jpg)](https://www.youtube.com/watch?v=AP3a90r8Y54)
圖：點擊上方圖片跳轉至 YouTube 觀看實作演示

---

## 參考專案與資源
*   [原始競賽專案 - void110916/C4M-robot-car](https://github.com/void110916/C4M-robot-car)
*   [原始競賽工作日誌](https://fast-wash-f15.notion.site/2021-6259e3a77f734da6a909c0269e0526be)