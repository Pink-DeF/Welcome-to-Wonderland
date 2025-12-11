#include "../mainMenu.h"

void MainMenuScene::draw()
{
    SDL_SetRenderViewport(renderer, NULL);
    // _wallpap.draw();

    for (auto i: _buttons){ i.draw(); }
}
MainMenuScene::MainMenuScene(){}

SDL_AppResult MainMenuScene::iterate()
{
    draw();

    return SDL_APP_CONTINUE;
}

SDL_AppResult MainMenuScene::click(SDL_MouseButtonEvent& button)
{
    if(_buttons[0].touch(button.x, button.y)){ config.newGame(); }
    if(_buttons[1].touch(button.x, button.y)){ config.doStart(); }
    else if(_buttons[2].touch(button.x, button.y)){ return SDL_APP_SUCCESS; }

    return SDL_APP_CONTINUE;
}