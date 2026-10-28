// SPDX-License-Identifier: CC0-1.0
// The GS drawing pipeline on the GPU: one vertex shader for the pre-expanded
// primitives, one pixel shader for the whole GS pixel pipeline (texture
// function, fog, alpha test incl. FAIL passes, destination alpha test, the GS
// blend equation, dithering, COLCLAMP, FBA, FBMSK, Z).  Mirrors
// src/ps2/gs/gs_raster.c + gs_tex.c rule for rule; docs/GPU.md lists where
// float interpolation can differ from the reference's doubles.
#include "gs_common.hlsli"

// ---- per-batch constants (gpu_internal.h GpuDrawCB, all uint4 slots) ----
cbuffer DrawCB : register(b0)
{
    uint4 D[12];
};
// The CLUT: 512 16-bit cells, two per uint.  A buffer, not a constant
// buffer: texels index it per pixel, and divergent constant-buffer indexing
// serialises (docs/GPU.md "Performance").
Buffer<uint> g_clut : register(t5);
Texture2D<float4> g_dst : register(t1);   // snapshot of the colour target
// Direct sampling (docs/GPU.md "Direct sampling"): the texture is a live
// render target, read at the internal resolution instead of the mirror.
Texture2D<float4> g_texc : register(t2);  // a colour target (or its snapshot)
Texture2D<float> g_texz : register(t3);   // a depth target
// Decoded texture (docs/GPU.md "Performance", DIRECT bit 2): level-0
// texels [D[10].z & 0xFFFF, D[10].w & 0xFFFF) x [D[10].z >> 16, D[10].w >> 16)
// of the mirror texture as RGBA8 (r | g << 8 | ...), exactly what
// tex_fetch(0, x, y) returns there (CS_decode wrote them with it).
Texture2D<uint> g_dec : register(t6);

#define F_TME (1u << 0)
#define F_FGE (1u << 1)
#define F_ABE (1u << 2)
#define F_FST (1u << 3)
#define F_DATE (1u << 4)
#define F_DATM (1u << 5)
#define F_ATE (1u << 6)
#define F_NEEDDST (1u << 7)
#define F_COLCLAMP (1u << 8)
#define F_DTHE (1u << 9)
#define F_FBA (1u << 10)
#define F_PABE (1u << 11)
#define F_FAILPASS (1u << 19)
#define F_MERGE (1u << 20)
#define F_NOZ (1u << 21)     // no depth target bound: Z is not needed

#ifdef GS_NOTEX
// untextured batches (docs/PERF-3D.md): the texture paths compile away, so
// the variant needs far fewer registers than the full shader
#define FLAGS (D[0].w & ~F_TME)
#else
#define FLAGS D[0].w
#endif
#define SCALE D[0].z
#define FPSM D[1].x
#define FBMSK D[1].y
#define AREF D[1].z
#define ALPHAABCD D[2].x
#define FIX D[2].y
#define FOGCOL D[2].z
#define ZMAX D[2].w
#define FAULT D[3].z
#define DIRECT D[3].w      // bit 0 on, bit 1 depth source, bits 8-15 source PSM,
                           // bits 16-21 / 22-28 the target's native size / 64 / 32 (0: no clamp)
// Enhancements (gpu_internal.h GE_*, docs/GPU.md "Graphics settings"):
// bits 0-1 texture filter override (1 bilinear, 2 nearest), bits 4-8
// anisotropic taps, bit 12 the texture is ordinary memory.  0 = Original.
#define ENH D[11].x
// Ordered blending (docs/GPU.md "Performance"): D[11].y, set by the core for
// batches drawn through the rasterizer-ordered view of the colour target
// (PS_main_rov*; a depth target only with ZTST ALWAYS): bits 0-3 the channel mask of pixels that
// pass the alpha test, bits 4-7 of pixels that fail it, bit 8 failing pixels
// are drawn (AFAIL FB_ONLY/RGB_ONLY), bit 9 passing pixels are drawn.
#define ROVCTL D[11].y

#ifdef GS_ROV
// The colour target as R32_UINT (the RGBA8 it holds, r | g << 8 | ...):
// every pixel's read-modify-write happens in primitive order, so blended,
// DATE and FBMSK-merge primitives that overlap need no snapshot and no
// batch split.
RasterizerOrderedTexture2D<uint> g_rov : register(u1);   // after the (unbound) SV_Target0
#endif
#ifdef GS_ZROV
// Depth in an ordered view (docs/PERF-3D.md): the depth target as R32_FLOAT
// holding exactly what the D32_FLOAT buffer held (z / 2^32).  The shader
// tests and writes it per pixel in primitive order, after every discard,
// with the comparison the output merger made (float >= / >), so blended and
// two-pass primitives under any depth test can share a batch.  ZCTL
// (D[11].z): bits 0-1 the test (GZ_*), bit 2 Z write of pixels that pass the
// alpha test (the pass drawn, without GS_ROV), bit 3 Z write of pixels that
// fail it (GS_ROV: both passes in one draw).
RasterizerOrderedTexture2D<float> g_zrov : register(u2);
#define ZCTL D[11].z
#endif

// Enhancement state of this pixel: the override/anisotropy apply (a non-
// sprite primitive, an ordinary texture, not a direct render-target read);
// the texel-space gradients per target pixel (exact triangles only).
static bool g_enh = false;
static bool g_grad_ok = false;
static float4 g_grad = float4(0, 0, 0, 0);   // du/dx, dv/dx, du/dy, dv/dy (level-0 texels)
static bool g_noexact = false;               // offset taps: float coordinates

struct VSIn {
    float2 pos : POSITION;   // window coordinates in pixels (XYOFFSET applied)
    float zf : ZF;
    uint zi : ZI;
    float4 col : COLOR;      // 0..255
    float3 stq : STQ;
    float2 uv : UV;          // texels (UV register / 16)
    float fog : FOG;
    uint vflags : VFLAGS;    // bit 0: Z is constant over the primitive (use zi)
                             // bit 1: STQ sprite, S/T from spr*
                             // bit 5: UV sprite, fixed-point DDA in spr*
                             //        (gpu_internal.h GpuVertex)
    float4 spra : SPRA;      // x0, y0, dx, dy (12.4)
    float4 sprb : SPRB;      // s0, s1, t0, t1
    float4 sprc : SPRC;      // u0, u1, v0, v1 (10.4)
};
struct VSOut {
    float4 pos : SV_Position;
    noperspective float zf : ZF;
    nointerpolation uint zi : ZI;
    noperspective float4 col : COLOR;
    noperspective float3 stq : STQ;
    noperspective float2 uv : UV;
    noperspective float fog : FOG;
    nointerpolation uint vflags : VFLAGS;
    nointerpolation float4 spra : SPRA;
    nointerpolation float4 sprb : SPRB;
    nointerpolation float4 sprc : SPRC;
};

VSOut VS_main(VSIn v)
{
    VSOut o;
    float kx = asfloat(D[0].x), ky = asfloat(D[0].y);
    o.pos = float4((v.pos.x + 0.5) * kx - 1.0, 1.0 - (v.pos.y + 0.5) * ky, 0.5, 1.0);
    o.zf = v.zf; o.zi = v.zi; o.col = v.col; o.stq = v.stq; o.uv = v.uv; o.fog = v.fog;
    o.vflags = v.vflags;
    o.spra = v.spra; o.sprb = v.sprb; o.sprc = v.sprc;
    return o;
}

float tex_lod(float q)
{
    uint lcm = (D[4].w >> 11) & 1, l = (D[4].w >> 12) & 3;
    float kk = (float)(int)D[6].x / 16.0;
    if (lcm) return kk;
    float aq = max(abs(q), 1e-30);
    return log2(1.0 / aq) * (float)(1u << l) + kk;
}

