@1
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@THAT
M=D
@0
D=A
@SP
M=M+1
A=M-1
M=D
@0
D=A
@THAT
D=D+M
@addr.0
M=D
@SP
M=M-1
A=M
D=M
@addr.0
A=M
M=D
@1
D=A
@SP
M=M+1
A=M-1
M=D
@1
D=A
@THAT
D=D+M
@addr.1
M=D
@SP
M=M-1
A=M
D=M
@addr.1
A=M
M=D
@0
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
@2
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
@0
D=A
@ARG
D=D+M
@addr.2
M=D
@SP
M=M-1
A=M
D=M
@addr.2
A=M
M=D
(LOOP)
@0
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
@SP
M=M-1
A=M
D=M
@COMPUTE_ELEMENT
D;JNE
@END
0;JMP
(COMPUTE_ELEMENT)
@0
D=A
@THAT
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
@1
D=A
@THAT
A=D+M
D=M
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
@2
D=A
@THAT
D=D+M
@addr.3
M=D
@SP
M=M-1
A=M
D=M
@addr.3
A=M
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@1
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
@SP
M=M-1
A=M
D=M
@THAT
M=D
@0
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
@1
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
@0
D=A
@ARG
D=D+M
@addr.4
M=D
@SP
M=M-1
A=M
D=M
@addr.4
A=M
M=D
@LOOP
0;JMP
(END)
