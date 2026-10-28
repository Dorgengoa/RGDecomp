/* rgp:protos */
#define RGP_SELF_PlacePointTableParse_386680 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483404;
extern void *D_00483408;
extern s32 D_0048340C;
extern u8 D_00454330[];

void PlacePointTableParse_386680(s32 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u128 spF20;
    u8 sp50[0xed0] __attribute__((aligned(16)));
    s32 i;

    arg0[0] = 0;
    arg0[1] = 0;
    if (arg1 == 0 || arg2 == 0) return;
    D_00483408 = &spF20;
    D_00483404 = arg0;
    D_0048340C = arg1;
    spF20 = 0;
    arg0[0] = ((s32)ConstructNewArray_100710(((s32 *)MemStackNew_14e1b0(0x2010, arg1)), PlacePointCtor_386790, 0, 0x20, 0x100));
    TextReaderCtor_15f140(sp50);
    BuildKeywordHashTable_15f270(sp50, D_00454330);
    TextReaderOpen_15f1b0(sp50, arg2, arg3);
    TextReaderParseAll_15f3f0(sp50);
    arg0[2] = (s32)((s32 *)MemStackNew_14e1b0(arg0[1] * 8, arg1));
    for (i = 0; i < arg0[1]; i++) {
        *(s32 *)arg0[2] = arg0[0] + (i << 5);
    }
}
