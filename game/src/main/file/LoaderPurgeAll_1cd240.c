/* rgp:protos */
#define RGP_SELF_LoaderPurgeAll_1cd240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void LoaderPurgeAll_1cd240(u8 *arg0)
{
    void *arr[3];
    u8 *p;
    u32 n;
    s32 i;
    s16 *list;
    s32 cnt;
    s32 j;
    u8 *o;
    void **e;

    n = 12;
    p = (u8 *)arr;
    if (p != NULL) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    arr[0] = arg0 + 0x20;
    arr[1] = arg0 + 0x28;
    arr[2] = arg0 + 0x30;
    for (i = 0; i < 3; i++) {
        list = ((s16 *)S16ArrayGetData_1ce1c0(arr[i]));
        cnt = ((short)S16ArrayGetCount_1ce1b0(arr[i]));
        for (j = 0; j < cnt;) {
            o = ((u8 *)LoaderGetUnit_1cde10(arg0, *list));
            if (o != NULL) {
                *(s16 *)(o + 0x82) = 1;
            }
            j++;
            list++;
        }
    }
    LoaderTick_1ccc30(arg0);
}
