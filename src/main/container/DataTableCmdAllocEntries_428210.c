#include "types.h"

typedef struct Ctx {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  m7C;
    u8   pad07E[0x2];
    s16  m80;
    u8   pad082[0xA];
    void *m8C;
} Ctx;

extern Ctx *D_004830F8;
extern s16 VariantGetInt_15f780(void);
extern void *ArenaNew_427f40(s32, void *, s32, s32);
extern void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
extern void DataTableAllocBitset_368960(Ctx *);

/* Allocate the 0x58-stride pool for however many entries VariantGetInt_15f780
   reports.  The `dsll32/dsra32 ..,16` on the call result is the s16 local;
   the `sh` stores $2 rather than $16 because the halfword store keeps the
   same sixteen bits either way. */

s32 DataTableCmdAllocEntries_428210(void)
{
    Ctx *g;
    s16 n;
    void *p;

    g = D_004830F8;
    n = VariantGetInt_15f780();
    g->m7C = n;
    if (n > 0) {
        p = ArenaNew_427f40(n * 0x58 + 0x10, g->m6C, g->m80, -1);
        g->m8C = ConstructNewArray_100710(p, 0, 0, 0x58, n);
        if (g->m8C == 0) {
            return 1;
        }
        DataTableAllocBitset_368960(g);
    }
    return 1;
}
