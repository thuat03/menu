#pragma once

void init()
{
	//Create window
	gWindow = SDL_CreateWindow("Demo menu with SDL_TTF", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create vsynced renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, WHITE_COLOR.a);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);

	//Initialize SDL_ttf
	TTF_Init();
}


void loadMedia()
{
	gFont = TTF_OpenFont("HARLOWSI.TTF", 40);

	//Load texture
	gButtons_1.set_texture("on-default.png", 0);
	gButtons_1.set_texture("on-triggered.png", 1);
	gButtons_1.set_texture("off-default.png", 2);
	gButtons_1.set_texture("off-triggered.png", 3);

		

	//Set buttons location
	gButtons_1.setPosition(50, 150);
}

void close()
{
	//Free loaded images
	gButtons_1.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	TTF_CloseFont(gFont);

	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}