/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateCallStep_4ebf50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EBF50 (196 bytes, 52 instructions) -- the 0.818 relative of
 * insmenu_InsectVsStateCallCursorMove_4ebe30: the same "forward to the record's handler" shape with
 * three more arguments and one more source of them.
 *
 * ★★★★★ ELEVEN arguments.  `$4..$11` is the PS2 EABI's full register set and
 * the `sd $2, 0x0/0x8/0x10($29)` run is arguments 9, 10 and 11 in EIGHT-byte
 * stack slots with no shadow area.  Each is `lw` (32-bit, sign-extended) then
 * `sd` -- an s32 argument widened into its slot, not an s64 value.
 *
 * ★ The three slots come from func_430940's out-parameters.  They are read
 * exactly once each and passed straight on, so they are plain locals here;
 * the `volatile` treatment insmenu_InsectVsMenuStateConfirm_4eb230 needs is for the case where a
 * compare chain and its arms read the same slot.
 *
 * ★ `ok = 1;` goes AFTER the calls, in the guard's delay slot -- see
 * insmenu_InsectVsStateCallCursorMove_4ebe30 for why: written earlier it is live across a call and
 * costs a callee-saved register.
 */

typedef u8 (*Handler)(void *a, void *b, s32 p0, s32 p1, s32 p2, s32 p3,
                      s32 p4, s32 p5, s32 q0, s32 q1, s32 q2);

typedef struct Rec {
    u8 pad00[8];
    Handler f8;
} Rec;

typedef struct Owner {
    u8 pad00[0x24];
    void *f24;
} Owner;

/*rgp*/

/*rgp*/
/*rgp*/

s32 insmenu_InsectVsStateCallStep_4ebf50(void *a, void *b)
{
    s32 v0, v1, v2, v3, v4, v5;
    s32 w0, w1, w2;
    Rec *r;
    s32 ok;

    r = ((Rec *)insmenu_InsectVsStateRowFind_4ec020(&v0, &v1, &v2, &v3, &v4, &v5));
    RecordGetPayloadIdsMaybe_430940(((Owner *)GetGameData_1fede0())->f24, &w0, &w1, &w2);
    ok = 1;
    if (r != 0) {
        if (r->f8 != 0) {
            ok = r->f8(a, b, v0, v1, v2, v3, v4, v5, w0, w1, w2);
        }
    }
    return ok != 0;
}
