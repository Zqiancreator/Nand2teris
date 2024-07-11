// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/8/FunctionCalls/StaticsTest/StaticsTest.tst

// Tests StaticTest.asm in the CPU emulator.
// This assembly file results from translating the staticsTest folder.

load StaticsTest.asm,
output-file StaticsTest.out,
compare-to StaticsTest.cmp,

set RAM[0] 261,
set RAM[1] 261,
set RAM[2] 310,    // ARG
set RAM[3] 3000,   // THIS
set RAM[4] 4000,   // THAT

repeat 2500 {
	ticktock;
}

output-list RAM[0]%D1.6.1 RAM[261]%D1.6.1 RAM[262]%D1.6.1;
output;
