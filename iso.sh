
pwd

mkdir -p ../iso_root/
mkdir -p ../iso_root/boot
mkdir -p ../iso_root/boot/limine/
mkdir -p ../iso_root/EFI/
mkdir -p ../iso_root/EFI/BOOT
mkdir -p ../iso_root/Konfig

cp -v ../limine/limine-bios.sys ../iso_root/boot/limine
cp -v ../limine/limine-bios-cd.bin ../iso_root/boot/limine
cp -v ../limine/limine-uefi-cd.bin ../iso_root/boot/limine
cp -v ../limine/BOOTX64.EFI ../iso_root/EFI/BOOT
cp -v ../limine/BOOTIA32.EFI ../iso_root/EFI/BOOT
cp -v kernel.elf ../iso_root/kernel
cp -v ../limine.conf ../iso_root/

cat ../limine.conf

xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label -r -J -joliet-long -V "Midnight OS" ../iso_root/ -o "image.iso"

../limine/limine bios-install image.iso

rm -rf ../iso_root/
cp ./image.iso ../
