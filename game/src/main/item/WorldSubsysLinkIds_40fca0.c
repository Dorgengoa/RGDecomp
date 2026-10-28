/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkIds_40fca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysLinkIds_40fca0(u8 *arg0, u8 *arg1, int rgp_a2, int rgp_a3) {
    s32 sp48[2];
    s32 k;
    s16 **pp;
    s32 id;
    u8 *q;
    u8 *p;

    if (arg1 == 0) {
        return 0;
    }
    k = *(s32 *)(arg1 + 0x84);
    if (k == 0) {
        return 0;
    }
    pp = *(s16 ***)(arg0 + 0x94);
    id=-1;
    if(pp!=0 && *pp!=0)id=**pp;
    q = arg0;
    if (arg0 != 0) {
        q += 0x88;
    }
    IterInit_370170(sp48, q, (int)rgp_a2, (int)rgp_a3);
    while ((p = ((u8 *)IterNext_370040(sp48))) != 0) {
        *(s32 *)(p + 0x10) = GroupGetRecordById_40e9d0(k, (long long)(id), *(s16 *)(p + 0x10));
        *(s32 *)(p + 0x14) = GroupGetRecordById_40e9d0(k, (long long)(id), *(s16 *)(p + 0x14));
        *(s32 *)(p + 0x18) = GroupGetRecordById_40e9d0(k, (long long)(id), *(s16 *)(p + 0x18));
        *(s32 *)(p + 0x1C) = GroupGetRecordById_40e9d0(k, (long long)(id), *(s16 *)(p + 0x1C));
    }
    return 1;
}
