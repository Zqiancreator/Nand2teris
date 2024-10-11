#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
std::string res;
int num = 0;
int tmp = 0;
int comp = 0;
#define TMP "addr."
#define STATIC "Foo."
#define TEMP_OFF 5
void getNum(std::string& src){
    num = 0;
    for(int i=0;i<src.size();i++){
        num*=10;
        num+=(src[i]-'0');
    }
}
void BinOper(std::string& token){ 
    res+= "@SP\nM=M-1\nA=M\nD=M\n";    
    if(token == "add")
        res+= "@SP\nM=M-1\nA=M\nM=M+D\n";    
    else if(token == "sub")
        res+= "@SP\nM=M-1\nA=M\nM=M-D\n";    
    else if(token == "and")
        res+= "@SP\nM=M-1\nA=M\nM=M&D\n";    
    else if(token == "or")
        res+= "@SP\nM=M-1\nA=M\nM=M|D\n";    
    res+= "@SP\nM=M+1\n";    
}

void compare(std::string& token){
    res+= "@SP\nM=M-1\nA=M\nD=M\n";    
    res+= "@TMP\nM=D\n";
    res +="@SP\nM=M-1\nA=M\nD=M\n";    
    res+= "@TMP\nD=D-M\n@TRUE"+std::to_string(comp)+"\n";
    if(token == "lt"){
        std::cout << "lt"<<std::endl;
        res+="D;JLT\n";
    }else if(token == "eq"){
        std::cout << "eq"<<std::endl;
        res+="D;JEQ\n";
    }else if(token == "gt"){
        std::cout << "gt"<<std::endl;
        res+="D;JGT\n";
    }
    else{
        std::cout<<"compare error\n";
    }
    res+="(FALSE"+std::to_string(comp)+")\nD=0\n@END"+std::to_string(comp)+"\n0;JMP\n";
    res+="(TRUE"+std::to_string(comp)+")\nD=-1\n(END"+std::to_string(comp)+")\n";
    res +="@SP\nA=M\nM=D\n";    
    res +="@SP\nM=M+1\n";    
    comp++;
}

