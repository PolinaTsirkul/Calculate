#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <stack>
#include "string"
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Calculate
{
	string expression;
	stack<int> digit;
	stack<char> sign;
public:
	void Expression();
	bool Mistakes(const string expression);
	void ExampleSolution(int& result);
	void Compute(stack<int> &digit, stack<char> &sign, int &result, bool isSimplification);
	void Simplification(const string expression, int& result);
};

