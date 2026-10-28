/* rgp:protos */
#define RGP_SELF_ItemDefGetDisplayName_40e470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void strcat(s32, void *);
extern void strcpy(s32, s32);
extern u8 D_00467920[];

s32 ItemDefGetDisplayName_40e470(void *arg0, s32 arg1, s32 arg2)
{
    if (arg1 == 0) {
        return 0;
    }
    strcpy(arg1, *(s32 *)((u8 *)arg0 + 0xC));
    if (arg2 != 0 && ItemDefIsWeapon_40e400(arg0) != 0) {
        strcat(arg1, D_00467920);
    }
    return 1;
}
