/* rgp:protos */
#define RGP_SELF_UiSelFrameInit_28da30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Temp0028da30 {
    s16 unk0;
    u8 pad2[0x20 - 2];
    s16 unk20;
    u8 pad22[0x42 - 0x22];
    s16 unk42;
    u8 pad44[0x62 - 0x44];
    s16 unk62;
} Temp0028da30;

typedef struct Obj0028da30Ret {
    u8 pad000[0x20];
    Temp0028da30 *unk20;
} Obj0028da30Ret;

typedef struct Arg0028da30 {
    s32 unk0;
    s16 unk4;
    u8 pad6[0xC - 6];
    s16 unkC;
} Arg0028da30;

/*rgp*/

void UiSelFrameInit_28da30(Arg0028da30 *arg0, s32 arg1, s32 arg2)
{
    Temp0028da30 *temp;

    temp = ((Obj0028da30Ret *)UiFindWidget_290460(arg1, arg2))->unk20;
    arg0->unk4 = 0;
    temp->unk0 = 8;
    temp->unk20 = 0x18;
    temp->unk42 = 0x18;
    temp->unk62 = 8;
    arg0->unk0 = arg1;
    arg0->unkC = 2;
}
