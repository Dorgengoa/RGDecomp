/* rgp:protos */
#define RGP_SELF_InsectCageMenuSelectSlotObj_3904a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00483310;
extern s32 D_004E94A0[8];
extern u8 D_004E94C0[0x400];

s32 InsectCageMenuSelectSlotObj_3904a0(u8 *arg0) {
    s32 t;
    s32 i;

    D_00483310 = 0;
    if (MenuObjCountActive_390ec0() <= 0) {
        return 0;
    }
    {
        t = D_004E94A0[*(s16 *)(arg0 + 0x10)];
        if (t == 0) {
            MenuCursorObjSetOwner_386270(D_004E94C0, 0);
            InsectCageNameLabelSetMaybe_388040(0);
        } else {
            MenuCursorObjSetOwner_386270(D_004E94C0, t);
            InsectCageNameLabelSetMaybe_388040(t);
        }
        for (i = 0; i < 5; i++) {
            t = D_004E94A0[i];
            if (t != 0) {
                if (i == *(s16 *)(arg0 + 0x10)) {
                    BitArraySetReturnOld_384360(t + 0x986, 2, 1);
                } else {
                    BitArraySetReturnOld_384360(t + 0x986, 2, 0);
                }
            }
        }
    }
    return 1;
}