// The mip levels a sample reads (gs_tex.c gs_tex_sample): the first level,
// how many (2: trilinear, with weight f/16 on the second) and the filter.
void tex_levels(float lod, out uint k0, out uint nlev, out bool lin, out int f)
{
    uint mmag = (D[4].w >> 4) & 1, mmin = (D[4].w >> 5) & 7, mxl = min((D[4].w >> 8) & 7, 6);
    if (g_enh && (ENH & 3)) {
        // texture filter override: bilinear <-> nearest, keeping the mip mode
        // (MMIN 0 nearest, 1 linear, 2/3 nearest-mip, 4/5 linear-mip)
        if ((ENH & 3) == 1) {
            mmag = 1;
            mmin = mmin == 0 ? 1 : (mmin == 2 ? 4 : (mmin == 3 ? 5 : mmin));
        } else {
            mmag = 0;
            mmin = mmin == 1 ? 0 : (mmin == 4 ? 2 : (mmin == 5 ? 3 : mmin));
        }
    }
    k0 = 0;
    nlev = 1;
    lin = false;
    f = 0;
    if (lod <= 0.0) {
        lin = mmag != 0;
    } else if (mmin == 1) {
        lin = true;
    } else if (mmin == 2 || mmin == 4) {
        k0 = min((uint)floor(lod + 0.5), mxl);
        lin = mmin == 4;
    } else if (mmin == 3 || mmin == 5) {
        uint k = (uint)floor(lod);
        lin = mmin == 5;
        if (k >= mxl) {
            k0 = mxl;
        } else {
            k0 = k; nlev = 2;
            f = (int)((lod - (float)k) * 16.0);
        }
    }
}

#ifdef GS_EXACT
// ---- exact triangles (docs/GPU.md "Exact triangles") ----
// The reference's draw_triangle, per pixel: edge functions of the 12.4
// vertices, w1 = e1 * inv, w2 = e2 * inv (double), every attribute
// a + (b-a)*w1 + (c-a)*w2 in double, then the same truncations.  Needs the
// D3D11.1 extended doubles (ddiv, dtoi/dtou, itod); the backend falls back
// to PS_main (float interpolation) without them.
//
// Float fast path (docs/GPU.md "Checkpoint 4"): double arithmetic runs at
// 1/64 rate on consumer GPUs, so coverage uses 32-bit integer edge functions
// where they are exact (TF_SMALL), attributes equal at the three vertices are
// taken as they are (the reference's lerp returns a + 0 + 0 = a exactly), and
// every other colour, fog and texture coordinate is evaluated in float with
// a rigorous bound E on its distance to the reference's double.  A value is
// used when every number within E of it truncates to the same integer
// (decide); otherwise that one value is evaluated in double exactly as
// before.  Z and the LOD's (float)Q stay double.
struct GpuTri {
    int3 x; int3 y;          // window 12.4, the reference's vertex order
    uint2 inv;               // 1.0 / area (double)
    float3 s; float3 t; float3 q;
    uint3 z; uint3 rgba; uint3 uv; uint3 fog;
    uint3 pad;               // x: 0 (g_unfuse); y: TF_* flags; z: float(inv) bits
};
StructuredBuffer<GpuTri> g_tris : register(t4);

// GpuTri.pad.y (gpu_core.cpp, keep in sync)
#define TF_SMALL 1u    // 32-bit edge functions are exact over every pixel drawn
#define TF_CRGBA 2u    // RGBA equal at the three vertices (flat shading: always)
#define TF_CZ 4u
#define TF_CFOG 8u
#define TF_CS 16u
#define TF_CT 32u
#define TF_CQ 64u
#define TF_CU 128u
#define TF_CV 256u

#define FU (1.0 / 8388608.0)   // 2^-23: one float ulp, relative

static bool g_ex = false;
static uint g_ti;              // the triangle (g_tris index)
static int g_e1, g_e2;         // edge functions w1 and w2 come from are nonzero (lerp3f)
static int2 g_n1, g_n2;        // TF_SMALL: e * SCALE = SCALE * n + d as (n, d), exact integers
static bool g_wdone = false;   // g_w1d/g_w2d computed
static double g_w1d, g_w2d;    // the reference's w1, w2
static float g_w1f, g_w2f;     // float w1, w2 (relative error <= g_kw)
static float g_kw;
static bool g_qdone = false;   // g_qd computed
static double g_qd;            // the reference's Q
static float g_euf, g_evf;     // texel coordinates of this pixel (before LOD scaling) in float ...
static float g_eue, g_eve;     // ... within this distance of the double (< 0: unknown)

// int -> double through utod.  WARP's itod is wrong on an integer that came
// out of dtoi: (double)(int)100.92 compared != 100.0, so floor_d returned
// 101 for 100.92 (Gouraud slivers one step off on WARP, scene.formats and
// scene.offscreen); utod of the same register is right.  Exact for every int.
double i2d(int t) { return (double)((uint)t ^ 0x80000000u) - 2147483648.0; }

// floor of a double; correct whether dtoi truncates (the spec) or rounds
// to nearest (WARP turns 39.99999999999997 into 40)
int floor_d(double x)
{
    int t = (int)x;
    if (i2d(t) > x) t -= 1;
    else if (i2d(t + 1) <= x) t += 1;
    return t;
}
uint ufloor_d(double x)      // 0 <= x < 2^32
{
    uint t = (uint)x;
    if ((double)t > x) t -= 1;
    else if (t != 0xFFFFFFFFu && (double)(t + 1) <= x) t += 1;
    return t;
}

// The reference rounds every product before the sum.  The NVIDIA driver
// contracts dmul + dadd into a fused multiply-add even for `precise` DXBC
// (one rounding: 83.0 where the reference has 82.99999999999997 and
// truncates to 82), so each product goes through a max() with a bound no
// product reaches, which no compiler can fuse across.  The bound is read
// from the triangle record so that no optimiser can fold the max() away.
static double g_unfuse;
double unfused(double p) { return max(p, g_unfuse); }

double lerp3d(double a, double b, double c, double w1, double w2)
{
    precise double r = a + unfused((b - a) * w1);
    precise double o = r + unfused((c - a) * w2);
    return o;
}

// gs_raster.c topleft(a, b): dy < 0 || (dy == 0 && dx > 0)
bool tl_edge(int ax, int ay, int bx, int by)
{
    int dx = bx - ax, dy = by - ay;
    return dy < 0 || (dy == 0 && dx > 0);
}

// ---- the float path ----
// The reference's w1, w2 for this pixel (double), on demand.
// int -> double without the dadd of i2d: the magnitude through utod (right on
// WARP too), the sign as a negation
double i2d_s(int t)
{
    double d = (double)(uint)abs(t);
    return t < 0 ? -d : d;
}

void need_wd()
{
    if (g_wdone) return;
    GpuTri T = g_tris[g_ti];
    double inv = asdouble(T.inv.x, T.inv.y);
    uint s = SCALE;
    precise double a = (i2d_s(g_n1.x) * i2d_s((int)s) + i2d_s(g_n1.y)) * inv;   // e * s exactly, times inv
    precise double b = (i2d_s(g_n2.x) * i2d_s((int)s) + i2d_s(g_n2.y)) * inv;
    if (s > 1) {
        double rs = 1.0 / i2d((int)s);
        a = a * rs;
        b = b * rs;
    }
    g_w1d = a;
    g_w2d = b;
    g_wdone = true;
}

// a + (b-a)*w1 + (c-a)*w2 in float, and E >= its distance to the reference's
// double.  kp: relative error bound of the float products (w's error and the
// product's rounding, plus the subtraction's for float attributes).  Each
// float operation is assumed faithful (error < 1 ulp of its result).  The
// sums' rounding errors are bounded by min(ulp-relative, the smaller
// operand), so an attribute whose products are 0 is exact (E = 0).
float lerp3f(float a, float b, float c, float kp, out float E)
{
    precise float d1 = b - a;
    precise float d2 = c - a;
    precise float p1 = d1 * g_w1f;
    precise float p2 = d2 * g_w2f;
    precise float r = a + p1;
    precise float o = r + p2;
    float ap1 = abs(p1), ap2 = abs(p2);
    precise float e = kp * (ap1 + ap2) + min((1.02 * FU) * abs(r), 2.01 * ap1) +
                      min((1.02 * FU) * abs(o), 2.01 * ap2);
    if (ap1 + ap2 > 0.0) e = e * 1.002 + 1.0e-36;
    // a difference or a product that float flushed to zero (denormal)
    // while the reference's is not
    if ((d1 == 0.0 && a != b) || (d2 == 0.0 && a != c) || (p1 == 0.0 && d1 != 0.0 && g_e1 != 0) ||
        (p2 == 0.0 && d2 != 0.0 && g_e2 != 0))
        e = 1.0e30;
    E = e;
    return o;
}

