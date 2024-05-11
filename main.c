#include <raylib.h>

#define T_K_MEANS_IMPL
#include "k_means.h"
#include <limits.h>

#define WIDTH  720
#define HEIGHT 540

#define N 500
#define DIM 2
#define K 6


int main(void) {

    InitWindow(WIDTH, HEIGHT, "km");
    SetTargetFPS(60);
    SetWindowMonitor(0);

    int data[(DIM+1) * N] = {0};
    int range[] = {WIDTH, HEIGHT};
    int centroids[K*DIM];
    Color colors[K];

    if (gen_data(data, N, DIM, range) < 0) return -1;
    print_data(data, N, DIM);

    if (gen_cents(centroids, K, DIM, range) < 0) return -1;
    print_cents(centroids, K, DIM);

    if (gen_colors(colors, K) < 0) return -1;

    int iteration = 0;
    k_means(data, N, centroids, K, DIM);

    while (!WindowShouldClose()) {
        if (iteration) {
            k_means(data, N, centroids, K, DIM);
            print_data(data, N, DIM);
        }

        BeginDrawing();
        ClearBackground(BLACK); 

        {
            draw_data(data, N, DIM, colors);
            draw_cents(centroids, K, DIM, colors);
        }

        EndDrawing();
        if (iteration) {
            k_means_adjust(data, N, centroids, K, DIM);
            print_cents(centroids, K, DIM);
        }

        if (IsKeyPressed(KEY_SPACE)) iteration = 1;
        else iteration = 0;

    }

    return 0;
}
