/* rgp:protos */
#line 1
#include "types.h"

#pragma optimization_level 3

/* factory.bin overlay, 0x004F6BA0 -- 364 B.  Collect the live trail records,
 * measure each against the scene's reference point, sort by that distance and
 * replay the four per-record updates in sorted order.
 *
 * .cpp for the ONE `jalr $25` (target in $t9 = a real `virtual`): vptr at
 * 0xC0 -> a 0xC0-byte non-polymorphic base with the vptr after it; slot 0xA4
 * is index (0xA4-8)/4 = 39.
 *
 * NOTE the index asymmetry in the gather loop is retail's own: the id is
 * written to `out[n]` but the distance to `out[i]`.
 */

struct SceneBase { u8 d[0xC0]; };

struct Scene : SceneBase {
    VC_VPTR_MEMBER;    
        
        
        
        
      void s16() { VCM0(void, 0x48); }  
        
        
        
        
        void s32() { VCM0(void, 0x88); }
        
        
    void f_A4(void *v) { VCM(void, (void *, void *), 0xA4, v); }
};

struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
    u8  f0E;
    u8  f0F;
    s32 f10;
};                                      /* 0x14 */

struct Ctx {
    u8    pad00[0x78];
    Cell *f78;
};

struct Vec { f32 f00; f32 f04; f32 f08; f32 f0C; };

struct Ent { f32 f00; s16 f04; };       /* 8 */

struct Game {
    u8  pad0000[0x4344];
    s32 f4344;
};

extern "C" Game  *GetCurrentScene_1f5be0(void);
extern "C" Scene *ObjRecGetLiveObject_1c3bc0(Game *g, s32 k);
extern "C" void   memset(void *p, s32 v, s32 n);
extern "C" f32    VecDistanceXZ_13d390(Vec *a, Vec *b);
extern "C" void   Qsort_132d08(void *base, s32 n, s32 sz, void *cmp);
extern "C" void   factory_FactoryMarkerDepthCmp_4f6160(void);

extern "C" void factory_FactoryMarkerDrawBase_4f5e70(void *o, s32 skip, s32 idx);
extern "C" void factory_FactoryMarkerDrawNumber_4f5710(void *o, s32 idx);
extern "C" void factory_FactoryMarkerDrawItemIcon_4f5490(void *o, s32 idx);
extern "C" void factory_FactoryMarkerDrawKindAnim_4f51a0(void *o, s32 idx);
extern "C" void factory_FactoryProduceDrawFailFlash_4f5000(void *o);

extern "C" void factory_FactoryMarkerDrawAll_4f6ba0(Ctx *o);

void factory_FactoryMarkerDrawAll_4f6ba0(Ctx *o)
{
    Vec    m __attribute__((aligned(16)));
    Ent    out[6] __attribute__((aligned(16)));
    Vec    v __attribute__((aligned(16)));
    Game  *g;
    Scene *s;
    Cell  *e;
    s32    i;
    s32    n;

    g = GetCurrentScene_1f5be0();
    s = ObjRecGetLiveObject_1c3bc0(g, g->f4344);
    s->f_A4(&m);

    n = 0;
    memset(out, 0, 0x30);

    for (i = 0; i < 6; i++) {
        e = &o->f78[i];
        if (e->f0E != 0) {
            out[n].f04 = i;
            v.f00 = e->f00;
            v.f04 = e->f04;
            v.f08 = e->f08;
            v.f0C = 1.0f;
            out[i].f00 = VecDistanceXZ_13d390(&v, &m);
            n++;
        }
    }

    if (n > 0) {
        Qsort_132d08(out, n, 8, (void *)factory_FactoryMarkerDepthCmp_4f6160);
        for (i = 0; i < n; i++) {
            factory_FactoryMarkerDrawBase_4f5e70(o, 0, out[i].f04);
            factory_FactoryMarkerDrawNumber_4f5710(o, out[i].f04);
            factory_FactoryMarkerDrawItemIcon_4f5490(o, out[i].f04);
            factory_FactoryMarkerDrawKindAnim_4f51a0(o, out[i].f04);
        }
        factory_FactoryProduceDrawFailFlash_4f5000(o);
    }
}
