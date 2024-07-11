// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.
(BEGIN)
	@R2
	D=M
	@BEGIN
	D;JGE	//R2>=0 wait for next input
	@R2
	M=0
	@CONDITION
	0;JMP
(LOOP)
	
	@R1
	D=M
	@R2
	M=M+D
(CONDITION)
	@R0
	M=M-1
	D=M
	@LOOP
	D;JGE
	@BEGIN
	0;JMP