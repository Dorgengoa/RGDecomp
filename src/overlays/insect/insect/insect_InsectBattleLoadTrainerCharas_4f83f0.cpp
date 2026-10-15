#include "types.h"
/* insect 0x004F83F0 -- 1,188 B, br 17.  A seven-arm `insect_InsectBattleGetStep_50d6a0(o,1)`
 * state dispatch.  C++: `lw $25,0x1B0($4) / lw $25,0x5C($25) / jalr $25` is a
 * virtual member call, virtual #21 (slot 8 + 4*21 = 0x5C), vptr at 0x1B0.
 * [[jalr-is-cpp-virtual]]
 *
 * Every test is `beql $2,$3,<arm>` -- a branch INTO the arm -- so this is a
 * real `switch` and the compare chain E,D,C,B,3C,A,1 is REVERSED from the
 * source order 1,A,3C,B,C,D,E ([[insect-dispatch-branch-polarity]]).  The arm
 * ADDRESSES confirm it: they ascend in exactly the reverse of the test order.
 *
 * The 0x88-byte record is insect_InsectBattleLoadJasterCfg_4f7530's `Rec`, same 0x90 size and same
 * count-before-buffer fill order.  There are TWO of them (frame slots 0x40 and
 * 0xD0) and two out-params (0x168, 0x16C); the case-0xA pair sits ABOVE the
 * case-0xE pair, matching source order.
 */

typedef struct Rec {
    s32 f00;
    u8 *f04;
    u8 *f08;
    u8 *f0C;
    u8 *f10;
    s32 f14;
    s32 f18;
    u8  pad1C[0x2C - 0x1C];
    u8 *f2C;
    s32 f30;
    u8  pad34[0x38 - 0x34];
    u8 *f38;
    s32 f3C;
    u8  f40[0x60 - 0x40];
    u8  f60[0x90 - 0x60];
} Rec;

class Ent {
public:
    u8 pad000[0x1B0];
    virtual void d00();  virtual void d01();  virtual void d02();
    virtual void d03();  virtual void d04();  virtual void d05();
    virtual void d06();  virtual void d07();  virtual void d08();
    virtual void d09();  virtual void d10();  virtual void d11();
    virtual void d12();  virtual void d13();  virtual void d14();
    virtual void d15();  virtual void d16();  virtual void d17();
    virtual void d18();  virtual void d19();  virtual void d20();
    virtual void f5C();                       /* slot 0x5C = 8 + 4*21 */
};

struct EntRaw {
    u8  pad000[0x1B0];
    u8 *f1B0;
};

typedef struct Ins {
    u8    pad000[0xDC];
    u8   *fDC;                          /* +0x00DC */
    u8    pad0E0[0x7C0 - 0xE0];
    u8    f7C0[0x870 - 0x7C0];          /* +0x07C0 */
    void *f870;                         /* +0x0870 */
    u8    pad874[0x884 - 0x874];
    Ent  *f884;                         /* +0x0884 */
    Ent  *f888;                         /* +0x0888 */
    u8    pad88C[0x5000 - 0x88C];
    u8    f5000[0x20];                  /* +0x5000 */
} Ins;

extern u8 D_00470F50[];
extern u8 D_00524C78[];
extern u8 D_00524CA0[];
extern u8 D_00524CB8[];
extern s8 D_00480F2C;                   /* gp - 0x4244 */

extern "C" void  func_131B60(Rec *p, s32 v, s32 n);
extern "C" u32   func_134BB0(u8 *s);
extern "C" void  func_134A98(u8 *d, u8 *s);
extern "C" void  func_14D810(u8 *p, s32 a, s32 b);
extern "C" void  func_14D830(u8 *p);
extern "C" s32   func_14D950(u8 *p, s32 a);
extern "C" void  func_14DAD0(u8 *p);
extern "C" void  func_14DB10(u8 *p, s32 a, s32 b, s32 c);
extern "C" void  func_14DFF0(u8 *p);
extern "C" void *func_14E230(s32 size, u8 *pool);
extern "C" void  func_1867A0(Ent *e, u8 *s, s32 k);
extern "C" void  func_1AFD00(Ent *e, Rec *r);
extern "C" void  func_1C3E80(void *h, s32 a, s32 b);
extern "C" void  func_1CFCD0(void *h, s32 a, Ent *e, s32 b);
extern "C" void *func_1ED3F0(s32 a, s8 b);
extern "C" s32   func_1FDB70(void);
extern "C" void  insect_ModelObjExCtor_4f78f0(Ent *e);
extern "C" s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern "C" void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern "C" s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern "C" void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern "C" s32   insect_InsectBattleBuildNpcPath_50df90(Ins *o, s32 k);
extern "C" s32   insect_InsectFileSlotGetData_511fa0(u8 *p, s32 *out);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(u8 *p);
extern "C" void  insect_InsectFileSlotRelease_512020(u8 *p);
extern "C" void  insect_InsectFileSlotRequest_512140(u8 *p, s32 t, s32 k);

