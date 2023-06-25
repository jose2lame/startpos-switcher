#include <filesystem>
#include <fstream>

#include <gdhm.hpp>
#include <matdash.hpp>
#include <matdash/minhook.hpp>
#include <matdash/boilerplate.hpp>
#undef isnan
#undef snprintf
#include <nlohmann/json.hpp>

#include "GDHMMain.hpp"
#include "ModLayers.hpp"
#include "mods.hpp"

using nlohmann::json;

void mod_main(HMODULE hModule) {
    if (gdhm::is_loaded()) {
        gdhm::gui::window (
            "STARTPOS SWITCHER",
            "",
            nullptr, 
            [](void) {}, 
            GDHMHeader,
            GDHMFooter
        );
        matdash::add_hook<&ModPlayLayer::_init>(
            gd::base + 0x1FB780
        );
        matdash::add_hook<&ModPlayLayer::resetLevel>(
            gd::base + 0x20BF00
        );
        matdash::add_hook<&ModPlayLayer::addObject>(
            gd::base + 0x2017E0
        );
        matdash::add_hook<&ModPlayLayer::onQuit>(
            gd::base + 0x20D810
        );
        matdash::add_hook<&ModUILayer::_keyDown>(
            gd::base + 0x25F890
        );
        matdash::add_hook<&ModPauseLayer::_keyDown>(
            gd::base + 0x1E6580
        );
        matdash::add_hook<&ModMenuLayer::onMoreGames>(
            gd::base + 0x1919C0
        );

        std::filesystem::create_directory(
            ".startpos_switcher"
        );

        if(std::filesystem::exists(
            ".startpos_switcher/settings.json"
        )) {
            json j = {};
            std::ifstream fs(
                ".startpos_switcher/settings.json"
            );

            if(fs.is_open()) {
                fs >> j;
                mods::toogle = j["Toogle"].
                    get<bool>();
                mods::useAD = j["Use A/D Keybinds"].
                    get<bool>();
                mods::hideInterface = j["Hide Interface"].
                    get<bool>();
                mods::switchOnDeath = j["Switch On Death"].
                    get<bool>();
                mods::useArrows = j["Use Arrows"].
                    get<bool>();
            }

            fs.close();
        } else {
            std::ofstream fs(
                ".startpos_switcher/settings.json",
                std::ios::out
            );

            if (fs.is_open()) {
                fs <<  
                    "{\"Toogle\" : false,"
                    "\"Use A/D Keybinds\" : false,"
                    "\"Hide Interface\" : false,"
                    "\"Switch On Death\" : false,"
                    "\"Use Arrows\" : false"
                    "\n}";
            }

            fs.close();
        }
    }
}
