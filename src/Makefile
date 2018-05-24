ifeq ($(OS),Windows_NT)
	TARGET = anago.exe
	LIBUSB = ../LibUSB-Win32
else
	TARGET = anago
	LIBUSB = ../libusb
endif

all: $(TARGET)
KAZZO = ../kazzo/firmware
SQUIRREL = ../SQUIRREL3
#CFLAGS += -g -O0
CFLAGS += -O2
CFLAGS += -Wall -Werror -I$(LIBUSB)/include -I$(SQUIRREL)/include -I$(KAZZO) -DDEBUG=1 -DANAGO=1
LDFLAG += -L. -L$(LIBUSB)/lib/gcc -L$(SQUIRREL)/lib
CC = gcc
OBJ = anago.o header.o crc32.o file.o interop.o \
	script_flash.o script_dump.o script_common.o \
	progress.o flash_device.o \
	reader_dummy.o reader_kazzo.o usb_device.o squirrel_wrap.o memory_manage.o
clean:
	rm -f $(OBJ) $(TARGET)
$(TARGET): $(OBJ) 
	g++ -o $@ $(LDFLAG) $(OBJ) -lusb -lsqstdlib -lsquirrel
install:
	rm -rf ../dist
	mkdir ../dist
	cp $(TARGET) scripts/* ../*.txt ../dist

script_flash.o: squirrel_wrap.h
script_dump.o: squirrel_wrap.h

