#include "types.h"

typedef struct E2a2cf0 {
    u8 pad00[4];
    s16 f4;
    s16 f6;
    u8 pad08[4];
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
} E2a2cf0;

typedef struct R2a2cf0 {
    u8 pad00[0x2C];
    s16 f2C;
} R2a2cf0;

typedef struct Q2a2cf0 {
    u8 pad00[0x10];
    R2a2cf0 *f10;
} Q2a2cf0;

typedef struct M2a2cf0 {
    u8 pad00[0x18];
    s32 f18;
} M2a2cf0;

extern E2a2cf0 *UiGetWidgetSprite_28fe10(s32 a, s32 b, s32 c);
extern M2a2cf0 *GetGameData_1fede0(void);
extern Q2a2cf0 *InvFindByCategoryIndex_3c86e0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void UiSetItemIconUv_288e50(E2a2cf0 *e, s32 a, s32 b, s32 c);

s32 MenuItemCategoryIconsFill_2a2cf0(s32 *p, s32 arg1)
{
    E2a2cf0 *base;
    M2a2cf0 *m;
    Q2a2cf0 *q;
    s32 i;
    s32 j;
    s32 k;
    s32 row;

    base = UiGetWidgetSprite_28fe10(*p, arg1, 0);
    if (base == 0) {
        return 0;
    }
    m = GetGameData_1fede0();
    for (i = 0; i < 3; i++) {
        row = i * 3;
        for (j = 0; j < 3; j++) {
            base[row + j].fE = 0;
            base[row + j].f6 = 0;
            base[row + j].fC = 0;
            base[row + j].f4 = 0;
            q = InvFindByCategoryIndex_3c86e0(m->f18, 2, 0, j, i, 0);
            if (q != 0) {
                UiSetItemIconUv_288e50(&base[j + row], q->f10->f2C, 0x28, 0x2D);
            }
        }
    }
    for (k = 0; k < 3; k++) {
        base[k + 9].fE = 0;
        base[k + 9].f6 = 0;
        base[k + 9].fC = 0;
        base[k + 9].f4 = 0;
        q = InvFindByCategoryIndex_3c86e0(m->f18, 3, 0, k, 0, 0);
        if (q != 0) {
            UiSetItemIconUv_288e50(&base[k + 9], q->f10->f2C, 0x28, 0x2D);
        }
    }
    for (k = 0; k < 8; k++) {
        base[k + 12].fE = 0;
        base[k + 12].f6 = 0;
        base[k + 12].fC = 0;
        base[k + 12].f4 = 0;
        q = InvFindByCategoryIndex_3c86e0(m->f18, 4, 0, k, 0, 0);
        if (q != 0) {
            UiSetItemIconUv_288e50(&base[k + 12], q->f10->f2C, 0x28, 0x2D);
        }
    }
    return 1;
}
