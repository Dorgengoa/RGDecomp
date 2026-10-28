/* rgp:protos */
#define RGP_SELF_AnimBlendTwoApplyFrames_1539d0 1
#define RGP_SELF_Apply 1
#define RGP_SELF_PlayOne 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma inline_depth(8)
typedef rg_u128 u128;

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 m[4][4]; } Mtx;
typedef struct Node { struct Node *next; u16 key; } Node;
typedef struct {
    s32 rot;
    s32 quat;
    s32 pos;
    s32 scl;
    s32 hasVis;
    s32 vis;
    s32 pad18[2];
    V4 p;
    V4 q;
    V4 s;
    V4 r;
} Sample;
typedef struct {
    u8 pad0[0x24];
    u8 vis;
    u8 pad25[0x90 - 0x25];
    f32 px;
    f32 py;
    f32 pz;
} Bone;

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

static inline void Apply(Bone *o, Sample *s) {
    Mtx m __attribute__((aligned(16)));
    if (s->scl != 0) {
        FrameSetScale_14a2c0(o, &s->s);
    }
    if (s->rot != 0) {
        ModelFrameSetRotQuat_14a130(o, &s->r);
    } else if (s->quat != 0) {
        MtxIdentity_13d2e0(&m);
        MatRotateVu0_13bc20(&m, &s->q);
        ModelFrameSetRotMatrix_14a160(o, &m);
    }
    if (s->pos != 0) {
        o->px = s->p.x;
        o->py = s->p.y;
        o->pz = s->p.z;
        FrameSetDirty_14a5e0(o);
    }
    if (s->hasVis != 0) {
        o->vis = s->vis;
    }
}

static inline s32 PlayOne(s32 a, s32 anim, f32 t) {
    Sample sm __attribute__((aligned(16)));
    Node *n;
    Bone *o;
    if (a == 0) {
        return 0;
    }
    for (n = ((Node *)AnimResGetFrameKeyList_14bf10(anim)); n != 0; n = n->next) {
        o = ((Bone *)ArrayGetChecked_152fd0(a, n->key));
        if (o == 0) {
            continue;
        }
        AnimKeyEvalFrame_155e10(&sm, n, t);
        Apply(o, &sm);
    }
    return 1;
}

s32 AnimBlendTwoApplyFrames_1539d0(s32 a, s32 b, s32 c, f32 t0, f32 t1, f32 w) {
    Sample sC __attribute__((aligned(16)));
    Sample sD __attribute__((aligned(16)));
    Sample sG __attribute__((aligned(16)));
    Node *na;
    Node *nb;
    Bone *o;
    f32 iw;

    if (a == 0) {
        return 0;
    }
    na = ((Node *)AnimResGetFrameKeyList_14bf10(b));
    nb = ((Node *)AnimResGetFrameKeyList_14bf10(c));
    if (na == 0 && nb == 0) {
        return 0;
    }
    if (na == 0) {
        return PlayOne(a, c, t1);
    }
    if (nb == 0) {
        return PlayOne(a, b, t0);
    }
    ((u128 *)&sG)[0] = 0;
    ((u128 *)&sG)[1] = 0;
    iw = 1.0f - w;
    while (na != 0 || nb != 0) {
        if (na != 0 && nb == 0) {
            o = ((Bone *)ArrayGetChecked_152fd0(a, na->key));
            AnimKeyEvalFrame_155e10(&sC, na, t0);
            if (o != 0) {
                Apply(o, &sC);
            }
            na = na->next;
        } else if (na == 0 && nb != 0) {
            o = ((Bone *)ArrayGetChecked_152fd0(a, nb->key));
            AnimKeyEvalFrame_155e10(&sD, nb, t1);
            if (o != 0) {
                Apply(o, &sD);
            }
            nb = nb->next;
        } else {
            while (!((nb != 0) ^ 1) && na->key > nb->key) {
                o = ((Bone *)ArrayGetChecked_152fd0(a, nb->key));
                AnimKeyEvalFrame_155e10(&sD, nb, t1);
                if (o != 0) {
                    Apply(o, &sD);
                }
                nb = nb->next;
            }
            if (nb == 0) {
                continue;
            }
            while (!((na != 0) ^ 1) && na->key < nb->key) {
                o = ((Bone *)ArrayGetChecked_152fd0(a, na->key));
                AnimKeyEvalFrame_155e10(&sC, na, t0);
                if (o != 0) {
                    Apply(o, &sC);
                }
                na = na->next;
            }
            if (na == 0) {
                continue;
            }
            if (na->key == nb->key) {
                o = ((Bone *)ArrayGetChecked_152fd0(a, na->key));
                ((u128 *)&sG)[0] = 0;
                ((u128 *)&sG)[1] = 0;
                AnimKeyBlendFrame_155bf0(&sG, t0, iw, na);
                AnimKeyBlendFrame_155bf0(&sG, t1, w, nb);
                if (o != 0) {
                    Apply(o, &sG);
                }
            }
            na = na->next;
            nb = nb->next;
        }
    }
    return 1;
}
