# STM32PRO_RTX5
VSCode + clangd + CMake + pyOCD + armclang + RTX5 + STM32CubeMX
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
      "svdFile": "STM32F103xx.svd", // Need to change
      "targetId": "STM32F103ZE", // Need to change
      "cmsisPack": "Keil.STM32F1xx_DFP.2.3.0.pack" // Need to change
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
        "STM32F103ZE", // Need to change
        "--pack",
        "Keil.STM32F1xx_DFP.2.3.0.pack", // Need to change
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
