cmake_minimum_required(VERSION 3.21)

# 设置目标机器类型
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

# 设置工具链路径
set(TOOLCHAIN_PATH C:/keil_v5/ARM/ARMCLANG/bin/)

# 设置编译器
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}armclang.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}armclang.exe)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

# 设置链接器
set(CMAKE_C_LINK_EXECUTABLE ${TOOLCHAIN_PATH}armlink.exe)
set(CMAKE_CXX_LINK_EXECUTABLE ${TOOLCHAIN_PATH}armlink.exe)
set(CMAKE_ASM_LINK_EXECUTABLE ${TOOLCHAIN_PATH}armlink.exe)

 # 设置FPU
set(FPU_FLAG "-mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# 设置Sections脚本路径
set(SECTIONS_SCRIPT_PATH ${CMAKE_SOURCE_DIR}/SYSTEM/Sections.sct)

# 设置通用编译参数
set(COMMON_FLAGS "--target=arm-arm-none-eabi -mcpu=${CMAKE_SYSTEM_PROCESSOR} ${FPU_FLAG}")

# 设置C编译器选项
set(CMAKE_C_FLAGS " ${COMMON_FLAGS} -std=c99 -O3 -Wall -fno-rtti -c -ffunction-sections -gdwarf-4")

# 设置C++编译器选项
set(CMAKE_CXX_FLAGS " ${COMMON_FLAGS} -std=c++11 -O3 -Wall -fno-rtti -c -ffunction-sections -gdwarf-4")

# 设置ASM编译器选项
set(CMAKE_ASM_FLAGS " ${COMMON_FLAGS} -masm=auto -c -gdwarf-3")

# 设置链接选项
set(CMAKE_EXE_LINKER_FLAGS "
    --cpu Cortex-M4.fp.sp \
    --strict \
    --scatter ${SECTIONS_SCRIPT_PATH} \
    --summary_stderr \
    --info summarysizes \
    --map --load_addr_map_info --xref --callgraph --symbols \
    --info sizes --info totals --info unused --info veneers \
    "
)

# 使能汇编
enable_language(ASM)

# 配置工程
project(STM32PRO C ASM)

# 添加全局宏定义
add_definitions(-DSTM32F407xx)

# 添加头文件引用目录
include_directories(Core/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
    C:/Keil_v5/ARM/ARMCLANG/include
    C:/Keil_v5/ARM/ARMCLANG/include/arm_linux
    C:/Keil_v5/ARM/ARMCLANG/include/arm_linux_compat
    C:/Keil_v5/ARM/ARMCLANG/include/libcxx
    SYSTEM/Inc
    RTOS2/RTX/Include
    RTOS2/Include
    RTOS2/RTX/Config
)

# 添加源文件
file(GLOB_RECURSE SOURCES
    Core/Src/*.c
    Drivers/STM32*_Driver/Src/*.c
    SYSTEM/Src/*.*
    RTOS2/RTX/Source/GCC/irq_armv7m.S
    RTOS2/RTX/Source/*.c
    RTOS2/Source/*.c
    RTOS2/RTX/Config/*.c
)

# 添加生成可执行文件
add_executable(release ${SOURCES})

# 生成hex
add_custom_command(TARGET release POST_BUILD
    COMMAND ${TOOLCHAIN_PATH}fromelf.exe --i32 -o release.hex release.elf
)
