#include<stdio.h>

#define N 3 //Dimension of the matrix
void luDecomposition(float A[N][N],float L[N][N],float U[N][N]){
    for(int i=0;i<N;i++){
        //Calculate Upper Triangular matrix U
        for(int k=i;k<N;k++){
            float sum=0.0;
            for(int j=0;j<i;j++){
                sum+=L[i][j]*U[j][k];
            }
            U[i][k]=A[i][k]-sum;
        }
        //Calculate Lower Triangular matrix l
        for(int k=i;k<N;k++){
            if(i==k){
                L[i][i]=1; //Diagonal elements of L are 1
            } else{
                float sum=0.0;
                for(int j=0;j<i;j++){
                    sum+=L[k][j]*U[j][i];
                }
                L[k][i]=(A[k][i]-sum)/U[i][i];
            }
        }
    }
}

void printMatrix(float matrix[N][N]){
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%f",matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    float A[N][N]={{2,3,1},{4,5,2},{6,7,3}};
    float L[N][N]={0}, U[N][N]={0};

    printf("Matrix A:\n");
    printMatrix(A);

    luDecomposition(A,L,U);

    printf("\nLower Triangular Matrix L:\n");
    printMatrix(L);

    printf("\nUpper Triangular Matrix U:\n");
    printMatrix(U);

    return 0;
}