/* rgp:protos */
#define RGP_SELF_AiCmdCountObjsInRangeMaybe_2c51b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Sub18 {
    u8 pad0[0x18E];
    s16 m18E;
} Sub18;

typedef struct Sys2c5 {
    u8 pad0[0x18];
    Sub18 *m18;
} Sys2c5;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct G2c5 {
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
    s32 list[16];
    s32 count;
    s32 flag;
} G2c5;
extern G2c5 D_004DB920;

s32 AiCmdCountObjsInRangeMaybe_2c51b0(s64 *arg0)
{
    s32 buf1C0[0x80] __attribute__((aligned(16)));
    s32 ids[0x20] __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    V4 a __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    V4 d __attribute__((aligned(16)));
    V4 up __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    V4 m[4] __attribute__((aligned(16)));
    s32 tbl;
    Sys2c5 *sys;
    s32 id;
    s64 *start;
    s32 r;
    s32 r2;
    s32 ty;
    s32 op;
    void *o;
    void *q;
    void *o2;
    f32 f23;
    f32 f22;
    f32 f21;
    f32 f20;
    s32 i;
    s32 j;
    s32 n;

    tbl = D_004DB920.m0;
    sys = ((Sys2c5 *)GetGameData_1fede0());
    id = ((short)CharaGetId_214a80(D_004DB920.mC));
    start = arg0;
    arg0++;
    r = ScriptSlotGetInt_2cc9c0(arg0++);
    ty = ScriptSlotGetInt_2cc9c0(arg0++);
    op = ScriptSlotGetInt_2cc9c0(arg0++);
    if (r == 0x102) {
        if (id >= 0 && id < 12) {
            r = 0x100;
        }
        if (id >= 0x80 && id < 0x9C) {
            r = 0x101;
        }
    } else if (r == 0x103) {
        if (id >= 0 && id < 12) {
            r = 0x101;
        }
        if (id >= 0x80 && id < 0x9C) {
            r = 0x100;
        }
    }
    switch (r) {
    case 0xFF:
        r2 = AiCollectAllIds_2cd4d0(buf1C0, 0x80);
        break;
    case 0x100:
        r2 = PartyCollectLiveMemberIds_2cd6e0(buf1C0);
        break;
    case 0x101:
        r2 = AiCollectTargetIds_2cd530(buf1C0);
        break;
    case 0x104:
        r2 = 1;
        buf1C0[0] = sys->m18->m18E;
        break;
    default:
        buf1C0[0] = r;
        r2 = 1;
        break;
    }
    if (r2 == 0) {
        ScriptSlotStoreIntRef_2cc900(start, r2);
        return 1;
    }
    switch (op) {
    case 0:
        v.x = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.y = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.z = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.w = ScriptSlotGetFloat_2cc9a0(arg0);
        r2 = ObjFindAttachPointsInRangeMaybe_2cd960(tbl, id, buf1C0, r2, &v, ty, 0, ids);
        break;
    case 4:
        v.x = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.y = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.z = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.w = ScriptSlotGetFloat_2cc9a0(arg0);
        r2 = ObjFindAttachPointsInRangeMaybe_2cd960(tbl, id, buf1C0, r2, &v, ty, 2, ids);
        break;
    case 8:
        o = ObjRecGetLiveObject_1c4a90(tbl, id);
        if (o == 0) {
            return 0;
        }
        n = *(s32 *)arg0;
        if (n == 0) {
            q = ModelGetFrame_1511f0(o, ScriptSlotGetInt_2cc9c0(arg0++));
        } else if (n == 2) {
            q = ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, ScriptSlotGetCodeAddr_2cc980(arg0++)));
        } else {
            return 0;
        }
        if (q == 0) {
            return 0;
        }
        v.x = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.y = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.z = ScriptSlotGetFloat_2cc9a0(arg0++);
        v.w = 1.0f;
        FrameTransformPoint_148f60(q, &v, &v);
        v.w = ScriptSlotGetFloat_2cc9a0(arg0);
        r2 = ObjFindAttachPointsInRangeMaybe_2cd960(tbl, id, buf1C0, r2, &v, ty, 2, ids);
        break;
    case 9:
        f23 = ScriptSlotGetFloat_2cc9a0(arg0++);
        f22 = ScriptSlotGetFloat_2cc9a0(arg0++);
        f21 = ScriptSlotGetFloat_2cc9a0(arg0++);
        f20 = ScriptSlotGetFloat_2cc9a0(arg0);
        n = D_004DB920.m8;
        j = AiGetTargetCharaId_2c0fd0(D_004DB920.m10);
        o2 = ObjRecGetLiveObject_1c4a90(D_004DB920.m0, n);
        o = ObjRecGetLiveObject_1c4a90(D_004DB920.m0, j);
        if (o2 != 0 && o != 0) {
            q = ModelGetRootFrame_1511a0(o2);
            o2 = ModelGetRootFrame_1511a0(o);
            if (q != 0 && o2 != 0) {
                FrameGetWorldPos_148f30(q, &a);
                FrameGetWorldPos_148f30(o2, &b);
                b.y = a.y;
                VecSub_13be40(&d, &b, &a);
                d.w = 0.0f;
                VecNormalize_13bd90(&d, &d);
                up.y = 1.0f;
                up.x = 0.0f;
                up.z = 0.0f;
                up.w = 0.0f;
                sceVu0OuterProduct(&c, &d, &up);
                c.w = 0.0f;
                m[3].w = 1.0f;
                v.x = f23;
                *(u128 *)&m[0] = *(u128 *)&c;
                v.y = f22;
                *(u128 *)&m[1] = *(u128 *)&up;
                v.z = f21;
                *(u128 *)&m[2] = *(u128 *)&d;
                m[3].x = 0.0f;
                m[3].y = 0.0f;
                m[3].z = 0.0f;
                v.w = 0.0f;
                MtxMulVec4_13c900(&v, m, &v);
                VecAdd_13be20(&v, &a, &v);
                v.w = f20;
                r2 = ObjFindAttachPointsInRangeMaybe_2cd960(tbl, id, buf1C0, r2, &v, ty, 2, ids);
            }
        }
        break;
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
        break;
    }
    if (D_004DB920.flag != 0) {
        for (i = 0; i < r2; i++) {
            n = D_004DB920.count;
            if (n < 16) {
                for (j = 0; j < n; j++) {
                    if (D_004DB920.list[j] == ids[i]) {
                        break;
                    }
                }
                if (j == n) {
                    D_004DB920.list[n] = ids[i];
                    D_004DB920.count++;
                }
            }
        }
    }
    ScriptSlotStoreIntRef_2cc900(start, r2);
    return 1;
}
