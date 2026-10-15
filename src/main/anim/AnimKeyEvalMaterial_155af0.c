#include "types.h"

typedef void (*Fn155af0)(u8 *, u8 *, f32);
extern Fn155af0 D_0047DEF0;
extern Fn155af0 D_0047DF00;

void AnimKeyEvalMaterial_155af0(u8 *arg0, u8 *arg1, f32 fparg0) {
    s32 i;
    s32 n;
    u8 *p;
    s32 type;
    u8 *d;
    Fn155af0 fn;

    p = arg1 + 0x10;
    n = *(s32 *)(arg1 + 0xC);
    *(s32 *)(arg0 + 0x4) = 0;
    *(s32 *)(arg0 + 0x0) = 0;
    for (i = 0; i < n; i++, p += 8) {
        type = *(s32 *)(p + 0x0);
        d = *(u8 **)(p + 0x4);
        switch (type) {
        case 5:
            *(s32 *)(arg0 + 0x0) = 0x3F800000;
            fn = (&D_0047DF00)[*d];
            if (fn != 0) {
                fn(arg0 + 0x10, d, fparg0);
            }
            break;
        case 6:
            *(s32 *)(arg0 + 0x4) = 0x3F800000;
            fn = (&D_0047DEF0)[*d];
            if (fn != 0) {
                fn(arg0 + 0x20, d, fparg0);
            }
            break;
        }
    }
}
