#pragma once
namespace Prog1 {
	// структура для задания строки матрицы
	struct Line {
		int n; // количество элементов в строке матрицы
		double* a; // массив элементов
	};

   // функции сравнения
	template <typename T>
	inline bool isgreater(const T& a, const T& b) noexcept
	{
		return a > b;
	}

	template <typename T>
	inline bool isless(const T& a, const T& b) noexcept
	{
		return a < b;
	}

	// прототипы функций
	Line* input(int& m) noexcept; // ввод матрицы
	void output(const char* msg, const Line *a, int m) noexcept; // вывод матрицы
	Line* erase(Line*& a, int m) noexcept; // освобождение занятой памяти
	//не лучшее название для функции, т.к. с таким именем есть стандарный алгоритм, который возвращает пару min и max
	int minmax(const Line * lines, int m, double& res) noexcept; // вычисление главного результата
	double minmax(const double* a, int m, bool(*f)(const double&, const double&)) noexcept; // вычисление min/max элемента вектора
	int betterminmax(const Line* lines, int m, double& res) noexcept; // minmax без дополнительной памяти
	int slightlybetterminmax(const Line* lines, int m, double& res) noexcept; // minmax без дополнительной памяти и с алгоритмами из stl
}
