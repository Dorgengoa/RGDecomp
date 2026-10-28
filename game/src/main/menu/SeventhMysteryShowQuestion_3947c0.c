/* rgp:protos */
#define RGP_SELF_SeventhMysteryShowQuestion_3947c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048347C;
extern s32 D_004834B0;
extern u8 D_004E9550[0x50];
extern s32 D_004E95A0[0x100];

s32 SeventhMysteryShowQuestion_3947c0(s32 arg0) {
    s32 *p;
    s32 i;

    p = &D_004E95A0[(s16)arg0];
    UiSetTextString_28f510(D_004E9550, 4, MsgTableLookup_28aa30(D_0048347C, *p * 5 + 1), 1);
    RandUniqueFill_3950e0(&D_004834B0, 4, 4);
    i = 0;
    do {
        UiSetTextString_28f510(D_004E9550, 8, MsgTableLookup_28aa30(D_0048347C, (&D_004834B0)[i] + 2 + *p * 5) + 1, i);
        i++;
    } while (i < 4);
    return 1;
}
