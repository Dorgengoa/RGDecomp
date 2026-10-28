/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_3f5200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Fill a record's byte field from N source entries.  Head of a 4-member clone
   group (176 B each) with DataTableCmdEntrySetParams_3f5150 / DataTableCmdEntrySetParams_3f5200 / DataTableCmdEntrySetParams_3f52b0, which
   differ only in the reader they call, the field's offset in the record, and
   the count.  Same `D_004830F8` pool as DataTableCmdEntryDefine_4148a0.

   `VariantGetInt_15f780(src++)` is the session-25 R8 POST-INCREMENT: retail sets the
   argument with `daddu $4,$16,$0` and advances with a separate
   `addiu $16,$16,0x8` in the jal's delay slot, which only happens when the
   pointer's element type is 8 bytes wide -- [[levers.d/main-session25-levers]].
   Every other advance spelling folds the copy and the add into one `addiu`. */

typedef struct R8 { u8 b[8]; } R8;
typedef struct Elem { u8 b[28]; } Elem;

typedef struct Rec {
    u8 pad000[0xD];
    u8 m18[8];
} Rec;

typedef struct Pool {
    u8    pad000[0x7C];
    s16   count;
    u8    pad07E[0xE];
    Elem *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/

s32 DataTableCmdEntrySetParams_3f5200(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Rec *rec;
    s32 j;

    if (n <= 0) {
        return 1;
    }
    i = D_004830FC - 1;
    if (i >= n) {
        return 1;
    }
    rec = ((Rec *)AbilityDataGetKind1Rec_3f5de0(&p->slots[i]));
    if (rec == NULL) {
        return 1;
    }
    for (j = 0; j < 5; j++) {
        rec->m18[j] = VariantGetInt_15f780(src++);
    }
    return 1;
}
