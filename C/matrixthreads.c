#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define MAX_THREADS 16

typedef struct {
    double** a;
    double** b;
    double** result;
    int size;
    int start_row;
    int end_row;
} ThreadData;

double** allocateMatrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    if (!matrix) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int I = 0; I < size; I++) {
        matrix[I] = (double*)malloc(size * sizeof(double));
        if (!matrix[I]) {
            perror("Memory allocation failed");
            for (int III = 0; III < I; III++) {
                free(matrix[III]);
            }
            free(matrix);
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

void populate(double** matrix, int size) {
    for (int I = 0; I < size; I++) {
        for (int II = 0; II < size; II++) {
            matrix[I][II] = (double)(rand() % 21 - 10);
        }
    }
}

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int I = data->start_row; I < data->end_row; I++) {
        for (int II = 0; II < data->size; II++) {
            double sum = 0.0;
            for (int III = 0; III < data->size; III++) {
                sum += data->a[I][III] * data->b[III][II];
            }
            data->result[I][II] = sum;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);
    srand(time(NULL));

    double** a = allocateMatrix(size);
    double** b = allocateMatrix(size);
    double** result = allocateMatrix(size);

    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];

    int num_threads = (size < MAX_THREADS) ? size : MAX_THREADS;
    int rows_per_thread = ceil((double)size / num_threads);

    clock_t start_time = clock();

    for (int I = 0; I < num_threads; I++) {
        threadData[I].a = a;
        threadData[I].b = b;
        threadData[I].result = result;
        threadData[I].size = size;
        threadData[I].start_row = I * rows_per_thread;
        threadData[I].end_row = (I + 1) * rows_per_thread;
        if (threadData[I].end_row > size) threadData[I].end_row = size;

        pthread_create(&threads[I], NULL, multiply, &threadData[I]);
    }

    for (int I = 0; I < num_threads; I++) {
        pthread_join(threads[I], NULL);
    }

    clock_t end_time = clock();

    printf("%f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    for (int I = 0; I < size; I++) {
        free(a[I]);
        free(b[I]);
        free(result[I]);
    }
    free(a);
    free(b);
    free(result);

    return 0;
}

