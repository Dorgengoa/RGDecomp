/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v114(s8 * a0) { VCM(void, (void *, s8 *), 0x114, a0); }
    s32 v118(s32 a0) { return VCM(s32, (void *, s32), 0x118, a0); }
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
void TextEntrySetMode_436450(s8 *, long long);
void TextEntryUpdate_436640(s8 *);
void MenuResGroupUnloadGroup3_4366a0(void);
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
        TextEntrySetMode_436450(D_00483298, (long long)(1));
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
        MenuResGroupUnloadGroup3_4366a0();
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