// floor(x) when every value within E of x has the same floor (the
// reference's double lies within E of x).  frac and gap are exact
// (Sterbenz) wherever they can be close to E < 0.25.  The minimum gap keeps
// clear of the reference's (u - floor(u)) * 16 rounding up to 16 just below
// an integer (gs_tex.c sample_level).
bool decide(float x, float E, out int n)
{
    float f = floor(x);
    n = (int)f;
    if (E == 0.0 || FAULT == 12) return true;   // FAULT: test control only (gpu.control_floatpath)
    precise float frac = x - f;
    precise float gap = (f + 1.0) - x;
    return E < 0.25 && frac > E && gap > max(E, 1.0e-12);
}

// The reference's a + (b-a)*w1 + (c-a)*w2 for integer vertex values below
// 2^31 (colour, fog, UV): the differences are exact integers.
double lerp_int_d(uint3 v)
{
    need_wd();
    double a = (double)v.x, d1 = i2d_s((int)(v.y - v.x)), d2 = i2d_s((int)(v.z - v.x));
    precise double r = a + unfused(d1 * g_w1d);
    precise double o = r + unfused(d2 * g_w2d);
    return o;
}

// floor(y * m) where y is the reference's integer lerp and the float x
// (within E < 0.25 of y * m) leaves B - 1 or B (B = round(x)): one double
// comparison.  m is a power of two, B / m is exact in float.
int floor_choice(uint3 v, float x, float E, float m)
{
    if (!(E < 0.25)) return floor_d(lerp_int_d(v) * (double)m);
    int B = (int)floor(x + 0.5);
    return lerp_int_d(v) < (double)((float)B / m) ? B - 1 : B;
}

// The reference's Q (double), on demand.
double need_qd()
{
    if (!g_qdone) {
        GpuTri T = g_tris[g_ti];
        need_wd();
        g_qd = (T.pad.y & TF_CQ) ? (double)T.q.x : lerp3d((double)T.q.x, (double)T.q.y, (double)T.q.z, g_w1d, g_w2d);
        g_qdone = true;
    }
    return g_qd;
}

// One texel coordinate of the reference (ax 0: u, 1: v) in double, before
// the LOD scaling (gs_raster.c pixel: UV / 16, or S/Q and T/Q times the
// texture size), on demand.
static uint g_axdone = 0;
// two scalars, not an array: a dynamically indexed array is an indexable
// temp (local memory) in DXBC
static double g_axd0, g_axd1;
double axis_d(uint ax)
{
    if (!((g_axdone >> ax) & 1)) {
        GpuTri T = g_tris[g_ti];
        need_wd();
        double r;
        if (FLAGS & F_FST) {
            uint3 c = ax ? (T.uv >> 16) : (T.uv & 0xFFFF);
            r = lerp3d((double)c.x, (double)c.y, (double)c.z, g_w1d, g_w2d) * 0.0625;   // exact /16
        } else {
            float3 a = ax ? T.t : T.s;
            double sd = lerp3d((double)a.x, (double)a.y, (double)a.z, g_w1d, g_w2d);
            double qd = need_qd();
            double qq = qd == 0.0 ? 1.0e-30L : qd;
            uint sz = ax ? min((D[4].y >> 4) & 15, 10) : min(D[4].y & 15, 10);
            r = sd / qq * i2d((int)(1u << sz));
        }
        if (ax) g_axd1 = r;
        else g_axd0 = r;
        g_axdone |= 1u << ax;
    }
    return ax ? g_axd1 : g_axd0;
}

// The texel and its 4-bit bilinear weight on each axis for every level the
// sample reads (tex_levels), computed once per pixel in exact_eval and read
// by sample_level / sample_direct through exact_axis.
static uint g_k0 = 0;
// [2 * (level - g_k0) + axis] = (texel, weight); four scalars (no indexable temp)
static int2 g_tc0, g_tc1, g_tc2, g_tc3;

// The LOD depends on Q (gs_tex.c gs_tex_sample with this TEX1): it picks a
// mip level or between the MMAG and MMIN filters.  With the enhancements
// (filter override, anisotropy) on, assume it does.
bool lod_needed()
{
    if (ENH != 0) return true;
    uint lcm = (D[4].w >> 11) & 1, mxl = min((D[4].w >> 8) & 7, 6), mmag = (D[4].w >> 4) & 1,
         mmin = (D[4].w >> 5) & 7;
    uint lin_min = (mmin == 1 || mmin == 4 || mmin == 5) ? 1u : 0u;
    return !lcm && !(mxl == 0 && lin_min == mmag);
}

// Coverage and w1, w2 in double, as the reference (lines, and triangles too
// large for 32-bit edge functions); the attributes then take the float path
// with the float of these w (one rounding: g_kw).
void exact_w_d(VSOut i, GpuTri T)
{
    uint s = SCALE;
    uint2 P = uint2(i.pos.xy);
    double X, Y;
    if (s == 1) {
        X = i2d((int)P.x) * 16.0;
        Y = i2d((int)P.y) * 16.0;
    } else {
        // the sub-sample's GS position: p - 0.5 + (k + 0.5) / scale
        X = ((i2d((int)P.x) + 0.5) / i2d((int)s) - 0.5) * 16.0;
        Y = ((i2d((int)P.y) + 0.5) / i2d((int)s) - 0.5) * 16.0;
    }
    double x0 = i2d(T.x.x), x1 = i2d(T.x.y), x2 = i2d(T.x.z);
    double y0 = i2d(T.y.x), y1 = i2d(T.y.y), y2 = i2d(T.y.z);
    precise double w1, w2;
    if (i.vflags & 4) {
        // line (draw_line): t = (16p - a0) / da along the major axis of the
        // native pixel (lines stay one native pixel wide); a + (b-a)*t is
        // lerp3d with w2 = 0 and c = a
        bool xm = (i.vflags & 8) != 0;
        uint2 np = P / s;
        double a0 = xm ? x0 : y0, da = xm ? x1 - x0 : y1 - y0;
        w1 = (i2d((int)(xm ? np.x : np.y)) * 16.0 - a0) / da;
        w2 = 0.0;
    } else {
        precise double e1 = (x0 - x2) * (Y - y2) - (y0 - y2) * (X - x2);
        precise double e2 = (x1 - x0) * (Y - y0) - (y1 - y0) * (X - x0);
        precise double e0 = (x2 - x1) * (Y - y1) - (y2 - y1) * (X - x1);
        // Coverage is decided here, not by the rasterizer: the triangle is
        // drawn as its bounding box (gpu_core.cpp).  The reference's rule:
        // e + bias >= 0 with bias 0 on a top-left edge, -1 otherwise; for
        // the integer edge values of scale 1 (and the sub-samples of x2/x4)
        // that is e > 0 || (e == 0 && top-left).  The values are exact
        // (products of 17-bit integers, sums below 2^53).
        int3 X3 = T.x, Y3 = T.y;
        bool t0 = tl_edge(X3.y, Y3.y, X3.z, Y3.z), t1 = tl_edge(X3.z, Y3.z, X3.x, Y3.x),
             t2 = tl_edge(X3.x, Y3.x, X3.y, Y3.y);
        if (!(e0 > 0.0 || (e0 == 0.0 && t0)) || !(e1 > 0.0 || (e1 == 0.0 && t1)) ||
            !(e2 > 0.0 || (e2 == 0.0 && t2)))
            discard;
        double inv = asdouble(T.inv.x, T.inv.y);
        w1 = e1 * inv;
        w2 = e2 * inv;
    }
    g_w1d = w1;
    g_w2d = w2;
    g_wdone = true;
    g_e1 = w1 != 0.0 ? 1 : 0;   // (lerp3f: a zero product is the reference's too)
    g_e2 = w2 != 0.0 ? 1 : 0;
    g_w1f = (float)w1;
    g_w2f = (float)w2;
    g_kw = 1.1 * FU;
}

