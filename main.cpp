// Lab01_example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Prog1.h"


int main()
{
	using namespace Prog1;
	Line* arr = nullptr; // �������� ������
	int m = 0; // ���������� ����� � �������
	double res = 0; // ���������� ���������

	arr = input(m); // ���� �������
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	if (slightlybetterminmax(arr, m, res)) {  // ���������� ���������� ����������
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}
	output("Sourced matrix", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); // ������������ ������
	return 0;
}
