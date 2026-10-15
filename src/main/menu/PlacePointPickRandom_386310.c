#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad[0x20];
} E00386310;

f32 RandFloat_13c010(void);
s32 PlacePointCollectByKind_386430(s32, s32, E00386310 *, s32);
void Copy20Bytes_3869c0(s32, E00386310 *);
void PlacePointInit_3869f0(E00386310 *);

void PlacePointPickRandom_386310(s32 arg0, s32 arg1, s32 arg2)
{
    E00386310 arr[0x100];
    E00386310 *p;
    s32 cap;
    s32 n;
    s32 t;

    if (arg1 != 0) {
        cap = 0x100;
        p = arr;
        do {
            PlacePointInit_3869f0(p);
            p++;
        } while (p < &arr[0x100]);
        p = arr;
        n = 0;
        if (arg2 == 0) {
            n += PlacePointCollectByKind_386430(arg0, 0, p, 0x100);
        } else {
            t = PlacePointCollectByKind_386430(arg0, 1, p, 0x100);
            n += t;
            n += PlacePointCollectByKind_386430(arg0, 2, p + t, cap - t);
        }
        Copy20Bytes_3869c0(arg1, &arr[(s32)(((f32)n - 1.0f) * RandFloat_13c010())]);
    }
}
