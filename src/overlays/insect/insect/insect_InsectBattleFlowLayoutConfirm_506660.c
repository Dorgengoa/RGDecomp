#include "types.h"
/* insect 0x00506660 -- 348 bytes, 87 instructions, 10 calls.
 * A four-arm switch: every compare is `beql` INTO the arm, so the source case
 * order is the compare chain reversed (1, 0xA, 0x1C, 0xB).  Case 0xB leaves
 * through the function's own `return`, case 0xA through the switch's `break`.
 */

typedef struct Obj {
    u8 pad00[0x4F90];
    u8 f4F90;                       /* +0x4F90 */
    u8 pad4F91[0x4FBC - 0x4F91];
    u8 f4FBC;                       /* +0x4FBC */
} Obj;

extern void insect_InsectCursorSetGetCurCell_511a90(u8 *p, s32 *a, s32 *b);
extern s32  insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern void insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void insect_InsectCursorSetGetCell_511a40(u8 *p, s32 k, s32 *a, s32 *b);
extern s32  insect_InsectCursorSetGetEvents_5119f0(u8 *p, s32 m);
extern void insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 k);

void insect_InsectBattleFlowLayoutConfirm_506660(Obj *o)
{
    s32 x;
    s32 y;
    s32 u;
    s32 v;
    s32 t;
    s32 r;
    s32 w;
    s32 k;

    insect_InsectCursorSetGetCurCell_511a90(&o->f4F90, &x, &y);
    t = insect_InsectBattleGetStep_50d6a0(o, 0);
    if (t == 0xB) {
        return;
    }
    switch (t) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 0xD, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0xA:
        break;
    case 0x1C:
        insect_InsectCursorSetGetCell_511a40(&o->f4F90, 8, &u, &v);
        r = -1;
        if (insect_InsectCursorSetGetEvents_5119f0(&o->f4F90, 0x80) != 0) {
            r = x;
        } else if (insect_InsectCursorSetGetEvents_5119f0(&o->f4F90, 0x20) != 0) {
            r = 1;
        }
        if (r == -1) {
            break;
        }
        w = 0x1D;
        k = 5;
        if (r != 0) {
            o->f4FBC |= 2;
            k = 6;
            w = 0x1E;
        }
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, w, 2, -1);
        insect_InsectBattlePlaySe_4f45b0(o, k);
        break;
    }
}
