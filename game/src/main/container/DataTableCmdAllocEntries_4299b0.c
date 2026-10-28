/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocEntries_4299b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN DataTableCmdAllocEntries_4299b0 -- 36 words / 144 B.
   COLD TWIN FAMILY L5: THIRTY-SIX members across two mnemonic groups
   (n=20 x 144 B and n=16 x 136 B) that are ONE source parameterised by the
   element size (24 here) and the per-caller builder ArenaNew_4299a0.  When the
   element size is a power of two mwcc emits a single `sll`; otherwise it
   emits the `sll / addu / sll` triple, which is the only reason the two
   groups differ in length.

   THE READING: the third parameter of ArenaNew_4299a0 must be declared **s32**, not
   s16.  The argument is `o->m80`, an s16 loaded with `lh`, so the width costs
   no instruction -- but it decides the caller's ARGUMENT SETUP ORDER.  With
   s16 (or u16) mwcc sets $5 before $4 and the object is exactly 2 words wrong
   (1 with u16); with s32, or with no prototype at all, $4 comes first and the
   object is byte-identical.  Measured negatives: an `if (r != 0)` body
   instead of the early `return 1` is 2 words SHORT, and an s64 fifth
   argument to ConstructNewArray_100710 is 1 word LONG.  */

typedef struct Ofunc_004299B0 {
    u8 pad00[0x6C];
    u8 m6C[0x10];
    s16 m7C;
    s16 pad7E;
    s16 m80;
    u8 pad82[0xA];
    s32 m8C;
} Ofunc_004299B0;

extern Ofunc_004299B0 *D_004830F8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocEntries_4299b0(s32 p0)
{
    Ofunc_004299B0 *o;
    s32 t;
    s32 n;
    s32 r;

    o = D_004830F8;
    t = VariantGetInt_15f780(p0);
    n = (s16)t;
    o->m7C = t;
    if (n > 0) {
        r = ((s32)ConstructNewArray_100710(ArenaNew_4299a0((n * 24) + 0x10, o->m6C, o->m80, -1), 0, 0, 24, n));
        o->m8C = r;
        if (r == 0) {
            return 1;
        }
        DataTableAllocBitset_368960(o);
    }
    return 1;
}
