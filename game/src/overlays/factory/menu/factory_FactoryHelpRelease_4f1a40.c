/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpRelease_4f1a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F1A40 -- 104 bytes / 26 words.  Release the live
 * job handle and mute the HUD loop: the leading three statements of
 * factory_FUN_004F16B0 verbatim, minus that unit's two field resets.
 *
 * * `lw $3, 0x7C($4)` / `beq $3, $2` with $2 = -1 branches PAST the two calls,
 *   so retail FALLS THROUGH into them: the body is `if (o->f7C != -1)`, not an
 *   early return.
 * * Retail RE-READS `lw $5, 0x7C($16)` AFTER the jal, so func_1F59D0()'s result
 *   is a NAMED LOCAL and the field read is a separate argument -- nested,
 *   mwcc evaluates the field first and CSEs it with the guard's load.
 * * The second guard spells the global at BOTH places (`lw $4` before the
 *   `beqz`, bare `nop` in the jal's delay slot); it is not hoisted.
 * * D_00484A30 is _gp - 0x740, inside the small-data window, so a plain
 *   4-byte extern.
 */

typedef struct Mod {
    u8  pad00[0x7C];
    s32 f7C;
} Mod;

extern void *D_00484A30;                        /* _gp - 0x740 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpRelease_4f1a40(Mod *o)
{
    s32 h;

    if (o->f7C != -1) {
        h = ((s32)GetLoaderMgr_1f59d0());
        LoaderReleaseById_1cd340(h, o->f7C);
    }
    if (D_00484A30 != 0) {
        MemStackReset_14d830(D_00484A30);
    }
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32E);
}
