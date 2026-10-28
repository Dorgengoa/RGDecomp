/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsCageViewStepCage_4f8db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F8DB0 (200 bytes, 50 instructions) -- step the 1..3 tab cursor
 * D_00480464 by `delta` and keep stepping until it lands on a tab whose entry
 * in the availability table is not -1, with a 1000-iteration safety stop.
 *
 * TWO measured spellings carry this unit, and neither survives alone (sweep
 * build/v_im06_8db0.py, 15 arms, 8 inert / 7 live; arming shown by
 * volatile_glob = 29 bad and delta_s16 = len 0xcc vs 0xc8):
 *
 * * D_00480464 is `volatile`.  Without it mwcc CSEs the `lh` issued by the
 *   loop CONDITION into the top of the loop BODY across the back edge, which
 *   is one instruction SHORT (0xc4 vs 0xc8) and shifts a1/a2/a3 by one
 *   register.  Retail RE-LOADS the cursor at the body top -- the `lh` sitting
 *   in the `beql` delay slot is that reload.
 * * Both clamps read the cursor into an s16 LOCAL first.  volatile alone is
 *   29 bad words: it forces a second `lh` in the head (retail issues one and
 *   reuses $3) and it reloads after the body's `sh` instead of sign-extending
 *   the value already in the register.  The local restores both.
 *   `s16 t` WITHOUT volatile is INERT -- byte-identical object to the plain
 *   baseline, so the two spellings are only jointly sufficient.
 *
 * * `sh` then `dsll32/dsra32 ..,16` off the `addu` is the s16 local being
 *   stored and then compared, not an (s16) cast of an s32 local.
 * * The table is read with `lb`, i.e. s8, so the sentinel is -1, not 0xFF.
 * * The clamp is written TWICE, not factored into a helper: the head
 *   materialises 1 and 3 inline with `addiu $2,$0,K`, the body hoists them
 *   into $5/$6 as loop invariants.
 */

extern volatile s16 D_00480464;  /* gp - 0x4D0C */

/*rgp*/
/*rgp*/

void insmenu_InsectVsCageViewStepCage_4f8db0(s32 delta)
{
    s8 *tab;
    s32 i;
    s16 t;

    t = D_00480464;
    if (t >= 4) {
        D_00480464 = 1;
    } else if (t <= 0) {
        D_00480464 = 3;
    }
    tab = ((s8 *)RecordGetCageInsectCountsMaybe_42fec0(*(void **)((u8 *)GetGameData_1fede0() + 0x24)));
    if (tab == 0) {
        return;
    }
    i = 0;
    while (tab[D_00480464 - 1] == -1) {
        t = D_00480464 + delta;
        D_00480464 = t;
        if (t >= 4) {
            D_00480464 = 1;
        } else if (t <= 0) {
            D_00480464 = 3;
        }
        i++;
        if (i >= 1000) {
            break;
        }
    }
}
