/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuResRequestState_510f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510F40 -- loads the map-marker table and shows widget 3 if it
 * arrived.  Pass-33 LIST rank: 132 bytes, 33 instructions, ONE conditional
 * branch, 6 calls.  Both exits return 1; the guard is an EARLY return on the
 * failure value, which is what retail falls through into. */

extern void *D_004802BC;          /* gp - 0x4EB4 */
extern s32   D_00480670;          /* gp - 0x4B00 */
extern s8    D_00480674;          /* gp - 0x4AFC */
extern void *D_004846B4;          /* gp - 0xABC  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 normal_SpaceMenuResRequestState_510f40(void);

s32 normal_SpaceMenuResRequestState_510f40(void)
{
    void *q;

    q = GetLoaderMgr_1f59d0();
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    D_00480670 = -1;
    D_00480674 = 0;
    D_00480670 = LoaderRequestFile_1cd870(q, D_004802BC, 0);
    LoaderQueueAppendSeparator_1cd670(q);
    if (D_00480670 == -1) {
        return 1;
    }
    StateMachineSetState_28ede0(D_004846B4, 3, 1);
    return 1;
}
