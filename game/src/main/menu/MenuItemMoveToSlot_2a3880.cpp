#include "types.h"
#pragma opt_propagation off

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v18() { return VCM0(s32, 0x50); }
};

struct Sub {
    u8 pad0[0x2C];
    s16 m2C;
};

struct Ctx {
    u8 pad0[0x18];
    s32 m18;
};

struct Rec {
    u8 pad0[0x8];
    s64 m8;
    u8 pad10[0xC];
    s16 m1C;
    s16 m1E;
};

struct Ent {
    u8 pad0[0x24];
    Rec *m24;
};

struct Self {
    s32 m0;
    u8 pad4[0xD];
    s8 m11;
    u8 pad12[0x2];
    s32 m14;
    s32 m18;
    u8 m1C;
    u8 pad1D[3];
    s32 m20;
    s32 m24;
    s32 m28;
    u8 pad2C[8];
    Obj *m34;
    u8 pad38[4];
    s32 m3C;
};

#define OBJ_M10(o) (*(Sub **)((u8 *)(o) + 0x10))
#define OBJ_M6(o) (*(s16 *)((u8 *)(o) + 6))

extern "C" {
Ctx *GetGameData_1fede0(void);
void UiSetItemIconSprite_288490(Self *, Ent *, s32, s32, s32, s32);
Ent *UiFindWidget_290460(s32, s32);
void MenuShowItemCount_2a02f0(Self *, s32, s32, s32, s32);
s32 InvMoveItemMaybe_3c5b10(s32, Obj *, s32, s32, s32 *, s32 *, Obj **, s32);
Obj *InvFindByInvId_3c87d0(s32, s32, s32);
s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
s32 InvIdGetMidIndex_3d52b0(s32);
s32 InvIdGetMinorIndex_3d5440(s32);
s32 InvIdGetMajorIndex_3d55f0(s32);
extern s32 D_004659F0[];
}

extern "C" s32 MenuItemMoveToSlot_2a3880(Self *self, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp8C;
    s32 sp88;
    Obj *sp84;
    Ctx *ctx;
    s32 id;
    s32 ret;
    Obj *obj;
    Ent *ent;
    Rec *rec;
    s32 n;
    s32 t;

    ctx = GetGameData_1fede0();
    id = InvMakeIdFromCategory_3c88b0(ctx->m18, self->m14, self->m11, arg3, arg4);
    { s32 v3c = self->m3C; ret = InvMoveItemMaybe_3c5b10(ctx->m18, self->m34, id, v3c, 0, 0, 0, 1); }
    if (ret == 0) {
        goto end;
    }
    if (ret == 3 || ret == 7 || ret == 5 || ret == 8) {
        obj = InvFindByInvId_3c87d0(ctx->m18, id, 0);
        { s32 v3c = self->m3C; InvMoveItemMaybe_3c5b10(ctx->m18, self->m34, id, v3c, &sp8C, &sp88, &sp84, 0); }
        ent = UiFindWidget_290460(self->m0, arg1);
        if (ent == 0) {
            return 0;
        }
        UiSetItemIconSprite_288490(self, ent, OBJ_M10(obj)->m2C, 0x28, 0x2D, 1);
        ent = UiFindWidget_290460(self->m0, arg2);
        if (ent == 0) {
            return 0;
        }
        rec = ent->m24;
        if (rec == 0) {
            return 0;
        }
        if (ret == 3 || self->m3C - sp8C == 0) {
            n = obj->v18();
            if (ret == 5) {
                self->m1C = 0;
                self->m20 = -1;
                self->m24 = -1;
                self->m28 = -1;
            }
            self->m34 = obj;
        } else if (ret == 8) {
            n = sp84->v18();
            self->m34 = sp84;
        } else {
            n = sp88;
            if (ret != 5) {
                self->m34 = obj;
            }
        }
        self->m3C = n;
        if (n > 1) {
            rec->m8 = n;
            rec->m1C = 10;
            rec->m1E = 0x10;
        } else {
            rec->m1E = 0;
            rec->m1C = 0;
        }
        if (ret == 7 || ret == 8) {
            if (self->m18 == 9) {
                self->m20 = 6;
            } else {
                self->m20 = InvIdGetMajorIndex_3d55f0(OBJ_M6(sp84));
            }
            t = InvIdGetMidIndex_3d52b0(OBJ_M6(sp84));
            { s32 b = InvIdGetMinorIndex_3d5440(OBJ_M6(sp84)); self->m24 = b + D_004659F0[0] * t; }
            self->m28 = -1;
            MenuShowItemCount_2a02f0(self, 0x76, 0x74, 0x77, self->m24);
        }
    } else {
        self->m1C = 0;
        self->m20 = -1;
        self->m24 = -1;
        self->m28 = -1;
        { s32 v3c = self->m3C; InvMoveItemMaybe_3c5b10(ctx->m18, self->m34, id, v3c, &sp8C, &sp88, &sp84, 0); }
    }
end:
    return ret;
}
