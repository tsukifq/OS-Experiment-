nasm编译命令：nasm boot.asm -o boot.bin

bochs软盘创建：Bximage根据提问选项选择fd 1.44 a.img

bochsrc修改：核心是路径

romimage: file=/home/qj/Downloads/workspace/bochs-2.6.8/bios/BIOS-bochs-latest
vgaromimage: file=/home/qj/Downloads/workspace/bochs-2.6.8/bios/VGABIOS-lgpl-latest

keyboard: keymap=/home/qj/Downloads/workspace/bochs-2.6.8/gui/keymaps/x11-pc-us.map

写到软盘第一个扇区：dd if=boot.bin of=a.img bs=512 count=1 conv=notrunc

启动：bochs -f bochsrc