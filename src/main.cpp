#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(LikeLevelAuto, LevelInfoLayer) {

    struct Fields {
        bool hasChecked; // used to check if a level has been liked / evaluated already
    };

    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        autoLike();
    }

    void updateSideButtons() {
        LevelInfoLayer::updateSideButtons();
        if (!LevelInfoLayer::shouldDownloadLevel()) autoLike();
    }

    // checks if a level can be liked and does so if it can be.
    void autoLike() {
        auto fields = m_fields.self();
        if (!Mod::get()->getSettingValue<bool>("enable") || fields->hasChecked || !m_likeBtn || !m_likeBtn->isEnabled()) return;

        if (Mod::get()->getSettingValue<bool>("progressReq")) {
            bool hasPercents = false;

            if (m_level->isPlatformer()) {
                hasPercents = Mod::get()->getSettingValue<bool>("normalPlat") && m_level->m_normalPercent.value() == 100;
                hasPercents = hasPercents || (Mod::get()->getSettingValue<bool>("pracPlat") && m_level->m_normalPercent.value() == 100);
            } else {
                int targetPercent = Mod::get()->getSettingValue<int>("percentMode");
                hasPercents = targetPercent <= m_level->m_normalPercent.value() && Mod::get()->getSettingValue<bool>("normalMode");
                hasPercents = hasPercents || (targetPercent <= m_level->m_practicePercent && Mod::get()->getSettingValue<bool>("practiceMode"));
            }

            if (!hasPercents) {
                fields->hasChecked = true;
                return;
            }
        }

        GameLevelManager::get()->likeItem(LikeItemType::Level, m_level->m_levelID, true, 0);
        incrementLikes();

        auto spr = CCSprite::createWithSpriteFrameName("GJ_like2Btn2_001.png");
        m_likeBtn->setSprite(spr);
        m_likeBtn->setEnabled(false);

        m_fields->hasChecked = true;
    }
};