#pragma once
namespace Prog1 {
	// ��������� ��� ������� ������ �������
	struct Line {
		int n; // ���������� ��������� � ������ �������
		double* a; // ������ ���������
	};

   // ������� ���������
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

	// ��������� �������
	Line* input(int& m) noexcept; // ���� �������
	void output(const char* msg, const Line *a, int m) noexcept; // ����� �������
	Line* erase(Line*& a, int m) noexcept; // ������������ ������� ������
	//�� ������ �������� ��� �������, �.�. � ����� ������ ���� ���������� ��������, ������� ���������� ���� min � max
	int minmax(const Line * lines, int m, double& res) noexcept; // ���������� �������� ����������
	double minmax(const double* a, int m, bool(*f)(const double&, const double&)) noexcept; // ���������� min/max �������� �������
	int betterminmax(const Line* lines, int m, double& res) noexcept; // minmax ��� �������������� ������
	int slightlybetterminmax(const Line* lines, int m, double& res) noexcept; // minmax ��� �������������� ������ � � ����������� �� stl
}
