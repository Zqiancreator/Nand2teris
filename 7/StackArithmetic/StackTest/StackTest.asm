@17
D=A
@SP
M=M+1
A=M-1
M=D
@17
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE0
D;JEQ
(FALSE0)
D=0
@END0
0;JMP
(TRUE0)
D=-1
(END0)
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
M=M+1
A=M-1
M=D
@16
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE1
D;JEQ
(FALSE1)
D=0
@END1
0;JMP
(TRUE1)
D=-1
(END1)
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
M=M+1
A=M-1
M=D
@17
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE2
D;JEQ
(FALSE2)
D=0
@END2
0;JMP
(TRUE2)
D=-1
(END2)
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
M=M+1
A=M-1
M=D
@891
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE3
D;JLT
(FALSE3)
D=0
@END3
0;JMP
(TRUE3)
D=-1
(END3)
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
M=M+1
A=M-1
M=D
@892
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE4
D;JLT
(FALSE4)
D=0
@END4
0;JMP
(TRUE4)
D=-1
(END4)
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
M=M+1
A=M-1
M=D
@891
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE5
D;JLT
(FALSE5)
D=0
@END5
0;JMP
(TRUE5)
D=-1
(END5)
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
M=M+1
A=M-1
M=D
@32766
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE6
D;JGT
(FALSE6)
D=0
@END6
0;JMP
(TRUE6)
D=-1
(END6)
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
M=M+1
A=M-1
M=D
@32767
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE7
D;JGT
(FALSE7)
D=0
@END7
0;JMP
(TRUE7)
D=-1
(END7)
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
M=M+1
A=M-1
M=D
@32766
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@TMP
M=D
@SP
M=M-1
A=M
D=M
@TMP
D=D-M
@TRUE8
D;JGT
(FALSE8)
D=0
@END8
0;JMP
(TRUE8)
D=-1
(END8)
@SP
A=M
M=D
@SP
M=M+1
@57
D=A
@SP
M=M+1
A=M-1
M=D
@31
D=A
@SP
M=M+1
A=M-1
M=D
@53
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@112
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
@SP
D=M-1
A=D
M=!M
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M&D
@SP
M=M+1
@82
D=A
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M|D
@SP
M=M+1
@SP
D=M-1
A=D
M=-M
