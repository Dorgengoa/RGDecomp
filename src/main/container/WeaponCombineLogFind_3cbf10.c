#include "types.h"

typedef struct E {
    s16 key;
    u8 flag;
    u8 pad;
} E;

typedef struct S {
    u8 pad[0x16A0];
    s16 n;
    E e[1];
} S;

E *WeaponCombineLogFind_3cbf10(S *self, s32 arg1, s32 arg2)
{
    s32 lo;
    s32 hi;
    s32 mid;
    E *e;
    s32 flag;
    s32 key;

    lo = 0;
    hi = self->n - 1;
    while (hi >= lo) {
        mid = lo + ((hi - lo) + 1) / 2;
        e = &self->e[mid];
        key = e->key;
        flag = e->flag & 1;
        if (key == arg1) {
            if ((u8)flag == (u8)arg2) {
                return e;
            }
            if (flag == 0 && arg2 != 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } else if (key < arg1) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return NULL;
}
