#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(LikeLevelAuto, LevelInfoLayer) {

    struct Fields {
        bool hasChecked; // used to check if a level has been liked / evaluated already
    };

    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        AutoLike();
    }

    void updateSideButtons() {
        LevelInfoLayer::updateSideButtons();
        if (!LevelInfoLayer::shouldDownloadLevel()) AutoLike();
    }

    // checks if a level can be liked and does so if it can be.
    void AutoLike() {
        auto ModPointer = Mod::get();
        if (!ModPointer->getSettingValue<bool>("enable") || m_fields->hasChecked) return;
        if (m_likeBtn && m_likeBtn->isEnabled()) {

            /*
            Eval if a level should be liked based on the players percentage.
            I should make this look nicer at some point..
            */
            if (ModPointer->getSettingValue<bool>("progressReq")) {
                int targetPercent = ModPointer->getSettingValue<int>("percentMode");
                bool hasPercents = false;

                hasPercents = targetPercent <= m_level->m_normalPercent.value() && ModPointer->getSettingValue<bool>("normalMode");
                hasPercents = hasPercents || (targetPercent <= m_level->m_practicePercent && ModPointer->getSettingValue<bool>("practiceMode"));
                if (!hasPercents) {
                    m_fields->hasChecked = true;
                    return;
                }
            } 

            // weird, but fixes mobile visual glitch for whatever reason
            LikeItemLayer* extraLikeLayer = LikeItemLayer::create(LikeItemType::Level, m_level->m_levelID, 0);
            extraLikeLayer->onLike(nullptr);
            CCSprite* disableButton = CCSprite::createWithSpriteFrameName("GJ_like2Btn2_001.png");
            m_likeBtn->setSprite(disableButton);
            m_likeBtn->m_bEnabled = false;
            likedItem(LikeItemType::Level, m_level->m_levelID.value(), true);
            CC_SAFE_DELETE(extraLikeLayer);
            m_fields->hasChecked = true;
        }
    }
};