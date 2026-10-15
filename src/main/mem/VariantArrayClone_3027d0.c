#include "types.h"

extern void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 VariantClone_302b10(u8 *, u8 *, s32, s32);

typedef struct {
    s32 unk0;
    u8 *unk4;
    s32 unk8;
} T3027d0;

static inline u8 *get3027d0(T3027d0 *a, s32 i)
{
    if (a->unk4 == NULL || i < 0 || a->unk8 <= i) {
        return NULL;
    }
    return a->unk4 + i * 5;
}

s32 VariantArrayClone_3027d0(T3027d0 *arg0, T3027d0 *arg1, s32 arg2, s32 arg3)
{
    s32 n;
    s32 i;
    u8 *p;

    arg0->unk0 = 0;
    arg0->unk4 = NULL;
    arg0->unk8 = 0;
    if (arg1 == NULL || arg2 == 0) {
        return 0;
    }
    if (arg1->unk0 == 0) {
        goto fail;
    }
    n = arg1->unk8;
    if (n < 0 || n > 0x20) {
    fail:
        return 0;
    }
    if (arg1->unk4 != NULL && n > 0) {
        p = (u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 5 + 0x10, arg2), 0, 0, 5, n);
        arg0->unk4 = p;
        if (p == NULL) {
            return 0;
        }
        arg0->unk8 = arg1->unk8;
        for (i = 0; i < arg0->unk8; i++) {
            if (VariantClone_302b10(arg0->unk4 + i * 5, get3027d0(arg1, i), arg2, arg3) == 0) {
                return 0;
            }
        }
    }
    arg0->unk0 = arg1->unk0;
    return 1;
}
