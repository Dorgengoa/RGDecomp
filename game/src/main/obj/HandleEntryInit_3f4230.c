/* rgp:protos */
#define RGP_SELF_HandleEntryInit_3f4230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003f4230 {
    s32 f00;
    s16 f04;
    s16 f06;
    s16 f08;
    u8 pad00A[0x2];
    s32 f0C;
    s32 f10;
    s32 f14;
    u8 b18 : 1;
} Obj_FUN_003f4230;

void HandleEntryInit_3f4230(Obj_FUN_003f4230 *o)
{
    o->f00 = 0;
    o->f06 = -1;
    o->f04 = 0;
    o->f08 = -1;
    o->f0C = -1;
    o->f10 = 0;
    o->f14 = 0;
    o->b18 = 0;
}
