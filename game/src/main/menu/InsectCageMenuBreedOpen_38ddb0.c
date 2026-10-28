/* rgp:protos */
#define RGP_SELF_InsectCageMenuBreedOpen_38ddb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcpy(s32, s32);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_0047FBD8;
extern s32 D_00483304;
extern u8 D_004E94A0[];
extern u8 D_004E94C0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
    u8 pad00A[0x6];
    s16 m10;
};

s32 InsectCageMenuBreedOpen_38ddb0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s16 t0;
    s32 t1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 t2;
    s32 r7;
    s32 r8;
    s32 rv9;
    s32 rv10;

    D_0047FBD8 = 0;
    r0 = ((short)InsectCageMenuGetCursorSlot_391000());
    p0->m10 = r0;
    r1 = MenuObjCountActive_390ec0();
    p0->m08 = (r1 + -1);
    t0 = p0->m10;
    t1 = *(s32 *)((u8 *)D_004E94A0 + (t0 << 2));
    r2 = (MenuCursorObjSetOwner_386270(D_004E94C0, t1), (s32)0);
    r3 = InsectCageMenuSetDrawFlag_390a80(1, 1);
    r4 = InsectCageMenuSetStateFlagMaybe_390aa0(6, 1);
    r5 = UiSetWidgetVisible_290010(p1, 0x7616, 1, -1);
    r6 = InsectCageMenuMsgLookup_389d30(0x4CF);
    t2 = D_00483304;
    r7 = ((s32)strcpy((t2 + 0xE00), r6));
    r8 = ScreenGetWidth_390d10();
    rv9 = r8;
    rv10 = (r8 >> 1);
    if (r8 < 0) {
        rv9 = (r8 + 1);
        rv10 = ((r8 + 1) >> 1);
    }
    UiSetTextCenteredX_28f300(p1, 0x7616, rv10, 0);
    return 1;
}
