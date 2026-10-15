#include "types.h"

extern "C" {

typedef unsigned __int128 u128;
typedef struct { f32 x, y, z, w; } V4;
typedef union { u128 q; V4 v; } Vec;

typedef struct Sub {
    s32 w0;
    s32 w4;
    s32 w8;
    u8 padC[0x54];
    s32 w60;
} Sub;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Sub sub;
} Node;

class Obj {
public:
    u8 pad0[0x120];
    u8 slot0[0x50];
    f32 f170;
    u8 pad174[0xC];
    Vec q180;
    u8 pad190[0x20];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual s32 v14();
    virtual void d4();
    virtual f32 v1C();
    u8 pad1B4[0x28];
    s32 w1DC;
    u8 pad1E0[0x20];
    Node *p200;
    s32 n204;
    u8 *a208;
    u8 pad20C[0x8];
    s32 n214;
    u8 *a218;
    u8 pad21C[0x4];
    Node *p220;
    s32 w224;
    u8 pad228[0x220];
    f32 f448;
    s32 w44C;
    s32 w450;
    u8 pad454[0x88];
    s32 w4DC;
};


s32 FrameGetWorldPos_148f30(s32, Vec *);
s32 ModelEmitDrawPacketsMaybe_14ec20(Obj *, s32, u8 *);
s32 ModelPrepareDrawMaybe_14f760(Obj *, s32, u8 *);
s32 ModelMeshUpdateBoundsMaybe_150170(Obj *, u8 *);
s32 ModelUpdateFrameWorlds_1502b0(Obj *, s32);
s32 ModelGetRootFrame_1511a0(Obj *);
s32 CameraWorldToView_15d140(Vec *, Vec *);
s32 GetDrawCtx_15de80(void);
s32 TexAnimeTableApplyMaybe_162f50(s32, s32, s32);
s32 DynClothDebugDrawColliders_1670a0(u8 *);
s32 DynClothDebugDrawBinds_167190(u8 *);
s32 ModelDrawOffscreenCompositeAtMaybe_16b8a0(Sub *, Obj *, Vec *, f32, f32);
extern f32 D_0047E1D0;
extern s32 D_004813A4;

static inline u8 *GetSlot(Obj *self, s32 i) {
    if (i < 0) {
        return self->slot0;
    }
    if (self->a218 == 0) {
        return 0;
    }
    if (i < 0 || i >= self->n214) {
        return 0;
    }
    return self->a218 + i * 0x50;
}

static inline u8 *GetX(Obj *self, s32 i) {
    if (self->a208 == 0 || self->n204 == 0) {
        return 0;
    }
    if (i < 0 || i >= self->n204) {
        return 0;
    }
    return self->a208 + i * 0x170;
}

s32 ModelObjExDraw_1ad7a0(Obj *self) {
    Vec sp80;
    Vec sp70;
    s32 j;
    u8 *xs;
    f32 scale;
    f32 fade;
    s32 t;
    s32 t2;
    Node *nd;
    s32 sum;
    s32 i;
    u8 *sl;
    Sub *sb;
    s32 save;
    s32 r;
    f32 z;

    if (self->v14() == 0) {
        return 0;
    }
    scale = self->f448;
    if (self->w1DC != 0) {
        scale *= self->v1C();
    }
    if (scale <= 0.0f) {
        return 0;
    }
    t = GetDrawCtx_15de80();
    if (self->w224 != 0) {
        t2 = GetDrawCtx_15de80();
        for (nd = self->p220; nd != 0; nd = nd->next) {
            sb = &nd->sub;
            if (sb->w8 != 0) {
                if (sb->w4 != 0) {
                    TexAnimeTableApplyMaybe_162f50(sb->w4, t2, self->w4DC);
                }
            }
        }
    }
    sum = 0;
    if (self->p200 == 0 || self->w450 == 0) {
        self->f170 = scale;
        if (ModelUpdateFrameWorlds_1502b0(self, t) == 0) {
            return 0;
        }
        for (i = -1; ; i++) {
            sl = GetSlot(self, i);
            if (sl == 0) {
                break;
            }
            ModelMeshUpdateBoundsMaybe_150170(self, sl);
            if (ModelPrepareDrawMaybe_14f760(self, t, sl) != 0) {
                sum += ModelEmitDrawPacketsMaybe_14ec20(self, t, sl);
            }
        }
    } else {
        if (ModelUpdateFrameWorlds_1502b0(self, t) == 0) {
            return 0;
        }
        for (i = -1; ; i++) {
            sl = GetSlot(self, i);
            if (sl == 0) {
                break;
            }
            ModelMeshUpdateBoundsMaybe_150170(self, sl);
        }
        fade = 1.0f;
        r = ModelGetRootFrame_1511a0(self);
        if (r != 0) {
            FrameGetWorldPos_148f30(r, &sp70);
        } else {
            sp70.q = self->q180.q;
        }
        sp70.v.w = 1.0f;
        CameraWorldToView_15d140(&sp80, &sp70);
        z = -sp80.v.z;
        sp80.v.z = z;
        if (!(z <= 10.0f)) {
            fade = 1.0f - (z - 10.0f) / D_0047E1D0;
            if (fade < 0.0f) {
                fade = 0.0f;
            }
        }
        for (nd = self->p200; nd != 0; nd = nd->next) {
            sb = &nd->sub;
            if (sb != 0) {
                save = sb->w60;
                if (self->w44C == 1) {
                    sb->w60 = 1;
                }
                if (self->w44C == 2) {
                    sb->w60 = 0;
                }
                sum += ModelDrawOffscreenCompositeAtMaybe_16b8a0(sb, self, &self->q180, fade, scale);
                sb->w60 = save;
            }
            if (scale < 1.0f) {
                break;
            }
        }
    }
    if (D_004813A4 != 0) {
        for (j = 0; j < self->n204; j++) {
            xs = GetX(self, j);
            if (xs == 0) {
                break;
            }
            if (D_004813A4 & 1) {
                DynClothDebugDrawBinds_167190(xs);
            }
            if (D_004813A4 & 2) {
                DynClothDebugDrawColliders_1670a0(xs);
            }
        }
    }
    return sum;
}

}
