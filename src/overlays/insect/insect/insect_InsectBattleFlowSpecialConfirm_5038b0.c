#include "types.h"
/* insect 0x005038B0 -- 664 bytes, 166 instructions.
 *
 * A nine-arm `switch` on insect_InsectBattleGetStep_50d6a0(o, 0).  Every compare is a
 * `beql`/`beq` INTO its arm, so the source case order is the compare chain
 * (0xB, 0xA, 0x22, 8, 7, 0x24, 0x1C, 0x1B, 1) REVERSED, and the arms' block
 * addresses agree: 0x503948 (1) < 0x503980 (0x1B, falling through) <
 * 0x5039A0 (0x1C) < 0x503A38 (0x24) < 0x503AC8 (7) < 0x503B0C (0x22).
 * Cases 8, 0xA and 0xB are EMPTY -- their compares branch straight at the
 * epilogue, and 0xB's annuls the `ld $31`. */

typedef struct Ent {
    u8 pad00[8];
    s8 f8;                          /* +0x08 */
    s8 f9;                          /* +0x09 */
    s8 fA;                          /* +0x0A */
    s8 fB;                          /* +0x0B */
} Ent;

typedef struct Obj {
    u8  pad0000[0x4F90];
    u8  f4F90[1];                   /* +0x4F90 */
    u8  pad4F91[0x4FBC - 0x4F91];
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5B20 - 0x4FBD];
    s32 f5B20;                      /* +0x5B20 */
    u8  pad5B24[0x5B28 - 0x5B24];
    s32 f5B28;                      /* +0x5B28 */
} Obj;

extern void insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 k);
extern s32  insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleClearFlag_50da90(Obj *o, s32 k);
extern s32  insect_InsectCursorSetGetEvents_5119f0(void *p, s32 m);
extern void insect_InsectCursorSetGetCurCell_511a90(void *p, s32 *a, s32 *b);
extern void insect_InsectCursorSetPushPage_511cf0(void *p, s32 a, s32 b);
extern Ent *insect_InsectCursorSetFindPage_511e60(void *p, s32 k);

void insect_InsectBattleFlowSpecialConfirm_5038b0(Obj *o)
{
    s32 v;
    s32 a;
    s32 b;
    Ent *p;
    Ent *q;
    s32 m;
    s32 n;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
        insect_InsectBattleSetState_50d8c0(o, 0x1A, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0x1B:
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
    case 0x1C:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &m, &n);
        v = -1;
        a = 0x22;
        b = 6;
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
            v = m;
        } else {
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                v = 1;
            }
        }
        if (v != -1) {
            if (v == 0) {
                a = 0x24;
                b = 5;
            }
            o->f4FBC = o->f4FBC | 2;
            insect_InsectBattleSetStep_50d7a0(o, a, 0, -1);
            insect_InsectBattlePlaySe_4f45b0(o, b);
        }
        break;
    case 0x24:
        insect_InsectBattleSetStep_50d7a0(o, 0x24, 2, -1);
        insect_InsectBattleSetState_50d8c0(o, 9, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 7, 0, -1);
        p = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB);
        q = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xD);
        q->f8 = p->f8;
        q->f9 = p->f9;
        q->fA = p->fA;
        q->fB = p->fB;
        o->f5B20 = o->f5B28;
        insect_InsectBattleClearFlag_50da90(o, 0x28);
        break;
    case 7:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) {
            insect_InsectBattleSetState_50d8c0(o, 3, 3, -1);
            insect_InsectBattleSetStep_50d7a0(o, 8, 0, -1);
        }
        break;
    case 8:
        break;
    case 0x22:
        insect_InsectBattleSetStep_50d7a0(o, 0x22, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0xA:
        break;
    case 0xB:
        break;
    }
}
