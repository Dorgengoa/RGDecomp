#include "types.h"

/* factory.bin overlay, 0x004FF530 -- clear one 0x10-byte cursor record.
 *
 * ★ `addiu $3, $0, -0x1` is issued FIRST, before the store that uses it: the
 * shared -1 is materialised once and fills the shadow.  Same shape as
 * factory_FactoryMaterialClearRefs_4f3fc0.
 */

typedef struct Cur {
    s32  f0;
    s16  f4;
    s16  f6;
    s16  f8;
    s16  fA;
    s16  fC;
    s16  fE;
} Cur;

void factory_FactoryGroupBaseReset_4ff530(Cur *o)
{
    o->f4 = -1;
    o->f0 = 0;
    o->f6 = 0;
    o->f8 = 0;
    o->fA = 0;
    o->fC = 0;
    o->fE = 0;
}
