COMMON_OBJECTS = x

CPU = msp430g2553
CFLAGS = -mmcu=${CPU} -Os -I../h
LDFLAGS = -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC =msp430-elf-gcc
AS = msp430-elf-gcc -mmcu={CPU} -c

all: blinkMain.elf

blinkMain.elf: ${x} blinkMain.o p2_interrupt_handler.o led.o switches.o buzzer.o StateMachine.o wdInterruptHandler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd
load: blinkMain.elf
	msp430loader.sh $^
clean:
	rm -f *.o *.elf
