/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuMainState_510d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510D90 -- gated on the 0x20-slot allocation succeeding, then on
 * two bytes of the gp record. */
typedef struct Rec { u8 pad00[0x14]; u8 f14; u8 pad15[0x6C - 0x15]; u8 f6C; } Rec;

extern u8   D_004B2570[];
extern Rec *D_004846B8;               /* gp - 0xAB8 */
extern s16  D_004846A8;               /* gp - 0xAC8 */

/*rgp*/
/*rgp*/

s32 normal_SpaceMenuMainState_510d90(void)
{
    Rec *r;

    if (PadIsTriggered_1839f0(D_004B2570, 0x20) != NULL) {
        r = D_004846B8;
        if (r->f14 != 5) {
            if (r->f6C == 0) {
                normal_SpaceMenuCancel_5117e0((void *)(r));
                D_004846A8 = 2;
            }
        }
    }
    return 1;
}
