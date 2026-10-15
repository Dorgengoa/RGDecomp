#include "types.h"
/* insect 0x00514B10 -- 216 bytes, 54 instructions, 4 calls.
 * The two-arm dispatch is a switch (both compares are `beql` INTO the arm),
 * so the source case order is the compare chain reversed: 8 then 4.
 */

typedef struct Obj {
    u8 pad00[0x3D];
    s8 f3D;                         /* +0x3D */
    u8 pad3E[0x40 - 0x3E];
    s8 f40;                         /* +0x40 */
} Obj;

extern s32 insect_InsectPieceGetStat_512e20(Obj *o, s32 b, s32 c);
extern s32 insect_InsectPieceRollVsResist_512bf0(Obj *o, s32 r, s32 n);
extern void insect_InsectPieceSetStatus_5132d0(Obj *o, s32 k);

s32 insect_InsectPieceTryInflictByFlag_514b10(Obj *o, s32 n, s32 b, s32 mode)
{
    s32 r;

    if (n > 0) {
        r = insect_InsectPieceGetStat_512e20(o, b, 0);
        if (insect_InsectPieceRollVsResist_512bf0(o, r, n) != 0 || n >= 0x270F) {
            switch (mode) {
            case 8:
                insect_InsectPieceSetStatus_5132d0(o, 4);
                if (o->f40 <= 0) {
                    o->f40 = 3;
                }
                break;
            case 4:
                insect_InsectPieceSetStatus_5132d0(o, 1);
                if (o->f3D <= 0) {
                    o->f3D = 3;
                }
                break;
            }
            return 1;
        }
    }
    return 0;
}
