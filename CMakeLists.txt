cmake_minimum_required(VERSION 3.10)

project(MidnightOS VERSION 1.0 LANGUAGES C CXX ASM)

enable_language(ASM_NASM)

# Specify compilers
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_ASM_NASM_COMPILER nasm)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_FLAGS "-lgcc -Wl,--export-dynamic -I./src/ -Wall -O0 -fno-stack-protector -fno-omit-frame-pointer -Wextra -ffreestanding -fno-stack-check -fno-lto -ffunction-sections -fdata-sections -m64 -msse -mno-mmx -mno-sse2 -fno-pic -mno-sse3 -mno-ssse3 -mno-avx -mno-avx2 -mno-avx512f -mno-red-zone -march=x86-64 -static -Isrc/ -Wformat-security -Wformat -g -mcmodel=kernel")
set(CMAKE_CXX_FLAGS "-lgcc -Wl,--export-dynamic -I./src/ -fpermissive -fno-rtti -fno-omit-frame-pointer -Wall -O0 -fno-stack-protector -Wextra -ffreestanding -fno-stack-check -fno-lto -ffunction-sections -fdata-sections -fno-exceptions -fno-pic -m64 -msse -mno-mmx -mno-sse2 -mno-sse3 -mno-ssse3 -mno-avx -mno-avx2 -mno-avx512f -mno-red-zone -march=x86-64 -fno-threadsafe-statics -std=c++20 -Isrc/ -Wformat-security -Wformat -g -mcmodel=kernel")
set(CMAKE_EXE_LINKER_FLAGS "-lgcc -nostdlib -static -z text -T ../linker.ld -Wl,--export-dynamic -z max-page-size=0x1000")
set(CMAKE_ASM_NASM_FLAGS "-f elf64")

# Define executable
add_executable(MidnightOS
        src/kernel.h
        src/init/main.c
        src/cpu/cpu.h
        src/cpu/cpu.c
        src/hal/gdt/gdt.c
        src/hal/gdt/gdt.h
        src/hal/initialize_arch.c
        src/hal/initialize_arch.h
        src/init/init.asm
        src/hal/gdt/flush_gdt.asm
        src/kdbg/debug_print.c
        src/kdbg/debug_print.h
        src/hal/io.c
        src/hal/io.h
        src/rtl/linked_list.c
        src/rtl/linked_list.h
        src/ke/error.c
        src/ke/error.h
        src/rtl/kcruntime.c
        src/rtl/spinlock.c
        src/rtl/spinlock.h
        src/ke/irql.c
        src/ke/irql.h
        src/ke/bugcheck.c
        src/ke/bugcheck.h
        src/ke/stacktrace.c
        src/ke/stacktrace.h
        src/hal/spratcher/spinit.c
        src/hal/spratcher/spinit.h
        src/mm/physical.c
        src/mm/physical.h
        src/rtl/limine.h
        src/mm/common.c
        src/mm/common.h
        src/hal/idt/idt.asm
        src/hal/idt/idt.c
        src/hal/idt/idt.h
        src/hal/idt/isr.c
        src/hal/idt/idt.inc
        src/hal/idt/raw_idt_table.c
        src/hal/idt/raw_idt_table.h
        src/rtl/dlmalloc.c
        src/rtl/dlmalloc.h
        src/mm/virtual.c
        src/mm/virtual.h
        src/mm/vmem-allocator.c
        src/mm/vmem-allocator.h
        src/mm/paging.h
        src/rtl/runtime.h
        src/ob/object.c
        src/ob/object.h
        src/se/descriptor.h
        src/se/manager.c
        src/se/manager.h
        src/rtl/memory.c
        src/rtl/memory.h
        src/hal/spratcher/features.c
        src/hal/spratcher/features.h
        src/hal/spratcher/features.asm

)

# Include directories
include_directories(MidnightOS PRIVATE src)
include_directories(MidnightOS PRIVATE src/acpi/)
include_directories(MidnightOS PRIVATE src/mem/liballoc/)
# target_include_directories(MidnightOS PRIVATE src)

# Post-build custom target
add_custom_target(PostBuild ALL
    COMMAND ${CMAKE_COMMAND} -E rename MidnightOS kernel.elf
    COMMAND chmod +x ../iso.sh
    COMMAND ../iso.sh
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Post-build: Renaming MidnightOS to kernel.elf and invoking iso.sh"
    DEPENDS MidnightOS
)

# QEMU execution custom target
add_custom_target(PerformAll ALL
    COMMAND qemu-system-x86_64.exe -cpu qemu64,+fsgsbase,+syscall -M smm=off -smp 6 -M q35 -m 2G -debugcon stdio -cdrom image.iso -drive if=pflash,unit=0,format=raw,file=../ovmf/ovmf-code-x86_64.fd,readonly=on -drive if=pflash,unit=1,format=raw,file=../ovmf/ovmf-vars-x86_64.fd
    DEPENDS PostBuild
)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE SOURCE_FILES
            ${CMAKE_SOURCE_DIR}/src/*.c
            ${CMAKE_SOURCE_DIR}/src/*.cpp
            ${CMAKE_SOURCE_DIR}/src/*.h
    )
    add_custom_target(Format
            COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES}
            COMMENT "Running clang-format on source files"
    )
endif()