//
// Created by armin on 12/1/2017.
//

#ifndef PROJECT_8_INTERPRETER_A_ALL_H
#define PROJECT_8_INTERPRETER_A_ALL_H



#include <iostream>
#include <cstdio>

#define Negative String("~")
#define Less_Equal String("<=")
#define Mod String("%")
#define Equal String("==")
#define AND String("&&")
#define OR String("||")
#define Not_Equal String("!=")
#define Greater_Equal String(">=")
#define Add String("+")
#define Minus String("-")
#define Multiply String("*")
#define Divide String("/")
#define Less String("<")
#define Greater String(">")
#define Not String("!")

void run();


bool Specific_Word(const String &Word)
{return Word == String("var") || Word == String("text") || Word == String("output") || Word == String("set");}

int Calculate( int left, int right,String &Operation){
    if (Operation == Negative)
        return left * -1;
    if (Operation == Less_Equal)
        return left <= right;
    if (Operation == Mod)
        return left % right;
    if (Operation == Equal)
        return left == right;
    if (Operation == AND)
        return left && right;
    if (Operation == OR)
        return left || right;
    if (Operation == Not_Equal)
        return left != right;
    if (Operation == Greater_Equal)
        return left >= right;
    if (Operation == Add)
        return left + right;
    if (Operation == Minus)
        return left - right;
    if (Operation == Multiply)
        return left * right;
    if (Operation == Divide)
        return left / right;
    if (Operation ==Less)
        return left < right;
    if (Operation == Greater)
        return left > right;
    if (Operation == Not)
        return left == 0;
    exit(1);
}


String Operation(String string){


    if (string == Add || string == Minus || string == Multiply || string == Divide || string == Mod || string == AND|| string == OR||
        string == Less || string == Greater || string == Equal|| string == Not_Equal|| string == Less_Equal|| string == Greater_Equal)
    { return "Binary"; }
    if(string == Negative || string == Not){ return "Unary"; }
    return "None";

}

int finish =0;
std::map<String,int> var;

class Expression{
    int length;
    int Space;

public:
    String* variables{};

    Expression(){
        length = 0;
        Space = 10;
        variables = new String[Space];
    }

    ~Expression(){
        delete[]variables;
    }

    void Isfull(){
        if (length == Space){
            Space = Space*2;
            String* New_Space = new String[Space];
            for(int i =0; i< length; i++){
                New_Space[i] = variables[i];
            }
            delete[]variables;
            variables = New_Space;
        }
    }

    void add(String New_variable){
        variables[length] = New_variable;
        length++;
    }
};

class Convert {
public:
    Expression *word;

    Convert() {
        word = 0;
    }

    ~Convert() = default;

    int convert(String Input) {
        int Converted = 0;
        for (int i = 0; i < Input.size(); i++) {
            Converted = ((Converted * 10) + (Input.c_str()[i] - '0'));
        }
        return Converted;

    };

    String Check_Type(String Input) {
        if ((Input.c_str()[0] <= 57) && (Input.c_str()[0] >= 48)) {
            return "Number";
        }
        if (var.find(Input) != var.end()) {
            return "Variable";
        }
        return "None";
    }

    int Result(Expression *Input) {
        Input->variables++;
        String variable = *Input->variables;
        if (Check_Type(variable) == "Number") {
            return convert(variable);
        }
        if (Check_Type(variable) == "Variable") {
            return var[variable];
        }
        else if ((Operation(variable)) == "Binary" || (Operation(variable)) == "Unary") {
            String Operat = variable;
            int left = Result(Input);
            int right=0;

            if (Operation(variable) == "Binary") {
                right = Result(Input);
            }
            else {right = 0;}
            return Calculate(left, right, Operat);
    } else exit(1);
}

    void Print(Expression* Input){
        String Input1 = String((Input->variables +1)->c_str());
        String Input2 = String((Input->variables +2)->c_str());

        if (String("text") == (String(Input->variables->c_str()))){
            Input->variables++;
            std::cout << Input->variables->c_str();
        }

        else if (String("output") == (String(Input->variables->c_str()))){
            if ( Operation(Input1) == "Unary" || Operation(Input1) == "Binary"){
                std::cout << Result(Input)<<std::endl;
            }
            else if( Check_Type(Input1) == "Number"){
                std::cout<< convert(Input1)<<std::endl;
            }
            else if( Check_Type(Input1) == "Variable"){
                std::cout<< var[Input1]<<std::endl;
            }
        }
        else if (String("var") == String(Input->variables->c_str())){
            if (var.find(Input1) != var.end()){
                std::cout << "variable " << (Input->variables +1)->c_str()<< " incorrectly re-initialized" << std::endl;
            }
            else if(Operation(Input2) != "None"){
                var[Input1] = Result(Input);
            }
            else if (Check_Type(Input2) == "Number"){
                var[Input1] = convert(Input2);
            }
            else if(Check_Type(Input2) == "Variable"){
                if (var.find(Input2) == var.end()){
                    std::cout << "variable "<< (Input->variables +2)->c_str() <<" not declared"<< std::endl;
                } else var[Input1] = var[Input2];
            }

        }
        else if (String("set") == String(Input->variables->c_str())){
            if (var.find(Input1) == var.end()){
                std::cout<< "variable "<< (Input->variables +1)->c_str()<<" not declared"<<std::endl;
            }
            else if(Operation(Input2) == "Binary" || Operation(Input2) == "Unary"){
                Input->variables ++;
                var[Input1] = Result(Input);
            }
            else if(Check_Type(Input2) == "Number"){
                var[Input1] = convert(Input2);
            }
            else if(Check_Type(Input2) == "Variable"){
                if(var.find(Input2) == var.end()){
                    std::cout<< "variable " << (Input->variables +2)->c_str()<< " not declared"<<std::endl;
                }
                else var[Input1] = var[Input2];
            }
        } else {std::cout << "Input is Wrong ."; exit(1);}

    }

    void Complete(Expression** Input){
        (*Input)->add(String(next_token()));
        (*Input)->Isfull();

        if(Specific_Word(String(peek_next_token()))){
            return;
        }
        read_next_token();
        if (String(next_token()) == String("//")){
            skip_line();
            return;
        }
        if (next_token_type == END){
            finish = 1;
            return;
        }
        Complete(Input);
    }

};



#endif //PROJECT_8_INTERPRETER_A_ALL_H