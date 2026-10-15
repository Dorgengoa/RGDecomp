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
    virtual void s00();  virtual void s01();  virtual void s02();
    virtual void s03();  virtual void s04();  virtual void s05();
    virtual void s06();  virtual void s07();  virtual void s08();
    virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();  virtual void s14();
    virtual void s15();  virtual void s16();  virtual void s17();
    virtual void s18();  virtual void s19();  virtual void s20();
    virtual void s21();  virtual void s22();  virtual void s23();
    virtual void s24();  virtual void s25();  virtual void s26();
    virtual void s27();  virtual void s28();  virtual void s29();
    virtual void s30();  virtual void s31();  virtual void s32();
    virtual void s33();  virtual void s34();  virtual void s35();
    virtual void s36();  virtual void s37();  virtual void s38();
    virtual void f_A4(void *v);
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

extern "C" Game  *func_1F5BE0(void);
extern "C" Scene *func_1C3BC0(Game *g, s32 k);
extern "C" void   func_131B60(void *p, s32 v, s32 n);
extern "C" f32    func_13D390(Vec *a, Vec *b);
extern "C" void   func_132D08(void *base, s32 n, s32 sz, void *cmp);
extern "C" void   factory_FactoryMarkerDepthCmp_4f6160(void);

extern "C" void factory_FactoryMarkerDrawBase_4f5e70(void *o, s32 skip, s32 idx);
extern "C" void factory_FactoryMarkerDrawNumber_4f5710(void *o, s32 idx);
extern "C" void factory_FactoryMarkerDrawItemIcon_4f5490(void *o, s32 idx);
extern "C" void factory_FactoryMarkerDrawKindAnim_4f51a0(void *o, s32 idx);
extern "C" void factory_FactoryProduceDrawFailFlash_4f5000(void *o);

extern "C" void factory_FactoryMarkerDrawAll_4f6ba0(Ctx *o);

void factory_FactoryMarkerDrawAll_4f6ba0(Ctx *o)
{
    Vec    m;
    Ent    out[6];
    Vec    v;
    Game  *g;
    Scene *s;
    Cell  *e;
    s32    i;
    s32    n;

    g = func_1F5BE0();
    s = func_1C3BC0(g, g->f4344);
    s->f_A4(&m);

    n = 0;
    func_131B60(out, 0, 0x30);

    for (i = 0; i < 6; i++) {
        e = &o->f78[i];
        if (e->f0E != 0) {
            out[n].f04 = i;
            v.f00 = e->f00;
            v.f04 = e->f04;
            v.f08 = e->f08;
            v.f0C = 1.0f;
            out[i].f00 = func_13D390(&v, &m);
            n++;
        }
    }

    if (n > 0) {
        func_132D08(out, n, 8, (void *)factory_FactoryMarkerDepthCmp_4f6160);
        for (i = 0; i < n; i++) {
            factory_FactoryMarkerDrawBase_4f5e70(o, 0, out[i].f04);
            factory_FactoryMarkerDrawNumber_4f5710(o, out[i].f04);
            factory_FactoryMarkerDrawItemIcon_4f5490(o, out[i].f04);
            factory_FactoryMarkerDrawKindAnim_4f51a0(o, out[i].f04);
        }
        factory_FactoryProduceDrawFailFlash_4f5000(o);
    }
}
