#include "types.h"

/* Member of the 2-member BYTE-IDENTICAL group headed by EvFollowObjApplyInitialState_2f7cc0; the shape and
   every lever are documented there.  `sltu $3, $0, $3` then `xori $3, $3, 1` is the bool round
   trip from [[levers.d/mwcc-cpp-bool-narrowing]]: `(((x & M) != 0) ^ 1) != 0`
   materialises the test as a VALUE where a plain `(x & M) == 0` branches on it
   directly and comes out two words short. */

typedef struct Flags {
    u8  pad000[0xD0];
    u32 mD0;
} Flags;

void ObjTypeMonographApplyInitialState_372210(Flags *f)
{
    if ((((f->mD0 & 0x80000000) != 0) ^ 1) != 0) {
        f->mD0 |= 0x40000000;
    }
}
