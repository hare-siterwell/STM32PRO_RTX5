cmake_minimum_required(VERSION 3.21)

# Specify the cross compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(TOOLCHAIN_PATH C:/keil_v5/ARM/ARMCLANG/)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}bin/armclang.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}bin/armclang.exe)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

set(CMAKE_C_LINK_EXECUTABLE ${TOOLCHAIN_PATH}bin/armlink.exe)
set(CMAKE_CXX_LINK_EXECUTABLE ${TOOLCHAIN_PATH}bin/armlink.exe)
set(CMAKE_ASM_LINK_EXECUTABLE ${TOOLCHAIN_PATH}bin/armlink.exe)

set(FPU_FLAG "-mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(COMMON_FLAGS "--target=arm-arm-none-eabi -mcpu=${CMAKE_SYSTEM_PROCESSOR} ${FPU_FLAG}")
set(CMAKE_C_FLAGS " ${COMMON_FLAGS} -std=c99 -O3 -Wall -fno-rtti -c -ffunction-sections -gdwarf-4")
set(CMAKE_CXX_FLAGS " ${COMMON_FLAGS} -std=c++11 -O3 -Wall -fno-rtti -c -ffunction-sections -gdwarf-4")
set(CMAKE_ASM_FLAGS " ${COMMON_FLAGS} -masm=auto -c -gdwarf-3")

set(SECTIONS_SCRIPT_PATH ${CMAKE_SOURCE_DIR}/SYSTEM/Sections.sct)
set(CMAKE_EXE_LINKER_FLAGS "
    --cpu Cortex-M4.fp.sp \
    --strict --scatter ${SECTIONS_SCRIPT_PATH} \
    --summary_stderr --info summarysizes \
    --map --load_addr_map_info --xref --callgraph --symbols \
    --info sizes --info totals --info unused --info veneers \
    "
)

enable_language(ASM)

# Configure the project
project(STM32PRO C ASM)
add_definitions(-DSTM32F407xx)
include_directories(Core/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
    ${TOOLCHAIN_PATH}include
    ${TOOLCHAIN_PATH}include/arm_linux
    ${TOOLCHAIN_PATH}include/arm_linux_compat
    ${TOOLCHAIN_PATH}include/libcxx
    SYSTEM/Inc
)

file(GLOB_RECURSE SOURCES
    Core/Src/*.c
    Drivers/STM32*_Driver/Src/*.c
    SYSTEM/Src/*.[sc]
)
add_executable(release ${SOURCES})

add_custom_command(TARGET release POST_BUILD
    COMMAND ${TOOLCHAIN_PATH}bin/fromelf.exe --i32 -o release.hex release.elf
)
