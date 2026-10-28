/* rgp:protos */
#define RGP_SELF_MenuCharaSelTabsLayoutMaybe_356600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s16 x, y; } P;
typedef struct { P e[12]; } Tab;
typedef struct { s16 v[8]; } Row;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Tab D_00453D20;
extern Tab D_00453D50;
extern f32 D_0047D288;
extern s16 D_0047F7D0;
extern s16 D_0047F7D2;
extern s16 D_0047F7D4;

s32 MenuCharaSelTabsLayoutMaybe_356600(s8 *self, s32 id, s32 sel) {
    s16 c[3];
    Row a[3] __attribute__((aligned(16)));
    Row b[3] __attribute__((aligned(16)));
    s8 *p;
    s8 *q;
    s32 n;
    s32 i;

    p = ((s8 *)GetGameData_1fede0());
    if (p == 0) {
        return 1;
    }
    {
        P *s = D_00453D20.e;
        P *d = (P *)a;
        s32 k = 12;
        do {
            k--;
            d->x = s->x;
            d->y = s->y;
            s++;
            d++;
        } while (k > 0);
    }
    {
        P *s = D_00453D50.e;
        P *d = (P *)b;
        s32 k = 12;
        do {
            k--;
            d->x = s->x;
            d->y = s->y;
            s++;
            d++;
        } while (k > 0);
    }
    n = PartyCountMembers_3c2010(*(s32 *)(p + 0x18), 1, 1);
    if (sel >= n) {
        sel = n - 1;
    }
    p = ((s8 *)UiFindWidget_290460(*(s32 *)(self + 0x5C), id));
    if (p == 0) {
        return 0;
    }
    q = *(s8 **)(p + 0x20);
    if (q == 0) {
        return 0;
    }
    *(s16 *)(q + 0x20) = a[sel].v[0];
    *(s16 *)(q + 0x22) = a[sel].v[1];
    *(s16 *)(q + 0x24) = a[sel].v[2];
    *(s16 *)(q + 0x26) = a[sel].v[3];
    *(s16 *)(q + 0x28) = a[sel].v[4];
    *(s16 *)(q + 0x2A) = a[sel].v[5];
    *(s16 *)(q + 0x2C) = a[sel].v[6];
    *(s16 *)(q + 0x2E) = a[sel].v[7];
    *(s16 *)(q + 0x40) = b[sel].v[0];
    *(s16 *)(q + 0x42) = b[sel].v[1];
    *(s16 *)(q + 0x44) = b[sel].v[2];
    *(s16 *)(q + 0x46) = b[sel].v[3];
    *(s16 *)(q + 0x48) = b[sel].v[4];
    *(s16 *)(q + 0x4A) = b[sel].v[5];
    *(s16 *)(q + 0x4C) = b[sel].v[6];
    *(s16 *)(q + 0x4E) = b[sel].v[7];
    if (sel == 0) {
        p = ((s8 *)UiFindWidget_290460(*(s32 *)(self + 0x5C), 0xC2));
        if (p == 0) {
            return 0;
        }
        q = *(s8 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        *(s16 *)(q + 0x2E) = 0;
        *(s16 *)(q + 0x26) = 0;
        *(s16 *)(q + 0x2C) = 0;
        *(s16 *)(q + 0x24) = 0;
    } else {
        p = ((s8 *)UiFindWidget_290460(*(s32 *)(self + 0x5C), 0xC2));
        if (p == 0) {
            return 0;
        }
        q = *(s8 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        *(s16 *)(q + 0x2E) = 0xE;
        *(s16 *)(q + 0x26) = 0xE;
        *(s16 *)(q + 0x2C) = 0xE;
        *(s16 *)(q + 0x24) = 0xE;
    }
    if (sel == 2) {
        p = ((s8 *)UiFindWidget_290460(*(s32 *)(self + 0x5C), 0xC2));
        if (p == 0) {
            return 0;
        }
        q = *(s8 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        *(s16 *)(q + 0xCE) = 0;
        *(s16 *)(q + 0xC6) = 0;
        *(s16 *)(q + 0xCC) = 0;
        *(s16 *)(q + 0xC4) = 0;
    } else {
        p = ((s8 *)UiFindWidget_290460(*(s32 *)(self + 0x5C), 0xC2));
        if (p == 0) {
            return 0;
        }
        q = *(s8 **)(p + 0x20);
        if (q == 0) {
            return 0;
        }
        *(s16 *)(q + 0xCE) = 0xE;
        *(s16 *)(q + 0xC6) = 0xE;
        *(s16 *)(q + 0xCC) = 0xE;
        *(s16 *)(q + 0xC4) = 0xE;
    }
    c[0] = D_0047F7D0;
    c[1] = D_0047F7D2;
    c[2] = D_0047F7D4;
    UiSetWidgetPos_290f60(*(s32 *)(self + 0x5C), id, c[sel], 0x10);
    for (i = 0; i < n; i++) {
        u16 id = i + 0x1A1;
        if (i == sel) {
            UiSetWidgetColor_2905b0(*(s32 *)(self + 0x5C), id, 1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(*(s32 *)(self + 0x5C), id, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        }
    }
    return 0;
}
