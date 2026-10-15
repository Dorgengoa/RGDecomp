#include "types.h"

/* Same handler family as ParamScriptSeLoopCmd_1af490: an 8-byte argument cursor, every
   advance in the reader's delay slot.  The table scan reuses $16 for the loop
   counter and then for the id it yields -- one source variable per lifetime,
   the register is shared by the allocator, not by the source. */

typedef struct Arg { s32 lo; s32 hi; } Arg;

typedef struct Ent {
    u8  pad00[0x40];
    s32 f40;
    s32 f44;
} Ent;                          /* 0x48 */

extern s32  VariantGetInt_15f780(Arg *p);
extern s32  SlotGetInt_15f720(Arg *p);
extern s32  Strcasecmp_1345b8(Ent *e, s32 name);
extern s32  ArchiveGetFileData_181dd0(s32 a, s32 b, s32 *out);
extern void *MotionListAddEntry_172520(void *ctx, s32 a, s32 b, s32 c, s32 d);
extern void MotResCopyAndRelocate_154650(void *o, s32 id, s32 d, s32 sub);

extern s32  D_0049D390[];
extern s32  D_0049D39C[];
extern s32  D_0049D3B8[];
extern s32 *D_0049D3BC[];
extern s32  D_0049D3C0[];
extern s32  D_0049D410[];
extern Ent *D_0049D414[];
extern u8  *D_0049D418[];
extern s32  D_0049D420[];
extern void *D_0049D41C[];

s32 InfoCfgMotionCmd_1ab520(Arg *p, s32 argc)
{
    s32   base;                 /* $23 */
    u8   *ctx;                  /* $22 */
    s32   d;                    /* $21 */
    s32   extra;                /* $20 */
    s32   name;                 /* $19 */
    s32   flag;                 /* $18 */
    Ent  *e;
    void *o;
    s32   id;
    s32   i;
    s32   n;
    s32   v;
    s32   sub;

    base = D_0049D390[0];
    d    = D_0049D39C[0];
    ctx  = D_0049D418[0];
    if (ctx == 0) {
        return 0;
    }
    if (d == 0) {
        return 0;
    }
    extra = 0;
    D_0049D420[0] = VariantGetInt_15f780(p++);
    name = SlotGetInt_15f720(p++);
    if (argc >= 3) {
        extra = VariantGetInt_15f780(p);
    }
    sub = 0;
    flag = 0;
    e = D_0049D414[0];
    /* Two guards branching to the SAME `id = 0` block, and the loop-exhausted
       path reaching a SECOND one -- so the zero is written twice in source. */
    if (e == 0 || D_0049D410[0] == 0) {
        id = 0;
    } else {
        for (i = 0; i < D_0049D410[0]; i++, e++) {
            if (Strcasecmp_1345b8(e, name) == 0) {
                sub = e->f44;
                id = e->f40;
                goto found;
            }
        }
        id = 0;
    }
found:
    if (id == 0) {
        id = ArchiveGetFileData_181dd0(base, name, &sub);
        flag = 1;
    }
    o = MotionListAddEntry_172520(ctx + 0x1F0, extra, D_0049D420[0], d, d);
    if (o == 0) {
        return 0;
    }
    if (flag != 0) {
        MotResCopyAndRelocate_154650(o, id, d, sub);
    } else {
        MotResCopyAndRelocate_154650(o, id, d, 0);
    }
    /* Named BEFORE the aliasing store to D_0049D41C, which is why retail does
       not reload it afterwards. */
    D_0049D41C[0] = o;
    v = D_0049D420[0];
    n = D_0049D3B8[0];
    if (n < D_0049D3C0[0]) {
        D_0049D3B8[0] = n + 1;
        D_0049D3BC[0][n] = v;
    }
    return 1;
}
