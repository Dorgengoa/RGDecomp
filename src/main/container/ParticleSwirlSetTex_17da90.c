#include "types.h"

/* Bitfield insert at +0x5C: andi $3,$0,1 / sll 2 / and ~4 / or  =>
   a 1-bit field at bit 2 assigned the literal 0 (brief: count the INSERTS). */

extern void NameTableCopyNode_15ad70(void *p);

typedef struct {
    u8 pad00[0x5C];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 5;
} Obj_17da90;

void ParticleSwirlSetTex_17da90(Obj_17da90 *p, s32 doit)
{
    if (doit) {
        NameTableCopyNode_15ad70((u8 *)p + 0x20);
        p->f2 = 0;
    }
}
