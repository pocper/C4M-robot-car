# raspberry Pi -> ASA V3 Master
# Created Time : 110/11/13
# Author : Tommy Huang

INC = -I "./"

Target = servo

$(Target).exe:$(Target).o
	@ gcc $< -o $@
	@ rm -f *.o
	@ servo.exe

servo.o:servo.c
	@ gcc -c $< $(INC) -o $@

.PHONY: cls

cls:
	@ rm -f *.o *.exe
