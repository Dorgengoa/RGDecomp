#include "types.h"

typedef struct E16f650 {
    s32 f00;
    s32 f04;
    s32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
} E16f650;

typedef struct H16f650 {
    s32 count;
    E16f650 *arr;
} H16f650;

extern H16f650 *D_00481194;

s32 AmixerCfgTrackEndCmd_16f650(void)
{
    H16f650 *h;
    E16f650 *arr;
    s32 n;
    s32 i;
    s32 j;
    s32 t0;
    s32 t4;
    s32 t8;
    f32 tC;
    f32 t10;
    f32 t14;
    f32 t18;
    f32 t1C;
    f32 t20;
    f32 *q;

    h = D_00481194;
    if (h == 0) {
        return 0;
    }
    n = h->count;
    arr = h->arr;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            q = &arr[j].f14;
            if (arr[i].f14 <= arr[j].f14) {
                continue;
            }
                t0 = arr[i].f00;
                t4 = arr[i].f04;
                t8 = arr[i].f08;
                tC = arr[i].f0C;
                t10 = arr[i].f10;
                t14 = arr[i].f14;
                t18 = arr[i].f18;
                t1C = arr[i].f1C;
                t20 = arr[i].f20;
                arr[i].f00 = arr[j].f00;
                arr[i].f04 = arr[j].f04;
                arr[i].f08 = arr[j].f08;
                arr[i].f0C = arr[j].f0C;
                arr[i].f10 = arr[j].f10;
                arr[i].f14 = *q;
                arr[i].f18 = arr[j].f18;
                arr[i].f1C = arr[j].f1C;
                arr[i].f20 = arr[j].f20;
                arr[j].f00 = t0;
                arr[j].f04 = t4;
                arr[j].f08 = t8;
                arr[j].f0C = tC;
                arr[j].f10 = t10;
                *q = t14;
                arr[j].f18 = t18;
                arr[j].f1C = t1C;
                arr[j].f20 = t20;
        }
    }
    return 1;
}
