// build: mwcc b210 + -sdatathreshold 16 (the local f32 sc[4] initializer object @N must be in .sdata at 0x47E1B0)
#pragma divbyzerocheck on
#pragma optimization_level 3
#include "types.h"
#pragma vu0_mmi_reg_binding on
extern unsigned __int128 vz1a8ad0 asm("vf0");
extern unsigned __int128 va1a8ad0 asm("vf1");
extern unsigned __int128 vb1a8ad0 asm("vf2");

typedef union V4_1a8ad0 {
    struct {
        f32 x, y, z, w;
    } v;
    unsigned __int128 q;
} __attribute__((aligned(16))) V4_1a8ad0;

typedef struct B4_1a8ad0 {
    V4_1a8ad0 r[4];
} B4_1a8ad0;

typedef struct R3_1a8ad0 {
    V4_1a8ad0 r[3];
} R3_1a8ad0;

typedef struct M4_1a8ad0 {
    V4_1a8ad0 r[4];
    V4_1a8ad0 ext;
} M4_1a8ad0;

struct Part1a8ad0 {
    f32 age;
    s32 f4;
    s32 n;
    Part1a8ad0 *next;
    u8 pad10[0xB0 - 0x10];
    s32 fB0;
    u8 *data;
    u8 padB8[8];
    u8 buf[1];
};

struct Pool1a8ad0 {
    u8 pad0[4];
    Part1a8ad0 **items;
    u8 pad8[4];
    s32 cap;
    s32 count;
};

class Obj1a8ad0 {
public:
    virtual void v0(Part1a8ad0 *p);
    virtual void v1(Part1a8ad0 *p);
    virtual void fn(Part1a8ad0 *p);
};
struct Hook1a8ad0 {
    Hook1a8ad0 *next;
    Obj1a8ad0 *obj;
};

struct Tbl1a8ad0 {
    s32 n;
    V4_1a8ad0 *v;
};

struct Fx1a8ad0 {
    u8 pad0[4];
    Hook1a8ad0 *hooks;
    s32 n;
    u8 padC[8];
    s32 kind;
    u8 pad18[0xC];
    f32 start;
    f32 on;
    f32 end;
    s32 loop;
    f32 period;
    s32 attach;
    u8 pad3C[8];
    Tbl1a8ad0 *tbl;
    u8 mode;
    u8 pad49[3];
    s32 interp;
    f32 div;
    s32 maxN;
    s32 rateMode;
    f32 rate;
    f32 rateVar;
    struct Gen1a8ad0 *gens;
    u8 useAlt;
};

struct Gen1a8ad0 {
    Gen1a8ad0 *next;
    Fx1a8ad0 *def;
};

struct Inst1a8ad0 {
    f32 time;
    s32 seed;
    u8 pad8[0xC0 - 8];
    f32 accum;
    s32 seq;
    s32 histN;
    u8 padCC[4];
    V4_1a8ad0 hist[3];
    s32 genN;
    Part1a8ad0 **lists;
    Pool1a8ad0 *pools;
    s32 stop;
};

