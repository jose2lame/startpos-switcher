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

#ifndef STARTPOS_SWITCHER_SRC_LAYERS_MENU_H_
#define STARTPOS_SWITCHER_SRC_LAYERS_MENU_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <gd.h>
#include <matdash.hpp>

using namespace cocos2d;
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
    MessageBox(NULL, TEXT("/ / lesaparamonov"), TEXT("Easter egg"), MB_OK);
  }
  counter++;
}

#endif // STARTPOS_SWITCHER_SRC_LAYERS_MENU_H_