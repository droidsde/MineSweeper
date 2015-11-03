//
//  NParticleSystemQuad.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/21.
//
//

#ifndef __LightingGame__NParticleSystemQuad__
#define __LightingGame__NParticleSystemQuad__

#include "Common.h"

class NParticleSystemQuad : public cocos2d::ParticleSystemQuad {
    
public:
    static NParticleSystemQuad* create(const std::string& filename);
    
    /* 親クラスのメソッドを上書きしたい */
    virtual void update(float dt) override;
    
    /* コールバック関数を保持する */
    std::function<void(NParticleSystemQuad*)> onFinishListener;
};

#endif /* defined(__LightingGame__NParticleSystemQuad__) */
