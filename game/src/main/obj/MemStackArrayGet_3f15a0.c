/* rgp:protos */
#define RGP_SELF_MemStackArrayGet_3f15a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* clone group cg06-005: bounds-checked element address in an array of
   0x58-byte records hung off the object.  Three guards, three separate
   return-0 blocks; the count lives in a NON-gp global (it must be declared as
   an array or mwcc puts the extern in .sdata and emits a gp-relative load).
   Members differ only in the member offset and that global. */

typedef struct Elem {
    u8 pad[0x58];
} Elem;

typedef struct Holder {
    u8 pad00[0x1C];
    Elem *arr;
} Holder;

extern s32 D_004644D0[4];

Elem *MemStackArrayGet_3f15a0(Holder *self, s32 i)
{
    Elem *arr;

    arr = self->arr;
    if (arr == 0) return 0;
    if (i < 0 || i >= D_004644D0[0]) return 0;
    return &arr[i];
}
