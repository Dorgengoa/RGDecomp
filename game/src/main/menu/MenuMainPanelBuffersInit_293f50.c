/* rgp:protos */
#define RGP_SELF_MenuMainPanelBuffersInit_293f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    void *p;
    s16 v[5];
} Req;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, const void *, u32);
extern void *memset(void *, s32, u32);
extern u8 D_00450300[];
extern u8 D_00450340[];
extern u8 D_004503C0[];
extern u8 D_00450480[];
extern u8 D_004504E0[];
extern u8 D_004507E0[];
extern u8 D_00450800[];
extern u8 D_004DB1B0[];

void MenuMainPanelBuffersInit_293f50(s8 *arg0) {
    Req req __attribute__((aligned(16)));
    u8 *d = D_004DB1B0;
    u8 *base;
    u8 *q;
    s8 *p;
    s32 i;
    u8 *r;
    s32 j;
    u16 id;
    u8 *src;
    s32 k;

    base = (u8 *)MemStackAllocQw_14d950(arg0, 0x40);
    i = 0;
    do {
        p = ((s8 *)UiFindWidget_290460(d, i + 0xD));
        if (p != NULL) {
            *(f32 *)(p + 0x18) = (f32)(i * 0x27 + 0x4C);
            memcpy(*(u8 **)(p + 0x20) = base + (i << 7), D_00450340, 0x80);
        }
        i++;
    } while (i < 8);

    q = (u8 *)MemStackAllocQw_14d950(arg0, 0x60);
    i = 0;
    do {
        p = ((s8 *)UiFindWidget_290460(d, i + 0x16));
        if (p != NULL) {
            *(f32 *)(p + 0x18) = (f32)(i * 0x27 + 0x4C);
            memcpy(*(u8 **)(p + 0x20) = q + i * 0xC0, D_004503C0, 0xC0);
        }
        i++;
    } while (i < 8);

    req.p = d;
    req.v[0] = 0x76;
    req.v[1] = 0x74;
    req.v[2] = 0x77;
    req.v[3] = 0x67;
    req.v[4] = 0x69;
    MenuPanelGridAlloc_28b660(arg0, &req);

    q = (u8 *)MemStackAllocQw_14d950(arg0, 0x2C);
    MemStackAllocQw_14d950(arg0, 0x10);
    UiSetWidgetSprites_290b90(d, 0x104, q);
    i = 0;
    do {
        memcpy(q, D_00450480, 0x60);
        i++;
        q += 0x60;
    } while (i < 7);
    *(s16 *)q = -1;

    q = (u8 *)MemStackAllocQw_14d950(arg0, 0x60);
    i = 0;
    do {
        UiSetWidgetSprites_290b90(d, i + 0xB8, q);
        UiSetWidgetSprites_290b90(d, i + 0xBE, q + 0x100);
        src = D_004504E0 + (i << 8);
        memcpy(q, src, 0x100);
        memcpy(q + 0x100, src, 0x100);
        i++;
        q += 0x200;
    } while (i < 3);

    q = (u8 *)MemStackAllocQw_14d950(arg0, 0x1A);
    r = (u8 *)MemStackAllocQw_14d950(arg0, 0x1A);
    j = 0;
    do {
        id = j + 0xCA;
        k = j * 0x1B + 0x40;
        UiSetWidgetSprites_290b90(d, id, q);
        UiSetWidgetSubItems_28eec0(d, id, r);
        memcpy(q, D_004507E0, 0x20);
        *(s16 *)(q + 2) = k;
        *(s16 *)(q + 0x20) = -1;
        q += 0x40;
        memcpy(r, D_00450800, 0x20);
        *(s16 *)(r + 2) = k;
        *(s16 *)(r + 0x20) = -1;
        j++;
        r += 0x40;
    } while (j < 6);

    q = (u8 *)MemStackAllocQw_14d950(arg0, 0x62);
    memset(q, 0, 0x620);
    i = 0;
    do {
        UiSetWidgetSprites_290b90(d, i + 0x166, q);
        memcpy(q, D_00450300, 0x40);
        i++;
        q += 0x40;
    } while (i < 0x18);
}
