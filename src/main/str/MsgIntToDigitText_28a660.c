#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    s8 *s;
    s32 x;
} E;

typedef struct {
    E e[10];
} T;

s32 CountDecimalDigits_28a770(s32);
s32 IntPow_28a7c0(s32, s32);
s8 *strcat(s8 *, s8 *);
extern s32 D_0044F890[20];

void MsgIntToDigitText_28a660(s8 *arg0, s32 arg1) {
    T tbl;
    s32 n;
    s32 cnt;
    s32 k;
    s32 d;
    s32 q;

    if (arg0 == NULL || arg1 < 0) {
        return;
    }
    tbl = *(T *)D_0044F890;
    n = arg1;
    *arg0 = 0;
    cnt = CountDecimalDigits_28a770(arg1);
    while (cnt > 0) {
        k = cnt - 1;
        if (k == 0) {
            strcat(arg0, tbl.e[n].s);
            return;
        }
        d = IntPow_28a7c0(10, k);
        q = n / d;
        strcat(arg0, tbl.e[q].s);
        cnt--;
        n -= q * d;
    }
}
