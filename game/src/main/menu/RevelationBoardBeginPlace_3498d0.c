/* rgp:protos */
#define RGP_SELF_RevelationBoardBeginPlace_3498d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj003498d0 {
    u8 pad000[0x76C];
    s16 unk76C;
    s16 unk76E;
    s16 unk770;
} Obj003498d0;

s32 RevelationBoardBeginPlace_3498d0(Obj003498d0 *arg0, s32 arg1)
{
    switch (arg1) {
    case 1:
        arg0->unk76C = 1;
        arg0->unk76E = 1;
        arg0->unk770 = 0;
        break;
    case 2:
        arg0->unk76C = 2;
        arg0->unk76E = 1;
        arg0->unk770 = 0;
        break;
    default:
        arg0->unk76C = -1;
        arg0->unk76E = 0;
        arg0->unk770 = 0;
        break;
    }
}
