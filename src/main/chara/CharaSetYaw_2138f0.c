#include "types.h"

extern f32 Sinf_128fd0(f32);
extern f32 Cosf_128d30(f32);
extern void VecNormalize_1cbb80(void *, void *);
extern void CharaSetRot_2387d0(void *, f32, f32, f32);
extern void SrtSetRotThunk_1c73d0(void *, f32, f32, f32);

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Vec3Pad {
    f32 x;
    f32 y;
    f32 z;
    f32 pad;
} Vec3Pad;

typedef struct Obj002138f0 {
    u8 pad0[0x440];
    Vec3 unk440;
    s32 unk44C;
    Vec3 unk450;
    s32 unk45C;
} Obj002138f0;

void CharaSetYaw_2138f0(Obj002138f0 *arg0, f32 fparg0)
{
    Vec3Pad sp30;
    u8 *var_3;
    u32 var_2;

    var_2 = 0x10;
    var_3 = (u8 *)&sp30;
    if (var_3 != NULL) {
        do {
            *var_3 = 0;
            var_2 -= 1;
            var_3 += 1;
        } while (var_2 != 0);
    }
    sp30.x = Sinf_128fd0(fparg0);
    sp30.z = Cosf_128d30(fparg0);
    CharaSetRot_2387d0(arg0, 0.0f, fparg0, 0.0f);
    SrtSetRotThunk_1c73d0(arg0, 0.0f, fparg0, 0.0f);
    {
        f32 tz = sp30.z;
        f32 ty = sp30.y;
        f32 tx = sp30.x;
        arg0->unk450.x = tx;
        arg0->unk450.y = ty;
        arg0->unk450.z = tz;
    }
    arg0->unk45C = 0;
    VecNormalize_1cbb80(&arg0->unk450, &arg0->unk450);
    {
        f32 tz = sp30.z;
        f32 ty = sp30.y;
        f32 tx = sp30.x;
        arg0->unk440.x = tx;
        arg0->unk440.y = ty;
        arg0->unk440.z = tz;
    }
    arg0->unk44C = 0;
    VecNormalize_1cbb80(&arg0->unk440, &arg0->unk440);
}
