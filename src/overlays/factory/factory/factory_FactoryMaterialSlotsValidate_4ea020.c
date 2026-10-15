#include "types.h"

/* factory.bin overlay, 0x004EA020 -- walk the group's item array and invalidate
 * every reservation whose remaining count has run out.
 * 244 bytes, 61 instructions, 4 conditional branches, 7 calls.
 *
 * * `beql $17, $0` into the epilogue is the null-group EARLY RETURN.
 * * `slt $1, $2, $3` -- the compare lands in `$at`, i.e. the STRICT `<`.
 * * The `addiu $19, $19, 0x1` appears twice only because the likely branch
 * steals the increment into its slot; there is ONE `i++` in the source, and it
 * sits in the for-clause AHEAD of the pointer advance -- `i++, e++` -- which is
 * what decides which of the two gets duplicated.
 * * `lw $4, 0x18($18)` is inside the loop: the context field is re-read at every
 * use, so it is spelled at the call site rather than hoisted into a local.
 */

typedef struct Item {
    u8 pad00[0x40];
} Item;                                         /* 0x40 */

typedef struct Group {
    u8    pad00[0xC];
    s16   f0C;
    u8    pad0E[0x2];
    Item *f10;
} Group;

typedef struct Hit {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
    s16 f08;
} Hit;

typedef struct Ctx {
    u8    pad00[0x18];
    void *f18;
} Ctx;

extern Ctx   *func_1FEDE0(void);
extern s32    func_367F30(void);
extern s32    func_3C78D0(void *w, s32 id, s32 a, s32 b);
extern Group *factory_FactoryPartGroupFindById_504080(s32 h, s32 k);
extern Hit   *factory_FactorySlotFindAt_502ad0(s32 h, s32 a, s32 b);
extern s32    factory_FactoryPartObjGetGridX_4fe120(Item *o);
extern s32    factory_FactoryPartObjGetGridY_4fe0c0(Item *o);

void factory_FactoryMaterialSlotsValidate_4ea020(void)
{
    Ctx   *ctx;
    s32    h;
    Group *g;
    Item  *e;
    Hit   *hit;
    s32    a;
    s32    b;
    s32    i;

    ctx = func_1FEDE0();
    h = func_367F30();
    g = factory_FactoryPartGroupFindById_504080(h, 0xD);
    if (g == 0) {
        return;
    }
    e = g->f10;
    for (i = 0; i < g->f0C; i++, e++) {
        a = factory_FactoryPartObjGetGridX_4fe120(e);
        b = factory_FactoryPartObjGetGridY_4fe0c0(e);
        hit = factory_FactorySlotFindAt_502ad0(h, a, b);
        if (hit != 0) {
            if (func_3C78D0(ctx->f18, hit->f04, 0, 0) < hit->f06) {
                hit->f04 = -1;
                hit->f06 = 0;
                hit->f08 = -1;
            }
        }
    }
}
