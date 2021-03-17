#include "Calculate.h"
void Calculate::Expression()
{
	cout << "Введите выражение и нажмите Enter\n";
	cout << "Выражение: ";
	getline(cin, this->expression, '\n');

	//удаляю пробелы из строки просто, чтобы в дальнейшем перебор в цикле был меньше
	this->expression.erase(remove_if(this->expression.begin(), this->expression.end(), isspace), this->expression.end());

	int result;
	if (!Mistakes(expression))
	{
		this->Simplification(this->expression, result);
		this->ExampleSolution(result);
		cout << "Ответ: " << result << "\n\n";
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
			cout << "Недопустимый символ в выражении\n";
			return 1;
		}
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' ||
			 expression[i] == '/' || expression[i] == '^' || expression[i] == '%') &&
			(expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' ||
			 expression[i + 1] == '/' || expression[i + 1] == '^' || expression[i + 1] == '%'))
		{
			cout << "Недопустимая запись: в выражении подряд идут два знака операции\n";
			return 1;
		}
		else if (expression[i] == ')' && (expression[i + 1] >= '0' && expression[i + 1] <= '9' ))
		{
			cout << "Недопустимая запись: между закрывающей скобкой и числом отсутствует знак бинарной операции\n";
			return 1;
		}
		else if (expression[i] == '(' && (expression[i + 1] == '+' || expression[i + 1] == '/' ||
			expression[i + 1] == '*' || expression[i + 1] == '%' || expression[i + 1] == '^'))
		{
			cout << "Недопустимая запись: между открывающей скобкой и бинарным знаком отсутсвует число\n";
			return 1;
		}
		else if (expression[i] > '0' && expression[i] < '9' && expression[i + 1] == '(')
		{
			cout << "Недопустимая запись: между числом и открывающей скобкой \nотсутствует знак операции\n";
			return 1;
		}
		else if (expression[i] == '(' && expression[i + 1] == ')')
		{
			cout << "Недопустимая запись: между открывающей и закрывающей скобкой отсутствует выражение\n";
			return 1;
		}
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' ||
			expression[i] == '%' || expression[i] == '^') && expression[i+1] == ')')
		{
			cout << "Недопустимая запись: между знаком бинарной операции и закрывающей скобкой отсутствует выражение\n";
			return 1;
		}
		else if (expression[i] == ')' && expression[i + 1] == '(')
		{
			cout << "Недопустимая запись: между закрывающей и открывающей скобкой отсутствует знак бинарной операции\n";
			return 1;
		}
		else if (expression[0] == '+' || expression[0] == '*' || expression[0] == '/' ||
			expression[0] == '^' || expression[0] == '%')
		{
			cout << "Недопустимая запись: выражение начинается со знака бинарной операции\n";
			return 1;
		}
		else if (expression[0] == ')')
		{
			cout << "Недопустимая запись: выражение начинается с закрывающей скобки\n";
			return 1;
		}
		else if (expression[expression.size()] == '+' || expression[expression.size()] == '-' || 
			expression[expression.size()] == '*' || expression[expression.size()] == '/' || 
			expression[expression.size()] == '^' || expression[expression.size()] == '%' )
		{
			cout << "Недопустимая запись: выражение заканчивается знаком бинарной операции\n";
			return 1;
		}
		else if (expression[i] == '/' && expression[i + 1] == '0')
		{
			cout << "Деление на ноль\n";
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
		cout << "Несоответствие между количеством открывающих и закрывающих скобок\n";
		return 1;
	}
		return 0;
}

