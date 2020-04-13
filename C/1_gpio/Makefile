objs := start.o app.o

gpioctrl.bin:$(objs)
	arm-linux-gnueabihf-ld -Ttext 0x87800000 -o gpioctrl.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S gpioctrl.elf $@
	arm-linux-gnueabihf-objdump -D -m arm gpioctrl.elf > gpioctrl.dis

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o *.bin *.elf *.dis
