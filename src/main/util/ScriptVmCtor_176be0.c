#include "types.h"

/* Reset: two fields are copied to two neighbours each, nine are cleared, one
   is set to 1, and the receiver comes back.

   ⚠ Two things in here are in the reference and are NOT tidy-uppable:
   +0x10 and +0x24 are each RE-READ for their second copy (mwcc does not CSE
   them, and neither did retail), and +0x40 is written to zero TWICE. Both are
   what the source says; removing either changes the word count. */

typedef struct Obj00176be0 {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x4];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x4];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
} Obj00176be0;

Obj00176be0 *ScriptVmCtor_176be0(Obj00176be0 *self)
{
    self->unk14 = self->unk10;
    self->unk18 = self->unk10;
    self->unk28 = self->unk24;
    self->unk2C = self->unk24;
    self->unk38 = 0;
    self->unk4 = 0;
    self->unkC = 0;
    self->unk20 = 0;
    self->unk40 = 0;
    self->unk0 = 1;
    self->unk3C = 0;
    self->unk40 = 0;
    self->unk44 = 0;
    return self;
}
