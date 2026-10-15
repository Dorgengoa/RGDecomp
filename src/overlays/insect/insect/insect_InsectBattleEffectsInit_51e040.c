#include "types.h"
/* insect 0x0051E040 -- 56 bytes.  A constructor: two words, a 15-entry s32
 * array at +0x08 (0x08 + 15*4 = 0x44), then a zero and a 1.0f.  The 1.0f goes
 * out as `lui 0x3F80` / `sw`, i.e. a float constant materialised in a GPR. */

typedef struct Obj {
    s32 m00;                        /* +0x00 */
    s32 m04;                        /* +0x04 */
    s32 m08[15];                    /* +0x08 */
    s32 m44;                        /* +0x44 */
    f32 m48;                        /* +0x48 */
} Obj;

void insect_InsectBattleEffectsInit_51e040(Obj *o)
{
    s32 i;

    o->m00 = 0;
    o->m04 = 0;
    for (i = 0; i < 15; i++) {
        o->m08[i] = 0;
    }
    o->m44 = 0;
    o->m48 = 1.0f;
}
