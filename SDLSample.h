#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./sdl-2.0.7/include/SDL.h"
#include"./sdl-2.0.7/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#ifdef __cplusplus
extern "C"
#endif

void DrawString(SDL_Surface *screen, int x, int y, const char *text,
	SDL_Surface *charset);

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor);