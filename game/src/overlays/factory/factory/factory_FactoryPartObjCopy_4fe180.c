/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjCopy_4fe180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FE180 -- reset one item slot, then copy the source
 * slot's node transform across and adopt its identifying fields.
 * 264 bytes, 68 instructions, 2 conditional branches, 6 calls (br/ins 0.029).
 *
 * * TWIN of `factory_FactoryBeltTileObjCopy_4ff030` at ratio 0.903 -- the same function over the
 * 0x34 record instead of the 0x40 one, so it loses `f34`/`f36`/`f38`/`f3C`.
 * The record itself is the one `factory_FactoryPartGroupBuildObjs_4fead0` initialises.
 *
 * * `f38` is copied with `lwc1`/`swc1` but CLEARED with `sw $0`, which is what a
 * plain `f32` field does: mwcc has no FPU round trip to make for the constant.
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
    s16   f34;
    s16   f36;
    f32   f38;
    s32   f3C;
} Item;                                         /* 0x40 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartObjCopy_4fe180(Item *o, Item *s)
{
    u8 m[0x10] __attribute__((aligned(16)));

    o->f24 = -1;
    o->f25 = 0;
    o->f26 = 0;
    o->f27 = 0;
    o->f28 = 0;
    o->f2A = 0;
    o->f30 = -1;
    o->f32 = -1;
    o->f34 = -1;
    o->f36 = -1;
    o->f38 = 0;
    o->f3C = 0;
    if (o->f20 != 0) {
        if (s->f20 != 0) {
            NodeGetTranslation_186650(s->f20, m);
            NodeSetTranslation_1866b0(o->f20, m);
            NodeGetRotation_1865e0(s->f20, m);
            NodeSetRotation_186620(o->f20, m);
            NodeGetScale_186560(s->f20, m);
            NodeSetScale_1865b0(o->f20, m);
        }
    }
    o->f25 = s->f25;
    o->f24 = -1;
    o->f26 = s->f26;
    o->f27 = s->f27;
    o->f28 = s->f28;
    o->f38 = s->f38;
    o->f30 = s->f30;
    o->f32 = s->f32;
    o->f34 = s->f34;
    o->f36 = s->f36;
}
