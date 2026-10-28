/* rgp:protos */
#define RGP_SELF_EvSubNodeMoveTo_253610 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct {
    u8 pad0[0x10];
    Vec4 unk10;
    s32 unk20;
    s32 unk24;
} Obj0_00253610;

typedef struct {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[0x60 - 0x44];
    s32 unk60;
    u8 pad64[0x70 - 0x64];
    Vec4 unk70;
    u8 pad80[0x90 - 0x80];
    Vec4 unk90;
} Obj1_00253610;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004BDDB0[0x400];

s32 EvSubNodeMoveTo_253610(Obj0_00253610 *arg0, Obj1_00253610 *arg1)
{
    Vec4 sp30 __attribute__((aligned(16)));

    if (arg1->unk40 >= arg0->unk20) {
        if (arg0->unk24 == 0) {
            sceVu0CopyVector(&arg1->unk70, &arg0->unk10);
        } else if (arg0->unk24 == 1) {
            arg1->unk70.x = arg0->unk10.x;
            arg1->unk70.z = arg0->unk10.z;
            EventCastSetObjFlags_257b10(D_004BDDB0, arg1->unk60, 0x4000);
        }
        arg1->unk40 = 0;
        return 0;
    }
    if (arg1->unk40 <= 0) {
        VecSub_13be40(&sp30, &arg0->unk10, &arg1->unk70);
        sceVu0DivVector(&arg1->unk90, &sp30, (f32)arg0->unk20);
        arg1->unk90.w = 1.0f;
    } else {
        if (arg0->unk24 == 0) {
            VecAdd_13be20(&arg1->unk70, &arg1->unk70, &arg1->unk90);
        } else if (arg0->unk24 == 1) {
            VecAdd_13be20(&arg1->unk70, &arg1->unk70, &arg1->unk90);
            EventCastSetObjFlags_257b10(D_004BDDB0, arg1->unk60, 0x4000);
        }
        arg1->unk70.w = 1.0f;
    }
    arg1->unk40++;
    return 1;
}
