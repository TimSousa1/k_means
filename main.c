#include <raylib.h>
#include <time.h>

// #define D_RADIUS 6
// #define K_RADIUS 5
#define MY_T_K_MEANS_SIZE_IMPL
typedef unsigned char size_d_tim_;

#define T_K_MEANS_IMPL
#include "k_means.h"

#define WIDTH  200
#define HEIGHT 200
#define FPS 60

#define N 1000
#define DIM 2
#define K 7


// colors is the color of each set
int draw_data(size_d_tim_ *arr, int *sets, int n, int dim, Color *colors);
int draw_cents(size_d_tim_ *arr, int n, int dim, Color *colors);
// generate random 'n' colors
int gen_colors(Color *colors, int n);
int reset(u_char *arr, int *sets, int n, u_char *m, int k, int dim, u_char *range, Color *colors);

int main(void) {

    InitWindow(WIDTH, HEIGHT, "km");
    SetTargetFPS(FPS);
    SetWindowMonitor(0);

    u_char data[N*DIM] = {0};
    u_char range[] = {WIDTH, HEIGHT};
    int sets[N] = {-1};

    u_char centroids[K*DIM];

    Color colors[K];

    srand(time(0));
    if (gen_data(data, N, DIM, range) < 0) return -1;
//    print_data(data, sets, N, DIM);

    if (gen_cents(data, N, centroids, K, DIM) < 0) return -1;
//    print_cents(centroids, K, DIM);

    if (gen_colors(colors, K) < 0) return -1;

#ifdef INTERACTIVE
    int iteration = 0;
#else
    int iteration = 1;
#endif

    k_means(data, sets, N, centroids, K, DIM);

    int eq = 0;

    while (!WindowShouldClose()) {
        if (iteration) {
            k_means(data, sets, N, centroids, K, DIM);
//            print_data(data, sets, N, DIM);
        }

        BeginDrawing();
        ClearBackground(BLACK); 

        {
            draw_data(data, sets, N, DIM, colors);
            draw_cents(centroids, K, DIM, colors);
        }

        EndDrawing();
        if (iteration) {
            eq = k_means_adjust(data, sets, N, centroids, K, DIM);
//           print_cents(centroids, K, DIM);
        }

#ifdef INTERACTIVE
        if (IsKeyPressed(KEY_SPACE)) iteration = 1;
        else iteration = 0;

        if (IsKeyPressed(KEY_W)) {
            reset(data, sets, N, centroids, K, DIM, range, colors);
        }
#else
        if (eq) {
            reset(data, sets, N, centroids, K, DIM, range, colors);
        }
#endif


    }

    return 0;
}


int reset(u_char *arr, int *sets, int n, u_char *m, int k, int dim, u_char *range, Color *colors) {
    gen_data(arr, n, dim, range);
    gen_cents(arr, n, m, k, dim);
    gen_colors(colors, k);

    for (int i = 0; i < n; i++) {
        sets[i] = -1;
    }

    return 0;
}


int draw_data(size_d_tim_ *arr, int *sets, int n, int dim, Color *colors) {
    if (dim != 2) return -1;

    for (int i = 0; i < n; i++) {
        DrawCircle(arr[0], arr[1], D_RADIUS, colors[sets[i]]);
        arr += dim;
    }

    return 0;
}


int draw_cents(size_d_tim_ *arr, int n, int dim, Color *colors) {
    if (dim != 2) return -1;

    for (int i = 0; i < n; i++) {
        DrawCircle(arr[0], arr[1], K_RADIUS, colors[i]);
        arr += dim;
    }

    return 0;
}


int gen_colors(Color *colors, int n) {
    if (!colors) return -1;

    for (int i = 0; i < n; i++) {
        colors[i].r = rand() % 200 + 55;
        colors[i].g = rand() % 200 + 55;
        colors[i].b = rand() % 200 + 55;
        colors[i].a = 255;
    }

    return 0;
}
