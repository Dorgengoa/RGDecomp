#include "types.h"

/* Head of a 2-member byte-identical group (156 B each):
   DataTableCmdEntrySetParams_400d90 / DataTableCmdEntrySetParams_416d50.  Same table as DataTableCmdEntryDefine_40f6e0 and ResGroupCmdObjSetRectMaybe_42aa60:
   the record count is the s16 at +0x7C of the object D_004830F8 points at,
   the record array is at +0x8C, and D_004830FC is the write cursor.  Three
   script operands are read through VariantGetInt_15f780 off a post-incremented
   8-byte cursor. */

typedef struct SArg0d90 {
    s32 w[2];
} SArg0d90;

struct Ent0d90 {
    u8  pad000[0x20];
    s16 m20;                    /* +0x20 */
    s16 m22;                    /* +0x22 */
    s16 m24;                    /* +0x24 */
    u8  pad026[52 - 0x26];
};                              /* 52 */

struct G0d90 {
    u8  pad000[0x7C];
    s16 m7C;                    /* +0x7C */
    u8  pad07E[0x8C - 0x7E];
    struct Ent0d90 *m8C;        /* +0x8C */
};

extern struct G0d90 *D_004830F8;
extern s16 D_004830FC;
extern s32 VariantGetInt_15f780(SArg0d90 *p);

s32 DataTableCmdEntrySetParams_400d90(SArg0d90 *p)
{
    struct G0d90 *g;
    struct Ent0d90 *e;
    s32 i;

    g = D_004830F8;
    if (g->m7C <= 0) {
        return 1;
    }
    i = D_004830FC - 1;
    if (i >= g->m7C) {
        return 1;
    }
    e = g->m8C + i;
    e->m20 = VariantGetInt_15f780(p++);
    e->m22 = VariantGetInt_15f780(p++);
    e->m24 = VariantGetInt_15f780(p);
    return 1;
}
