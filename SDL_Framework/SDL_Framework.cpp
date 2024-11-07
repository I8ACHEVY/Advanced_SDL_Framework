// SDL_Framework.cpp : Kyle Bowman 11-04-2024
//

#include "GameManager.h"

using SDL_Framework::GameManager;

int main(int argc, char* args[])
{   
    GameManager* game = GameManager::Instance();

    game->Run();

    GameManager::Release();
    game = nullptr;

    return 0;
}