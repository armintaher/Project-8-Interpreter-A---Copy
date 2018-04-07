//
// Created by armin on 12/1/2017.
//


#include <iostream>
#include <map>
#include "Parse.h"
#include "String.h"
#include "All.h"

using namespace std;

void run(){
    while(true) {
        if (next_token_type == SYMBOL) {
            skip_line();
        }
        read_next_token();
        if (next_token_type == NAME) {
            Convert *Input = new Convert;
            Expression *Input_Exp = new Expression;
            Complete(&Input_Exp);
            Input->word = Input_Exp;
            Print(Input_Exp);
        }
        if (next_token_type == END) {
            var.clear();
            return;
        }
    }




}
