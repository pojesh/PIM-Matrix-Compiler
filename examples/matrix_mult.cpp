#include <iostream>

// Matrix dimensions
const int N = 16;

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
    int A[N][N] = {0};
    int B[N][N] = {0};
    int C[N][N] = {0};
    
    // Initialize matrices with some values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j + 1;
        }
    }
    
    // Perform matrix multiplication
    matrixMultiply(A, B, C);
    
    // Print result (just a small portion to avoid overwhelming output)
    std::cout << "Result matrix C (showing top-left 4x4 corner):" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << C[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    return 0;
}