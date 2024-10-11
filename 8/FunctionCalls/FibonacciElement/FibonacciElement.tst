// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/8/FunctionCalls/FibonacciElement/FibonacciElement.tst

// Tests FibonacciElement.asm on the CPU emulator. 
// FibonacciElement.asm results from translating Main.vm and Sys.vm into
// a single assembly program, stored in the file FibonacciElement.asm.

load FibonacciElement.asm,
output-file FibonacciElement.out,
compare-to FibonacciElement.cmp,

set RAM[0] 261,    // SP
set RAM[1] 261,    // LCL
set RAM[2] 310,    // ARG
set RAM[3] 3000,   // THIS
set RAM[4] 4000,   // THAT

repeat 6000 {
	ticktock;
}

// Outputs the stack pointer and the value at the stack's base.
// That's where the implementation should put the return value.
output-list RAM[0]%D1.6.1 RAM[261]%D1.6.1;
output;
