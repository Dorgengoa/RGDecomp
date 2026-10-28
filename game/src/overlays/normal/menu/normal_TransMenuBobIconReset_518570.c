/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobIconReset_518570 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518570 -- four gp globals published, written in retail's
 * EMISSION order.  mwcc reorders stores to distinct gp globals freely, so
 * source order does not set the store order -- it sets which value gets `$3`
 * and which `$4`, which is what this order is chosen for.
 * One of the 55 unnamed functions. */
extern s32 D_004806D8;
extern s32 D_004806DC;
extern s32 D_004806E0;
extern s32 D_00484790;

void normal_TransMenuBobIconReset_518570(void)
{
    D_004806D8 = 0xF4;
    D_00484790 = 0;
    D_004806DC = 0xBE;
    D_004806E0 = -1;
}
