#include "types.h"

/* Leaf, no frame.  The count is reloaded, not held: writing the load as a
   pointer walk lets mwcc CSE the ADDRESS into its own register (`addiu
   $8,$4,0x600`) and costs two words, so the count must be a struct MEMBER
   whose offset folds into both `lw`s.
   The two element addresses have OPPOSITE addu operand order
   (`addu $3,$4,$3` then `addu $3,$3,$4`): the second uses the named-product
   plus integer-cast form that flips it. */

typedef struct Ent003130d0 {
    s32 a;
    s32 b;
    s32 c;
} Ent003130d0;

typedef struct Tbl003130d0 {
    Ent003130d0 arr[128];
    s32 n;
} Tbl003130d0;

void TextLayoutSetPos_3130d0(Tbl003130d0 *self, s32 a, s32 b)
{
    s32 n;
    s32 off;

    n = self->n;
    if (n < 0x80) {
        *(s32 *)((u8 *)self + n * 12) = a;
        off = self->n * 12;
        *(s32 *)((u8 *)(off + (s32)self) + 4) = b;
    }
}
