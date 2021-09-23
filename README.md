# STM32PRO_RTX5
VSCode + clangd + CMake + pyOCD + ARMClang + RTX5 + STM32CubeMX
## Features
- Cool

## Getting Started

### launch.json
```
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "pyOCD",
      "type": "cortex-debug",
      "request": "launch",
      "cwd": "${workspaceFolder}",
      "servertype": "pyocd",
      "executable": "build/release.elf",
      "runToMain": true,
      "svdFile": "STM32F40x.svd",
      "targetId": "STM32F407ZG",
      "cmsisPack": "Keil.STM32F4xx_DFP.2.15.0.pack"
    }
  ]
}
```

### tasks.json
```
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Load",
      "type": "shell",
      "command": "pyocd",
      "args": [
        "flash",
        "--erase",
        "sector",
        "--target",
        "STM32F407ZG",
        "--pack",
        "Keil.STM32F4xx_DFP.2.15.0.pack",
        "build/release.hex"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```

### pyOCD (Need Python)
```
pip install pyocd
```

### VSCode Extensions
- C/C++
- clangd
- CMake
- CMake Tools
- Cortex-Debug
