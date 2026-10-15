#include "types.h"
/* insect 0x00522A50 -- 56 B / 14 words.  Exact twin of insect_InsectAiGetStep_5229a0
 * against the FIRST of the record's two 5-element s32 arrays (+0x00). */
typedef struct Ins {
    s32 f00[5];                     /* +0x00 */
    s32 f14[5];                     /* +0x14 */
} Ins;

s32 insect_InsectAiGetState_522a50(Ins *o)
{
    s32 i;
    s32 v;

    for (i = 4; i >= 0; i--) {
        v = o->f00[i];
        if (v != -1) {
            return v;
        }
    }
    return -1;
}
