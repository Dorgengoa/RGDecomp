/* rgp:protos */
#define RGP_SELF_EventCastFrameAnimUpdateAllMaybe_24cd20 1
#define RGP_SELF_it_begin 1
#define RGP_SELF_it_next 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct M4 { V4 r[4]; } M4;
typedef struct Sub {
    u8 pad0[0x3C];
    s16 h3C;
    s16 h3E;
    u8 pad40[0x20];
    s16 h60;
    u8 pad62[0xE];
    s32 x70;
} Sub;
typedef struct Item {
    u8 pad0[0x1C];
    s32 id;
    u8 pad20[0x30];
    Sub sub;
    u8 padC4[0xC];
    s32 id2;
    u8 padD4[0xC];
    f32 pos[2];
    s32 state[2];
    u8 padF0[8];
    s32 mode[2];
    f32 spd[2];
    f32 lim[2][2];
    s32 bone[2];
    s32 axis[2];
    f32 off[2];
} Item;
typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 key;
} Node;
typedef struct Mgr {
    Node *head;
    Node *cur;
    s32 end;
    u8 padC[0x314];
    s32 *ids;
    s32 count;
} Mgr;
typedef struct Parm { s32 x0; u8 pad4[0x18]; f32 f1C; } Parm;
typedef struct Bone { u8 pad[0x60]; M4 m; } Bone;

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
extern char D_0045EB00[];
extern char D_0045EBA8[];
extern char D_0045EBB0[];
extern char D_0045EBB8[];
extern f32 D_0047D24C;
extern f32 D_0047D90C;

static inline s32 it_begin(Mgr *l)
{
    if (l->cur != 0) return -1;
    l->cur = l->head;
    l->end = 0;
    return 0;
}

static inline Item *it_next(Mgr *l, s32 *key)
{
    Node *n = l->cur;
    Item *r;
    if (n == 0) return 0;
    *key = n->key;
    r = (Item *)((u8 *)n + 0x10);
    l->cur = n->next;
    if (l->cur == 0) l->end = 1;
    return r;
}

void EventCastFrameAnimUpdateAllMaybe_24cd20(Mgr *o, s32 ctx)
{
    M4 mm __attribute__((aligned(16)));
    M4 m __attribute__((aligned(16)));
    Parm *pm;
    s32 mdl2;
    s32 mdl;
    f32 pos;
    Sub *sb;
    s32 k;
    s32 state;
    Bone *nd;
    f32 hi;
    f32 spd;
    s32 id;
    f32 off;
    Bone *b;
    f32 mode;
    s32 key;
    s32 i;
    f32 l;
    f32 lo;
    s32 axis;
    Item *it;
    f32 a;

    for (i = 0; i < o->count; i++) {
        id = o->ids[i];
        if (it_begin(o) != 0) {
            it = 0;
        } else {
            while ((it = it_next(o, &key)) != 0) {
                if (id == key) break;
            }
            o->cur = 0;
            o->end = 0;
        }
        if (it == 0) continue;
        id = it->id;
        mdl2 = it->id2;
        mdl = ((s32)ObjRecGetLiveObject_1c4a90(ctx, id));
        mdl2 = ((s32)ObjRecGetLiveObject_1c4a90(ctx, mdl2));
        if (mdl != 0 && mdl2 != 0) {
            b = ((Bone *)ModelGetFrame_1511f0(mdl2, ModelFindFrameIndexByName_151220(mdl2, D_0045EB00)));
            if (b == 0) b = ((Bone *)ModelGetFrame_1511f0(mdl2, ModelFindFrameIndexByName_151220(mdl2, D_0045EBA8)));
            if (b == 0) b = ((Bone *)ModelGetFrame_1511f0(mdl2, ModelFindFrameIndexByName_151220(mdl2, D_0045EBB0)));
            if (b == 0) b = ((Bone *)ModelGetFrame_1511f0(mdl2, ModelFindFrameIndexByName_151220(mdl2, D_0045EBB8)));
            if (b != 0) {
                sb = &it->sub;
                if (b != 0) {
                    sb->x70 = (s32)b;
                    sb->h60 = 1;
                }
                sb->h3C = 1;
                sb->h3E = 0;
                HeadLookUpdate_1c5460(sb, ctx);
            }
        }
        for (k = 0; k < 2; k++) {
            pos = it->pos[k];
            mode = (f32)it->mode[k];
            state = it->state[k];
            spd = it->spd[k];
            off = it->off[k];
            hi = it->lim[k][0] + off;
            lo = it->lim[k][1] + off;
            switch (state) {
            case 0:
                break;
            case 1:
                pos *= D_0047D90C;
                a = (pos < 0.0f) ? -pos : pos;
                if (a < D_0047D24C) {
                    pos = 0.0f;
                    state = 0;
                }
                break;
            case 2:
                if (mode == 0.0f) {
                    pos += spd;
                    if (!(pos < hi)) {
                        mode = 1.0f;
                        l = it->lim[k][(s32)mode];
                        it->off[k] = l * ((f32)(Rand_133710() % 50 + 50) / 100.0f);
                    }
                } else if (mode == 1.0f) {
                    pos -= spd;
                    if (pos <= lo) {
                        mode = 0.0f;
                        l = it->lim[k][(s32)mode];
                        it->off[k] = l * ((f32)(Rand_133710() % 50 + 50) / 100.0f);
                    }
                }
                break;
            }
            it->pos[k] = pos;
            it->mode[k] = (s32)mode;
            it->state[k] = state;
            if (mdl != 0 && state != 0) {
                nd = ((Bone *)ModelGetFrame_1511f0(mdl, it->bone[(u32)k]));
                axis = it->axis[(u32)k];
                if (nd == 0) {
                    pm = ((Parm *)ObjFindNthAttachPoint_1addc0(mdl, 5, 0));
                    if (pm != 0) {
                        nd = ((Bone *)ModelGetFrame_1511f0(mdl, pm->x0));
                        if (!(pm->f1C <= 0.0f)) {
                            axis = (s32)(pm->f1C - 0.5f);
                        } else {
                            axis = 2;
                        }
                    }
                }
                if (nd != 0) {
                    switch (axis) {
                    case 0:
                        MtxRotX_13ce90(&m, pos);
                        break;
                    case 1:
                        MtxRotY_13ce20(&m, pos);
                        break;
                    case 2:
                        MtxRotZ_13cdb0(&m, pos);
                        break;
                    default:
                        MtxRotZ_13cdb0(&m, pos);
                        break;
                    }
                    mm.r[0] = nd->m.r[0];
                    mm.r[1] = nd->m.r[1];
                    mm.r[2] = nd->m.r[2];
                    mm.r[3] = nd->m.r[3];
                    MtxMulVec4_13c900(&mm.r[0], &m, &mm.r[0]);
                    MtxMulVec4_13c900(&mm.r[1], &m, &mm.r[1]);
                    MtxMulVec4_13c900(&mm.r[2], &m, &mm.r[2]);
                    ModelFrameSetMatrix_14a190(nd, &mm);
                }
            }
            if (state == 2) it->state[k] = 1;
        }
    }
}
