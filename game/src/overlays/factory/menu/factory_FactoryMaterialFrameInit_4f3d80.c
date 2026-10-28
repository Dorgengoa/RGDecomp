/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialFrameInit_4f3d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3D80 -- 124 bytes / 31 words.  Straight-line
 * six-call list that (re)builds the scrolling text box embedded at +0x50.
 *
 * * Every call recomputes `addiu $4, $16, 0x50`, so the sub-object address is
 *   written at each call site (`&o->f50`) and is NOT a named local -- a local
 *   would be materialised once in a callee-saved register.
 * * `daddu $7, $6, $0` after `addiu $6, $0, 0x17` is mwcc sharing ONE constant
 *   between the third and fourth arguments: the source passes 0x17 twice.
 * * The 28Dxxx family's spellings come from factory_FUN_004EC5E0 (func_28DB70
 *   takes `void *`, the rest `const u8 *`).
 */

typedef struct Mod {
    u8    pad00[0x40];
    void *f40;
    u8    pad44[0xC];
    u8    f50;
} Mod;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

void factory_FactoryMaterialFrameInit_4f3d80(Mod *o)
{
    UiSelFrameReset_28db70(&o->f50);
    UiSelFrameInit_28da30(&o->f50, o->f40, 0x63);
    UiSelFrameSetRect_28db40(&o->f50, 0x63, 0x17, 0x17, 0x2B, 0x2E, 0, 0);
    UiSelFrameCalcTileCounts_28d9d0(&o->f50);
    UiSelFrameSetScrollPeriod_28d9c0(&o->f50, 1);
    UiSelFrameAnimStep_28d820(&o->f50, 0x63);
}
