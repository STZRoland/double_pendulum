#include "SDL.h"
#include "Pendulum.h"
#include <queue>


// Forward declarations
class SDL_Renderer;
class SDL_Color;


#ifndef RENDERING_H
#define RENDERING_H

namespace Rendering {
    void renderPendulum(SDL_Renderer* renderer, PendulumPhysics::Pendulum pendulum, int x_offset, int y_offset, SDL_Color color);
    int DrawFilledCircle(SDL_Renderer * renderer, int x, int y, int radius);

    class Trace {
    int n_frames;
    SDL_Color color;
    std::deque<std::tuple<double, double>> coordinates;

    public:
        Trace(int n_frames, SDL_Color color);
        void addCoordinate(std::tuple<double, double> coordinate, int x_offset, int y_offset);
        void render(SDL_Renderer* renderer);
    };
}

#endif