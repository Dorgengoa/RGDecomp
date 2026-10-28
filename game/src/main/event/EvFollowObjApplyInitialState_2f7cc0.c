/* rgp:protos */
#define RGP_SELF_EvFollowObjApplyInitialState_2f7cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (48 B each): EvFollowObjApplyInitialState_2f7cc0 /
   ObjTypeMonographApplyInitialState_372210.  `sltu $3, $0, $3` then `xori $3, $3, 1` is the bool round
   trip from [[levers.d/mwcc-cpp-bool-narrowing]]: `(((x & M) != 0) ^ 1) != 0`
   materialises the test as a VALUE where a plain `(x & M) == 0` branches on it
   directly and comes out two words short. */

typedef struct Flags {
    u8  pad000[0xD0];
    u32 mD0;
} Flags;

void EvFollowObjApplyInitialState_2f7cc0(Flags *f)
{
    if ((((f->mD0 & 0x80000000) != 0) ^ 1) != 0) {
        f->mD0 |= 0x40000000;
    }
}
