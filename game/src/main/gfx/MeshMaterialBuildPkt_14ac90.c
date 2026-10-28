/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_MeshMaterialBuildPkt_14ac90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;

typedef union { u128 q; struct { f32 x, y, z, w; } f; } V4;

typedef struct Obj {
    u32 m0;
    s16 m4;
    u8 pad6;
    s8 m7;
    s16 m8;
    s16 mA;
    u8 *mC;
    s32 m10;
    s32 m14;
    s16 m18;
    s16 m1A;
    s32 m1C;
    V4 m20;
    V4 m30;
} Obj;

typedef struct Desc {
    u128 m0;
    u8 pad10[0x10];
    u128 m20;
    s32 m30;
    s32 m34;
    u8 pad38[8];
    s32 m40;
    s32 m44;
    s32 m48;
    u8 m4C;
    u8 m4D;
    u8 m4E;
    u8 m4F;
    u8 m50;
    u8 m51;
    s8 m52;
    u8 m53;
} Desc;

typedef struct Ctx { u8 pad[0x28]; u8 *m28; s32 m2C; } Ctx;
typedef struct Ctx2 { u8 pad[0x3BA0]; s32 m3BA0; } Ctx2;

extern f32 D_0047D41C __attribute__((section(".sdata")));
extern f32 D_0047D1DC __attribute__((section(".sdata")));
extern u128 D_0047DE80 __attribute__((section(".sdata")));
extern u128 D_0047DE90 __attribute__((section(".sdata")));

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MeshMaterialBuildPkt_14ac90(Obj *obj, Desc *desc, Ctx *ctx, Ctx2 *ctx2)
{
    u8 *pkt;
    s32 t;
    s32 flags;
    u32 a;
    s32 bits;
    u8 *p;
    s32 n;
    s32 total;
    s32 h;

    if (desc == 0) {
        return 0;
    }
    pkt = ctx->m28 + ctx->m2C * 16;
    t = ctx2->m3BA0;
    if (pkt == 0) {
        return 0;
    }
    flags = desc->m44;
    obj->m20.q = desc->m0;
    obj->m30.q = desc->m20;
    if (desc->m40 == 6) {
        desc->m4E = 0;
        flags |= 0x400;
    }
    if (desc->m40 == 11) {
        flags &= ~2;
        if (obj->m30.f.y <= 2.0f) {
            obj->m30.f.y = 800.0f;
        }
    }
    if (flags & 0x200) {
        flags &= ~4;
    }
    if (flags & 0x80) {
        a = desc->m53;
        obj->m20.f.w = obj->m20.f.w * ((f32)a / 128.0f);
        if (!(obj->m20.f.w <= 1.0f)) {
            obj->m20.f.w = 1.0f;
        }
        if (obj->m20.f.w < 0.0f) {
            obj->m20.f.w = 0.0f;
        }
        obj->m20.f.w = obj->m20.f.w * D_0047D41C;
    }
    total = 0;
    *(u128 *)(pkt + 0x00) = 0;
    *(u32 *)(pkt + 0x08) = 0x01000101;
    *(u32 *)(pkt + 0x0C) = 0x6C030052;
    *(u128 *)(pkt + 0x10) = obj->m20.q;
    *(u128 *)(pkt + 0x20) = 0;
    *(u128 *)(pkt + 0x30) = obj->m30.q;
    *(u128 *)(pkt + 0x40) = 0;
    *(u32 *)(pkt + 0x48) = 0x01000101;
    *(u32 *)(pkt + 0x4C) = 0x6C030056;
    *(u128 *)(pkt + 0x50) = 0;
    switch (desc->m40) {
    case 1:
        *(u32 *)(pkt + 0x50) = 0x8000;
        *(u32 *)(pkt + 0x54) = 0x90000000;
        *(u32 *)(pkt + 0x58) = 0x44444441;
        *(u32 *)(pkt + 0x5C) = 4;
        break;
    case 4:
        *(u32 *)(pkt + 0x50) = 0x8000;
        *(u32 *)(pkt + 0x54) = 0x10000000;
        *(u32 *)(pkt + 0x58) = 4;
        flags |= 0x20;
        *(u32 *)(pkt + 0x5C) = 0;
        break;
    case 5:
        *(u32 *)(pkt + 0x50) = 0x8000;
        *(u32 *)(pkt + 0x54) = 0xD0000000;
        *(u32 *)(pkt + 0x58) = 0x24124120;
        *(u32 *)(pkt + 0x5C) = 0x41241;
        break;
    case 10:
        *(u32 *)(pkt + 0x50) = 0x8000;
        *(u32 *)(pkt + 0x54) = 0x30000000;
        *(u32 *)(pkt + 0x58) = 0x412;
        *(u32 *)(pkt + 0x5C) = 0;
        break;
    case 0:
    case 2:
    case 3:
    case 6:
    case 7:
    case 8:
    case 9:
    default:
        *(u32 *)(pkt + 0x50) = 0x8000;
        *(u32 *)(pkt + 0x54) = 0x30000000;
        *(u32 *)(pkt + 0x58) = 0x412;
        *(u32 *)(pkt + 0x5C) = 0;
        break;
    }
    *(u128 *)(pkt + 0x60) = 0;
    bits = 0;
    if (flags & 2) {
        bits |= 0x10;
    }
    if (flags & 8) {
        bits |= 0x20;
    }
    if (flags & 0x20) {
        bits |= 0x40;
    }
    if (desc->m4C != 0) {
        bits |= 8;
    }
    *(u32 *)(pkt + 0x60) = bits;
    *(u32 *)(pkt + 0x64) = flags;
    *(f32 *)(pkt + 0x68) = 1.0f + D_0047D1DC * (f32)desc->m52;
    *(u128 *)(pkt + 0x70) = 0;
    p = pkt + 0x80;
    if (t != 0) {
        if (desc->m40 == 6 || desc->m40 == 8) {
            obj->mC = ((u8 *)DrawCtxGetRefracTexNode_13ffc0(ctx2));
        } else {
            obj->mC = ((u8 *)NameTableFindByName_159fb0(t, desc->m34, -1));
        }
        if (obj->mC != 0) {
            *(u128 *)(p + 0x00) = D_0047DE80;
            *(u128 *)(p + 0x10) = D_0047DE90;
            *(u64 *)(p + 0x20) = *(u64 *)(obj->mC + 0x40);
            *(u64 *)(p + 0x28) = 0x14;
            *(u64 *)(p + 0x30) = *(u64 *)(obj->mC + 0x48);
            *(u64 *)(p + 0x38) = 8;
            p += 0x40;
        }
    }
    n = (s32)(p - pkt) / 16;
    MemStackAllocQw_14d950(ctx, n);
    obj->m4 = n;
    obj->m0 = ((u32)pkt);
    obj->m8 = bits;
    obj->mA = desc->m40;
    obj->m1C = flags;
    obj->m7 = desc->m52;
    total += n;
    obj->m10 = ((s32)MemStackStrDup_14cf10(desc->m30, ctx));
    h = ((s32)MemStackNew_14e230(0x60, ctx));
    obj->m14 = h;
    if (h != 0) {
        GsEnvInit_1573b0(h);
        GsEnvSetDefaultsMaybe_1571d0(obj->m14);
        if (desc->m48 != -1) {
            GsEnvSetBlendPreset_157150(obj->m14, desc->m48);
        }
        if (desc->m4D != 0xFF) {
            GsTestSetAlphaFunc_1570c0(obj->m14, desc->m4D, desc->m4E);
        }
        if (obj->m1C & 0x2000) {
            GsTestSetAlphaFail_1570a0(obj->m14, 1);
        }
        if (desc->m4F != 0xFF) {
            GsTestSetDestAlphaMode_157010(obj->m14, desc->m4F);
            GsTestSetDate_156ff0(obj->m14, desc->m4F != 0);
        }
        if (desc->m50 != 0xFF) {
            GsTestSetZTest_156f40(obj->m14, desc->m50);
        }
        if (desc->m51 != 0xFF) {
            GsZbufSetZMask_156ee0(obj->m14, desc->m51);
        }
        if (flags & 0x80) {
            GsFbaSetEnable_156e80(obj->m14, 1);
        }
        if (flags & 0x400) {
            GsFrameSetMaskMode_156cc0(obj->m14, 1);
        }
    }
    obj->m18 = 0;
    if (obj->m1C & 1) {
        obj->m18 += 4;
    }
    if (obj->m1C & 4) {
        obj->m18 += 1;
    }
    obj->m1A = 0;
    if (obj->m1C & 0x40) {
        obj->m1A += 1;
    }
    if (desc->m52 != 0) {
        obj->m1A += 4;
    }
    return total;
}
