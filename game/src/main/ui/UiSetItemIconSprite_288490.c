/* rgp:protos */
#define RGP_SELF_UiSetItemIconSprite_288490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 pad10[0xc];
    u16 unk1C;
} T288490_win;

/*rgp*/
extern char *strcpy(char *, const char *);
extern char D_00460EA8[];

T288490_win *UiSetItemIconSprite_288490(void *p0, u8 *obj, s32 id, s32 x0, s32 y0, s32 p5) {
    T288490_win *win;
    s32 w;
    s32 h;
    s32 idx;
    s16 x;
    s16 y;
    f32 cx;
    f32 cy;
    f32 fx;
    s16 px;
    s16 py;

    if (obj == NULL) {
        return NULL;
    }
    win = *(T288490_win **)(obj + 0x20);
    if (win == NULL) {
        return NULL;
    }
    x = x0;
    y = y0;
    if (id >= 0) {
        idx = (id % 100) - 1;
        UiIconGetSheetPos_288720(id / 1000, (id % 1000) / 100, &px, &py);
        if (idx < 0 || idx > 0x40) {
            idx = 0;
        }
        h = 0x20;
        w = h;
        if (id == 0x8FD) {
            h = 0x28;
            w = h;
        }
        cx = (f32)(idx % 8);
        cy = (f32)((idx / 8) % 8);
        strcpy((char *)(obj + 4), D_00460EA8);
        if (x == -1) {
            x = w;
        }
        if (y == -1) {
            y = h;
        }
        fx = cx * (f32)w;
        win->unk8 = (f32)px + fx;
        if (!((f32)px + fx < 992.0f)) {
            w -= 1;
        }
        win->unkA = (f32)py + cy * (f32)h;
        win->unkC = w;
        win->unkE = h;
        win->unk4 = x;
        win->unk6 = y;
        win->unk1C = 2;
    } else {
        win->unkA = 0;
        win->unk8 = 0;
        win->unkE = 0;
        win->unkC = 0;
        win->unk6 = 0;
        win->unk4 = 0;
        win->unk1C = 2;
    }
    return win;
}
