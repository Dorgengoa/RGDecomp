/* rgp:protos */
#define RGP_SELF_MapAreaCollectVisibleTreeMaybe_1db930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S001db930 {
    u8 pad0[0x128];
    void *unk128[20];
    void *unk178[20];
    s16 unk1C8;
    s16 unk1CA;
} S001db930;

/*rgp*/
/*rgp*/

s32 MapAreaCollectVisibleTreeMaybe_1db930(S001db930 *arg0, void **arg1, s32 arg2) {
    s32 n;
    void **p;
    s32 i;

    if (arg1 == NULL || arg2 <= 0) return 0;
    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(arg0)) == 0) return 0;
    if (((unsigned char)MapDataIsHidden_1e7c10(arg0)) != 0) return 0;
    n = 0;
    arg1[n++] = arg0;
    p = arg0->unk178;
    i = 0;
    while (i < arg0->unk1CA) {
        if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(*p)) != 0 && ((unsigned char)MapDataIsHidden_1e7c10(*p)) == 0) {
            arg1[n++] = *p;
        }
        i++;
        p++;
    }
    p = arg0->unk128;
    i = 0;
    while (i < arg0->unk1C8) {
        if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(*p)) != 0 && ((unsigned char)MapDataIsHidden_1e7c10(*p)) == 0) {
            arg1[n++] = *p;
        }
        i++;
        p++;
    }
    return n;
}
