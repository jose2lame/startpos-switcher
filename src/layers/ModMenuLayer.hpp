#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <gd.h>
#include <matdash.hpp>

USING_NS_CC;

using namespace gd;

class ModMenuLayer : MenuLayer {
public:
    void onMoreGames(CCObject* obj);
};

void ModMenuLayer::onMoreGames(CCObject* obj) {
    matdash::orig<&ModMenuLayer::onMoreGames>(this, obj);

    static auto counter = 0;

    if (counter == 4) {
        counter = 0;
        MessageBox(
            NULL, 
            TEXT("/ / lesaparamonov"), 
            TEXT("Easter egg"), 
            MB_OK
        );
    }

    counter++;
}