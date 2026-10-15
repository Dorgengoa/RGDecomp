#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002931a0 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
    s16 m08;         /* +0x8 */
    u8 m0A;         /* +0xA */
    u8 pad00B[0x1];
    s32 m0C;         /* +0xC */
} Obj_FUN_002931a0;

Obj_FUN_002931a0 * UiTextElemInit_2931a0(Obj_FUN_002931a0 *o)
{
    o->m02 = 0;
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
    o->m0A = 0;
    o->m0C = 0;
    return o;
}
