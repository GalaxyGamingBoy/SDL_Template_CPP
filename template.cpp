#include <iostream>
#include <fstream>
#include <cstring>

#include <SDL.h>
#include <json.hpp>

nlohmann::json kAppSettings;

SDL_Window* gWin = NULL;
SDL_Surface* gScrSurface = NULL;

const char* ConvertStringToChars(std::string str) {
    return str.c_str();
}

const char* CreateFilePath(std::string path, std::string fileName) {
    const char* SStartPath = ConvertStringToChars(path);
    char* startPath = strdup(SStartPath);
    const char* file = ConvertStringToChars(fileName);
    return strcat(startPath, file);
}

void ReadJsonSettingsFile() {
    std::ifstream file("settings.json");
    kAppSettings = nlohmann::json::parse(file);
}

void PrintError(std::string errorMessage) {
    std::cout << errorMessage << " SDL_Error: " << SDL_GetError() << std::endl;
}

SDL_Surface* loadSurface(std::string path, std::string fileName)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(CreateFilePath(path, fileName));
	if (loadedSurface == NULL)
	{
		PrintError("Unable to load image!");
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			PrintError("Unable to optimize image");
		}
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		PrintError("SDL could not initialize!");
		success = false;
	}
	else
	{
		gWin = SDL_CreateWindow(ConvertStringToChars(kAppSettings["win"]["title"]), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                kAppSettings["win"]["width"], kAppSettings["win"]["height"], SDL_WINDOW_SHOWN);
		if (gWin == NULL)
		{
			PrintError("Window could not be created!");
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWin);
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	//gImage = loadSurface(path);
	//if (gStretchedSurface == NULL)
	//{
	//	PrintError("Failed to load image!");
	//	success = false;
	//}

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argv, char** args) {
    ReadJsonSettingsFile();

    if (!init())
	{
		PrintError("Failed to initialize!");
	}
	else
	{
		if (!loadMedia())
		{
			PrintError("Failed to load media!");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_UpdateWindowSurface(gWin);
			}
		}
	}
	close();

	return 0;
}
