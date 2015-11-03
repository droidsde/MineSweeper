//
//  ParticleSystemPool.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/21.
//
//

#ifndef __LightingGame__ParticleSystemPool__
#define __LightingGame__ParticleSystemPool__

#include "Common.h"
#include "NParticleSystemQuad.h"

class ParticleSystemPool : public cocos2d::Ref {
    
public:
    static ParticleSystemPool* create(std::string filename, size_t size);
    bool init(std::string filename, size_t size);
    void push(NParticleSystemQuad* particle);
    NParticleSystemQuad* pop();
    
protected:
    /* プールの実体 */
    cocos2d::Vector<NParticleSystemQuad*> _pool;
};

#endif /* defined(__LightingGame__ParticleSystemPool__) */
