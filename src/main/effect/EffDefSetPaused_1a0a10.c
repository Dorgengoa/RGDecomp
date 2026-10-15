#include "types.h"

/* Handle-table lookup (HandleTableGet_1a1d50, see src/s26a/HandleTableGet_1a1d50.c) followed
   by a single byte-field store.  arg1 (the Handle) is stashed to a stack
   temp that is never read again in the retail listing (sw $5,0x2C($29) in
   the jal's delay slot) -- kept here as a volatile local so mwcc does not
   drop the dead store, matching the project's established convention for
   this exact residue shape (see src/event/MemStackReturnToOwnerMaybe_14dad0.c).

   MEASURED: the temp's stack cell moves 4 words (0x28 -> retail's 0x2C)
   depending on whether it is typed as the union Handle0a10 or a plain u32
   holding the same bits -- `volatile u32 sp2C = a1.all;` is the one that
   reproduces retail's offset; the union-typed local lands one cell lower. */

typedef union Handle0a10 {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle0a10;

typedef struct Rec0a10 { u8 b[0x10]; } Rec0a10;

typedef struct Table0a10 {
    u8    pad000[0x4];
    u32   count;
    Rec0a10 *recs;
    u8    pad00C[0x8];
    u32  *tags;
} Table0a10;

typedef struct Obj0a10 {
    void *unk0;
} Obj0a10;

extern Rec0a10 *HandleTableGet_1a1d50(Table0a10 *t, Handle0a10 h);

void EffDefSetPaused_1a0a10(u8 *a0, Handle0a10 a1, u8 a2)
{
    volatile u32 sp2C = a1.all;
    Rec0a10 *rec;
    Obj0a10 *obj;

    rec = HandleTableGet_1a1d50((Table0a10 *)(a0 + 0xB0), a1);
    if (rec != 0) {
        obj = *(Obj0a10 **)rec;
    } else {
        obj = 0;
    }
    *((u8 *)obj + 0x51) = a2;
}
