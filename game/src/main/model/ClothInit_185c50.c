/* rgp:protos */
#define RGP_SELF_ClothInit_185c50 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] on the READ-ONLY gp
   float extern(s) -- const + __attribute__((section(".sdata"))). */
#include "types.h"

typedef rg_u128 u128;

typedef struct Obj00185c50 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 pad14[0x18 - 0x14];
    s32 unk18;
    u8 pad1C[0x20 - 0x1C];
    s32 unk20;
    f32 unk24;
    s32 unk28;
    u8 pad2C[0x30 - 0x2C];
    f32 unk30;
    f32 unk34;
    s32 unk38;
    u8 pad3C[0x40 - 0x3C];
    u8 unk40[0x10];
    s32 unk50;
    s32 unk54;
} Obj00185c50;

extern f32 D_0047DCA0 __attribute__((section(".sdata")));
extern f32 D_0047D90C __attribute__((section(".sdata")));

void ClothInit_185c50(Obj00185c50 *self)
{
    f32 t1;
    f32 t2;
    f32 v34;
    s32 v50;

    self->unk0 = 0;
    self->unk4 = 0;
    t1 = D_0047DCA0;
    self->unk10 = 0;
    t2 = D_0047D90C;
    self->unkC = 0;
    v34 = 1.0f;
    self->unk8 = 0;
    v50 = 0x1E69D;
    self->unk18 = 0;
    self->unk28 = 0;
    self->unk20 = 0;
    self->unk24 = t1;
    self->unk30 = t2;
    self->unk34 = v34;
    self->unk38 = 0;
    *(u128 *)self->unk40 = 0;
    self->unk50 = v50;
    self->unk54 = 0;
}
