#include "types.h"

/* factory.bin overlay, 0x004FFA30 -- 84 bytes / 21 words, 3 branches, 0 calls.
 * Sum the 0x06 field over the part list at `0x2AC` (0xC stride, count `0x2B0`),
 * truncating the accumulator to 16 bits AFTER EVERY ADD.
 *
 * Sub-family B of lane fy04 with `factory_FactoryBeltHasRoom_500d30` (same walk, no
 * truncation, different tail).
 *
 * * `dsll32 $2,16 / dsra32 $2,16` INSIDE the loop is an s32 accumulator with an
 *   explicit `(s16)` cast on the sum ([[normal-s16-cast-sign-extension]]); an
 *   `s16 sum` is the measured null there, and it would also put a truncation
 *   on the return, which retail does not have -- so the return type is s32.
 * * `beql $6, $0` tests the WALKER, not a field: the loop body really is
 *   guarded by `if (p != 0)`.  The `addiu $5,$5,1` in its likely slot is the
 *   `i++` of the merge point duplicated, not a second increment.
 * * The count `lh` sits in the null-check's likely slot, so it is read AFTER
 *   the guard, i.e. a local assigned inside the guarded region.
 */

typedef struct Part {
    u8  pad00[0x6];
    s16 f06;
    u8  pad08[0x4];
} Part;

typedef struct Obj {
    u8    pad000[0x2AC];
    Part *parts;
    s16   nparts;
} Obj;

s32 factory_FactoryBeltTotalLength_4ffa30(Obj *o)
{
    Part *p;
    s32   n;
    s32   i;
    s32   sum;

    p = o->parts;
    if (p == 0) {
        return 0;
    }
    n = o->nparts;
    sum = 0;
    for (i = 0; i < n; i++, p++) {
        if (p != 0) {
            sum = (s16)(sum + p->f06);
        }
    }
    return sum;
}
