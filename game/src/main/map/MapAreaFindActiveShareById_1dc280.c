/* rgp:protos */
#define RGP_SELF_MapAreaFindActiveShareById_1dc280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *MapAreaFindActiveShareById_1dc280(void *p0, s32 key)
{
    void **pp;
    s32 i;

    if (((unsigned char)MapDataIsLoaded_1e79d0((int)p0)) == 0) {
        return 0;
    }
    if (key < ((short)MapIdIndexGetMinId_1ddbe0((u8 *)p0 + 0xFC)) || ((short)MapIdIndexGetMaxId_1ddbf0((void *)((s32)p0 + 0xFC))) < key) {
        return 0;
    }
    pp = (void **)((u8 *)p0 + 0x128);
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x1C8)) {
        if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980(*pp)) != 0) {
            if (key == ((short)MapDataGetId_1e7bd0(*pp))) {
                return *pp;
            }
        }
        i++;
        pp++;
    }
    return 0;
}
