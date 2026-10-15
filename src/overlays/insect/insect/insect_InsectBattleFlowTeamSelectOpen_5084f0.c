#include "types.h"
/* insect 0x005084F0 -- 380 bytes, 95 instructions. */

typedef struct Sub {
    u8  pad00[4];
} Sub;

typedef struct Ent {
    u8  pad00[8];
    s8  f08;                        /* +0x08 */
    s8  f09;                        /* +0x09 */
    s8  f0A;                        /* +0x0A */
    s8  f0B;                        /* +0x0B */
} Ent;

typedef struct Obj {
    u8  pad0000[0x4F90];
    Sub f4F90;                      /* +0x4F90 */
    u8  pad4F94[0x5EF1 - 0x4F94];
    u8  f5EF1;                      /* +0x5EF1 */
    u8  pad5EF2[0x5EF8 - 0x5EF2];
    s32 f5EF8;                      /* +0x5EF8 */
} Obj;

extern s32 insect_InsectBattleGetStep_50d6a0(Obj *a, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Obj *a, s32 b, s32 c, s32 d);
extern void insect_InsectBattleSetState_50d8c0(Obj *a, s32 b, s32 c, s32 d);
extern s32 insect_InsectBattleTestFlag_50da40(Obj *a, s32 k);
extern s32 insect_InsectBattleGetPoolCount_50db60(Obj *a, s32 k);
extern void insect_InsectCursorSetPageSetScrollMax_511ae0(Sub *s, Ent *e, s32 k, s16 m);
extern void insect_InsectCursorSetPageSetSize_511b80(Sub *s, Ent *e, s32 k, s16 m);
extern void insect_InsectCursorSetPushPage_511cf0(Sub *s, s32 k, s32 m);
extern Ent *insect_InsectCursorSetFindPage_511e60(Sub *s, s32 k);

void insect_InsectBattleFlowTeamSelectOpen_5084f0(Obj *a)
{
    s32 k;
    s32 n;
    s32 w;
    s32 u;
    Ent *e;

    switch (insect_InsectBattleGetStep_50d6a0(a, 0)) {
    case 1:
        k = 1;
        if (insect_InsectBattleTestFlag_50da40(a, 2) != 0) {
            k = 0x11;
        }
        a->f5EF8 = k;
        insect_InsectBattleSetState_50d8c0(a, 7, 2, -1);
        insect_InsectBattleSetStep_50d7a0(a, 0xA, 0, -1);
        insect_InsectCursorSetPushPage_511cf0(&a->f4F90, 1, 1);
        n = insect_InsectBattleGetPoolCount_50db60(a, a->f5EF1);
        w = 0;
        u = (s16)n;
        if (n >= 5) {
            u = 5;
            w = (s16)(n - 5);
        }
        insect_InsectCursorSetPageSetSize_511b80(&a->f4F90, insect_InsectCursorSetFindPage_511e60(&a->f4F90, 1), 1, (s16)u);
        insect_InsectCursorSetPageSetScrollMax_511ae0(&a->f4F90, insect_InsectCursorSetFindPage_511e60(&a->f4F90, 1), 1, (s16)w);
        e = insect_InsectCursorSetFindPage_511e60(&a->f4F90, 1);
        if (e != 0) {
            e->f09 = 0;
            e->f08 = 0;
            e->f0B = 0;
            e->f0A = 0;
        }
        break;
    case 0xA:
        if (insect_InsectBattleGetStep_50d6a0(a, 2) == 0x1A) {
            insect_InsectBattleSetState_50d8c0(a, 7, 0, -1);
        }
        break;
    case 0xB:
        break;
    }
}
