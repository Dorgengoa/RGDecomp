/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuTexRelease_4ec090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EC090 -- tear the factory HUD down: drop the list
 * body if one was built, mute the loop, and clear the two module flags.
 * 68 bytes, 20 instructions, 1 conditional branch, 3 calls.
 *
 * * The guarded call passes the value it TESTED -- `lw $4` before the `beqz`
 * and a bare `nop` in the `jal`'s delay slot -- so the global is spelled at
 * both places, not hoisted into a local.
 */

extern void *D_00484A30;                        /* _gp - 0x740  */
extern s32   D_00484A88;                        /* _gp - 0x6E8  */
extern u8    D_00480800;                        /* _gp - 0x4970 */

/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuTexRelease_4ec090(void)
{
    if (D_00484A30 != 0) {
        MemStackReset_14d830(D_00484A30);
    }
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32E);
    D_00484A88 = 0;
    D_00480800 = 0;
}
