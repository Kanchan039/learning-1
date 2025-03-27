#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6
#define MAX_ITER 100

// Define the functions
void functions(double x[], double f[]) {
    f[0] = x[0] * x[0] + x[1] * x[1] - 4;  // Example: x^2 + y^2 - 4 = 0
    f[1] = x[0] - x[1] - 1;  // Example: x - y - 1 = 0
}

// Define the Jacobian matrix
void jacobian(double x[], double J[2][2]) {
    J[0][0] = 2 * x[0]; // df1/dx
    J[0][1] = 2 * x[1]; // df1/dy
    J[1][0] = 1;        // df2/dx
    J[1][1] = -1;       // df2/dy
}

// Function to solve a linear system using Gaussian elimination
void solve_linear_system(double A[2][2], double B[2], double X[2]) {
    double det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    if (fabs(det) < EPSILON) {
        printf("Jacobian is singular!\n");
        return;
    }
    X[0] = (B[0] * A[1][1] - B[1] * A[0][1]) / det;
    X[1] = (A[0][0] * B[1] - A[1][0] * B[0]) / det;
}

// Newton-Raphson method for a system of equations
void newton_raphson(double x[]) {
    int iter;
    double f[2], J[2][2], delta[2];
    for (iter = 0; iter < MAX_ITER; iter++) {
        functions(x, f);
        jacobian(x, J);
        double negF[2] = {-f[0], -f[1]};
        solve_linear_system(J, negF, delta);
        x[0] += delta[0];
        x[1] += delta[1];
        if (fabs(delta[0]) < EPSILON && fabs(delta[1]) < EPSILON) {
            break;
        }
    }
    if (iter == MAX_ITER) {
        printf("Solution did not converge.\n");
    } else {
        printf("Converged in %d iterations.\n", iter);
        printf("Solution: x = %lf, y = %lf\n", x[0], x[1]);
    }
}

int main() {
    double x[2] = {1.0, 1.0};  // Initial guess
    newton_raphson(x);
    return 0;
}