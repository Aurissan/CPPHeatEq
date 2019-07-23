# CPPHeatEq
A simple program that provides a numerical and an analytical solution 
of the heat equation in a one-dimensional rod with Dirichlet boundary conditions in given time. The solution requires the user to input
thermal diffusivity (d), rod length (xmax), the length step (dx), time (tmax) and the time step (dt). The left boundary is set at 10°C, the right one at 20°C. The results are written into 2 .csv files - norm.csv (analytical) and results.csv (numerical).
# Analytical solution
This solution is obtained from the following equation: ![Alt text](img/main.png?raw=true), where ![Alt text](img/ck.png?raw=true)

However, the solution is only accurate for the value of the rod length L=25 due to the c<sub>k</sub> coefficients being pre-calculated.
# Notes
This code was originally written as a part of the assignment in my 3rd year at MUCTR.
