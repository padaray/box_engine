#include <stdio.h>
#include <SDL2/SDL.h>
 
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *surface = NULL;
int window_size_w = 800;
int window_size_h = 600; 

void exit_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int args, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    /*----------------設定視窗畫面----------------*/
    window = SDL_CreateWindow("Test Windows", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_w, window_size_h, SDL_WINDOW_SHOWN);
    if (!window)
        return -1;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        return -1;    
    /*------------------------------------------*/


    /*--------------初始化方塊--------------*/
    SDL_Rect rec;

    // 設置方塊大小
    rec.x = 10;
    rec.y = 570;
    rec.w = 30;
    rec.h = 30;

    int ground_y = 570;  // 地板位置
    bool direc_flag = true;  // true = right
    int slide_speed = 4;  // 方塊滑行速度

    bool is_jumping = false;  // 跳躍flag
    float jump_speed = 20;  //跳躍初速度
    float recent_js = 0;  //方塊速度
    float gravity = 0.5;  //重力加速度
    bool print_space = false;  // 是不是剛按下space

    /*---------------------------------*/

    SDL_Event event;


    while(1) {
        
        // 刷新背景顏色為黑色
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /*---------------重力加速度---------------*/
        if(is_jumping && print_space) {
            recent_js = jump_speed;
            rec.y -= recent_js;
            recent_js -= gravity;
            print_space = false;
            if(rec.y <= 0) {
                recent_js = 0;
            }
        } else if (is_jumping && rec.y >= 0) {
            rec.y -= recent_js;
            recent_js -= gravity;
            if (rec.y >= ground_y) {
                recent_js = 0;
                is_jumping = false;
                rec.y = ground_y;
            }
        } else if (is_jumping && rec.y < 0) {
            rec.y = 0;
            continue;
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

        // 刷新渲染器
        SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        SDL_RenderFillRect(renderer, &rec);  //更新方塊
        SDL_RenderPresent(renderer);
        SDL_Delay((1.0 / 240) * 1000);  //方塊更新頻率


        /*-----------------按鍵管理-----------------*/
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {

                    // ESC : 關閉視窗
                    case SDLK_ESCAPE:
                        exit_window();
                        break;
                                        
                    // SPACE : 跳躍控制
                    case SDLK_SPACE:
                        is_jumping = true;
                        print_space = true;
                        break;
                    
                    default:
                        break;
                }
            }
        }
        /*-----------------------------------------*/


    }

    exit_window();
    return 0;
}

