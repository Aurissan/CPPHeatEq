// EFDMHeateq.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void analytical(int nx, int nt, double dx, double dt, double d, double xmax, double** u) { //analytical solution
	double pi = 3.1415926;
	double c1 = 20 / pi;
	double c3 = 20 / (3 * pi);
	double c5 = 20 / (5 * pi);
	double c7 = 20 / (7 * pi);
	double** v = new double*[nx + 1];
	for (int i = 0; i < nx + 1; i++) {
		v[i] = new double[nt + 1];
	}
	for (int i = 0; i < nx + 1; i++) {
		for (int j = 0; j < nt + 1; j++) {
			v[i][j] = (20 * dx*i) / 25 + c1*exp(-(pi*pi*d*dt*j) / (xmax*xmax))*sin((pi*dx*i) / xmax) + c3*exp(-(9 * pi*pi*d*dt*j) / (xmax*xmax))*sin((3 * pi*dx*i) / xmax) + c5*exp(-(25 * pi*pi*d*dt*j) / (xmax*xmax))*sin((5 * pi*dx*i) / xmax) + c7*exp(-(49 * pi*pi*d*dt*j) / (xmax*xmax))*sin((7 * pi*dx*i) / xmax);
		} //analytical equation
	}
	
	double* norm = new double[nt + 1];
	for (int i = 0; i < nt + 1; i++) {
		double sum = 0;
		for (int j = 0; j < nx + 1; j++) {
			sum += pow(abs(v[j][i] - u[j][i]), 2);
		}
		norm[i] = sqrt(sum);
	}
	ofstream fout;
	fout.open("norm.csv");
	for (int i = 0; i < nt + 1; i++) {
		fout << i*dt << ";";
	}
	fout << endl;
	for (int i = 0; i < nt + 1; i++) {
		fout << norm[i] << ";";
	}
	fout.close();
}

int main() {
	double xmax, dx, tmax, dt, d;
	cout << "enter d: " << endl; //thermal diffusivity
	cin >> d;
	cout << "enter xmax: " << endl; //length of a 1d rod
	cin >> xmax;
	cout << "enter dx: " << endl; //length step
	cin >> dx;
	cout << "enter tmax: " << endl; //maximum time
	cin >> tmax;
	cout << "enter dt: " << endl; //time step
	cin >> dt;
	double courant = d * (dt / (dx*dx)); //calculate Courant number
	cout << "Courant number: " << courant << endl;
	int nt, nx;
	nx = xmax / dx;
	nt = tmax / dt;;
	double** u = new double*[nx + 1];
	for (int i = 0; i < nx + 1; i++) {
		u[i] = new double[nt + 1];
	}
	for (int i = 0; i < nx + 1; i++) {
		u[i][0] = 10;  //left boundary condition
	}
	for (int i = 0; i < nt + 1; i++) {
		u[0][i + 1] = 0;
		for (int j = 1; j < nx; j++) {
			u[j][i + 1] = u[j][i] + courant * (u[j + 1][i] - 2 * u[j][i] + u[j - 1][i]); //explicit recurrence equation
		}
		u[nx][i + 1] = 20;  //right boundary condition

	}
	ofstream fout;
	fout.open("results.csv");
	fout << " " << ";";
	for (int i = 0; i < nt + 1; i++) {
		fout << i*dt << ";";
	}
	fout << endl;
	for (int i = 0; i < nx + 1; i++) {
		fout << i*dx << ";";
		for (int j = 0; j < nt + 1; j++) {
			fout << u[i][j] << ";";
		}
		fout << endl;
	}
	analytical(nx, nt, dx, dt, d, xmax, u);
	cout << "Done calculating." << endl;
	system("pause");
	return 0;
}

