#include "types.h"


typedef void (*VFn)(void *, void *);
typedef s16 *(*VFn2)(void *, s16);

struct Info { u8 pad[0x30]; s32 f30; };
class Obj {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void Set(void *);
    u8 pad4[0xC];
    Info *f10;
};
class Tbl {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25();
    virtual s16 *Get(s16);
};
struct Ent { u8 pad[0x18]; s16 *f18; };
struct Self {
    s32 h;
    u8 pad4[0xD];
    s8 f11;
    u8 pad12[0xE];
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    u8 pad34[0x72 - 0x34];
    u8 buf72[1];
};
struct Bits { u8 pad[8]; u16 k; };

extern "C" {
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
Bits *UiGetWidgetText_28f620(s32, s32, s32);
s32 ItemRecKindIs6_3d4510(Obj *);
void UiSetTextString_28f510(s32, s32, void *, s32);
s32 ItemDefIsKindCId4B0_40e310(Info *);
Ent *InvObjCastToItem4B0_3d3cd0(Obj *);
s32 CageRecIsPlaced_3d0d20(Ent *);
s32 ThinkMenuIsOpenThunk_521290(void);
s32 TransMenuIsOpenThunk_516a50(void);
s16 MainMenuGetExitCodeThunkMaybe_2974d0(void);
s32 LoadHandleIsReady_28b200(void *);
u8 *GetGameData_1fede0(void);
void CageRecGetPos_3d0b40(Ent *, void *);
void GetWorldDataMgr_1fedf0(void);
s32 GetMapMgr_201a90(void);
s32 MapFindBlockAtPos_1e3a00(s32, void *, f32);
s32 MapBlockGetPlaceNameMsgId_1e0060(s32);
s32 MsgTableLookup_28aa30(void *, s32);
void Sprintf_1343b8(void *, void *, s32, s32);
void MenuItemInfoPopupLayout_289f30(Obj *, s16 **);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
}
extern u8 D_004823CC;
extern void *D_004823D8;
extern void *D_004823DC;
extern void *D_004823F8;
extern void *D_00484774;
extern u8 D_004613C8[];
extern u8 D_004DB390[];

extern "C" s32 MenuItemInfoPopupShow_2a33e0(Self *self, Obj *obj, s32 arg2, s32 arg3, s16 **arr, s32 arg5, s32 arg6, s32 arg7, f32 f) {
    u8 sp[0x10];
    Bits *bt;
    s32 t;
    bool ok;
    Ent *e;
    s32 j;
    s32 r;
    s32 n;
    void *tbl;
    s32 a;
    s32 b;
    s16 *p;
    s32 id;
    u8 *g;
    s32 k;

    if (arr[0] == 0 || arr[1] == 0 || arr[2] == 0 || arr[3] == 0) return 0;
    t = UiGetWidgetSprite_28fe10(self->h, arg3, 0);
    if (t == 0) return 0;
    *(s16 *)(t + 0x166) = 0x37;
    *(s16 *)(t + 0xC6) = 0x37;
    *(s16 *)(t + 0x46) = 0x37;
    *(s16 *)(t + 0x182) = 0x47;
    *(s16 *)(t + 0x122) = 0x47;
    *(s16 *)(t + 0xE2) = 0x47;
    *(s16 *)(t + 0x62) = 0x47;
    *(s16 *)(t + 0x2) = 0x47;
    *(s16 *)(t + 0x86) = 0x50;
    bt = UiGetWidgetText_28f620(self->h, arg2, 1);
    ok = 1;
    bt->k = (bt->k & 0xFF80) | 2;
    if (obj != 0 && arg7 >= 0) {
        if (D_004823CC != 0) {
            if (ItemRecKindIs6_3d4510(obj) != 0) {
                ok = 0;
            } else if (self->f11 == self->f2C && arg7 == self->f30) {
                ok = 0;
            }
        }
        if (self->f11 == self->f20 && arg7 == self->f24 && self->f28 <= 0) {
            ok = 0;
        }
    }
    if (obj != 0 && ok) {
        obj->Set(D_004DB390);
        UiSetTextString_28f510(self->h, arg2, D_004DB390, 0);
        if (ItemDefIsKindCId4B0_40e310(obj->f10) != 0) {
            e = InvObjCastToItem4B0_3d3cd0(obj);
            if (e != 0 && CageRecIsPlaced_3d0d20(e) != 0 && ThinkMenuIsOpenThunk_521290() == 0 && TransMenuIsOpenThunk_516a50() == 0) {
                if (MainMenuGetExitCodeThunkMaybe_2974d0() == 1 && LoadHandleIsReady_28b200(D_004823F8) == 0) {
                    return 1;
                }
                k = *(s16 *)(*(u8 **)(GetGameData_1fede0() + 0x18) + 4);
                j = e->f18[3];
                if (j == k) {
                    CageRecGetPos_3d0b40(e, sp);
                    GetWorldDataMgr_1fedf0();
                    r = MapFindBlockAtPos_1e3a00(GetMapMgr_201a90(), sp, 0.0f);
                    if (r != 0) {
                        n = MapBlockGetPlaceNameMsgId_1e0060(r);
                        tbl = D_00484774;
                        if (MainMenuGetExitCodeThunkMaybe_2974d0() == 1) {
                            tbl = D_004823DC;
                        }
                        a = MsgTableLookup_28aa30(D_004823D8, 0x45A);
                        b = MsgTableLookup_28aa30(tbl, n);
                        Sprintf_1343b8(self->buf72, D_004613C8, a, b);
                        UiSetTextString_28f510(self->h, arg2, self->buf72, 1);
                    }
                } else {
                    p = (*(Tbl **)(*(u8 **)(*(u8 **)(GetGameData_1fede0() + 8) + 0x34) + 0x14))->Get(j);
                    if (p != 0 && *p > 0) {
                        id = *p + 0x44F;
                        if (*p == 0x15) id = 0x45B;
                        a = MsgTableLookup_28aa30(D_004823D8, 0x45A);
                        b = MsgTableLookup_28aa30(D_004823D8, id);
                        Sprintf_1343b8(self->buf72, D_004613C8, a, b);
                        UiSetTextString_28f510(self->h, arg2, self->buf72, 1);
                    }
                }
            } else {
                UiSetTextString_28f510(self->h, arg2, (void *)obj->f10->f30, 1);
            }
        } else {
            UiSetTextString_28f510(self->h, arg2, (void *)obj->f10->f30, 1);
        }
        MenuItemInfoPopupLayout_289f30(obj, arr);
        UiSetWidgetPos_290f60(self->h, arg3, arg5, arg6);
        UiFadeWidgetAlpha_290690(self->h, arg3, 1.0f, f, -1.0f);
    } else {
        *arr[0] = -1;
        *arr[1] = -1;
        *arr[2] = -1;
        *arr[3] = -1;
        UiFadeWidgetAlpha_290690(self->h, arg3, 0.0f, -f, -1.0f);
    }
    return 1;
}
