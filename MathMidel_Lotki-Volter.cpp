#include <fstream>
#include <math.h>
#include <iostream>
//
//////////////////////хищник-жертва///////////////////
//#define ALPHA 0.25
//#define BETA 0.002
//#define GAMMA 0.5
//#define DELTA 0.1
/////////////////////////////////////////////////////
//
//
//double fx(double x, double y)
//{
//	return (ALPHA * x - BETA * x * y);
//}
//
//double fy(double x, double y)
//{
//	return (-GAMMA * y + DELTA * x * y);
//}
//
//int main()
//{
//	float x0 = 100.0f;
//	float y0 = 100.0f;
//	float x = x0;
//	float _y = y0;
//	float _h = 0.1f;
//	float _k1x, _k2x, _k3x, _k4x;
//	float _k1y, _k2y, _k3y, _k4y;
//	std::ofstream file;
//	try
//	{
//		file.open("Lab1.txt");
//	}
//	catch (std::exception& e)
//	{
//		std::cout <<e.what() << std::endl;
//	}
//	for (float x = x0 ; x <= 101; x += _h)
//	{
//		file << x << "\t"  << _y  << "\n";
//
//		_k1x = _h * fx(x, _y);
//		_k1y = _h * fy(x, _y);
//		_k2x = _h * fx(x + 0.5 * _h, _y + 0.5 * _k1x);
//		_k2y = _h * fy(x + 0.5 * _h, _y + 0.5 * _k1y);
//		_k3x = _h * fx(x + 0.5 * _h, _y + 0.5 * _k2x);
//		_k3y = _h * fy(x + 0.5 * _h, _y + 0.5 * _k2y);
//		_k4x = _h * fx(x + _h, _y + _k3x);
//		_k4y = _h * fy(x + _h, _y + _k3y);
//
//		x = x + _h / 6.0 * (_k1x + 2 * _k2x + 2 * _k3x + _k4x);
//		_y = _y + _h / 6.0 * (_k1y + 2 * _k2y + 2 * _k3y + _k4y);
//	}
//	file.close();
//	return (0);
//}
//
using namespace std;


#define hh			0.1	// Определяем шаг

// Параметры системы
#define X_init		1.0	// кол-во жертвы(V)
#define Y_init		0.05// кол-во хищников(P)
#define Alpha		0.25// вероятность рождаемости жертв
#define Beta		0.1	// вероятность смертности жертв при встрече с хищником
#define Gamma		0.5	// вероятность убыли хищников при нехватке еды
#define Delta		0.1	// вероятность достаточности еды для размножения хищников

#define T_start		0.0	// Время начала
#define T_finish	100.0// Время окончания

// Функция для жертвы
double fx(double x, double y)
{
	return (Alpha * x - Beta * x * y);
}

// Функция для хищника
double fy(double x, double y)
{
	return (-Gamma * y + Delta * x * y);
}

// Метод Рунге-Кутта для решения системы 
void runge_kutta(double *x, double *y, double h, double(*fx)(double, double), double(*fy)(double, double))
{
	double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4;

	dx1 = fx(*x, *y);
	dy1 = fy(*x, *y);
	dx2 = fx(*x + (h / 0.5) * dx1, *y + (h / 0.5) * dy1);
	dy2 = fy(*x + (h / 0.5) * dx1, *y + (h / 0.5) * dy1);
	dx3 = fx(*x + (h / 0.5) * dx2, *y + (h / 0.5) * dy2);
	dy3 = fy(*x + (h / 0.5) * dx2, *y + (h / 0.5) * dy2);
	dx4 = fx(*x + h * dx3, *y + h * dy3);
	dy4 = fy(*x + h * dx3, *y + h * dy3);

	*x += h * (dx1 + 2.0 * dx2 + 2.0 * dx3 + dx4) / 6.0;
	*y += h * (dy1 + 2.0 * dy2 + 2.0 * dy3 + dy4) / 6.0;
}

int main()
{
	setlocale(0, "");
	std::ofstream file;
	file.open("Lab1.txt");

	double x, y;
	double i = T_start;
	x = X_init;
	y = Y_init;

	do
	{
		file << x << "\t" << y << endl;
		runge_kutta(&x, &y, hh, fx, fy);
		i += hh;

	} while (i <= T_finish);

	file << "\n";
	file << Alpha / Beta << "\t" << Gamma / Delta << endl;
	return 0;
}
