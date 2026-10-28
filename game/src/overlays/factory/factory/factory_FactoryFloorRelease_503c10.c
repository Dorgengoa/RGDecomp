/* rgp:protos */
#define RGP_SELF_factory_FactoryFloorRelease_503c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00503C10 -- release the panel's 0x2EE0 resource
 * through the world handle, then clear the sixteen-field cursor block.
 * 180 bytes, 48 instructions, 2 conditional branches, 6 calls.
 *
 * * `h = func_201A90()` is a NAMED LOCAL, not the inline
 * `func_1E49B0(func_201A90(), ...)` spelling `factory_FactoryPartGroupBuildObjs_4fead0` uses: the
 * handle is read once and used again at the tail `func_1E3320`, so it lives in
 * `$16` across both calls ([[factory-count-the-gp-loads]]).
 *
 * * The `beql $2, $0` whose delay slot repeats `.L00503C5C`'s own
 * `daddu $4, $16, $0` is a plain branch-around, not a likely branch carrying
 * work -- `scripts/f_ds.py`'s classification.
 */

typedef struct Panel {
    u8  pad000[0x234];
    s32 f234;
    u8  f238[0x5C];
    s32 f294;
    s16 f298;
    s16 f29A;
    s32 f29C;
    s32 f2A0;
    s16 f2A4;
    s16 f2A6;
    s32 f2A8;
    s32 f2AC;
    s16 f2B0;
    s16 f2B2;
    u8  pad2B4[0x4];
    s32 f2B8;
    s32 f2BC;
    s32 f2C0;
    s32 f2C4;
} Panel;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryFloorRelease_503c10(Panel *o)
{
    s32 h;
    s32 t;
    s32 r;

    h = ((s32)GetMapMgr_201a90());
    t = MapSlotsFindBlockById_1e49b0(h, 0x2EE0, 0);
    if (t != 0) {
        r = MapDataGetModel_1e7810(t);
        if (r != 0) {
            MapAreaModelNopRelated_188fe0();
        }
    }
    MapBlockIdListAdd_1e3320(h, 0x2EE0);
    o->f234 = 0;
    MemStackReset_14d830(o->f238);
    o->f294 = 0;
    o->f298 = 0;
    o->f29A = 0;
    o->f29C = 0;
    o->f2A0 = 0;
    o->f2A4 = 0;
    o->f2A6 = 0;
    o->f2A8 = 0;
    o->f2AC = 0;
    o->f2B0 = 0;
    o->f2B2 = 0;
    o->f2B8 = 0;
    o->f2BC = 0;
    o->f2C0 = 0;
    o->f2C4 = 0;
}