// col: RGBA (truncated, clamped), z: the reference's uint32 Z, fog, q (float, LOD only)
void exact_eval(VSOut i, out uint4 col, out uint zo, out uint fogo, out float qf)
{
    g_ti = (uint)i.sprc.x;
    GpuTri T = g_tris[g_ti];
    g_unfuse = -1.0e300L - (double)T.pad.x;   /* pad.x = 0 */
    uint tf = T.pad.y;
    uint s = SCALE;
    g_ex = true;
    g_wdone = false;
    g_qdone = false;
    g_axdone = 0;
    if ((i.vflags & 4) || !(tf & TF_SMALL)) {
        exact_w_d(i, T);
    } else {
        // 32-bit edge functions (TF_SMALL: every coordinate difference
        // below 2^15, so each product is below 2^30).  At scale s the
        // sub-sample's GS position is X = 16p + dx/s (p the native pixel,
        // dx = 16k + 8 - 8s for sub-sample k), so e * s = s * n + d with n
        // the native pixel's edge function and d = C1 * dy - C2 * dx (below
        // 2^22): exact, and so is the decision e = 0 (top-left rule).
        uint2 P = uint2(i.pos.xy);
        uint2 np = P / s, kk = P - np * s;
        int X = (int)np.x * 16, Y = (int)np.y * 16;
        int dx = 16 * (int)kk.x + 8 - 8 * (int)s, dy = 16 * (int)kk.y + 8 - 8 * (int)s;
        int3 cx = int3(T.x.z - T.x.y, T.x.x - T.x.z, T.x.y - T.x.x);   // edges 0, 1, 2
        int3 cy = int3(T.y.z - T.y.y, T.y.x - T.y.z, T.y.y - T.y.x);
        int3 bx = int3(T.x.y, T.x.z, T.x.x), by = int3(T.y.y, T.y.z, T.y.x);   // each edge's start
        int3 n = cx * (Y - by) - cy * (X - bx);
        int3 d = cx * dy - cy * dx;
        bool3 big = abs(n) >= (1 << 22);                 // then |s n| > |d|: the sign is n's
        int3 es = big ? int3(0, 0, 0) : n * (int)s + d;  // exact otherwise
        bool3 pos = big ? (n > 0) : (es > 0), zero = big ? bool3(false, false, false) : (es == 0);
        bool t0 = tl_edge(T.x.y, T.y.y, T.x.z, T.y.z), t1 = tl_edge(T.x.z, T.y.z, T.x.x, T.y.x),
             t2 = tl_edge(T.x.x, T.y.x, T.x.y, T.y.y);
        if (!(pos.x || (zero.x && t0)) || !(pos.y || (zero.y && t1)) || !(pos.z || (zero.z && t2)))
            discard;
        g_n1 = int2(n.y, d.y);
        g_n2 = int2(n.z, d.z);
        g_e1 = big.y || es.y != 0 ? 1 : 0;
        g_e2 = big.z || es.z != 0 ? 1 : 0;
        float invf = asfloat(T.pad.z);
        float3 ef = big ? (float3)n * (float)s + (float3)d : (float3)es;
        if (s > 1) invf = invf / (float)s;
        g_w1f = ef.y * invf;
        g_w2f = ef.z * invf;
        // w's relative error: e (float of an exact integer, or of s * n + d
        // with |s n| > (s - 1) |d|) and inv rounded to float, the product
        // (and the division by the scale); faithful operations
        g_kw = (s > 1 ? 8.1 : 2.6) * FU;
    }
    {
        float kpi = g_kw + 1.05 * FU;     // integer attributes: exact differences
        float kpf = g_kw + 2.05 * FU;     // float attributes: the difference rounds too
        // colour and fog: (int) then clamp of the lerp (one loop, so the
        // double fallback exists once in the shader)
        col = uint4(T.rgba.x & 255, (T.rgba.x >> 8) & 255, (T.rgba.x >> 16) & 255, T.rgba.x >> 24);
        fogo = T.fog.x;
        uint kb = (tf & TF_CRGBA) ? 4u : 0u, ke = ((FLAGS & F_FGE) && !(tf & TF_CFOG)) ? 5u : 4u;
        [loop] for (uint k = kb; k < ke; k++) {
            uint3 v3 = k < 4 ? (T.rgba >> (8 * k)) & 255 : T.fog;
            float E;
            float o = lerp3f((float)v3.x, (float)v3.y, (float)v3.z, kpi, E);
            int n;
            if (!decide(o, E, n)) n = floor_choice(v3, o, E, 1.0);
            uint c = (uint)clamp(n, 0, 255);
            if (k == 4) fogo = c;
            else col = k == 0 ? uint4(c, col.yzw) : (k == 1 ? uint4(col.x, c, col.zw)
                     : (k == 2 ? uint4(col.xy, c, col.w) : uint4(col.xyz, c)));
        }
        zo = 0;
        qf = 0.0;
        if (!(FLAGS & F_NOZ)) {
            int zn = 0;
            float zE = 1.0;
            if (tf & TF_CZ) {
                zo = T.z.x;
            } else if (max(T.z.x, max(T.z.y, T.z.z)) < (1u << 24) &&
                       decide(lerp3f((float)T.z.x, (float)T.z.y, (float)T.z.z, kpi, zE), zE, zn)) {
                zo = (uint)max(zn, 0);   // Z below 2^24: exact in float, decided there
            } else {
                need_wd();
                double zd = lerp3d((double)T.z.x, (double)T.z.y, (double)T.z.z, g_w1d, g_w2d);
                zo = ufloor_d(zd < 0.0 ? 0.0 : (zd > 4294967295.0 ? 4294967295.0 : zd));
            }
        }
        g_euf = 0.0;
        g_evf = 0.0;
        g_eue = 0.0;
        g_eve = 0.0;
        if (FLAGS & F_TME) {
            if (FLAGS & F_FST) {
                float eu = 0.0, ev = 0.0;
                float uu = (tf & TF_CU) ? (float)(T.uv.x & 0xFFFF)
                                        : lerp3f((float)(T.uv.x & 0xFFFF), (float)(T.uv.y & 0xFFFF),
                                                 (float)(T.uv.z & 0xFFFF), kpi, eu);
                float vv = (tf & TF_CV) ? (float)(T.uv.x >> 16)
                                        : lerp3f((float)(T.uv.x >> 16), (float)(T.uv.y >> 16), (float)(T.uv.z >> 16),
                                                 kpi, ev);
                g_euf = uu / 16.0;
                g_evf = vv / 16.0;
                g_eue = eu / 16.0;
                g_eve = ev / 16.0;
                qf = lod_needed() ? (float)need_qd() : T.q.x;
            } else {
                uint tw = min(D[4].y & 15, 10), th = min((D[4].y >> 4) & 15, 10);
                float es = 0.0, et = 0.0, eq = 0.0;
                float ss = (tf & TF_CS) ? T.s.x : lerp3f(T.s.x, T.s.y, T.s.z, kpf, es);
                float tt = (tf & TF_CT) ? T.t.x : lerp3f(T.t.x, T.t.y, T.t.z, kpf, et);
                float qq;
                if (tf & TF_CQ) {
                    qq = T.q.x;
                    qf = qq;
                } else if (lod_needed()) {
                    // the LOD needs the double's own float rounding
                    qq = (float)need_qd();
                    qf = qq;
                    eq = abs(qq) * FU + 1.0e-37;
                } else {
                    qq = lerp3f(T.q.x, T.q.y, T.q.z, kpf, eq);
                    qf = qq;
                }
                float aq = abs(qq);
                if (aq > 2.0 * eq && aq > 1.0e-30) {
                    // S/Q: |S/Q - Sd/Qd| <= (ES |Q| + |S| EQ) / (|Q| (|Q| - EQ)),
                    // plus the float division (2.5 ulp in D3D11) and the
                    // reference's own rounding
                    precise float ru = ss / qq;
                    precise float rv = tt / qq;
                    precise float den = aq * (aq - eq);
                    precise float eru = (es * aq + abs(ss) * eq) / den + (3.0 * FU) * abs(ru);
                    precise float erv = (et * aq + abs(tt) * eq) / den + (3.0 * FU) * abs(rv);
                    float W = (float)(1u << tw), H = (float)(1u << th);
                    g_euf = ru * W;
                    g_evf = rv * H;
                    g_eue = (eru * 1.002 + abs(ru) * 1.0e-14) * W;
                    g_eve = (erv * 1.002 + abs(rv) * 1.0e-14) * H;
                } else {
                    g_eue = -1.0;   // Q about 0: double
                    g_eve = -1.0;
                }
            }
            if (!(g_eue >= 0.0)) g_euf = (float)axis_d(0);
            if (!(g_eve >= 0.0)) g_evf = (float)axis_d(1);
        }
    }
    if (!(FLAGS & F_TME)) return;
    // The texel and its 4-bit weight on each axis at every level the sample
    // reads: the float value when every number within its bound gives the
    // same texel and weight, else the reference's double.  Bilinear:
    // floor(16x - 8) = floor(16x) - 8 gives both the texel (>> 4) and the
    // weight (& 15), as the reference's x - 0.5, floor and (x - floor(x)) *
    // 16 do in double.  One loop, so the double fallback exists once.
    {
        uint k0, nlev;
        bool lin;
        int fw;
        tex_levels(tex_lod(qf), k0, nlev, lin, fw);
        bool direct = (DIRECT & 1) != 0;
        g_k0 = direct ? 0u : k0;
        uint nj = direct ? 2u : 2u * nlev;
        [loop] for (uint j = 0; j < nj; j++) {
            uint ax = j & 1, k = g_k0 + (j >> 1);
            float f = direct ? (float)s : 1.0 / (float)(1u << k);   // exact
            bool pow2 = !direct || (s & (s - 1)) == 0;
            float c = ax ? g_evf : g_euf, e = ax ? g_eve : g_eue;
            int ic = 0, fc = 0, n;
            bool ok = false;
            if (e >= 0.0) {
                precise float x = c * f;
                precise float E = e * f;
                if (!pow2) E = E * 1.001 + abs(x) * (1.01 * FU);   // the product's rounding (float and double)
                if (decide(lin ? x * 16.0 : x, lin ? E * 16.0 : E, n)) {
                    ok = true;
                    if (lin) {
                        n -= 8;
                        ic = n >> 4;
                        fc = n & 15;
                    } else {
                        ic = n;
                    }
                }
            }
            if (!ok && (FLAGS & F_FST) && pow2 && e >= 0.0) {
                // UV: 16x = U * f exactly (U the lerp in 1/16 texels), and the
                // reference's x - 0.5, floor, * 16 is floor(16x) - 8 exactly
                // (no double lies just below an integer there): choose
                // between the two integers the float value leaves
                GpuTri T = g_tris[g_ti];
                uint3 v3 = ax ? (T.uv >> 16) : (T.uv & 0xFFFF);
                float m = lin ? f : f * 0.0625;   // floor(16x) or floor(x), x = U / 16 * f
                precise float xm = c * 16.0 * m;
                precise float Em = e * 16.0 * m;
                n = floor_choice(v3, xm, Em, m);
                if (lin) {
                    n -= 8;
                    ic = n >> 4;
                    fc = n & 15;
                } else {
                    ic = n;
                }
                ok = true;
            }
            if (!ok) {
                double xd = axis_d(ax) * (double)f;
                if (!lin) {
                    ic = floor_d(xd);
                } else {
                    xd -= 0.5;
                    ic = floor_d(xd);
                    fc = floor_d((xd - i2d(ic)) * 16.0);
                }
            }
            int2 tcv = int2(ic, fc);
            if (j == 0) g_tc0 = tcv;
            else if (j == 1) g_tc1 = tcv;
            else if (j == 2) g_tc2 = tcv;
            else g_tc3 = tcv;
        }
    }
    // Texel-space gradients per target pixel, for anisotropic filtering
    // only (an enhancement; never used by the Original pipeline).
    // dw/dX from the edge functions, X in 1/16 GS pixels, 16/scale per pixel.
    bool want_grad = (ENH >> 4) & 31;
    if (want_grad && !(i.vflags & 4)) {
        float inv_f = (float)asdouble(T.inv.x, T.inv.y) * 16.0 / (float)s;
        float2 dw1 = float2(-(float)(T.y.x - T.y.z), (float)(T.x.x - T.x.z)) * inv_f;
        float2 dw2 = float2(-(float)(T.y.y - T.y.x), (float)(T.x.y - T.x.x)) * inv_f;
        g_grad_ok = true;
        if (FLAGS & F_FST) {
            float3 U = float3(T.uv & 0xFFFF) / 16.0, V = float3(T.uv >> 16) / 16.0;
            float2 du = (U.y - U.x) * dw1 + (U.z - U.x) * dw2;
            float2 dv = (V.y - V.x) * dw1 + (V.z - V.x) * dw2;
            g_grad = float4(du.x, dv.x, du.y, dv.y);
        } else {
            uint tw = min(D[4].y & 15, 10), th = min((D[4].y >> 4) & 15, 10);
            float Qf = qf == 0.0 ? 1.0e-30 : qf;
            float S = g_euf * Qf / (float)(1u << tw), Tt = g_evf * Qf / (float)(1u << th);
            float2 dS = (T.s.y - T.s.x) * dw1 + (T.s.z - T.s.x) * dw2;
            float2 dT = (T.t.y - T.t.x) * dw1 + (T.t.z - T.t.x) * dw2;
            float2 dQ = (T.q.y - T.q.x) * dw1 + (T.q.z - T.q.x) * dw2;
            float2 du = (dS * Qf - S * dQ) / (Qf * Qf) * (float)(1u << tw);
            float2 dv = (dT * Qf - Tt * dQ) / (Qf * Qf) * (float)(1u << th);
            g_grad = float4(du.x, dv.x, du.y, dv.y);
        }
    }
}

