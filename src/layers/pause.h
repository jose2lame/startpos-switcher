#ifndef STARTPOS_SWITCHER_SRC_LAYERS_PAUSE_H_
#define STARTPOS_SWITCHER_SRC_LAYERS_PAUSE_H_

#include <gd.h>
#include <matdash.hpp>

#include "play.h"
#include "../mods.h"
#include "../switcher.h"

using namespace cocos2d;
using namespace gd;
class ModPauseLayer final {
 public:
  void KeyDown(cocos2d::enumKeyCodes key);
};
void ModPauseLayer::KeyDown(enumKeyCodes key) {
  auto play_layer = PlayLayer::get();
  matdash::orig<&ModPauseLayer::KeyDown>(this, key);
  if ((key == switcher::key_binds[0] || key == switcher::key_binds[1]) && 
      mods::is_toogled) {
    switcher::UpdateIndex(key == switcher::key_binds[1]);
    if (!mods::is_to_switch_on_death) switcher::SwitchStartPos(play_layer);
    else {
      switcher::direction = (key == switcher::key_binds[1]);
      switcher::is_to_switch = true;
    }
  }
}

#endif // STARTPOS_SWITCHER_SRC_LAYERS_PAUSE_H_