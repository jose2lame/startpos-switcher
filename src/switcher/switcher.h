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

#ifndef STARTPOS_SWITCHER_SRC_SWITCHER_H_
#define STARTPOS_SWITCHER_SRC_SWITCHER_H_

#include <cstddef>
#include <array>

#include <cocos2d.h>
#include <gd.h>

namespace switcher {

using StartPosInfo = std::vector<std::pair<gd::StartPosObject*,
                                 cocos2d::CCPoint> >;
extern StartPosInfo start_poses;
extern std::array<cocos2d::enumKeyCodes, 2> key_binds;
extern std::ptrdiff_t index;
extern cocos2d::CCLabelBMFont* text;
extern cocos2d::CCSprite* left_arrow;
extern cocos2d::CCSprite* right_arrow;
extern gd::CCMenuItemSpriteExtra* left_arrow_button;
extern gd::CCMenuItemSpriteExtra* right_arrow_button;
extern bool direction;
extern bool is_to_switch;
extern bool is_in_menu;
extern bool is_created;
void SwitchStartPos(gd::PlayLayer* game);
void UpdateIndex(bool increment);
struct Callbacks {
  void LeftArrowButton(cocos2d::CCObject* obj);
  void RightArrowButton(cocos2d::CCObject* obj);
};

} // namespace switcher

#endif // STARTPOS_SWITCHER_SRC_SWITCHER_H_