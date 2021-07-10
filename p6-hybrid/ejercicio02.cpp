#include <iostream>
#include <omp.h>

// Mac:  g++ -Xpreprocessor -fopenmp ejercicio2.cpp -o ejercicio2 -lomp
// Linux: g++ -fopenmp ejercicio2.cpp -o ejercicio2

void calculo_a(double A [], int n){
    /* O(n^2) */
    for (int i =0; i < n; i ++) { 
        int sum = 0;
        for (int j =0; j < n; j ++) { 
            sum += j;
        }
        A [i] = sum;
    }
}

void calculo_b(double B [], int n){
    /* O(n^2) */
    for (int i =0; i < n; i ++) { 
        int sum = 0;
        for (int j =0; j < n; j ++) { 
            sum += i;
        }
        B [i] = sum;
    }
}

void calculo_c(double C [], int n){
    /* O(n^2) */
    for (int i =0; i < n; i ++) { 
        int sum = 0;
        for (int j =0; j < n; j ++) { 
            sum += j+i;
        }
        C [i] = sum;
    }
}

double OpVec ( double A [] , double B [] , double C [] , int n ){
    int i , j;
    double s1 , s2 , a , res ;

    calculo_a (A ,n ); /* funcion calculo a */
    calculo_b (B ,n ); /* funcion calculo b */
    calculo_c (C ,n ); /* funcion calculo c */

#pragma omp task firstprivate(i,j,s1,A,B) 
{
    for (i =0; i < n; i ++) { /* primer bucle for */
        s1 =0;
        for (j =0; j < n; j ++) s1 += A[i ]* B[i ];
        for (j =0; j < n; j ++) A[i ]*= s1 ;
    }
} // end omp task

    for (i =0; i < n; i ++) { /* segundo bucle for */
        s2 =0;
        for (j =0; j < n; j ++) s2 += B[i ]* C[i ];
        for (j =0; j < n; j ++) C[i ]*= s2 ;
    }

#pragma omp taskwait
    /* calculo final */
    a= s1 / s2 ;
    res =0;
    for (i =0; i < n; i ++) res += a* C[i ];

    return res ;
}

int main() {

    int n = 10000;
    double A [n];
    double B [n];
    double C [n];

    /* Inicializar vectores */
    for(int i = 0; i < n; i++){
        A[i] = 1; B[i] = 2; C[i] = 3;
    }

    /* Llama a la función */
#pragma omp parallel 
{
    OpVec(A, B, C, n);
}

}