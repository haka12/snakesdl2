#pragma once
#include<iostream>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<vector>
#include<SDL_ttf.h>
#include<time.h>
#include"SDL_mixer.h"
using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect player;
SDL_Event event;
SDL_Rect food;
SDL_Rect srect;
SDL_Color black = { 0,0,0,1 };
SDL_Surface* score;
TTF_Font *sfont;
int playerx = 0;
int playery = 0;
int oldx, oldy;
bool collide;
bool go = false;
pair <int, int> floc;
vector<int> tailx;
vector<int> taily;
