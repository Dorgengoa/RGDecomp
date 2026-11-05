/* rg-override: replaces game/src/main/gfx/ViewSetPerspective_1564a0.c sha256 453637120ab31fdd859f9528b6c045139fdcf994195c5e9eff751adfa239dd84
 * why: investigation switch RG_CULL_WIDEN (docs/WIDESCREEN.md "Culling check"): frustum-culling planes for a wider frame; unset = the generated body;
 *      draw-path random numbers (docs/WIDESCREEN.md "Draw-path random numbers", lane randdraw): at a port-only aspect the
 *      planes of the retail frustum are kept beside the game's (rg_cull_* below), and a frame narrower than retail WIDE
 *      culls with retail's planes; 4:3 and 16:9 run the generated body unchanged */
/* rgp:protos */
#define RGP_SELF_ViewSetPerspective_1564a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct M4 { V4 r[4]; } __attribute__((aligned(16))) M4;
typedef struct Prm {
    f32 fov;
    u8 pad4[8];
    f32 m20;
    f32 m24;
    u8 pad28[0x18];
    f32 aspect;
    u8 pad44[4];
    f32 near;
    f32 far;
} Prm;
typedef struct Cam {
    u8 pad0[0x14];
    Prm prm;
    u8 pad50[0xA0];
    M4 proj;
    M4 m130;
    u8 pad170[0x90];
    M4 m200;
    f32 m240;
    f32 m244;
    u8 pad248[8];
    M4 m250;
    u8 pad290[0x80];
    V4 pl[12];
    M4 m3D0;
    M4 m410;
    M4 m450;
    M4 m490;
} Cam;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* RG_CULL_WIDEN=K (investigation only): after the generated body, the view-frustum culling
 * planes pl[0..5] and their transposes m3D0 / m410 are rebuilt for a frame K times wider
 * (projection x scale / K).  The projection, the screen matrix and the guard-band planes
 * pl[6..11] / m450 / m490 (the VU clip-path choice) stay, so the picture must not change:
 * whatever appears only with it was culled while on screen.  Unset or <= 1: no effect. */
extern char *getenv(const char *);
extern double atof(const char *);
static f32 cull_widen(void)
{
    static f32 k = -1.0f;
    if (k < 0.0f) {
        const char *e = getenv("RG_CULL_WIDEN");
        k = e ? (f32)atof(e) : 0.0f;
    }
    return k;
}

static void cull_widen_planes(Cam *c, f32 k)
{
    M4 pw __attribute__((aligned(16)));
    M4 m __attribute__((aligned(16)));

    pw = c->proj;
    pw.r[0].x /= k;
    sceVu0TransposeMatrix(&m, &pw);
    VecAdd_13be20(&c->pl[0], &m.r[3], &m.r[2]);
    VecScale_13be00(&c->pl[0], &c->pl[0], 1.0f / VecLength_13d4a0(&c->pl[0]));
    VecSub_13be40(&c->pl[1], &m.r[3], &m.r[2]);
    VecScale_13be00(&c->pl[1], &c->pl[1], 1.0f / VecLength_13d4a0(&c->pl[1]));
    VecSub_13be40(&c->pl[2], &m.r[3], &m.r[0]);
    VecScale_13be00(&c->pl[2], &c->pl[2], 1.0f / VecLength_13d4a0(&c->pl[2]));
    VecAdd_13be20(&c->pl[3], &m.r[3], &m.r[0]);
    VecScale_13be00(&c->pl[3], &c->pl[3], 1.0f / VecLength_13d4a0(&c->pl[3]));
    VecSub_13be40(&c->pl[4], &m.r[3], &m.r[1]);
    VecScale_13be00(&c->pl[4], &c->pl[4], 1.0f / VecLength_13d4a0(&c->pl[4]));
    VecAdd_13be20(&c->pl[5], &m.r[3], &m.r[1]);
    VecScale_13be00(&c->pl[5], &c->pl[5], 1.0f / VecLength_13d4a0(&c->pl[5]));
    sceVu0TransposeMatrix(&c->m3D0, (M4 *)&c->pl[2]);
    sceVu0TransposeMatrix(&c->m410, (M4 *)&c->pl[0]);
}

