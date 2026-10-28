/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetCursorObj_390f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004E94A0[];
/*rgp*/

s32 InsectCageMenuGetCursorObj_390f70(void)
{
    s32 r = ((short)InsectCageMenuGetCursorSlot_391000());
    if (r < 0) goto zero;
    if (r < 5) goto ok;
zero:
    return 0;
ok:
    return D_004E94A0[r];
}
