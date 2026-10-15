#include "types.h"
/* insect 0x00522310 -- 428 bytes, 107 instructions, jump table at
 * jtbl_00525750 (0x11 entries). */

typedef struct P1 {
    u8  pad00[0x58];
    void *f58;                      /* +0x58 */
} P1;

typedef struct P2 {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x38 - 0x19];
    s8  f38;                        /* +0x38 */
} P2;

typedef struct P3 {
    u8  pad00[4];
} P3;

extern s32 insect_InsectPieceRollVsResist_512bf0(P3 *p, s32 h, s32 k);
extern s32 insect_InsectPieceGetStat_512e20(P3 *p, s32 k, s32 m);
extern s32 insect_InsectPieceIsKing_514b00(P2 *p);
extern void insect_InsectBoardPickMoveCell_4edd90(void *o, P2 *b, P3 *c, void **e, void **f,
                                s8 m);
extern s32 insect_InsectBoardAbilityFindTarget_4ef0f0(void *o, P2 *b, void *d, void *e, void *f,
                               s32 *px, s32 *py, s32 z);

s8 insect_InsectAiSpecialCanHit_522310(P1 *p1, P2 *p2, P3 *p3, void *d, void **e, void **f)
{
    s32 sx;
    s32 sy;
    s32 k;
    s32 m;

    if (p2 == 0 || p3 == 0 || d == 0) {
        return 0;
    }
    k = 0;
    m = 0;
    switch (p2->f38) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        k = 1;
        break;
    case 6:
    case 7:
    case 0xB:
    case 0xC:
    case 0xE:
        k = 0;
        break;
    case 8:
    case 0xD:
        k = (s8)insect_InsectPieceRollVsResist_512bf0(p3, insect_InsectPieceGetStat_512e20(p3, 0, 0), p2->f18);
        break;
    case 9:
        k = (s8)insect_InsectPieceRollVsResist_512bf0(p3, insect_InsectPieceGetStat_512e20(p3, 1, 0), p2->f18);
        break;
    case 0xF:
        k = 1;
        m = 1;
        break;
    case 0x10:
        k = 1;
        m = 1;
        break;
    }
    if (insect_InsectPieceIsKing_514b00(p2) == 0) {
        m = 1;
    }
    insect_InsectBoardPickMoveCell_4edd90(p1->f58, p2, p3, e, f, (s8)m);
    if (k != 0) {
        if (insect_InsectBoardAbilityFindTarget_4ef0f0(p1->f58, p2, d, e[0], f[0], &sx, &sy, 0) != 0) {
            k = 1;
        } else {
            k = 0;
        }
    }
    return (s8)k;
}