/* ---- draw-path random numbers (lane randdraw 2026-11-01; docs/WIDESCREEN.md "Draw-path random
 * numbers").  Drawing a lit map object with a flickering light (NodeObjDrawLit_1947f0,
 * MapAreaModelApplyNearestPlightsMaybe_188590 -> LightFlickerScale_18e2c0) or a fire-flare batch
 * (FuncDataTableDrawFireFlaresMaybe_18eb30) draws numbers from the game's one generator
 * Rand_133710, which the AI and the event scripts use too: what is drawn feeds the logic.  Retail
 * draws what its frustum (projection aspect 0.75, or 0.5625 with the WIDE flag) lets through, so
 * the port's 4:3 and 16:9 match it.  At a wider port-only aspect (21:9, 32:9, RG_CULL_WIDEN) the
 * objects only the wider planes let through are drawn with the generator's private stream
 * (rg_crt_rand_private, src/crt/crt_libc.c): the game's sequence stays the retail one.  A frame
 * narrower than retail WIDE with the flag (16:10) culls with retail WIDE's planes (a little more
 * is drawn off screen) so that nothing retail draws is missed.
 *   retail aspect: the WIDE branch's 0.5625 when the camera gets the port's WIDE aspect
 *   (rg_aspect_d(), SceneCameraApplyAspect_1c6a10 override), else the aspect given.
 *   NodeObjIsInView_194200 override: rg_cull_retail_post (the retail test after the game's; the
 *   object is visible when either passes; extra = only the port's planes).
 *   NodeObjIsInViewUnoccludedMaybe_194100 override: no frustum test there -> rg_cull_mark(o, 0).
 *   Draw sites (NodeObjDrawLitThunk_187f50 / _188580, MapAreaModelDrawBucketLit_1883c0,
 *   MapAreaModelDrawFireFlares_1882a0 overrides): rg_cull_draw_begin(obj) .. _end around one
 *   object's drawing.
 * RG_RAND_ISOLATE=0: off (the 2026-10-31 behaviour, for A/B runs).  Host state only. */
extern float rg_aspect_d(void);
extern int rg_crt_rand_private;
typedef __UINTPTR_TYPE__ uptr194;
static int rand_isolate(void)
{
    static int on = -1;
    if (on < 0) {
        const char *e = getenv("RG_RAND_ISOLATE");
        on = !(e && e[0] == '0');
    }
    return on;
}

typedef struct CullRet { Cam *cam; s32 active; M4 m3D0; M4 m410; } CullRet;
static CullRet g_cret[16] __attribute__((aligned(16)));

static CullRet *cret_for(Cam *c, int make)
{
    s32 i;
    for (i = 0; i < 16; i++)
        if (g_cret[i].cam == c)
            return &g_cret[i];
    if (!make)
        return 0;
    for (i = 0; i < 16; i++)
        if (g_cret[i].cam == 0 || !g_cret[i].active) {
            g_cret[i].cam = c;
            return &g_cret[i];
        }
    g_cret[15].cam = c;
    return &g_cret[15];
}

/* the six frustum planes for projection aspect `aspect` (the generated body's code) */
static void cull_planes_for(Cam *c, f32 aspect, V4 *pl, M4 *m3D0, M4 *m410)
{
    M4 pw __attribute__((aligned(16)));
    M4 m __attribute__((aligned(16)));

    pw = c->proj;
    pw.r[0].x = aspect * (1.0f / Tanf_1290b8(c->prm.fov / 2.0f));
    sceVu0TransposeMatrix(&m, &pw);
    VecAdd_13be20(&pl[0], &m.r[3], &m.r[2]);
    VecScale_13be00(&pl[0], &pl[0], 1.0f / VecLength_13d4a0(&pl[0]));
    VecSub_13be40(&pl[1], &m.r[3], &m.r[2]);
    VecScale_13be00(&pl[1], &pl[1], 1.0f / VecLength_13d4a0(&pl[1]));
    VecSub_13be40(&pl[2], &m.r[3], &m.r[0]);
    VecScale_13be00(&pl[2], &pl[2], 1.0f / VecLength_13d4a0(&pl[2]));
    VecAdd_13be20(&pl[3], &m.r[3], &m.r[0]);
    VecScale_13be00(&pl[3], &pl[3], 1.0f / VecLength_13d4a0(&pl[3]));
    VecSub_13be40(&pl[4], &m.r[3], &m.r[1]);
    VecScale_13be00(&pl[4], &pl[4], 1.0f / VecLength_13d4a0(&pl[4]));
    VecAdd_13be20(&pl[5], &m.r[3], &m.r[1]);
    VecScale_13be00(&pl[5], &pl[5], 1.0f / VecLength_13d4a0(&pl[5]));
    sceVu0TransposeMatrix(m3D0, (M4 *)&pl[2]);
    sceVu0TransposeMatrix(m410, (M4 *)&pl[0]);
}

/* after the generated body (and RG_CULL_WIDEN): keep the retail planes / cull like retail.
 * aspect value: smaller = wider frame (proj x scale = aspect / tan(fov/2)). */
