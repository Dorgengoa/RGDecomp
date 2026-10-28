/* rgp:protos */
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504EE0 -- 376 B.  Three-state shake driver:
 * four virtual calls through the global scene object's 0xC0 vptr, with the
 * decay + counter tail on state 2.
 *
 * .cpp for the four `jalr $25` calls (target in $t9 = a real `virtual`).
 * vptr at 0xC0 -> a 0xC0-byte non-polymorphic base with the vptr after it;
 * slot 0xA4 = index (0xA4-8)/4 = 39, 0xA8 = 40, 0xB0 = 42, 0xB4 = 43.
 */

struct SceneBase { u8 d[0xC0]; };

struct Scene : SceneBase {
    VC_VPTR_MEMBER;    
        
        
        
        
        
        
        
        
        
        void s32() { VCM0(void, 0x88); }
        
        
    void f_A4(void *v) { VCM(void, (void *, void *), 0xA4, v); }
    void f_A8(void *v) { VCM(void, (void *, void *), 0xA8, v); }
    
    void f_B0(void *v) { VCM(void, (void *, void *), 0xB0, v); }
    void f_B4(void *v) { VCM(void, (void *, void *), 0xB4, v); }
};

struct Vec { f32 f00; f32 f04; f32 f08; f32 f0C; };

struct Pan {
    u8  pad000[0x3E8];
    s32 f3E8;
    s32 f3EC;
    f32 f3F0;
};

struct Game {
    u8  pad0000[0x4344];
    s32 f4344;
};

extern "C" f32 D_0047D8D8;

extern "C" Game  *GetCurrentScene_1f5be0(void);
extern "C" Scene *ObjRecGetLiveObject_1c3bc0(Game *g, s32 k);

extern "C" void factory_FactoryCameraShakeStep_504ee0(Pan *o);

void factory_FactoryCameraShakeStep_504ee0(Pan *o)
{
    Vec    a __attribute__((aligned(16)));
    Vec    b __attribute__((aligned(16)));
    Scene *s;
    Game  *g;
    f32    d;

    g = GetCurrentScene_1f5be0();
    s = ObjRecGetLiveObject_1c3bc0(g, g->f4344);

    switch (o->f3E8) {
    case 0:
        o->f3EC = 0;
        break;
    case 1:
        o->f3E8 = 2;
        o->f3EC = 0;
        s->f_A4(&a);
        s->f_A8(&b);
        d = o->f3F0;
        a.f04 += d;
        b.f04 += d;
        s->f_B0(&a);
        s->f_B4(&b);
        break;
    case 2:
        s->f_A4(&a);
        s->f_A8(&b);
        d = o->f3F0;
        a.f04 += d;
        b.f04 += d;
        s->f_B0(&a);
        s->f_B4(&b);
        o->f3F0 = o->f3F0 * D_0047D8D8;
        o->f3EC++;
        if (o->f3EC > 0xA) {
            o->f3E8 = 0;
            o->f3EC = 0;
            o->f3F0 = 0.0f;
        }
        break;
    }
}
