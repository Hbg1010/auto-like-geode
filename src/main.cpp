#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LikeLevelAuto, LevelInfoLayer) {
    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        if (!Mod::get()->getSettingValue<bool>("enable")) return;
        
        if (m_likeBtn && m_likeBtn->isEnabled()) {
            //this works and i wish it didnt. easiest soloution though
            // and before you ask, no it does not duplicate likes. IDK WHY
            LikeItemLayer* extraLikeLayer = LikeItemLayer::create(LikeItemType::Level, m_level->m_levelID, 0);
            LevelInfoLayer::onLike(nullptr);
            if (LikeItemLayer* parent = getParent()->getChildByType<LikeItemLayer*>(0)) {
                parent->setVisible(false);
                parent->onLike(nullptr);
            }

            #ifndef GEODE_IS_DESKTOP
            CCSprite* disableButton = CCSprite::createWithSpriteFrameName("GJ_like2Btn2_001.png");
            m_likeBtn->setSprite(disableButton);
            m_likeBtn->m_bEnabled = false;
            incrementLikes();
            #endif

            // Lets just be safe
            CC_SAFE_DELETE(extraLikeLayer);
        }
    }
};