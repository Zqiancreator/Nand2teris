// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.
	@color
	M=0
(BEGIN)
	@SCREEN
	D=A
	@address
	M=D
	M=M-1
	@KBD
	D=M
	@BLACK
	D;JGT
	@WHITE
	0;JMP
(BLACK)
	@color
	D=M
	M=-1
	@BEGIN
	D;JLT
	@LOOP
	0;JMP
(WHITE)
	@color
	D=M
	M=0
	@BEGIN
	D;JEQ
	
(LOOP)
	@8192
	D=A
	@i
	M=D

(PAINT)
	@color
	D=M
	@address
	M=M+1
	A=M
	M=D
	@i
	M=M-1
	D=M
	@PAINT
	D;JGT
	@BEGIN
	0;JMP
	