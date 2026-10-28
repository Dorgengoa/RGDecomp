/* rgp:protos */
#define RGP_SELF_insect_InsectLiveTalkTableCmdCount_523a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00523A00 -- 172 bytes, 43 instructions.  Allocate the record array
 * of the D_00485208 context and clear every record.  The gp global is
 * RE-LOADED at every use except the final `sw $0,0xC($3)`, which reuses the
 * copy the loop's exit test left live. */

typedef struct InsectRec {
    s32 f00, f04, f08, f0C, f10, f14, f18, f1C, f20, f24, f28, f2C;   /* 0x30 */
} InsectRec;

typedef struct InsectCtx {
    InsectRec *base;   /* +0x00 */
    void *f04;         /* +0x04 */
    s32 count;         /* +0x08 */
    s32 f0C;           /* +0x0C */
} InsectCtx;

typedef struct Slot { u8 raw[4]; } Slot;

extern InsectCtx *D_00485208;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectLiveTalkTableCmdCount_523a00(Slot *v)
{
    InsectCtx *c;
    InsectRec *r;
    s32 i;
    s32 n;

    D_00485208->count = VariantGetInt_15f780(v);
    c = D_00485208;
    n = c->count;
    D_00485208->base = ((InsectRec *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x30 + 0x10, c->f04), 0, 0, 0x30, n));
    r = D_00485208->base;
    for (i = 0; i < D_00485208->count; i++, r++) {
        insect_InsectLiveTalkRecordClear_523ab0((s32 *)r);
    }
    D_00485208->f0C = 0;
    return 1;
}
