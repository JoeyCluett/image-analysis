#pragma once

#include <SDL/SDL.h>
#include "core.h"
#include <functional>
#include <map>

// i use sdl instead of SDL anywhere i create a function that wraps SDL functionality

typedef std::map<uint8_t, std::function<void(void*)>> sdl_event_map_t;

void sdl_evaluate_events(const sdl_event_map_t& event_map);

