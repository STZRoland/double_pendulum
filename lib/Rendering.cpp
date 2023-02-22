#include "Rendering.h"


namespace Rendering
{
    
    void renderPendulum(SDL_Renderer* renderer, PendulumPhysics::Pendulum pendulum, int x_offset, int y_offset, SDL_Color color)
    {
        // Get coordinates of pendulum
        auto[x, y] = pendulum.getCoordinates();

        // Draw pendulum
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x_offset, y_offset, x+x_offset, y+y_offset);
        DrawFilledCircle(renderer, x+x_offset, y+y_offset, pendulum.mass);
    }


    int DrawFilledCircle(SDL_Renderer * renderer, int x, int y, int radius)
    {
        // https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c

        int offsetx, offsety, d;
        int status;

        offsetx = 0;
        offsety = radius;
        d = radius -1;
        status = 0;

        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                        x + offsety, y + offsetx);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                        x + offsetx, y + offsety);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                        x + offsetx, y - offsety);
            status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                        x + offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2*offsetx) {
                d -= 2*offsetx + 1;
                offsetx +=1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }

        return status;
    }


    Trace::Trace(int n_frames, SDL_Color color)
    {
        this->n_frames = n_frames;
        this->color = color;
    }

    void Trace::addCoordinate(std::tuple<double, double> coordinate, int x_offset, int y_offset)
    {
        coordinate = std::make_tuple(std::get<0>(coordinate) + x_offset, std::get<1>(coordinate) + y_offset);
        coordinates.push_front(coordinate);
        if (coordinates.size() > n_frames)
        {
            coordinates.pop_back();
        }
    }

    void Trace::render(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        for (int i = 0; i < coordinates.size(); i++)
        {
            auto[x, y] = coordinates[i];
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a - (color.a / n_frames) * i);
            // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}