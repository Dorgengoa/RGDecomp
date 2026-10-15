#include "types.h"
/* insect 0x005045F0 -- 340 bytes, 85 instructions. */

typedef struct Sub {
    u8  pad00[4];
} Sub;

typedef struct Obj {
    u8  pad0000[0x4F90];
    Sub f4F90;                      /* +0x4F90 */
    u8  pad4F94[0x4FBC - 0x4F94];
    u8  f4FBC;                      /* +0x4FBC */
} Obj;

extern void insect_InsectBattlePlaySe_4f45b0(Obj *a, s32 k);
extern s32 insect_InsectBattleGetStep_50d6a0(Obj *a, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Obj *a, s32 b, s32 c, s32 d);
extern void insect_InsectBattleSetState_50d8c0(Obj *a, s32 b, s32 c, s32 d);
extern void insect_InsectCursorSetGetCurCell_511a90(Sub *s, s32 *p, s32 *q);
extern void insect_InsectCursorSetPushPage_511cf0(Sub *s, s32 k, s32 m);
extern s32 insect_InsectCursorSetGetEvents_5119f0(Sub *s, s32 k);

void insect_InsectBattleFlowGiveUpConfirm_5045f0(Obj *a)
{
    s32 v0;
    s32 v1;
    s32 n;
    s32 q;
    s32 s;

    switch (insect_InsectBattleGetStep_50d6a0(a, 0)) {
    case 0xA:
        break;
    case 1:
        insect_InsectBattleSetState_50d8c0(a, 0x16, 2, -1);
        insect_InsectBattleSetStep_50d7a0(a, 0xA, 0, -1);
        insect_InsectCursorSetPushPage_511cf0(&a->f4F90, 7, 1);
        a->f4FBC = a->f4FBC & 0xFD;
        break;
    case 0x49:
        insect_InsectCursorSetGetCurCell_511a90(&a->f4F90, &v0, &v1);
        n = -1;
        q = 5;
        s = 0x4B;
        if (insect_InsectCursorSetGetEvents_5119f0(&a->f4F90, 0x80) != 0) {
            n = v0;
        } else if (insect_InsectCursorSetGetEvents_5119f0(&a->f4F90, 0x20) != 0) {
            n = 1;
        }
        if (n != -1) {
            if (n != 0) {
                q = 6;
                s = 0x4A;
            }
            insect_InsectBattleSetStep_50d7a0(a, 0xA, 0, -1);
            insect_InsectBattleSetStep_50d7a0(a, s, 2, -1);
            insect_InsectBattlePlaySe_4f45b0(a, q);
        }
        break;
    case 0xB:
        break;
    }
}
