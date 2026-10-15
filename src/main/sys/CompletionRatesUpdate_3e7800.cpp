#include "types.h"

typedef struct {
    u16 a;
    u16 pad : 2;
    u16 v : 10;
    u16 pad2 : 4;
} Item;

typedef struct {
    u8 pad0[0x16A0];
    s16 n;
    Item items[1];
} Ui;

typedef struct {
    u8 pad0[0x10];
    Ui *ui;
    u8 pad14[4];
    s32 f18;
} Self;

extern "C" {
u8 InvHasItemInCategory_3c7f40(s32, s32, s32, s32);
s32 StateVarSet_3cc9c0(Ui *, s32, s16, s32);
s32 StateVarGet_3ccac0(Ui *, s32);
void StateFlagSet_3ccb70(Ui *, s32, bool, s32);
extern s32 D_00466B40[];
}

extern "C" s32 CompletionRatesUpdate_3e7800(Self *self) {
    s32 total = 0;
    s32 got = 0;
    s32 i;
    s32 pct;
    s32 pct2;
    bool flag;
    Ui *ui;
    s32 n;
    s32 cnt;
    Item *it;
    s32 j;
    f32 avg;

    i = 0;
    for (;;) {
        s32 id = D_00466B40[i];
        if (id < 0) {
            break;
        }
        u8 ok = InvHasItemInCategory_3c7f40(self->f18, id, 2, 0);
        total++;
        if (ok) {
            got++;
        }
        i++;
    }
    pct = (s32)(100.0f * ((f32)got / (f32)total));
    flag = 0;
    if (pct < 0) {
        pct = 0;
    } else if (pct >= 100) {
        pct = 100;
        flag = 1;
    }
    StateFlagSet_3ccb70(self->ui, 0x1E1, flag, 0);
    StateVarSet_3cc9c0(self->ui, 0x65, pct, 0);
    pct = (s32)(100.0f * ((f32)(StateVarGet_3ccac0(self->ui, 5) - 1) / 6.0f));
    flag = 0;
    if (pct < 0) {
        pct = 0;
    } else if (pct >= 100) {
        flag = 1;
        pct = 100;
    }
    StateFlagSet_3ccb70(self->ui, 0x1E3, flag, 0);
    StateVarSet_3cc9c0(self->ui, 0x67, pct, 0);
    ui = self->ui;
    n = ui->n;
    pct = (s32)(100.0f * ((f32)n / 100.0f));
    flag = 0;
    if (pct < 0) {
        pct = 0;
    } else if (pct >= 100) {
        pct = 100;
    }
    cnt = 0;
    it = ui->items;
    for (j = 0; j < n; j++, it++) {
        if (it->v > 0) {
            cnt++;
        }
    }
    pct2 = (s32)(100.0f * ((f32)cnt / 50.0f));
    if (pct2 < 0) {
        pct2 = 0;
    } else if (pct2 >= 100) {
        pct2 = 100;
    }
    if (pct >= 100 && pct2 >= 100) {
        flag = 1;
    }
    StateFlagSet_3ccb70(ui, 0x1E6, flag, 0);
    avg = (pct + pct2) / 2;
    StateVarSet_3cc9c0(self->ui, 0x6A, avg, 0);
    return 1;
}
