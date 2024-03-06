#include <SDL_image.h>
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int main() {
    IMG_Init(IMG_INIT_PNG);
    srand(time(NULL));
    int speed = 3;
    int ycords = 700;
    int xcords = 1000;
    SDL_bool shot = SDL_FALSE;
    SDL_bool dead = SDL_FALSE;
    int powery;
    int powerx;
    int deadcount = 0;
    int reward = 5;
    SDL_bool powered = SDL_FALSE;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xcords, ycords, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    powerx = (rand() % (xcords - 30));
    powery = (rand() % (ycords - 30));

    SDL_Rect player = { 0, 0, 50, 50 }; 
    SDL_Rect enemy = { 350, 250, 50, 50 };
    SDL_Rect projectile = { player.x + 20, player.y + 20, 10, 10 };
    SDL_Rect projectile1 = { player.x + 20, player.y + 20, 10, 10 };
    SDL_Rect projectile2 = { player.x + 20, player.y + 20, 10, 10 };
    SDL_Rect projectile3 = { player.x + 20, player.y + 20, 10, 10 };
    SDL_Rect powerup = { powerx, powery, 30, 30 };

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        if (state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
        }

        // background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear the window with the render color
        SDL_RenderClear(renderer);
        //player movement
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player);
        if (state[SDL_SCANCODE_D] && player.x + speed + 50 < xcords) {
            player.x += speed;
        }
        if (state[SDL_SCANCODE_A] && player.x - speed > 0) {
            player.x -= speed;
        }
        if (state[SDL_SCANCODE_W] && player.y - speed > 0) {
            player.y -= speed;
            if (shot != SDL_TRUE) {
                projectile.y -= speed;
            }
        }
        if (state[SDL_SCANCODE_S] && player.y + speed + 50 < ycords) {
            player.y += speed;
            if (shot != SDL_TRUE) {
                projectile.y += speed;
            }
            
        }
        SDL_Delay(1);
        //enemy
        if (dead != SDL_TRUE) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemy);
            if (player.x > enemy.x) {
                enemy.x += (speed - 1);
            }
            if (player.x < enemy.x) {
                enemy.x -= (speed - 1);
            }
            if (player.y < enemy.y) {
                enemy.y -= (speed - 1);
            }
            if (player.y > enemy.y) {
                enemy.y += (speed - 1);
            }
        }
        //enemy death
        if (dead == SDL_TRUE) {
            dead = SDL_FALSE;
            enemy.x = (xcords - 50);
            enemy.y = 325;
        }
        //enemy fighting
        if (enemy.y >= (player.y - 50) && enemy.y < (player.y + 50) && enemy.x >= (player.x -50) && enemy.x <= (player.x + 50)) {
            player.x = 10;
            player.y = 10;
        }
        //player fighting
        if (shot != SDL_TRUE) {
            projectile.x = (player.x + 50);
            projectile.y = (player.y + 15);
            projectile1.x = player.x + 20;
            projectile1.y = player.y + 20;
            projectile2.x = player.x + 20;
            projectile2.y = player.y + 20;
            projectile3.x = player.x + 20;
            projectile3.y = player.y + 20;
        }
        if (state[SDL_SCANCODE_F]) {
            shot = SDL_TRUE;
        }
        if (shot == SDL_TRUE) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &projectile);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &projectile1);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &projectile2);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &projectile3);


            projectile.x += 20;
            if (powered == SDL_TRUE) {
                projectile1.y += 20;
                projectile2.x -= 20;
                projectile3.y -= 20;
            }
            //registering an enemy
            if (projectile.y > enemy.y && projectile.y < (enemy.y + 50) && projectile.x > enemy.x && projectile.x < (enemy.x + 50)) {
                dead = SDL_TRUE;
                deadcount++;
            }
            if (projectile1.y > enemy.y && projectile1.y < (enemy.y + 50) && projectile1.x > enemy.x && projectile1.x < (enemy.x + 50)) {
                dead = SDL_TRUE;
                deadcount++;
            }
            if (projectile2.y > enemy.y && projectile2.y < (enemy.y + 50) && projectile2.x > enemy.x && projectile2.x < (enemy.x + 50)) {
                dead = SDL_TRUE;
                deadcount++;
            }
            if (projectile3.y > enemy.y && projectile3.y < (enemy.y + 50) && projectile3.x > enemy.x && projectile3.x < (enemy.x + 50)) {
                dead = SDL_TRUE;
                deadcount++;
            }

            if (dead == SDL_TRUE || projectile.x >= xcords && shot == SDL_TRUE) {

                shot = SDL_FALSE;
            }
        }       
        //powerup
        if (deadcount >= reward) {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(renderer, &powerup);
            if (player.y > (powerup.y - 51) && player.y < (powerup.y + 31) && player.x > (powerup.x - 50) && player.x < (powerup.x + 30)) {
                powerup.x = (rand() % (xcords - 50));
                powerup.y = (rand() % (ycords - 50));
                reward += 5;
                powered = SDL_TRUE;
                
            }
        }

        // Update the screen
        SDL_RenderPresent(renderer);

    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}