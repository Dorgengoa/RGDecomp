#include "types.h"
/* insect 0x0050DA40 -- 72 bytes, 18 instructions, a leaf with no frame.
 * A 64-bit bitset: `bgez`/`addiu 0x1F`/`sra 5` is a signed `/ 32` and
 * `andi 0x1F`/`addiu -0x20` a signed `% 32`.  The `and` is 64-bit, so the
 * s32 return needs the `dsll32/dsra32 ..,0` normalisation.
 */

typedef struct Obj {
    u8  pad0000[0x5DB8];
    s64 m5DB8[1];                   /* +0x5DB8 */
} Obj;

s32 insect_InsectBattleTestFlag_50da40(Obj *o, s32 i)
{
    return o->m5DB8[i / 32] & (1 << (i % 32));
}
