#include "Calculate.h"
void Calculate::Expression()
{
	cout << "������� ��������� � ������� Enter\n";
	cout << "���������: ";
	getline(cin, this->expression, '\n');

	//������ ������� �� ������ ������, ����� � ���������� ������� � ����� ��� ������
	this->expression.erase(remove_if(this->expression.begin(), this->expression.end(), isspace), this->expression.end());

	int result;
	if (!Mistakes(expression))
	{
		this->Simplification(this->expression, result);
		this->ExampleSolution(result);
		cout << "�����: " << result << "\n\n";
	}
	
}

bool Calculate::Mistakes(const string expression)
{
	int open = 0;
	int close = 0;
	for (int i = 0; i < expression.size() + 1; i++)
	{
		if (expression[i] != '(' && expression[i] != ')' && expression[i] != '+' &&
			expression[i] != '-' && expression[i] != '*' && expression[i] != '/' &&
			expression[i] != '%' && expression[i] != '^' && (expression[i] < '0' && expression[i] > 9))
		{
			cout << "������������ ������ � ���������\n";
			return 1;
		}
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' ||
			 expression[i] == '/' || expression[i] == '^' || expression[i] == '%') &&
			(expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' ||
			 expression[i + 1] == '/' || expression[i + 1] == '^' || expression[i + 1] == '%'))
		{
			cout << "������������ ������: � ��������� ������ ���� ��� ����� ��������\n";
			return 1;
		}
		else if (expression[i] == ')' && (expression[i + 1] >= '0' && expression[i + 1] <= '9' ))
		{
			cout << "������������ ������: ����� ����������� ������� � ������ ����������� ���� �������� ��������\n";
			return 1;
		}
		else if (expression[i] == '(' && (expression[i + 1] == '+' || expression[i + 1] == '/' ||
			expression[i + 1] == '*' || expression[i + 1] == '%' || expression[i + 1] == '^'))
		{
			cout << "������������ ������: ����� ����������� ������� � �������� ������ ���������� �����\n";
			return 1;
		}
		else if (expression[i] > '0' && expression[i] < '9' && expression[i + 1] == '(')
		{
			cout << "������������ ������: ����� ������ � ����������� ������� \n����������� ���� ��������\n";
			return 1;
		}
		else if (expression[i] == '(' && expression[i + 1] == ')')
		{
			cout << "������������ ������: ����� ����������� � ����������� ������� ����������� ���������\n";
			return 1;
		}
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' ||
			expression[i] == '%' || expression[i] == '^') && expression[i+1] == ')')
		{
			cout << "������������ ������: ����� ������ �������� �������� � ����������� ������� ����������� ���������\n";
			return 1;
		}
		else if (expression[i] == ')' && expression[i + 1] == '(')
		{
			cout << "������������ ������: ����� ����������� � ����������� ������� ����������� ���� �������� ��������\n";
			return 1;
		}
		else if (expression[0] == '+' || expression[0] == '*' || expression[0] == '/' ||
			expression[0] == '^' || expression[0] == '%')
		{
			cout << "������������ ������: ��������� ���������� �� ����� �������� ��������\n";
			return 1;
		}
		else if (expression[0] == ')')
		{
			cout << "������������ ������: ��������� ���������� � ����������� ������\n";
			return 1;
		}
		else if (expression[expression.size()] == '+' || expression[expression.size()] == '-' || 
			expression[expression.size()] == '*' || expression[expression.size()] == '/' || 
			expression[expression.size()] == '^' || expression[expression.size()] == '%' )
		{
			cout << "������������ ������: ��������� ������������� ������ �������� ��������\n";
			return 1;
		}
		else if (expression[i] == '/' && expression[i + 1] == '0')
		{
			cout << "������� �� ����\n";
			return 1;
		}
		else if (expression[i] == '(' || expression[i] == ')')
		{
			if (expression[i] == '(')
				open++;
			else
				close++;
		}
	}
	if (open != close)
	{
		cout << "�������������� ����� ����������� ����������� � ����������� ������\n";
		return 1;
	}
		return 0;
}

void Calculate::ExampleSolution(int &result)
{
	/*��� �������� ���� ������������� � ��������� � ����� ����
	�������� ��� ����, ����� �������� ����������� � ���������� �������
	��������, � ��������� (������� �������� ����� ���������) 56-0+26, ����� ������ � ����������,
	��� ��� �� ����� ��������� ������ ������, � �� ��������, � ����� ����� ��������� 30(��������),� �� 82*/

	stack<int> copy_digit; 
	stack<char> copy_sign;
	int size_digit = this->digit.size();
	int size_sign = this->sign.size();
	for (int i = 0; i < size_digit; i++)
	{
		copy_digit.push(this->digit.top());
		this->digit.pop();
	}
	for (int k = 0; k < size_sign; k++)
	{
		copy_sign.push(this->sign.top());
		this->sign.pop();
	}
	while (!copy_sign.empty())
	{
		Compute(copy_digit, copy_sign, result, true);
	}
}

