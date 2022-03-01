.PHONY: all
all: barebones.iso

.PHONY: run
run: barebones.iso
	qemu-system-x86_64 -M q35 -m 2G -cdrom barebones.iso

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1
	make -C limine

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

barebones.iso: limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp kernel/kernel.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-eltorito-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-eltorito-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o barebones.iso
	limine/limine-install barebones.iso
	rm -rf iso_root

.PHONY: clean
clean:
	rm -f iso_root barebones.iso
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf limine
	$(MAKE) -C kernel distclean
