#include "types.h"

extern s8 *D_00481528;
extern s8 *D_0048152C;

s32 PathLocalize_1c28c0(s8 *arg0, s8 *arg1) {
    s8 *d;
    s8 *s;
    s8 *p;
    s8 c;
    s8 t;
    if ((arg0 == NULL) || (arg1 == NULL)) return 0;
    d = arg0;
    s = arg1;
    for (;;) {
        c = *s;
        s += 1;
        if (c == 0) {
            break;
        }
        if ((s8)(s32)c == 0x3F || (s8)(s32)c == 0x21) {
            p = ((s8)(s32)c == 0x21) ? D_0048152C : D_00481528;
            for (;;) {
                t = *p;
                p += 1;
                if (t == 0) {
                    break;
                }
                *d = t;
                d += 1;
            }
        } else {
            *d = c;
            d += 1;
        }
    }
    *d = 0;
    return 1;
}