extern "C" {
void XformInitIdentity_1a86a0(M4_1a8ad0 *m);
void QwordCopy5_1a86d0(M4_1a8ad0 *d, M4_1a8ad0 *s);
void MtxGetScale_1a8580(M4_1a8ad0 *m, V4_1a8ad0 *v);
void XformPairComposeOffset_19a010(Inst1a8ad0 *inst, M4_1a8ad0 *m, s32 a);
void XformPairComposeOffsetNoScale_199f60(Inst1a8ad0 *inst, M4_1a8ad0 *m, s32 a);
void VecSub_13be40(V4_1a8ad0 *d, V4_1a8ad0 *a, V4_1a8ad0 *b);
void VecAdd_13be20(V4_1a8ad0 *d, V4_1a8ad0 *a, V4_1a8ad0 *b);
void VecScale_13be00(V4_1a8ad0 *d, V4_1a8ad0 *a, f32 s);
void VecAddInPlace_13e070(V4_1a8ad0 *d, V4_1a8ad0 *a);
void VecSubInPlace_13e050(V4_1a8ad0 *d, V4_1a8ad0 *a);
void MtxIdentity_13d2e0(B4_1a8ad0 *m);
void MtxMul_13d240(R3_1a8ad0 *d, B4_1a8ad0 *a, void *b);
f32 VecDistance_13d3d0(V4_1a8ad0 *a, V4_1a8ad0 *b);
f32 VecLength_13d4a0(V4_1a8ad0 *v);
void MtxMulVec4_13c900(V4_1a8ad0 *d, R3_1a8ad0 *m, V4_1a8ad0 *v);
void VecMul_13bd40(V4_1a8ad0 *d, V4_1a8ad0 *a, V4_1a8ad0 *b);
f32 RandFloat_1980f0(s32 *seed);
f32 RandGaussian_197d70(s32 *seed);
Part1a8ad0 *MemStackHeapAllocFront_14dd10(s32 heap, s32 size);
void MemStackHeapFree_14dcb0(s32 heap, Part1a8ad0 *p);
void XformPairInit_19a240(Part1a8ad0 *p);
s32 Rand_133710(void);
void EffParticleStoreMatrix_199f20(Part1a8ad0 *p, s32 kind, M4_1a8ad0 *m);
M4_1a8ad0 *EffParticleGetMatrix_199f00(Part1a8ad0 *p);
void MtxMulPointSwapped_1a8660(M4_1a8ad0 *m, V4_1a8ad0 *pos, V4_1a8ad0 *v);
void XformPairAddPos_19a1f0(Part1a8ad0 *p, V4_1a8ad0 *v);
void EffObjStepChannels_1a9b50(Fx1a8ad0 *def, Part1a8ad0 *p, f32 dt);
extern u8 D_0044AC40[];
extern f32 D_0047DA2C;
extern f32 D_0047DA30;
extern f32 D_0047D420;
}

static inline u8 Started1a8ad0(Fx1a8ad0 *f, f32 t)
{
    s32 r = 1;

    if (t < f->start) {
        r = 0;
    }
    return r;
}

static inline bool Dead1a8ad0(Fx1a8ad0 *f, f32 t)
{
    s32 r;

    if (f->loop != 0) {
        r = 0;
    } else {
        r = f->end < t;
    }
    return r;
}

static inline s32 Off1a8ad0(Fx1a8ad0 *f, f32 t)
{
    f32 x;
    f32 p;

    if (f->period == 0.0f) {
        return 0;
    }
    x = t - f->start;
    if (x < 0.0f) {
        return 0;
    }
    p = f->on + f->period;
    {
        f32 n = (f32)(s32)(x / p);

        x = x - n * p;
    }
    if (!(x <= f->on)) {
        return 1;
    }
    return 0;
}

static inline f32 Rand1a8ad0(s32 *seed)
{
    *seed = *seed * 0x5D588B65 + 1;
    return 2.3283064e-10f * (f32)(u32)*seed;
}

static inline bool Slot1a8ad0(Part1a8ad0 *p)
{
    return !(p->fB0 < 0);
}

static inline void Init1a8ad0(Part1a8ad0 *p, s32 n, u8 *buf)
{
    if (n != 0) {
        u8 *d = buf;
        d = (u8 *)(s32)d;
        p->age = 0;
        p->next = 0;
        p->fB0 = -1;
        XformPairInit_19a240(p);
        p->n = n;
        p->data = d;
    } else {
        p->age = 0;
        p->next = 0;
        p->fB0 = -1;
        XformPairInit_19a240(p);
        p->n = 0;
        p->data = 0;
    }
}

static inline Part1a8ad0 *Alloc1a8ad0(Pool1a8ad0 *pool)
{
    Part1a8ad0 *q;
    s32 c = pool->count;

    if (c >= pool->cap) {
        q = 0;
    } else {
        pool->count = c + 1;
        q = pool->items[c];
    }
    return q;
}

