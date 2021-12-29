#include <iostream>
#include <fstream>
#include <cstring>

#include <SDL.h>
#include <json.hpp>

nlohmann::json kAppSettings;

const char* ConvertStringToChars(std::string str) {
    return str.c_str();
}

void ReadJsonSettingsFile() {
    std::ifstream file("settings.json");
    kAppSettings = nlohmann::json::parse(file);
}

void PrintError(std::string errorMessage) {
    std::cout << errorMessage << " SDL_Error: " << SDL_GetError() << std::endl;
}

int main(int argv, char** args) {
    ReadJsonSettingsFile();

    SDL_Window* win = NULL;
    SDL_Surface* scrSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        PrintError("SDL could not initialize!");
    }
    else {
        win = SDL_CreateWindow(ConvertStringToChars(kAppSettings["win"]["title"]), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            kAppSettings["win"]["width"], kAppSettings["win"]["height"], SDL_WINDOW_SHOWN);

        if (win == NULL) {
            PrintError("Window could not be created!");
        }
        else {
            scrSurface = SDL_GetWindowSurface(win);
            SDL_FillRect(scrSurface, NULL, SDL_MapRGB(scrSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(win);
            SDL_Delay(2000);
            SDL_DestroyWindow(win);
            SDL_Quit();
        }
    }
    return 0;
}