// sample_level / sample_direct: the texel and weight exact_eval decided for
// this level and axis
void exact_axis(uint ax, uint k, out int ic, out int fc)
{
    uint ti = min(2 * (k - g_k0) + ax, 3u);
    int2 t = ti == 0 ? g_tc0 : (ti == 1 ? g_tc1 : (ti == 2 ? g_tc2 : g_tc3));
    ic = t.x;
    fc = t.y;
}
#endif

// ---------------------------------------------------------------- texturing
uint clut_cell(uint i)
{
    i &= 511;
    uint w = g_clut[i >> 1];
    return (i & 1) ? (w >> 16) : (w & 0xFFFF);
}
uint4 expand16(uint c)
{
    uint ta0 = D[6].y, ta1 = D[6].z, aem = D[6].w;
    uint a;
    if (c & 0x8000) a = ta1;
    else a = (aem && (c & 0x7FFF) == 0) ? 0 : ta0;
    return uint4((c & 31) << 3, ((c >> 5) & 31) << 3, ((c >> 10) & 31) << 3, a);
}
uint4 expand24(uint c)
{
    uint ta0 = D[6].y, aem = D[6].w;
    c &= 0xFFFFFF;
    return uint4(c & 255, (c >> 8) & 255, (c >> 16) & 255, (aem && c == 0) ? 0 : ta0);
}
uint4 unpack32(uint c) { return uint4(c & 255, (c >> 8) & 255, (c >> 16) & 255, c >> 24); }

uint2 level_geom(uint k)
{
    uint4 s = D[7 + (k >> 1)];
    return (k & 1) ? s.zw : s.xy;
}

uint4 tex_fetch(uint k, int x, int y)
{
#ifndef GS_DECODE
    if ((DIRECT & 4) && k == 0) {
        uint4 dr = uint4(D[10].z & 0xFFFF, D[10].z >> 16, D[10].w & 0xFFFF, D[10].w >> 16);
        if (x >= (int)dr.x && y >= (int)dr.y && x < (int)dr.z && y < (int)dr.w)
            return unpack32(g_dec.Load(int3(x - (int)dr.x, y - (int)dr.y, 0)));
    }
#endif
    uint psm = D[4].x;
    uint2 g = level_geom(k);
    uint raw = gs_read_pixel(psm, g.x, g.y, (uint)x, (uint)y);
    switch (psm) {
    case PSMCT32: case PSMZ32: return unpack32(raw);
    case PSMCT24: case PSMZ24: return expand24(raw);
    case PSMCT16: case PSMCT16S: case PSMZ16: case PSMZ16S: return expand16(raw);
    default: break;
    }
    uint cpsm = D[4].z & 15, csa = (D[4].z >> 4) & 31;
    if (cpsm == PSMCT32 || cpsm == PSMCT24) {
        uint e = ((csa & 15) * 16 + raw) & 255;
        uint c = clut_cell(e) | (clut_cell(e + 256) << 16);
        return cpsm == PSMCT24 ? expand24(c) : unpack32(c);
    }
    return expand16(clut_cell(csa * 16 + raw));
}

int wrapc(int c, uint mode, int size, int mn, int mx)
{
    switch (mode) {
    case 0: return c & (size - 1);
    case 1: return clamp(c, 0, size - 1);
    case 2: return clamp(c, mn, mx);
    default: return (c & mn) | mx;
    }
}

