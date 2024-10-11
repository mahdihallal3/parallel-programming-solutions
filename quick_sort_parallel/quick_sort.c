#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void swap(float *x, float *y) {
    float tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(float *array, int low, int high) {
    float pivot = array[high]; // last element as pivot
    int i = low - 1;           // index of smaller element
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void parallel_quicksort(float *array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);

        #pragma omp task
        parallel_quicksort(array, low, pivot - 1);
        
        #pragma omp task
        parallel_quicksort(array, pivot + 1, high);
    }
}

int verify_sorted (float *A, int n) {
   int i;

   for (i = 0; i < n-1; i++)
      if (A[i] > A[i+1]) return 0;
   return 1;
}

int main() {
    int n = 1000000; // Number of elements to sort
    float *A = (float *)malloc(n * sizeof(float)); // Allocate memory for the array

    // Initialize array with random values
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100000;
    }
    
    struct timeval stop, start;
   
    gettimeofday(&start, NULL);
    
    omp_set_num_threads(7);
    // Start parallel region
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallel_quicksort(A, 0, n - 1); // Sort the array
        }
    }
    
    gettimeofday(&stop,NULL);

    if (verify_sorted (A, n)) {
    printf ("Elements are sorted\n");
    printf("\nTime: %lu", (stop.tv_sec-start.tv_sec)*1000000 + stop.tv_usec - start.tv_usec);
   }
   
   else {
    printf ("ERROR: Elements are NOT sorted\n");
   }
    
    free(A); // Free allocated memory
    return 0;
}