void Calculate::Compute(stack<int> &digit, stack<char> &sign, int &result, bool isSimplification)
{
	int num1, num2;
	char symbol;
	num1 = digit.top();
	digit.pop();
	num2 = digit.top();
	digit.pop();
	symbol = sign.top();
	sign.pop();
	switch (symbol)
	{
	case '+':
		result = num1 + num2;
		break;
	case '-':
		if (isSimplification == 1) //���� �� �������� ���� �����, � ������� �������� ����� ����������� ����� �������
			result = num1 - num2;
		else
			result = num2 - num1;
		break;
	case '*':
		result = num1 * num2;
		break;
	case '/':
		if (num1 == 0)
		{
			cout << "������� �� ����!";
			break;
		}
		if (isSimplification == 1) //���� �� �������� ���� �����, � ������� �������� ����� ����������� ����� �������
			result = num1 / num2; 
		else
			result = num2 / num1;
		break;
	case '^':
		result = pow(num2, num1);
		break;
	case '%':
		result = num2 % num1;
		break;
	}
	digit.push(result);
}

void Calculate::Simplification(const string expression, int &result)
{
	//�����, ������� �������� ��������� (� ���������� �������� ��������� � ���������� �����������: '+' ��� '-')

	string digit_string;
	int digit_int;
	for (int i = 0; i < this->expression.size() + 1; i++)
	{
		/*���� ������� ������� ����� ����� �� 0 �� 9, �� ���������� � ������
		���� � ��� ��������� ���������� �� �������� � ������� �������, �� ���� ����� �� ���������� � ������
		���� � ��� ����� ����� ������ ���� ������� �����, �� ���� ���������� ��� � ������*/
		if ((expression[i] >= '0' && expression[i] <= '9') || (i == 0 && expression[i] == '-') || 
			(i != 0 && expression[i-1] == '(' && expression[i] == '-'))
		{
			digit_string += expression[i];
		}
		else 
		{
			if (digit_string != "")
			{
				//���������� ������ � ������� �������� � ���������� � ����
				digit_int = stoi(digit_string);
				digit.push(digit_int);
				digit_string = "";
			}
			/*���� ������� ������� ����� ���������, ������� ����� ��� �� ���������, ��� � ��������, ������� ��� ����� � �����,
			�� ������� ����������� �������� �� ����� � ���������� ����������, � ����� ������ ������� ������� � ����*/
			if (!sign.empty() && ( (expression[i] == '+' || expression[i] == '-') && (sign.top() == '+' || sign.top() == '-') ||
				(expression[i] == '*' || expression[i] == '/') && (sign.top() == '*' || sign.top() == '/' )))
			{
				Compute(this->digit, this->sign, result, false);
				if (expression[i] != '\0' )
					sign.push(expression[i]);
			}
			/*���� �� �������� �����-�� �� ���� ������, �� ���������� ��� � ���� �� �������, ��� ��� ��� ����������
			��� ���������� ������� �������� �����, ������� ����� ����� ����� �����*/
			else if (sign.empty() || expression[i] == '(' || expression[i] == '^' || expression[i] == '%' ||
			        ((sign.top() == '+' || sign.top() == '-') && (expression[i] == '*' || expression[i] == '/')) ||
			        (sign.top() == '(' && (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || 
				    expression[i] == '/')) )
			{
				if(expression[i]!='\0')
					sign.push(expression[i]);
			}

			/*���� � ������� ����� ����� ���� ���������� � ������� ��� ������� �� �������, �� ����� ���������*/
			else if (sign.top() == '^' || sign.top() == '%')
			{
				Compute(this->digit, this->sign, result, false);
				/*���� ����� ����, ��� �� ������� � ������� ��� ����� ������� �� �������, � ����� ����� 
				�������� � ����� ������ �����������, �� ��������� ��� (����� ��������� ��������� ��������)*/
				if (!sign.empty() && (sign.top() == '*' || sign.top() == '/' || sign.top() == '+' || sign.top() == '-'))
				{
					Compute(this->digit, this->sign, result, false);
				}
				/*� ������ ����� ���� ���������� �� ��������� � ���� �� ������� ��� ������� �������*/
				if (expression[i] != '\0')
					sign.push(expression[i]);
			}

			/*���� ��������� ���� ��������� ��� �������, �� ����� ���������*/
		    else if ((sign.top() == '*' || sign.top() == '/') )
			{
				Compute(this->digit, this->sign, result, false);
				if (!sign.empty() && (sign.top() == '+' || sign.top() == '-'))
				{
					Compute(this->digit, this->sign, result, false);
				}
				/*���� ������� ������� ����� ')', �� � ���� �� �������. ���� ���� ��������� �������, ������� ����� 
				������� ��� ��������, ����������� ������ ������*/
				if (expression[i] != '\0' && expression[i] != ')')
					sign.push(expression[i]);
			}
			
		}
		if (expression[i] == ')')
		{
			/*���� ��� ������� ����� ')', �� ����� ��������� ��, ��� ��������� ������ ������ �� ��� ���, ���� �� �������� 
			������������� ������*/
			while (this->sign.top() != '(')
			{
			    Compute(this->digit, this->sign, result, false);
		    }
		    sign.pop();
			/*���� ����� ����������� ������� ��� �������� ��������� ��� �������, �� ����� ���������, ���� ��������� ���������*/
		    if (!sign.empty() && (sign.top() == '*' || sign.top() == '/'))
	    	{
		    	Compute(this->digit, this->sign, result, false);
		    }
		}
	}
	
}