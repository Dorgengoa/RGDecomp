/* rgp:protos */
#define RGP_SELF_InsectCageMenuSetCursorTarget_389790 1
#define RGP_SELF_flagA 1
#define RGP_SELF_flagB 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg {
    u8 pad0[0xA];
    s16 xA;
    u8 padC[4];
    s16 x10;
    s16 x12;
} Arg;

typedef struct Pos {
    s16 x;
    s16 y;
    u8 pad[0x1C];
} Pos;

typedef struct Mgr {
    u8 pad0[0x9C4];
    s32 x9C4;
    s32 x9C8;
} Mgr;

typedef struct Ent {
    u8 pad0[0x10];
    s16 x10;
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00483308;
extern s32 D_00483328;
extern s32 D_0048332C;
extern u8 D_004E94E0[0x400];

static inline u8 flagA(void) {
    return ((Mgr *)InsectCageMenuGetCursorObj_390f70())->x9C4 != 0;
}

static inline u8 flagB(void) {
    return ((Mgr *)InsectCageMenuGetCursorObj_390f70())->x9C8 != 0;
}

void InsectCageMenuSetCursorTarget_389790(s32 arg0, Arg *arg1, s32 arg2) {
    s32 sp5C;
    s32 sp58;
    Ent *e;
    s32 n;
    s32 sel;
    s32 i;
    Pos *a;
    Pos *b;

    switch (arg0) {
    case 1:
        InsectCageMenuGetIconPosMaybe_389c60(arg1->x10, arg1->x12, &sp5C, &sp58);
        sp5C -= 0x1E;
        sp58 += 0x1A;
        break;
    case 2:
        InsectCageMenuGetMarkerPos_389b80(((signed char)InsectCageGetType_3910c0()), arg1->x12, &sp5C, &sp58);
        InsectCageMenuSetRowMarker_389a80(0, 1, ((signed char)InsectCageGetType_3910c0()), arg1->x12);
        break;
    case 3:
        e = ((Ent *)UiEntryListFindDataByTag_28ec30(D_004E94E0, 0x753A));
        InsectCageMenuGetMarkerPos_389b80(e->x10, arg1->x12, &sp5C, &sp58);
        InsectCageMenuSetRowMarker_389a80(1, 1, e->x10, arg1->x12);
        break;
    case 0:
        UiGetWidgetPos_2910a0(D_00483308, 0x7562, &sp5C, &sp58);
        sel = arg1->x12;
        n = arg1->xA;
        if (((Mgr *)InsectCageMenuGetCursorObj_390f70()) != NULL && (flagA() || flagB())) {
            n = 2;
        }
        sp58 += sel * 0x18;
        for (i = 0; i <= n; i++) {
            if (sel != i) {
                UiSetSpriteW_28fbf0(D_00483308, 0x7562, 0x98, i + 4);
            } else {
                UiSetSpriteW_28fbf0(D_00483308, 0x7562, 1, i + 4);
                UiSetSpriteW_28fbf0(D_00483308, 0x7558, 0x98, 0);
                UiSetSpriteY_28fc90(D_00483308, 0x7558, i * 0x18 + 4, 0);
            }
        }
        sp5C -= 0x1E;
        sp58 += 6;
        break;
    case 4:
        UiGetWidgetAbsPos_290fc0(D_00483308, 0x75E4, &sp5C, &sp58);
        a = ((Pos *)UiGetWidgetSprite_28fe10(D_00483308, 0x75E4, 0));
        b = ((Pos *)UiGetWidgetSprite_28fe10(D_00483308, 0x75EE, 0));
        if (b != NULL) {
            sp5C -= a->x;
            sp58 -= a->y;
            sp5C += b[arg1->x10].x;
            sp58 += b[arg1->x10].y;
        }
        arg2 = 1;
        sp5C -= 0x20;
        break;
    }
    D_00483328 = sp5C;
    D_0048332C = sp58;
    InsectCageMenuCursorBobUpdate_389700(arg2);
}
