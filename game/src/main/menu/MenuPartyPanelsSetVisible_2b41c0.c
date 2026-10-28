/* rgp:protos */
#define RGP_SELF_MenuPartyPanelsSetVisible_2b41c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Ctx;

typedef struct {
    u8 pad0[0x16];
    s16 unk16;
} Elem;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u16 D_0047ED40[3];
extern s32 D_00482360;
extern s32 D_00482364;

s32 MenuPartyPanelsSetVisible_2b41c0(s32 arg0) {
    Ctx *c;
    s32 i;
    s32 j;
    s32 k;
    s32 a;
    s32 b;
    s32 e;

    c = ((Ctx *)GetGameData_1fede0());
    i = 0;
    a = arg0 & 0xFF;
    for (; i < PartyCountMembers_3c2010(c->unk18, 1, 1); i++) {
        UiSetWidgetsVisibleById_291110(D_00482360, (i + 0xDF) & 0xFFFF, a, 1);
    }
    if (((Elem *)UiEntryListFindByTag_28ea40(D_00482364, 0x13))->unk16 != 0) {
        goto end;
    }
    b = (u8)arg0;
    UiSetWidgetsVisibleById_291110(D_00482360, 0xD6, b, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x17E, 0, 1);
    for (j = 0; j < PartyCountReserve_3c1c20(c->unk18, 1, 1); j++) {
        UiSetWidgetsVisibleById_291110(D_00482360, (j + 0xE2) & 0xFFFF, b, 1);
        k = 0;
        do {
            UiSetWidgetsVisibleById_291110(D_00482360, (j + D_0047ED40[k]) & 0xFFFF, b, 1);
            k++;
        } while (k < 3);
    }
    arg0 &= 0xFF; e = arg0;
    UiSetWidgetsVisibleById_291110(D_00482360, 0x104, e, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x103, e, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0x102, e, 1);
    UiSetWidgetsVisibleById_291110(D_00482360, 0xD9, e, 1);
end:
    return 1;
}
