#undef isnan
#undef snprintf

#include "main.h"

#include <fstream>

#include <cocos2d.h>
#include <gdhm.hpp>
#include <nlohmann/json.hpp>

#include "../mods/mods.h"
#include "../switcher/switcher.h"

#define CHECKBOX(name, value, onActivate) \
    gdhm::gui::checkbox ( \
        gdhm::new_id, \
        name, \
        value, \
        nullptr, \
        onActivate, \
        "", \
        onActivate \
    )

using namespace cocos2d;
using nlohmann::json;
void GDHMHeader() {
  auto UpdateJson = []() {
    json j = {};
    std::fstream fs(".ephir-mods/startpos-switcher/data/settings.json", std::ios::in | std::ios::out);
    if (fs.is_open()) fs >> j;
    fs.close();
    fs.open(".ephir-mods/startpos-switcher/data/settings.json", std::ios::out | std::ios::trunc);
    if (fs.is_open()) {
      j["Toogle"] = mods::is_toogled;
      j["Use A/D Keybinds"] = mods::is_using_ad;
      j["Hide Interface"] = mods::is_hidden_interface;
      j["Switch On Death"] = mods::is_to_switch_on_death;
      j["Use Arrows"] = mods::is_used_arrows;
      fs << j;
    }
    fs.close();
  };
  auto SetKeybinds = [&UpdateJson]() {
    if (mods::is_using_ad) switcher::key_binds = {KEY_A, KEY_D};
    else switcher::key_binds = {KEY_Left, KEY_Right};
    UpdateJson();
  };
  auto OnToogle = [&UpdateJson]() {
    if (switcher::is_created) {
      if (switcher::is_in_menu == false) {
          switcher::text->setVisible(!(mods::is_hidden_interface) && mods::is_toogled && 
                                     !(switcher::start_poses.empty()));
          switcher::left_arrow_button->setVisible(
              !(mods::is_hidden_interface) &&
              mods::is_toogled && 
              !(switcher::start_poses.empty()) &&
              mods::is_used_arrows);
          switcher::right_arrow_button->setVisible(
              (!mods::is_hidden_interface) && 
              mods::is_toogled && 
              !(switcher::start_poses.empty()) && 
              mods::is_used_arrows);
      }
    }
    UpdateJson();
  };
  SetKeybinds();
  OnToogle();
  CHECKBOX("Toogle", &mods::is_toogled, OnToogle);
  CHECKBOX("Use A/D Keybinds", &mods::is_using_ad, SetKeybinds);
  CHECKBOX("Hide Interface", &mods::is_hidden_interface, OnToogle);
  CHECKBOX("Switch On Death", &mods::is_to_switch_on_death, UpdateJson);
  CHECKBOX("Use Arrows", &mods::is_used_arrows, OnToogle);
}
void GDHMFooter() {
  gdhm::gui::label("");
  gdhm::gui::label("By Ephir");
}