// One mip level, point or bilinear.  Written as a loop over the taps so the
// compiler inlines a single texel fetch (an unrolled 4-tap x 2-level version
// takes fxc minutes to optimise).
uint4 sample_level(uint k, bool lin_, float u, float v)
{
    uint tw = min(D[4].y & 15, 10), th = min((D[4].y >> 4) & 15, 10);
    uint lw = tw >= k ? tw - k : 0, lh = th >= k ? th - k : 0;
    int W = 1 << lw, H = 1 << lh;
    uint wms = D[4].w & 3, wmt = (D[4].w >> 2) & 3;
    int minu = (int)D[5].x, maxu = (int)D[5].y, minv = (int)D[5].z, maxv = (int)D[5].w;
    if (k > 0 && wms == 2) { minu >>= k; maxu >>= k; }
    if (k > 0 && wmt == 2) { minv >>= k; maxv >>= k; }
    float sc = 1.0 / (float)(1u << k);
    u *= sc; v *= sc;
    int iu, iv, fu, fv, ntap;
    if (!lin_) {
        iu = (int)floor(u); iv = (int)floor(v);
        fu = 0; fv = 0; ntap = 1;
    } else {
        u -= 0.5; v -= 0.5;
        float fu0 = floor(u), fv0 = floor(v);
        iu = (int)fu0; iv = (int)fv0;
        fu = (int)((u - fu0) * 16.0); fv = (int)((v - fv0) * 16.0);
        ntap = 4;
    }
#ifdef GS_EXACT
    if (g_ex && !g_noexact) {
        exact_axis(0, k, iu, fu);
        exact_axis(1, k, iv, fv);
    }
#endif
#ifndef GS_DECODE
    // Bilinear on the decoded level-0 texels when the 2x2 block is
    // contiguous after wrapping and inside the decoded rect: the same four
    // texels and weights as the loop below (tex_fetch reads them from the
    // decoded copy there too), with one bounds test instead of one per tap
    // (docs/PERF-3D.md).
    if (ntap == 4 && k == 0 && (DIRECT & 4)) {
        int x0 = wrapc(iu, wms, W, minu, maxu), x1 = wrapc(iu + 1, wms, W, minu, maxu);
        int y0 = wrapc(iv, wmt, H, minv, maxv), y1 = wrapc(iv + 1, wmt, H, minv, maxv);
        int4 dr = int4(D[10].z & 0xFFFF, D[10].z >> 16, D[10].w & 0xFFFF, D[10].w >> 16);
        if (x1 == x0 + 1 && y1 == y0 + 1 && x0 >= dr.x && y0 >= dr.y && x1 < dr.z && y1 < dr.w) {
            // four Loads (a Gather through a sampler selected other texels
            // on WARP; Loads are exact on every device)
            int2 lp = int2(x0 - dr.x, y0 - dr.y);
            uint4 q = uint4(g_dec.Load(int3(lp + int2(0, 1), 0)), g_dec.Load(int3(lp + int2(1, 1), 0)),
                            g_dec.Load(int3(lp + int2(1, 0), 0)), g_dec.Load(int3(lp, 0)));
            int4 a4 = (int4)unpack32(q.w) * ((16 - fu) * (16 - fv)) + (int4)unpack32(q.z) * (fu * (16 - fv)) +
                      (int4)unpack32(q.x) * ((16 - fu) * fv) + (int4)unpack32(q.y) * (fu * fv);
            return (uint4)(a4 >> 8);
        }
    }
#endif
    int4 acc = int4(0, 0, 0, 0);
    [loop] for (int tap = 0; tap < ntap; tap++) {
        int dx = tap & 1, dy = tap >> 1;
        int x = wrapc(iu + dx, wms, W, minu, maxu);
        int y = wrapc(iv + dy, wmt, H, minv, maxv);
        int wgt = (dx ? fu : 16 - fu) * (dy ? fv : 16 - fv);
        acc += (int4)tex_fetch(k, x, y) * wgt;
    }
    return (uint4)(acc >> 8);
}

// ---- direct sampling of a render target (level 0, no CLUT) ----
// Texel j of the upscaled target (j = native texel * scale + sub-sample)
// holds the stored value of its native texel as the target keeps it: RGBA8
// for colour (to_stored gives the raw bits back exactly), z / 2^32 for depth
// (exact for Z24/Z16).  Decoded per the texture PSM like tex_fetch.
uint4 fetch_direct(int jx, int jy)
{
    uint di = DIRECT;
    uint raw;
    {
        /* the read set's bilinear margin may reach a texel or two past the target (its last
         * rows/columns owned): those taps read its edge, not the texture's spare rows */
        uint nw = (di >> 16) & 63, nh = (di >> 22) & 127;
        int s = (int)SCALE;
        if (nw) jx = clamp(jx, 0, (int)nw * 64 * s - 1);
        if (nh) jy = clamp(jy, 0, (int)nh * 32 * s - 1);
    }
    if (di & 2) {
        raw = (uint)(g_texz.Load(int3(jx, jy, 0)) * 4294967296.0);
    } else {
        uint4 c = (uint4)round(g_texc.Load(int3(jx, jy, 0)) * 255.0);
        raw = to_stored((di >> 8) & 255, c);
    }
    switch (D[4].x) {
    case PSMCT32: return unpack32(raw);
    case PSMCT24: case PSMZ24: return expand24(raw);
    default: return expand16(raw);
    }
}

// Sprites sampled directly at scale > 1 (PS_main): the coordinates of the
// reference's own sample of this pixel.  Point sampling keeps the native
// texel the reference picks and takes the sub-sample of it that lies at
// this sub-sample's offset (so a 1:1 copy on texel corners or centres
// reproduces the source at the internal resolution, and a point-sampled
// pass never reads a texel the reference does not).
static float2 g_unat;
static bool g_anchor;

// The wrap modes of wrapc, in upscaled texels (s per native texel): the
// same native texel range, with the sub-sample kept.  s = 1: wrapc.
int wrap_hr(int j, uint mode, int size, int mn, int mx, int s)
{
    switch (mode) {
    case 0: { int n = size * s; int m = j % n; return m < 0 ? m + n : m; }
    case 1: return clamp(j, 0, size * s - 1);
    case 2: return clamp(j, mn * s, mx * s + s - 1);
    default: {
        int i = j >= 0 ? j / s : -((-j + s - 1) / s);
        return ((i & mn) | mx) * s + (j - i * s);
    }
    }
}

// sample_level(0, ...) on the upscaled target: the native texel coordinate
// u maps to u * scale upscaled texels; point or bilinear (4-bit weights)
// there.  At scale 1 this is exactly sample_level(0, ...).
uint4 sample_direct(bool lin_, float u, float v)
{
    int s = (int)SCALE;
    uint tw = min(D[4].y & 15, 10), th = min((D[4].y >> 4) & 15, 10);
    int W = 1 << tw, H = 1 << th;
    uint wms = D[4].w & 3, wmt = (D[4].w >> 2) & 3;
    int minu = (int)D[5].x, maxu = (int)D[5].y, minv = (int)D[5].z, maxv = (int)D[5].w;
    if (!lin_ && g_anchor) {
        int2 ni = int2(floor(g_unat));
        int2 sub = clamp(int2(floor((float)s * (0.5 + float2(u, v) - g_unat))), 0, s - 1);
        return fetch_direct(wrapc(ni.x, wms, W, minu, maxu) * s + sub.x,
                            wrapc(ni.y, wmt, H, minv, maxv) * s + sub.y);
    }
    u *= (float)s; v *= (float)s;
    int iu, iv, fu, fv, ntap;
    if (!lin_) {
        iu = (int)floor(u); iv = (int)floor(v);
        fu = 0; fv = 0; ntap = 1;
    } else {
        u -= 0.5; v -= 0.5;
        float fu0 = floor(u), fv0 = floor(v);
        iu = (int)fu0; iv = (int)fv0;
        fu = (int)((u - fu0) * 16.0); fv = (int)((v - fv0) * 16.0);
        ntap = 4;
    }
#ifdef GS_EXACT
    if (g_ex) {
        exact_axis(0, 0, iu, fu);
        exact_axis(1, 0, iv, fv);
    }
#endif
    int4 acc = int4(0, 0, 0, 0);
    [loop] for (int tap = 0; tap < ntap; tap++) {
        int dx = tap & 1, dy = tap >> 1;
        int x = wrap_hr(iu + dx, wms, W, minu, maxu, s);
        int y = wrap_hr(iv + dy, wmt, H, minv, maxv, s);
        int wgt = (dx ? fu : 16 - fu) * (dy ? fv : 16 - fv);
        acc += (int4)fetch_direct(x, y) * wgt;
    }
    return (uint4)(acc >> 8);
}

