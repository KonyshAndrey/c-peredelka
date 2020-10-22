#include <SDL.h>
#include <iostream>
#include <functional>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 640;

bool init(std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>& win, std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>& ren)
{
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
    win = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(SDL_CreateWindow("Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
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

    int r = 0;
    while (r < 1 || r > 10)
    {
        std::cout << "Enter radius of a circle (1 <= r <= 10): ";
        std::cin >> r;
    }

    if (!init(win, ren))
    {
        SDL_Quit;
        return 1;
    }

    SDL_SetRenderDrawColor(ren.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(ren.get());
    SDL_SetRenderDrawColor(ren.get(), 0x00, 0x00, 0x00, 0x00);

    int x = 0;
    int X1 = 320;
    int Y1 = 320;
    int y = r * 30;
    int delta = 1 - 2 * r * 30;
    int error = 0;
    while (y >= 0)
    {
        SDL_RenderDrawPoint(ren.get(), X1 + x, Y1 + y);
        SDL_RenderDrawPoint(ren.get(), X1 + x, Y1 - y);
        SDL_RenderDrawPoint(ren.get(), X1 - x, Y1 + y);
        SDL_RenderDrawPoint(ren.get(), X1 - x, Y1 - y);
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0))
        {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0))
        {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }

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