static void cull_retail(Cam *c, f32 aspect, s32 widened)
{
    V4 pl[6] __attribute__((aligned(16)));
    CullRet *e;
    f32 ra;

    if (!rand_isolate()) {
        if ((e = cret_for(c, 0)) != 0)
            e->active = 0;
        return;
    }
    ra = (GetAspectMode_1c6aa0() == 1 && aspect == rg_aspect_d()) ? 0.5625f : aspect;
    if (ra < aspect && !widened) {
        /* narrower than retail WIDE (16:10): cull with retail's planes */
        cull_planes_for(c, ra, c->pl, &c->m3D0, &c->m410);
    }
    if (ra > aspect || widened) {
        e = cret_for(c, 1);
        cull_planes_for(c, ra, pl, &e->m3D0, &e->m410);
        e->active = 1;
    } else if ((e = cret_for(c, 0)) != 0) {
        e->active = 0;
    }
}

/* ---- the object marks: is this object drawn only because of the port's wider planes? */
#define MK_N 16384
static uptr194 g_mk_key[MK_N];
static u8 g_mk_val[MK_N];
static s32 g_mk_used;
static s32 g_mk_extra;        /* keys marked extra now */
static unsigned long long g_retail_only;   /* retail-visible boxes the port planes missed */
static unsigned long long g_extra_draws;

unsigned long long rg_cull_extra_count(void) { return g_extra_draws; }

static u32 mk_slot(uptr194 k)
{
    return (u32)((k >> 4) * 2654435761u) & (MK_N - 1);
}

static void mk_set(uptr194 k, u8 v)
{
    u32 i = mk_slot(k);
    while (g_mk_key[i] != 0 && g_mk_key[i] != k)
        i = (i + 1) & (MK_N - 1);
    if (g_mk_key[i] == 0) {
        if (!v)
            return;   /* absent = not extra */
        if (g_mk_used >= MK_N * 3 / 4) {
            /* drop the cleared keys, keep the extra marks */
            static uptr194 kk[MK_N];
            s32 j, n = 0;
            for (j = 0; j < MK_N; j++)
                if (g_mk_key[j] != 0 && g_mk_val[j])
                    kk[n++] = g_mk_key[j];
            for (j = 0; j < MK_N; j++) {
                g_mk_key[j] = 0;
                g_mk_val[j] = 0;
            }
            g_mk_used = 0;
            g_mk_extra = 0;
            for (j = 0; j < n; j++)
                mk_set(kk[j], 1);
            mk_set(k, v);
            return;
        }
        g_mk_key[i] = k;
        g_mk_used++;
    }
    if (g_mk_val[i] != v)
        g_mk_extra += v ? 1 : -1;
    g_mk_val[i] = v;
}

static u8 mk_get(uptr194 k)
{
    u32 i = mk_slot(k);
    while (g_mk_key[i] != 0) {
        if (g_mk_key[i] == k)
            return g_mk_val[i];
        i = (i + 1) & (MK_N - 1);
    }
    return 0;
}

/* NodeObjIsInView_194200 override, after the game's test r (port planes): the box against the
 * retail planes (when this camera has them), run last so the VU0 registers end as retail's own
 * test leaves them.  Returns r || retail: the box test of a plane through the eye is not
 * monotonic in the frame width (a box beside / behind the eye can pass the narrow plane and
 * fail the wider one), so a retail-visible object is drawn (and counted) even when the port's
 * planes miss it.  The object is "extra" when only the port's planes let it in. */
void rg_randlog_obj(const char *what, const void *obj, s32 a, s32 b);
s32 rg_cull_retail_post(void *obj, void *box, void *world, s32 r)
{
    M4 buf __attribute__((aligned(16)));
    CullRet *e;
    u8 *g;
    s32 rv = -1;

    g = (u8 *)(uptr194)(u32)GetDrawCtxCamera_15de60();
    if (g != 0 && (e = cret_for((Cam *)g, 0)) != 0 && e->active) {
        MtxMul_13d240(&buf, g + 0xB0, world);
        rv = AabbInFrustum_13be60(box, &buf, &e->m3D0, &e->m410) != 0;
    }
    rg_randlog_obj("mark", obj, r, rv);
    mk_set((uptr194)obj, (u8)(r != 0 && rv == 0));
    if (rv == 1 && r == 0) {
        g_retail_only++;
        return 1;
    }
    return r;
}

/* no frustum test (NodeObjIsInViewUnoccludedMaybe_194100, a hidden object): not extra */
void rg_cull_mark(void *obj, s32 r)
{
    (void)r;
    mk_set((uptr194)obj, 0);
}

/* around one object's drawing: private random numbers for an extra object */
s32 rg_cull_draw_begin(void *obj)
{
    if (g_mk_extra == 0 || !mk_get((uptr194)obj))
        return 0;
    g_extra_draws++;
    rg_crt_rand_private++;
    return 1;
}

void rg_cull_draw_end(s32 tok)
{
    if (tok)
        rg_crt_rand_private--;
}

