//
// this program demonstrates interpolated Gourad 
// shading on a square. it is usually used on 
// triangles but i expanded it to a parallelogram. 
//
// in hindsight, this was a dumb idea. it doesnt 
// work the way i had anticipated
//

// my rendering library of choice, its easy to use
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <iostream>
#include <core.h>
#include <triangles.h>
#include <sdl_core.h>

#define SCREEN_SIZE 600

using namespace std;

// intensity is from 0 to 255
void draw_lines_to(SDL_Surface* s, int x, int y, int intensity);

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    auto* s = SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    xy_pair p[4] = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}; // pt coords
    float_t c[4] = { 0.0,       0.0,        1.0,        1.0 }; // color intensities
    xy_pair current_point = {0.0, 0.0};
    int mouse_x, mouse_y;

    bool running     = true;

    sdl_event_map_t sdl_event_map;

    // capture the mouse position
    sdl_event_map.insert({ 
        SDL_MOUSEMOTION,
        [
                &current_point, 
                &mouse_x, 
                &mouse_y
        ](void* ptr) {

            auto* mouse_motion = reinterpret_cast<SDL_MouseMotionEvent*>(ptr);

            //cout 
            //    << "mouse motion callback [" 
            //    << mouse_motion->x << " : " 
            //    << mouse_motion->y << "]\n";

            // calculate the mapped coordinates
            float_t x = float_t(mouse_motion->x) / SCREEN_SIZE;
            float_t y = float_t(mouse_motion->y) / SCREEN_SIZE;
            mouse_x = mouse_motion->x;
            mouse_y = mouse_motion->y;

            current_point = { x, y }; 
        }
    });

    // capture quit condition
    sdl_event_map.insert({ 
        SDL_KEYDOWN,
        [&running](void* ptr) {
            auto* key_event = reinterpret_cast<SDL_KeyboardEvent*>(ptr);

            //cout << "keydown callback" << endl;

            if(key_event->keysym.sym == SDLK_ESCAPE)
                running = false;
        }
    });

    while(running) {
        sdl_evaluate_events(sdl_event_map);

        float_t final_intensity = 0.0;

        final_intensity = 
            c[0]*(size(current_point, p[1], p[2]) + size(current_point, p[2], p[3])) + 
            c[1]*(size(current_point, p[0], p[3]) + size(current_point, p[2], p[3])) + 
            c[2]*(size(current_point, p[0], p[3]) + size(current_point, p[0], p[1])) + 
            c[3]*(size(current_point, p[0], p[1]) + size(current_point, p[1], p[2]));

        cout << "final intensity: " << final_intensity/2.0 << endl;

        {
            final_intensity /= 2.0;
            SDL_FillRect(s, NULL, 0); // clear the screen

            SDL_Rect r;
            r.x = 0; r.y = 0;
            r.w = SCREEN_SIZE;
            r.h = SCREEN_SIZE;

            int rgbv = final_intensity*255;

            SDL_FillRect(s, &r, SDL_MapRGB(s->format, rgbv, rgbv, rgbv));
            SDL_Flip(s);
        }

        SDL_Delay(25);
    }

    SDL_Quit();

    return 0;
}

void draw_lines_to(SDL_Surface* s, int x, int y, int intensity) {

    // blank the screen
    SDL_FillRect(s, NULL, 0);

    lineRGBA(s, 0, 0, x, y, intensity, intensity, intensity, 255);
    lineRGBA(s, SCREEN_SIZE-1, 0, x, y, intensity, intensity, intensity, 255);
    lineRGBA(s, 0, SCREEN_SIZE-1, x, y, intensity, intensity, intensity, 255);
    lineRGBA(s, SCREEN_SIZE-1, SCREEN_SIZE-1, x, y, intensity, intensity, intensity, 255);

    SDL_Flip(s);
}
