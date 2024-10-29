
#include "Playable.h"

void Playable::setup(System* sys)
{
    sys_ = sys;
    menu_ = nullptr;
    state_ = MENU;

}

void Playable::loop()
{
    switch (state_)
    {
        case MENU:
            if (menu_ == nullptr)
            {
                state_ = GAME_INIT;
                return;
            }
            if(menu_->handle())
                state_ = GAME_INIT;
            menu_->render();
            break;

        case GAME_INIT:
            game_init();
            state_ = PLAY;
            break;

        case PLAY:
            game();
            break;

        default:
            break;
    }
}