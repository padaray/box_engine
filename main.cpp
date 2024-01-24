#include <SDL2/SDL.h>
 
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
int window_size_w = 800;
int window_size_h = 600; 
int main(int args, char *argv[])
{
    
    /*------------初始化視窗------------*/
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Test Windows", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_w, window_size_h, SDL_WINDOW_SHOWN);
    if (!window)
        return -1;
    surface = SDL_GetWindowSurface(window);
    if (!surface)
        return -2;
    /*---------------------------------*/


    /*------------初始化方塊------------*/
    SDL_Rect rec;
    rec.x = 10;
    rec.y = 570;
    rec.w = 30;
    rec.h = 30;
    int ground_y = 570;
    bool direc_flag = true; //true = right

    bool is_jumping = false;
    int jump_height = 100;

    int gravity = 2;
    /*---------------------------------*/
    SDL_Event event;
 
    while (1)
    {
        SDL_FillRect(surface, &rec, SDL_MapRGB(surface->format, 0, 0, 0));


        if(is_jumping) {
            rec.y -= 6;
            if(rec.y <= ground_y - jump_height) {
                is_jumping = false;
            }
        } else {
            if (rec.y < ground_y) {
                rec.y += gravity;
            } else {
                rec.y = ground_y; // 限制到地面
            }
        }

        if(rec.x > (window_size_w - rec.w) && direc_flag){
            direc_flag = false;
        }else if (rec.x < 0 && !direc_flag){
            direc_flag = true;
        }

        rec.x += (direc_flag ? 8 : -8);
        
 
        SDL_FillRect(surface, &rec, SDL_MapRGB(surface->format, 135, 206, 250));
 
        SDL_UpdateWindowSurface(window);
        SDL_Delay((1.0 / 60) * 1000);

        /*---------------按鍵管理---------------*/
        while (SDL_PollEvent(&event)) {
            //關閉視窗
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                goto exit_window;
            }
             //跳躍控制
            if (!is_jumping && rec.y == 570 && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                is_jumping = true;
            }
        }
        
        /*--------------------------------------*/
    }

exit_window:
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}

