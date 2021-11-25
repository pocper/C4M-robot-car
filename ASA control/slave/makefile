# 最後更改時間
# 日期 : 2021/10/12

#for atmega328 擴充板

INC  +=  -I "../"
INC  +=  -I "./"
INC  +=  -I "C:\Program Files (x86)\Atmel\Studio\7.0\packs\atmel\ATmega_DFP\1.7.374\include"

CFLAGS    = -mmcu=atmega328pb
CFLAGS   += -DF_CPU=8000000UL
CFLAGS   += -B "C:\Program Files (x86)\Atmel\Studio\7.0\packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega328pb"
CFLAGS   += -Wall -std=gnu99 -Os
CFLAGS   += -funsigned-char -funsigned-bitfields
CFLAGS   += -fpack-struct -fshort-enums 
CFLAGS   += -lprintf_flt -lscanf_flt
CFLAGS   += -Wl,-u,vfprintf -Wl,-u,vfscanf


HEXFLAGS  = -R .eeprom -R .fuse -R .lock -R .signature

PORT    = 8

o2elf   = avr-gcc $^ $(CFLAGS) $(LIB) -o $@
c2o     = avr-gcc -c $< $(CFLAGS) $(INC) -o $@

Red     = \e[1;31m
Yellow  = \e[1;33m

Error   = error[^\n]*
Warning = warning[^\n]*

R_Replace = \\$(Red)&\\\e[0m
Y_Replace = \\$(Yellow)&\\\e[0m

error_msg   = -e 's|$(Error)|$(R_Replace)|gI'
warning_msg = -e 's|$(Warning)|$(Y_Replace)|gI'
delete_msg  = -e 's|\[[^\n]*||g'

o_msg = $$($(o2elf) 2>&1 | sed $(delete_msg) $(error_msg) $(warning_msg))
c_msg = $$($(c2o) 2>&1 | sed $(delete_msg) $(error_msg) $(warning_msg))

SRC = $(wildcard ../*.c ./*.c ./src/*.c)
OBJ = $(addsuffix .o,$(basename $(SRC)))

slave.hex:slave.elf
	@ avr-objcopy -O ihex $(HEXFLAGS) $< $@
	@ rm -f *.elf 
	@ echo Complete file!

slave.elf: $(OBJ)
	@ echo -e "$(o_msg)"
	@ rm -f *.o

%.o:%.c
	@ echo -e "$(c_msg)"

.PHONY: cls load term test

cls:
	@ rm -f *.o src/*.o *.elf *.hex
	@ echo Complete clean!

load:
	@ asaloader prog -p COM$(PORT) -f slave.hex

term:
	@ terminal -p $(PORT) -b 38400