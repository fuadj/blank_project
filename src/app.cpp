#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include "error.h"
#include "simpio.h"
#include "stack.h"

using namespace std;

void applyOperator(char op, Stack<double> & operandStack);
void helpCommand();

int main() {
    cout << "RPC Calculator (type H for help)" << endl;
    Stack<double> operandStack;
    while (true) {
        string line = getLine("> ");
        if (line.length() == 0) line = "Q";
        char ch = toupper(line[0]);
        if (ch == 'Q') {
            break;
        } else if (ch == 'C') {
            operandStack.clear();
        } else if (ch == 'H') {
            helpCommand();
        } else if (isdigit(ch)) {
            operandStack.push(stringToReal(line));
        } else {
            applyOperator(ch, operandStack);
        }
    }
    return 0;
}

void applyOperator(char op, Stack<double> &operandStack) {
    if (operandStack.size() < 2) return;

    double right_side = operandStack.pop();
    double left_side = operandStack.pop();

    double result;
    bool computed_result = true;

    switch (op) {
    case '+':
        result = left_side + right_side;
        break;
    case '-':
        result = left_side - right_side;
        break;
    case '*':
        result = left_side * right_side;
        break;
    case '/':
        if (right_side != 0)
            result = left_side / right_side;
        else
            result = 0;
        break;
    default:
        computed_result = false;
        break;
    }

    if (computed_result) {
        operandStack.push(result);
        cout << result << endl;
    } else {
        operandStack.push(left_side);
    }
}

void helpCommand() {
    cout << "Enter expressions in Reverse Polish Notation," << endl;
    cout << "in which operators follow the operand to which" << endl;
    cout << "they apply. Each line consists of a number, an" << endl;
    cout << "operator, or one of the followign commands:" << endl;
    cout << " Q -- Quit the program" << endl;
    cout << " H -- Display this help message " << endl;
    cout << " C -- Clear the calculator stack" << endl;
}


