void PushFunc(std::vector<std::string>& tokens){
    if(tokens[1] == "constant"){// @num D=A @SP M=M+1 A=M-1 M=D 
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@SP\nM=M+1\nA=M-1\nM=D\n";    
    }
    else if(tokens[1] == "local"){// @num D=A @LCL A=D+M D=M @SP M=M+1 A=M-1 M=D   
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@LCL\nA=D+M\nD=M\n"; 
        res +="@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
    else if(tokens[1] == "argument"){
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@ARG\nA=D+M\nD=M\n"; 
        res +="@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
    else if(tokens[1] == "this"){
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@THIS\nA=D+M\nD=M\n"; 
        res +="@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
    else if(tokens[1] == "that"){
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@THAT\nA=D+M\nD=M\n"; 
        res +="@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
    else if(tokens[1] == "temp"){// @SP M=M-1 A=M D=M @num M=D 
        getNum(tokens[2]);
        num+=TEMP_OFF;
        res+= "@"+std::to_string(num)+"\n"+"D=M\n";
        res +="@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
    else if(tokens[1] == "static"){// @SP M=M-1 A=M D=M @num M=D 
        getNum(tokens[2]);
        res += "@"+std::string(STATIC)+std::to_string(num)+"\n"+"D=M\n";
        res += "@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
    else if(tokens[1] == "pointer"){//  @num D=M @SP M=M+1 A=M D=M
        getNum(tokens[2]);
        switch (num)
        {
        case 0: // THIS
            res +="@THIS\nD=M\n"; 
            break;
        case 1:
            res +="@THAT\nD=M\n"; 
            break;
        default:
            printf("error pointer arr\n");
            break;
        }
        res +="@SP\nM=M+1\nA=M-1\nM=D\n"; 
    }
 
}

void PopFunc(std::vector<std::string>& tokens){
    if(tokens[1] == "local"){// @num D=A @LCL D=D+M @TMP.num M=D @SP M=M-1 A=M D=M @TMP.num A=M M=D 
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@LCL\nD=D+M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nM=D\n"; 
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nA=M\nM=D\n"; 
    }
    else if(tokens[1] == "argument"){// @num D=A @LCL D=D+M @TMP.num M=D @SP M=M-1 A=M D=M @TMP.num A=M M=D 
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@ARG\nD=D+M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nM=D\n"; 
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nA=M\nM=D\n"; 
    }
    else if(tokens[1] == "this"){// @num D=A @LCL D=D+M @TMP.num M=D @SP M=M-1 A=M D=M @TMP.num A=M M=D 
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@THIS\nD=D+M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nM=D\n"; 
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nA=M\nM=D\n"; 
    }
    else if(tokens[1] == "that"){// @num D=A @LCL D=D+M @TMP.num M=D @SP M=M-1 A=M D=M @TMP.num A=M M=D 
        getNum(tokens[2]);
        res+= "@"+std::to_string(num)+"\n"+"D=A\n";
        res +="@THAT\nD=D+M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nM=D\n"; 
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        res +="@"+std::string(TMP)+std::to_string(tmp)+"\nA=M\nM=D\n"; 
    }
    else if(tokens[1] == "temp"){// @SP M=M-1 A=M D=M @num M=D 
        tmp--;// meaningless just keep tmp no change
        getNum(tokens[2]);
        num+=TEMP_OFF;
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        res+= "@"+std::to_string(num)+"\n"+"M=D\n";
    }
    else if(tokens[1] == "static"){// @SP M=M-1 A=M D=M @num M=D 
        tmp--;// meaningless just keep tmp no change
        getNum(tokens[2]);
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        res+= "@"+std::string(STATIC)+std::to_string(num)+"\n"+"M=D\n";
    }
    else if(tokens[1] == "pointer"){// @SP M=M-1 A=M D=M @num M=D 
        tmp--;
        getNum(tokens[2]);
        res +="@SP\nM=M-1\nA=M\nD=M\n"; 
        switch (num)
        {
        case 0: // THIS
            res += "@THIS\nM=D\n";
            break;
        case 1:
            res += "@THAT\nM=D\n";
            break;
        default:
            printf("error pointer arr\n");
            break;
        }
    }
    tmp++;
}

int main() {
    // std::ifstream inputFile("MemoryAccess\\BasicTest\\BasicTest.vm");
    // std::ifstream inputFile("MemoryAccess\\PointerTest\\PointerTest.vm");
    // std::ifstream inputFile("MemoryAccess\\StaticTest\\StaticTest.vm");
    // std::ifstream inputFile("StackArithmetic\\StackTest\\StackTest.vm");
    std::ifstream inputFile("StackArithmetic\\SimpleAdd\\SimpleAdd.vm");
    // std::ofstream outputFile("MemoryAccess\\BasicTest\\BasicTest.asm");
    // std::ofstream outputFile("MemoryAccess\\PointerTest\\PointerTest.asm");
    // std::ofstream outputFile("MemoryAccess\\StaticTest\\StaticTest.asm");
    // std::ofstream outputFile("StackArithmetic\\StackTest\\StackTest.asm");
    std::ofstream outputFile("StackArithmetic\\SimpleAdd\\SimpleAdd.asm");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    int size;
    while (std::getline(inputFile, line)) {
        res.clear();
        tokens.clear();
        std::istringstream iss(line);
        if(line[0]=='/'&&line[1]=='/')
            continue;
        while (std::getline(iss, token, ' ')) {
            tokens.push_back(token);
        }
        size = tokens.size();
        if(size == 1){
            if(token == "add"){
                std::cout<<"add"<<std::endl;
                BinOper(token);
            }
            else if(token == "sub"){
                std::cout<<"sub"<<std::endl;
                BinOper(token);
            }
            else if(token == "and"){
                std::cout<<"and"<<std::endl;
               BinOper(token);
            }else if(token == "or"){
                std::cout<<"or"<<std::endl;
               BinOper(token);
            }else if(token == "not"){
                std::cout<<"not"<<std::endl;
                res+="@SP\nD=M-1\nA=D\nM=-M\n";
            }else if(token == "neg"){
                std::cout<<"neg"<<std::endl;
                res+="@SP\nD=M-1\nA=D\nM=!M\n";
            }else{
                compare(token);
            }
        }
        if(size == 3){
            if(tokens[0] == "push"){
                std::cout<<"push"<<std::endl;
                PushFunc(tokens);
            }
            else if(tokens[0] == "pop"){
                std::cout<<"pop "<<std::endl;
                PopFunc(tokens);
            }
            else{
                std::cout << "error input";
            }
        }
        outputFile << res;                
    }

    inputFile.close();
    outputFile.close();

    std::cout << "end" << std::endl;

    return 0;
}