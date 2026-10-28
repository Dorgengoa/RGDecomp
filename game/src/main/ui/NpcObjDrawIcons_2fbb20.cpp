/* rgp:protos */
#line 1
#include "types.h"

struct Vec4 {
    f32 x, y, z, w;
};

struct Base {
    u8 pad[0xC0];
};

struct Cam : public Base {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetMat(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
};

struct Pt {
    s32 x, y, z, w;
};

struct Mark {
    u8 pad0[8];
    s16 kind;            /* 0x08 */
    u8 padA[0x2E];
    f32 x;               /* 0x38 */
    f32 y;               /* 0x3C */
    f32 z;               /* 0x40 */
    u8 pad44[4];
    s32 flags;           /* 0x48 */
};

struct Ctl {
    u8 pad0[0xC4];
    s16 target;          /* 0xC4 */
    s16 id;              /* 0xC6 */
    u8 padC8[0x14];
    f32 scale;           /* 0xDC */
};

struct Wld {
    u8 pad0[8];
    u8 *sub;             /* 0x08 */
};

extern "C" {
f32 Sinf_128fd0(f32);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetGouraud_13e3b0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetUseUV_13e3e0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetFrameMask_13e420(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void DrawListEndPrim_141a20(s32);
s32 DrawListBeginPrim_141b00(s32);
s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetWidth_1451e0(s32);
s32 NameTableFindByName_159fb0(s32, void *, s32);
s32 ProjectToScreenOffset_15d160(Pt *, Vec4 *);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
Cam *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
u8 *ObjRecGetLiveObject_1c4a90(u8 *, s32);
u8 *GetStaticScene_1c6c70(void);
Wld *GetGameData_1fede0(void);
f32 ModelObjGetScaledHeight_23b110(u8 *);
Mark * GroupGetRecordById_41c2a0(s32, long long, long long, s32);
extern u8 D_00461E00[];
extern u8 D_00461E08[];
extern f32 D_0047F0B0;
extern f32 D_0047F0B4;
extern f32 D_0047F0B8;
extern f32 D_0047F0BC;
}

#define ZERO16(v) { u8 *p_ = (u8 *)&(v); u32 n_ = 0x10; if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }

extern "C" void NpcObjDrawIcons_2fbb20(Ctl *ctl) {
    Vec4 pos __attribute__((aligned(16)));
    Vec4 m __attribute__((aligned(16)));
    struct WorldPosition : Vec4 {}; WorldPosition v;
    Pt sa __attribute__((aligned(16)));
    Vec4 fa0 __attribute__((aligned(16)));
    Vec4 fa1 __attribute__((aligned(16)));
    Pt sb __attribute__((aligned(16)));
    Vec4 fb0 __attribute__((aligned(16)));
    Vec4 fb1 __attribute__((aligned(16)));
    u8 *world;
    s32 tub;
    Cam *cam;
    u8 *obj;
    s32 tu;
    s32 tv;
    s32 off;
    s32 c;
    s32 tex;
    s32 db;
    s32 x1;
    s32 z;
    s32 y1;
    s32 W;
    s32 H;
    s32 mgr;
    s32 du;
    s32 u0;
    f32 a;
    s32 mgrb;
    s32 dub;
    s32 zb;
    s32 Wb;
    s32 Hb;
    s32 offb;
    s32 yb1;
    s32 cb;
    s32 xb1;
    s32 texb;
    s32 ub0;
    Mark *mk;
    u8 *objb;




    f32 ab;

    if (!(*(u16 *)ctl & 1)) return;
    world = GetStaticScene_1c6c70();
    mk = GroupGetRecordById_41c2a0(*(s32 *)(GetGameData_1fede0()->sub + 0x6C), (long long)(ctl->id), (long long)(-1), 1);
    if (mk == 0) return;
    if (mk->flags & 0x3E) {
        cam = ObjRecGetLiveObject_1c3bc0(world, *(s32 *)(world + 0x4344));
        if (cam == 0) return;
        cam->GetMat(&m);
        { Vec4 *pv = &v; pv->x = D_0047F0B0; pv->y = D_0047F0B4; pv->z = D_0047F0B8; pv->w = D_0047F0BC; }
        v.x = mk->x;
        v.y = mk->y;
        v.z = mk->z;
        if (VecDistance_13d3d0(&m, &v) <= 320.0f) return;
        if (ctl->target == -1) return;
        obj = ObjRecGetLiveObject_1c4a90(world, ctl->target);
        if (obj == 0) return;
        a = ModelObjGetScaledHeight_23b110(obj);
        pos.x = mk->x;
        pos.y = mk->y + a;
        pos.z = mk->z;
        pos.w = 1.0f;
        if (mk->flags & 2) { tu = 0x86; tv = 0x14; }
        if (mk->flags & 4) { tu = 0x74; tv = 0x14; }
        if (mk->flags & 8) { tu = 0x98; tv = 0x14; }
        if (mk->flags & 0x10) { tu = 0xAA; tv = 0x14; }
        if (ProjectToScreenOffset_15d160(&sa, &pos) != 0) {
            mgr = GetDrawCtx_15de80();
            sa.x -= 0x80;
            x1 = sa.x + 0x100;
            sa.y -= 0x180;
            z = sa.z;
            y1 = sa.y + 0x100;
            W = DrawEnvGetWidth_1451e0(mgr);
            H = DrawEnvGetHeight_1451d0(mgr);
            W <<= 4;
            ZERO16(fa0);
            fa0.x = (f32)x1;
            fa0.y = (f32)sa.y;
            fa0.z = (f32)sa.z;
            ZERO16(fa1);
            fa1.y = (f32)y1;
            fa1.z = (f32)sa.z;
            fa1.x = (f32)sa.x;
            if (sa.x >= W || x1 <= 0) return;
            if ((f32)sa.y < 0.0f || sa.y > H << 4) return;
            if ((f32)y1 < 0.0f || y1 > H << 4) return;
            du = 0;
            off = 0;
            if (sa.x <= 0) {
                off = sa.x;
                if (sa.x / 16 == 0) off = 0;
                du = -off >> 4;
            }
            if (x1 > W) {
                off = x1 - W;
                du = -(off >> 4);
            }

            db = GetDrawCtxNameTable_15de40();
            DrawListAddTexLoad_1418c0(mgr, 0x338, 1.0f);
            tex = NameTableFindByName_159fb0(db, D_00461E00, 0x338);
            c = DrawListBeginPrim_141b00(mgr);
            a = 128.0f * Sinf_128fd0(ctl->scale);
            GsPktSetOriginMode_13e2f0(c, 0);
            GsPktSetTextured_13e400(c, 1);
            GsPktSetAlphaBlend_13e500(c, 1);
            GsPktSetBlendMode_13e4f0(c, 1);
            GsPktEnableAlphaTest_13e4d0(c, 1);
            GsPktSetGouraud_13e3b0(c, 1);
            GsPktSetTexFilter_13e3d0(c, 1);
            GsPktSetZWriteMask_13e430(c, 0);
            GsPktSetFrameMask_13e420(c, -1);
            GsPktEnableZTest_13e460(c, 1);
            GsPktSetUseUV_13e3e0(c, 1);
            GsPktOpenPrim_13f730(c, 6);
            GsPktSetTexture_13ec00(c, tex);
            GsPktSetRGBAQ_13ee40(c, 0x80, 0x80, 0x80, (s32)a);
            u0 = tu + 1;
            tu += 0x11;
            if (off != 0) {
                if (du > 0) {
                    u0 += du;
                    sa.x = 0;
                } else {
                    tu += du;
                    x1 = W;
                }
            }
            GsPktSetUV_13ed60(c, u0, tv + 1);
            GsPktSetXYZ_13ef10(c, sa.x, sa.y, sa.z);
            GsPktSetUV_13ed60(c, tu, tv + 0x13);
            GsPktSetXYZ_13ef10(c, x1, y1, z);
            GsPktClose_13f5b0(c);
            DrawListEndPrim_141a20(mgr);
        }
    }
    if (!(mk->kind & 6)) return;
    if (ctl->target == -1) return;
    objb = ObjRecGetLiveObject_1c4a90(world, ctl->target);
    if (objb == 0) return;
    ab = ModelObjGetScaledHeight_23b110(objb);
    pos.x = mk->x;
    pos.y = mk->y + ab;
    pos.z = mk->z;
    pos.w = 1.0f;
    if (ProjectToScreenOffset_15d160(&sb, &pos) == 0) return;
    mgrb = GetDrawCtx_15de80();
    zb = sb.z;
    sb.x -= 0x200;
    sb.y -= 0x280;
    xb1 = sb.x + 0x400;
    yb1 = sb.y + 0x280;
    Wb = DrawEnvGetWidth_1451e0(mgrb);
    Hb = DrawEnvGetHeight_1451d0(mgrb);
    Wb <<= 4;
    ZERO16(fb0);
    fb0.x = (f32)xb1;
    fb0.y = (f32)sb.y;
    fb0.z = (f32)sb.z;
    ZERO16(fb1);
    fb1.y = (f32)yb1;
    fb1.z = (f32)sb.z;
    fb1.x = (f32)sb.x;
    if (sb.x >= Wb || xb1 <= 0) return;
    if ((f32)sb.y < 0.0f || sb.y > Hb << 4) return;
    if ((f32)yb1 < 0.0f || yb1 > Hb << 4) return;
    dub = 0;
    offb = 0;
    if (sb.x <= 0) {
        offb = sb.x;
        if (sb.x / 16 == 0) offb = 0;
        dub = -offb >> 4;
    }
    if (xb1 > Wb) {
        offb = xb1 - Wb;
        dub = -(offb >> 4);
    }
    DrawListAddTexLoad_1418c0(mgrb, 0x32B, 1.0f);
    cb = DrawListBeginPrim_141b00(mgrb);
    texb = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00461E08, 0x32B);
    GsPktSetOriginMode_13e2f0(cb, 0);
    GsPktSetTextured_13e400(cb, 1);
    GsPktSetAlphaBlend_13e500(cb, 1);
    GsPktSetBlendMode_13e4f0(cb, 1);
    GsPktEnableAlphaTest_13e4d0(cb, 1);
    GsPktSetGouraud_13e3b0(cb, 1);
    GsPktSetTexFilter_13e3d0(cb, 1);
    GsPktSetZWriteMask_13e430(cb, 0);
    GsPktSetFrameMask_13e420(cb, -1);
    GsPktEnableZTest_13e460(cb, 1);
    GsPktSetUseUV_13e3e0(cb, 1);
    GsPktOpenPrim_13f730(cb, 6);
    GsPktSetTexture_13ec00(cb, texb);
    GsPktSetRGBAQ_13ee40(cb, 0x80, 0x80, 0x80, 0x80);
    ub0 = 0xC1;
    tub = 0xFF;
    if (offb != 0) {
        if (dub > 0) {
            ub0 += dub;
            sb.x = 0;
        } else {
            tub += dub;
            xb1 = Wb;
        }
    }
    GsPktSetUV_13ed60(cb, ub0, 0x100);
    GsPktSetXYZ_13ef10(cb, sb.x, sb.y, sb.z);
    GsPktSetUV_13ed60(cb, tub, 0x128);
    GsPktSetXYZ_13ef10(cb, xb1, yb1, zb);
    GsPktClose_13f5b0(cb);
    DrawListEndPrim_141a20(mgrb);
}
