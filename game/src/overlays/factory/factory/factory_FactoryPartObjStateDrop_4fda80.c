/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjStateDrop_4fda80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* RESIDUE (9 bad, EXACT length), all in 0x004FDBE4-0x004FDC74.  Retail runs the
 * two float statements STRICTLY sequentially with the whole chain destructive
 * in $f0: pos[1]->$f0, o->f38->$f2, D_0047DB7C->$f1.  Ours reloads pos[1] into
 * $f1 and D into $f3, then HOISTS `neg.s $f0,$f3` (= -D_0047DB7C) above
 * statement 1's mul.s/swc1 -- a 4th live float reg -- so retail's
 * swc1 $f0,0x44($29) lands at 0x004FDC6C and ours at 0x004FDC74.
 * INERT: naming the sum (`sum = o->f38 + pos[1]`) -> identical 9 words;
 *        naming the negated constant in a statement placed AFTER the pos[1]
 *        store (`dneg = -D_0047DB7C;`) -> identical 9 words.
 * [[normal-named-product-local]] does NOT fire on this shape.
 * MEASURED POSITIVES this round (18 -> 9): `u8 flag` gives retail's
 * `daddiu $3,$0,1`; dropping the `!= 0` token from `if (flag)` / `if (n)`
 * removed andi+sltu (+3 words) and 2x andi (+1 word) respectively.
 */

/* factory.bin overlay, 0x004FDA80 -- the three-phase bounce animation for a
 * dropped item: phase 0 seeds the velocity, phase 1 integrates it and bounces
 * off the floor, phase 2 lands it.  704 bytes.
 */

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Kind {
    u8  pad00[0x18];
    f32 f18;
} Kind;

typedef struct Src {
    u8    pad00[0x4];
    f32   f04;
    u8    pad08[0x18];
    u8    f20;
    u8    pad21[0x3];
    Kind *f24;
} Src;

typedef struct Slot {
    u8    pad00[0x20];
    Node *f20;
    s8    f24;
    s8    f25;
    u8    pad26[0x1];
    s8    f27;
    s16   f28;
    u8    pad2A[0xE];
    f32   f38;
} Slot;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32  D_0047DC9C;
extern f32  D_0047DB7C;

void factory_FactoryPartObjStateDrop_4fda80(Slot *o, Src *s)
{
    f32   pos[4] __attribute__((aligned(16)));
    f32   sc[4] __attribute__((aligned(16)));
    Node *nd;
    s32   h;
    u8    flag;
    u8    n;
    s8   *p;
    u32   m;

    o->f20->f32 = 1;
    if (o->f24 != o->f25) {
        factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, s->f24, 0);
        factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 0);
        factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, s->f24, 0);
        nd = o->f20;
        p = (s8 *)sc;
        m = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                m--;
                p++;
            } while (m != 0);
        }
        sc[0] = 1.0f;
        sc[1] = 1.0f;
        sc[2] = 1.0f;
        NodeSetScale_1865b0(nd, sc);
        o->f24 = o->f25;
        o->f28 = 0;
    }
    NodeGetTranslation_186650(o->f20, pos);
    switch (o->f27) {
    case 0:
        factory_FactoryPartObjSetNodesVisible_4fd110(o, s->f24, 0);
        pos[1] = s->f04;
        o->f38 = dpmul(2.0, RandFloat_13c010());
        o->f27 = o->f27 + 1;
        o->f28 = 0;
        break;
    case 1:
        o->f38 = o->f38 - D_0047DC9C;
        flag = 0;
        if (pos[1] + o->f38 < 0.0f) {
            if (o->f28 == 0) {
                h = GetCurrentScene_1f5be0();
                if (s->f24->f18 < 0.5f) {
                    GameSceneSoundSlot6PlaySeVol_1d05c0(h, 3, 1.0f);
                } else {
                    GameSceneSoundSlot6PlaySeVol_1d05c0(h, 4, 1.0f);
                }
                factory_FactoryCameraShakeStart_505070(GetFactoryObj_367f30(), s->f24->f18);
            }
            flag = 1;
            *(volatile f32 *)&pos[1] = D_0047DB7C * -(o->f38 + pos[1]);
            o->f38 = o->f38 * -D_0047DB7C;
            o->f28 = o->f28 + 1;
        } else {
            pos[1] = pos[1] + o->f38;
        }
        n = 0;
        if (flag || pos[1] < 2.5f) {
            n = 1;
        }
        if (n) {
            n = s->f20;
        }
        factory_FactoryPartObjSetNodesVisible_4fd110(o, s->f24, n);
        if (o->f28 >= 0xF) {
            pos[1] = 0.0f;
            o->f27 = o->f27 + 1;
            o->f28 = 0;
        }
        break;
    case 2:
        factory_FactoryPartObjSetNodesVisible_4fd110(o, s->f24, s->f20);
        pos[1] = 0.0f;
        o->f25 = 3;
        o->f27 = 0;
        o->f28 = 0;
        break;
    default:
        o->f27 = 0;
        o->f28 = 0;
        break;
    }
    NodeSetTranslation_1866b0(o->f20, pos);
}
