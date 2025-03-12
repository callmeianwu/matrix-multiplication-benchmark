#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int** generate_random_matrix(int N) {
    int** mat = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        mat[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 10;
        }
    }
    return mat;
}

void free_matrix(int** mat, int N) {
    for (int i = 0; i < N; i++) {
        free(mat[i]);
    }
    free(mat);
}

void matrix_multi_omp(int** A, int** B, int** C, int N) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }
    
    int N = atoi(argv[1]);
    srand((unsigned)time(NULL));

    int** A = generate_random_matrix(N);
    int** B = generate_random_matrix(N);
    int** C = generate_random_matrix(N);

    clock_t start = clock();
    matrix_multi_omp(A, B, C, N);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    // Print ONLY the numeric time so it fits in the CSV
    printf("%f\n", elapsed);

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}

