#include "types.h"
/* insect 0x00501FF0 -- 400 bytes, 100 instructions, 14 calls.
 * A five-arm switch (every compare is `beql` INTO the arm, so the source case
 * order is the compare chain reversed: 1, 2, 3, 4, 5).  `case 2` is an empty arm.
 */

typedef struct Obj {
    u8 pad00[0x4F90];
    u8 f4F90;                       /* +0x4F90 */
    u8 pad4F91[0x4FBC - 0x4F91];
    u8 f4FBC;                       /* +0x4FBC */
} Obj;

extern s32  insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern void insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectCursorSetGetCurCell_511a90(u8 *p, s32 *a, s32 *b);
extern s32  insect_InsectCursorSetGetEvents_5119f0(u8 *p, s32 m);
extern void insect_InsectBattleSetFlag_50dad0(Obj *o, s32 k);
extern void insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 k);
extern void insect_InsectCursorSetSetSize_511bd0(u8 *p, s32 a, s32 b);

void insect_InsectBattleFlowSelectFirstTurn_501ff0(Obj *o)
{
    s32 x;
    s32 y;
    s32 r;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 0x1E, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
        break;
    case 2:
        break;
    case 3:
        insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
        o->f4FBC |= 0x10;
        break;
    case 4:
        insect_InsectCursorSetGetCurCell_511a90(&o->f4F90, &x, &y);
        r = -1;
        if (insect_InsectCursorSetGetEvents_5119f0(&o->f4F90, 0x80) != 0) {
            r = 5;
            if (y != 0) {
                insect_InsectBattleSetFlag_50dad0(o, 0x47);
            }
            insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 4, 2, -1);
        } else if (insect_InsectCursorSetGetEvents_5119f0(&o->f4F90, 0x20) != 0) {
            r = 0x2B;
        }
        insect_InsectBattlePlaySe_4f45b0(o, r);
        break;
    case 5:
        o->f4FBC &= ~0x10;
        insect_InsectBattleSetFlag_50dad0(o, 0x46);
        insect_InsectCursorSetSetSize_511bd0(&o->f4F90, 2, 1);
        o->f4FBC |= 2;
        insect_InsectBattleSetState_50d8c0(o, 0xF, 0, -1);
        break;
    }
}
