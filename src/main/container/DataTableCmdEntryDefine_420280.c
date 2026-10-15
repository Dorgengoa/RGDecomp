/* DataTableCmdEntryDefine_420280 -- byte-identical clone of DataTableCmdEntryDefine_40f6e0 (200 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 3-member byte-identical group (200 B each):
   DataTableCmdEntryDefine_420280 / DataTableCmdEntryDefine_41e900 / DataTableCmdEntryDefine_420280.

   MEASURED, 8 arms in one sweep: the advance MUST be written as a byte-cast
   round trip.  `arg + 1`, `arg++`, `arg = arg + 1`, a `u8 *` local and the
   inline `arg + 1` are ONE object (6002514d) that sinks the add into the
   argument register (`addiu $4,$17,8`, 49 words).  Only
   `arg = (Tok *)((u8 *)arg + 8)` keeps it live across the VariantGetInt_15f780 call
   as retail's separate `addiu $17,$17,0x8`. */

typedef struct Tok0f6e0 { s32 a; s32 b; } Tok0f6e0;

struct Ent0f6e0 { s16 m0; s16 m2; void *m4; };
struct G0f6e0 {
    u8 pad000[0x6C];
    u8 m6C[0x10];
    s16 m7C;
    u8 pad07E[0x8C - 0x7E];
    struct Ent0f6e0 *m8C;
};
extern struct G0f6e0 *D_004830F8;
extern s16 D_004830FC;
extern s32   VariantGetInt_15f780(void);
extern s32   SlotGetInt_15f720(void *p);
extern s32   Base64Decode_36a700(void *dst, s32 x);
extern void *ArenaAlloc_3702f0(void *arena, s32 n, s32 align);
extern void *memcpy(void *dst, const void *src, s32 n);

s32 DataTableCmdEntryDefine_420280(Tok0f6e0 *arg)
{
    struct G0f6e0 *g;
    struct Ent0f6e0 *e;
    s32 n;
    void *q;
    u8 buf[0x2000];

    g = D_004830F8;
    if (g->m7C <= 0) { return 1; }
    if (D_004830FC >= g->m7C) { return 1; }
    e = g->m8C + D_004830FC;
    arg = (Tok0f6e0 *)((u8 *)arg + 8);
    e->m0 = (s16)VariantGetInt_15f780();
    n = Base64Decode_36a700(buf, SlotGetInt_15f720(arg));
    e->m2 = (s16)n;
    e->m4 = 0;
    if (n > 0) {
        q = ArenaAlloc_3702f0(&g->m6C, n, 1);
        e->m4 = q;
        memcpy(q, buf, n);
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
