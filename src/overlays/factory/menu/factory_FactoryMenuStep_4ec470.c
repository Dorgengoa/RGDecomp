#include "types.h"

/* factory.bin overlay, 0x004EC470 -- leave the factory screen: fade the loop
 * out if the mixer is up, then close the five shared windows.
 * 100 bytes, 28 instructions, 1 conditional branch, 7 calls.
 *
 * * `1.0f` is `lui $2, 0x3F80` + `mtc1 $2, $f12`, a materialised constant, NOT
 * a float-pool load -- so it is written as a literal and not named as an
 * external ([[main-pass33-lists]] section 4).
 *
 * * The `beql`'s delay slot repeats the merge block's own
 * `lw $4, -0x498C($28)`, so it is a plain branch-around.
 */

extern void *D_004807E4;                        /* _gp - 0x498C */
extern void *D_004807E8;                        /* _gp - 0x4988 */
extern void *D_004807EC;                        /* _gp - 0x4984 */
extern void *D_004807F0;                        /* _gp - 0x4980 */
extern void *D_004807F8;                        /* _gp - 0x4978 */

extern s32  func_15DE40(void);
extern void func_157CA0(s32 h, s32 id, f32 t);
extern void func_2913A0(void *w);
extern void func_28ED70(void *w);

void factory_FactoryMenuStep_4ec470(void)
{
    s32 h;

    h = func_15DE40();
    if (h != 0) {
        func_157CA0(h, 0x32E, 1.0f);
    }
    func_2913A0(D_004807E4);
    func_2913A0(D_004807E8);
    func_2913A0(D_004807EC);
    func_2913A0(D_004807F0);
    func_28ED70(D_004807F8);
}
