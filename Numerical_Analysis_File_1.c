#include <stdio.h>
#include <math.h>
#define EPSILON 1e-6 //Precision for the solution
#define MAX_ITER 100 //Maximum iterations for the method

//Function for the 1st equation
double f1(double x,double y){
    return x*y+x*x-y*y*y-1;
}
//Function for the 2nd equation
double f2(double x,double y){
    return x+2*y-x*y*y-2;
}


//Partial derivative of f1 with respect to x
double df1_dx(double x,double y){
    return y+2*x;
}
//Partial derivative of f1 with respect to y
double df1_dy(double x,double y){
    return x-3*y*y;
}


//Partial derivative of f2 with respect to x
double df2_dx(double x,double y){
    return 1-y*y;
}
//Partial derivative of f2 with respect to y
double df2_dy(double x,double y){
    return 2-2*x*y;
}

//Now, we will define the function for solving system of equations using Newton Raphson Method
void solve_system(double x0,double y0){
    double x=x0, y=y0;
    double fx1, fx2, j11, j12, j21, j22, det, dx, dy;
    int iter=0;

    while(iter<MAX_ITER){
        //Firstly, we will calculate the function values
        fx1=f1(x,y);
        fx2=f2(x,y);
        //If the function values are sufficiently close to zero, we have a solution
        if(fabs(fx1)<EPSILON && fabs(fx2)<EPSILON){
            printf("Solution found: x=%f,y=%f\n",x,y);
            return;
        }
        //Now we will proceed with Newton Raphson Method when the above condition is not satisfied
        //Compute the Jacobian Matrix
        j11=df1_dx(x,y);
        j12=df1_dy(x,y);
        j21=df2_dx(x,y);
        j22=df2_dy(x,y);

        //Calculate the determinant of the jacobian 
        det=j11*j22-j12*j21;
        if(fabs(det)<EPSILON){
            printf("jacobian is singular, cannot proceed.\n");
            return;
        }
        //Compute the changes (dx,dy) using the inverse of the Jacabian
        dx=(fx1*j22-fx2*j12)/det;
        dy=(fx2*j11-fx1*j21)/det;
        //Update the values of x and y
        x=x-dx;
        y=y-dy;

        iter++;
    }
    //If the loop finishes, the solution was not found within MAX_ITER
    printf("Solution not found within %d iterations.\n",MAX_ITER);
}

int main(){
    double x0=1.0, y0=1.0; //Initial guess
    solve_system(x0,y0);
    return 0;
}