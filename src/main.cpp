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
            if (auto parent = getParent()->getChildByType<LikeItemLayer*>(0)) {
                parent->onLike(nullptr);
            }

            // Lets just be safe
            CC_SAFE_DELETE(extraLikeLayer);
        }
    }
};

#include <Geode/modify/LikeItemLayer.hpp>
class $modify(LikeLevelPage, LikeItemLayer) {
    bool init(LikeItemType p0, int p1, int p2) {
        if (!LikeItemLayer::init(p0, p1, p2)) return false;
        if (Mod::get()->getSettingValue<bool>("enable") && p0 == LikeItemType::Level) {
            this->setVisible(false);
            LikeItemLayer::onLike(nullptr);
        }
        
        return true;
    }
};