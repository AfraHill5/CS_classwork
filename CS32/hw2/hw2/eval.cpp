//Zach North
//603 885 768
//Homework 2 Question 5

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int infixConvert(const string& infix, string& postfix);
void postfixEval(string& postfix, bool values[], bool& result);


int evaluate(const string& infix, bool values[], string& postfix, bool& result)
{
	// Evaluates a boolean expression
          // Precondition: infix is an infix boolean expression consisting of
          //   the digits 0 through 9, the operators |, &, and !, and parentheses,
          //   with embedded blanks allowed for readability. 
          // Postcondition: If infix is a syntactically valid infix boolean
          //   expression, then postfix is set to the postfix form of that
          //   expression, result is set to the value of the expression (where
          //   each digit k represents the kth element of the values array), and
          //   the function returns zero.  If infix is a malformed expression,
          //   the return value is 1. (In that case, postfix may or may not be
          //   changed and but result must be unchanged.)



	int check = infixConvert(infix, postfix);
	//Now the postfix string has been filled with the expression
	if (check == 1)
		return 1; //malformed expression
	postfixEval(postfix, values, result);
	//evaluates the postfix expression
	return 0;
}

int infixConvert(const string& infix, string& postfix) //performs the conversion from infix to postfix
{
	if (infix.size() == 0)
		return 1; //must have some infix to evaluate
	int numberDigits = 0; //keeps track of the number of digits to avoid syntax errors
	bool containsComparisonOperator = false; //checks for a comparison operator
	postfix = ""; //blanks the postfix so it can be modified with input
	stack<char> operatorStack; //initializes the operating stack
	int j = infix.size();
	for (int i = 0; i < j; i++) //steps through the characters in the infix string
	{
		char current = infix[i];
		switch (current)
		{
		case ' ':
			break; //skips spaces
		case '0': //case: operand
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			postfix += current;
			numberDigits++;
			break;

		case '(':
			operatorStack.push(current);
			break;

		case ')': //pops the stack until it reaches a matching '('
			while (operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop(); //removes the original '('
			break;


		case '!': //operators
			while (operatorStack.size() > 0 && operatorStack.top() != '(' && operatorStack.top() != '&' && operatorStack.top() != '|') //the stack is not empty, the stack top is not '(', and the current char has lower precedence than the current stack top
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(current); //pushes the current ch onto the stack
			break;

		case '|':
			while (operatorStack.size() > 0 && operatorStack.top() != '(') //the stack is not empty, the stack top is not '(', and the current char has lower precedence than the current stack top
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(current); //pushes the current ch onto the stack
			containsComparisonOperator = true;
			break;
		case '&': 
			while (operatorStack.size() > 0 && operatorStack.top() != '(' && operatorStack.top() != '|') //the stack is not empty, the stack top is not '(', and the current char has lower precedence than the current stack top
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(current); //pushes the current ch onto the stack
			containsComparisonOperator = true;
			break;
		default: //malformed expression
			return 1;
		}
	}
	while (operatorStack.size() > 0) //adds the rest to postfix
	{
		if (operatorStack.top() == '(')
			return 1; //extra parenthesis -- syntax error
		postfix += operatorStack.top();
		operatorStack.pop();
	}
	if (containsComparisonOperator && numberDigits < 2)
		return 1; //trying to compare digits with less than 2 to compare
	if (numberDigits >= 2 && !containsComparisonOperator)
		return 1;

	return 0; //made it through successfully
}

void postfixEval(string& postfix, bool values[], bool& result)
{
	stack<bool> operandStack; //initializes the operand stack
	int j = postfix.size();
	for (int i = 0; i < j; i++)
	{
		char current = postfix[i];
		if (current == '0' || current == '1' || current == '2' || current == '3' || current == '4' || current == '5' || current == '6' || current == '7' || current == '8' || current == '9')
			//if the current character is an operand, push it on the stack
			operandStack.push(values[current - '0']);
		else //not an operand, must be an operator
		{
			bool operand2 = operandStack.top();
			operandStack.pop();
			bool operand1 = operandStack.top();
			operandStack.pop();
			switch (current)
			{
			case '!': //***I have no idea if this works.
				operandStack.push(!operand1); //flips operand 1
				operandStack.push(operand2); //puts operand 2 back on the stack
				break;
			case '&': //checks for equality
				if (operand1 == operand2)
					operandStack.push(true);
				else
					operandStack.push(false);
				break;
			case '|': //checks for difference
				if (operand1 != operand2)
					operandStack.push(true);
				else
					operandStack.push(false);
				break;
			}
		}
	}
	result = operandStack.top(); //there should be only one value left in the stack.
}

