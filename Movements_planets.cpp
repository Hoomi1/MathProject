#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

const unsigned int N = 4;
const double G = 6.674;
const double M = 1.9891 * pow(10, 10);

int main()
{
	static double x, y, ax, ay, V, r = 0;
	double x0[N] = { 0 };
	double y0[N] = { 0 };
	double V0x[N] = { 0 };
	double V0y[N] = { -38.86, -34.79, -29.29, -21.97 };
	double h[N] = { 7600, 19400, 31500, 59360 };
	x0[0] = { -0.467 * 1.496 * pow(10, 8) };
	x0[1] = { -0.728 * 1.496 * pow(10, 8) };
	x0[2] = { -1.017 * 1.496 * pow(10, 8) };
	x0[3] = { -1.67  * 1.496 * pow(10, 8) };

	std::ofstream file1;
	file1.open("Lab4_1.txt");
	std::ofstream file2;
	file2.open("Lab4_2.txt");
	std::ofstream file3;
	file3.open("Lab4_3.txt");
	std::ofstream file4;
	file4.open("Lab4_4.txt");

	for (double t = 0; t < 3801601; t = t + 3801.6)
	{
		for (int i = 0; i < N; ++i)
		{
			r = sqrt((x0[i] * x0[i]) + (y0[i] * y0[i]));
			ax = G * M * x0[i] / (r * r * r);
			V = V0x[i] + ax * h[i];
			x = x0[i] - V * h[i];
			V0x[i] = V;
			x0[i] = x;
		}
		for (int i = 0; i < N; ++i)
		{
			r = sqrt((x0[i] * x0[i] + y0[i] * y0[i]));
			ay = G * M * y0[i] / (r * r * r);
			V = V0y[i] - ay * h[i];
			y = y0[i] + V * h[i];
			V0y[i] = V;
			y0[i] = y;
		}

		file1 << std::fixed << std::setprecision(6) << x0[0] << "\t" << y0[0] << std::endl;
		file2 << std::fixed << std::setprecision(6) << x0[1] << "\t" << y0[1] << std::endl;
		file3 << std::fixed << std::setprecision(6) << x0[2] << "\t" << y0[2] << std::endl;
		file4 << std::fixed << std::setprecision(6) << x0[3] << "\t" << y0[3] << std::endl;
	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();
	return (0);
}
