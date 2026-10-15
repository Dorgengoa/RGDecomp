#include "types.h"
/* insect 0x522C30 -- 20 B / 5 words.  `beqz $5, L / nop / sw $5, 0x70($4)`:
 * a guarded setter.  The guard is a plain `beqz` with a NOP in the delay slot,
 * not a `bnel` with the store in it, so it is a straight `if (v != 0) { ... }`
 * whose body mwcc did not sink. */

typedef struct Obj {
    u8  pad00[0x70];
    s32 m70;                 /* +0x70 */
} Obj;

void insect_InsectAiSetHeap_522c30(Obj *o, s32 v)
{
    if (v != 0) {
        o->m70 = v;
    }
}
