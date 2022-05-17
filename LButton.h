#pragma once
//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render();

	void set_texture(const string& str, const int& n);

	void free();

	LButtonSprite getStatus();

	bool getBool();

	void freeStatus() {
		mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	}
	void updateStatus() {
		if (mCurrentSprite == BUTTON_SPRITE_MOUSE_DOWN && on) {
			on = false;
			freeStatus();
		}
		if (mCurrentSprite == BUTTON_SPRITE_MOUSE_DOWN && !on) {
			on = true;
			freeStatus();
		}
	}

private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	//TTF current render
	SDL_Texture *gtexture[4];

	SDL_Rect rect;

	bool on;
};

LButtonSprite LButton::getStatus() {
	return mCurrentSprite;
}

SDL_Texture* loadTexture(string path) {

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	for (int i = 0; i < 4; i++) {
		gtexture[i] = NULL;
	}
	on = true;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
	rect = { x,y,BUTTON_WIDTH,BUTTON_HEIGHT };
}

void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

			}
		}
	}
}

void LButton::render()
{
	//Show current button sprite

	if (mCurrentSprite == BUTTON_SPRITE_MOUSE_OUT && on) {
		SDL_RenderCopy(gRenderer, gtexture[0], NULL, &rect);
	}

	if (mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION && on) {
		SDL_RenderCopy(gRenderer, gtexture[1], NULL, &rect);
	}

	if (mCurrentSprite == BUTTON_SPRITE_MOUSE_OUT && !on) {
		SDL_RenderCopy(gRenderer, gtexture[2], NULL, &rect);
	}

	if (mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION && !on) {
		SDL_RenderCopy(gRenderer, gtexture[3], NULL, &rect);
	}
}

void LButton::set_texture(const string& str, const int& n) {
	gtexture[n] = loadTexture(str);
}

void LButton::free() {
	for (int i = 0; i < 4; i++) {
		gtexture[i] = NULL;
	}
}