# C4M-robot-car

## 目錄 | Content
- [C4M-robot-car](#c4m-robot-car)
  - [目錄 | Content](#目錄--content)
  - [專案起源與背景 | Background](#專案起源與背景--background)
    - [專案起源](#專案起源)
    - [專案背景](#專案背景)
    - [競賽規則](#競賽規則)
  - [賽道任務流程 | Mission Workflow](#賽道任務流程--mission-workflow)
  - [實現邏輯 | Implementation](#實現邏輯--implementation)
    - [1. 前置設定 (Setup)](#1-前置設定-setup)
    - [2. 啟動任務 (Execution)](#2-啟動任務-execution)
    - [3. 自主運行邏輯 (Autonomous Logic)](#3-自主運行邏輯-autonomous-logic)
  - [硬體規格 | Hardware](#硬體規格--hardware)
    - [核心計算平台](#核心計算平台)
    - [動力與影像系統](#動力與影像系統)
    - [電源系統](#電源系統)
    - [硬體照片](#硬體照片)
  - [系統架構 | System Architecture](#系統架構--system-architecture)
  - [運行環境 | Software](#運行環境--software)
    - [相關資源連結](#相關資源連結)
    - [1. 安裝 avrdude (Windows)](#1-安裝-avrdude-windows)
    - [2. 安裝 asaloader](#2-安裝-asaloader)
    - [3. 安裝 RS232terminal](#3-安裝-rs232terminal)
    - [4. 安裝 AVR 8-bit Toolchain](#4-安裝-avr-8-bit-toolchain)
  - [如何運行 | How to Run](#如何運行--how-to-run)
    - [1. ASA 底層控制 (ASA Control)](#1-asa-底層控制-asa-control)
    - [2. 樹梅派影像辨識 (Raspberry Control)](#2-樹梅派影像辨識-raspberry-control)
    - [3. 遠端控制端 (Remote Control Interface) - *Competition Official*](#3-遠端控制端-remote-control-interface---competition-official)
  - [專案結果 | Project Results](#專案結果--project-results)
  - [參考專案與資源 | References](#參考專案與資源--references)

---

## 專案起源與背景 | Background
### 專案起源
本專案實作 **2021 東京威力科創機器人大賽-鋼鐵擂台** 之競賽任務，並針對上半場「智慧賽道」的自動化導引進行特化開發。

### 專案背景
本專案 Fork 自原始競賽專案：[void110916/C4M-robot-car](https://github.com/void110916/C4M-robot-car)。
原始專案是由本人、 **void110916** 與另外一位組員 共同協作完成的參賽專案。為了進一步優化 **自動化光學檢測 (AOI)** 與 **精準顏色辨識** 技術，我將原專案進行延伸開發，專門針對「關卡一：直線行走」之挑戰進行硬體特化，並將其獨立為目前這個 Repo。

### 競賽規則
**官方規則參考**：[2021 TEL Robot Combat 競賽規則 (PDF)](https://cdn.bountyhunter.co/file/c47dcc6c-9e44-54ce-84c1-6cf93e437aab.pdf)

## 賽道任務流程 | Mission Workflow
> [!IMPORTANT]
> 智慧賽道 - 關卡一：直線行走  
> 機器人需利用影像處理技術，自主辨識並通過指定顏色的拱門。

* **設計規範與場地布置**
    * 動態顏色判定：三道關卡的通過順序由現場抽籤決定。
    * 賽道規格：總長 **350cm**，寬 **100cm**。
    * 障礙間隔：拱門間距 **95cm**。
    * 辨識目標：色板下緣離地高度為 **22cm**。

|<img src="./image/course_spec.jpg" height="250">|<img src="./image/course.png" height="250">|
|:----------------------------------------------:|:-----------------------------------------:|
|圖：關卡設計規範                                 |圖：場地布置實景                             |




## 實現邏輯 | Implementation
本專案透過 **Raspberry Pi 4** 作為運作核心，實現從影像辨識到運動控制的全自動化流程。

### 1. 前置設定 (Setup)
透過 VNC 遠端連入樹梅派桌面環境，執行控制程式。使用者需根據現場抽籤結果，於終端機（CLI）輸入三層關卡欲偵測的目標顏色順序（例如：綠、藍、紅）。

<img src="./image/vnc_terminal_interface.png" height="300">

*圖：自動化模式下的參數設定介面*

### 2. 啟動任務 (Execution)
設定完成後，系統即由待命狀態轉入自動化任務模式。

### 3. 自主運行邏輯 (Autonomous Logic)
*   **影像辨識**：啟動 OpenCV 捕捉畫面，針對特定高度（22cm）區域進行色彩過濾與輪廓偵測。
*   **決策判斷**：比對當前辨識到的色塊是否符合預設關卡顏色。
*   **運動控制**：
    *   若顏色正確，系統計算色塊中心點位移，進行路徑修正。
    *   指令由樹梅派透過 **Micro-USB** 傳輸至 **M128**，最終驅動底層麥克納姆輪執行避障與推進。

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

### 硬體照片
| <img src="./image/car_original.png" height="250"> | <img src="./image/car_aoi_specialized.png" height="250"> |
| :-----------------------------------------------: | :------------------------------------------------------: |
|原始賽事版本：完整競賽配置（含手臂與貨斗）             |AOI 課程特化版本：精簡化架構                                |

## 系統架構 | System Architecture
```
+-------------------+       +-------------------+       +-------------------+
|                   |       |                   |       |                   |
|       (1)         |       |       (2)         |       |       (3)         |
|      電源板       | Power |       樹梅派       |<----->|       鏡頭        |
| (Power / Wiring)  |------>|   [影像辨識中心]   |       |     (Camera)      |
|                   |       |                   |       |                   |
+-----|-------------+       +---------|---------+       +-------------------+
      |                               | 
 Power|     +-------------------------+ Micro-USB
      |     | UART0                     
      v     v                     
+-------------------+       +-------------------+       +-------------------+
|                   |       |                   |       |                   |
|       (4)         |       |       (5)         |       |       (6)         |
|     ASA M128      | UART1 |  Extension Board  |  PWM  |     4x Servos     |
|    (ATmega128)    |------>|   (ATmega328PB)   |------>|  (Mecanum Wheels) |
|    [邏輯處理]      |       |  [馬達驅動擴充板]  |       |                   |
+-------------------+       +-------------------+       +-------------------+
```
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

### 1. ASA 底層控制 (ASA Control)
* **編譯函數庫文件：**
    ```bash
    git clone --branch 3.9.0 https://gitlab.com/MVMC-lab/c4mlib/c4mlib.git
    make -C c4mlib/c4mlib
    ```

* **燒錄主控 (Master):**
    ```bash
    make -C ASA_control/master
    asaloader prog -p COM{num} -f ASA_control/master/master.hex
    terminal -p {num} -b 38400
    ```

* **燒錄從屬 (Slave):**
    ```bash
    make -C ASA_control/slave
    avrdude -c atmelice_isp -p m328pb -U flash:w:ASA_control/slave/slave.hex:i
    ```

### 2. 樹梅派影像辨識 (Raspberry Control)
處理 OpenCV 顏色偵測與自動化導引邏輯：
  1.  **連線**：  
        需先透過 **RealVNC** 遠端連入樹梅派桌面環境。
  2.  **執行指令**：  
        ```bash
        # 環境安裝
        sudo apt-get update && sudo apt-get install -y libopencv-dev python3-opencv
        pip install -r raspberry_control/requirements.txt

        # 啟動辨識程式
        python raspberry_control/color.py
        ```
  3.  **通訊邏輯(上半場 - 關卡一)**：  
        電腦 (監控) $\rightarrow$ RealVNC (WiFi) $\rightarrow$ 樹梅派 (RPi 4) $\rightarrow$ Micro-USB (Data) $\rightarrow$ M128 $\rightarrow$ Extension Board

### 3. 遠端控制端 (Remote Control Interface) - *Competition Official*
> [!TIP]
> 此介面為「東京威力科創機器人大賽-鋼鐵擂台」下半場任務專用的正式操控終端。

1. **功能定位**：  
   * 操控整合：提供操作員即時控制麥克納姆輪、5 軸機械手臂、以及監控避障感測器狀態的功能。
   * 即時狀態可視化：介面右側區域可即時顯示車斗及機械手臂相對於車體的空間位置（Side/Top View），輔助操作員精準抓取目標。
   * 注意：由於車體機構並非本人繪製，為尊重原創者，本專案不提供相關機構模型（.obj）。因此，在運行此控制介面時，側視圖與頂視圖（Side/Top View）區域將無法正常顯示模型，但不影響其他遙控功能。

2.  **開發環境與編譯**：  
    若需重新編譯該控制介面，請確保環境具備 .NET SDK並透過Visual Studio 執行：
    ```bash
    cp model_Robot/* remote_control/Bluetooth/model_Robot/
    dotnet build "remote_control/Bluetooth.sln"
    ```

    <img src="./image/robot_control_gui.png" height="250">

    圖：正式賽事所使用的 C# GUI 操控面板

3. 通訊邏輯(下半場模式)：  
    電腦 $\rightarrow$ 藍牙 (Bluetooth) $\rightarrow$ Extension Board $\rightarrow$ M128。

## 專案結果 | Project Results
[![專案演示影片](https://img.youtube.com/vi/AP3a90r8Y54/hqdefault.jpg)](https://www.youtube.com/watch?v=AP3a90r8Y54)

點擊上方圖片跳轉至 YouTube 觀看實作演示


## 參考專案與資源 | References
* [Original Competition Repo](https://github.com/void110916/C4M-robot-car) - 包含上半場及下半場的程式控制邏輯。
* [Official Work Log](https://fast-wash-f15.notion.site/2021-6259e3a77f734da6a909c0269e0526be) - 詳細的硬體設計細節與賽事背景。