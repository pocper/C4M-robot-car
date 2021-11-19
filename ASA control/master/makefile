# 最後更改時間
# 日期 : 2021/11/20
# 作者 : Tommy Huang
# 板子 : ASA_V3_Master

# ================================================================== #

# 使用者自定義路徑

# - MVMC-lab/c4mlib
# - 版本號 : e7b7ffa209d06a22c2e3bd52047e831eb89660de
# - 連結: https://gitlab.com/MVMC-lab/c4mlib/c4mlib

C4MLIB_Path = D:\AVR\C4MLIB_master

INC   =  -I "$(C4MLIB_Path)"

# C4M-robot-car/ASA control/global_def.h 及 C4M-robot-car/ASA control/pwm_def.h之檔案路徑
INC  +=  -I "../"

# C4M-robot-car/ASA control/master/之檔案路徑
INC  +=  -I "./"

# AtmelStudio 7.0函式庫路徑
INC  +=  -I "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\avr\include"

# C4MLIB_master\c4mlib\libc4m.a之檔案
# 需自行編譯函式庫!!
LIB   =  "$(C4MLIB_Path)\c4mlib\libc4m.a"

# 燒錄ASA_V3_Master之腳位
PORT    = 8
# ================================================================== #

# 自動化旗標

CFLAGS    = -mmcu=atmega128
CFLAGS   += -DF_CPU=11059200UL
CFLAGS   += -Wall -gdwarf-2 -std=gnu99 -Os -lm
CFLAGS   += -funsigned-char -funsigned-bitfields
CFLAGS   += -fpack-struct -fshort-enums 
CFLAGS   += -lprintf_flt -lscanf_flt
CFLAGS   += -Wl,-u,vfprintf -Wl,-u,vfscanf
CFLAGS   += -Wl,-u,USE_C4MLIB_INTERRUPT
CFLAGS   += -Wl,-u,USE_C4MLIB_STD_ISR

HEXFLAGS  = -R .eeprom -R .fuse -R .lock -R .signature

o2elf   = avr-gcc $^ $(CFLAGS) $(LIB) -o $@
c2o     = avr-gcc -c $< $(CFLAGS) $(INC) -o $@

Red     = \e[1;31m
Yellow  = \e[1;33m

Error   = error[^\n]*
Warning = warning[^\n]*

R_Replace   = \\$(Red)&\\\e[0m
Y_Replace   = \\$(Yellow)&\\\e[0m

error_msg = -e 's|$(Error)|$(R_Replace)|gI'
warning_msg = -e 's|$(Warning)|$(Y_Replace)|gI'
delete_msg = -e 's|\[[^\n]*||g'

o_msg   = $$($(o2elf) 2>&1 | sed $(delete_msg) $(error_msg) $(warning_msg))
c_msg   = $$($(c2o) 2>&1 | sed $(delete_msg) $(error_msg) $(warning_msg))

SRC = $(wildcard ../*.c ./*.c)
OBJ = $(addsuffix .o,$(basename $(SRC)))

master.hex:master.elf
	@ avr-objcopy -O ihex  $(HEXFLAGS) $< $@
	@ rm -f *.o  *.elf
	@ echo Complete file!
	@ asaloader prog -p COM$(PORT) -f $@
	@ terminal -p $(PORT) -b 38400

master.elf: $(OBJ)
	@ echo -e "$(o_msg)"

%.o:%.c
	@ echo -e "$(c_msg)"

.PHONY: cls load term

cls:
	@ rm -f *.o  *.elf *.hex
	@ echo Complete clean!

load:
	@ asaloader prog -p COM$(PORT) -f main.hex

term:
	@ terminal -p $(PORT) -b 38400