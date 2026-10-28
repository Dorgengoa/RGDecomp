/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveDialogOpen_4fcee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FCEE0 -- open the parts dialog once: bail if the
 * game is in the blocking state, if the dialog is already up or if no job
 * record is free, then latch the flag, build the dialog and reset the swing
 * angle.  148 bytes, 37 instructions, 4 branches, 4 calls.
 *
 * * The `Dlg` container is `factory_FactoryRemoveDialogLayout_4fbe10`'s verbatim (`f64` is the
 *   `u8` open flag, `f6C` the widget handle); `f60` is the `f32` this
 *   function resets.
 * * `-0x7D84($28)` is 0x0047D3EC, `-3.1415927f`, inside mwcc's `.lit4` pool
 *   (0x0047D1D0-0x0047D7FF).  WRITING THE LITERAL is one word wrong here --
 *   the overlay has no literal-pool reloc retarget, so mwcc emits the constant
 *   into THIS OBJECT'S OWN `.lit4` and the `lwc1` loses its `%gp_rel`.  The
 *   `extern f32` spelling of `factory_FactoryMaterialQtyOpen_4ed6d0` is the one that matches.
 * * `ori $5, $0, 0x8912` rather than `addiu` is just the constant clearing
 *   0x7FFF; the id parameter stays `s32`.
 * * `sb $2, 0x64($16)` sits in `factory_FactoryRemoveDialogLayout_4fbe10`'s delay slot, so the
 *   flag store PRECEDES the call in source.
 */

typedef struct Game {
    u8  pad000[0x2D0];
    s32 f2D0;
} Game;

typedef struct Job {
    s32 f00;
} Job;

typedef struct Dlg {
    u8    pad00[0x60];
    f32   f60;
    u8    f64;
    u8    pad65[0x7];
    void *f6C;
} Dlg;

extern f32   D_0047D3EC;                        /* _gp - 0x7D84, -3.1415927f */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryRemoveDialogOpen_4fcee0(Dlg *o)
{
    Game *g;
    Job  *j;

    g = ((Game *)GetFactoryObj_367f30());
    if (g == 0) {
        return;
    }
    if (g->f2D0 & 1) {
        return;
    }
    if (o->f64 != 0) {
        return;
    }
    j = ((Job *)FactoryGetRequestPtr_367ec0());
    if (j == 0) {
        return;
    }
    o->f64 = 1;
    factory_FactoryRemoveDialogLayout_4fbe10(o);
    UiEntryListSelectByTag_28ea90(o->f6C, 0x8912, 0);
    o->f60 = D_0047D3EC;
    j->f00 = 1;
}
