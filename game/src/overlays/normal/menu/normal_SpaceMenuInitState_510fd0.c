/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuInitState_510fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510FD0 -- resets the map-marker module's selection state and
 * re-shows widget 2.  Pass-33 LIST rank: 64 bytes, 16 instructions, ZERO
 * branches, 1 call.  Every global is `%gp_rel`, so all of them stay plain
 * scalar externs; `D_004846BC = 0;` is written before the call and fills its
 * delay slot. */

extern s32   D_00480670;          /* gp - 0x4B00 */
extern s8    D_00480674;          /* gp - 0x4AFC */
extern s32   D_00480678;          /* gp - 0x4AF8 */
extern s16   D_004846A8;          /* gp - 0xAC8  */
extern void *D_004846B4;          /* gp - 0xABC  */
extern s32   D_004846BC;          /* gp - 0xAB4  */

/*rgp*/

extern s32 normal_SpaceMenuInitState_510fd0(void);

s32 normal_SpaceMenuInitState_510fd0(void)
{
    D_00480670 = -1;
    D_00480678 = -1;
    D_00480674 = 0;
    D_004846A8 = 0;
    D_004846BC = 0;
    StateMachineSetState_28ede0(D_004846B4, 2, 1);
    return 1;
}
