/* rgp:protos */
#define RGP_SELF_MenuShowPlayTime_298a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MenuShowPlayTime_298a40 -- window 0x00296000-0x0029C000.  Four-out-parameter
   query (PlayTimeGet_28aeb0) whose first result picks between two panel messages.

   Readings:
     * `beql $16,$0` PAST the body -> fall-through is the if BODY -> positive
       `if (p != 0)`.
     * `slti $1,$2,0x64` + `bnel $1,$0` PAST the 3-arm -> if/else-if chain,
       cases AS WRITTEN, and the test that FALLS THROUGH is the one written
       first: `if (n > 99) { m10 = 3; ...0xE7 } else { m10 = 2; ...0xF1 }`.
     * THE COMPARE MUST BE THE STRICT `n > 0x63`, NOT `n >= 0x64`.  Both emit
       `slti ..,0x64`, but `>=` puts the result in $2 and `>` puts it in $at,
       which is retail's `slti $1,$2,0x64` / `bnel $1,$0`.  MEASURED, 5 arms in
       one round trip: `n > 0x63` MATCH and `0x63 < n` is the SAME object
       (5abc4f53); `n >= 0x64` and `!(n < 0x64)` are the same object the other
       way (e14bfa0b, 2 bad); `(u8)(n > 0x63) != 0` is two words LONG.  This is
       [[insect-scheduler-tiebreak]]'s `$at`-compare lever (`b > 1` beat
       `b >= 2` there) and it TRANSFERS FROM INSECT TO MAIN.
     * the four out-parameters are address-taken locals at sp+0x2C/28/24/20;
       mwcc allocates stack locals in REVERSE declaration order, so they are
       declared n, b, c, d (n highest).  The fourth is written by the callee
       and never read -- it still needs its slot.
     * `lw 0x2C($29)` appears TWICE (once per arm, in the branch delay slots):
       an address-taken local is RE-LOADED at every use, so `n` is read again
       after the call as one source read.
     * `sd $3` from an `lw`-loaded value means the destination fields at
       0x08 / 0x28 / 0x48 are 64-BIT.  */

typedef struct Obj98A40 {
    u8 pad00[0x8];
    s64 m08;                 /* +0x08, sd */
    s16 m10;                 /* +0x10, sh */
    u8 pad12[0x16];
    s64 m28;                 /* +0x28, sd */
    u8 pad30[0x18];
    s64 m48;                 /* +0x48, sd */
} Obj98A40;

/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_004DB1B0[];

void MenuShowPlayTime_298a40(s32 id)
{
    Obj98A40 *p;
    s32 n;
    s32 b;
    s32 c;
    s32 d;

    p = UiGetWidgetSubItem_28f2b0(D_004DB1B0, id, 0);
    if (p != 0) {
        PlayTimeGet_28aeb0(&n, &b, &c, &d);
        if (n > 0x63) {
            p->m10 = 3;
            UiSetSpriteX_28fcd0(D_004DB1B0, 0x33, 0xE7, 4);
        } else {
            p->m10 = 2;
            UiSetSpriteX_28fcd0(D_004DB1B0, 0x33, 0xF1, 4);
        }
        p->m08 = n;
        p->m28 = b;
        p->m48 = c;
    }
}
