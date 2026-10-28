/* rgp:protos */
#define RGP_SELF_MapAreaTreeCollectCollTrisNearMaybe_1dac30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item001dac30 {
    u8 pad0[0x46];
    s16 unk46;
    u8 pad48[0x60 - 0x48];
} Item001dac30;

typedef struct S001dac30 {
    u8 pad0[0x128];
    void *unk128[20];
    void *unk178[20];
    s16 unk1C8;
    s16 unk1CA;
} S001dac30;

/*rgp*/
/*rgp*/
/*rgp*/

s32 MapAreaTreeCollectCollTrisNearMaybe_1dac30(S001dac30 *arg0, Item001dac30 *arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0)
{
    s32 n;
    s32 i;
    void **p;
    Item001dac30 *q;
    s32 j;

    if (arg1 == NULL || arg2 <= 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0(arg0)) == 0) {
        return 0;
    }
    n = 0;
    n += MapDataCollectCollTrisMaybe_1e6c80(arg0, arg1, arg2, arg3);
    p = arg0->unk128;
    for (i = 0; i < arg0->unk1C8; i++, p++) {
        if (n >= arg2) {
            break;
        }
        if (((unsigned char)MapDataIsLoaded_1e79d0(*p)) != 0) {
            n += MapDataCollectCollTrisMaybe_1e6c80(*p, arg1 + n, arg2 - n, arg3);
        }
    }
    q = arg1;
    for (j = 0; j < n; j++) {
        q->unk46 |= 0x800;
        q++;
    }
    p = arg0->unk178;
    for (i = 0; i < arg0->unk1CA; i++, p++) {
        if (n >= arg2) {
            break;
        }
        if (((unsigned char)MapDataIsLoaded_1e79d0(*p)) != 0) {
            n += MapBlockCollectCollTrisNearMaybe_1df8c0(*p, arg1 + n, arg2 - n, arg3, arg4, fparg0);
        }
    }
    return n;
}
