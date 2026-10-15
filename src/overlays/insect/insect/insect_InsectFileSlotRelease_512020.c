#include "types.h"
/* insect 0x00512020 -- 12 bytes, 3 instructions.  mwcc emits a real `j` tail
 * call with the store in its delay slot. */

typedef struct Obj {
    u8  pad00[0x28];
    s32 m28;                        /* +0x28 */
} Obj;

extern void insect_InsectFileSlotStep_512060(Obj *o);

void insect_InsectFileSlotRelease_512020(Obj *o)
{
    o->m28 = 4;
    insect_InsectFileSlotStep_512060(o);
}
