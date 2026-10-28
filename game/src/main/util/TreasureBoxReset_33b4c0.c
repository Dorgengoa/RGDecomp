/* rgp:protos */
#define RGP_SELF_TreasureBoxReset_33b4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A zero-fill whose last byte is SIX one-bit fields.  `lbu / and ~mask /
   or value<<pos / sb` is mwcc's bitfield INSERT, and the masks read the bit
   positions straight off: ~2, ~3, ~5, ~9, ~0x11, ~0x21 are bits 1, 0, 1, 2,
   3, 4, 5.  The `andi $25, $0, 0x1` is the inserted value itself -- mwcc
   masks it to the field width and does NOT fold it away even when it is a
   literal zero, which is why one `andi` of the zero register is CSE'd across
   all seven inserts.

   Bit 1 is written once in the middle of the fill and again in the closing
   run of six; that is seven inserts, not six. */

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    f32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s32 unk30;
    s16 unk34;
    s16 unk36;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    f32 unk58;
    s32 unk5C;
    f32 unk60;
    s32 unk64;
    s32 unk68;
    f32 unk6C;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
} DvNode;

void TreasureBoxReset_33b4c0(DvNode *p)
{
    p->unk20 = -1;
    p->unk22 = -1;
    p->unk24 = -1;
    p->unk00 = 0;
    p->unk04 = 0;
    p->unk08 = 0;
    p->unk0C = 1.0f;
    p->unk10 = 0;
    p->unk14 = 0;
    p->unk18 = 0;
    p->unk1C = 0;
    p->unk26 = 0;
    p->unk28 = 0;
    p->unk2A = 0;
    p->unk2C = 0;
    p->b1 = 0;
    p->unk30 = 0;
    p->unk34 = -1;
    p->unk38 = 0;
    p->unk3C = 0;
    p->unk40 = 0;
    p->unk44 = 0;
    p->unk48 = 0;
    p->unk4C = 0;
    p->unk50 = 0;
    p->unk54 = 0;
    p->unk58 = 1.0f;
    p->unk5C = 0;
    p->unk60 = 1.0f;
    p->unk64 = 0;
    p->unk68 = 0;
    p->unk6C = -1.0f;
    p->b0 = 0;
    p->b1 = 0;
    p->b2 = 0;
    p->b3 = 0;
    p->b4 = 0;
    p->b5 = 0;
}
