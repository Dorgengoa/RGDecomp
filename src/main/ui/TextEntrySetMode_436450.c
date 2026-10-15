#include "types.h"

typedef struct E436450 {
    s16 h0;
    s16 h2;
} E436450;

typedef struct T436450 {
    E436450 e[6];
} T436450;

typedef struct O436450 {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
} O436450;

typedef struct A436450 {
    u8 pad0[4];
    s32 w4;
    u8 pad8[4];
    s32 wC;
    u8 pad10[0xE0 - 0x10];
    s16 hE0;
    u8 padE2[6];
    u8 bE8[0xAF];
    u8 b197[0xAF];
} A436450;

extern s32 MsgTableLookup_28aa30(s32, s32);
extern O436450 *UiEntryListFindByTag_28ea40(s32, s32);
extern void memcpy(void *, s32, s32);
extern T436450 D_004552D0;

void TextEntrySetMode_436450(A436450 *arg0, s64 arg1)
{
    T436450 tbl;
    O436450 *o;
    s32 id;
    s16 i;
    s16 t;
    s16 h;
    E436450 *src;
    E436450 *d;
    s32 n;
    s32 w;

    arg0->hE0 = arg1;
    t = arg1;
    if (t == 1 || t == 3) {
        id = 0x47E;
    } else if (t == 0) {
        id = 0x32;
    } else {
        id = 0x41A;
    }
    memcpy(arg0->bE8, MsgTableLookup_28aa30(arg0->wC, id), 0xAF);
    id = 0x41B;
    switch (arg0->hE0) {
    case 0:
        id = 0x41B;
        break;
    case 1:
        id = 0x41C;
        break;
    case 2:
        id = 0x41D;
        break;
    case 3:
        id = 0x41E;
        break;
    case 4:
        id = 0x41B;
        break;
    }
    memcpy(arg0->b197, MsgTableLookup_28aa30(arg0->wC, id), 0xAF);
    w = arg0->w4;
    if (w != 0) {
        d = tbl.e;
        src = D_004552D0.e;
        n = 6;
        do {
            n--;
            d->h0 = src->h0;
            d->h2 = src->h2;
            d++;
            src++;
        } while (n > 0);
        o = UiEntryListFindByTag_28ea40(w, 0x6D61);
        o->h4 = 0x12;
        o->h6 = 0xB;
        o->hC = 0x12;
        o->hE = 0;
        for (i = 0; tbl.e[i].h0 != -1; i++) {
            if (arg0->hE0 == tbl.e[i].h0) {
                o->hE = tbl.e[i].h2;
            }
        }
        if (arg0->hE0 == 4) {
            o->hE = 0;
            o->hC = 0;
        }
        o->h8 = 0x15;
        o->hA = 0x19;
    }
}
