#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

int main(int argc, char* argv[]) {

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load an image
    SDL_Surface* imageSurface = IMG_Load("../assets/test.png");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);

    // Load a sound
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* music = Mix_LoadMUS("../assets/default.mp3");

    Mix_VolumeMusic(MIX_MAX_VOLUME / 12);

    // Play the sound
    Mix_PlayMusic(music, -1);

    // Main loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the image
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);

        // Update the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
