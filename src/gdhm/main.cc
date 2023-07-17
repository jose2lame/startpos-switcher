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
  auto updateJson = []() {
    json j = {};
    std::fstream fs(".startpos_switcher/settings.json", std::ios::in | std::ios::out);
    if (fs.is_open()) fs >> j;
    fs.close();
    fs.open(".startpos_switcher/settings.json", std::ios::out | std::ios::trunc);
    if (fs.is_open()) {
      j["Toogle"] = mods::is_toogled;
      j["Use A/D key_binds"] = mods::is_using_ad;
      j["Hide Interface"] = mods::is_hidden_interface;
      j["Switch On Death"] = mods::is_to_switch_on_death;
      j["Use Arrows"] = mods::is_used_arrows;
      fs << j;
    }
    fs.close();
  };
  auto setkey_binds = [&updateJson]() {
    if (mods::is_using_ad) switcher::key_binds = {KEY_A, KEY_D};
    else switcher::key_binds = {KEY_Left, KEY_Right};
    updateJson();
  };
  auto onToogle = [&updateJson]() {
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
    updateJson();
  };
  setkey_binds();
  onToogle();
  CHECKBOX("Toogle", &mods::is_toogled, onToogle);
  CHECKBOX("Use A/D key_binds", &mods::is_using_ad, setkey_binds);
  CHECKBOX("Hide Interface", &mods::is_hidden_interface, onToogle);
  CHECKBOX("Switch On Death", &mods::is_to_switch_on_death, updateJson);
  CHECKBOX("Use Arrows", &mods::is_used_arrows, onToogle);
}
void GDHMFooter() {
  gdhm::gui::label("");
  gdhm::gui::label("By GD Ephir");
}