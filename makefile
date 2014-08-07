PROJECTNAME=PongOS

$(PROJECTNAME): bin/*.bin
	cat $? > $(PROJECTNAME).bin

	@if [ -e $(PROJECTNAME).flp ]; then rm -f $(PROJECTNAME).flp; fi;
	@dd status=noxfer conv=notrunc if=$(PROJECTNAME).bin of=$(PROJECTNAME).flp

	rm -f $(PROJECTNAME).bin

bin/*.bin: *.asm
	@if ! [ -d bin ]; then mkdir bin; fi
	for i in $(basename $?); do nasm -f bin -o $$i.bin $$i.asm; done

	mv -f *.bin bin/

run: $(PROJECTNAME)
	qemu-system-i386 -fda $(PROJECTNAME).flp
