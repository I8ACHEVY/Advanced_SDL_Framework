// OpenGL : Kyle Bowman 01/06/2025
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