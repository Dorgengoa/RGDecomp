#include "types.h"


extern void TextStyleSetOutlineMode_26f160(void *arg0, s32 arg1);
extern void MesWinSetFrameType_272b30(s32 xa0, s32 arg0);
extern void MesWinSetSeEnabled_272b50(void *arg0, s32 arg1);
extern void MesWinSetFixedPos_272b70(void *arg0, s32 arg1);

void MesWinSetStyle_276d60(void *arg0, s32 arg1)
{
    s32 u;
    switch (arg1) {
    case 0:
        MesWinSetFrameType_272b30(u, 1);
        TextStyleSetOutlineMode_26f160(arg0, 5);
        MesWinSetFixedPos_272b70(arg0, 0);
        MesWinSetSeEnabled_272b50(arg0, 1);
        return;
    case 1:
        MesWinSetFrameType_272b30(u, 0);
        TextStyleSetOutlineMode_26f160(arg0, 5);
        MesWinSetFixedPos_272b70(arg0, 1);
        MesWinSetSeEnabled_272b50(arg0, 0);
        *(s8*)((u8 *)arg0 + 0x1DEE) = 0;
        return;
    }
}
