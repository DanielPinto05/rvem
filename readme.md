## What it is

rvem stands for RISC-V Emulator, which is the ultimate goal of the project. 

Before I started with an emulator, I wanted an assembler first. So currently that's what asm.cpp aims to do. It's been demoed only with the addi instruction, but many more instructions to come!

## How to build and use the assembler

1. Put your assembly file into the inputs folder
2. Compile asm.cpp. Ctrl+Shift+B to use VS Code build preferences, which will leave the executable in build folder
3. Run 
` ./build/asm t1`
to assembler t1. 
Note: Currently you need to run this from the top-level directory rvem, otherwise the program can't find your input file.
4. Machine code will output as a .txt file of the same name in the inputs folder. In the example above, t1.txt will be the output. 

## Emulator

To come, once the assembler works reasonably well!