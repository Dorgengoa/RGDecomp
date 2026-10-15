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

extern void  func_14D830(void *p);
extern s32   func_15DE40(void);
extern void  func_158AC0(s32 h, s32 id);

void factory_FactoryMenuTexRelease_4ec090(void)
{
    if (D_00484A30 != 0) {
        func_14D830(D_00484A30);
    }
    func_158AC0(func_15DE40(), 0x32E);
    D_00484A88 = 0;
    D_00480800 = 0;
}
