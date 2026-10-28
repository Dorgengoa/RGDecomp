#include "vec.h"

/* Four qwords, loaded then stored. The SDK writes libvu0 as inline assembly
   with HARD-CODED registers, which is why retail's are $6..$9 in ascending
   address order -- a compiler allocating four u128 locals shortens the first
   one's live range instead and emits the loads 0x10, 0x20, 0x30, 0x00. */

void sceVu0CopyMatrix(Mtx4 *dst, const Mtx4 *src)
{
    asm volatile {
        lq  $6, 0x0($5)
        lq  $7, 0x10($5)
        lq  $8, 0x20($5)
        lq  $9, 0x30($5)
        sq  $6, 0x0($4)
        sq  $7, 0x10($4)
        sq  $8, 0x20($4)
        sq  $9, 0x30($4)
    }
}
