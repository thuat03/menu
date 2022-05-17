#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>

using namespace std;
//The window, renderer and font
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

#include"const.h"
#include"LButtonSprite.h"

//Mouse button sprites

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

#include"LTexture.h"
#include"LButton.h"

//Button objects
LButton gButtons_1;

LTexture gCurrentTexture;

#include"Render.h"

int main(int argc, char* args[]) {

	init();
	
	loadMedia();

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			gButtons_1.handleEvent(&e);
		}
		SDL_SetRenderDrawColor(gRenderer, LIME_COLOR.r, LIME_COLOR.g, LIME_COLOR.b, LIME_COLOR.a);
		
		SDL_RenderClear(gRenderer);

		gButtons_1.updateStatus();
		gButtons_1.render();

		gCurrentTexture.loadFromRenderedText("Welcome to 2048!", ORANGE_COLOR);
		gCurrentTexture.render(125, 50);


		//Ấn vào exit để thoát 

		SDL_RenderPresent(gRenderer);
	}

	close();
	return 0;
}