void ViewSetPerspective_1564a0(Cam *c, f32 fov, f32 aspect, f32 a2, f32 a3, f32 near, f32 far)
{
    M4 m __attribute__((aligned(16)));
    M4 m2 __attribute__((aligned(16)));
    Prm *p;
    s32 i;

    p = &c->prm;
    c->prm.fov = fov;
    c->prm.m20 = a2;
    c->prm.m24 = a3;
    c->prm.near = near;
    c->prm.far = far;
    c->prm.aspect = aspect;
    MtxIdentity_13d2e0(&c->proj);
    c->proj.r[0].x = aspect * (1.0f / Tanf_1290b8(p->fov / 2.0f));
    c->proj.r[1].y = 1.0f / Tanf_1290b8(p->fov / 2.0f);
    c->proj.r[2].z = -(p->far + p->near) / (p->far - p->near);
    c->proj.r[3].z = -2.0f * p->far * p->near / (p->far - p->near);
    c->proj.r[2].w = -1.0f;
    c->proj.r[3].w = 0.0f;
    MtxMul_13d240(&c->m200, &c->m130, &c->proj);
    sceVu0TransposeMatrix(&m, &c->proj);
    VecAdd_13be20(&c->pl[0], &m.r[3], &m.r[2]);
    VecScale_13be00(&c->pl[0], &c->pl[0], 1.0f / VecLength_13d4a0(&c->pl[0]));
    VecSub_13be40(&c->pl[1], &m.r[3], &m.r[2]);
    VecScale_13be00(&c->pl[1], &c->pl[1], 1.0f / VecLength_13d4a0(&c->pl[1]));
    VecSub_13be40(&c->pl[2], &m.r[3], &m.r[0]);
    VecScale_13be00(&c->pl[2], &c->pl[2], 1.0f / VecLength_13d4a0(&c->pl[2]));
    VecAdd_13be20(&c->pl[3], &m.r[3], &m.r[0]);
    VecScale_13be00(&c->pl[3], &c->pl[3], 1.0f / VecLength_13d4a0(&c->pl[3]));
    VecSub_13be40(&c->pl[4], &m.r[3], &m.r[1]);
    VecScale_13be00(&c->pl[4], &c->pl[4], 1.0f / VecLength_13d4a0(&c->pl[4]));
    VecAdd_13be20(&c->pl[5], &m.r[3], &m.r[1]);
    VecScale_13be00(&c->pl[5], &c->pl[5], 1.0f / VecLength_13d4a0(&c->pl[5]));
    sceVu0TransposeMatrix(&c->m3D0, (M4 *)&c->pl[2]);
    sceVu0TransposeMatrix(&c->m410, (M4 *)&c->pl[0]);
    ((u128 *)&c->m250)[0] = ((u128 *)&c->proj)[0];
    ((u128 *)&c->m250)[1] = ((u128 *)&c->proj)[1];
    ((u128 *)&c->m250)[2] = ((u128 *)&c->proj)[2];
    ((u128 *)&c->m250)[3] = ((u128 *)&c->proj)[3];
    for (i = 0; i < 4; i++) {
        c->m250.r[i].x *= c->m240;
        c->m250.r[i].y *= c->m244;
    }
    sceVu0TransposeMatrix(&m2, &c->m250);
    VecAdd_13be20(&c->pl[6], &m2.r[3], &m2.r[2]);
    VecScale_13be00(&c->pl[6], &c->pl[6], 1.0f / VecLength_13d4a0(&c->pl[6]));
    VecSub_13be40(&c->pl[7], &m2.r[3], &m2.r[2]);
    VecScale_13be00(&c->pl[7], &c->pl[7], 1.0f / VecLength_13d4a0(&c->pl[7]));
    VecSub_13be40(&c->pl[8], &m2.r[3], &m2.r[0]);
    VecScale_13be00(&c->pl[8], &c->pl[8], 1.0f / VecLength_13d4a0(&c->pl[8]));
    VecAdd_13be20(&c->pl[9], &m2.r[3], &m2.r[0]);
    VecScale_13be00(&c->pl[9], &c->pl[9], 1.0f / VecLength_13d4a0(&c->pl[9]));
    VecSub_13be40(&c->pl[10], &m2.r[3], &m2.r[1]);
    VecScale_13be00(&c->pl[10], &c->pl[10], 1.0f / VecLength_13d4a0(&c->pl[10]));
    VecAdd_13be20(&c->pl[11], &m2.r[3], &m2.r[1]);
    VecScale_13be00(&c->pl[11], &c->pl[11], 1.0f / VecLength_13d4a0(&c->pl[11]));
    sceVu0TransposeMatrix(&c->m450, (M4 *)&c->pl[8]);
    sceVu0TransposeMatrix(&c->m490, (M4 *)&c->pl[6]);
    if (cull_widen() > 1.0f)
        cull_widen_planes(c, cull_widen());
    cull_retail(c, aspect, cull_widen() > 1.0f);
}