// Anisotropic filtering (an enhancement, docs/GPU.md "Graphics settings"):
// at the GS-chosen level k, taps spread over the pixel's footprint (the
// parallelogram of the texel-space gradients): along the major axis as many
// as its length in level-k texels (capped at the setting), and across the
// minor axis too when that is also longer than a texel (a texture without
// mipmaps, or a GS LOD finer than the footprint), at most 2 x the setting in
// all.  A footprint within one texel (magnified or 1:1) is the plain GS
// sample, so nothing changes where the GS filter does not alias.
uint4 sample_aniso(uint k, bool lin_, float u, float v)
{
    uint maxn = (ENH >> 4) & 31;
    if (!g_enh || !lin_ || maxn < 2 || !g_grad_ok) return sample_level(k, lin_, u, v);
    float2 ax = g_grad.xy, ay = g_grad.zw;
    float lx = length(ax), ly = length(ay);
    float2 maj = lx >= ly ? ax : ay, mnr = lx >= ly ? ay : ax;
    float sc = 1.0 / (float)(1u << k);
    uint n1 = (uint)clamp(ceil(max(lx, ly) * sc - 1.0 / 64.0), 1.0, (float)maxn);
    uint n2 = (uint)clamp(ceil(min(lx, ly) * sc - 1.0 / 64.0), 1.0, (float)max(1u, (2u * maxn) / n1));
    if (n1 * n2 < 2) return sample_level(k, lin_, u, v);
    g_noexact = true;
    int4 acc = int4(0, 0, 0, 0);
    [loop] for (uint j = 0; j < n1 * n2; j++) {
        float t1 = ((float)(j % n1) + 0.5) / (float)n1 - 0.5;
        float t2 = ((float)(j / n1) + 0.5) / (float)n2 - 0.5;
        float2 o = maj * t1 + mnr * t2;
        acc += (int4)sample_level(k, lin_, u + o.x, v + o.y);
    }
    g_noexact = false;
    return (uint4)(acc / (int)(n1 * n2));
}

uint4 tex_sample(float u, float v, float lod)
{
    uint k0, nlev;
    bool lin;
    int f;
    tex_levels(lod, k0, nlev, lin, f);
    // direct sampling is only chosen for states that read level 0 alone
    if (DIRECT & 1) return sample_direct(lin, u, v);
    int4 acc = int4(0, 0, 0, 0);
    [loop] for (uint n = 0; n < nlev; n++) {
        int4 c = (int4)sample_aniso(k0 + n, lin, u, v);
        acc += c * (nlev == 1 ? 16 : (n == 0 ? 16 - f : f));
    }
    return (uint4)(acc >> 4);
}

uint4 tex_function(uint4 t, uint4 c)
{
    uint tfx = (D[4].y >> 9) & 3, tcc = (D[4].y >> 8) & 1;
    int4 ti = (int4)t, ci = (int4)c;
    int4 o;
    switch (tfx) {
    case 0:
        o.rgb = clamp((ti.rgb * ci.rgb) >> 7, 0, 255);
        o.a = tcc ? clamp((ti.a * ci.a) >> 7, 0, 255) : ci.a;
        break;
    case 1:
        o.rgb = ti.rgb;
        o.a = tcc ? ti.a : ci.a;
        break;
    case 2:
        o.rgb = clamp(((ti.rgb * ci.rgb) >> 7) + ci.a, 0, 255);
        o.a = tcc ? clamp(ti.a + ci.a, 0, 255) : ci.a;
        break;
    default:
        o.rgb = clamp(((ti.rgb * ci.rgb) >> 7) + ci.a, 0, 255);
        o.a = tcc ? ti.a : ci.a;
        break;
    }
    return (uint4)o;
}

bool alpha_test(uint atst, uint a, uint ref)
{
    switch (atst) {
    case 0: return false;
    case 1: return true;
    case 2: return a < ref;
    case 3: return a <= ref;
    case 4: return a == ref;
    case 5: return a >= ref;
    case 6: return a > ref;
    default: return a != ref;
    }
}

int dimx_at(uint x, uint y)
{
    uint word = (y & 2) ? D[3].y : D[3].x;
    uint sh = (y & 1) * 16 + (x & 3) * 4;
    int v = (int)((word >> sh) & 7);
    return v >= 4 ? v - 8 : v;
}

struct PSOut {
    float4 c : SV_Target0;
#ifndef GS_ZROV
    float d : SV_Depth;
#endif
};

// floor() for interpolated integer-valued attributes; the small bias keeps
// a value that is constant over the primitive from dropping one step when
// the barycentric weights sum to 1 - ulp.
float fl(float v) { return floor(v + 1.0 / 512.0); }

int floordiv(int a, int b)
{
    int q = a / b;
    if ((a % b) != 0 && ((a < 0) != (b < 0))) q--;
    return q;
}

// Texel coordinates (u, v) of pixel px, at GS offset `off` pixels from it
// (sub-sample positions of direct sampling; 0 = the reference's own).
void tex_coords(VSOut i, uint2 px, float2 off, out float u, out float v)
{
    uint tw = min(D[4].y & 15, 10), th = min((D[4].y >> 4) & 15, 10);
    float q = i.stq.z;
    float s_ = i.stq.x, t_ = i.stq.y, uu = i.uv.x, vv = i.uv.y;
    bool exact_uv = false;
    if (i.vflags & 32) {
        // UV sprite: the reference's fixed-point DDA (gs_sprite_uv_at),
        // U = Shi + Thi*k + ((Slo + Tlo*k) >> 16), k = px - base
        int kx = (int)px.x - (int)i.spra.x, ky = (int)px.y - (int)i.spra.y;
        int U = (int)i.sprb.x + (int)i.sprc.x * kx + (int)(((uint)i.sprb.y + (uint)i.sprc.y * (uint)kx) >> 16);
        int V = (int)i.sprb.z + (int)i.sprc.z * ky + (int)(((uint)i.sprb.w + (uint)i.sprc.w * (uint)ky) >> 16);
        uu = (float)U / 16.0;
        vv = (float)V / 16.0;
        if (off.x != 0.0 || off.y != 0.0) {
            // + step * offset (step: 16.16 in 1/16 texels per pixel)
            uu += ((float)(int)i.sprc.x + i.sprc.y / 65536.0) * off.x / 16.0;
            vv += ((float)(int)i.sprc.z + i.sprc.w / 65536.0) * off.y / 16.0;
        }
        exact_uv = true;
    } else if (i.vflags & 2) {
        // sprite: the reference's formula per pixel instead of an
        // interpolated attribute (exact texel addressing on 2D sprites)
        float fx = i.spra.z > 0 ? (((float)px.x + off.x) * 16.0 - i.spra.x) / i.spra.z : 0.0;
        float fy = i.spra.w > 0 ? (((float)px.y + off.y) * 16.0 - i.spra.y) / i.spra.w : 0.0;
        s_ = i.sprb.x + (i.sprb.y - i.sprb.x) * fx;
        t_ = i.sprb.z + (i.sprb.w - i.sprb.z) * fy;
        uu = (i.sprc.x + (i.sprc.y - i.sprc.x) * fx) / 16.0;
        vv = (i.sprc.z + (i.sprc.w - i.sprc.z) * fy) / 16.0;
    }
    if (FLAGS & F_FST) {
        u = uu; v = vv;
    } else {
        float qq = q == 0.0 ? 1e-30 : q;
        u = s_ / qq * (float)(1u << tw);
        v = t_ / qq * (float)(1u << th);
    }
    // Float interpolation lands a hair below exact texel coordinates the
    // reference computes in double (u = 639.99994 instead of 640): nudge
    // up by a few ulps of |u| before floor/fraction.
    if (!exact_uv) {
        u += max(abs(u), 1.0) * (1.0 / 262144.0);
        v += max(abs(v), 1.0) * (1.0 / 262144.0);
    }
}

