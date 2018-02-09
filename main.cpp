#include"all.h"
void renderfood(SDL_Renderer* renderer, SDL_Rect food) {
	SDL_SetRenderDrawColor(renderer,255, 0, 0, 1);
	SDL_RenderFillRect(renderer, &food);
}
void renderplayer(SDL_Renderer* renderer, SDL_Rect player, vector<int> tailX, vector<int> tailY,int x, int y, int taillen) {
	SDL_SetRenderDrawColor(renderer, 128, 0, 0, 1);
	for (int i = 0; i < taillen; i++) {
		player.x = tailX[i];
		player.y = tailY[i];
		SDL_RenderFillRect(renderer, &player);
	}
	player.x = x;
	player.y = y;
	SDL_RenderFillRect(renderer, &player);
}
bool collison(int foodx, int foody, int playerx, int playery) {
	if (playerx == foodx && playery == foody) {
			return true;
		}
	else
		return false;
}
pair<int,int> getfood(vector<int>tailx, vector<int>taily, int px, int py,int taillen) {
	srand(time(0));
	int	a =rand()%24;
	int	b =rand()%24;
		a *= 25;
		b *= 25;
		for (int i = 0; i < taillen; i++) {
			if ((a == tailx[i] && b == taily[i]) || (a == px && b == py)) {
				int	a = rand() % 24;
				int	b = rand() % 24;
				a *= 25;
				b *= 25;
			}
		}
	floc = make_pair(a,b);
	return floc;
}
void renderscore(SDL_Renderer* renderer,int taillen) {
sfont = TTF_OpenFont("ariblk.ttf", 12);
string s = to_string(taillen);
score = TTF_RenderText_Solid(sfont,(string("SCORE::")+s).c_str(),black);
SDL_Texture*sc = SDL_CreateTextureFromSurface(renderer, score);
srect.w=50;
srect.h=50;
srect.x=275;
srect.y=25;
SDL_RenderCopy(renderer, sc, NULL, &srect);
}
void rendergover(SDL_Renderer* renderer) {
	sfont = TTF_OpenFont("ariblk.ttf", 12);
	score = TTF_RenderText_Solid(sfont,(string("GAMEOVER")).c_str(), black);
	SDL_Texture*sc = SDL_CreateTextureFromSurface(renderer, score);
	srect.w = 200;
	srect.h = 200;
	srect.x = 200;
	srect.y = 200;
	SDL_RenderCopy(renderer, sc, NULL, &srect);
	SDL_RenderPresent(renderer);
}

void gameover(vector<int>tailx, vector<int>taily, int px, int py, int taillen) {
	for (int i = 0; i < taillen; i++) {
		if ((px == tailx[i] && py == taily[i])||(px<0||px>600||py<0||py>600)){
			go= true;
		}
	}
}
int main(int argc, char* argv[]) {
start:	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 625, 625, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0);
	Mix_Music *cap=Mix_LoadMUS("eat.mp3");
	Mix_Music *gov= Mix_LoadMUS("buzz.mp3");
	player.x = 300;
	player.y = 300;
	player.h = 25;
	player.w = 25;
	int taillen = 0;
	floc = getfood(tailx, taily, playerx, playery, taillen);
	food.x = floc.first;
	food.y = floc.second;
	food.h = 25;
	food.w = 25;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	string initialKey = "right";
	while(1){
		if (event.type == SDL_QUIT)
		{	
			exit(0);
		}
		while (SDL_PollEvent(&event) != 0)	{			
			if (event.type == SDL_KEYDOWN) {
				if (initialKey != "down" && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					initialKey = "up";
				}
				else if (initialKey != "right" && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					initialKey = "left";
				}
				else if (initialKey != "up" && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					initialKey = "down";
				}
				else if (initialKey != "left" && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					initialKey = "right";
				}
			}
		}
		oldx = playerx;
		oldy = playery;
			if (initialKey == "right"&& go==false) {
				player.x += 25;
			}
			else if (initialKey == "left"&& go == false) {
				player.x -= 25;
			}
			else if (initialKey == "down"&& go == false) {
				player.y += 25;
			}
			else if(initialKey == "up"&& go == false) {
				player.y -= 25;
			}
		int foodx = food.x;
		int foody = food.y;
		playerx = player.x;
		playery = player.y;	
		collide = collison(foodx, foody, playerx, playery);
		if (collide == true){
			Mix_PlayMusic(cap, 0);
			floc = getfood(tailx, taily, playerx, playery,taillen);
			food.x = floc.first;
			food.y = floc.second;
			taillen++;
			tailx.push_back(oldx);
			taily.push_back(oldy);
		}
		
		if (tailx.size()== taillen) {
			for (int i = 0; i < taillen-1; i++) {
					tailx[i] = tailx[i+1];
					taily[i] = taily[i+1];
			}
			if (taillen > 0) {
				tailx[taillen - 1] = oldx;
				taily[taillen- 1] = oldy;
			}
			gameover(tailx, taily, playerx, playery, taillen);
			if (go==true) {
				Mix_PlayMusic(gov, 0);
				rendergover(renderer);
					if (event.type == SDL_KEYDOWN) {
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
							tailx.clear();
							taily.clear();
							SDL_Quit();
							go = false;
							goto start;
						}
					}
					SDL_Delay(500);
				}
			}
		SDL_SetRenderDrawColor(renderer, 0, 128, 0, 1);
		SDL_RenderClear(renderer);
		renderplayer(renderer, player, tailx, taily, playerx, playery, taillen);
		renderfood(renderer,food);
		renderscore(renderer, taillen);
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	} 
	return 0;
	}

