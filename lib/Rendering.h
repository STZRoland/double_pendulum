#include "SDL.h"
#include "Pendulum.h"


// Forward declarations
class SDL_Renderer;
class SDL_Color;


#ifndef RENDERING_H
#define RENDERING_H

namespace Rendering {
    void renderPendulum(SDL_Renderer* renderer, PendulumPhysics::Pendulum pendulum, int x_offset, int y_offset, SDL_Color color);
    int DrawFilledCircle(SDL_Renderer * renderer, int x, int y, int radius);
}

#endif