PSOut PS_main(VSOut i)
{
    PSOut o;
    uint flags = FLAGS;
    uint scale = SCALE;
    uint2 px = uint2(i.pos.xy) / scale;
    uint scanmsk = (flags >> 12) & 3;
    if (scanmsk == 2 && (px.y & 1)) discard;
    if (scanmsk == 3 && !(px.y & 1)) discard;

    if (i.vflags & 4) {
        // line: keep the reference DDA's minor pixel (exact integer math;
        // spra = a0, b0, da, db in 12.4)
        bool xm = (i.vflags & 8) != 0;
        int p = (int)(xm ? px.x : px.y), q = (int)(xm ? px.y : px.x);
        int a0 = (int)i.spra.x, b0 = (int)i.spra.y, da = (int)i.spra.z, db = (int)i.spra.w;
        int k = floordiv(db * (p * 16 - a0), da);
        if (floordiv(b0 + 8 + k, 16) != q) discard;
    }
    uint4 col = (uint4)clamp(int4(fl(i.col.r), fl(i.col.g), fl(i.col.b), fl(i.col.a)), 0, 255);
    uint ez = 0, efog = 0;
    float eq = 0.0;
    g_enh = (flags & F_TME) && (ENH & 0x1000) != 0 && !(i.vflags & 38) && !(DIRECT & 1);
#ifdef GS_EXACT
    if (i.vflags & 64) exact_eval(i, col, ez, efog, eq);
#endif
    if (flags & F_TME) {
        float q = i.stq.z;
        float u, v;
        tex_coords(i, px, float2(0.0, 0.0), u, v);
#ifdef GS_EXACT
        if (g_ex) { q = eq; u = g_euf; v = g_evf; }
#endif
        // Direct sampling at scale > 1: sprites evaluate the reference's
        // per-pixel UV at the sub-sample's own position (GS x = px - 0.5 +
        // (k + 0.5) / scale), so an upscaled source keeps its detail.
        // Interpolated primitives already are.  Scale 1: no offset.
        g_anchor = false;
        g_unat = float2(u, v);
        if ((DIRECT & 1) && scale > 1 && (i.vflags & 34)) {
            float2 off = ((float2)(uint2(i.pos.xy) - px * scale) + 0.5) / (float)scale - 0.5;
            tex_coords(i, px, off, u, v);
            g_anchor = true;
        }
        uint4 t = tex_sample(u, v, tex_lod(q));
        col = tex_function(t, col);
    }
    if (flags & F_FGE) {
        uint f = (uint)clamp((int)fl(i.fog), 0, 255);
#ifdef GS_EXACT
        if (g_ex) f = efog;
#endif
        uint3 fc = uint3(FOGCOL & 255, (FOGCOL >> 8) & 255, (FOGCOL >> 16) & 255);
        col.rgb = (f * col.rgb + (255 - f) * fc) >> 8;
    }

    uint as = col.a;
    uint atst = (flags >> 14) & 7;
    bool apass = !(flags & F_ATE) || alpha_test(atst, as, AREF);
#ifdef GS_ROV
    // both alpha-test passes in one: the channel mask of this pixel's pass
    uint rcm;
    if (apass) { if (!(ROVCTL & 0x200u)) discard; rcm = ROVCTL & 15u; }
    else { if (!(ROVCTL & 0x100u)) discard; rcm = (ROVCTL >> 4) & 15u; }
#else
    if (flags & F_FAILPASS) { if (apass) discard; }
    else { if (!apass) discard; }
#endif

    uint fpsm = FPSM;
    bool f16 = psm_is16(fpsm);
    uint4 dst = uint4(0, 0, 0, 0);
#ifdef GS_ROV
    uint2 rp = uint2(i.pos.xy);
    uint draw32 = g_rov[rp];
    dst = uint4(draw32 & 255u, (draw32 >> 8) & 255u, (draw32 >> 16) & 255u, draw32 >> 24);
#else
    if (flags & F_NEEDDST)
        dst = (uint4)round(g_dst.Load(int3(i.pos.xy, 0)) * 255.0);
#endif
    if (flags & F_DATE) {
        if (fpsm == PSMCT32 || f16) {
            uint bit = (dst.a >> 7) & 1;
            if (bit != ((flags & F_DATM) ? 1u : 0u)) discard;
        }
    }

    uint z;
#ifdef GS_EXACT
    if (g_ex) {
        z = ez;
    } else
#endif
    if (i.vflags & 1) {
        z = i.zi;
    } else if (i.vflags & 16) {
        // triangle Z plane: z0 + gx * (16*px - x0) + gy * (16*py - y0)
        float zz = i.sprb.x + i.spra.z * ((float)px.x * 16.0 - i.spra.x) +
                   i.spra.w * ((float)px.y * 16.0 - i.spra.y);
        z = (uint)clamp(floor(zz), 0.0, 4294967040.0);
    } else {
        z = (uint)clamp(floor(i.zf), 0.0, 4294967040.0);
    }
    z = min(z, ZMAX);
    float zdepth = (float)z * (1.0 / 4294967296.0);
#ifdef GS_ZROV
    if (!(flags & F_NOZ)) {
        uint2 zp = uint2(i.pos.xy);
        float zd = g_zrov[zp];
        uint zfn = ZCTL & 3u;
        if ((zfn == 2u && !(zdepth >= zd)) || (zfn == 3u && !(zdepth > zd))) discard;
#ifdef GS_ROV
        bool zw = (ZCTL & (apass ? 4u : 8u)) != 0;
#else
        bool zw = (ZCTL & 4u) != 0;
#endif
        if (zw) g_zrov[zp] = zdepth;
    }
#else
    o.d = zdepth;
#endif

    int3 rgb = (int3)col.rgb;
    if ((flags & F_ABE) && !((flags & F_PABE) && !(as & 0x80))) {
        uint abcd = ALPHAABCD;
        uint sa = abcd & 3, sb = (abcd >> 2) & 3, sc = (abcd >> 4) & 3, sd = (abcd >> 6) & 3;
        if (i.vflags & 128u) { uint t = sa; sa = sb; sb = t; }   // native primitive: A and B swapped
        int ad = fpsm == PSMCT24 ? 0x80 : (int)dst.a;
        int cc = sc == 0 ? (int)as : (sc == 1 ? ad : (int)FIX);
        int3 cs = (int3)col.rgb, cd = (int3)dst.rgb;
        int3 A = sa == 0 ? cs : (sa == 1 ? cd : int3(0, 0, 0));
        int3 B = sb == 0 ? cs : (sb == 1 ? cd : int3(0, 0, 0));
        int3 Dd = sd == 0 ? cs : (sd == 1 ? cd : int3(0, 0, 0));
        rgb = (((A - B) * cc) >> (FAULT == 1 ? 6 : 7)) + Dd;   // FAULT: test control only
    }
    if ((flags & F_DTHE) && f16) rgb += dimx_at(px.x, px.y);
    if (flags & F_COLCLAMP) rgb = clamp(rgb, 0, 255);
    else rgb &= 255;
    uint aout = (as | ((flags & F_FBA) ? 0x80u : 0u)) & 255;
    uint4 oc = uint4((uint3)rgb, aout);
    if (flags & F_MERGE) {
        // FBMSK bits that a channel write mask cannot express: merge with the
        // destination in the frame buffer's stored format.
        uint mask = to_stored(fpsm, unpack32(FBMSK));
        uint nraw = to_stored(fpsm, oc), draw = to_stored(fpsm, dst);
        oc = from_stored(fpsm, (draw & mask) | (nraw & ~mask));
    } else if (f16) {
        oc = from_stored(fpsm, to_stored(fpsm, oc));
    }
    if (fpsm == PSMCT24) oc.a = 0;
#ifdef GS_ROV
    // the hardware write mask of the RTV path, then the ordered store
    uint4 keep = uint4(rcm & 1u, (rcm >> 1) & 1u, (rcm >> 2) & 1u, (rcm >> 3) & 1u);
    uint4 res = keep != 0 ? oc : dst;
    g_rov[rp] = res.r | (res.g << 8) | (res.b << 16) | (res.a << 24);
#endif
    o.c = (float4)oc / 255.0;
    return o;
}

#ifdef GS_DECODE
// One texel of the decoded texture per thread: tex_fetch of level 0 over the
// rect in D[10].zw (the batch's DrawCB otherwise; DIRECT is 0 here).
RWTexture2D<uint> g_decout : register(u0);
[numthreads(8, 8, 1)]
void CS_decode(uint3 id : SV_DispatchThreadID)
{
    int x = (int)(D[10].z & 0xFFFF) + (int)id.x, y = (int)(D[10].z >> 16) + (int)id.y;
    if (x >= (int)(D[10].w & 0xFFFF) || y >= (int)(D[10].w >> 16)) return;
    uint4 c = tex_fetch(0, x, y);
    if (FAULT == 7) c.r ^= 1;   // test control only (gpu.control_decode)
    g_decout[id.xy] = c.r | (c.g << 8) | (c.b << 16) | (c.a << 24);
}
#endif
