objs := start.o app.o

sdk.bin:$(objs)
	arm-linux-gnueabihf-ld -Timx6ul.lds -o sdk.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S sdk.elf $@
	arm-linux-gnueabihf-objdump -D -m arm sdk.elf > sdk.dis

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o *.bin *.elf *.dis
