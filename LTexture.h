#pragma once

class LTexture {
private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

public:

	LTexture() {
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	~LTexture() {
		free();
	}

	void loadFromFile(string path) {
		free();

		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
	}

	void loadFromRenderedText(string textureText, SDL_Color textColor) {
		free();

		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		mWidth = textSurface->w;
		mHeight = textSurface->h;
		SDL_FreeSurface(textSurface);
	}

	void free() {
		if (mTexture != NULL) {
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
		}
	}

	void setColor(Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetTextureColorMod(mTexture, red, green, blue);
	}

	void setBlendMode(SDL_BlendMode blending) {
		SDL_SetTextureBlendMode(mTexture, blending);
	}

	void setAlpha(Uint8 alpha) {
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_Rect renderQuad = { x,y,mWidth,mHeight };
		if (clip != NULL) {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	}

	int getWidth() {
		return mWidth;
	}

	int getHeight() {
		return mHeight;
	}
};