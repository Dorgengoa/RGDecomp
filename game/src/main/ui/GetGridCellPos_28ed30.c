/* rgp:protos */
#define RGP_SELF_GetGridCellPos_28ed30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0028ed30 {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8 pad008[0x8];
    s16 f10;
    s16 f12;
} Obj_FUN_0028ed30;

void GetGridCellPos_28ed30(Obj_FUN_0028ed30 *o, s32 *a, s32 *b)
{
    *a = o->f00 + o->f10 * o->f04;
    *b = o->f02 + o->f12 * o->f06;
}
