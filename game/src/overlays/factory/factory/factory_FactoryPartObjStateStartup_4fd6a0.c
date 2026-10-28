/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjStateStartup_4fd6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FD6A0 -- the five-phase machine for a working
 * machine node: re-bind the four attachment kinds when the state latch moves,
 * then advance the phase counter.  760 bytes.
 */

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Part {
    u8   pad00[0x3C];
    s32  f3C;
} Part;

typedef struct Kind {
    u8    pad00[0x8];
    u16   f08;
    u8    pad0A[0x46];
    s32  *f50;
} Kind;

typedef struct Src {
    u8    pad00[0x20];
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

void factory_FactoryPartObjStateStartup_4fd6a0(Slot *o, Src *s)
{
    f32   sc[4] __attribute__((aligned(16)));
    Node *nd;
    Part *x;
    s32  *pp;
    s32   h;
    s8   *p;
    u32   m;

    o->f20->f32 = 1;
    factory_FactoryPartObjSetNodesVisible_4fd110(o, s->f24, s->f20);
    if (o->f24 != o->f25) {
        switch (o->f27) {
        case 0:
        case 1:
        case 2:
            factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, s->f24, 0);
            factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 0);
            factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, s->f24, 0);
            break;
        case 3:
            factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, s->f24, 0);
            factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 0);
            break;
        case 4:
            factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, s->f24, 0);
            factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 1);
            factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, s->f24, 1);
            break;
        }
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
    switch (o->f27) {
    case 0:
        o->f27 = o->f27 + 1;
        o->f28 = 0;
        break;
    case 1:
        if (o->f28 >= 0x10 || (s->f24->f08 & 2) != 0) {
            *(s8 *)((u8 *)o + 0x27) = *(s8 *)((u8 *)o + 0x27) + 1;
            o->f28 = 0;
        }
        break;
    case 2:
        GameSceneSoundSlot6PlaySeVol_1d05c0(GetCurrentScene_1f5be0(), 7, 1.0f);
        o->f27 = o->f27 + 1;
        o->f28 = 0;
        break;
    case 3:
        pp = s->f24->f50;
        if (pp != NULL) {
            while ((h = *pp) != 0) {
                x = ((Part *)NodeObjFindChildByName_195040(o->f20, h));
                if (x != NULL) {
                    if ((Rand_133710() & 1) != 0) {
                        x->f3C = x->f3C & ~1;
                    } else {
                        x->f3C = x->f3C | 1;
                    }
                }
                pp++;
            }
        }
        if (o->f28 > 0x1E) {
            o->f27 = o->f27 + 1;
            o->f28 = 0;
        }
        break;
    case 4:
        factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 1);
        factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, s->f24, 1);
        o->f25 = 5;
        o->f27 = 0;
        o->f28 = 0;
        break;
    default:
        o->f27 = 0;
        o->f28 = 0;
        break;
    }
    o->f28 = o->f28 + 1;
}
