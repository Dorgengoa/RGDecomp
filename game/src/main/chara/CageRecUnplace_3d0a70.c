/* rgp:protos */
#define RGP_SELF_CageRecUnplace_3d0a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T003d0a70 {
    u8 pad0[2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 padA[0x10 - 0xA];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[0x7EC - 0x20];
    s32 unk7EC;
} T003d0a70;

typedef struct A003d0a70 {
    u8 pad0[0x18];
    T003d0a70 *unk18;
} A003d0a70;

/*rgp*/
/*rgp*/
extern A003d0a70 *D_004838E8;

s32 CageRecUnplace_3d0a70(A003d0a70 *arg0)
{
    s16 temp_5;
    T003d0a70 *temp_3;

    if (CageRecIsPlaced_3d0d20((void *)arg0) == 0) {
        return 0;
    }
    {
        temp_3 = arg0->unk18;
        if (temp_3->unk4 <= 0) {
            temp_5 = temp_3->unk2;
            if (temp_5 == 0x410D) {
                InvAddItemCoreMaybe_3c6540((s32)D_004838E8->unk18, temp_5, 0, 1, -1, 0, 0);
            }
        }
        arg0->unk18->unk2 = -1;
        arg0->unk18->unk6 = -1;
        arg0->unk18->unk8 = -1;
        arg0->unk18->unk10 = 0;
        arg0->unk18->unk14 = 0;
        arg0->unk18->unk18 = 0;
        arg0->unk18->unk1C = 0;
        arg0->unk18->unk7EC = 0xBF800000;
        return 1;
    }
}
