#include "types.h"

/* factory.bin overlay, 0x004FF030 -- reset one item slot, then copy the source
 * slot's node transform across and adopt its identifying fields.
 * 224 bytes, 56 instructions, 2 conditional branches, 6 calls (br/ins 0.036).
 *
 * * TWIN of `factory_FactoryPartObjCopy_4fe180` at ratio 0.903 -- the same function over the
 * 0x40 record instead of the 0x34 one, so that one also carries
 * `f34`/`f36`/`f38`/`f3C`.
 * The record itself is the one `factory_FactoryPartGroupBuildObjs_4fead0` initialises.
 *
 * * The `beql`'s delay slot duplicates `lb $4, 0x25($16)`, the merge block's
 * first instruction, so the two guards really are nested and the whole trailing
 * copy is outside both.
 */

typedef struct Item {
    u8    pad00[0x20];
    void *f20;
    s8    f24;
    s8    f25;
    s8    f26;
    s8    f27;
    s16   f28;
    s16   f2A;
    u8    pad2C[0x4];
    s16   f30;
    s16   f32;
} Item;                                         /* 0x34 */

extern void func_186560(void *nd, u8 *m);
extern void func_1865B0(void *nd, u8 *m);
extern void func_1865E0(void *nd, u8 *m);
extern void func_186620(void *nd, u8 *m);
extern void func_186650(void *nd, u8 *m);
extern void func_1866B0(void *nd, u8 *m);

void factory_FactoryBeltTileObjCopy_4ff030(Item *o, Item *s)
{
    u8 m[0x10];

    o->f24 = -1;
    o->f25 = 0;
    o->f26 = 0;
    o->f27 = 0;
    o->f28 = 0;
    o->f2A = 0;
    o->f30 = -1;
    o->f32 = -1;
    if (o->f20 != 0) {
        if (s->f20 != 0) {
            func_186650(s->f20, m);
            func_1866B0(o->f20, m);
            func_1865E0(s->f20, m);
            func_186620(o->f20, m);
            func_186560(s->f20, m);
            func_1865B0(o->f20, m);
        }
    }
    o->f25 = s->f25;
    o->f24 = -1;
    o->f26 = s->f26;
    o->f27 = s->f27;
    o->f28 = s->f28;
    o->f30 = s->f30;
    o->f32 = s->f32;
}
