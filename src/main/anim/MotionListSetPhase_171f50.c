#pragma optimization_level 3
#include "types.h"

typedef struct Arr00171f50 { u8 pad0[4]; s32 n; u8 *data; } Arr00171f50;

static inline u8 *at00171f50(Arr00171f50 *a, s32 i)
{
    s32 ok;

    if (a->data == NULL) {
        ok = 0;
    } else if (i >= 0) {
        if (i >= a->n) {
            ok = 0;
        } else {
            ok = 1;
        }
    } else {
        ok = 0;
    }
    if (ok != 0) {
        return a->data + i * 0x30;
    }
    return NULL;
}

void MotionListSetPhase_171f50(void *arg0, f32 fparg0)
{
    u8 *n;
    u8 *e;
    u8 *h;
    Arr00171f50 *q;
    u8 *r;
    f32 f;
    f32 v;
    s32 idx;

    for (n = *(u8 **)((u8 *)arg0 + 4); n != NULL; n = *(u8 **)n) {
        e = n + 0x10;
        if (e != NULL) {
            f = 0.0f;
            if (!(fparg0 < 0.0f) && (fparg0 <= 1.0f)) {
                h = *(u8 **)(e + 0xC);
                idx = *(s32 *)(e + 0x14);
                if (h == NULL) {
                    v = f;
                } else {
                    q = (Arr00171f50 *)(h + 0x10);
                    if (q == NULL) {
                        v = f;
                    } else {
                        r = at00171f50(q, idx);
                        if (r != NULL) {
                            v = fparg0 * (*(f32 *)(r + 0x28) - *(f32 *)(r + 0x24));
                        } else {
                            v = 0.0f;
                        }
                    }
                }
                *(f32 *)(e + 0x18) = v;
                *(f32 *)(e + 0x1C) = v;
            }
        }
    }
}
