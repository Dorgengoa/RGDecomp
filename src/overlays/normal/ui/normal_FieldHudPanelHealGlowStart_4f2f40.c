#include "types.h"
/* normal 0x004F2F40 -- writes one 8-byte slot of p->f33C, then pushes the
 * matching 784-byte record at the gp pointer 0x00484414. */
typedef struct A {
    u8    pad000[0x18];
    void *f18;
} A;

typedef struct Slot {
    s32 f00;
    s16 f04;
    s16 f06;
} Slot;

typedef struct N {
    u8   pad000[0x33C];
    Slot f33C[3];
} N;

typedef struct Big {
    u8 pad000[784];
} Big;

extern void *D_00484414;          /* gp - 0xD5C */
extern u8    D_00526380[];

extern A   *func_1FEDE0(void);
extern s32  func_3C3070(void *p, s16 key);
extern void func_33BF40(void *p, u8 *q, s32 n);

void normal_FieldHudPanelHealGlowStart_4f2f40(N *p, s16 key, s16 v)
{
    A  *a;
    s32 i;

    a = func_1FEDE0();
    if (a == NULL) {
        return;
    }
    i = func_3C3070(a->f18, key);
    if (i < 0 || i > 2) {
        return;
    }
    {
        p->f33C[i].f04 = v;
        p->f33C[i].f00 = 0;
        p->f33C[i].f06 = key;
        if (D_00484414 != NULL) {
            func_33BF40(&((Big *)D_00484414)[i], D_00526380, 0x32B);
        }
    }
}