// VU0 CopyVectorXYZ (d.xyz = s.xyz) via mwcc VU0 intrinsics, no asm code.
// The `if (p) { p = (T)(s32)(u32)p; }` no-ops emit zero words but split the basic block before the
// scheduler, standing in for the barrier the original inline asm block gave (s88m 1a8b lever).
static inline void CopyXYZ1a8ad0(void *s, void *d)
{
    if (d) { d = (void *)(s32)(u32)d; }
    unsigned __int128 *dd = (unsigned __int128 *)(u32)d;
    unsigned __int128 *ss = (unsigned __int128 *)(s32)(u32)s;
    ss = (unsigned __int128 *)(s32)ss;
    va1a8ad0 = *dd;
    vb1a8ad0 = *ss;
    va1a8ad0 = _vaddbc(va1a8ad0, 0xE, vb1a8ad0, vz1a8ad0, 8);
    *dd = va1a8ad0;
}

// third call site: retail forms &s before &d and loads d before s (volatile loads keep d first).
static inline void CopyXYZb1a8ad0(void *s, void *d)
{
    if (s) { s = (void *)(s32)(u32)s; }
    if (d) { d = (void *)(s32)(u32)d; }
    unsigned __int128 *dd = (unsigned __int128 *)(u32)d;
    unsigned __int128 *ss = (unsigned __int128 *)(s32)(u32)s;
    ss = (unsigned __int128 *)(s32)ss;
    va1a8ad0 = *(volatile unsigned __int128 *)dd;
    vb1a8ad0 = *(volatile unsigned __int128 *)ss;
    va1a8ad0 = _vaddbc(va1a8ad0, 0xE, vb1a8ad0, vz1a8ad0, 8);
    *dd = va1a8ad0;
}

