#include "types.h"
#include "vec.h"

typedef struct M4 { u128 a; u128 b; u128 c; u128 d; } M4;

extern void Mat34To44_13e1f0(M4 *, u8 *);
extern void ModelFrameSetMatrix_14a190(u8 *, M4 *);

static inline u8 *get(u8 *a, s32 i)
{
    if (i < 0 || !(i < *(s32 *)(a + 0x90))) {
        return NULL;
    }
    return (*(u8 ***)(a + 0x94))[i];
}

void DynClothRefreshPoseFramesMaybe_16a240(u8 *arg0)
{
    M4 m;
    s32 i;
    u8 *p;

    if (*(s32 *)(arg0 + 0x0) == 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0x150) == 0) {
        return;
    }
    for (i = 0; i < *(s32 *)(arg0 + 0x90); i++) {
        p = get(arg0, i);
        if (p == NULL) {
            continue;
        }
        if (*(s32 *)(*(u8 **)(arg0 + 0x98) + i * 0x50 + 0xC) == 0) {
            continue;
        }
        if (*(s8 *)(p + 0x2C) == 0) {
            m.a = *(u128 *)(p + 0x60);
            m.b = *(u128 *)(p + 0x70);
            m.c = *(u128 *)(p + 0x80);
            m.d = *(u128 *)(p + 0x90);
        } else {
            Mat34To44_13e1f0(&m, p + 0x30);
        }
        ModelFrameSetMatrix_14a190(p, &m);
    }
}
