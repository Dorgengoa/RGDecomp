/* rgp:protos */
#define RGP_SELF_HandleEntryRelease_3f2500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
    u8 pad0c[0x34 - 0xC];
    s32 unk34;
    u8 pad38[0x70 - 0x38];
    s32 unk70;
    u8 pad74[0x7C - 0x74];
    s32 unk7C;
    u8 pad80[0x84 - 0x80];
    s32 unk84;
} Obj003F2500;

typedef struct {
    u8 pad0[8];
    s16 unk8;
} Obj1003F2500;

/*rgp*/                             /* extern */
/*rgp*/                                /* extern */
/*rgp*/                  /* extern */
/*rgp*/              /* extern */
/*rgp*/              /* extern */
/*rgp*/              /* extern */
/*rgp*/              /* extern */

u16 HandleEntryRelease_3f2500(Obj003F2500 *arg0, Obj1003F2500 *arg1, s32 arg2) {
    s16 temp_3;
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    s32 temp_4_4;
    s32 temp_4_5;
    u16 var_16;

    if (arg1 == NULL) {
        return 0;
    }
    var_16 = 1;
    if (arg2 != 0) {
        HandleEntryFreeRes_3f2900((int)arg0, (void *)arg1);
    }
    temp_4 = arg0->unk34;
    if ((temp_4 != 0) && !(WorldSubsysPlanetEntryRelease_411860(temp_4, arg1) & 0xFF)) {
        var_16 = 0;
    }
    temp_4_2 = arg0->unk70;
    if ((temp_4_2 != 0) && !(WorldSubsysPlanetEntryDetach_402330(temp_4_2, arg1, 0, 0) & 0xFF)) {
        var_16 = 0;
    }
    temp_4_3 = arg0->unk7C;
    if ((temp_4_3 != 0) && !(WorldSubsysPlanetEntryRelease_41fc70(temp_4_3, arg1, 0, 0) & 0xFF)) {
        var_16 = 0;
    }
    temp_4_4 = arg0->unk84;
    if ((temp_4_4 != 0) && !(WorldSubsysPlanetEntryRelease_40ec10(temp_4_4, arg1, 0, 0) & 0xFF)) {
        var_16 = 0;
    }
    temp_4_5 = arg0->unk8;
    if (temp_4_5 != 0) {
        temp_3 = arg1->unk8;
        if ((temp_3 >= 0) && (temp_3 < 2)) {
            MemStackReset_14d830(temp_4_5 + (temp_3 * 0x58));
        }
    }
    if (arg2 != 0) {
        HandleEntryInit_3f4230(arg1);
    }
    return var_16;
}
