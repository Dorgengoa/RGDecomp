/* rgp:protos */
#define RGP_SELF_insect_InsectAiPushStep_522930 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522930 -- 104 bytes, 26 instructions, no calls.
 *
 * A 5-slot ring at index 5..9.  The first loop carries TWO pointer locals --
 * `p = a + i` (whose load folds the +0x14 into its displacement) and
 * `q = p + 5` (the base of the store) -- which is the shape retail emits
 * (`addu $2,$4,$2` / `addiu $6,$2,0x14` / `lw $2,0x14($2)` / `sw $5,0x0($6)`).
 */

s32 insect_InsectAiPushStep_522930(s32 *a, s32 v)
{
    s32  i;
    s32 *p;
    s32 *q;

    for (i = 0; i < 5; i++) {
        p = a + i;
        q = p + 5;
        if (p[5] == -1) {
            *q = v;
            return 1;
        }
    }
    for (i = 0; i < 4; i++) {
        a[i + 5] = a[i + 6];
    }
    a[9] = v;
    return 0;
}
