/* rgp:protos */
#define RGP_SELF_EventIconTableReset_278b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem_00278b40 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    f32 unk20;
    f32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} Elem_00278b40;

typedef struct Tail_00278b40 {
    u8 pad[0x400];
    s32 unk400;
    s32 unk404;
} Tail_00278b40;

typedef rg_u128 u128;

void EventIconTableReset_278b40(Elem_00278b40 *arg0)
{
    s32 i;

    for (i = 0; i < 0x10; i++) {
        arg0[i].unk28 = -1;
        arg0[i].unk20 = 1.0f;
        arg0[i].unk24 = 1.0f;
        *(u128 *)&arg0[i].unk0 = 0;
        *(u128 *)&arg0[i].unk10 = 0;
        arg0[i].unk2C = 0;
        arg0[i].unk30 = 0x2D;
        arg0[i].unk34 = 0;
        arg0[i].unk38 = 0;
    }
    ((Tail_00278b40 *)arg0)->unk400 = -1;
    ((Tail_00278b40 *)arg0)->unk404 = 0;
}
