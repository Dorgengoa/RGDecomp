/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePoisonTick_50f220 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x0050F220 -- 120 B / 30 words.
 *
 * $17 holds the object across three calls, $16 holds `n`.  The first call
 * takes $4 UNTOUCHED from entry (the `daddu $17,$4,$0` does not clobber it and
 * the jal's delay slot is a nop), so it takes the same object.
 *
 * `beql $2,$0` to the epilogue is the `!= 0` guard's fall-through.  The div
 * takes `mflo`, so it is a `/` and carries the trap.  0x80408080 is a u32
 * literal, hence lui/ori. */

typedef struct F220Obj { u8 pad00[0x1E]; s16 m1E; } F220Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattlePoisonTick_50f220(F220Obj *o)
{
    s32 n;

    if (o != 0) {
        if (insect_InsectPieceIsPoisoned_514c70(o) != 0) {
            n = o->m1E / 10 + 1;
            insect_InsectPieceDamageHp_514fd0(o, n);
            insect_InsectBattleDamagePopupSpawn_50f730(o, n, 0x80408080);
        }
    }
}
