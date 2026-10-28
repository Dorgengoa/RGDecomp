/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;
typedef struct Mtx4 { u128 r[4]; } Mtx4;

typedef struct Light {
    u8 pad0[0x20];
    f32 radius;
    u8 pad24[0xC];
} Light;

typedef struct Env {
    u8 pad0[0xC0];
    u128 color;
    u8 padD0[0x10];
    Light lights[4];
} Env;

typedef struct Cam {
    u8 pad0[0xC];
    s32 active;
    u8 b10;
    u8 pad11[0x9F];
    u8 mB0[0x220];
    u8 m2D0[0x100];
    u8 m3D0[0x40];
    u8 m410[0x40];
    u8 m450[0x40];
    u8 m490[0x40];
} Cam;

typedef struct Scene {
    u8 pad0[0xF20];
    Cam *cam;
    u8 padF24[0x36B4 - 0xF24];
    Env *env;
} Scene;

typedef struct Obj {
    u8 pad0[0x20];
    s32 *col;
    u8 pad24;
    u8 b25;
    s16 h26;
    u8 pad28[6];
    s16 h2E;
    u8 pad30[0x70];
    Mtx4 m;
} Obj;

struct Info;
struct MdlB {
    u8 pad0[0x20];
    f32 min[4];
    f32 max[4];
    u8 pad40[0x10];
};
class Mdl : public MdlB {
public:
    VC_VPTR_MEMBER;
    s32 vC(s32 a0) { return VCM(s32, (void *, s32), 0xC, a0); }
    
    s32 v14(s32 a0, struct Info * a1) { return VCM(s32, (void *, s32, struct Info *), 0x14, a0, a1); }
    u8 pad54[0x10];
    s32 w64;
    u8 pad68[0xC0];
    s32 w128;
    s32 w12C;
};

typedef struct Item {
    s32 key;
    s32 obj;
    s32 mdl;
    s32 flags;
    f32 depth;
    s32 p14;
    s32 p18;
    s32 p1C;
} Item;

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    Item it;
} Node;

typedef struct Tbl {
    s32 n;
    s32 w4;
    s32 *p;
} Tbl;

typedef struct PTbl {
    s32 n;
    s32 *p;
} PTbl;

typedef struct Req {
    s32 on;
    s32 w4;
    Tbl *clr;
    PTbl *mdls;
    s32 bounds;
    u8 pad14[0xC];
    u128 bmin;
    u128 bmax;
    s32 key;
    Node *list;
} Req;

typedef struct Ctx {
    s32 on;
    u8 pad4[0x100];
    PTbl *objs;
    u8 pad108[0x68];
    f32 scale;
} Ctx;

typedef struct Info {
    s32 mode;
    f32 scale;
    u8 pad8[8];
    u128 col;
} Info;

typedef struct Mesh {
    u8 pad0[0x28];
    s32 base;
    s32 idx;
} Mesh;

extern "C" {
extern void AabbProjectScreenBounds_13c4f0(Vec4 *, Vec4 *, void *, Mtx4 *, f32 *, f32 *);
extern void MtxMulPoint_13c890(Vec4 *, Mtx4 *, Light *);
extern void MtxInverse_13cf40(Mtx4 *, Mtx4 *);
extern void MtxMulAffine_13d1d0(Mtx4 *, void *, Mtx4 *);
extern void BBoxUnion_13dea0(Vec4 *, Vec4 *);
extern Mesh *DrawListGetCurBuf_142790(Scene *);
extern s32 VifPktUploadMatrix_148440(Scene *, s32, Mtx4 *);
extern void MemStackAllocQw_14d950(Mesh *, s32);
extern void BoxTransformExtentsVu0Maybe_14fed0(Vec4 *, Vec4 *, void *);
extern void BoxToCenterExtentsVu0Maybe_14ff40(f32 *, Mtx4 *);
extern s32 ModelBuildSkinMtxPacketMaybe_150390(Ctx *, Scene *, s32, Req *, s32, s32);

}

