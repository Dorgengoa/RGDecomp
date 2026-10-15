#include "types.h"

class Obj {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void v0C8();
    virtual void v0CC();
    virtual void v0D0();
    virtual void v0D4();
    virtual void v0D8();
    virtual void v0DC();
    virtual void v0E0();
    virtual void v0E4();
    virtual void v0E8();
    virtual void v0EC();
    virtual void v0F0();
    virtual void v0F4();
    virtual void v0F8();
    virtual void v0FC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114(s8 *);
    virtual s32 v118(s32);
};

typedef struct Holder {
    u8 pad[0x96C];
    Obj *obj;
} Holder;

extern "C" {
void MemStackReset_14d830(void *);
void LoaderReleaseById_1cd340(s32, s16);
s32 LoaderGetData_1cd490(s32, s16, s32 *);
s32 LoaderGetStatus_1cd4f0(s32, s16);
s32 GetLoaderMgr_1f59d0(void);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
void InsectCageMenuSelectEntry_390d40(s32, s32);
Holder *InsectCageMenuGetCursorObj_390f70(void);
void TextEntrySetState_434410(s8 *, s32, s32);
void TextEntrySetName_435780(s8 *, s32);
void TextEntrySetMode_436450(s8 *, s32);
void TextEntryUpdate_436640(s8 *);
void MenuResGroupUnloadGroup3_4366a0(s8 *);
void TextEntryLoadRes_4366f0(s8 *, void *, s32);
extern s16 D_0047FBD0;
extern s8 *D_00483298;
extern s8 D_0048329C;
extern s32 D_0048330C;
extern s8 *D_00484104;
extern u8 D_004E9440[];
}

static inline void wait_state(s32 h){
        switch (LoaderGetStatus_1cd4f0(h, D_0047FBD0)) {
        case -1:
            break;
        case 0:
            return;
        case 1:
            D_0048329C++;
            break;
        }

}
extern "C" s32 InsectCageMenuRename_38be70(s32 pad0, s32 arg1) {
    s32 sp4C;
    s32 h;
    Obj *obj;
    Holder *p;
    s32 r;

    h = GetLoaderMgr_1f59d0();
    if (D_0048329C == 1) {
        wait_state(h);
        return 0;
    }
    sp4C = 0;
    obj = 0;
    p = InsectCageMenuGetCursorObj_390f70();
    if (p != 0) {
        obj = p->obj;
    }
    if (obj == 0) {
        D_0048329C = 7;
    }
    switch (D_0048329C) {
    case 2:
        UiSetWidgetsVisibleById_291110(arg1, 0x753A, 0, 1);
        UiSetWidgetsVisibleById_291110(arg1, 0x7544, 0, 1);
        UiSetWidgetVisible_290010(D_0048330C, 0x7602, 0, -1);
        TextEntryLoadRes_4366f0(D_00483298, D_004E9440, LoaderGetData_1cd490(h, D_0047FBD0, &sp4C));
        LoaderReleaseById_1cd340(h, D_0047FBD0);
        D_0047FBD0 = -1;
        D_00484104 = D_00483298;
        D_0048329C += 1;
        break;
    case 3:
        *(s16 *)(D_00483298 + 0xE6) = 0;
        TextEntrySetMode_436450(D_00483298, 1);
        TextEntrySetState_434410(D_00483298, 0x6D61, 1);
        TextEntrySetName_435780(D_00483298, obj->v118(0));
        D_0048329C += 1;
        break;
    case 4:
        switch (*(s16 *)(D_00483298 + 0xE6)) {
        case 0:
            break;
        case 1:
            D_0048329C = 5;
            break;
        case 2:
            D_0048329C = 6;
            break;
        }
        break;
    case 5:
        D_0048329C = 7;
        break;
    case 6:
        obj->v114(D_00483298 + 0x30);
        D_0048329C = 7;
        break;
    case 7:
        MenuResGroupUnloadGroup3_4366a0(D_00483298);
        D_00484104 = 0;
        D_00483298 = 0;
        D_0048329C = 0;
        UiSetWidgetsVisibleById_291110(arg1, 0x753A, 1, 1);
        UiSetWidgetsVisibleById_291110(arg1, 0x7544, 1, 1);
        InsectCageMenuSelectEntry_390d40(0x7531, 0);
        MemStackReset_14d830(D_004E9440);
        break;
    }
    if (D_0048329C >= 4 && D_00483298 != 0) {
        TextEntryUpdate_436640(D_00483298);
    }
    return 0;
}
