set disassembly-flavor intel
symbol-file kernel.elf
target remote localhost:1234
layout asm
break KernelMain
continue