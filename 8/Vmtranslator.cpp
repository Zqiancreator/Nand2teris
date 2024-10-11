#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
std::string res;
std::string className = "";
int num = 0;
int tmp = 0;
int comp = 0;
int func = 0;
int ret = 0;
int retst = 0;


#define InFileNum 3
#define InFile "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\8\\FunctionCalls\\StaticsTest\\Sys.vm"
#define InFile1 "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\8\\FunctionCalls\\StaticsTest\\Class1.vm"
#define InFile2 "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\8\\FunctionCalls\\StaticsTest\\Class2.vm"
#define OutFile "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\8\\FunctionCalls\\StaticsTest\\StaticsTest.asm"
#define TMP "addr."
#define STATIC "static."
#define TEMP_OFF 5
#define endFrame "endFrame" + std::to_string(func)
#define returnaddr "returnaddr" + std::to_string(ret)
#define returndest "returndest" + std::to_string(retst)
void getNum(std::string& src){
    num = 0;
    for(unsigned int i=0;i<src.size();i++){
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
        res += "@"+std::string(STATIC)+std::to_string(num)+className+"\n"+"D=M\n";
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
    else{
        std::cout<<"error push\n";
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
        res += "@SP\nM=M-1\nA=M\nD=M\n"; 
        res += "@"+std::string(STATIC)+std::to_string(num)+className+"\n"+"M=D\n";
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
    else{
        std::cout<<"error pop\n";
    }
    tmp++;
}

void possessFunc(std::vector<std::string>& tokens){// function FuncName nLocals
    if(tokens[0] == "function"){ // 
        res += "(" +tokens[1]+ ")\n";
        for(int i = 0;i < std::stoi(tokens[2]); i++){// seserve n local
            res+="@SP\nM=M+1\nA=M-1\nM=0\n";
        }
        int pos = tokens[1].find('.');// get class name for static
        if(pos!=0)
            className = tokens[1].substr(0,pos);
    }
    else if(tokens[0] == "return"){
        res += "@LCL\nD=M\n@"+std::string(endFrame)+"\nM=D\n@5\nD=A\n@"+std::string(endFrame)+"\nA=M-D\nD=M\n@"+std::string(returnaddr)+"\nM=D\n";// restor the return addr
        res += "@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D\n"; // restore the return val to arg location
        res += "@ARG\nD=M+1\n@SP\nM=D\n"; // change SP to return val location
        res += "@"+std::string(endFrame)+"\nM=M-1\nA=M\nD=M\n@THAT\nM=D\n";
        res += "@"+std::string(endFrame)+"\nM=M-1\nA=M\nD=M\n@THIS\nM=D\n";
        res += "@"+std::string(endFrame)+"\nM=M-1\nA=M\nD=M\n@ARG\nM=D\n";
        res += "@"+std::string(endFrame)+"\nM=M-1\nA=M\nD=M\n@LCL\nM=D\n";// restores THAT THIS ARG LCL
        res += "@"+std::string(returnaddr)+"\nA=M\n0;JMP\n"; // goto return addr
        ret++;// TODO
    }
    else if(tokens[0] == "call"){// call functionName nArgs
        res += "@" + std::string(returndest) + "\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n";// push returndest
        res += "@LCL\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        res += "@ARG\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        res += "@THIS\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        res += "@THAT\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";// saves LCL ARG THIS THAT
        res += "@5\nD=A\n@SP\nD=M-D\n@"+tokens[2]+"\nD=D-A\n@ARG\nM=D\n";// ARG = SP-5-nArgs
        res += "@SP\nD=M\n@LCL\nM=D\n";// LCL=SP
        res += "@"+tokens[1]+"\n0;JMP\n";// goto func
        res += "("+ std::string(returndest) +")\n";
        retst++;// TODO
    }
}

int main() {
    std::ifstream inputFile(InFile);
    std::ofstream outputFile(OutFile);

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
    for(int i=0;i<InFileNum;i++){
        while (std::getline(inputFile, line)) {
            res.clear();
            tokens.clear();
            std::istringstream iss(line);
            if((line[0]=='/'&&line[1]=='/')||line=="")
                continue;
            // while (std::getline(iss, token, ' ')) {// this way can't possess tap space in lines
            //     if(token==" "|| token == "//")
            //         break;
            //     tokens.push_back(token);
            // }
            while(iss >> token){
                if(token==" "|| token == "//")
                    break;
                tokens.push_back(token);
            }
            size = tokens.size();
            if(size == 1){
                if(tokens[0] == "add"){
                    std::cout<<"add"<<std::endl;
                    BinOper(tokens[0]);
                }
                else if(tokens[0] == "sub"){
                    std::cout<<"sub"<<std::endl;
                    BinOper(tokens[0]);
                }
                else if(tokens[0] == "and"){
                    std::cout<<"and"<<std::endl;
                BinOper(tokens[0]);
                }else if(tokens[0] == "or"){
                    std::cout<<"or"<<std::endl;
                BinOper(tokens[0]);
                }else if(tokens[0] == "not"){
                    std::cout<<"not"<<std::endl;
                    res+="@SP\nD=M-1\nA=D\nM=!M\n";
                }else if(tokens[0] == "neg"){
                    std::cout<<"neg"<<std::endl;
                    res+="@SP\nD=M-1\nA=D\nM=-M\n";
                }else if(tokens[0] == "return"){
                    std::cout<<"return"<<std::endl;
                    possessFunc(tokens);
                }
                else{
                    compare(tokens[0]);
                }
            }
            else if(size == 2){
                if(tokens[0] == "label"){
                    std::cout<<"label "<< tokens[1]<<std::endl;
                    res+="("+tokens[1]+")\n";
                }
                else if(tokens[0] == "if-goto"){
                    std::cout<<"if-goto\n";
                    res += "@SP\nM=M-1\nA=M\nD=M\n@"+tokens[1]+"\nD;JNE\n";
                }
                else if(tokens[0] == "goto"){
                    std::cout<<"goto\n";
                    res += "@"+tokens[1]+"\n0;JMP\n";
                }
                else{
                    std::cout<<"error 2\n";
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
                else if(tokens[0] == "function"){
                    std::cout<<"function"<<std::endl;
                    possessFunc(tokens);
                }
                else if(tokens[0] == "call"){
                    std::cout<<"call"<<std::endl;
                    possessFunc(tokens);
                }
                else{
                    std::cout << "error input\n";
                }
            }
            outputFile << res;                
        }
        inputFile.close();
        if(i==0)
            inputFile.open(InFile1);
        else if(i==1)
            inputFile.open(InFile2);
        
    }

    inputFile.close();
    outputFile.close();

    std::cout << "end" << std::endl;

    return 0;
}