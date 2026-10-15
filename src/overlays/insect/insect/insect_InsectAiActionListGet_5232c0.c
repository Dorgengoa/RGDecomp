#include "types.h"
/* insect 0x5232C0 -- 16 B / 4 words.  `sll $2,$5,2 / addu $2,$2,$4 /
 * lw 0x4($2)`: a plain word-array subscript.  mwcc puts the SCALED INDEX in rs
 * and the base in rt whenever a non-zero displacement is folded into the load;
 * that falls out of `o->m4[i]`, it is not a source-order choice. */

typedef struct Obj {
    u8  pad00[0x4];
    s32 m04[4];              /* +0x4 */
} Obj;

s32 insect_InsectAiActionListGet_5232c0(Obj *o, s32 i)
{
    return o->m04[i];
}
