#include "types.h"

extern void InsectCageMenuSetCursorVisible_389d00(s32);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern void MenuObjSetResumeFx_384b60(s32);
extern void InsectCageMenuSetRowMarker_389a80(s32, s32, s32, s32);
extern void InsectCageMenuSetDrawFlag_390a80(s32, s32);
extern void InsectCageMenuItemGridSetStates_38f920(s32, s32);
extern s32 InsectCageMenuBuildObjList_3909a0(void);
extern s32 MenuObjCountActive_390ec0(void);
extern void MenuCursorObjSetVisible_386280(void *, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void InsectCageMenuSelectSlotObj_3904a0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s16 D_0047FBD4;
extern s16 D_0047FBD8;
extern s32 D_004832D8;
extern s16 D_00483334;
extern u8 D_004E94C0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
    u8 pad00A[0x6];
    s16 m10;
};

s32 InsectCageMenuRefreshSlots_3905a0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 l5;
    s32 r12;
    s32 r13;
    s16 t1;

    InsectCageMenuSetCursorVisible_389d00(0);
    InsectCageMenuSetStateFlagMaybe_390aa0(1, 0);
    InsectCageMenuSetStateFlagMaybe_390aa0(2, 0);
    InsectCageMenuSetStateFlagMaybe_390aa0(3, 0);
    t0 = D_004832D8;
    MenuObjSetResumeFx_384b60(t0);
    l5 = 0;
    do {
        InsectCageMenuSetRowMarker_389a80(0, 0, l5, -1);
        InsectCageMenuSetRowMarker_389a80(1, 0, l5, -1);
        l5 = (l5 + 1);
    } while (l5 < 3);
    InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
    InsectCageMenuSetDrawFlag_390a80(1, 0);
    InsectCageMenuSetDrawFlag_390a80(2, 0);
    InsectCageMenuItemGridSetStates_38f920(0, 0);
    D_0047FBD4 = -1;
    D_0047FBD8 = -1;
    r12 = InsectCageMenuBuildObjList_3909a0();
    D_00483334 = 0;
    r13 = MenuObjCountActive_390ec0();
    if (r13 <= 0) {
        MenuCursorObjSetVisible_386280(D_004E94C0, 0);
        UiSetWidgetVisible_290010(p1, 0x7544, 0, -1);
        p0->m08 = 0;
    } else {
        InsectCageMenuSetStateFlagMaybe_390aa0(6, 1);
        InsectCageMenuSetDrawFlag_390a80(1, 1);
        InsectCageMenuItemGridSetStates_38f920(0, 0);
        MenuCursorObjSetVisible_386280(D_004E94C0, 1);
        UiSetWidgetVisible_290010(p1, 0x7544, 1, -1);
        t1 = p0->m10;
        if (r12 <= t1) {
            p0->m10 = 0;
        }
        p0->m08 = (r13 + -1);
        InsectCageMenuSelectSlotObj_3904a0(p0, p1);
    }
    return 1;
}
