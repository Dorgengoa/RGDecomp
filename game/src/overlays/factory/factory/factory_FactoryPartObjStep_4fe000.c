/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjStep_4fe000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FE000 -- dispatch one document page to its
 * renderer.
 *
 * A compiled `switch` over page kinds 0..6, so mwcc emits a real jump table;
 * scripts/f_jtbl.py points it at the overlay's own factory_jtbl_0050CE00.
 *
 * ★★ `case 0` HAS TO BE IN THE SOURCE even though it shares the default's
 * body.  The bound is `sltiu $1, $2, 0x7` with a SEVEN-entry table and NO
 * bias: written as cases 1..6 mwcc would subtract 1 first, exactly as
 * `factory_FactoryPartsItemToGroup_4efb80` does for its 0x4183 base.  Entry 0 of the table holds
 * the default block's address, which is what `case 0: default:` produces.
 *
 * ★ `beql $3, $0, .L004FE0B8` carrying `ld $31, 0x0($29)` is a PLAIN branch to
 * the epilogue at 0x004FE0B4 with the merge's first instruction duplicated
 * into the slot; both guards leave by the same path and the asymmetry with the
 * second guard's `beqz`/`nop` is mwcc's, not the source's.
 *
 * ★ The seven renderers take (page, doc) -- proved from the CALLEES, each of
 * which reads $4 and $5 before writing them, not from these call sites, where
 * both arguments are pass-throughs and marshal nothing.
 */

typedef struct Doc {
    u8  pad0[0x24];
    s32 f24;
} Doc;

typedef struct Page {
    u8   pad0[0x20];
    void *f20;
    s8   f24;
    s8   f25;
} Page;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartObjStep_4fe000(Page *p, Doc *d)
{
    if (p->f20 != 0 && d->f24 != 0) {
        switch (p->f25) {
        case 0:
        default:
            factory_FactoryPartObjStatePlace_4fdf10(p, d);
            break;
        case 1:
            factory_FactoryPartObjStateFollow_4fdd40(p, d);
            break;
        case 2:
            factory_FactoryPartObjStateDrop_4fda80(p, d);
            break;
        case 3:
            factory_FactoryPartObjStateOff_4fd9a0(p, d);
            break;
        case 4:
            factory_FactoryPartObjStateStartup_4fd6a0(p, d);
            break;
        case 5:
            factory_FactoryPartObjStateOn_4fd5c0(p, d);
            break;
        case 6:
            factory_FactoryPartObjStateWork_4fd2f0(p, d);
            break;
        }
    }
}
