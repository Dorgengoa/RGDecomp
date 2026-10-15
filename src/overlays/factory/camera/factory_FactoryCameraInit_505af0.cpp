#include "types.h"

typedef unsigned __int128 u128;

/* factory.bin overlay, 0x00505AF0 -- 612 B.  Reset the factory panel's camera
 * block: seed the eighteen tuning words, rebuild the eye vector from the two
 * angles and the radius, push it through the scene camera, then replicate the
 * target row into the eight history slots and clear the flags.
 *
 * .cpp for the four `jalr $25` (target in $t9 = a real `virtual`): vptr at
 * 0xC0 -> a 0xC0-byte non-polymorphic base with the vptr after it; slots
 * 0x58 = index (0x58-8)/4 = 20, 0xB0 = 42, 0xB4 = 43, 0xC8 = 48.
 *
 * `$f20` held across the two calls is the NAMED float product r
 * ([[normal-named-product-local]]).
 */

struct SceneBase { u8 d[0xC0]; };

struct Scene : SceneBase {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void f_58();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void f_B0(void *v);
    virtual void f_B4(void *v);
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void f_C8(f32 t);
};

union V16 {
    u128 q;
    struct { f32 x; f32 y; f32 z; f32 w; } v;
};

struct Vec { f32 x; f32 y; f32 z; f32 w; };

struct Pan {
    u8   pad000[0x360];
    V16  m360;
    V16  m370;
    V16  m380;
    V16  m390;
    f32  f3A0;
    f32  f3A4;
    f32  f3A8;
    f32  f3AC;
    f32  f3B0;
    f32  f3B4;
    f32  f3B8;
    f32  f3BC;
    f32  f3C0;
    f32  f3C4;
    f32  f3C8;
    f32  f3CC;
    f32  f3D0;
    f32  f3D4;
    f32  f3D8;
    f32  f3DC;
    f32  f3E0;
    f32  f3E4;
    u8   pad3E8[0x400 - 0x3E8];
    V16  m400;
    V16  m410;
    V16  m420;
    V16  m430;
    V16  m440;
    V16  m450;
    V16  m460;
    V16  m470;
    u8   b480;
    s8   b481;
    u8   b482;
    u8   b483_0 : 1;
    u8   b483_1 : 1;
    u8   b483_r : 6;
    f32  f484;
};

struct Game {
    u8  pad0000[0x4344];
    s32 f4344;
};


extern "C" Game  *func_1F5BE0(void);
extern "C" Scene *func_1C3BC0(Game *g, s32 k);
extern "C" void   func_309440(Scene *s, s32 n);
extern "C" f32    func_128D30(f32 a);
extern "C" f32    func_128FD0(f32 a);
extern "C" void   func_13BE20(void *a, void *b, void *c);
extern "C" void   func_131B60(void *p, s32 v, s32 n);
extern "C" void   func_1CAD10(void *p);
extern "C" void   factory_FactoryCameraShakeReset_505060(Pan *p);

extern "C" void factory_FactoryCameraInit_505af0(Pan *p);

void factory_FactoryCameraInit_505af0(Pan *p)
{
    Vec    e;
    Game  *g;
    Scene *s;
    f32    r;

    p->f3A0 = 0.0f;
    p->f3A4 = 0.7853981852531433f;
    p->f3A8 = 400.0f;
    p->f3AC = 0.056099869310855865f;
    p->f3B0 = 0.04908738657832146f;
    p->f3B4 = 20.0f;
    p->f3B8 = 0.0f;
    p->f3BC = 0.0f;
    p->f3C0 = 0.0f;
    p->f3C4 = 2.5464789867401123f;
    p->f3C8 = 0.012500000186264515f;
    p->f3D4 = 0.49087387323379517f;
    p->f3D8 = 1.3253594636917114f;
    p->f3DC = 320.0f;
    p->f3E0 = 800.0f;
    p->f3CC = 60.0f;
    p->f3D0 = 10.0f;
    p->f3E4 = 0.20000000298023224f;
    factory_FactoryCameraShakeReset_505060(p);

    g = func_1F5BE0();
    s = func_1C3BC0(g, g->f4344);
    func_309440(s, 0x10);

    p->m360.v.x = 30.0f;
    p->m360.v.y = p->f3CC;
    p->m360.v.z = 30.0f;
    p->m360.v.w = 1.0f;

    r = p->f3A8 * func_128D30(p->f3A4);
    e.x = r * func_128FD0(p->f3A0);
    e.y = p->f3A8 * func_128FD0(p->f3A4);
    r = p->f3A8 * func_128D30(p->f3A4);
    e.z = r * func_128D30(p->f3A0);
    e.w = 0.0f;
    func_13BE20(&p->m370, &p->m360, &e);

    s->f_B0(&p->m370);
    s->f_B4(&p->m360);

    p->m380.q = p->m360.q;
    p->m390.q = p->m360.q;
    p->m420.q = p->m360.q;
    p->m440.q = p->m360.q;
    p->m430.q = p->m360.q;
    p->m450.q = p->m360.q;
    p->m460.q = p->m360.q;
    p->m470.q = p->m360.q;
    func_131B60(&p->m400, 0, 0x10);
    func_131B60(&p->m410, 0, 0x10);
    func_1CAD10(&p->m370);
    func_1CAD10(&p->m360);

    p->b480 = 0;
    p->b481 = -1;
    p->b482 = 0;
    p->b483_1 = 0;
    p->b483_0 = 0;
    p->f484 = 0.5f;

    s->f_58();
    s->f_C8(1.0f);
}
