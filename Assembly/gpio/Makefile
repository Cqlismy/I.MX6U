all:gpioctrl.S
	arm-linux-gnueabihf-gcc -g -c gpioctrl.S -o gpioctrl.o
	arm-linux-gnueabihf-ld -Ttext 0x87800000 gpioctrl.o -o gpioctrl.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g gpioctrl.elf gpioctrl.bin
	arm-linux-gnueabihf-objdump -D gpioctrl.elf > gpioctrl.dis

clean:
	rm -rf *.o *.bin *.elf *.dis
