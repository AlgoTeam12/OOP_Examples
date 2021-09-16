// Lab01_example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Prog1.h"


int main()
{
	using namespace Prog1;
	Line* arr = nullptr; // исходный массив
	int m = 0; // количество строк в матрице
	double res = 0; // полученный результат

	arr = input(m); // ввод матрицы
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	if (slightlybetterminmax(arr, m, res)) {  // вычисление требуемого результата
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}
	output("Sourced matrix", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); // освобождение памяти
	return 0;
}
