/* rgp:protos */
#define RGP_SELF_MenuItemModelZoomOutState_2a7b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct {
    u8 pad0[0x14];
    s16 x14;
    s16 x16;
} Grp;

typedef struct {
    u8 pad0[0x2C];
    s32 x2C;
    s32 x30;
} Map;

typedef struct {
    u8 pad0[0x170];
    f32 x170;
} Cam;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004659F0[0x400];
extern f32 D_0047D578;
extern f32 D_0047D5A0;
extern f32 D_0047D5A4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern Map *D_00482374;
extern s16 D_00482488;
extern Cam *D_004824BC;
extern f32 D_004824E0;
extern f32 D_004824E4;

s32 MenuItemModelZoomOutState_2a7b50(s32 pad0, s32 arg1)
{
    Vec v __attribute__((aligned(16)));
    s16 n;
    u8 *p;
    u32 c;
    Grp *g;
    s32 k;
    s32 w;
    f32 e;
    Cam *cam;

    if (arg1 != 0) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x140, 0.0f, D_0047D5A0, -1.0f);
    }
    n = 0;
    D_004824E0 -= D_0047D578;
    if (D_004824E0 <= 0.0f) {
        D_004824E0 = 0.0f;
        n++;
    }
    D_004824E4 -= D_0047D5A4;
    if (D_004824E4 <= 0.0f) {
        D_004824E4 = 0.0f;
        n++;
    }
    e = D_004824E0;
    cam = D_004824BC;
    c = 0x10;
    p = (u8 *)&v;
    if (p != NULL) {
        do {
            *p = 0;
            c--;
            p++;
        } while (c != 0);
    }
    v.x = e;
    v.y = e;
    v.z = e;
    ModelSetScale_150ff0(cam, &v);
    D_004824BC->x170 = D_004824E4;
    if (n >= 2) {
        D_00482488 = 0;
        MenuItemModelRelease_2a7130();
        MenuItemTempRBufFree_2a89d0();
        MenuInvGridHighlightMaybe_2a0050(D_00482374, 0);
        g = ((Grp *)UiEntryListFindByTag_28ea40(D_00482364, 3));
        k = D_00482374->x30;
        w = *(s32 *)D_004659F0;
        g->x14 = k % w;
        g->x16 = k / w;
        MenuItemSelectTab_2b3550(D_00482374->x2C, 0, 1);
        D_00482374->x2C = -1;
        D_00482374->x30 = -1;
        StateMachineSetState_28ede0(D_0048235C, 9, 0);
    }
    return 1;
}
