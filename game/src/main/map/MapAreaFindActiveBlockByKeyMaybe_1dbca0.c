/* rgp:protos */
#define RGP_SELF_MapAreaFindActiveBlockByKeyMaybe_1dbca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *MapAreaFindActiveBlockByKeyMaybe_1dbca0(void *p0, s32 key)
{
    void **pp;
    s32 i;

    if (((unsigned char)MapDataIsLoaded_1e79d0((int)p0)) == 0) {
        return 0;
    }
    if (key < ((short)MapIdIndexGetMinId_1ddbe0((u8 *)p0 + 0x10C)) || ((short)MapIdIndexGetMaxId_1ddbf0((void *)((s32)p0 + 0x10C))) < key) {
        return 0;
    }
    pp = (void **)((u8 *)p0 + 0x178);
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x1CA)) {
        if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(*pp)) != 0) {
            if (key == ((short)MapDataGetKeyMaybe_1e7bc0(*pp))) {
                return *pp;
            }
        }
        i++;
        pp++;
    }
    return 0;
}
