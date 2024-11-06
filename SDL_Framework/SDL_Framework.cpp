// SDL_Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include "Graphics.h"

bool quit = false;

int main(int argc, char* args[])
{   // Initialize SDL subsystem
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not init, error: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "STL Advanced Framework\n";

    window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cerr << "Unable to create a window. SDL_Error: "
            << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Unable to get renderer. SDL_Error: "
            << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Colour red
    SDL_Event events = {};

    //main game loop
    while (!quit)
    {   //event polling loop, while there are events inside of out events variable
        while (SDL_PollEvent(&events))
        {   // Handle each and every event we want to look for
            switch (events.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        // Draw code below
        SDL_RenderFillRect(renderer, nullptr);
        SDL_RenderPresent(renderer);

        // Destroy renderer
        SDL_DestroyRenderer(renderer);
        //Destroy the window
        SDL_DestroyWindow(window);

        
    }
    // terminate SDL subsystems
    SDL_Quit();
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
//