#include "types.h"
/* insect 0x0051D3C0 -- 76 bytes.  A 15-entry scan of the pointer array at +8;
 * a null entry falls through to the increment (`beql` into the increment),
 * a live one is tested `slti .., 0x1A` so the source predicate is `>= 0x1A`. */
typedef struct It {
    u8  pad00[0x14];
    s32 f14;                        /* +0x14 */
} It;

typedef struct Ctx {
    u8   pad00[8];
    It  *arr[0xF];                  /* +0x08 */
} Ctx;

s32 insect_InsectBattleEffectsAnySpecialActive_51d3c0(Ctx *c)
{
    s32 i;

    for (i = 0; i < 0xF; i++) {
        It *p = c->arr[i];
        if (p != 0) {
            if (p->f14 >= 0x1A) {
                return 1;
            }
        }
    }
    return 0;
}
