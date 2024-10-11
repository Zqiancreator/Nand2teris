#include <iostream>
#include <iosfwd>
#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <fstream>
#include <sstream>
#define OutFile "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\10\\ExpressionLessSquare\\myfinalExpressionLessSquare.xml"
#define InFile1 "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\10\\ExpressionLessSquare\\MainT.xml"
#define InFile2 "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\10\\ExpressionLessSquare\\SquareT.xml"
#define InFile3 "D:\\DeskTop\\nand2tetris\\nand2tetris\\projects\\10\\ExpressionLessSquare\\SquareGameT.xml"
#define FileNum 3
// A 开头被用了  B 使用了别人的开头
#define ERROR_PRINT                                                                                \
    {                                                                                              \
        std::cout << "error occured at File " << __FILE__ << " at line " << __LINE__ << std::endl; \
        outputFile << res;                                                                         \
        res.clear();                                                                               \
        exit(0);                                                                                   \
    }

#define PRINT_TOKEN do{res += Space + line + "\n"; printTimes++;}while(0)

// 词法分析器
class Lexer
{
private:
    int    printTimes;
    int    filenum;
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::string line;
    std::string res;
    std::string token;
    std::string tokenType;
    std::istringstream iss;
    std::string Space;
    std::unordered_set<std::string> type = {"int", "char", "boolean"};
    std::unordered_set<std::string> keywords = {"return", "class", "function", "var", "int", "float", "let", "void", "while", "do", "static", "boolean", "if", "else", "field", "constructor", "method", "this", "char", "false", "null", "true"};
    std::unordered_set<std::string> keywordConstant = {"this", "false", "null", "true"};
    std::unordered_set<char> op = {'=', '<', '+', '-', '/', '*', '|', '&', '>'};
    std::unordered_set<char> unaryOp = {'-', '~'}; // &lt;

public:
    Lexer() : inputFile(InFile1, std::ios::in), outputFile(OutFile, std::ios::out)
    {
        Space = "";
        printTimes = 0;
        filenum = 1;
        if (!inputFile.is_open() || !outputFile.is_open())
        {
            throw std::runtime_error("Could not open file.");
        }
        res.clear();
    }

    void getToken()
    {
        iss.clear();
        iss.str(line);
        iss >> tokenType;
        iss >> token;
    }

