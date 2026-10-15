#include "types.h"
/* normal 0x00518480 -- same two-widget publish pair as 0x005183C0, but the
 * two int arguments come from gp globals.  D_004806D8 is read BEFORE the call
 * (retail parks it in $17 from the jal's delay slot), D_004806DC after. */

extern s32   D_004806D8;   /* gp - 0x4A98 */
extern s32   D_004806DC;   /* gp - 0x4A94 */
extern void *D_004846E8;   /* gp - 0xA88  */
extern void *D_00484710;   /* gp - 0xA60  */

extern s32  normal_TransMenuBobIconOffset_5184f0(void);
extern void func_290F60(void *w, u16 id, s32 x, s32 y);

void normal_TransMenuBobIconPlace_518480(void)
{
    s32 x = D_004806D8;
    s32 a = normal_TransMenuBobIconOffset_5184f0();
    s32 y = D_004806DC + a;

    if (D_004846E8 != NULL) {
        func_290F60(D_004846E8, 0x75D1, x, y);
    }
    if (D_00484710 != NULL) {
        func_290F60(D_00484710, 0x75D1, x, y);
    }
}
