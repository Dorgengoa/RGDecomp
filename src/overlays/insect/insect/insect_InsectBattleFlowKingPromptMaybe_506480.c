#include "types.h"
/* insect 0x00506480 -- 476 bytes, 119 instructions. */

typedef struct Obj {
    u8  pad0000[0x4F90];
    u8  f4F90[0x2C];                /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5DA8 - 0x4FBD];
    s32 f5DA8;                      /* +0x5DA8 */
    u8  pad5DAC[0x5EF1 - 0x5DAC];
    u8  f5EF1;                      /* +0x5EF1 */
    u8  pad5EF2[0x5EF8 - 0x5EF2];
    s32 f5EF8;                      /* +0x5EF8 */
} Obj;

extern s32 insect_InsectBattleTestFlag_50da40(Obj *o, s32 k);
extern void insect_InsectBattleClearFlag_50da90(Obj *o, s32 k);
extern void insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern s32 insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern s32 insect_InsectCursorSetGetEventsExcept_5119b0(void *p, s32 m);
extern void insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 k);

void insect_InsectBattleFlowKingPromptMaybe_506480(Obj *o)
{
    s32 a;
    s32 b;

    if (o->f5DA8 != 0) {
        if (insect_InsectBattleTestFlag_50da40(o, 0x38) == 0) {
            insect_InsectBattleClearFlag_50da90(o, 0x1E);
            o->f5EF8 = 0x11;
            a = 14;
            b = 10;
            if (o->f5EF1 == 0) {
                b = 1;
                a = 0x22;
                o->f5EF1 = 1;
            } else {
                o->f5EF1 = 0;
            }
            if (o->f5EF1 != 0) {
                o->f4FBC |= 1;
            } else {
                o->f4FBC &= 0xFE;
            }
            if (a == 14) {
                insect_InsectBattleSetState_50d8c0(o, 15, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x1E, 2, -1);
            }
            insect_InsectBattleSetState_50d8c0(o, a, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, b, 0, -1);
            return;
        }
    }
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetStep_50d7a0(o, 10, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, 14, 2, -1);
        insect_InsectBattleClearFlag_50da90(o, 0x1E);
        o->f4FBC |= 2;
        if (insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
            o->f5EF8 = 1;
        }
        break;
    case 10:
        break;
    case 5:
        if (insect_InsectCursorSetGetEventsExcept_5119b0(o->f4F90, 0x4000) != 0) {
            insect_InsectBattlePlaySe_4f45b0(o, 5);
            insect_InsectBattleSetStep_50d7a0(o, 10, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
        }
        break;
    }
}
