#include "types.h"
#undef NULL
#define NULL 0

typedef struct {
    s32 *unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
} Obj0030D270;

static inline u32 find0030d270(Obj0030D270 *arg0, s32 arg1) {
    u32 i;
    s32 *p;
    if (arg0->unk0 == NULL) {
        return -1;
    }
    if (arg1 == 0) {
        return -1;
    }
    p = arg0->unk0;
    for (i = 0; i < arg0->unk4; i++, p++) {
        if (*p == arg1) {
            return i;
        }
    }
    return -1;
}

static inline bool removeat0030d270(Obj0030D270 *arg0, u32 idx) {
    u32 i;
    if (arg0->unk0 == NULL) {
        return false;
    }
    if (arg0->unk4 <= idx) {
        return false;
    }
    for (i = idx + 1; i < arg0->unk4; i++) {
        ((s32 *)((u8 *)arg0->unk0 - 4))[i] = arg0->unk0[i];
    }
    arg0->unk4--;
    for (arg0->unkC = 1; arg0->unkC < arg0->unk4; arg0->unkC <<= 1) {
    }
    return true;
}

extern "C" bool PtrArrayRemove_30d270(Obj0030D270 *arg0, s32 arg1) {
    return removeat0030d270(arg0, find0030d270(arg0, arg1));
}
