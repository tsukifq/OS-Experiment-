环境：Ubuntu18.04

qemu、riscv64gcc工具均已下载，安装，配好环境变量。

![image-20230714091213970](C:\Users\q\AppData\Roaming\Typora\typora-user-images\image-20230714091213970.png)

![image-20230714091125428](C:\Users\q\AppData\Roaming\Typora\typora-user-images\image-20230714091125428.png)

使用busybox，可在系统态下运行编译好的linux内核，使用指令能成功启动linux内核。

```
qemu-system-riscv64 -M virt -m 256M -nographic -kernel arch/riscv/boot/Image -drive file=rootfs.img,format=raw,id=hd0  -device virtio-blk-device,drive=hd0 -append "root=/dev/vda rw console=ttyS0"
```

![image-20230714091428808](C:\Users\q\AppData\Roaming\Typora\typora-user-images\image-20230714091428808.png)

接下来对于自己已经修改好的系统调用，希望通过一个用户态程序对其进行调试。类比于x86环境下gdb跟踪hello world的运行过程，可以看到它进入系统调用，在write函数处打断点能看到具体调用write函数时的一系列信息（见下图）。

![image-20230714092152361](C:\Users\q\AppData\Roaming\Typora\typora-user-images\image-20230714092152361.png)

![image-20230714093038499](C:\Users\q\AppData\Roaming\Typora\typora-user-images\image-20230714093038499.png)

在riscv64环境下，使用qemu，参考以下教程[RISC-V 汇编语言程序的调试 - 计算机组成原理（2021年） (tsinghua.edu.cn)](https://lab.cs.tsinghua.edu.cn/cod-lab-docs/labs/5-riscv-assem/)

打好断点，运行continue指令调试自己写的程序时，相比于上述教程中运行到设置好的断点处0x80000000停止运行（如下图），实际上会从0x1000一直运行下去（陷入类似死循环的地方），没有经过自己打的断点处。即实际没有运行自己写的程序。推测原因是代码段放置位置有误（64位系统中不能放到0x80000000处），不知如何解决。

![image-20230714102848026](C:\Users\q\AppData\Roaming\Typora\typora-user-images\image-20230714102848026.png)