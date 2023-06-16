#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <iterator>
#include <map>

using namespace std;

void PostfixEval(string instr) {
  stack <int> stack;
  map <char, int> variables;

  istringstream stream(instr);
  string thing;
  while (stream >> thing) {
    if (isdigit(thing[0])) {
      stack.push(stoi(thing));
    }
    else if (thing[0] == '$') {
      int val;
      if (variables.find(thing[1]) == variables.end()) {
          val = 0;
      } 
      else {
          val = variables[thing[1]];
      }
      stack.push(val);
    }
    else if (isalpha(thing[0])) {
      if (stack.empty()) {
          cerr << "Error: Incomplete input postfix expression." << endl;
          return;
      }
      variables[thing[0]] = stack.top();
      stack.pop();
    }
    else {
      if (stack.size() < 2) {
        cout << "Error: Incomplete input postfix expression." << endl;
        return;
      }
      int operand2 = stack.top();
      stack.pop();
      int operand1 = stack.top();
      stack.pop();
      if (thing[0] == '+') {
        stack.push(operand1 + operand2);
      }
      else if (thing[0] == '-') {
        stack.push(operand1 - operand2);
      }
      else if (thing[0] == '*') {
        stack.push(operand1 * operand2);
      }
      else if (thing[0] == '/') {
        if (operand2 == 0) {
          cerr << "Error: Division by zero." << endl;
          return;
        }
        stack.push(operand1/operand2);
      }
      else {
        cerr << "Error: Invalid string \"" << instr << "\"" << endl;
        return;
      }
    }
    }
          
  if (stack.size() != 1) {
    cerr << "The evaluation is incomplete, missing input operators." << endl;
    return;
  }
  int answerResult = stack.top();
  stack.pop();
  cout << "The result of evaluating the postfix expression \"" << instr << "\" is the value: " << answerResult << endl;
  
}
