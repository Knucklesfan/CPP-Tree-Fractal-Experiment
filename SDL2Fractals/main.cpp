
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <chrono>

//Screen dimension constants
const double Pi = 3.14159265358979323846264;
static int iterations = 2;
static int size = 2;

double Convert(float degree)
{
    return (degree * (Pi / 180));
}

void drawFractal(SDL_Renderer* renderer, Uint16 x1, Uint16 y1, float angle, int depth, Uint8 size, float factor) {
    if (depth > 0) {
        Uint16 x2 = x1 + cos(Convert(angle)) * depth * size * factor;
        Uint16 y2 = y1 + sin(Convert(angle)) * depth * size * factor;
        SDL_SetRenderDrawColor(renderer, rand() % 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        drawFractal(renderer, x2, y2, angle, depth - 2, size, factor);
        drawFractal(renderer, x2, y2, angle - 35, depth - 2, size, factor);
        drawFractal(renderer, x2, y2, angle + 35, depth - 2, size, factor);
    }
}
int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            int x = 0;
            SDL_SetWindowTitle(window, "Fractal Demo");
            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                auto start = std::chrono::system_clock::now();
                drawFractal(renderer, 640, 700, -90.0f, iterations, size, 1.0f);
                auto end = std::chrono::system_clock::now();
                printf("%i\n", iterations);
                SDL_RenderPresent(renderer);
                x++;
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                    case SDL_QUIT:
                        done = SDL_TRUE;
                        break;
                    case SDL_KEYUP:
                        switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            iterations--;
                            break;

                        case SDLK_RIGHT:
                            iterations++;
                            break;
                        case SDLK_UP:
                            size--;
                            break;

                        case SDLK_DOWN:
                            size++;
                            break;

                        }
                    }

                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}