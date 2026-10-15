#include "types.h"
#pragma divbyzerocheck on

typedef struct Pt {
    s16 x;
    s16 y;
} Pt;

typedef struct Win {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    u8 pad10[0xC];
    s16 x1C;
} Win;

typedef struct Ent {
    u8 pad0[0x20];
    Win *w;
} Ent;

typedef struct Self {
    u8 pad0[0x14];
    s32 id;
    s16 x18;
    u8 pad1A;
    u8 x1B;
} Self;

extern void UiIconGetSheetPos_288720(s32, s32, s16 *, s16 *);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern Ent *UiFindWidget_290460(void *, s32);
extern char *strcpy(char *, const char *);
extern char D_00461378[];
extern const f32 D_0047D7EC __attribute__((section(".sdata")));
extern Pt D_0047EBB0[] __attribute__((section(".sdata")));
extern u8 D_004DB1B0[];

void DebugItemListShowIcon_299980(Self *self) {
    s16 a;
    s16 b;
    Pt pts[4];
    Pt *s;
    Pt *d;
    s32 n;
    Ent *e;
    u8 *base;
    Win *w;
    s32 id;
    Win *w2;
    s32 m;
    s16 px;
    s16 py;
    s32 wd;
    s32 h;
    f32 fx;
    f32 fy;

    if (self->x1B == 0) {
        return;
    }
    base = D_004DB1B0;
    if (base == 0) {
        return;
    }
    s = D_0047EBB0;
    d = pts;
    n = 4;
    do {
        n--;
        d->x = s->x;
        d->y = s->y;
        s++;
        d++;
    } while (n > 0);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x1CF, 1, 1);
    UiSetWidgetPos_290f60(D_004DB1B0, 0x1CF, 0x14A, 0x50);
    e = UiFindWidget_290460(base, 0x1CF);
    if (e == 0) {
        return;
    }
    w = e->w;
    if (w == 0) {
        return;
    }
    w->x4 = pts[self->x18].x + 4;
    w->x6 = (s32)(*(volatile f32 *)&D_0047D7EC * (f32)(pts[self->x18].y + 4));
    w->xC = 0x40;
    w->xE = 0x40;
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x1D0, 1, 1);
    UiSetWidgetPos_290f60(D_004DB1B0, 0x1D0, 2, 2);
    id = self->id;
    e = UiFindWidget_290460(base, 0x1D0);
    if (e == 0) {
        return;
    }
    w2 = e->w;
    if (w2 == 0) {
        return;
    }
    px = pts[self->x18].x;
    py = (s32)(D_0047D7EC * (f32)pts[self->x18].y);
    if (id >= 0) {
        m = id % 100 - 1;
        UiIconGetSheetPos_288720(id / 1000, id % 1000 / 100, &a, &b);
        if (m < 0 || m > 0x40) {
            m = 0;
        }
        h = 0x20;
        wd = h;
        if (id == 0x8FD) {
            h = 0x28;
            wd = h;
        }
        fx = (f32)(m % 8);
        fy = (f32)(m / 8 % 8);
        strcpy((char *)e + 4, D_00461378);
        if (px == -1) {
            px = wd;
        }
        if (py == -1) {
            py = h;
        }
        w2->x8 = (s32)((f32)a + fx * (f32)wd);
        if (!((f32)a + fx * (f32)wd < 992.0f)) {
            wd--;
        }
        w2->xA = (s32)((f32)b + fy * (f32)h);
        w2->xC = wd;
        w2->xE = h;
        w2->x4 = px;
        w2->x6 = py;
        w2->x1C = 2;
    } else {
        w2->xA = 0;
        w2->x8 = 0;
        w2->xE = 0;
        w2->xC = 0;
        w2->x6 = 0;
        w2->x4 = 0;
        w2->x1C = 2;
    }
}
