#undef isnan
#undef snprintf

#include <filesystem>
#include <fstream>

#include <gdhm.hpp>
#include <matdash.hpp>
#include <matdash/minhook.hpp>
#include <matdash/boilerplate.hpp>
#include <nlohmann/json.hpp>

#include "gdhm/main.h"
#include "mod_layers.h"
#include "mods.h"

using nlohmann::json;
void mod_main(HMODULE hModule) {
  if (gdhm::is_loaded()) {
    gdhm::gui::window("STARTPOS SWITCHER", "", nullptr, []() {}, GDHMHeader, 
                      GDHMFooter);
    matdash::add_hook<&ModPlayLayer::Init>(gd::base + 0x1FB780);
    matdash::add_hook<&ModPlayLayer::resetLevel>(gd::base + 0x20BF00);
    matdash::add_hook<&ModPlayLayer::addObject>(gd::base + 0x2017E0);
    matdash::add_hook<&ModPlayLayer::onQuit>(gd::base + 0x20D810);
    matdash::add_hook<&ModUILayer::KeyDown>(gd::base + 0x25F890);
    matdash::add_hook<&ModPauseLayer::KeyDown>(gd::base + 0x1E6580);
    matdash::add_hook<&ModMenuLayer::onMoreGames>(gd::base + 0x1919C0);
    std::filesystem::create_directory(".startpos_switcher");
    if (std::filesystem::exists(".startpos_switcher/settings.json")) {
      json j = {};
      std::ifstream fs(".startpos_switcher/settings.json");
      if (fs.is_open()) {
        fs >> j;
        mods::is_toogled = j["Toogle"].get<bool>();
        mods::is_using_ad = j["Use A/D key_binds"].get<bool>();
        mods::is_hidden_interface = j["Hide Interface"].get<bool>();
        mods::is_to_switch_on_death = j["Switch On Death"].get<bool>();
        mods::is_used_arrows = j["Use Arrows"].get<bool>();
      }
      fs.close();
    } else {
      std::ofstream fs(".startpos_switcher/settings.json", std::ios::out);
      if (fs.is_open()) {
        fs <<  
            "{\"Toogle\" : false,"
            "\"Use A/D key_binds\" : false,"
            "\"Hide Interface\" : false,"
            "\"Switch On Death\" : false,"
            "\"Use Arrows\" : false"
            "\n}";
      }
      fs.close();
    }
  }
}