// Copyright (C) 2023  Ephir
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef STARTPOS_SWITCHER_SRC_LAYERS_PAUSE_H_
#define STARTPOS_SWITCHER_SRC_LAYERS_PAUSE_H_

#include <gd.h>
#include <matdash.hpp>

#include "play.h"
#include "../mods/mods.h"
#include "../switcher/switcher.h"

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