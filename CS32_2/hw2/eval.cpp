#include <string>
#include <iostream>
#include <stack>
#include <cctype>
#include "Map.h"
using namespace std;


	// Evaluates an integer arithmetic expression
	// Precondition: infix is an infix integer arithmetic
	//   expression consisting of single lower case letter operands,
	//   parentheses, and the operators +, -, *, /, with embedded blanks
        //   allowed for readability. 
	// Postcondition: If infix is a syntactically valid infix integer
	//   expression whose only operands are single lower case letters
	//   (whether or not they appear in the values map), then postfix is
        //   set to the postfix form of the expression; otherwise postfix may
        //   or may not be changed, result is unchanged, and the function
        //   returns 1.  If infix is syntactically valid but contains at
        //   least one lower case letter operand that does not appear in the
        //   values map, then result is unchanged and the function returns 2.
        //   If infix is syntactically valid and all its lower case operand
        //   letters appear in the values map, then if evaluating the
        //   expression (using for each letter in the expression the value in
        //   the map that corresponds to it) attempts to divide by zero, then
	//   result is unchanged and the function returns 3; otherwise,
        //   result is set to the value of the expression and the function
        //   returns 0.

int precedence(const char& c); //returns the precedence of an operator

 
int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	postfix = "";
	stack<char> operatorStack;
	for (int i = 0; i < infix.length(); i++)
		//for each char in the infix string
	{
		char ch = infix.at(i);
		switch(ch)
		{
		case ' ': //blank, do nothing
			break;
		case 'a': //case: operand
		case 'b': case 'c':
		case 'd': case 'e':
		case 'f': case 'g':
		case 'h': case 'i':
		case 'j': case 'k':
		case 'l': case 'm':
		case 'n': case 'o':
		case 'p': case 'q':
		case 'r': case 's':
		case 't': case 'u':
		case 'v': case 'w':
		case 'x': case 'y':
		case 'z':
			postfix += ch;
			break;
		case '(': //beginning of expression
			operatorStack.push(ch);
			break;
		case ')': //end of expression
			//need to find matching '('
			while(operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
			break;
		case '+': //case: operator
		case '-':
		case '*':
		case '/':
			while (operatorStack.size() != 0 && operatorStack.top() != '(' &&
					precedence(ch) > precedence(operatorStack.top()))
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(ch);
			break;

		default: //some other character, syntactically invalid
			return 1;
		}
	}
	if (operatorStack.empty() && postfix.length()>=2) //syntax error
		return 1;
	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	//now, postfix is set and ready to be evaluated
	stack<int> operandStack;
	for (int i = 0; i < postfix.length(); i++)
	{
		int operand1, operand2;
		char ch = postfix.at(i);
		switch (ch)
		{
		case ' ': //blank
			break; //do nothing
		case 'a': //case: operand
		case 'b': case 'c':
		case 'd': case 'e':
		case 'f': case 'g':
		case 'h': case 'i':
		case 'j': case 'k':
		case 'l': case 'm':
		case 'n': case 'o':
		case 'p': case 'q':
		case 'r': case 's':
		case 't': case 'u':
		case 'v': case 'w':
		case 'x': case 'y':
		case 'z':
			if (values.contains(ch))
			{
				int val;
				values.get(ch, val);
				operandStack.push(val);
			}
			else
				return 2; //invalid char
			break;
		case '+': //case operator
		case '-':
		case '*':
		case '/':
			if (operandStack.size() < 2)
				return 1; //invalid input
			operand2 = operandStack.top();
			operandStack.pop();
			operand1 = operandStack.top();
			operandStack.pop();
			if (ch == '+')
			{
				operand1 += operand2;
				operandStack.push(operand1);
				break;
			}
			else if (ch == '-')
			{
				operand1 -= operand2;
				operandStack.push(operand1);
				break;				
			}
			else if (ch == '*')
			{
				operand1 *= operand2;
				operandStack.push(operand1);
				break;
			}
			else //(ch == '/')
			{
				if (operand2 == 0)
					return 3; //attempting to divide by 0
				operand1 /= operand2;
				operandStack.push(operand1);
				break;
			}
		default:
			return 1; //bad syntax
		}
	}
	//there should be only one value on the stack, and it is the answer
	if (operandStack.empty()) //syntax error, probably empty string
		return 1;
	result = operandStack.top();
	return 0;
}

int precedence(const char& c) //returns the precedence of an operator
{
	if (c == '*' || c == '/' || c == '%')
		return 2;
	else if (c == '+' || c == '-')
		return 2;
	else //error
		return 0;
}

#include <cassert>
int main()
	{
	    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
	    Map m;
	    for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	    string pf;
	    int answer;
	    assert(evaluate("a+ e", m, pf, answer) == 0  &&
	                            pf == "ae+"  &&  answer == -6);
	    answer = 999;
	    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
	    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
	    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
	    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
	    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
	      // unary minus not allowed:
	    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
	    assert(evaluate("a*b", m, pf, answer) == 2  &&
	                            pf == "ab*"  &&  answer == 999);
	    assert(evaluate("y+o*(a-u) ", m, pf, answer) == 0  &&
	                            pf == "yoau-*+"  &&  answer == -1);
	    answer = 999;
	    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                                    pf == "oyy-/"  &&  answer == 999);
	    assert(evaluate(" a  ", m, pf, answer) == 0  &&
	                            pf == "a"  &&  answer == 3);
	    assert(evaluate("((a))", m, pf, answer) == 0  &&
	                            pf == "a"  &&  answer == 3);
	    cout << "Passed all tests" << endl;
	}