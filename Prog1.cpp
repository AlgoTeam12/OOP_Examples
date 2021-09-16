#include <iostream>
#include <algorithm>
#include <vector>
#include "Prog1.h"

namespace Prog1 {
	// функция ввода
	Line* input(int& rm) noexcept
	{
		const char* pr = ""; // будущее сообщение об ошибке
		Line* lines = nullptr;  // динамический массив строк матрицы
		int m = 0;	// количество строк матрицы
		// сначала вводим количество строк
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (!(std::cin >> m)) // обнаружена ошибка ввода или конец файла
				return nullptr;
		} while (m < 1);

		// выделяем память под массив структур - строк матрицы
		try {
			lines = new Line[m];
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "Too many rows in matrix: " << ba.what() << std::endl;
			return nullptr;
		}
		for (int i = 0; i < m; i++) {
			// теперь для каждой строки матрицы вводим количество столбцов 
			pr = "";
			do {
				std::cout << pr << std::endl;
				std::cout << "Enter number of items in line #" << (i + 1) << " --> ";
				pr = "You are wrong; repeat please!";
				if (!(std::cin >> lines[i].n)) { // обнаружена ошибка ввода или конец файла
					erase(lines, i); // освобождение памяти, занятой ранее введенными строками
					return nullptr;
				}
			} while (lines[i].n < 1);


			// и выделяем необходимую память под элементы строки
			try {
				lines[i].a = new double[lines[i].n];
			}
			catch (std::bad_alloc& ba)
			{
				std::cout << "Too many items in matrix: " << ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}

			// теперь можно вводить сами элементы данной строки матрицы
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < lines[i].n; j++) {
				if (!(std::cin >> lines[i].a[j])) { // обнаружена ошибка ввода или конец файла
					erase(lines, i + 1); // освобождение памяти, занятой ранее введенными строками
					return nullptr;
				}
			}
		}
		// формируем результат - количество строк в матрице
		rm = m;
		return lines;
	}

	// функция вывода
	void output(const char* msg, const Line* a, int m) noexcept
	{
		int i, j;
		std::cout << msg << ":" << std::endl;
		for (i = 0; i < m; ++i) {
			for (j = 0; j < a[i].n; ++j)
				std::cout << (j ? " " : "") << a[i].a[j];
			std::cout << std::endl;
		}
	}



	// функция освобождения занятой памяти
	Line* erase(Line*& lines, int m) noexcept
	{
		int i;
		for (i = 0; i < m; i++)
			delete[] lines[i].a;
		delete[] lines;
		return nullptr;
	}

	// функция вычисления главного результата
	int minmax(const Line * lines, int m, double& res) noexcept
	{
		double* s = nullptr;
		try {
			s = new double[m]; // вектор для получения max элементов в строке - по строкам
		}
		catch (std::bad_alloc& ba)
		{
			std::cerr << ba.what() << std::endl;
			return 1;
		}
		int i;
		for (i = 0; i < m; i++)
			s[i] = minmax(lines[i].a, lines[i].n, isgreater);
		res = minmax(s, m, isless);
		delete[] s;
		return 0;
	}

	int betterminmax(const Line* lines, int m, double& res) noexcept
	{
		res = std::numeric_limits<double>::max();
		double t = 0;
		for (int i = 0; i < m; ++i)
			res = (t = minmax(lines[i].a, lines[i].n, isgreater)) < res ? t : res;
		return 0;
	}


	int slightlybetterminmax(const Line* lines, int m, double& res) noexcept
	{
		res = std::numeric_limits<double>::max();
		double t = 0;
		for (int i = 0; i < m; ++i)
			res = std::min(*std::max_element(lines[i].a, lines[i].a + lines[i].n), res);
		return 0;
	}


	// функция вычисления min/max элемента вектора
	double minmax(const double *a, int m, bool(*f)(const double&, const double&)) noexcept
	{
		double res = a[0];
		int i;
		for (i = 0; i < m; ++i)
			if (f(a[i], res))
				res = a[i];
		return res;
	}
}
