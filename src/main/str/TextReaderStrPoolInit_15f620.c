#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0015f620 {
    u8 pad000[0x18];
    s32 m18;         /* +0x18 */
    s32 m1C;         /* +0x1C */
    s32 m20;         /* +0x20 */
} Obj_FUN_0015f620;

void TextReaderStrPoolInit_15f620(Obj_FUN_0015f620 *o, s32 p1, s32 p2)
{
    o->m20 = p1;
    o->m18 = p2;
    o->m1C = o->m20;
}
