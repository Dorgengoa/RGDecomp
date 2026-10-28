/* rgp:protos */
#define RGP_SELF_SunLightInit_293d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

/*rgp*/
/*rgp*/
extern f32 D_0047DCB0;
extern f32 D_0047DCD0 __attribute__((section(".sdata")));

typedef struct E293d70 {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} E293d70;

typedef struct T293d70 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    u8 pad3[0xd];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s32 unk44;
    f32 unk48;
    s32 unk4C;
    E293d70 e[16];
    s32 unk150;
    u8 pad154[0x4];
    s32 unk158;
    s32 unk15C;
    s32 unk160;
    s32 unk164;
    f32 unk168;
    s32 unk16C;
} T293d70;

void SunLightInit_293d70(T293d70 *arg0)
{
    s32 i;
    f32 f;
    s32 m;

    arg0->unk10 = 98.0f;
    arg0->unk14 = 98.0f;
    arg0->unk18 = 128.0f;
    arg0->unk1C = 128.0f;
    arg0->unk20 = 0.0f;
    arg0->unk24 = 0.0f;
    arg0->unk28 = 0.0f;
    arg0->unk2C = 128.0f;
    arg0->unk30 = 0.0f;
    arg0->unk34 = 1000.0f;
    arg0->unk38 = 0.0f;
    arg0->unk3C = 0.0f;
    arg0->unk40 = 512.0f;
    arg0->unk48 = 1.0f;
    arg0->unk44 = 0x10;
    arg0->unk0 = 1;
    arg0->unk4C = 1;
    arg0->unk150 = 2;
    arg0->unk160 = 150;
    arg0->unk164 = 150;
    arg0->unk15C = arg0->unk160 + Rand_133710() % arg0->unk164;
    arg0->unk158 = 0;
    arg0->unk168 = 1.0f;
    arg0->unk16C = 0;
    arg0->unk1 = 0;
    arg0->unk2 = 0;
    f = 0.0f;
    for (i = 0; i < 16; i++) {
        arg0->e[i].a = arg0->unk40;
        arg0->e[i].b = f;
        arg0->e[i].c = 2.0f + (f32)(Rand_133710() % 8);
        arg0->e[i].d = (f32)(Rand_133710() % 3140) / 1000.0f;
        f += (f32)(Rand_133710() % (s32)D_0047DCD0) / 1000.0f;
        f = WrapAngle_13c050(f + D_0047DCB0);
    }
}
