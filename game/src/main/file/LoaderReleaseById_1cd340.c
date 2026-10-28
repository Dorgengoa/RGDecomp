/* rgp:protos */
#define RGP_SELF_LoaderReleaseById_1cd340 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x82];
    s16 unk82;
} Obj001CD340;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void LoaderReleaseById_1cd340(s32 *arg0, s32 arg1)
{
    s32 sp4C;
    s32 sp48;
    s32 *arr[2];
    u8 *p;
    u32 n;
    s32 i;
    Obj001CD340 *o;
    s32 **q;

    if (arg1 < 0 || arg1 == 0x3FFF) {
        return;
    }
    p = (u8 *)arr;
    n = 8;
    if (p != NULL) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    arr[0] = arg0 + 0xC;
    arr[1] = arg0 + 8;
    for (i = 0; i < 2; i++) {
        q = &arr[i];
        o = ((Obj001CD340 *)LoaderQueueFindUnitById_1cdc70(arg0, arg1, *q, &sp4C));
        if (o != NULL) {
            LoaderUnitFree_1ce300(o, *arg0);
            q = &arr[i];
            S16ArrayRemoveAt_1ce0a0(*q, sp4C);
            while ((((__typeof__((S16ArrayGetChecked_1ce170(*q, sp4C)) + 0LL))(S16ArrayGetChecked_1ce170(*q, sp4C)) << 0x30) >> 0x30) == 0x3FFF) {
                S16ArrayRemoveAt_1ce0a0(*q, sp4C);
            }
            return;
        }
    }
    o = ((Obj001CD340 *)LoaderQueueFindUnitById_1cdc70(arg0, arg1, arg0 + 0xA, &sp48));
    if (o != NULL) {
        o->unk82 = 1;
    }
}
