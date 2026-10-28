/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuRelease_511010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00511010 -- teardown/close of the 0x4B2570 sub-scene. */

extern u8    D_00480674;          /* gp - 0x4AFC */
extern s32   D_00480670;          /* gp - 0x4B00 */
extern void *D_004846B0;          /* gp - 0xAC0  */
extern s32   D_004846B4;          /* gp - 0xABC  */
extern s32   D_004846B8;          /* gp - 0xAB8  */
extern u8    D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_SpaceMenuRelease_511010(void)
{
    void *w;

    if (D_004846B8 != 0) {
        D_004846B8 = 0;
    }
    if (D_004846B4 != 0) {
        D_004846B4 = 0;
    }
    if (D_004846B0 != 0) {
        MemStackReset_14d830(D_004846B0);
    }
    w = GetLoaderMgr_1f59d0();
    if (D_00480674 != 0 && D_00480670 != -1) {
        LoaderReleaseById_1cd340(w, D_00480670);
        D_00480674 = 0;
        D_00480670 = -1;
    }
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    return 1;
}