void Calculate::ExampleSolution(int &result)
{
	/*наш основной стек переворачиваю и записываю в новый стек
	делается для того, чтобы операции вычислялись в правильном порядке
	например, в выражении (которое осталось после упрощения) 56-0+26, будет ошибка в результате,
	так как мы будет вычислять справа налево, а не наоборот, и тогда будет результат 30(неверный),а не 82*/

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
		if (isSimplification == 1) //если мы передали стек копию, в котором элементы будут вычисляться слева направо
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
			cout << "Деление на ноль!";
			break;
		}
		if (isSimplification == 1) //если мы передали стек копию, в котором элементы будут вычисляться слева направо
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
	//метод, который упрощает выражение (в результате остаются операторы с одинаковым приоритетом: '+' или '-')

	string digit_string;
	int digit_int;
	for (int i = 0; i < this->expression.size() + 1; i++)
	{
		/*если элемент массива равен цифре от 0 до 9, то записываем в строку
		если у нас выражение начинается со значения с унарным минусом, то этот минус мы записываем в строку
		если у нас сразу после скобки идет унарный минус, то тоже записываем это в строку*/
		if ((expression[i] >= '0' && expression[i] <= '9') || (i == 0 && expression[i] == '-') || 
			(i != 0 && expression[i-1] == '(' && expression[i] == '-'))
		{
			digit_string += expression[i];
		}
		else 
		{
			if (digit_string != "")
			{
				//превращаем строку в интовое значение и записываем в стек
				digit_int = stoi(digit_string);
				digit.push(digit_int);
				digit_string = "";
			}
			/*если элемент массива равен оператору, который имеет тот же приоритет, что и оператор, который уже лежит в стеке,
			то сначала вытаскиваем значение со стека и производим вычисления, а потом кладем элемент массива в стек*/
			if (!sign.empty() && ( (expression[i] == '+' || expression[i] == '-') && (sign.top() == '+' || sign.top() == '-') ||
				(expression[i] == '*' || expression[i] == '/') && (sign.top() == '*' || sign.top() == '/' )))
			{
				Compute(this->digit, this->sign, result, false);
				if (expression[i] != '\0' )
					sign.push(expression[i]);
			}
			/*если мы встерили какой-то из этих знаков, то отправляем его в стек со знаками, так как для вычислений
			нам необходимо сначала получить число, которое стоит после этого знака*/
			else if (sign.empty() || expression[i] == '(' || expression[i] == '^' || expression[i] == '%' ||
			        ((sign.top() == '+' || sign.top() == '-') && (expression[i] == '*' || expression[i] == '/')) ||
			        (sign.top() == '(' && (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || 
				    expression[i] == '/')) )
			{
				if(expression[i]!='\0')
					sign.push(expression[i]);
			}

			/*если в вершине стека лежит знак возведения в степень или остатка от деления, то сразу вычисляем*/
			else if (sign.top() == '^' || sign.top() == '%')
			{
				Compute(this->digit, this->sign, result, false);
				/*если после того, как мы возвели в степень или нашли остаток от деления, в стеке лежит 
				оператор с более низким приоритетом, то вычисляем его (чтобы сохранить приоритет операций)*/
				if (!sign.empty() && (sign.top() == '*' || sign.top() == '/' || sign.top() == '+' || sign.top() == '-'))
				{
					Compute(this->digit, this->sign, result, false);
				}
				/*и только после всех вычислений мы добавляем в стек со знаками наш элемент массива*/
				if (expression[i] != '\0')
					sign.push(expression[i]);
			}

			/*если встретили знак умножения или деления, то сразу вычисляем*/
		    else if ((sign.top() == '*' || sign.top() == '/') )
			{
				Compute(this->digit, this->sign, result, false);
				if (!sign.empty() && (sign.top() == '+' || sign.top() == '-'))
				{
					Compute(this->digit, this->sign, result, false);
				}
				/*Если элемент массива равен ')', то в стек не заносим. Ниже есть отдельное условие, которое будет 
				считать все элементы, находящиеся внутри скобки*/
				if (expression[i] != '\0' && expression[i] != ')')
					sign.push(expression[i]);
			}
			
		}
		if (expression[i] == ')')
		{
			/*если наш элемент равен ')', то будем вычислять всё, что находится внутри скобок до тех пор, пока не встретим 
			открывающуюся скобку*/
			while (this->sign.top() != '(')
			{
			    Compute(this->digit, this->sign, result, false);
		    }
		    sign.pop();
			/*если перед открывающей скобкой был оператор умножения или деления, то сразу вычисляем, дабы сохранить приоритет*/
		    if (!sign.empty() && (sign.top() == '*' || sign.top() == '/'))
	    	{
		    	Compute(this->digit, this->sign, result, false);
		    }
		}
	}
	
}