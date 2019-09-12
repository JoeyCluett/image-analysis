//
// this program demonstrates interpolated Gouraud 
// shading on a square. it is usually used on 
// triangles but i expanded it to a parallelogram. 
//
// this is the modified guorad algorithm. it 
// actually just performs regular gouraud shading 
// on the two triangles that make up the square 
// which is the standard way to shade squares anyway
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

// doesnt matter what order the points are in
float_t get_color(
    float_t xf, float_t yf, 
    const xy_pair& a, const xy_pair& b, const xy_pair& c,
    float_t acolor, float_t bcolor, float_t ccolor);

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    auto* s = SDL_SetVideoMode(SCREEN_SIZE, SCREEN_SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    xy_pair p[4] = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}; // pt coords
    float_t c[4] = {0.0,        0.5,        1.0,        0.5 }; // color intensities
    
    // a bunch of stuff that is modified by the event loop

    bool running     = true;
    sdl_event_map_t sdl_event_map;

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

        SDL_FillRect(s, NULL, 0); // clear screen

        for(int j = 0; j < SCREEN_SIZE; j++) {
            for(int i = 0; i < SCREEN_SIZE; i++) {

                auto slope = float_t(j) / float_t(i);
                float_t mapped_x = float_t(i) / SCREEN_SIZE; 
                float_t mapped_y = float_t(j) / SCREEN_SIZE;

                float_t final_intensity;

                if(slope <= 1.0) {
                
                    final_intensity = 2.0 * get_color(
                        mapped_x, mapped_y,
                        p[0], p[1], p[2],
                        c[0], c[1], c[2]
                    );
                
                }
                else {
                    
                    final_intensity = 2.0 * get_color(
                        mapped_x, mapped_y,
                        p[0], p[2], p[3],
                        c[0], c[2], c[3]
                    );

                }

                //cout << "final intensity: " << final_intensity << endl;

                int rgbv = (final_intensity * 255);                

                SDL_Rect r;
                r.x = i; r.y = j;
                r.w = 1;
                r.h = 1;

                SDL_FillRect(s, &r, SDL_MapRGB(s->format, rgbv, rgbv, rgbv));

            }
        }

        SDL_Flip(s);
        SDL_Delay(25);
    }

    SDL_Quit();

    return 0;
}

float_t get_color(
        float_t xf, float_t yf, 
        const xy_pair& a, const xy_pair& b, const xy_pair& c, 
        float_t acolor, float_t bcolor, float_t ccolor) {

    // yay

    // the gouraud eqn really is this simple    
    float_t fcolor = 
        acolor*size({xf, yf}, b, c) +
        bcolor*size({xf, yf}, a, c) + 
        ccolor*size({xf, yf}, a, b);

    return fcolor;

}
