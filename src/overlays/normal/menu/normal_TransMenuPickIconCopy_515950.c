#include "types.h"
/* normal 0x00515950 -- copy the four 0x8..0xE shorts off the source widget
 * onto the destination and force 0x4/0x6 to 0x28.  The `andi 0xFFFF` is the
 * u16 id parameter conversion, not a source mask. */

typedef struct Box {
    u8  pad00[4];
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
} Box;

extern void *D_004846E8;          /* gp - 0xA88 */

extern Box *func_28FE10(void *w, u16 id, s32 a);

void normal_TransMenuPickIconCopy_515950(s32 idx)
{
    Box *dst;
    Box *src;

    dst = func_28FE10(D_004846E8, 0x7553, 0);
    src = func_28FE10(D_004846E8, idx + 0x754F, 0);
    if (dst != NULL) {
        if (src != NULL) {
            dst->f04 = 0x28;
            dst->f06 = 0x28;
            dst->f08 = src->f08;
            dst->f0A = src->f0A;
            dst->f0C = src->f0C;
            dst->f0E = src->f0E;
        }
    }
}
