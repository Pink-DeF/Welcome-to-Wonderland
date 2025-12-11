#include "../jumpscare.h"

JumpscareScene::JumpscareScene(size_t ID) { _enemyID = ID; changeVisible(); }

void JumpscareScene::draw()
{
    if(timer == 0){ return; }
    SDL_SetRenderViewport(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, _frames[_enemyID].r, _frames[_enemyID].g, _frames[_enemyID].b, 255);
    SDL_RenderFillRect(renderer, &rend);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    timer--;
    SDL_Delay(15);
    draw();
}