#include "types.h"
/* insect 0x004F8E50 -- a four-arm `insect_InsectBattleGetStep_50d6a0(o, 1)` state dispatch,
 * the same family as the already-matched insect_FUN_004F7530 (whose Rec
 * descriptor, fill order and Ins layout transfer verbatim).
 *
 * The compare chain is 0xB, 0x1C, 0x1B, 1 and every test is `beql` INTO the
 * arm, so the source case order is the REVERSE: 1, 0x1B, 0x1C, 0xB.  The arm
 * addresses ascend in exactly that order (0x4F8EB0, 0x4F8ED4, 0x4F8F18,
 * 0x4F9068).
 *
 * jalr.json calls this "vptr 0x1B0 + 0x3010" but there is only ONE class:
 * 0x17B0 + 3 * 0x790 == 0x2E60 and 0x2E60 + 0x1B0 == 0x3010, so the second
 * site is arr[3]'s own vptr with the base folded into the displacement.
 * Slots 0x50 and 0x5C are virtuals #18 and #21 (8 + 4*N).
 *
 * D_00484FA8 is the gp window: gp - 0x1C8, the neighbour of
 * insect_FUN_00502C20's D_00484FA0 (gp - 0x1D0).
 */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18();               /* slot 0x50 */
    virtual void s19(); virtual void s20();
    virtual void s21();               /* slot 0x5C */
};

typedef struct Rec {
    s32 f00;                        /* +0x00 */
    u8 *f04;                        /* +0x04 */
    u8 *f08;                        /* +0x08 */
    u8 *f0C;                        /* +0x0C */
    u8 *f10;                        /* +0x10 */
    s32 f14;                        /* +0x14 */
    s32 f18;                        /* +0x18 */
    u8  pad1C[0x2C - 0x1C];
    u8 *f2C;                        /* +0x2C */
    s32 f30;                        /* +0x30 */
    u8  pad34[0x38 - 0x34];
    u8 *f38;                        /* +0x38 */
    s32 f3C;                        /* +0x3C */
    u8  f40[0x60 - 0x40];           /* +0x40 */
    u8  f60[0x90 - 0x60];           /* +0x60 */
} Rec;

typedef struct EL {
    u8 pad000[0x790];
} EL;

typedef struct Ins {
    u8 pad000[0x660];
    u8 f660[0x17B0 - 0x660];        /* +0x0660 */
    EL arr[4];                      /* +0x17B0, stride 0x790 */
    u8 pad35F0[0x5000 - 0x35F0];
    u8 f5000[0x20];                 /* +0x5000 */
} Ins;

extern s32 D_00484FA8;              /* gp window: PLAIN, never const */
extern u8  D_00524140[];
extern u8  D_00524C78[];

extern "C" void func_1343B8(void *d, const u8 *t, s32 v);
extern "C" void func_131B60(Rec *p, s32 v, s32 n);
extern "C" void func_14DAD0(u8 *p);
extern "C" void func_14DB10(u8 *p, s32 a, s32 b, s32 c);
extern "C" void func_14DE90(u8 *p);
extern "C" void func_1AFD00(EL *s, Rec *r);
extern "C" void func_1AFF40(EL *a, EL *b, u8 *t);
extern "C" s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern "C" void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern "C" void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern "C" s32  insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern "C" s32  insect_InsectFileSlotGetData_511fa0(u8 *p, s32 *out);
extern "C" s32  insect_InsectFileSlotIsLoaded_512010(u8 *p);
extern "C" void insect_InsectFileSlotRelease_512020(u8 *p);
extern "C" void insect_InsectFileSlotRequest_512140(u8 *p, u8 *t, s32 k);

extern "C" void insect_InsectBattleLoadMarkerModels_4f8e50(Ins *o)
{
    s32 q;
    u8  buf[0x2C];
    Rec r;
    u8 *t;
    s32 n;
    s32 k;
    EL *e;
    EL *g;

    t = (u8 *)o + 0x660;

    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        D_00484FA8 = 0;
        func_14DE90(t);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 1, -1);
        break;
    case 0x1B:
        func_1343B8(buf, D_00524140, 0x14D - D_00484FA8);
        insect_InsectFileSlotRequest_512140(o->f5000, buf, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 1, -1);
        break;
    case 0x1C:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            e = &o->arr[D_00484FA8];
            func_14DB10(t, 2, 0, 0x40);
            n = insect_InsectFileSlotGetData_511fa0(o->f5000, &q);
            func_131B60(&r, 0, 0x88);
            r.f2C = r.f40;
            r.f30 = 8;
            r.f3C = 8;
            r.f38 = r.f60;
            r.f00 = n;
            r.f04 = D_00524C78;
            r.f14 = 0x29C;
            r.f08 = t;
            r.f0C = t;
            r.f10 = t;
            r.f18 = 0;
            ((VE *)e)->s21();
            func_1AFD00(e, &r);
            if (D_00484FA8 == 2) {
                g = &o->arr[3];
                ((VE *)g)->s21();
                ((VE *)g)->s18();
                func_1AFF40(e, g, t);
            }
            func_14DAD0(t);
            insect_InsectFileSlotRelease_512020(o->f5000);
            k = 0xB;
            if (D_00484FA8 < 2) {
                k = 0x1B;
            }
            insect_InsectBattleSetStep_50d7a0(o, k, 1, -1);
            D_00484FA8 = D_00484FA8 + 1;
        }
        break;
    case 0xB:
        if (insect_InsectBattleTestFlag_50da40(o, 5) != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        }
        break;
    }
}
