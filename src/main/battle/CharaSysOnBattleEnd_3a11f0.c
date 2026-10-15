#include "types.h"

typedef struct {
    u8 pad0[0x28];
    s32 unk28;
    u8 pad2c[0x168 - 0x2c];
    s16 unk168;
    u8 pad16a[0x188 - 0x16a];
    u64 unk188;
    u8 pad190[0x1C8 - 0x190];
    s32 unk1C8;
} Sub;

typedef struct {
    u8 pad0[4];
    u8 f4_0 : 1;
    u8 f4_1 : 1;
    u8 f4_2 : 1;
    u8 f4_3 : 5;
    u8 pad5[0x238 - 5];
    Sub *unk238;
    u8 pad23c[0x248 - 0x23C];
    s32 unk248;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 3;
} Obj;

typedef struct {
    u8 pad0[0xC];
    struct { u8 pad0[8]; f64 unk8; } *unkC;
} Ctx;

extern void FieldHudLogClose_203fa0(void);
extern void CharaSysStatusExpireAll_3a1550(Obj *);
extern void BattleCalcResults_3a2100(Obj *);
extern void CharaSysEventLogReset_3a33e0(Obj *);
extern void CharaSysEncounterDistRoll_3a59d0(Obj *, s32);
extern void BattleHistoryPush_3a7e70(void *, void *);
extern Ctx *D_004837C0;

s32 CharaSysOnBattleEnd_3a11f0(Obj *arg0, s32 arg1)
{
    if (D_004837C0 == NULL) {
        return 0;
    }
    if (!arg0->b0) {
        return 0;
    }
    arg0->b0 = 0;
    CharaSysStatusExpireAll_3a1550(arg0);
    arg0->b4 = 0;
    arg0->b2 = 0;
    arg0->f4_2 = 1;
    if (arg1 == 1) {
        BattleCalcResults_3a2100(arg0);
    }
    if (arg0->unk238 != NULL) {
        arg0->unk238->unk168 = arg1;
        arg0->unk238->unk188 = D_004837C0->unkC->unk8;
        if (arg1 == 1) {
            arg0->unk238->unk1C8 = arg0->unk248;
        } else {
            arg0->unk238->unk1C8 = 0;
        }
    }
    if (arg0->unk238 != NULL) {
        arg0->unk238->unk28 = -1;
    }
    if (arg0->unk238 != NULL) {
        BattleHistoryPush_3a7e70((u8 *)arg0 + 0x28, (u8 *)arg0->unk238 + 0x168);
    }
    FieldHudLogClose_203fa0();
    CharaSysEventLogReset_3a33e0(arg0);
    CharaSysEncounterDistRoll_3a59d0(arg0, 1);
    return 1;
}
