#include "types.h"

/* Handle-table lookup (HandleTableGet_1a1d50, see src/s26a/HandleTableGet_1a1d50.c) followed
   by a single byte-field store.  arg1 (the Handle) is stashed to a stack
   temp that is never read again in the retail listing (sw $5,0x2C($29) in
   the jal's delay slot) -- kept here as a volatile local so mwcc does not
   drop the dead store, matching the project's established convention for
   this exact residue shape (see src/event/MemStackReturnToOwnerMaybe_14dad0.c).

   MEASURED: the temp's stack cell moves 4 words (0x28 -> retail's 0x2C)
   depending on whether it is typed as the union Handle09d0 or a plain u32
   holding the same bits -- `volatile u32 sp2C = a1.all;` is the one that
   reproduces retail's offset; the union-typed local lands one cell lower. */

typedef union Handle09d0 {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle09d0;

typedef struct Rec09d0 { u8 b[0x10]; } Rec09d0;

typedef struct Table09d0 {
    u8    pad000[0x4];
    u32   count;
    Rec09d0 *recs;
    u8    pad00C[0x8];
    u32  *tags;
} Table09d0;

typedef struct Obj09d0 {
    void *unk0;
} Obj09d0;

extern Rec09d0 *HandleTableGet_1a1d50(Table09d0 *t, Handle09d0 h);

void EffDefSetHidden_1a09d0(u8 *a0, Handle09d0 a1, u8 a2)
{
    volatile u32 sp2C = a1.all;
    Rec09d0 *rec;
    Obj09d0 *obj;

    rec = HandleTableGet_1a1d50((Table09d0 *)(a0 + 0xB0), a1);
    if (rec != 0) {
        obj = *(Obj09d0 **)rec;
    } else {
        obj = 0;
    }
    *((u8 *)obj + 0x52) = a2;
}
