/* rgp:protos */
#define RGP_SELF_WorldSubsysLinkIds_420640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysLinkIds_420640(u8 *arg0, u8 *arg1, int rgp_a2, int rgp_a3) {
    s32 sp48[2];
    s32 k;
    s16 **pp;
    s32 id;
    u8 *q;
    u8 *p;

    if (arg1 == 0) {
        return 0;
    }
    k = *(s32 *)(arg1 + 0x7C);
    if (k == 0) {
        return 0;
    }
    pp = *(s16 ***)(arg0 + 0x94);
    if (pp == 0) {
        return 0;
    }
    if (*pp == 0) {
        return 0;
    }
    id = **pp;
    q = arg0;
    if (arg0 != 0) {
        q += 0x88;
    }
    IterInit_370170(sp48, q, (int)rgp_a2, (int)rgp_a3);
    while ((p = ((u8 *)IterNext_370040(sp48))) != 0) {
        *(s32 *)(p + 0x4) = GroupGetRecordById_41fb10(k, id, *(s16 *)(p + 0x4));
        *(s32 *)(p + 0x8) = GroupGetRecordById_41fb10(k, id, *(s16 *)(p + 0x8));
        *(s32 *)(p + 0xC) = GroupGetRecordById_41fb10(k, id, *(s16 *)(p + 0xC));
    }
    return 1;
}
