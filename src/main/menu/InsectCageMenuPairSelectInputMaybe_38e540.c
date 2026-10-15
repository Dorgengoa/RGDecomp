#include "types.h"

extern s32 PlayMenuSe_289ef0();
extern s32 UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern s32 BitArraySetReturnOld_384360(s8 *, s32, s32);
extern s32 MenuObjSetStopMotion_384a80(s32);
extern s32 MenuObjSetShowModel_3858a0(s32, s32, s8 *);
extern s32 MenuObjRandDelayMaybe_385fa0(s8 *);
extern s32 MenuObjGetFrontPos_386000(s8 *, s8 *);
extern s32 MenuCursorObjSetOwner_386270(void *, s32);
extern s32 MenuCursorObjSetVisible_386280(void *, s32);
extern s32 MenuObjInsectSatietyUnderCap_386bd0(s8 *);
extern s32 MenuObjInsectIsAdult_386c90(s8 *);
extern s32 MenuObjInsectGetSex_386cf0(s8 *);
extern s32 InsectCageMenuGetCursorInvItem_38f550(s32 *);

extern s32 InsectCageMenuSetDrawFlag_390a80(s32, s32);
extern s32 InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern s32 InsectCageMenuSelectEntry_390d40(s32, s32);
extern s8 *InsectCageMenuGetCursorObj_390f70();
extern s8 *InsectCageMenuGetSlotObj_390fc0(s32);
extern s32 InsectCageMenuGetCursorSlot_391000();
extern s32 ModelObjPlayMotionByName_1867a0(s8 *, void *, s32);
extern u8 D_00464108[];
extern s32 D_004832D8;
extern s16 D_00483364;
extern s8 D_00483378;
extern s8 *D_0048337C;
extern s8 *D_00483380;
extern s8 *D_00483384;
extern s32 D_004E94A0[];
extern u8 D_004E94C0[];
extern s32 D_004E94F4[];
extern s32 D_004E94FC[];
extern u8 D_004E9510[];

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    s16 h10;
} Obj;

extern s32 InsectCageMenuDisplayModeInput_390420(Obj *, s32, s32);
s32 InsectCageMenuPairSelectInputMaybe_38e540(Obj *arg0, s32 arg1, s32 arg2) {
    s32 sp4C;
    s32 fc;
    s32 f4;
    s32 i;
    s32 id;
    s8 *p;
    s8 *e;
    s8 **pp;
    s32 t;

    fc = D_004E94FC[0];
    f4 = D_004E94F4[0];
    if (f4 & 4) {
        PlayMenuSe_289ef0(4);
        arg0->h10 = arg0->h8;
        MenuCursorObjSetOwner_386270(D_004E94C0, D_004E94A0[arg0->h10]);
    } else if (f4 & 8) {
        PlayMenuSe_289ef0(4);
        arg0->h10 = 0;
        MenuCursorObjSetOwner_386270(D_004E94C0, D_004E94A0[arg0->h10]);
    } else if (fc & 1) {
        MenuCursorObjSetOwner_386270(D_004E94C0, D_004E94A0[arg0->h10]);
    } else if (fc & 0x40) {
        InsectCageMenuDisplayModeInput_390420(arg0, arg1, fc);
    } else if (fc & 2) {
        D_00483378 = 0;
        if (arg2 == 1) {
            D_00483378 = 1;
        }
        id = arg0->h10;
        if (id == InsectCageMenuGetCursorSlot_391000()) {
            PlayMenuSe_289ef0(6);
            return 0;
        }
        p = InsectCageMenuGetSlotObj_390fc0(id);
        if (p == 0) {
            PlayMenuSe_289ef0(6);
            return 0;
        }
        D_0048337C = p;
        t = *(s32 *)(p + 0x9C8) != 0;
        if (t) goto fail;
        t = *(s32 *)(p + 0x9C4) != 0;
        if (t) {
        fail:
            InsectCageMenuSelectEntry_390d40(0x7536, 0);
            PlayMenuSe_289ef0(6);
            return 0;
        }
        if ((u8)MenuObjInsectSatietyUnderCap_386bd0(p) == 0) {
            D_00483364 = 0x4BD;
            InsectCageMenuSelectEntry_390d40(0x7536, 0);
            PlayMenuSe_289ef0(6);
            return 0;
        }
        D_00483380 = InsectCageMenuGetCursorObj_390f70();
        D_00483384 = p;
        if (arg2 == 1) {
            if (MenuObjInsectIsAdult_386c90(p) == 0) {
                D_00483364 = 0x4BB;
                InsectCageMenuSelectEntry_390d40(0x7536, 0);
                PlayMenuSe_289ef0(6);
                return 0;
            }
            if (MenuObjInsectGetSex_386cf0(D_00483380) == MenuObjInsectGetSex_386cf0(D_00483384)) {
                D_00483364 = 0x4C3;
                if (MenuObjInsectGetSex_386cf0(D_00483380) == 0) {
                    D_00483364 = 0x4C2;
                }
                InsectCageMenuSelectEntry_390d40(0x7536, 0);
                PlayMenuSe_289ef0(6);
                return 0;
            }
        }
        PlayMenuSe_289ef0(5);
        InsectCageMenuSetStateFlagMaybe_390aa0(6, 0);
        MenuCursorObjSetVisible_386280(D_004E94C0, 0);
        InsectCageMenuSetDrawFlag_390a80(1, 0);
        UiSetWidgetVisible_290010(arg1, 0x7616, 0, -1);
        InsectCageMenuGetCursorInvItem_38f550(&sp4C);
        for (i = 0; i < 2; i++) {
            e = (s8 *)(D_004E9510 + (i << 5));
            *(s32 *)(e + 0x10) = sp4C;
            pp = &(&D_00483380)[i];
            MenuObjGetFrontPos_386000(e, *pp);
            MenuObjRandDelayMaybe_385fa0(e);
            MenuObjSetShowModel_3858a0(D_004832D8, i, *pp);
            ModelObjPlayMotionByName_1867a0(*pp, D_00464108, 0);
            BitArraySetReturnOld_384360(*pp + 0x986, 8, 0);
            BitArraySetReturnOld_384360(*pp + 0x986, 2, 0);
        }
        MenuObjSetStopMotion_384a80(D_004832D8);
        return 1;
    } else if (fc & 4) {
        PlayMenuSe_289ef0(6);
        InsectCageMenuSelectEntry_390d40(0x7534, 0);
    }
    return 0;
}