extern "C" s32 ParticleEmitterSpawnMaybe_1a8ad0(Fx1a8ad0 *e, s32 heap, Inst1a8ad0 *inst, s32 a3, f32 dt)
{
    M4_1a8ad0 base;
    V4_1a8ad0 altScale;
    M4_1a8ad0 alt;
    V4_1a8ad0 h[4];
    volatile f32 blend __attribute__((aligned(16)));
    R3_1a8ad0 rot;
    M4_1a8ad0 pf;
    V4_1a8ad0 off;
    V4_1a8ad0 seqv;
    V4_1a8ad0 tmp;
    V4_1a8ad0 mid;
    V4_1a8ad0 ctr;
    B4_1a8ad0 bm;
    M4_1a8ad0 *altp;
    s32 hasAlt;
    s32 n;
    f32 now;
    Gen1a8ad0 *gen;
    s32 idx;
    f32 speed;
    s32 i;

    n = 0;
    now = inst->time;
    if (!Started1a8ad0(e, now)) {
        return 0;
    }
    gen = e->gens;
    idx = 0;
    XformInitIdentity_1a86a0(&base);
    if (e->useAlt != 0) {
        XformPairComposeOffsetNoScale_199f60(inst, &base, a3);
    } else {
        XformPairComposeOffset_19a010(inst, &base, a3);
    }
    altp = 0;
    hasAlt = 0;
    if (e->mode != 0 && e->tbl != 0 && e->tbl->n > 0) {
        hasAlt = 1;
        XformInitIdentity_1a86a0(&alt);
        XformPairComposeOffset_19a010(inst, &alt, a3);
        altp = &alt;
        MtxGetScale_1a8580(altp, &altScale);
    }
    h[0].q = 0;
    speed = 0.0f;
    if (e->interp != 0) {
        V4_1a8ad0 *pos = &base.r[3];

        if (e->interp == 1) {
            if (inst->histN > 0) {
                VecSub_13be40(&h[1], &inst->hist[0], pos);
                speed = VecLength_13d4a0(&h[1]) / e->div;
            }
        } else if (e->interp == 2) {
            if (inst->histN > 0) {
                VecSub_13be40(&h[1], &inst->hist[0], pos);
                VecSub_13be40(&h[2], &inst->hist[1], pos);
                VecSub_13be40(&h[3], &inst->hist[2], pos);
                if (inst->histN < 3) {
                    for (i = inst->histN + 1; i < 3; i++) {
                        h[i].q = h[inst->histN].q;
                    }
                }
                VecSub_13be40(&mid, &h[0], &h[1]);
                VecAddInPlace_13e070(&mid, &h[1]);
                VecSubInPlace_13e050(&mid, &h[2]);
                VecScale_13be00(&mid, &mid, 0.5f);
                VecAdd_13be20(&ctr, &h[1], &mid);
                MtxIdentity_13d2e0(&bm);
                {
                B4_1a8ad0 *bmp = &bm;
                CopyXYZ1a8ad0(&h[0], &bm.r[0]);
                if (bmp) { bmp = (B4_1a8ad0 *)(s32)(u32)bmp; }
                CopyXYZ1a8ad0(&ctr, &bm.r[1]);
                if (bmp) { bmp = (B4_1a8ad0 *)(s32)(u32)bmp; }
                CopyXYZb1a8ad0(&h[1], &bm.r[2]);
                if (bmp) { bmp = (B4_1a8ad0 *)(s32)(u32)bmp; }
                MtxMul_13d240(&rot, bmp, D_0044AC40);
                }
                {
                    f32 a = VecDistance_13d3d0(&h[0], &ctr);
                    f32 b = VecDistance_13d3d0(&h[1], &ctr);

                    blend = b / (a + b);
                }
                speed = VecLength_13d4a0(&h[1]) / e->div;
            }
        }
        if (!(speed <= (f32)e->maxN)) {
            speed = (f32)e->maxN;
        }
    }
    for (; gen != 0; gen = gen->next, idx++) {
        if (!(inst->genN > idx)) {
            break;
        }
        Fx1a8ad0 *def = gen->def;
        f32 step = 1.0f;
        Part1a8ad0 **list = &inst->lists[idx];
        Part1a8ad0 *p;
        Part1a8ad0 *prev;
        Part1a8ad0 *next;

        if (def->attach != 0 && !(speed <= D_0047DA2C)) {
            step = step / speed;
        }
        if (!Dead1a8ad0(e, now)) {
        if (inst->stop == 0) {
        if (!Off1a8ad0(e, now)) {
            f32 t;
            s32 poolOff;

            n++;
            XformInitIdentity_1a86a0(&pf);
            QwordCopy5_1a86d0(&pf, &base);
            poolOff = idx * sizeof(Pool1a8ad0);
            for (t = 0.0f; t < D_0047DA30; t += step) {
                s32 interp = e->interp;
                s32 rm;
                f32 r;
                f32 add;

                if (interp != 0 && step < 1.0f) {
                    switch (interp) {
                    case 2: {
                        f32 u;

                        if (t < 0.5f) {
                            u = blend * t / 0.5f;
                        } else {
                            f32 bl = blend;

                            u = bl + (1.0f - bl) * (t - 0.5f) / 0.5f;
                        }
                        f32 sc[4] __attribute__((aligned(16))) = {0.0f, 0.0f, 1.0f, 0.0f};

                        sc[1] = u;
                        sc[0] = u * u;
                        MtxMulVec4_13c900(&off, &rot, (V4_1a8ad0 *)sc);
                        break;
                    }
                    case 1:
                        VecScale_13be00(&off, &h[1], t);
                        break;
                    default:
                        off.q = 0;
                        break;
                    }
                } else {
                    off.q = 0;
                }
                rm = e->rateMode;
                if (rm <= 0) {
                    r = e->rate;
                } else if (rm == 1) {
                    f32 x = 2.0f * (RandFloat_1980f0(&inst->seed) - 0.5f);

                    r = e->rate + e->rateVar * x;
                } else if (rm == 2) {
                    f32 x = RandGaussian_197d70(&inst->seed);

                    r = e->rate + D_0047D420 * (e->rateVar * x);
                } else {
                    r = e->rate;
                }
                add = dt * r;
                if (add < 0.0f) {
                    add = 0.0f;
                }
                inst->accum += add;
                for (; inst->accum >= 1.0f; inst->accum -= 1.0f) {
                    Pool1a8ad0 *pools = inst->pools;

                    p = 0;
                    if (pools != 0) {
                        Pool1a8ad0 *pool = (Pool1a8ad0 *)((u8 *)pools + poolOff);
                        Part1a8ad0 *q;
                        s32 c = pool->count;

                        if (c >= pool->cap) {
                            q = 0;
                        } else {
                            pool->count = c + 1;
                            q = pool->items[c];
                        }

                        if (q != 0) {
                            Init1a8ad0(q, def->n, q->buf);
                            p = q;
                        }
                    } else {
                        Part1a8ad0 *q = MemStackHeapAllocFront_14dd10(heap, def->n + 0xC);

                        if (q == 0) {
                            p = 0;
                        } else {
                            p = q;
                            p = (Part1a8ad0 *)(s32)p;
                            Init1a8ad0(p, def->n, q->buf);
                        }
                    }
                    if (p != 0) {
                        Init1a8ad0(p, def->n, p->buf);
                        if (*list != 0) {
                            p->next = *list;
                            *list = p;
                        } else {
                            *list = p;
                            p->next = 0;
                        }
                        XformPairInit_19a240(p);
                        if (def->attach != 0) {
                            Hook1a8ad0 *hk;

                            VecAdd_13be20(&pf.r[3], &base.r[3], &off);
                            p->f4 = Rand_133710();
                            for (hk = def->hooks; hk != 0; hk = hk->next) {
                                hk->obj->fn(p);
                            }
                            if (def->attach != 0) {
                                EffParticleStoreMatrix_199f20(p, def->kind, &pf);
                            }
                        } else {
                            Hook1a8ad0 *hk;

                            XformPairInit_19a240(p);
                            p->f4 = Rand_133710();
                            for (hk = def->hooks; hk != 0; hk = hk->next) {
                                hk->obj->fn(p);
                            }
                        }
                        if (hasAlt != 0) {
                            Tbl1a8ad0 *tbl = e->tbl;
                            u8 mode = e->mode;
                            s32 cnt = tbl->n;
                            s32 k = 0;

                            switch (mode) {
                            case 1:
                                inst->seq %= cnt;
                                k = inst->seq++;
                                break;
                            case 2: {
                                u32 s;
                                f32 x;

                                s = inst->seed * 0x5D588B65 + 1;
                                inst->seed = s;
                                x = (f32)cnt * (2.3283064e-10f * (f32)s);

                                k = cnt - 1;
                                k = (x >= (f32)k) ? k : (s32)x;
                                break;
                            }
                            }
                            tbl = e->tbl;
                            if (k >= 0 && tbl->n > k) {
                                seqv = tbl->v[k];
                            }
                            *(s32 *)&seqv.v.w = 0;
                            if (Slot1a8ad0(p)) {
                                MtxMulPointSwapped_1a8660(altp, &EffParticleGetMatrix_199f00(p)->r[3], &seqv);
                            } else if (e->useAlt != 0) {
                                VecMul_13bd40(&tmp, &seqv, &altScale);
                                XformPairAddPos_19a1f0(p, &tmp);
                            } else {
                                XformPairAddPos_19a1f0(p, &seqv);
                            }
                        }
                        n++;
                    }
                }
            }
        }
        }
        }
        prev = 0;
        for (p = *list; p != 0; p = next) {
            bool kill;

            next = p->next;
            p->age = p->age + dt;
            kill = Dead1a8ad0(def, p->age);
            if (inst->stop != 0 && ((volatile Fx1a8ad0 *)def)->loop != 0) {
                kill = true;
            }
            if (kill) {
                if (prev != 0) {
                    prev->next = p->next;
                } else {
                    *list = p->next;
                }
                if (inst->pools != 0) {
                    Pool1a8ad0 *pool = (Pool1a8ad0 *)((u8 *)inst->pools + idx * sizeof(Pool1a8ad0));

                    if (pool->count > 0) {
                        pool->items[--pool->count] = p;
                    }
                } else {
                    MemStackHeapFree_14dcb0(heap, p);
                }
            } else {
                prev = p;
                EffObjStepChannels_1a9b50(def, p, dt);
                n++;
            }
        }
    }
    if (e->interp != 0) {
        for (i = 1; i >= 0; i--) {
            *(unsigned __int128 *)&inst->hist[i + 1] = *(unsigned __int128 *)&inst->hist[i];
        }
        inst->hist[0] = base.r[3];
        inst->histN++;
        if (inst->histN >= 3) {
            inst->histN = 3;
        }
    }
    return n;
}