    void varDec()
    { // A   'var' type varName (',' varName)* ';'
        res += Space + "<varDec>\n";
        Space += " ";
        PRINT_TOKEN;                   // var
        std::getline(inputFile, line); // type
        PRINT_TOKEN;
        std::getline(inputFile, line); // varName
        PRINT_TOKEN;
        std::getline(inputFile, line);
        iss.str(line);
        iss >> token;
        iss >> token;
        while (token == ",")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // varName
            PRINT_TOKEN;
            std::getline(inputFile, line); // ,
            iss.str(line);
            iss >> token;
            iss >> token;
        }
        if (token == ";")
        {
            PRINT_TOKEN;
        }
        else
            ERROR_PRINT
        Space.erase(Space.begin());
        res += Space + "</varDec>\n";
    }

    void statements()
    { // AB     statement*
        res += Space + "<statements>\n";
        Space += " ";
        while (token != "}")
        {
            if (token == "let")
            {
                LetStatement();
            }
            else if (token == "if")
            {
                ifStatement();
            }
            else if (token == "while")
            {
                whileStatement();
            }
            else if (token == "do")
            {
                doStatement();
            }
            else if (token == "return")
            {// return expression? ';'
                res += Space + "<returnStatement>\n";
                Space += " ";
                PRINT_TOKEN;
                std::getline(inputFile, line); // expression? ;
                getToken();
                if (token == ";")
                {
                    PRINT_TOKEN;
                }
                else
                {
                        Expression();
                        // std::getline(inputFile, line); // ;
                        // getToken();
                        if (token == ";")
                        {
                            PRINT_TOKEN;
                        }
                        else
                            ERROR_PRINT
                }
                Space.erase(Space.begin());
                res += Space + "</returnStatement>\n";
                std::getline(inputFile, line); // 保持一致
                getToken();
            }

            // std::getline(inputFile, line); // look for next statement
            // getToken();
        }
        outputFile << res;
        res.clear();
        Space.erase(Space.begin());
        res += Space + "</statements>\n";
    }

    void ExpressionList()
    { // B   (expression (',' expression)*)?
        res += Space + "<expressionList>\n";
        Space += " ";
        std::getline(inputFile, line);
        getToken();
        if (tokenType == "<identifier>" || op.find(token[0]) != op.end() || keywordConstant.find(token) != keywordConstant.end() || token == "("||tokenType == "<stringConstant>" || tokenType == "<integerConstant>")
        {

            Expression();

            while (token == ",")
            {
                PRINT_TOKEN;
                std::getline(inputFile, line); // for expression
                getToken();
                Expression();
            }
        }
        Space.erase(Space.begin());
        res += Space + "</expressionList>\n";
    }

    void Term()
    {   // C TODO chang to AB
        // integerConstant | stringConstant | keywordConstant | varName |
        //   varName '[' expression ']' | subroutineCall | '(' expression ')' | unaryOp term
        Space += " ";
        res += Space + "<term>\n";
        Space += " ";

        if (tokenType == "<stringConstant>" || tokenType == "<integerConstant>" || keywordConstant.find(token) != keywordConstant.end())
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // 保持一致
            getToken();
        }
        else if (tokenType == "<identifier>")
        { // subroutineCall TODO
            PRINT_TOKEN;
            std::getline(inputFile, line); // ( [ . 或者多余
            getToken();
            if (token == "(")
            {
                PRINT_TOKEN;
                ExpressionList();
                if (token == ")")
                {

                    PRINT_TOKEN;
                }
                else
                    ERROR_PRINT
                std::getline(inputFile, line); // 保持一致
                getToken();
            }
            else if (token == "[")
            {
                PRINT_TOKEN;
                std::getline(inputFile, line); // for expression
                getToken();
                Expression();
                if (token == "]")
                {

                    PRINT_TOKEN;
                }
                else
                    ERROR_PRINT
                std::getline(inputFile, line); // 保持一致
                getToken();
            }
            else if (token == ".")
            {
                PRINT_TOKEN;
                std::getline(inputFile, line); // subroutineName
                PRINT_TOKEN;
                std::getline(inputFile, line); // (
                getToken();
                if (token == "(")
                {
                    PRINT_TOKEN;
                    ExpressionList();
                    if (token == ")")
                    {
                        PRINT_TOKEN;
                        // break;
                    }
                    else
                        ERROR_PRINT
                    std::getline(inputFile, line); // 保持一致
                    getToken();
                }
            }
        }
        else if (token == "(")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // for expression
            getToken();
            Expression();
            if (token == ")")
            {
                PRINT_TOKEN;
            }
            else
                ERROR_PRINT

            std::getline(inputFile, line); // 保持一致
            getToken();
        }
        else if (unaryOp.find(token[0]) != unaryOp.end())
        {
            PRINT_TOKEN;
            std::getline(inputFile, line);
            getToken();
            Term();
        }
        else
            ERROR_PRINT
        Space.erase(Space.begin());
        res += Space + "</term>\n";
        Space.erase(Space.begin());
    }

    void Expression()
    { // AB   term(op term)*
        Space += " ";
        res += Space + "<expression>\n";
        Term();
        while (op.find(token[0]) != op.end())
        {
            PRINT_TOKEN;
            std::getline(inputFile, line);
            getToken();
            Term();
        }
        res += Space + "</expression>\n";
        Space.erase(Space.begin());
        outputFile << res;
        res.clear();
    }

    void whileStatement()
    { // AB   while '(' expression ')' '{' statements '}'
        res += Space + "<whileStatement>\n";
        Space += " ";
        PRINT_TOKEN; // while
        std::getline(inputFile, line);
        getToken();
        if (token == "(")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // for expression
            getToken();
            Expression();
        }
        else
            ERROR_PRINT
        if (token != ")")
            ERROR_PRINT
        else
            PRINT_TOKEN;
        std::getline(inputFile, line);
        getToken();
        if (token == "{")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line);
            getToken();
            statements();
        }
        else
            ERROR_PRINT
        if (token == "}")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line);// B
            getToken();
        }
        else
            ERROR_PRINT
        Space.erase(Space.begin());
        res += Space + "</whileStatement>\n";
    }

    void ifStatement()
    { // AB   'if' '(' expression ')' '{' statements '}' ('else' '{' statements '}')?
        res += Space + "<ifStatement>\n";

        Space += " ";
        PRINT_TOKEN;                   // if
        std::getline(inputFile, line); // (
        getToken();
        if (token != "(")
        {
            ERROR_PRINT
        }
        PRINT_TOKEN;
        std::getline(inputFile, line); // for expression
        getToken();
        Expression();
        if (token != ")")
        {
            ERROR_PRINT
        }
        PRINT_TOKEN;
        std::getline(inputFile, line); // {
        getToken();
        if (token != "{")
        {
            ERROR_PRINT
        }
        PRINT_TOKEN;
        std::getline(inputFile, line); // for statements
        getToken();
        statements();
        if (token != "}")
        {
            ERROR_PRINT
        }
        PRINT_TOKEN;
        std::getline(inputFile, line); // else
        getToken();
        if (token == "else")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // {
            getToken();
            if (token != "{")
            {
                ERROR_PRINT
            }
            PRINT_TOKEN;
            std::getline(inputFile, line); // for statements
            getToken();
            statements();
            if (token != "}")
            {
                ERROR_PRINT
            }
            PRINT_TOKEN;
            std::getline(inputFile, line); // 保持一致
            getToken();
        }
        Space.erase(Space.begin());
        res += Space + "</ifStatement>\n";
    }

    void doStatement()
    { // AB 'do' subroutineCall ';'

        res += Space + "<doStatement>\n";

        Space += " ";
        PRINT_TOKEN; // do
        subroutineCall();
        std::getline(inputFile, line); // ;
        getToken();
        if (token != ";")
        {
            ERROR_PRINT
        }
        else
            PRINT_TOKEN;
        std::getline(inputFile, line);
        getToken();
        Space.erase(Space.begin());
        res += Space + "</doStatement>\n";
    }

    void LetStatement()
    { // AB 'let' varName ('[' expression ']')? '=' expression ';'
        res += Space + "<letStatement>\n";

        Space += " ";
        PRINT_TOKEN; // let

        std::getline(inputFile, line); // varName
        PRINT_TOKEN;
        std::getline(inputFile, line); // [ or =
        getToken();
        if (token == "[")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // for expression
            getToken();
            Expression();
            PRINT_TOKEN;
            if (token == "]")
            {
                std::getline(inputFile, line); // =
                getToken();
            }
            else
                ERROR_PRINT
        }
        if (token == "=")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // for expression
            getToken();
            Expression();
            if (token == ";")
            {
                PRINT_TOKEN;
                std::getline(inputFile, line); // for expression
                getToken();
            }
            else
                ERROR_PRINT
        }
        else
            ERROR_PRINT

        Space.erase(Space.begin());
        res += Space + "</letStatement>\n";
    }

    void classVarDec()
    { // A ('static'|'field') type varName (',' varName)* ';'
        res += Space + "<classVarDec>\n";
        Space += " ";
        if (token == "static" || token == "field")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // type
            getToken();

            if (type.find(token) != type.end())
            {
                PRINT_TOKEN;
                std::getline(inputFile, line); // varName
                PRINT_TOKEN;
                std::getline(inputFile, line); // ,
                getToken();

                while (token == ",")
                {
                    PRINT_TOKEN;
                    std::getline(inputFile, line); // varName
                    PRINT_TOKEN;
                    std::getline(inputFile, line); // ,
                    getToken();
                }
                if (token == ";")
                {
                    PRINT_TOKEN;
                }
                else
                {
                    ERROR_PRINT
                }
            }
            else
                ERROR_PRINT
        }
        Space.erase(Space.begin());
        res += Space + "</classVarDec>\n";
    }

    void subroutineCall()
    { // C  subroutineName '(' expressionList ')' | (className | varName) '.' subroutineName '(' expressionList ')'
        std::getline(inputFile, line); // Name
        PRINT_TOKEN;
        std::getline(inputFile, line);
        getToken();
        if (token == "(")
        {
            PRINT_TOKEN;
            ExpressionList();
            if (token != ")")
            {
                ERROR_PRINT
            }
            else
                PRINT_TOKEN;
        }
        else if (token == ".")
        {
            PRINT_TOKEN;
            subroutineCall();
        }
        else
        {
            ERROR_PRINT
        }

    }

    void subroutineDec()
    { // A   ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
        res += Space + "<subroutineDec>\n";
        Space += " ";
        if (token == "constructor" || token == "function" || token == "method")
        {
            PRINT_TOKEN;
        }
        std::getline(inputFile, line); // void or type
        getToken();
        if (token == "void" || type.find(token) != type.end())
        {

            PRINT_TOKEN;
        }
        else
            ERROR_PRINT
        std::getline(inputFile, line); // subroutineName
        PRINT_TOKEN;
        std::getline(inputFile, line);
        getToken();
        if (token == "(")
        {
            PRINT_TOKEN;
            parameterList();
            if (token == ")")
            {
                PRINT_TOKEN;
                subroutineBody();

            }
            else
                ERROR_PRINT
        }
        else
            ERROR_PRINT

        Space.erase(Space.begin());
        res += Space + "</subroutineDec>\n";
    }

    void subroutineBody()
    { // '{' varDec* statements '}'
        res += Space + "<subroutineBody>\n";
        Space += " ";
        std::getline(inputFile, line);
        getToken();
        if (token == "{")
        {
            PRINT_TOKEN;
            std::getline(inputFile, line);
            getToken();
            while (token == "var")
            {
                varDec();
                std::getline(inputFile, line);
                getToken();
            }
            statements();
            if (token == "}")
            {
                PRINT_TOKEN;
            }
            else
                ERROR_PRINT
        }

        Space.erase(Space.begin());
        res += Space + "</subroutineBody>\n";
    }

    void parameterList()
    { // ((type varName) (',' type varName)*)?
        res += Space + "<parameterList>\n";
        Space += " ";
        std::getline(inputFile, line); // type
        getToken();
        if (type.find(token) != type.end())
        {
            PRINT_TOKEN;
            std::getline(inputFile, line); // varName
            PRINT_TOKEN;
            std::getline(inputFile, line); // ,
            getToken();
            while (token == ",")
            {
                PRINT_TOKEN;
                std::getline(inputFile, line); // type
                getToken();
                if (type.find(token) != type.end())
                {

                    PRINT_TOKEN;
                }
                else
                    ERROR_PRINT
                std::getline(inputFile, line); // varName
                PRINT_TOKEN;
                std::getline(inputFile, line); // ,
                getToken();
            }
        }
        Space.erase(Space.begin());
        res += Space + "</parameterList>\n";
    }

    // 解析主函数示例
    void parseInputAndLex()
    {
        while (std::getline(inputFile, line)||filenum<=FileNum)
        {
            getToken();

            if (token == "class")
            { // 'class' className '{' classVarDec* subroutineDec* '}'
                res += Space + "<class>\n";
                Space += ' ';
                PRINT_TOKEN;
                std::getline(inputFile, line); // className
                PRINT_TOKEN;
                getToken();
                type.insert(token);

                std::getline(inputFile, line); // {
                getToken();

                if (token == "{")
                { // TODO classVarDec*
                    PRINT_TOKEN;
                    while (1)
                    {
                        std::getline(inputFile, line);
                        getToken();
                        if (token == "static" || token == "field")
                            classVarDec();
                        else if (token == "constructor" || token == "function" || token == "method")
                            subroutineDec();
                        else if (token == "{")
                            break;
                        else if (token == "}")
                        {
                            PRINT_TOKEN;
                            break;
                        }
                        else
                            ERROR_PRINT
                    }
                }
                else
                {
                    ERROR_PRINT
                }
                Space.erase(Space.begin());
                res += Space + "</class>\n";
            }
            else if (tokenType == "<tokens>" || tokenType == "</tokens>")
                continue;
            
            inputFile.close();
            switch (filenum)
            {
            case 1:
                inputFile.open(InFile2);
                break;
            case 2:
                inputFile.open(InFile3);
                break;
            default:
                break;
            }
            filenum++;
        }
        outputFile << res;
        res.clear();
    }
};

int main()
{
    Lexer lexer = Lexer();
    lexer.parseInputAndLex(); // 示例输入并分析
    return 0;
}