extern "C" void insect_InsectBattleLoadTrainerCharas_4f83f0(Ins *o)
{
    Rec  rA;
    Rec  rE;
    s32  qA;
    s32  qE;
    u8  *t;
    u8  *pool;
    Ent *m;
    s32  n;
    s32  k;

    t = o->fDC;
    pool = o->f7C0;
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        pool = (u8 *)func_1ED3F0(func_1FDB70(), D_00480F2C);
    }
    if (t == 0) {
        return;   /* guard */
    }
    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        D_00480F2C = 1;
        if (insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
            func_14DB10(t, 2, 0, 0x40);
            func_14DFF0(pool);
            func_14D810(pool, func_14D950(t, 0x5000), 0x5000);
            if (func_134BB0(D_00524CB8) < 0x10) {
                func_134A98(pool, D_00524CB8);
            }
            func_14D830(pool);
            func_14DAD0(t);
        }
        m = (Ent *)func_14E230(0x790, pool);
        if (m != 0) {
            insect_ModelObjExCtor_4f78f0(m);
            ((EntRaw *)m)->f1B0 = D_00470F50;
        }
        o->f884 = m;
        insect_InsectFileSlotRequest_512140(o->f5000, insect_InsectBattleBuildNpcPath_50df90(o, 1), 1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 1, -1);
        break;
    case 0xA:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            n = insect_InsectFileSlotGetData_511fa0(o->f5000, &qA);
            func_131B60(&rA, 0, 0x88);
            rA.f30 = 8;
            rA.f2C = rA.f40;
            rA.f3C = 8;
            rA.f38 = rA.f60;
            rA.f00 = n;
            rA.f04 = D_00524C78;
            rA.f08 = pool;
            rA.f0C = pool;
            rA.f10 = pool;
            rA.f14 = 0x242;
            rA.f18 = 1;
            o->f884->f5C();
            func_1AFD00(o->f884, &rA);
            insect_InsectFileSlotRelease_512020(o->f5000);
            insect_InsectBattleSetStep_50d7a0(o, 0x3C, 1, -1);
            func_1CFCD0(o->f870, 0x9B, o->f884, 0);
            func_1C3E80(o->f870, 1, 0x9B);
        }
        break;
    case 0x3C:
        func_1867A0(o->f884, D_00524CA0, 4);
        k = 0xB;
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            k++;
        }
        insect_InsectBattleSetStep_50d7a0(o, k, 1, -1);
        break;
    case 0xB:
        insect_InsectBattleSetFlag_50dad0(o, 8);
        if (insect_InsectBattleTestFlag_50da40(o, 5) != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        }
        break;
    case 0xC:
        D_00480F2C = D_00480F2C + 1;
        insect_InsectBattleSetStep_50d7a0(o, 0xD, 1, -1);
        break;
    case 0xD:
        m = (Ent *)func_14E230(0x790, pool);
        if (m != 0) {
            insect_ModelObjExCtor_4f78f0(m);
            ((EntRaw *)m)->f1B0 = D_00470F50;
        }
        o->f888 = m;
        insect_InsectFileSlotRequest_512140(o->f5000, insect_InsectBattleBuildNpcPath_50df90(o, 0), 1);
        insect_InsectBattleSetStep_50d7a0(o, 0xE, 1, -1);
        break;
    case 0xE:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            n = insect_InsectFileSlotGetData_511fa0(o->f5000, &qE);
            func_131B60(&rE, 0, 0x88);
            rE.f30 = 8;
            rE.f2C = rE.f40;
            rE.f3C = 8;
            rE.f38 = rE.f60;
            rE.f00 = n;
            rE.f04 = D_00524C78;
            rE.f08 = pool;
            rE.f0C = pool;
            rE.f10 = pool;
            rE.f14 = 0x241;
            rE.f18 = 1;
            o->f888->f5C();
            func_1AFD00(o->f888, &rE);
            insect_InsectFileSlotRelease_512020(o->f5000);
            insect_InsectBattleSetStep_50d7a0(o, 0x3C, 1, -1);
            func_1CFCD0(o->f870, 0x8A, o->f888, 0);
            func_1C3E80(o->f870, 1, 0x8A);
            func_1867A0(o->f888, D_00524CA0, 4);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        }
        break;
    }
}
