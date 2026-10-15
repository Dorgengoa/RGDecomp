#include "types.h"
/* insect 0x0050EE60 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x5C =
 * virtual #21 (8 + 4*21).  [[jalr-is-cpp-virtual]]
 *
 * The `lui 0x47 / addiu 0x0F50 / sw 0x1B0` is the INLINED constructor's vptr
 * write, done through a raw alias struct so mwcc does not emit a vtable of
 * our own for the dummy class.
 */

class VQ {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21();                 /* slot 0x5C */
};

/* Alias for the raw vptr write. */
struct QRaw {
    u8 pad000[0x1B0];
    const void *vptr;
};

struct S {
    u8   pad000[0x38];
    s8   f038;
    u8   pad039[0x58 - 0x39];
    VQ  *f058;
    u8   pad05C[0x6C - 0x5C];
    s16  f06C;
};

struct P {
    u8  pad000[0x2C];
    s32 f02C;
    u8  pad030[0x34 - 0x30];
    s32 f034;
};

struct G {
    u8   pad000[0x1E4];
    char f1E4[4];
};

struct Cfg {
    s32   f00;
    const void *f04;
    void *f08;
    void *f0C;
    void *f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    void *f2C;
    s32   f30;
    s32   f34;
    void *f38;
    s32   f3C;
    s32   f40[8];
    s32   f60[8];
    s32   f80[4];
};

extern const u8 D_00470F50[];
extern const char D_00525108[];
extern const char D_00525110[];
extern const u8 D_00524C78[];
extern const u8 D_00524EC0[];

extern "C" s32   func_31A8D0(void);
extern "C" s32   func_1F5BE0(void);
extern "C" void  func_14DB10(void *p, s32 a, s32 b, s32 c);
extern "C" void *func_14E230(s32 size, void *pool);
extern "C" void *func_14E030(void *o);
extern "C" void  func_14DFF0(void *o);
extern "C" s32   func_14D950(P *p, s32 n);
extern "C" void  func_14D810(void *o, s32 a, s32 n);
extern "C" void  func_14DAD0(P *p);
extern "C" void  func_14D830(void *o);
extern "C" u32   func_134BB0(const char *s);
extern "C" void  func_134A98(void *d, const char *s);
extern "C" void  func_1343B8(char *d, const char *f, s32 a);
extern "C" G    *func_15DE40(void);
extern "C" void  func_131B60(void *d, s32 c, s32 n);
extern "C" void  func_1AFD00(VQ *q, Cfg *c);
extern "C" void  func_1CFCD0(s32 h, s16 id, VQ *q, s32 k);
extern "C" void  func_1C3E80(s32 h, s32 k, s16 id);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(s32 a);
extern "C" void  insect_InsectFileSlotRelease_512020(s32 a);
extern "C" s32   insect_InsectFileSlotGetData_511fa0(s32 a, s32 *out);
extern "C" s32   insect_InsectModelMemFindIndex_512870(s32 b, s16 h);
extern "C" P    *insect_InsectModelMemGetSlot_512820(s32 b, s16 h);
extern "C" void  insect_ModelObjExCtor_4f78f0(VQ *q);
extern "C" void  insect_InsectPieceAttachSubModel_515210(S *s, const u8 *t);

extern "C" s32 insect_InsectBattleSpawnBombModel_50ee60(S *s)
{
    s32  n;
    char buf[4];
    Cfg  cfg;
    s32  r;
    s32  b;
    s32  rv;
    s32  cc;
    s32  a;
    s32  v23;
    s16  h;
    s32  v22;
    P   *p;
    void *o;
    s32  len;
    VQ  *q;
    G   *g;

    rv = 0;
    if (s->f038 != 0x11) {
        return 0;
    }
    r = func_31A8D0();
    a = r + 0x5000;
    b = r + 0x4B4C;
    cc = func_1F5BE0();
    if (insect_InsectFileSlotIsLoaded_512010(a) != 0) {
        n = 0;
        v23 = insect_InsectFileSlotGetData_511fa0(a, &n);
        h = s->f06C;
        v22 = insect_InsectModelMemFindIndex_512870(b, h);
        p = insect_InsectModelMemGetSlot_512820(b, h);
        func_14DB10(p, 2, 0, 0x40);
        o = func_14E230(0x58, p);
        if (o != 0) {
            o = func_14E030(o);
        }
        len = p->f034 - p->f02C;
        func_14DFF0(o);
        func_14D810(o, func_14D950(p, len), len);
        func_14DAD0(p);
        func_14D830(o);
        if (func_134BB0(D_00525108) < 0x10) {
            func_134A98(o, D_00525108);
        }
        q = (VQ *)func_14E230(0x790, o);
        if (q != 0) {
            insect_ModelObjExCtor_4f78f0(q);
            ((QRaw *)q)->vptr = D_00470F50;
        }
        func_1343B8(buf, D_00525110, v22);
        g = func_15DE40();
        func_134A98(g->f1E4, buf);
        func_131B60(&cfg, 0, 0x88);
        cfg.f14 = v22 + 0x263;
        cfg.f30 = 8;
        cfg.f2C = cfg.f40;
        cfg.f3C = 8;
        cfg.f38 = cfg.f60;
        cfg.f00 = v23;
        cfg.f04 = D_00524C78;
        cfg.f18 = 1;
        cfg.f08 = o;
        cfg.f0C = o;
        cfg.f10 = o;
        q->s21();
        func_1AFD00(q, &cfg);
        g->f1E4[0] = 0;
        s->f058 = q;
        insect_InsectPieceAttachSubModel_515210(s, D_00524EC0);
        insect_InsectFileSlotRelease_512020(a);
        func_1CFCD0(cc, s->f06C + 0x40, q, 0);
        func_1C3E80(cc, 1, s->f06C + 0x40);
        rv = 1;
    }
    return rv;
}
