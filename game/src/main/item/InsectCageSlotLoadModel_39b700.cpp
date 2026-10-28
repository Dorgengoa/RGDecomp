/* rgp:protos */
#line 1
#include "types.h"

class VC39b700 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f50() { VCM0(void, 0x50); }
};

struct P39b700 {
    s32 unk0;
    u8 *unk4;
    u8 *unk8;
    u8 *unkC;
    u8 *unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1c[0x10];
    u8 *unk2C;
    s32 unk30;
    u8 pad34[4];
    u8 *unk38;
    s32 unk3C;
    u8 buf40[0x20];
    u8 buf60[0x20];
    u8 pad80[8];
};

struct Name39b700 {
    s8 c[0x20];
};

struct Q39b700 {
    u8 pad0[0x4DC];
};

struct O39b700 {
    s32 unk0;
    u8 *unk4;
    u8 unk8[2];
    s16 unkA;
    s32 unkC;
    u8 pad10[4];
    s32 unk14;
    VC39b700 *unk18;
    u8 pad1c[2];
    s16 unk1E;
    s32 unk20;
    s32 unk24;
};

struct G39b700 {
    u8 pad0[0x18];
    s32 unk18;
};

extern "C" {
s32 InsectCageSlotGetState_39bb00(O39b700 *);
void LoadHandlePoll_1ccb00(u8 *);
void LoaderReleaseHandle_1ccb70(u8 *);
G39b700 *GetGameData_1fede0(void);
s32 InsectCageSlotGetId_39b460(O39b700 *);
s32 InvGetItem4B0_3c80c0(s32, s32);
s32 MemStackHeapAlloc_14db10(u8 *, s32, s32, s32);
void MemStackReturnToOwnerMaybe_14dad0(u8 *);
u8 *GetDrawCtxNameTable_15de40(void);
void strcpy(u8 *, s8 *);
VC39b700 *MemStackNew_14e230(s32, u8 *);
void ModelObjExCtor_1c4920(VC39b700 *, int, int, int);
void memset(void *, s32, s32);
void InfoCfgParseAll_1afd00(VC39b700 *, P39b700 *);
void CageRecGetPos_3d0b40(s32, u8 *);
void ModelSetPos_151110(VC39b700 *, u8 *);
f32 CageRecGetYaw_3d0b30(s32);
void ModelSetRot_151080(VC39b700 *, f32 *);
void MatIdentity_1cbe40(u8 *);
void Character2LightBlendSetTarget_1aebe0(VC39b700 *, s32, u8 *, u8 *, f32 *, f32 *, s32);
void InsectCageSlotFadeStart_39b3f0(O39b700 *, s32);
void InsectCageSlotRelease_39b9c0(O39b700 *);
extern u8 D_004545F0[0x20];
extern u8 D_004643C8[16];
extern u8 D_00470F50[16];
extern f32 D_0047FFA0;
extern f32 D_0047FFA4;
extern f32 D_0047FFA8;
extern f32 D_0047FFAC;

static inline void Clr(u8 *p, u32 n)
{
    if (p != NULL) {
        while (n != 0) {
            *p = 0;
            n--;
            p++;
        }
    }
}

void InsectCageSlotLoadModel_39b700(O39b700 *arg0) {
    Name39b700 name __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(P39b700)) + (0x88) + (0x90)];
    u8 spA0[0x10] __attribute__((aligned(16)));
    u8 sp60[0x40] __attribute__((aligned(16)));
    f32 col[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    G39b700 *g;
    u8 *w;
    VC39b700 *p;
    f32 f;
    VC39b700 *q;

    if (((short)InsectCageSlotGetState_39bb00(arg0)) != 1) {
        return;
    }
    LoadHandlePoll_1ccb00(arg0->unk8);
    if (arg0->unkA == 0) {
        return;
    }
    arg0->unk1E = 3;
    if (arg0->unkA == 1) {
        g = GetGameData_1fede0();
        arg0->unk14 = InvGetItem4B0_3c80c0(g->unk18, ((short)InsectCageSlotGetId_39b460(arg0)));
        if (arg0->unk14 != 0) {
            arg0->unk0 = MemStackHeapAlloc_14db10(arg0->unk4, 3, 0x780, 0x40);
            if (arg0->unk0 != 0) {
                w = GetDrawCtxNameTable_15de40();
                name = *(Name39b700 *)D_004545F0;
                strcpy(w + 0x1E4, name.c);
                p = MemStackNew_14e230(0x790, arg0->unk4);
                if (p != NULL) {
                    ModelObjExCtor_1c4920(p, 0, 0, 0);
                    *(u8 **)((u8 *)p + 0x1B0) = D_00470F50;
                }
                arg0->unk18 = p;
                memset(&(*(P39b700 *)(rgp_blk1 + 0x0)), 0, 0x88);
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk2C = (*(P39b700 *)(rgp_blk1 + 0x0)).buf40;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk30 = 8;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk38 = (*(P39b700 *)(rgp_blk1 + 0x0)).buf60;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk3C = 8;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk0 = arg0->unkC;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk4 = D_004643C8;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk8 = arg0->unk4;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unkC = arg0->unk4;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk10 = arg0->unk4;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk14 = arg0->unk20;
                (*(P39b700 *)(rgp_blk1 + 0x0)).unk18 = 1;
                arg0->unk18->f50();
                InfoCfgParseAll_1afd00(arg0->unk18, &(*(P39b700 *)(rgp_blk1 + 0x0)));
                *(s32 *)((u8 *)arg0->unk18 + 0x4DC) = (*(P39b700 *)(rgp_blk1 + 0x0)).unk14;
                *(s32 *)((u8 *)arg0->unk18 + 0x448) = 0;
                arg0->unk24 = 0;
                CageRecGetPos_3d0b40(arg0->unk14, spA0);
                ModelSetPos_151110(arg0->unk18, spA0);
                f = CageRecGetYaw_3d0b30(arg0->unk14);
                q = arg0->unk18;
                Clr((u8 *)v, 16);
                v[1] = f;
                *(s32 *)&v[0] = 0;
                *(s32 *)&v[2] = 0;
                ModelSetRot_151080(q, v);
                w[0x1E4] = 0;
                col[0] = D_0047FFA0;
                col[1] = D_0047FFA4;
                col[2] = D_0047FFA8;
                col[3] = D_0047FFAC;
                MatIdentity_1cbe40(sp60);
                Character2LightBlendSetTarget_1aebe0(arg0->unk18, 0, sp60, sp60, col, col, 0);
                arg0->unk1E = 2;
            }
            MemStackReturnToOwnerMaybe_14dad0(arg0->unk4);
        }
    }
    if (((short)InsectCageSlotGetState_39bb00(arg0)) == 2) {
        LoaderReleaseHandle_1ccb70(arg0->unk8);
        InsectCageSlotFadeStart_39b3f0(arg0, 0xF);
    } else {
        InsectCageSlotRelease_39b9c0(arg0);
    }
}
}
