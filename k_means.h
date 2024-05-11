#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <raylib.h>

// gen rand data with 'dim' dimensions. dim+1 is the set the point belongs to. ex: for dim = 2, n = 2  -> arr = [x, y, set, x, y, set]
// range is an array with 'dim' points specifying the limit of random values. if range = [100, 200], x -- [0, 100] and y -- [0, 200]
int gen_data(int *arr, int n, int dim, int *range);
int gen_cents(int *arr, int n, int dim, int *range);

int print_data(int *arr, int n, int dim);
// colors is the color of each set
int draw_data(int *arr, int n, int dim, Color *colors);

int print_cents(int *arr, int n, int dim);
int draw_cents(int *arr, int n, int dim, Color *colors);

// set points' sets
int k_means(int *arr, int n, int *m, int k, int dim);
// get new centroids
int k_means_adjust(int *arr, int n, int *m, int k, int dim);

// generate random 'n' colors
int gen_colors(Color *colors, int n);


#ifdef T_K_MEANS_IMPL

int gen_data(int *arr, int n, int dim, int *range) {
    if (!arr) return -1;
    if (!range) return -1;

    srand(time(NULL));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < dim; j++){
            arr[j] = rand() % range[j];
        }
        arr[dim] = -1;
        arr += dim+1;
    }

    return 0;
}


int gen_cents(int *arr, int n, int dim, int *range) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < dim; j++) {
            arr[j] = rand() % range[j];
        }
        arr += dim;
    }

    return 0;
}


int print_cents(int *arr, int n, int dim) {
    printf("centroids:\n");
    for (int i = 0; i < n; i++) {
        printf("[");

        for (int j = 0; j < dim-1; j++) {
            printf("%d, ", arr[j]);
        }
        printf("%d]\n", arr[dim-1]);
        arr += dim;
    }

    return 0;

}


int draw_cents(int *arr, int n, int dim, Color *colors) {
    if (dim != 2) return -1;

    for (int i = 0; i < n; i++) {
        DrawCircle(arr[0], arr[1], 7.0f, colors[i]);
        arr += dim;
    }

    return 0;
}


int print_data(int *arr, int n, int dim) {
    printf("data:\n");
    for (int i = 0; i < n; i++) {
        printf("[");

        for (int j = 0; j < dim-1; j++) {
            printf("%d, ", arr[j]);
        }
        printf("%d | %d]\n", arr[dim-1], arr[dim]);
        arr += dim+1;
    }

    return 0;
}


int draw_data(int *arr, int n, int dim, Color *colors) {
    if (dim != 2) return -1;

    for (int i = 0; i < n; i++) {
        DrawCircle(arr[0], arr[1], 3.0f, colors[arr[dim]]);
        arr += dim+1;
    }

    return 0;
}


int k_means(int *arr, int n, int *m, int k, int dim) {
    for (int i = 0; i < n; i++) { // for each point
        int set_ix = -1;
        long min_d = LONG_MAX;
        int *m_t = m;

        for (int g = 0; g < k; g++) { // for each centroid
            long d = 0;
            for (int j = 0; j < dim; j++) { // for each dim
                d += (m_t[j] - arr[j])*(m_t[j] - arr[j]);
            }

            if (d < min_d) {
                min_d = d;
                set_ix = g;
            }

            m_t += dim;
        }

        arr[dim] = set_ix;
        arr += dim+1;
    }

    return 0;
}


int k_means_adjust(int *arr, int n, int *m, int k, int dim) {
    int *sum = calloc(k*dim, sizeof(*sum));
    int *sum_n = calloc(k, sizeof(*sum_n));

    for (int i = 0; i < n; i++) { // for each point
        int ix = arr[dim];
        for (int j = 0; j < dim; j++) { // for each dim
            sum[ix*dim + j] += arr[j];
        }
        sum_n[ix]++;
        arr += dim+1;
    }

    for (int g = 0; g < k; g++) {
        for (int j = 0; j < dim; j++) { // for each dim
            printf("sum: %d | sum_n: %d\n", sum[g*dim + j], sum_n[g]);
        }
    }

    for (int g = 0; g < k; g++) { // for each centroid
        for (int j = 0; j < dim; j++) { // for each dim
            m[j] = sum[j] / sum_n[g];
            printf("%d ", sum[j]);
        }
        m += dim;
        sum += dim;
    }

    return 0;
}


int gen_colors(Color *colors, int n) {
    if (!colors) return -1;

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        colors[i].r = rand() % 200 + 55;
        colors[i].g = rand() % 200 + 55;
        colors[i].b = rand() % 200 + 55;
        colors[i].a = 255;
    }

    return 0;
}

#endif
