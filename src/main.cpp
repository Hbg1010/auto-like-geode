#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LikeLevelAuto, LevelInfoLayer) {
    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);

        log::debug("is enabled? ", m_likeBtn->isEnabled());

        if (m_likeBtn && m_likeBtn->isEnabled()) {
            LikeItemLayer* x = LikeItemLayer::create(LikeItemType::Level, m_level->m_levelID, 0);
            x->onLike(nullptr);
            x->onClose(nullptr); // 0x1efb49173c0
            // CC_SAFE_DELETE(x);
        }
    }
};

#include <Geode/modify/LikeItemLayer.hpp>
class $modify(LikeLevelPage, LikeItemLayer) {
    bool init(LikeItemType p0, int p1, int p2) {
        if (!LikeItemLayer::init(p0, p1, p2)) return false;
        log::debug("{} and {}", p1, p2);
        return true;
    }
};