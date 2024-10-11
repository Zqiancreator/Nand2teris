#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <fstream>
#include <sstream>
#define OutFile "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\10\\Square\\myT.xml"
#define InFile "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\10\\Square\\SquareGame.jack"

// 词法单元定义
struct Token {
    enum Type { keyword, identifier, symbol, stringConstant, integerConstant} type;
    std::string text;

    Token(Type t, const std::string& txt) : type(t), text(txt) {}
};


// 词法分析器
class Lexer {
private:
    std::ifstream in;
    std::vector<Token> tokens;
    std::string currentToken;
    std::ofstream outputFile;
    std::string line;
    std::string res;
    std::string word;
    std::unordered_set<std::string> keywords = {"return", "class", "function", "var", "int", "float", "let", "void", "while", "do", "static", "boolean", "if", "else", "field", "constructor", "method", "this", "char", "false", "null", "true"};
    std::unordered_set<char> symbols = {']', '[', '.', ';', '=', '-', '{', '}', '(', ')', ',', '<','+','/', '*', '|', '&', '>', '~'};// &lt;
    static void FindType(std::unordered_set<std::string>& keywords, std::string& word, std::string& res){
        if(keywords.find(word) != keywords.end()){
            res += "<keyword> " + word + " </keyword>\n";
        }
        else{
            int j = 0;
            for( j=0;j<word.size();j++){// integerConstant
                if(word[j]<'0'||word[j]>'9')
                    break;
            }
            if(j==word.size())
                res += "<integerConstant> " + word +" </integerConstant>\n";
            else 
                res += "<identifier> " + word +" </identifier>\n";
        }
        word.clear();
    }
public:
    
    Lexer() : in(InFile, std::ios::in), outputFile(OutFile, std::ios::out) {
        if (!in.is_open() || !outputFile.is_open()) {
            throw std::runtime_error("Could not open file.");
        }
        res = "<tokens>\n";
    }


    // 解析主函数示例
    void parseInputAndLex() {
        int i = 0;
        bool isstring = false;
        bool isDox = false;
        while (std::getline(in,line))
        {
            std::istringstream iss(line);
            
            for(i=0;i<line.size();i++){
                if((line[i]=='/'&&line[i+1]=='*')||isDox){// 多行注释
                    if(line[i]=='*'&&line[i+1]=='/'){
                        i++;
                        isDox = false; 
                    }
                    else
                        isDox = true;
                    continue;
                }
                if((line[i]=='/'&&line[i+1]=='/')||line=="")
                    break;
                if(line[i]=='"'||isstring){// string
                    if(line[i]=='"'){
                        isstring = ! isstring;
                        if(!isstring){
                            res += "<stringConstant> " + word +" </stringConstant>\n";
                            word.clear();
                        }
                    }
                    else
                        word += line[i];
                    continue; 
                }
                else if(line[i]==' '||line[i]=='\t'){// space or tap
                    if(word.size()==0)
                        continue;
                    else{
                        FindType(keywords, word, res);
                    }
                }else if(symbols.find(line[i]) != symbols.end()){// symbol
                    if(word.size()!=0){
                        FindType(keywords, word, res);
                    }
                    switch (line[i])
                    {
                    case '<':
                        res += "<symbol> &lt; </symbol>\n";
                        break;
                    case '&':
                        res += "<symbol> &amp; </symbol>\n";
                        break;
                    case '>':
                        res += "<symbol> &gt; </symbol>\n";
                        break;
                    default:
                        res += "<symbol> " + std::string(1,line[i]) + " </symbol>\n";
                        break;
                    }
                    continue;
                    
                }else
                    word += line[i];
            }
            
            outputFile << res;
            res.clear();
        }  
        res = "</tokens>\n";
        outputFile << res;
    }
};

int main() {
    Lexer lexer = Lexer();
    lexer.parseInputAndLex(); // 示例输入并分析
    return 0;
}