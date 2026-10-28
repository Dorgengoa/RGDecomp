/* rgp:protos */
#define RGP_SELF_InsectCageMenuSlotJumpInput_390380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004E94F4[0x400];

s32 InsectCageMenuSlotJumpInput_390380(void *arg0, s32 arg1) {
    if (!(MenuObjCountActive_390ec0() > 0)) {
        return 0;
    }
    if (((*(s32 *)D_004E94F4) & 4)) {
        PlayMenuSe_289ef0(4);
        *(s16 *)((u8 *)arg0 + 0x10) = *(s16 *)((u8 *)arg0 + 0x8);
        InsectCageMenuSelectSlotObj_3904a0(arg0);
    } else {
        if ((*(s32 *)D_004E94F4) & 8) {
            PlayMenuSe_289ef0(4);
            *(u16 *)((u8 *)arg0 + 0x10) = 0;
            InsectCageMenuSelectSlotObj_3904a0(arg0);
        }
    }
    return 1;
    return 0;
}
