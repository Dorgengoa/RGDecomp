#include "types.h"

/* A member-by-member copy, and the thing that decides it is the EMISSION
   PATTERN of the load/store pairs:

     INTERLEAVED  lw/sw, lw/sw, ...        -> N separate assignments
     BATCHED      lw,lw,lw then sw,sw,sw   -> ONE sub-struct assignment

   Retail interleaves everything from 0x00 to 0x2C and then batches three
   `lwc1`s before three `swc1`s at 0x30 and again at 0x40, and four `lbu`s
   before four `sb`s at 0x50.  Those three groups are a three-float member, a
   second one, and a four-byte member -- written as scalars the unit is 17
   words wrong at the right length, and each group is worth exactly the words
   it batches.  Sharpens the two-float `lwc1/lwc1/swc1/swc1` note in
   memory/levers.d/main-pass31-spellings.md, which is the same rule at N=2.

   The four-byte member's own spelling is a MEASURED NULL: `{u8 a,b,c,d;}`
   and `{u8 v[4];}` compile to the identical object.  A struct ASSIGNMENT is
   what matters, not what is inside it. */

typedef struct { f32 x, y, z; } DvV3;

typedef struct { u8 a, b, c, d; } DvB4;

typedef struct {
    s32   unk00;
    s32   unk04;
    s32   unk08;
    s32   unk0C;
    s32   unk10;
    s32   unk14;
    s16   unk18;
    s16   unk1A;
    s16   unk1C;
    s16   unk1E;
    s8    unk20;
    s8    unk21;
    s8    unk22;
    u8    unk23;
    u8    unk24;
    u8    unk25;
    s16   unk26;
    s32   unk28;
    s32   unk2C;
    DvV3  unk30;
    f32   unk3C;
    DvV3  unk40;
    f32   unk4C;
    DvB4  unk50;
} DvCopy;

DvCopy *MapDataCopy_1eac90(DvCopy *d, DvCopy *s)
{
    d->unk00 = s->unk00;
    d->unk04 = s->unk04;
    d->unk08 = s->unk08;
    d->unk0C = s->unk0C;
    d->unk10 = s->unk10;
    d->unk14 = s->unk14;
    d->unk18 = s->unk18;
    d->unk1A = s->unk1A;
    d->unk1C = s->unk1C;
    d->unk1E = s->unk1E;
    d->unk20 = s->unk20;
    d->unk21 = s->unk21;
    d->unk22 = s->unk22;
    d->unk23 = s->unk23;
    d->unk24 = s->unk24;
    d->unk25 = s->unk25;
    d->unk26 = s->unk26;
    d->unk28 = s->unk28;
    d->unk2C = s->unk2C;
    d->unk30 = s->unk30;
    d->unk3C = s->unk3C;
    d->unk40 = s->unk40;
    d->unk4C = s->unk4C;
    d->unk50 = s->unk50;
    return d;
}
