/* rgp:protos */
#define RGP_SELF_InsectCageRecTableParse_391320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);
extern u8 D_00454350[0x400];
extern s8 D_00483438;
extern s32 D_0048343C;

void InsectCageRecTableParse_391320(s32 arg0, s32 arg1, s32 arg2)
{
    u8 sp40[0xED0] __attribute__((aligned(16)));
    s32 var_16;

    D_0048343C = 0;
    D_00483438 = 0;
    if (arg0 == 0 || arg1 == 0) {
        return;
    }
    D_0048343C = ((s32)MemStackNew_14e1b0(0xB90, arg0));
    var_16 = 0;
    do {
        memset((void *)(D_0048343C + var_16 * 0x94), 0, 0x94);
        var_16 += 1;
    } while (var_16 < 0x14);
    TextReaderCtor_15f140(sp40);
    BuildKeywordHashTable_15f270(sp40, D_00454350);
    TextReaderOpen_15f1b0(sp40, arg1, arg2);
    TextReaderParseAll_15f3f0(sp40);
}
