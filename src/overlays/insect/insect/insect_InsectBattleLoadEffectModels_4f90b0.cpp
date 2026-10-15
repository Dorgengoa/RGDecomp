#include "types.h"
/* insect 0x004F90B0 -- C++ virtual dispatch, vptr at +0x1B0, slots 0x44 and
 * 0x5C = virtuals #15 and #21.  [[jalr-is-cpp-virtual]]
 *
 * Case 0xA is the same 0x790 allocate / D_00470F50 vptr store / 0x88-byte
 * descriptor body as the already-matched insect_FUN_004F76B0, wrapped in a
 * twelve-iteration loop.  The descriptor's fill ORDER is 004F76B0's, and it is
 * exactly the order retail's eleven `sw` come out in.
 *
 * The compare chain is 0xB, 0xA, 1 with every test a `beql` INTO the arm, so
 * the source case order is the REVERSE: 1, 0xA, 0xB.
 *
 * `lw $6, -0x38($2)` off a `%hi/%lo(D_00524110)` base is `D_00524110[i - 0xE]`
 * with the -0x38 folded into the load displacement -- the reloc names
 * 0x524110, so the SYMBOL is D_00524110 and the bias is in the index.
 */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(f32 a);          /* slot 0x44 */
    virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20();
    virtual void s21();               /* slot 0x5C */
};

struct Q {
    u8 pad000[0x58];
    u8 f58[1];
};

struct M {
    u8    pad000[0x538];
    s32   f538;
    void *f53C;
};

struct Desc {
    void *f00;
    void *f04;
    void *f08;
    void *f0C;
    void *f10;
    s32   f14;
    s32   f18;
    u8    pad1C[0x2C - 0x1C];
    void *f2C;
    s32   f30;
    u8    pad34[4];
    void *f38;
    s32   f3C;
    u8    b40[0x20];
    u8    b60[0x30];
};

struct O {
    u8    pad000[0x4A8];
    u8    f4A8[0x870 - 0x4A8];
    void *f870;
    u8    pad874[0x5000 - 0x874];
    u8    f5000[0x20];
    u8    pad5020[0x5F82 - 0x5020];
    u8    f5F82[0x40];
};

extern "C" u8  D_00470F50[];
extern "C" u8  D_00524C78[];
extern "C" u8  D_00524CA0[];
extern "C" u8  D_00524CC0[];
extern "C" u8  D_00524CD0[];
extern u8 *D_00524110[];
extern s32 D_0047E180;

extern "C" void  func_131B60(void *d, s32 c, s32 n);
extern "C" void  func_1343B8(void *d, const u8 *t, const u8 *v);
extern "C" void  func_14DAD0(void *p);
extern "C" void *func_14DB10(void *p, s32 a, s32 b, s32 c);
extern "C" void  func_14DE90(void *p);
extern "C" void *func_14E230(s32 size, void *pool);
extern "C" void  func_1867A0(VE *m, void *t, s32 k);
extern "C" void  func_1AFD00(VE *m, Desc *d);
extern "C" void *func_1C2800(void *h, void *t, s32 *out);
extern "C" void  func_1C3E40(void *h, s32 a, s32 id);
extern "C" void  func_1CFCD0(void *h, s32 id, VE *m, s32 k);
extern "C" Q    *func_2D9040(void);
extern "C" s32   insect_InsectBattleGetStep_50d6a0(O *o, s32 k);
extern "C" void  insect_InsectBattleSetStep_50d7a0(O *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetState_50d8c0(O *o, s32 a, s32 b, s32 c);
extern "C" s32   insect_InsectBattleTestFlag_50da40(O *o, s32 k);
extern "C" void  insect_InsectBattleSetupEffects_50e260(O *o);
extern "C" void *insect_InsectFileSlotGetData_511fa0(void *p, s32 *out);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(void *p);
extern "C" void  insect_InsectFileSlotRelease_512020(void *p);
extern "C" void  insect_InsectFileSlotRequest_512140(void *p, void *q, s32 n);
extern "C" void  insect_ModelObjExCtor_4f78f0(void *o);

extern "C" void insect_InsectBattleLoadEffectModels_4f90b0(O *o)
{
    Desc  d;
    s32   tmp;
    void *e;
    void *p;
    void *n;
    s32   i;
    u8   *s;
    VE   *m;
    Q    *q;
    s32   t;

    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        insect_InsectBattleSetupEffects_50e260(o);
        insect_InsectFileSlotRequest_512140(o->f5000, D_00524CC0, 6);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 1, -1);
        break;
    case 0xA:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            p = insect_InsectFileSlotGetData_511fa0(o->f5000, &tmp);
            e = o->f4A8;
            func_14DE90(e);
            for (i = 0xE; i < 0x1A; i++) {
                s = o->f5F82;
                func_14DB10(e, 2, 0, 0x40);
                func_1343B8(s, D_00524CD0, D_00524110[i - 0xE]);
                n = func_1C2800(p, s, &tmp);
                m = (VE *)func_14E230(0x790, e);
                if (m != 0) {
                    insect_ModelObjExCtor_4f78f0(m);
                    *(void **)((u8 *)m + 0x1B0) = D_00470F50;
                }
                if (m != 0) {
                    q = func_2D9040();
                    func_131B60(&d, 0, 0x88);
                    d.f2C = d.b40;
                    d.f30 = 8;
                    d.f3C = 8;
                    d.f38 = d.b60;
                    d.f00 = n;
                    d.f04 = D_00524C78;
                    d.f14 = 0x29C;
                    d.f08 = e;
                    d.f0C = e;
                    d.f10 = e;
                    d.f18 = 0;
                    m->s21();
                    ((M *)m)->f53C = q->f58;
                    if (q->f58 != 0) {
                        t = D_0047E180;
                        D_0047E180 = t + 1;
                        ((M *)m)->f538 = t;
                    }
                    func_1AFD00(m, &d);
                    func_1867A0(m, D_00524CA0, 2);
                    m->s15(1.0f);
                }
                func_1CFCD0(o->f870, i + 0x80, m, 0);
                func_14DAD0(e);
                func_1C3E40(o->f870, 1, i + 0x80);
            }
            insect_InsectFileSlotRelease_512020(o->f5000);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        }
        break;
    case 0xB:
        if (insect_InsectBattleTestFlag_50da40(o, 5) != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        }
        break;
    }
}
