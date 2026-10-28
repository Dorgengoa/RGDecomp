/* rgp:protos */
#define RGP_SELF_SysCfgParse_1c2950 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;
extern u8 D_0044AFF0[];
struct Obj0 { s32 m00; s32 m04; };
struct Obj1 { s32 m00; s32 m04; };
void SysCfgParse_1c2950(s32 p0, s32 p1)
{
    u128 vF00[3];
    u128 v30[237];
    struct Obj1 *l1;
    struct Obj0 *l2;
    s32 l0;
    if (p0 != 0) {
        l1 = (struct Obj1 *)vF00;
        l2 = (struct Obj0 *)D_0044AFF0;
        l0 = 5;
        do {
            l1->m00 = l2->m00;
            l1->m04 = l2->m04;
            l0 = (l0 + -1);
            l1 = (struct Obj1 *)((u8 *)l1 + 8);
            l2 = (struct Obj0 *)((u8 *)l2 + 8);
        } while (l0 > 0);
        TextReaderCtor_15f140(v30);
        BuildKeywordHashTable_15f270(v30, vF00);
        TextReaderOpen_15f1b0(v30, p0, p1);
        TextReaderParseAll_15f3f0(v30);
        return;
    }
}
