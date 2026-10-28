/* rgp:protos */
#define RGP_SELF_PartyFindCharaById_3c2ed0 1
#define RGP_SELF_inner 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483890;

static inline s32 inner(u8 *arg0, s32 arg1) {
    s32 v;
    s32 t;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 10) {
        v = -1;
    } else {
        t = PartyCountMembers_3c2010(arg0, 1, 1);
        if (arg1 < t) {
            v = ((s16 *)(arg0 + 0x190))[arg1];
        } else if (arg1 < t + 7) {
            v = ((s16 *)(arg0 + 0x196))[arg1 - t];
        } else {
            v = -1;
        }
    }
    if (v < 0) {
        return 0;
    }
    return ((s32)CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), v));
}

s32 PartyFindCharaById_3c2ed0(u8 *arg0, int rgp_a1) {
    s32 idx;

    if (D_00483890 == NULL) {
        return 0;
    }
    idx = PartyFindSlotOfId_3c3070((void *)arg0, (int)rgp_a1);
    if (idx < 0) {
        return 0;
    }
    return inner(arg0, idx);
}
