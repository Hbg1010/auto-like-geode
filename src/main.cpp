#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LikeLevelAuto, LevelInfoLayer) {
    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        if (!Mod::get()->getSettingValue<bool>("enable")) return;
        
        if (m_likeBtn && m_likeBtn->isEnabled()) {
            LikeItemLayer* extraLikeLayer = LikeItemLayer::create(LikeItemType::Level, m_level->m_levelID, 0);
            extraLikeLayer->onLike(nullptr);
            CCSprite* disableButton = CCSprite::createWithSpriteFrameName("GJ_like2Btn2_001.png");
            m_likeBtn->setSprite(disableButton);
            m_likeBtn->m_bEnabled = false;
            incrementLikes();
            CC_SAFE_DELETE(extraLikeLayer);
        }
    }
};