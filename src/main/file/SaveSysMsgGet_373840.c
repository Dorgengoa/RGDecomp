#include "types.h"

typedef struct { s32 v[27]; } Arr27;
typedef struct Obj00373840 {
    s16 unk0;
    u8 unk2;
    u8 pad3;
    Arr27 unk4;
} Obj00373840;

extern u8 D_004E9080[0x400];
extern u8 D_004E9082[0x400];
extern Arr27 D_004E9084;

void SaveSysMsgGet_373840(Obj00373840 *arg0)
{
    arg0->unk0 = (*(s16 *)D_004E9080);
    arg0->unk2 = (*(u8 *)D_004E9082);
    arg0->unk4 = D_004E9084;
}
