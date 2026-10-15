#include "types.h"
/* insect 0x00510DA0 -- 20 B / 5 words.  Three word clears through the object
 * pointer and then the object is PUBLISHED into the gp context global; the
 * publish lands in the `jr $31` delay slot.
 *
 * `sw $4, -0x1A0($28)` is D_00484FD0, the same context handle that
 * insect_FUN_00510B30 writes and insect_FUN_005109F0 reads. */

typedef struct Obj {
    s32 m00;                    /* +0x00 */
    s32 m04;                    /* +0x04 */
    s32 m08;                    /* +0x08 */
} Obj;

extern void *D_00484FD0;

void insect_InsectHelpInit_510da0(Obj *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
    D_00484FD0 = o;
}
