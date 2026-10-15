#include "types.h"
#pragma optimization_level 3


typedef struct { f32 x, y; } V2;
typedef struct { f32 x, y, u, v, d; } Vtx;
typedef struct { f32 a, b, c, d; } Pl;
typedef struct { Pl p[4]; } Pls;
typedef struct { s32 w[16]; } PlsI;
typedef struct { s32 x, y, w, h; } Rc;

void *GetDrawCtx_15de80(void);
s32 DrawEnvGetWidth_1451e0(void *);
s32 DrawEnvGetHeight_1451d0(void *);
s32 IsWidescreen_1c6ab0(void);
f32 AngleWrap_1cbf30(f32);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void GsPktOpenPrim_13f730(void *, s32);
void GsPktSetTexture_13ec00(void *, s32);
void GsPktSetRGBAQVec_13edd0(void *, s32);
void GsPktSetUV_13ed60(void *, s32, s32);
void GsPktSetXYZf_13f060(void *, f32, f32, f32);
void GsPktClose_13f5b0(void *);
extern Pls D_00454050;
extern f32 D_0047D7EC;

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

static inline void AddV(Vtx *q, s32 *n, f32 x, f32 y, f32 u, f32 v) {
    q += *n;
    q->x = x;
    q->y = y;
    q->u = u;
    q->v = v;
    (*n)++;
}


#define ADDQ(x_, y_, u_, v_) { q->x = x_; q->y = y_; q->u = u_; q->v = v_; q++; cnt[0]++; }
#define ADDV(q_, n_, x_, y_, u_, v_) { Vtx *w_ = &(q_)[n_]; w_->x = x_; w_->y = y_; w_->u = u_; w_->v = v_; n_++; }
static inline s32 AddR(Vtx *q, s32 n, f32 x, f32 y, f32 u, f32 v) { q[n].x = x; q[n].y = y; q[n].u = u; q[n].v = v; return n + 1; }
static inline void AddP(Vtx *q, f32 x, f32 y, f32 u, f32 v) { q->x = x; q->y = y; q->u = u; q->v = v; }
static inline void AddN(Vtx *q, s32 *n, f32 x, f32 y, f32 u, f32 v) { s32 k = *n; q[k].x = x; q[k].y = y; q[k].u = u; q[k].v = v; *n = k + 1; }

static inline f32 fmr(f32 b, f32 a) { return a * b; }

void DrawRotatedQuad_383c70(void *dst, Rc *r, s32 a2, s32 a3, f32 cx, f32 cy, f32 w, f32 h, f32 ang) {
    void *ctx;
    f32 sw;
    f32 sh;
    f32 k;
    f32 s;
    f32 c;
    V2 ax;
    V2 ay;
    s32 cnt[2];
    Pls pl;
    Vtx buf[2][16];
    Vtx *vc;
    Vtx *vn;
    Vtx *out;
    s32 j;
    s32 n;
    s32 cur;
    s32 nxt;
    Vtx *v;
    s32 i;
    f32 t;
    s32 m;
    Pl *pp;
    s32 p;
    Vtx *q;




    ctx = GetDrawCtx_15de80();
    sw = DrawEnvGetWidth_1451e0(ctx);
    sh = DrawEnvGetHeight_1451d0(ctx);
    k = IsWidescreen_1c6ab0() ? 0.75f : 1.0f;
    w *= 0.5f;
    h *= 0.5f;
    ang = AngleWrap_1cbf30(ang);
    s = Sinf_128fd0(ang);
    c = Cosf_128d30(ang);
    ZERO(&ax, 8);
    ax.x = w * c;
    ax.y = w * s;
    ZERO(&ay, 8);
    ay.x = -h * s;
    ay.y = h * c;
    ax.x *= k;
    ax.y *= D_0047D7EC;
    ay.x *= k;
    ay.y *= D_0047D7EC;
    *(PlsI *)&pl = *(PlsI *)&D_00454050;
    cur = 0;
    q = buf[cur];
    cnt[0] = 0;
    ADDQ(r->x, r->y, cx - ax.x - ay.x, cy - ax.y - ay.y);
    ADDQ(r->x + r->w, r->y, cx + ax.x - ay.x, cy + ax.y - ay.y);
    ADDQ(r->x + r->w, r->y + r->h, ay.x + (cx + ax.x), ay.y + (cy + ax.y));
    ADDQ(r->x, r->y + r->h, ay.x + (cx - ax.x), ay.y + (cy - ax.y));
    pl.p[2].a = sw;
    pl.p[3].a = sw;
    pl.p[2].b = sh;
    pl.p[3].b = sh;
    cur = 0;
    pp = pl.p;
    for (p = 0; p < 4; p++, pp++) {
        nxt = 1 - cur;
        cnt[nxt] = 0;
        v = buf[cur];
        for (i = 0; i < cnt[cur]; i++) {
            v->d = pp->c * (v->u - pp->a) + pp->d * (v->v - pp->b);
            v++;
        }
        vc = buf[cur];
        vn = vc + 1;
        out = buf[nxt];
        for (j = 0; j < cnt[cur]; j++, vc++, vn++) {
            if (j + 1 == cnt[cur]) {
                vn = buf[cur];
            }
            if (!(vc->d < 0.0f)) {
                *(V2 *)&out->x = *(V2 *)&vc->x;
                cnt[nxt]++;
                *(V2 *)&out->u = *(V2 *)&vc->u;
                out->d = vc->d;
                out++;
            }
            { f32 dn = vn->d; f32 dv = vc->d; if (dv * dn < 0.0f) {
                cnt[nxt]++;
                t = -dv / (dn - dv);
                out->u = vc->u + t * (vn->u - vc->u);
                out->v = vc->v + t * (vn->v - vc->v);
                out->x = vc->x + t * (vn->x - vc->x);
                out->y = vc->y + t * (vn->y - vc->y);
                out++;
            }
            }
        }
        cur = nxt;
    }
    if (cnt[cur] < 3) {
        return;
    }
    GsPktOpenPrim_13f730(dst, 5);
    GsPktSetTexture_13ec00(dst, a2);
    GsPktSetRGBAQVec_13edd0(dst, a3);
    m = cnt[cur];
    v = buf[cur];
    for (i = 0; i < m; i++, v++) {
        GsPktSetUV_13ed60(dst, v->x, v->y);
        GsPktSetXYZf_13f060(dst, v->u, v->v, 0.0f);
    }
    GsPktClose_13f5b0(dst);
}
