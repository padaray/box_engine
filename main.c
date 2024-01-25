#include <stdio.h>
#include <SDL2/SDL.h>
 
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
int window_size_w = 800;
int window_size_h = 600; 

void exit_window() {
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

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
    int slide_speed = 4;

    bool is_jumping = false;
    int jump_height = 200;
    int jump_distance = 0;
    int jump_speed = 4;

    float gravity = 0.5;
    float fall_speed = 0;
    /*---------------------------------*/
    SDL_Event event;
 
    while (1)
    {
        SDL_FillRect(surface, &rec, SDL_MapRGB(surface->format, 0, 0, 0));


        /*---------------重力加速度---------------*/
        if(is_jumping) {

            //跳高限制
            rec.y -= jump_speed;
            jump_distance += jump_speed;
            if(jump_distance >= jump_height || rec.y <= 0) {
                is_jumping = false;
                jump_distance = 0;
                fall_speed = 0;
            }

        } else {
            if (rec.y < ground_y) {
                fall_speed += gravity;
                rec.y += fall_speed;
            } else {
                fall_speed = 0;
                rec.y = ground_y; // 限制到地面
            }
        } 
        /*---------------------------------------*/



        /*-----------------滑行速度-----------------*/
        if(rec.x > (window_size_w - rec.w) && direc_flag){
            direc_flag = false;
        }else if (rec.x < 0 && !direc_flag){
            direc_flag = true;
        }

        rec.x += (direc_flag ? slide_speed : -slide_speed);
        /*-----------------------------------------*/
        
 
        SDL_FillRect(surface, &rec, SDL_MapRGB(surface->format, 135, 206, 250));
 
        SDL_UpdateWindowSurface(window);
        SDL_Delay((1.0 / 240) * 1000);

        /*---------------按鍵管理---------------*/
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {

                    // ESC : 關閉視窗
                    case SDLK_ESCAPE:
                        exit_window();
                        break;

                    // SPACE : 跳躍控制
                    case SDLK_SPACE:
                        // if (!is_jumping && rec.y == ground_y) {
                        //     is_jumping = true;
                        // }
                        is_jumping = true;
                        break;
                    
                    default:
                        break;
                }
            }
        }
        /*--------------------------------------*/
    }

    exit_window();
 
    return 0;
}

