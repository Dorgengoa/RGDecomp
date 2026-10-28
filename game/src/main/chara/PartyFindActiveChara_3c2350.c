/* rgp:protos */
#define RGP_SELF_PartyFindActiveChara_3c2350 1
#define RGP_SELF_find 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
/*rgp*/
extern void *D_00483890;

static inline s32 find(void *arg0, s32 arg1)
{
    s32 i;

    if (arg1 < 0) {
        return -1;
    }
    for (i = 0; i < *(s16 *)((u8 *)arg0 + 0x18C); i++) {
        if (*(s16 *)((u8 *)arg0 + 0x190 + i * 2) == arg1) {
            return i;
        }
    }
    return -1;
}

static inline s32 get(void *arg0, s32 i)
{
    if (i < 0) {
        return -1;
    }
    if (i < *(s16 *)((u8 *)arg0 + 0x18C)) {
        return ((s16 *)((u8 *)arg0 + 0x190))[i];
    }
    return -1;
}

s32 PartyFindActiveChara_3c2350(void *arg0, s32 arg1)
{
    s32 var_5;
    s32 var_7;
    s32 n;

    if (D_00483890 == NULL) {
        return 0;
    }
    var_7 = find(arg0, arg1);
    if (var_7 < 0) {
        return 0;
    }
    if (D_00483890 == NULL) {
        return 0;
    }
    n = *(s16 *)((u8 *)arg0 + 0x18C);
    if (var_7 < 0 || var_7 >= n) {
        var_5 = -1;
    } else {
        var_5 = ((s16 *)((u8 *)arg0 + 0x190))[var_7];
    }
    if (var_5 < 0) {
        return 0;
    }
    return ((s32)CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), var_5));
}
