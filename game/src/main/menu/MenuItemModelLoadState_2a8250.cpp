/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Vec4 {
    f32 x, y, z, w;
    Vec4 &operator=(const Vec4 &o) {
        *(u128 *)this = *(const u128 *)&o;
        return *this;
    }
} __attribute__((aligned(16))) Vec4;

class Cam {
    u8 pad000[0xC0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void setLag(f32 a0) { VCM(void, (void *, f32), 0xC8, a0); }
    u8 padc4[0x1C];
    Vec4 eye;
    Vec4 at;
};

extern "C" {


void ModelSetScale_150ff0(s8 *, void *);
void CameraSetLag_177170(Cam *, f32, f32);
void LoaderQueueAppendSeparator_1cd670(s32);
s32 GetLoaderMgr_1f59d0();
void GetGameData_1fede0();
void LoadHandleArrayReset_28b160(void *, s32);
s32 LoadHandleIsPending_28b210(void *);
s32 LoadHandleGetId_28b220(void *);
void LoadHandleFree_28b230(void *);
s32 LoadHandleGetData_28b270(void *, s32 *);
s32 LoadHandleGetStatus_28b2e0(void *);
void LoadHandleRequestFile_28b550(void *, s32, s32, s32);
s8 *UiEntryListFindByTag_28ea40(s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void MenuItemModelCreate_2a7190(s32);
void MenuItemTempRBufInit_2a8a20();
void *memset(void *, s32, u32);
extern s32 D_004659F0[];
extern f32 D_0047D5AC;
extern s32 D_0047EC58;
extern f32 D_0047EC90;
extern f32 D_0047EC94;
extern f32 D_0047EC98;
extern f32 D_0047ECA0;
extern f32 D_0047ECA4;
extern f32 D_0047ECA8;
extern f32 D_0047ECAC;
extern f32 D_0047ECB0;
extern f32 D_0047ECB4;
extern f32 D_0047ECB8;
extern f32 D_0047ECBC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s8 *D_00482374;
extern Cam *D_004823D4;
extern s16 D_00482488;
extern s8 *D_004824BC;
extern u8 D_004824E0[8];
extern u8 D_004DB4E0[0x100];

}

extern "C" s32 MenuItemModelLoadState_2a8250(s32 pad0, s32 arg1) {
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    s32 i;
    s8 *e;
    union { s32 i[3]; f32 f[3]; } tbl;
    s32 sel;
    u8 buf[0x10] __attribute__((aligned(16)));
    u8 *p;
    s32 out;
    u32 n;
    s8 *q;

    if (arg1 != 0) {
        D_00482488 = 0;
        tbl.f[0] = D_0047EC90;
        tbl.f[1] = D_0047EC94;
        tbl.f[2] = D_0047EC98;
        GetGameData_1fede0();
        sel = -1;
        for (i = 0; i < 3; i++) {
            s32 t_ = tbl.i[i];
            if (t_ == *(s32 *)(D_00482374 + 0x6C)) {
                sel = i;
            }
        }
        if (sel < 0) {
            return 0;
        }
        MenuItemTempRBufInit_2a8a20();
        LoadHandleArrayReset_28b160(D_004DB4E0, 1);
        LoadHandleRequestFile_28b550(D_004DB4E0, (&D_0047EC58)[sel], 0, 0);
        LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
        if (D_004823D4 != NULL) {
            { f32 *p_a = (f32 *)&a; p_a[0] = D_0047ECA0; p_a[1] = D_0047ECA4; p_a[2] = D_0047ECA8; p_a[3] = D_0047ECAC; }
            { f32 *p_b = (f32 *)&b; p_b[0] = D_0047ECB0; p_b[1] = D_0047ECB4; p_b[2] = D_0047ECB8; p_b[3] = D_0047ECBC; }
            D_004823D4->eye = a;
            D_004823D4->at = b;
            CameraSetLag_177170(D_004823D4, 1.0f, -1.0f);
            D_004823D4->setLag(-1.0f);
        }
        memset(D_004824E0, 0, 8);
        D_00482488 = 1;
        UiFadeWidgetAlpha_290690(D_00482360, 0x140, 0.0f, D_0047D5AC, -1.0f);
        e = UiEntryListFindByTag_28ea40(D_00482364, 3);
        *(s32 *)(D_00482374 + 0x30) = *(s16 *)(e + 0x14) + *(s16 *)(e + 0x16) * D_004659F0[0];
        *(s32 *)(D_00482374 + 0x2C) = *(s8 *)(D_00482374 + 0x11);
    }
    if (LoadHandleGetId_28b220(D_004DB4E0) == -1) {
        return 0;
    }
    if (((unsigned char)LoadHandleIsPending_28b210(D_004DB4E0)) == 0) {
        return 0;
    }
    if (LoadHandleGetStatus_28b2e0(D_004DB4E0) == 1) {
        MenuItemModelCreate_2a7190(LoadHandleGetData_28b270(D_004DB4E0, &out));
        q = D_004824BC;
        if (q != NULL) {
            p = buf;
            n = 0x10;
            if (p != NULL) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
            *(s32 *)(buf + 0) = 0;
            *(s32 *)(buf + 4) = 0;
            *(s32 *)(buf + 8) = 0;
            ModelSetScale_150ff0(q, buf);
            *(s32 *)(D_004824BC + 0x170) = 0;
        }
        LoadHandleFree_28b230(D_004DB4E0);
        StateMachineSetState_28ede0(D_0048235C, 0xAF, 0);
    }
    return 1;
}
