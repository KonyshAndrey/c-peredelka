#include <SDL.h>
#include <iostream>
#include <cmath>
#include <functional>

#define PI 3.14159265

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 480;
int one_in_pixels = 60;

bool init(std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>& win, std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>& ren)
{
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
    win = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(SDL_CreateWindow("Sinc(x)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    if (win.get() == nullptr)
    {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        ok = false;
    }

    ren = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (ren.get() == nullptr)
    {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
        ok = false;
    }
    return ok;
}

int main(int arhc, char** argv)
{
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> win;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> ren;
    if (!init(win, ren))
    {
        SDL_Quit;
        return 1;
    }

    SDL_SetRenderDrawColor(ren.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(ren.get());
    SDL_SetRenderDrawColor(ren.get(), 0x00, 0x00, 0x00, 0x00);

    for (int i = 0; i <= SCREEN_WIDTH; i++)
        if (i - SCREEN_WIDTH / 2 == 0)
            SDL_RenderDrawPoint(ren.get(), i, SCREEN_HEIGHT / 2 - one_in_pixels);
        else
            SDL_RenderDrawPoint(ren.get(), i, SCREEN_HEIGHT / 2 - sin(((double)i - SCREEN_WIDTH / 2) / one_in_pixels) / (((double)i - SCREEN_WIDTH / 2) / one_in_pixels) * one_in_pixels);

    for (double i = 0; i <= SCREEN_WIDTH; i += one_in_pixels)
        SDL_RenderDrawLine(ren.get(), i, SCREEN_HEIGHT / 2 - 5, i, SCREEN_HEIGHT / 2 + 5);

    SDL_RenderDrawLine(ren.get(), 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(ren.get());
    bool _quit = false;
    SDL_Event e;
    while (!_quit)
    {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                _quit = true;
        SDL_Delay(10);
    }
    SDL_Quit;
    return 0;
}
