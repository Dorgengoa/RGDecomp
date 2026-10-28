/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintConfirm_4fb840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FB840 -- pump the parts-shop confirm dialog: one
 * step per state, driving `factory_FactoryBlueprintCancel_4fb5a0` and the panel rebuilder.
 *
 * A compiled `switch` over states 0..9, so mwcc emits a real jump table;
 * scripts/f_jtbl.py points it at the overlay's own factory_jtbl_0050CD50.
 *
 * ★ Entries 5, 7 and 8 share ONE block and case 2 is a SEPARATE COPY of the
 * same single call -- read the table, not the code, to decide which arms share
 * a label.  Physical block order 0, 1, 2, 3, 4, 6, 9, then the shared 5/7/8 is
 * source order.
 *
 * ★ Every inner dispatch is an if/else-if CHAIN: each `bnel` carries the NEXT
 * GUARD'S CONSTANT (`addiu $3, $0, 0x1`), never a case body's store, which is
 * what `scripts/f_ds.py` prints.
 *
 * ★ SPLIT THE CALL OUT OF A STORE WHOSE LVALUE CONTAINS IT, in case 4.
 * `func_367EC0()->f00 = 4;` as one statement puts `addiu $3, $0, 0x4` in the
 * `jal`'s DELAY SLOT; retail leaves that slot empty and materialises the 4
 * after the call, which is what `j = func_367EC0(); j->f00 = 4;` gives.  One
 * word, and the length guard is what catches it.
 *
 * ★ `daddu $16, $2, $0` in the bound check's delay slot is `func_207DF0`'s
 * result being parked in a callee-saved register for its single use 130
 * instructions later -- a named local, not a reload.
 */

typedef struct Item {
    u8  pad0[0x14];
    s16 f14;
} Item;

typedef struct Job {
    s32 f00;
    u8  pad04[0xC];
    s32 f10;
} Job;

typedef struct Panel {
    u8    pad0[0x70];
    s32   f70;
    u8    pad74[8];
    u8    f7C;
    u8    pad7D[3];
    void *f80;
    void *f84;
} Panel;

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

void factory_FactoryBlueprintConfirm_4fb840(Panel *o)
{
    void *s;
    Job  *j;
    s16   v;

    s = SceneSoundGetSlot0HandleCur_207df0();
    switch (o->f7C) {
    case 0:
        factory_FactoryBlueprintOpenDetail_4f97a0(o);
        break;
    case 1:
        v = ((Item *)UiEntryListFindByTag_28ea40(o->f84, 0x88D6))->f14;
        if (v == 0) {
            o->f7C = 9;
            factory_FactoryBlueprintDialogLayout_4f7ed0(o);
        } else if (v == 1) {
            factory_FactoryBlueprintCancel_4fb5a0(o);
        }
        break;
    case 2:
        factory_FactoryBlueprintCancel_4fb5a0(o);
        break;
    case 3:
        v = ((Item *)UiEntryListFindByTag_28ea40(o->f84, 0x88EA))->f14;
        if (v == 0) {
            o->f7C = 4;
            factory_FactoryBlueprintDialogLayout_4f7ed0(o);
        } else if (v == 1) {
            factory_FactoryBlueprintCancel_4fb5a0(o);
        }
        break;
    case 4:
        v = ((Item *)UiEntryListFindByTag_28ea40(o->f84, 0x88EA))->f14;
        if (v == 0) {
            o->f7C = 5;
            factory_FactoryBlueprintDialogLayout_4f7ed0(o);
            j = ((Job *)FactoryGetRequestPtr_367ec0());
            j->f00 = 4;
        } else if (v == 1) {
            factory_FactoryBlueprintCancel_4fb5a0(o);
        }
        break;
    case 6:
        v = ((Item *)UiEntryListFindByTag_28ea40(o->f84, 0x88EA))->f14;
        if (v == 0) {
            o->f7C = 7;
            factory_FactoryBlueprintDialogLayout_4f7ed0(o);
            factory_FactoryBlueprintClearChosen_4faf10(o);
        } else if (v == 1) {
            factory_FactoryBlueprintCancel_4fb5a0(o);
        }
        break;
    case 9:
        v = ((Item *)UiEntryListFindByTag_28ea40(o->f84, 0x88EA))->f14;
        if (v == 0) {
            factory_FactoryBlueprintShowChosen_4f7ad0(o);
            j = ((Job *)FactoryGetRequestPtr_367ec0());
            j->f00 = 3;
            j->f10 = o->f70;
            o->f7C = 8;
            UiSetWidgetVisible_290010(o->f80, 0x27, 0, -1);
            factory_FactoryBlueprintDialogLayout_4f7ed0(o);
            SoundPlayScaledVolume_1b9520(s, 9, 0, 1.0f);
            UiSetWidgetVisible_290010(o->f80, 0x20, 1, -1);
            factory_FactoryBlueprintGridRefresh_4f9ac0(o);
            factory_FactoryBlueprintShowName_4f9db0(o);
        } else if (v == 1) {
            factory_FactoryBlueprintCancel_4fb5a0(o);
        }
        break;
    case 5:
    case 7:
    case 8:
        factory_FactoryBlueprintCancel_4fb5a0(o);
        break;
    }
}
