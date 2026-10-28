/* rgp:protos */
#define RGP_SELF_DamagePopupInit_2d3bf0 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- `const` +
   __attribute__((section(".sdata"))) on the gp float extern(s) this unit
   READS.  The barrier it removes is the surrounding stores, not a write to
   the symbol; const-ing only the floats is right, const-ing every extern
   goes length-wrong. */
#include "types.h"

typedef struct Obj002d3bf0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 flag0 : 1;
    u8 unk3C_rest : 7;
} Obj002d3bf0;

extern f32 D_0047D284 __attribute__((section(".sdata")));

void DamagePopupInit_2d3bf0(Obj002d3bf0 *arg0)
{
    f32 d24;

    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 1.0f;
    arg0->unk10 = 128.0f;
    d24 = D_0047D284;
    arg0->unk14 = 128.0f;
    arg0->unk18 = 128.0f;
    arg0->unk1C = 128.0f;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->flag0 = 0;
    arg0->unk20 = 3.0f;
    arg0->unk24 = d24;
    arg0->unk38 = 0;
    arg0->unk28 = 1.0f;
    arg0->unk2E = 0;
    arg0->unk2C = 0;
}
