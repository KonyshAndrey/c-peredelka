#include <SDL.h>
#include <iostream>
#include <functional>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

bool init(std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>& win, std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>& ren)
{
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
    win = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(SDL_CreateWindow("House", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
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

    SDL_Rect rect = { 100, 240, 300, 200 };
    SDL_RenderDrawRect(ren.get(), &rect);

    rect = { 150, 330, 60, 110 };
    SDL_RenderDrawRect(ren.get(), &rect);
    SDL_RenderDrawLine(ren.get(), 200, 380, 200, 390);

    rect = { 300, 300, 60, 60 };
    SDL_RenderDrawRect(ren.get(), &rect);
    rect = { 330, 300, 30, 60 };
    SDL_RenderDrawRect(ren.get(), &rect);
    rect = { 330, 320, 30, 40 };
    SDL_RenderDrawRect(ren.get(), &rect);

    SDL_RenderDrawLine(ren.get(), 100, 240, 250, 100);
    SDL_RenderDrawLine(ren.get(), 250, 100, 400, 240);

    SDL_RenderDrawLine(ren.get(), 330, 240 - 65, 330, 100);
    SDL_RenderDrawLine(ren.get(), 370, 240 - 28, 370, 100);
    SDL_RenderDrawLine(ren.get(), 330, 100, 370, 100);

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
