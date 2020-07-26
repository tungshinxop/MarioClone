#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include <string>
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Globals
SDL_Window* gWindow = NULL;
Texture2D* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Mix_Music* gMusic = NULL;

Uint32 gOldTime;    

//SDL_Texture* gTexture = NULL;

using namespace std;

int angle = 0;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void LoadMusic(string path);

void Render();
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();

int main(int argc, char* arg[])
{

    //Check if SDL was set up correctly
    if (InitSDL()) {
        //Set up the screen manager -Start with level 1 
        gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);

        gOldTime = SDL_GetTicks();

        //Load music
        LoadMusic("Music/Mario.ogg");

        //Play music
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(gMusic, -1);
        }

        //Flag to check if we wish to quit
        bool quit = false;

        //Gameloop
        while (!quit) {
            Render();
            //If quit == true exit the while loop and proceed to CloseSDL();
            quit = Update();
        }
    }
    //Close Window and free resources
    CloseSDL();

    return 0;
}

bool InitSDL() {
    if (TTF_Init() < 0) { 
        cout << "Error: " << TTF_GetError() << endl; 
        return false; 
    }

    //Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL did not initialise. Error: " << SDL_GetError();
        return false;
    }
    else {
        //Create the window
        gWindow = SDL_CreateWindow("Games Engine Creation",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        //Initialise renderer
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);


        //Initialise Mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            cout << "Mixer could not initialise. Error: " << Mix_GetError() << endl;    
            return false;
        }


        //if (gRenderer != NULL) {
        //    //Load the background texture

        //    gTexture = new Texture2D(gRenderer);


        //    if (!gTexture->LoadFromFile("Images/test.bmp")) {
        //        cout << "could not load file from texture." << endl;
        //        return false;
        //    }
        //    //Initialise PNG loading
        //    int imageFlags = IMG_INIT_PNG;
        //    if (!(IMG_Init(imageFlags) && imageFlags)) {
        //        cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
        //        return false;
        //    }
        //}
        //else
        //{
        //    cout << "Renderer was not initialise. Error " << SDL_GetError();
        //    return false;
        //}

        //Did we get created?
        if (gWindow == NULL) {
            //Nope
            cout << "Window was not created. Error: " << SDL_GetError();
            return false;
        }
    }

    return true;
}

void CloseSDL() {
    //Clear up the texture 
    delete gTexture;
    gTexture = NULL;

    //Destroy game screen manager 
    delete gameScreenManager;
    gameScreenManager = NULL;

    //Release the renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    //Release music 
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    //Release the window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystem
    IMG_Quit();
    SDL_Quit();

    //Quit ttf
    TTF_Quit();
}

bool Update() {
    //Get the new time
    Uint32 newTime = SDL_GetTicks();

    //Event handler
    SDL_Event e;

    SDL_PollEvent(&e);

    //Handle any events
    switch (e.type)
    {
        //Click the 'X' to quit
        case SDL_QUIT:
            return true;
            break;

        case SDL_KEYUP:
            switch (e.key.keysym.sym) {
                case SDLK_RETURN:
                    if (gameScreenManager->GetNextGameState() == CHOOSE_LEVEL_STATE) {
                        gameScreenManager->ChangeScreen(SCREEN_MENU);
                    }
                    else if(gameScreenManager->GetNextGameState() == GAME_STATE_LEVEL_1)
                    {
                        gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
                    }
                    else if(gameScreenManager->GetNextGameState() == GAME_STATE_LEVEL_2)
                    {
                        gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
                    }
                    else if(gameScreenManager->GetNextGameState() == EXIT_STATE)
                    {
                        return true;
                    }
                    break;
            }
            break;

        /*case SDL_MOUSEBUTTONDOWN:
            return true;
            break;*/
    }

    gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

    //Set the current time as old time
    gOldTime = newTime;

    return false;
}

void Render() {
    //Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    ////Call the render function in Texture2D class
    ////Responsible for the renderlocation and other parameters like position,flip ,angle,...
    //gTexture->Render(Vector2D(), SDL_FLIP_NONE);

    //Call render function in gamescreen manager
    gameScreenManager->Render();

    //Update the screen
    SDL_RenderPresent(gRenderer);
}


void LoadMusic(string path) {
    gMusic = Mix_LoadMUS(path.c_str());

    if (gMusic == NULL) {
        cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
    }
}
//SDL_Texture* LoadTextureFromFile(string path) {
//    //Remove the memory used for previous texture
//    FreeTexture();
//
//    SDL_Texture* pTexture = NULL;
//
//    //Load the surface
//    SDL_Surface* pSurface = IMG_Load(path.c_str()); 
//    if (pSurface != NULL) {
//        //Create the texture from the pixels on the surface 
//        pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
//        if (pTexture == NULL) {
//            cout << "Unable to create texture from surface. Error" << SDL_GetError() << endl;
//        }
//        else
//        {
//            //Remove the surface loaded now that we have the texture
//            SDL_FreeSurface(pSurface);
//        }
//    }
//    else
//    {
//        cout << "Unable to create texture from surface. Error " << IMG_GetError() << endl;
//    }
//
//    //Return the texture
//    return pTexture;
//}

//void FreeTexture() {
//    //Check if the texture exists before removing it
//    if (gTexture != NULL) {
//        SDL_DestroyTexture(gTexture);
//        gTexture = NULL;
//    }
//}