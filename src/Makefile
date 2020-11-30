COMMON_OBJECTS = 

CPU = msp430g2553
CFLAGS = -mmcu=${CPU}  -I../h
LDFLAGS = -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC =msp430-elf-gcc
AS = msp430-elf-as

all: blinkMain.elf

blinkMain.elf: ${x} blinkMain.o p2_interrupt_handler.o led.o switches.o buzzer.o StateMachine.o lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
load: blinkMain.elf
	msp430loader.sh blinkMain.elf
clean:
	rm -f *.o *.elf
