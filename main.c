#include <raylib.h>
#include <time.h>

// #define D_RADIUS 6
// #define K_RADIUS 5

#define T_K_MEANS_IMPL
#include "k_means.h"

#define WIDTH  120
#define HEIGHT 120
#define FPS 60

#define N 100
#define DIM 2
#define K 3


int reset(int *arr, int n, int *m, int k, int dim, int *range, Color *colors);

int main(void) {

    InitWindow(WIDTH, HEIGHT, "km");
    SetTargetFPS(FPS);
    SetWindowMonitor(0);

    int data[(DIM+1) * N] = {0};
    int range[] = {WIDTH, HEIGHT};

    int centroids[K*DIM];

    Color colors[K];

    srand(time(0));
    if (gen_data(data, N, DIM, range) < 0) return -1;
    // print_data(data, N, DIM);

    if (gen_cents(data, N, centroids, K, DIM) < 0) return -1;
    // print_cents(centroids, K, DIM);

    if (gen_colors(colors, K) < 0) return -1;

#ifdef INTERACTIVE
    int iteration = 0;
#else
    int iteration = 1;
#endif

    k_means(data, N, centroids, K, DIM);

    int eq = 0;

    while (!WindowShouldClose()) {
        if (iteration) {
            k_means(data, N, centroids, K, DIM);
//            print_data(data, N, DIM);
        }

        BeginDrawing();
        ClearBackground(BLACK); 

        {
            draw_data(data, N, DIM, colors);
            draw_cents(centroids, K, DIM, colors);
        }

        EndDrawing();
        if (iteration) {
            eq = k_means_adjust(data, N, centroids, K, DIM);
//           print_cents(centroids, K, DIM);
        }

#ifdef INTERACTIVE
        if (IsKeyPressed(KEY_SPACE)) iteration = 1;
        else iteration = 0;

        if (IsKeyPressed(KEY_W)) {
            reset(data, N, centroids, K, DIM, range, colors);
        }
#else
        if (eq) {
            reset(data, N, centroids, K, DIM, range, colors);
        }
#endif


    }

    return 0;
}


int reset(int *arr, int n, int *m, int k, int dim, int *range, Color *colors) {
    gen_data(arr, n, dim, range);
    gen_cents(arr, n, m, k, dim);
    gen_colors(colors, k);

    return 0;
}
