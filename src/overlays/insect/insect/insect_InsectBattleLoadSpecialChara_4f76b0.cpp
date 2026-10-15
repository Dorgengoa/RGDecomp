#include "types.h"
/* insect 0x004F76B0 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x5C =
 * virtual #21.  [[jalr-is-cpp-virtual]]  Same 0x790 allocate / D_00470F50
 * vptr store / 0x88-byte descriptor shape as 0x005125F0. */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21();               /* slot 0x5C */
};

struct R {
    u8 pad000[0x50];
    s8 f50;
};

struct Q {
    u8  pad000[0x58];
    u8  f58[1];
};

struct O {
    u8    pad000[0x138];
    u8    f138[0x5000 - 0x138];
    u8    f5000[0x51BC - 0x5000];
    VE   *f51BC;
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
    u8    b60[0x28];
    u8    b88[0x14];
};

struct M {
    u8    pad000[0x538];
    s32   f538;
    void *f53C;
};

extern "C" u8 D_00470F50[];
extern "C" u8 D_00524C78[];
extern s32 D_0047E180;
extern "C" R *insect_InsectBattleGetSpecialRec_50db30(void);
extern "C" void insect_InsectBattleSetState_50d8c0(O *o, s32 a, s32 b, s32 c);
extern "C" void insect_InsectBattleSetStep_50d7a0(O *o, s32 a, s32 b, s32 c);
extern "C" s32 insect_InsectBattleGetStep_50d6a0(O *o, s32 k);
extern "C" void insect_InsectFileSlotRequest_512140(void *p, void *q, s32 n);
extern "C" s32 insect_InsectFileSlotIsLoaded_512010(void *p);
extern "C" void *insect_InsectFileSlotGetData_511fa0(void *p, s32 *out);
extern "C" void insect_InsectFileSlotRelease_512020(void *p);
extern "C" void insect_ModelObjExCtor_4f78f0(void *o);
extern "C" void func_14DE90(void *p);
extern "C" void *func_14DB10(void *p, s32 a, s32 b, s32 c);
extern "C" void *func_14E230(s32 size, void *pool);
extern "C" void func_14DAD0(void *p);
extern "C" Q *func_2D9040(void);
extern "C" void func_131B60(void *d, s32 c, s32 n);
extern "C" void func_1AFD00(VE *o, Desc *d);

extern "C" void insect_InsectBattleLoadSpecialChara_4f76b0(O *o)
{
    Desc  d;
    s32   tmp;
    R    *r;
    s8   *h;
    void *e;
    void *p;
    VE   *m;
    Q    *q;
    s32   t;

    r = insect_InsectBattleGetSpecialRec_50db30();
    if (r == 0) {
        insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
    } else {
        h = &r->f50;
        if (r->f50 == 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        } else {
        switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
        case 1:
            insect_InsectFileSlotRequest_512140(o->f5000, h, 7);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 1, -1);
            break;
        case 0xA:
            if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
                e = o->f138;
                p = insect_InsectFileSlotGetData_511fa0(o->f5000, &tmp);
                func_14DE90(e);
                func_14DB10(e, 2, 0, 0x40);
                m = (VE *)func_14E230(0x790, e);
                if (m != 0) {
                    insect_ModelObjExCtor_4f78f0(m);
                    *(void **)((u8 *)m + 0x1B0) = D_00470F50;
                }
                q = func_2D9040();
                func_131B60(&d, 0, 0x88);
                d.f2C = d.b40;
                d.f30 = 8;
                d.f3C = 8;
                d.f38 = d.b60;
                d.f00 = p;
                d.f04 = D_00524C78;
                d.f14 = 0x29D;
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
                o->f51BC = m;
                func_14DAD0(e);
                insect_InsectFileSlotRelease_512020(o->f5000);
                insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
            }
            break;
        }
        }
    }
}
