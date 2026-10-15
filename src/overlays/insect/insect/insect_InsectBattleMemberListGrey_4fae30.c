#include "types.h"
/* insect 0x004FAE30 -- 204 bytes, 51 instructions, 5 calls.
 *
 * The colour is built by `ori`/`dsll`/`ori` (a ZERO-extended 64-bit value) and
 * sign-extended by `dsll32`/`dsra32 ..,0` at the JOIN, which is what a `u32`
 * local converted to an `s32` argument looks like -- a plain `s32 c` would be
 * materialised with `lui`/`ori` and need no conversion at all.  The same
 * `dsll32`/`dsra32 ..,0` on the tail call's fourth argument is why
 * insect_InsectTeamCountPlaced_5137c0 is declared returning `u32` here.
 */

typedef struct Ctx {
    u8  pad00[0x878];
    s32 m878;                       /* +0x878 */
} Ctx;

extern void *insect_InsectTeamGetPiece_5138d0(void *a, s32 i);
extern s32   insect_InsectPieceTestStatus_513280(void *p, s32 k);
extern s64   insect_InsectTeamCountPlaced_5137c0(void *a);
extern void  func_290A40(s32 h, s32 id, s32 col, s32 i);
extern void  func_291250(s32 h, s32 id, s32 a, s32 v);

void insect_InsectBattleMemberListGrey_4fae30(Ctx *g, void *s)
{
    s32 i;
    u64 c;
    void *p;

    if (s != 0) {
        for (i = 0; i < 5; i++) {
            p = insect_InsectTeamGetPiece_5138d0(s, i);
            if (p != 0) {
                c = 0xFF7F7F7F;
                if (insect_InsectPieceTestStatus_513280(p, 0x21) != 0) {
                    c = 0xFF202020;
                }
                func_290A40(g->m878, 0x7545, c, i);
            }
        }
        func_291250(g->m878, 0x753D, 0, insect_InsectTeamCountPlaced_5137c0(s));
    }
}