#pragma optimization_level 3
extern "C" s32 ModelPrepareDrawMaybe_14f760(Ctx *ctx, Scene *sc, Req *req)
{
    Light *lights[4];
    Mtx4 m __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x10 + sizeof(Vec4)) + (0x0 + sizeof(Vec4)) + (0x10) + (0x20)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Vec4) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    __attribute__((aligned(16))) unsigned char rgp_blk2[(0x10 + sizeof(Vec4)) + (0x0 + sizeof(Vec4)) + (0x10) + (0x20)]; typedef char rgp_blk2_chk0[(0x0) + sizeof(Vec4) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    Mtx4 wm __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Info info __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 f __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 e __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Mtx4 inv __attribute__((aligned(16)));
    Vec4 p __attribute__((aligned(16)));
    Node *node;
    Mesh *mesh;
    s32 count;
    s32 hasB;
    s32 fail;
    s32 vis;
    s32 fl;
    Cam *cam;
    Env *env;
    PTbl *mdls;
    Tbl *clr;
    s32 key;
    s32 start;
    s32 cur;
    Light *lp;
    s32 i;
    s32 on;
    s32 anyL;
    Item *it;
    Obj *obj;
    s32 flags;
    Mdl *mdl;
    f32 depth;
    s32 bb;
    s32 *col;
    s16 h;
    s32 j;
    f32 r;
    s32 n;
    s32 q;
    s32 *pz;

    if (req == NULL) {
        return 0;
    }
    if (req->on == 0) {
        return 0;
    }
    mesh = DrawListGetCurBuf_142790(sc);
    if (mesh == NULL || ctx->on == 0) {
        return 0;
    }
    node = req->list;
    cam = sc->cam;
    env = sc->env;
    mdls = req->mdls;
    clr = req->clr;
    key = req->key;
    if (node == NULL) {
        return 0;
    }
    count = 0;
    start = mesh->base + mesh->idx * 16;
    cur = start;
    if (cam->active != 0) {
        lp = env->lights;
        for (i = 0; i < 4; i++) {
            on = 1;
            if (lp->radius <= 0.0f) {
                on = 0;
            }
            if ((u8)on) {
                lights[count] = lp;
                count++;
            }
            lp++;
        }
    }
    hasB = 0;
    fail = 0;
    anyL = count > 0;
    for (; node != NULL; node = node->next) {
        it = &node->it;
        if (key != 0 && it->key != key) {
            continue;
        }
        obj = (Obj *)ctx->objs->p[it->obj];
        if (obj == NULL) {
            fail = 1;
            break;
        }
        if (obj->b25 == 0) {
            it->p14 = 0;
            it->p18 = 0;
            continue;
        }
        mdl = (Mdl *)mdls->p[it->mdl];
        if (mdl == NULL) {
            fail = 1;
            break;
        }
        flags = 0;
        depth = 0.0f;
        m.r[0] = obj->m.r[0];
        m.r[1] = obj->m.r[1];
        m.r[2] = obj->m.r[2];
        m.r[3] = obj->m.r[3];
        fl = 0;
        if (mdl->vC(2) != 0) {
            bb = mdl->w128 > 0;
            if (bb) {
                bb = mdl->w12C != 0;
            }
            if ((u8)bb) {
                fl |= 1;
            }
            bb = mdl->w64 != 0x20;
            if (bb) {
                fl |= 2;
            }
        }
        flags |= fl;
        MtxMulAffine_13d1d0(&wm, cam->mB0, &m);
        vis = 1;
        info.scale = ctx->scale * ((f32)obj->h2E / 16384.0f);
        col = obj->col;
        if (col != NULL && *col != 0) {
            info.col = *(u128 *)(col + 4);
        } else {
            info.col = env->color;
        }
        BoxToCenterExtentsVu0Maybe_14ff40(mdl->min, &wm);
        BoxTransformExtentsVu0Maybe_14fed0(&a, &b, cam->m3D0);
        if (b.x <= -a.x || b.y <= -a.y || b.z <= -a.z || b.w <= -a.w) {
            vis = 0;
        } else {
            BoxTransformExtentsVu0Maybe_14fed0(&a, &b, cam->m410);
            depth = b.x;
            if (depth <= -a.x || b.y <= -a.y) {
                vis = 0;
            }
        }
        if (vis == 0) {
            it->p14 = 0;
            it->p18 = 0;
            continue;
        }
        h = obj->h26;
        if (h & 8) {
            flags |= 0x10;
        }
        if (cam->b10 != 0 || (h & 1)) {
            info.mode = 3;
        } else {
            info.mode = 1;
        }
        BoxTransformExtentsVu0Maybe_14fed0(&c, &d, cam->m490);
        while (!(d.x <= c.x)) {
            if (d.y <= c.y) {
                break;
            }
            BoxTransformExtentsVu0Maybe_14fed0(&e, &f, cam->m450);
            if (!(f.x <= e.x) && !(f.y <= e.y) && !(f.z <= e.z) && !(f.w <= e.w)) {
                info.mode = 0;
            }
            break;
        }
        if (anyL) {
            MtxInverse_13cf40(&inv, &m);
            for (j = 0; j < count; j++) {
                lp = lights[j];
                MtxMulPoint_13c890(&p, &inv, lp);
                r = 1.25f * lp->radius;
                if (!(p.x < mdl->max[0] - r) && !(p.y < mdl->max[1] - r) && !(p.z < mdl->max[2] - r) &&
                    p.x <= mdl->min[0] + r && p.y <= mdl->min[1] + r && p.z <= mdl->min[2] + r) {
                    flags |= 4;
                    info.mode |= 0x40;
                    break;
                }
            }
        }
        if (info.mode & 1) {
            flags |= 8;
        }
        n = VifPktUploadMatrix_148440(sc, cur, &m);
        it->p14 = cur;
        q = cur + n * 16;
        n = mdl->v14(q, &info);
        it->p18 = q;
        it->flags = flags;
        q = q + n * 16;
        it->depth = depth;
        cur = q;
        n = ModelBuildSkinMtxPacketMaybe_150390(ctx, sc, q, req, it->mdl, it->obj);
        if (n > 0) {
            cur += n * 16;
        } else {
            fail = 1;
            break;
        }
        if (req->bounds != 0) {
            if (hasB == 0) {
                AabbProjectScreenBounds_13c4f0(&(*(Vec4 *)(rgp_blk1 + 0x0)), &(*(Vec4 *)(rgp_blk1 + 0x10)), cam->m2D0, &m, mdl->min, mdl->max);
                hasB = 1;
            } else {
                AabbProjectScreenBounds_13c4f0(&(*(Vec4 *)(rgp_blk2 + 0x0)), &(*(Vec4 *)(rgp_blk2 + 0x10)), cam->m2D0, &m, mdl->min, mdl->max);
                BBoxUnion_13dea0(&(*(Vec4 *)(rgp_blk1 + 0x0)), &(*(Vec4 *)(rgp_blk2 + 0x0)));
            }
        }
        it->p1C = q;
    }
    if (fail) {
        return 0;
    }
    if (hasB) {
        req->bmin = *(u128 *)&(*(Vec4 *)(rgp_blk1 + 0x0));
        req->bmax = *(u128 *)&(*(Vec4 *)(rgp_blk1 + 0x10));
    }
    pz = clr->p;
    for (n = clr->n; n > 0; n--) {
        *pz = 0;
        pz++;
    }
    n = (cur - start) / 16;
    MemStackAllocQw_14d950(mesh, n);
    return n;
}
