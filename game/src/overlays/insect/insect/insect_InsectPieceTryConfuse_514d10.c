/* rgp:protos */
#define RGP_SELF_insect_InsectPieceTryConfuse_514d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514D10 -- 172 bytes, 43 instructions.
 * The `dsll32/dsra32 ..,24` off a plain `lb` is an s32 local carrying the
 * incremented counter plus an explicit (s8) cast -- the s8 analogue of
 * [[normal-s16-cast-sign-extension]].
 */

typedef struct Obj {
    u8  pad00[0x3E];
    s8  m3E;                        /* +0x3E */
    u8  pad3F[0x71 - 0x3F];
    s8  m71;                        /* +0x71 */
    s8  m72;                        /* +0x72 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectPieceTryConfuse_514d10(Obj *o, s32 a)
{
    s32 t;

    insect_InsectPieceClearStatus_513340(o, 2);
    if (insect_InsectPieceRollVsResist_512bf0(o, insect_InsectPieceGetStat_512e20(o, 1, 0), a) != 0) {
        o->m72 = o->m71;
        if (insect_InsectPieceIsKing_514b00(o) == 0) {
            o->m3E = 3;
            t = o->m71 + 1;
            o->m71 = t;
            if ((s8)t > 1) {
                o->m71 = 0;
            }
            insect_InsectPieceSetStatus_5132d0(o, 2);
        }
    }
}
