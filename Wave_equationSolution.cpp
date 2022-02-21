#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#define PI 3.14

double func(double x)
{
	return (0.2 * (1 - x) * sin(PI * x));
}

int main()
{
	std::ofstream file;
	file.open("Lab2.txt");
	double _h = 0.1;
	double _k = 0.05;
	double _x = 0;
	double _ld = (_k / _h);
	double arr[11][11] = { 0 };
	for (int i = 1; i < 10; ++i)
	{
		arr[i][1] = func(_x + _h);
		_x = _x + _h;
	}
	int a = 0;
	for (int i = 1; i < 10; ++i, ++a)
	{
		for (int j = 2; j < 10; ++j)
			arr[i] [j] = 2 * (1 - _ld * _ld) * arr[i][j - 1] + _ld * _ld * (arr[i+ 1][j - 1] + arr[i - 1][j - 1]) - arr[i] [j - 2];
		for (int j = 1; j < 10; ++j)
		{
			file << std::fixed << std::setprecision(6) << arr[i][j] << "\t";
		}
		std::cout << "\n";
	}
	file.close();
	return (0);

}

