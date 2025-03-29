#include <iostream>

// Matrix dimensions
const int N = 3;

// Matrix multiplication function
void matrixMultiply(int A[][N], int B[][N], int C[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;  // Initialize result element
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Example matrices
    int A[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int B[N][N] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    
    int C[N][N] = {0};
    
    // Perform matrix multiplication
    matrixMultiply(A, B, C);
    
    // Print result
    std::cout << "Result matrix C:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}