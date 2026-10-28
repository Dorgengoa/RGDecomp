/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSetHp_512ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512EE0 -- 252 bytes, 63 instructions, 5 calls.
 * Clamp a hit value into range, then grade the delta against three
 * thresholds; the sign of the delta flips the grade.
 */

typedef struct Obj {
    u8  pad00[0x1A];
    s16 f1A;                        /* +0x1A */
    s16 f1C;                        /* +0x1C */
    s16 f1E;                        /* +0x1E */
    u8  pad20[0x4D - 0x20];
    s8  f4D;                        /* +0x4D */
    s8  f4E;                        /* +0x4E */
} Obj;

/*rgp*/
/*rgp*/
extern s32  abs(s32 x);

void insect_InsectPieceSetHp_512ee0(Obj *o, s32 v)
{
    s32 r;
    s32 d;

    r = 0x1E;
    if (v <= 0) {
        v = 0;
    }
    if (v >= o->f1E) {
        v = o->f1E;
    }
    if (v <= 0) {
        if (insect_InsectPieceTestStatus_513280(o, 0x23) == 0) {
            insect_InsectPieceSetStatus_5132d0(o, 0x1D);
        } else {
            v = 1;
        }
    }
    o->f1C = v;
    o->f4E = 0;
    d = (s16)(v - o->f1A);
    if (abs(d) < 0xC9) {
        r = 3;
    } else if (abs(d) < 0x65) {
        r = 2;
    } else if (abs(d) < 0x33) {
        r = 1;
    }
    if (d < 0) {
        r = (s16)-r;
    }
    o->f4D = r;
}
