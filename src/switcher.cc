#include "switcher.h"

#include "mods.h"

using namespace cocos2d;
using namespace gd;
switcher::StartPosInfo switcher::start_poses = {};
std::array<enumKeyCodes, 2>
    switcher::key_binds = {KEY_Left, KEY_Right};
std::ptrdiff_t switcher::index = 0;
CCLabelBMFont* switcher::text = nullptr;
CCSprite* switcher::left_arrow = nullptr;
CCSprite* switcher::right_arrow = nullptr;
CCMenuItemSpriteExtra* switcher::left_arrow_button = nullptr;
CCMenuItemSpriteExtra* switcher::right_arrow_button = nullptr;
bool switcher::is_in_menu = false;
bool switcher::is_created = false;
namespace {

void PulseObjects(void) {
  switcher::left_arrow->runAction(
      CCSequence::create(CCFadeTo::create(0.0f, 255), 
                         CCFadeTo::create(1.0f, 255), 
                         CCFadeTo::create(0.5f, 70), nullptr));
  switcher::right_arrow->runAction(
      CCSequence::create(CCFadeTo::create(0.0f, 255), 
                         CCFadeTo::create(1.0f, 255), 
                         CCFadeTo::create(0.5f, 70), nullptr));
  switcher::text->runAction(
      CCSequence::create(CCFadeTo::create(0.0f, 255),
                         CCFadeTo::create(1.0f, 255), 
                         CCFadeTo::create(0.5f, 70), nullptr));
}

} // namespace
void switcher::SwitchStartPos(PlayLayer* game) {
  switcher::is_to_switch = false;
  if (switcher::start_poses.empty() || game->m_isPracticeMode) return;
  game->m_startPosCheckpoint = nullptr;
  if (switcher::index == -1) {
    game->m_startPos = nullptr;
    game->m_playerStartPosition = ccp(0, 105);
  } else {
    game->m_startPos = switcher::start_poses[switcher::index].first;
    game->m_playerStartPosition = switcher::start_poses[switcher::index].second;
  }
  game->resetLevel();
  if (game->m_bIsPaused)
    GameSoundManager::sharedState()->stopBackgroundMusic();
}
void switcher::UpdateIndex(bool increment) {
  switcher::index += increment;
  switcher::index -= !increment;
  if (switcher::index == switcher::start_poses.size()) switcher::index = -1;
  else if (switcher::index < -1) 
    switcher::index = switcher::start_poses.size() - 1;
  auto label = std::format("{}/{}", 
                           std::to_string(switcher::index + 1),
                           std::to_string(switcher::start_poses.size()));
  switcher::text->setString(label.c_str());
  PulseObjects();
}
bool switcher::direction;
bool switcher::is_to_switch = false;
void switcher::Callbacks::LeftArrowButton(CCObject* obj) {
  auto* play_layer = PlayLayer::get();
  switcher::UpdateIndex(false);
  if (!mods::is_to_switch_on_death) switcher::SwitchStartPos(play_layer);
  else {
    switcher::direction = false;
    switcher::is_to_switch = true;
  }
}
void switcher::Callbacks::RightArrowButton(CCObject* obj) {
  auto* play_layer = PlayLayer::get();
  switcher::UpdateIndex(true);
  if (!mods::is_to_switch_on_death) switcher::SwitchStartPos(play_layer);
  else {
    switcher::direction = true;
    switcher::is_to_switch = true;
  }
}