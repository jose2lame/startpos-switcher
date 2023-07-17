#ifndef STARTPOS_SWITCHER_SRC_LAYERS_PLAY_H_
#define STARTPOS_SWITCHER_SRC_LAYERS_PLAY_H_

#include <gd.h>
#include "../mods/mods.h"
#include "../switcher/switcher.h"

using namespace cocos2d;
using namespace gd;
class ModPlayLayer final : gd::PlayLayer {
 public:
  bool Init(gd::GJGameLevel* lvl);
  void addObject(gd::GameObject* game);
  void resetLevel();
  void onQuit();
};
bool ModPlayLayer::Init(GJGameLevel* lvl) {
  switcher::index = -1;
  switcher::start_poses.clear();
  switcher::is_in_menu = false;
  switcher::is_created = true;
  switcher::text = 
      CCLabelBMFont::create(
          "0/0", 
          "bigFont.fnt"
      );
  CCSize visible_size = CCDirector::sharedDirector()->getVisibleSize();
  switcher::text->setPosition(visible_size.width / 2, 15);
  switcher::text->setScale(0.5f);
  switcher::text->setOpacity(70);
  switcher::text->setZOrder(0x7FFFFFFF);
  switcher::left_arrow = CCSprite::createWithSpriteFrameName(
      "GJ_arrow_03_001.png");
  switcher::left_arrow->setScale(0.5f);
  switcher::left_arrow->setOpacity(70);
  switcher::right_arrow = CCSprite::createWithSpriteFrameName(
      "GJ_arrow_03_001.png");
  switcher::right_arrow->setScale(0.5f);
  switcher::right_arrow->setOpacity(70);
  switcher::right_arrow->setFlipX(true);
  bool result = matdash::orig<&ModPlayLayer::Init>(this, lvl);
  switcher::left_arrow_button = CCMenuItemSpriteExtra::create(
      switcher::left_arrow, 
      this, 
      menu_selector(switcher::Callbacks::LeftArrowButton));
  switcher::left_arrow_button->setPosition(ccp(-30, 0));
  switcher::right_arrow_button = CCMenuItemSpriteExtra::create(
      switcher::right_arrow, 
      this, 
      menu_selector(switcher::Callbacks::RightArrowButton));
  switcher::right_arrow_button->setPosition(ccp(30, 0));
  auto menu = CCMenu::create();
  menu->addChild(switcher::left_arrow_button);
  menu->addChild(switcher::right_arrow_button);
  menu->setPosition(ccp(((visible_size.width / 2)), 15));
  menu->setZOrder(0x7FFFFFFF);
  switcher::text->setVisible(!switcher::start_poses.empty() && mods::is_toogled &&
                             !mods::is_hidden_interface);
  switcher::left_arrow_button->setVisible((!switcher::start_poses.empty() && 
                                        mods::is_toogled &&
                                        !mods::is_hidden_interface &&
                                        mods::is_used_arrows));
  switcher::right_arrow_button->setVisible((!switcher::start_poses.empty() && 
                                         mods::is_toogled && 
                                         !mods::is_hidden_interface &&
                                         mods::is_used_arrows));
  addChild(switcher::text);
  addChild(menu);
  return result;
}
void ModPlayLayer::addObject(GameObject* game) {
  matdash::orig<&ModPlayLayer::addObject>(this, game);
  if (game->m_nObjectID == 31) {
    game->retain();
    switcher::start_poses.push_back({reinterpret_cast<StartPosObject*>(game),
                                    game->getPosition()});
    switcher::index++;
    if (switcher::text != nullptr) {
        std::string label = std::format(
            "{}/{}",
            std::to_string(switcher::index + 1), 
            std::to_string(switcher::start_poses.size()));
        switcher::text->setString(label.c_str());
    }
    game->release();
  }
}
void ModPlayLayer::resetLevel() {
  m_isTestMode = m_startPos != 0;
  matdash::orig<&ModPlayLayer::resetLevel>(this);
  if (switcher::is_to_switch) switcher::SwitchStartPos(this);
}
void ModPlayLayer::onQuit() {
  matdash::orig<&ModPlayLayer::onQuit>(this);
  switcher::is_in_menu = true;
}

#endif // STARTPOS_SWITCHER_SRC_LAYERS_PLAY_H_