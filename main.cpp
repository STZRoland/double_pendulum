#include <iostream>
#include "lib/Pendulum.h"
#include "lib/Rendering.h"

#include "SDL.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const double FPS = 120;
const double FRAME_DELAY = 1000 / FPS;

const int X_OFFSET = SCREEN_WIDTH / 2;
const int Y_OFFSET = 100;

// Set up simulation parameters
double dt = 1 / double(FPS) * 10;
double GRAVITY = 9.8;
double FRICTION = 0.01;

int main() {
    // Set up the penduli
    double m1 = 15;
    double l1 = 200;
    double theta1 = 3.14 / 2;
    double omega1 = 0;
    PendulumPhysics::Pendulum p1(m1, l1, theta1, omega1);

    double m2 = 5;
    double l2 = 70;
    double theta2 = 3.14;
    double omega2 = 0;
    PendulumPhysics::Pendulum p2(m2, l2, theta2, omega2);

    PendulumPhysics::DoublePendulum dp(p1, p2, GRAVITY, FRICTION);

    // Define Rendering
    SDL_Color color1 = { 0, 0, 255, 255 };
    SDL_Color color2 = { 0, 255, 0, 255 };

    Rendering::Trace trace1(200, color1);
    Rendering::Trace trace2(200, color2);

    // Setup SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "SDL2Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    
    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to black (background will be rendered in this color)
    SDL_RenderClear(renderer);

    // Event loop
    bool quit = false;
    SDL_Event event;

    int i = 0;
    Uint32 frameStart;
    int frameTime;

    while (!quit)
    {
        frameStart = SDL_GetTicks();
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Simulation code here
        dp.update(dt);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        Rendering::renderPendulum(renderer, dp.p1, X_OFFSET, Y_OFFSET, color1);
        Rendering::renderPendulum(renderer, dp.p2, X_OFFSET + std::get<0>(dp.p1.getCoordinates()), 
            Y_OFFSET + std::get<1>(dp.p1.getCoordinates()), color2);
        
        trace1.addCoordinate(dp.getP1Coordinates(), X_OFFSET, Y_OFFSET);
        trace2.addCoordinate(dp.getP2Coordinates(), X_OFFSET, Y_OFFSET);

        trace1.render(renderer);
        trace2.render(renderer);

        SDL_RenderPresent(renderer);
        
        // Limit to FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }

        i++;
    }

    return 0;
}
