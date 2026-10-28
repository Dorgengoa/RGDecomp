// SPDX-License-Identifier: CC0-1.0
// Native model pipeline (docs/NATIVE-RENDER.md): the dominant VU1 model
// program's per-vertex math (src/native/render/nr_vu1.c is the reference)
// as a vertex shader over the mesh's raw quantised attributes, and a pixel
// shader with a hardware-sampled decoded texture, the GS texture function,
// fog and alpha test.  Blending, depth and culling are fixed-function state.

cbuffer NrCB : register(b0)
{
    float4 R[24];
};
cbuffer NrBones : register(b1)  // bound for skinned meshes only
{
    float4 B[256];      // VU1 qwords 768..1023: bone matrix rows
};

Texture2D<float4> g_tex : register(t0);
SamplerState g_smp : register(s0);
#ifdef NR_ZROV
// depth targets in rasterizer-ordered views (docs/PERF-3D.md fix 1): the
// emulated path keeps its fast depth-in-ROV mode, so native draws test and
// write Z there too (u2: after SV_Target0 and the dual-source SV_Target1)
RasterizerOrderedTexture2D<float> g_zrov : register(u2);
#define PS_ZCTL asuint(R[23].w)   // bits 0-1 GpuZFunc, bit 4 Z write
#endif

#ifdef NR_CROV
// Immediate primitives the fixed-function output merger cannot draw as the GS does (CT16
// frames, destination alpha test, blend factor Ad, partial FBMSK, AFAIL modes, COLCLAMP off,
// PABE, SCANMSK, dithering): the colour target in a rasterizer-ordered view (u1, as the
// emulated path's PS_main_rov, at u3: GS bytes, R | G << 8 | B << 16 | A << 24) and the GS pixel
// back end in the shader (docs/NATIVE-RENDER.md "Ordered immediate draws", checkpoint 9).
// Row 1 (immediate draws only: rows 0-10 are mesh constants):
//   x flags: CR_*; bits 8-9 AFAIL      y FBMSK      z ALPHA A|B<<2|C<<4|D<<6, FIX << 8, FPSM << 16
// Row 2: xy DIMX (rows 0-1, rows 2-3), z the internal scale
RasterizerOrderedTexture2D<uint> g_crov : register(u3);   // (u0-u1: the outputs, u2: zrov)
#define CR_DATE 1u
#define CR_DATM 2u
#define CR_PABE 4u
#define CR_COLCLAMP 8u
#define CR_DTHE 16u
#define CR_SCAN 32u     // SCANMSK on: bit 6 = the prohibited line parity
#define CR_SCANODD 64u
#define CR_ABE 0x800u
bool nr_is16(uint psm) { return psm == 0x02u || psm == 0x0Au || psm == 0x32u || psm == 0x3Au; }
uint4 nr_from_stored(uint psm, uint raw)
{
    if (nr_is16(psm))
        return uint4((raw & 31u) << 3, ((raw >> 5) & 31u) << 3, ((raw >> 10) & 31u) << 3, (raw & 0x8000u) ? 0x80u : 0u);
    uint4 c = uint4(raw & 255u, (raw >> 8) & 255u, (raw >> 16) & 255u, raw >> 24);
    if (psm == 0x01u || psm == 0x31u) c.a = 0u;
    return c;
}
uint nr_to_stored(uint psm, uint4 c)
{
    if (nr_is16(psm))
        return ((c.r >> 3) & 31u) | (((c.g >> 3) & 31u) << 5) | (((c.b >> 3) & 31u) << 10) | ((c.a >> 7) << 15);
    uint v = c.r | (c.g << 8) | (c.b << 16) | (c.a << 24);
    if (psm == 0x01u || psm == 0x31u) v &= 0xFFFFFFu;
    return v;
}
#endif

// R[22].x (as uint): the program variant (nr_vu1.h NRV_*)
#define NRV_SKIN 1u
#define NRV_UVSCROLL 2u
#define NRV_VCOL 4u
#define NRV_ZSCALE 8u
#define NRV_ENVMAP 64u
#define NRV_LIGHT 128u
#define NRV_REFRACT 1024u
#define NRV_IM 2048u
#define NRV_REFLECT 4096u   // kind 0x43F100 (nr_vu1.c reflect_uv)        // immediate primitives (VS_im; docs/NATIVE-RENDER.md "Immediate packets")
#define VARIANT asuint(R[22].x)

// R[23] (as uint), filled by gpu_core: PS state
#define PS_FLAGS asuint(R[23].x)
#define PF_TME 1u
#define PF_FGE 2u
#define PF_ATE 4u
#define PF_FBA 8u
#define PF_TCC 16u
#define PF_BLEND 32u
#define PF_FIXF 64u     // blend factor from FIX, not As
#define PF_ADEST 128u   // blend factor from Ad (approximation: Ad / 128 not available)
#define PF_FAULT 0x100u // TEST CONTROL ONLY: red channel dropped
#define PF_CT24 0x200u  // texture = a CT24 target read directly: alpha = TEXA.TA0 (bits 16-23), AEM bit 24
#define PF_SNAP 0x400u  // upscaled sprite: texture coordinates at the native pixel centre (scale R[22].y)
#define PF_NATTAP 0x800u // bilinear from an upscaled target: taps a native texel apart (native size R[13].xy)
#define PF_SUBPH 0x1000u // point from an upscaled target: the native texel, at the destination's sub-sample phase
#define PF_CT16 0x2000u  // texture = a 16-bit target read directly: alpha bit -> TEXA TA1 (R[13].z) / TA0 (bits 16-23), AEM bit 24
#define PF_GSLIN 0x4000u // immediate primitives: bilinear with the GS's 4-bit weights and truncation (R[13].w bit 0/1: clamp U/V)
#define PF_SHARPX 0x8000u // squeezed point-sampled 2D (gpu_set_im_xfree): sharp-bilinear in X, nearest in Y
#define PF_NOUV16 0x2000000u // CONTROL ONLY ($RG_NR_UV16=0): PF_SNAP without gs_uv16
#define PS_ATEST asuint(R[23].y)   // bits 0-2 ATST, 8-15 AREF, 16-17 TFX, 24-31 FIX
#define PS_FOGCOL asuint(R[23].z)

struct VSIn {
    int4 pos : POSITION;
    int4 nrm : NORMAL;
    int2 uv : TEXCOORD0;      // int16 UV (nr_vtx.u/v): V2-8 unsigned or V2-16 signed
    uint4 col : COLOR;
    uint4 bi : BLENDINDICES;
    uint4 bw : BLENDWEIGHT;
};

struct VSOut {
    float4 pos : SV_Position;
    noperspective float4 col : COLOR;     // GS Gouraud: linear in screen space
    float2 uv : TEXCOORD0;                // u, v: perspective-correct = S/Q, T/Q
    noperspective float fog : FOG;
    noperspective float2 uvs : TEXCOORD1; // refraction: STQ (u, v, 1), linear in screen space
    noperspective float3 stq : TEXCOORD2; // immediate: S, T, Q linear in screen space (GS), divided per pixel
};

float3 bone_mul(uint row, float4 p)       // VU: acc = r0 x + r1 y + r2 z + r3 w
{
    return B[row].xyz * p.x + B[row + 1].xyz * p.y + B[row + 2].xyz * p.z + B[row + 3].xyz * p.w;
}
float3 bone_mul3(uint row, float3 n)
{
    return B[row].xyz * n.x + B[row + 1].xyz * n.y + B[row + 2].xyz * n.z;
}

VSOut VS_nr(VSIn v)
{
    VSOut o;
    uint var = VARIANT;
    // decode (0x4392C0 / 0x4393B0): itof15 * scale
    float3 p = (float3)v.pos.xyz * (1.0 / 32768.0) * R[4].xyz;
    float3 n = (float3)v.nrm.xyz * (1.0 / 32768.0) * R[5].xyz;
    if (var & NRV_SKIN) {
        float3 ap = 0, an = 0;
        [unroll] for (int k = 0; k < 4; k++) {
            float w = (float)v.bw[k] * asfloat(0x3B808081u);   // the decode pieces' LOI
            if (w != 0.0) {
                ap += bone_mul(v.bi[k], float4(p * w, w));
                an += bone_mul3(v.bi[k], n * w);
            }
        }
        p = ap;
        n = an;
    }
    // kind (0x43E980 UV scroll, 0x43EA30 environment map)
    float2 uv = (float2)v.uv.xy * (1.0 / 32768.0) * R[6].xy;
    if (var & NRV_UVSCROLL) uv += R[6].zw;
    if (var & NRV_ENVMAP) {
        uv.x = (R[12].x * n.x + R[12].z * n.y + R[13].x * n.z + 1.0) * 0.5;
        uv.y = (R[12].y * n.x + R[12].w * n.y + R[13].y * n.z + 1.0) * 0.5;
    }
    if (var & NRV_REFLECT) {
        // kind 0x43F100: reflection of the eye -> vertex direction (world space) about N
        float3 wv = R[12].xyz * p.x + R[13].xyz * p.y + R[14].xyz * p.z + R[15].xyz - R[16].xyz;
        float3 nn = R[17].xyz * n.x + R[18].xyz * n.y + R[19].xyz * n.z;
        float l = length(wv);
        wv *= l > 0.0 ? 1.0 / l : 0.0;
        float d = 2.0 * dot(wv, nn);
        uv = (float2(wv.x - d * nn.x, wv.z - d * nn.z) + 1.0) * 0.5;
    }
    // colour (0x43A620 constant, 0x43AEC0 vertex colour, 0x43A700 lights)
    float4 c;
    if (var & NRV_LIGHT) {
        float4 d = max(R[14] * n.x + R[15] * n.y + R[16] * n.z, 0.0);
        c.rgb = R[21].rgb + R[17].rgb * d.x + R[18].rgb * d.y + R[19].rgb * d.z + R[20].rgb * d.w;
        c.a = R[21].a;
        if (var & NRV_VCOL) {
            // 0x43B120: lights x vertex colour / 128, or (87.y & 0x100, R[22].z) lights + vertex colour
            float4 vc = (float4)v.col * (256.0 / 32768.0);
            c.rgb = (asuint(R[22].z) & 0x100u) ? c.rgb + vc.rgb * 128.0 : c.rgb * vc.rgb;
            c.a *= vc.a;
        }
    } else if (var & NRV_VCOL) {
        c = R[7] * ((float4)v.col * (256.0 / 32768.0));
    } else {
        c = R[7];
    }
    float2 uvs = 0;
    if (var & NRV_REFRACT) {
        // kind 0x43ECD0 (nr_vu1.c nr_vu1_vertex): the clip matrix R[12..15] (VU qw72-75),
        // around the object origin, scaled by R[16].z (82.z), offset by R[16].xy;
        // output 0x43E380: RGB 128
        float3 cc = R[12].xyw * p.x + R[13].xyw * p.y + R[14].xyw * p.z + R[15].xyw;
        float2 o2 = float2(R[15].x, -R[15].y) / R[15].w;
        float2 s2 = float2(cc.x, -cc.y) / cc.z;
        uvs = ((s2 - o2) * R[16].z + R[16].xy + o2 + 1.0) * 0.5;
        c.rgb = 128.0;
    }
    c = min(c, R[8]);
    // output (0x1900 pieces): screen = qw68..71 * p
    float4 clip = R[0] * p.x + R[1] * p.y + R[2] * p.z + R[3];
    float w = clip.w;
    float q = 1.0 / w;
    float z = clip.z * q;
    if (var & (NRV_ZSCALE | NRV_REFRACT)) z = min(z * R[10].x, R[10].y);
    // the GS sees ftoi4 coordinates: x, y truncated to 1/16 pixel, Z to an
    // integer (XYZF2 PACKED takes bits 4-27); doing the same keeps native
    // geometry on the emulated path's grid (coplanar decals, shadows)
    z = floor(clamp(z, 0.0, R[10].z));       // the depth format's range (Z24: 2^24 - 1)
    float sx = floor(clip.x * q * 16.0) * (1.0 / 16.0);
    float sy = floor(clip.y * q * 16.0) * (1.0 / 16.0);
    if (!(abs(sx) < 1e6) || !(abs(sy) < 1e6) || w <= 0.0) { sx = clip.x * q; sy = clip.y * q; }
    float fog = clamp(R[9].x + R[9].w * w, R[9].z, R[9].y);
    // GS window -> render target NDC (gpu_core: R[11] = OFX - 0.5, OFY - 0.5, kx, ky),
    // kept in clip space (times w) so the rasterizer clips and interpolates uv
    // perspective-correctly
    o.pos.x = (sx - R[11].x) * w * R[11].z - w;
    o.pos.y = w - (sy - R[11].y) * w * R[11].w;
    o.pos.z = z * (1.0 / 4294967296.0) * w;  // the targets hold Z / 2^32 (docs/GPU.md)
    o.pos.w = w;
    o.col = floor(c);                         // VU ftoi0
    o.uv = uv;
    o.uvs = uvs;
    o.stq = float3(0.0, 0.0, 1.0);
    o.fog = floor(fog);
    return o;
}

struct PSOut {
#ifdef __spirv__
    // Vulkan (docs/NATIVE-VULKAN.md): dual-source blending reads output location 0, index 1
    [[vk::location(0)]] float4 c0 : SV_Target0;
    [[vk::location(0), vk::index(1)]] float4 c1 : SV_Target1;
#else
    float4 c0 : SV_Target0;
    float4 c1 : SV_Target1;                   // dual-source blend factor (GS alpha / 128)
#endif
};

// Immediate primitives (gpu_core.cpp gpu_nr_im_submit): vertices in GS primitive
// coordinates (pixels), XYOFFSET and the target mapping in R[11] as for meshes,
// Z as the GS holds it, colour 0..255, texture coordinates normalised.
struct VSImIn {
    float2 xy : POSITION;
    uint z : BLENDINDICES;
    uint4 col : COLOR;
    float3 stq : TEXCOORD0;
    uint fog : TEXCOORD1;
};

VSOut VS_im(VSImIn v)
{
    VSOut o;
    o.pos.x = (v.xy.x - R[11].x) * R[11].z - 1.0;
    o.pos.y = 1.0 - (v.xy.y - R[11].y) * R[11].w;
    o.pos.z = (float)v.z * (1.0 / 4294967296.0);
    o.pos.w = 1.0;
    o.col = (float4)v.col;
    o.uv = 0;
    o.uvs = 0;
    o.stq = v.stq;
    o.fog = (float)v.fog;
    return o;
}

// PF_SNAP's coordinates in texels (u - 1/2) as the GS's 4-bit sub-texel position: the GS holds
// them in fixed point, so a 1:1 or exactly scaled mapping lands on a 1/16 boundary, while the
// snap's extrapolation (ddx * a non-dyadic offset at x3, x5, x6, ...) can fall a few ulps below
// it: floor -> the neighbouring texel at 15/16 (the CT16 channel shuffle of the shadow-map
// blur then mixes two halves' bit fields: alpha bands every 8 texels, shadow bands 2026-10-26).
// Within 1/4096 texel below a boundary counts as on it (the extrapolation error is a few ulps;
// wider, 1/512, also moved bilinear sprites of x2 / x4 by up to 8 levels).
float2 gs_uv16(float2 p)
{
    return floor(p * 16.0 + 1.0 / 256.0) / 16.0;
}

// a texel of a target read directly (0..255): the texture format's alpha (TEXA) per texel,
// before any filtering, as the GS expands each texel it fetches
float4 nr_expand(float4 t, uint fl)
{
    if (fl & PF_CT24) t.a = ((fl >> 24) & 1u) != 0u && all(t.rgb == 0.0) ? 0.0 : (float)((fl >> 16) & 255u);
    if (fl & PF_CT16) t.a = t.a >= 64.0 ? R[13].z : (((fl >> 24) & 1u) != 0u && all(t.rgb == 0.0) ? 0.0 : (float)((fl >> 16) & 255u));
    return t;
}

PSOut PS_nr(VSOut i)
{
    PSOut o;
    uint fl = PS_FLAGS, at = PS_ATEST;
    float4 vc = i.col;                         // 0..255 (GS units, alpha 0x80 = 1.0)
    float4 c = vc;
    if (fl & PF_TME) {
        float3 stq = i.stq;
        if (fl & PF_SNAP) {
            // the GS evaluates a sprite's texture coordinates once per (native)
            // pixel: every sub-sample takes the value at the pixel's centre
            float sc = R[22].y;
            float2 c = (floor(i.pos.xy / sc) + 0.5) * sc;
            if (R[22].w != 0.0) c.x = i.pos.x;   // squeezed 2D (gpu_set_im_xfree): Y only
            stq += ddx(i.stq) * (c.x - i.pos.x) + ddy(i.stq) * (c.y - i.pos.y);
        }
        float2 tuv = (VARIANT & NRV_IM) ? stq.xy / (stq.z != 0.0 ? stq.z : 1e-30)
                   : (VARIANT & NRV_REFRACT) ? i.uvs : i.uv;
        if (VARIANT & NRV_IM) tuv *= R[12].xy;      // GS-normalised -> the sampled texture (a live target: its size)
        float4 t;
        if (fl & (PF_NATTAP | PF_SUBPH)) {
            // the destination pixel's sub-sample phase (centre of the sub-texel)
            float sc = R[22].y;
            float2 k = floor(i.pos.xy);
            float2 ph = (k - floor(k / sc) * sc + 0.5) / sc;
            float2 sz = R[13].xy;
            if (fl & PF_SUBPH) {
                t = nr_expand(floor(g_tex.Sample(g_smp, (floor(tuv * sz) + ph) / sz) * 255.0 + 0.5), fl);
            } else {
                // the GS's 4-bit weights and >> 8 truncation (as PF_GSLIN): the draw-back's
                // alpha >= 1 second pass depends on it
                float2 p = tuv * sz - 0.5;
                if ((fl & (PF_SNAP | PF_NOUV16)) == PF_SNAP) p = gs_uv16(p);
                float2 i0 = floor(p);
                int2 f = (int2)((p - i0) * 16.0);
                int4 t00 = (int4)nr_expand(floor(g_tex.Sample(g_smp, (i0 + ph) / sz) * 255.0 + 0.5), fl);
                int4 t10 = (int4)nr_expand(floor(g_tex.Sample(g_smp, (i0 + float2(1, 0) + ph) / sz) * 255.0 + 0.5), fl);
                int4 t01 = (int4)nr_expand(floor(g_tex.Sample(g_smp, (i0 + float2(0, 1) + ph) / sz) * 255.0 + 0.5), fl);
                int4 t11 = (int4)nr_expand(floor(g_tex.Sample(g_smp, (i0 + float2(1, 1) + ph) / sz) * 255.0 + 0.5), fl);
                t = (float4)((t00 * ((16 - f.x) * (16 - f.y)) + t10 * (f.x * (16 - f.y)) + t01 * ((16 - f.x) * f.y) + t11 * (f.x * f.y)) >> 8);
            }
        } else if (fl & PF_GSLIN) {
            // the GS filter exactly (gs_draw.hlsl sample_level): taps at floor(u - 1/2), weights
            // in 1/16, sum >> 8.  Alpha-tested two-pass edges (the composite draw-back: alpha > 0,
            // then alpha >= 1 drawn opaque) depend on the truncation
            uint W, H;
            g_tex.GetDimensions(W, H);
            float2 p = tuv * float2((float)W, (float)H) - 0.5;
            if ((fl & (PF_SNAP | PF_NOUV16)) == PF_SNAP) p = gs_uv16(p);
            float2 p0 = floor(p);
            int2 f = (int2)((p - p0) * 16.0), a = (int2)p0, b = a + 1;
            uint cl = asuint(R[13].w);
            int2 wm = int2((int)W - 1, (int)H - 1);
            a.x = (cl & 1u) ? clamp(a.x, 0, wm.x) : (a.x & wm.x); b.x = (cl & 1u) ? clamp(b.x, 0, wm.x) : (b.x & wm.x);
            a.y = (cl & 2u) ? clamp(a.y, 0, wm.y) : (a.y & wm.y); b.y = (cl & 2u) ? clamp(b.y, 0, wm.y) : (b.y & wm.y);
            int4 t00 = (int4)nr_expand(round(g_tex.Load(int3(a.x, a.y, 0)) * 255.0), fl);
            int4 t10 = (int4)nr_expand(round(g_tex.Load(int3(b.x, a.y, 0)) * 255.0), fl);
            int4 t01 = (int4)nr_expand(round(g_tex.Load(int3(a.x, b.y, 0)) * 255.0), fl);
            int4 t11 = (int4)nr_expand(round(g_tex.Load(int3(b.x, b.y, 0)) * 255.0), fl);
            t = (float4)((t00 * ((16 - f.x) * (16 - f.y)) + t10 * (f.x * (16 - f.y)) + t01 * ((16 - f.x) * f.y) + t11 * (f.x * f.y)) >> 8);
        } else if (fl & PF_SHARPX) {
            // sharp-bilinear in X: the two texels either side of the nearest texel boundary,
            // weighted by how much of the pixel's footprint (one output pixel wide) each
            // covers; nearest (the point sampler at the texel centre) in Y
            uint W, H;
            g_tex.GetDimensions(W, H);
            float u = tuv.x * (float)W;
            float fw = max(abs(ddx(u)), 1e-6);
            float seam = floor(u + 0.5);
            float w = saturate((u - seam) / fw + 0.5);
            float4 t0 = nr_expand(floor(g_tex.SampleLevel(g_smp, float2((seam - 0.5) / (float)W, tuv.y), 0) * 255.0 + 0.5), fl);
            float4 t1 = nr_expand(floor(g_tex.SampleLevel(g_smp, float2((seam + 0.5) / (float)W, tuv.y), 0) * 255.0 + 0.5), fl);
            t = floor(lerp(t0, t1, w) + 0.5);
        } else {
            t = nr_expand(floor(g_tex.Sample(g_smp, tuv) * 255.0 + 0.5), fl);
        }
        uint tfx = (at >> 16) & 3u;
        bool tcc = (fl & PF_TCC) != 0;
        if (tfx == 0u) {                       // MODULATE
            c.rgb = min(floor(vc.rgb * t.rgb / 128.0), 255.0);
            c.a = tcc ? min(floor(vc.a * t.a / 128.0), 255.0) : vc.a;
        } else if (tfx == 1u) {                // DECAL
            c.rgb = t.rgb;
            c.a = tcc ? t.a : vc.a;
        } else if (tfx == 2u) {                // HIGHLIGHT
            c.rgb = min(floor(vc.rgb * t.rgb / 128.0) + vc.a, 255.0);
            c.a = tcc ? min(t.a + vc.a, 255.0) : vc.a;
        } else {                               // HIGHLIGHT2
            c.rgb = min(floor(vc.rgb * t.rgb / 128.0) + vc.a, 255.0);
            c.a = tcc ? t.a : vc.a;
        }
    }
#ifdef NR_CROV
    bool apass = true;
#endif
    if (fl & PF_ATE) {
        uint atst = at & 7u;
        float aref = (float)((at >> 8) & 255u);
        bool ok = true;
        if (atst == 0u) ok = false;
        else if (atst == 2u) ok = c.a < aref;
        else if (atst == 3u) ok = c.a <= aref;
        else if (atst == 4u) ok = c.a == aref;
        else if (atst == 5u) ok = c.a >= aref;
        else if (atst == 6u) ok = c.a > aref;
        else if (atst == 7u) ok = c.a != aref;
#ifdef NR_CROV
        apass = ok;
#else
        if (!ok) discard;                    // AFAIL KEEP (the only mode the census sees)
#endif
    }
#ifdef NR_CROV
    uint rfl = asuint(R[1].x), afail = (rfl >> 8) & 3u;
    if (!apass && afail == 0u) discard;
    bool zw_ok = apass || afail == 2u;               // ZB_ONLY writes Z
    bool c_ok = apass || afail == 1u || afail == 3u; // FB_ONLY / RGB_ONLY write colour
    bool a_ok = apass || afail == 1u;                // RGB_ONLY keeps the stored alpha
    uint2 rp = (uint2)i.pos.xy;
    uint2 px = (uint2)(floor(i.pos.xy / max(R[2].z, 1.0)));   // the native pixel (dither, scan mask)
    if ((rfl & CR_SCAN) && ((px.y & 1u) != 0u) == ((rfl & CR_SCANODD) != 0u)) discard;
    uint fpsm = (asuint(R[1].z) >> 16) & 63u;
    uint4 dst = nr_from_stored(fpsm, nr_to_stored(fpsm, (uint4(g_crov[rp], g_crov[rp] >> 8, g_crov[rp] >> 16, g_crov[rp] >> 24) & 255u)));
    if ((rfl & CR_DATE) && (fpsm == 0x00u || nr_is16(fpsm))) {
        if (((dst.a >> 7) & 1u) != ((rfl & CR_DATM) ? 1u : 0u)) discard;
    }
#endif
#ifdef NR_ZROV
    {
        uint zc = PS_ZCTL, zfn = zc & 3u;
        if (zfn >= 2u) {
            uint2 xy = (uint2)i.pos.xy;
            // the hardware path's DepthBias -2: two Z units toward "far"
            // (immediate primitives: no bias, like the emulated path they replace)
            float zf = (VARIANT & NRV_IM) ? i.pos.z : i.pos.z - 2.0 / 4294967296.0;
            float zd = g_zrov[xy];
            bool zok = zfn == 2u ? zf >= zd : zf > zd;
            if (!zok) discard;
#ifdef NR_CROV
            if ((zc & 16u) && zw_ok) g_zrov[xy] = zf;
        } else if (zfn == 1u && (zc & 16u) && zw_ok) {
#else
            if (zc & 16u) g_zrov[xy] = zf;
        } else if (zfn == 1u && (zc & 16u)) {
#endif
            g_zrov[(uint2)i.pos.xy] = i.pos.z;
        }
    }
#endif
    if (fl & PF_FGE) {
        uint fc = PS_FOGCOL;
        float3 fcol = float3(fc & 255u, (fc >> 8) & 255u, (fc >> 16) & 255u);
        float f = i.fog;
        c.rgb = floor((c.rgb * f + fcol * (255.0 - f)) / 256.0);
    }
#ifdef NR_CROV
    {
        // the GS pixel back end (gs_draw.hlsl PS_main's, in the same order)
        uint as = (uint)c.a;
        int3 rgb = (int3)c.rgb;
        uint rz = asuint(R[1].z);
        if ((rfl & CR_ABE) && !((rfl & CR_PABE) && !(as & 0x80u))) {
            uint sa = rz & 3u, sb = (rz >> 2) & 3u, sc = (rz >> 4) & 3u, sd = (rz >> 6) & 3u;
            int ad = fpsm == 0x01u ? 0x80 : (int)dst.a;
            int cc = sc == 0u ? (int)as : (sc == 1u ? ad : (int)((rz >> 8) & 255u));
            int3 cs = rgb, cd = (int3)dst.rgb;
            int3 A = sa == 0u ? cs : (sa == 1u ? cd : int3(0, 0, 0));
            int3 Bv = sb == 0u ? cs : (sb == 1u ? cd : int3(0, 0, 0));
            int3 Dd = sd == 0u ? cs : (sd == 1u ? cd : int3(0, 0, 0));
            rgb = (((A - Bv) * cc) >> 7) + Dd;
        }
        if ((rfl & CR_DTHE) && nr_is16(fpsm)) {
            uint word = (px.y & 2u) ? asuint(R[2].y) : asuint(R[2].x);
            int dv = (int)((word >> ((px.y & 1u) * 16u + (px.x & 3u) * 4u)) & 7u);
            rgb += dv >= 4 ? dv - 8 : dv;
        }
        if (rfl & CR_COLCLAMP) rgb = clamp(rgb, 0, 255);
        else rgb &= 255;
        uint4 oc = uint4((uint3)rgb, (as | ((fl & PF_FBA) ? 0x80u : 0u)) & 255u);
        if (!c_ok) oc = dst;
        if (!a_ok) oc.a = dst.a;
        uint mask = nr_to_stored(fpsm, uint4(asuint(R[1].y), asuint(R[1].y) >> 8, asuint(R[1].y) >> 16, asuint(R[1].y) >> 24) & 255u);
        uint nraw = nr_to_stored(fpsm, oc), draw = nr_to_stored(fpsm, dst);
        oc = nr_from_stored(fpsm, (draw & mask) | (nraw & ~mask));
        g_crov[rp] = oc.r | (oc.g << 8) | (oc.b << 16) | (oc.a << 24);
    }
#endif
    float F = (fl & PF_FIXF) ? (float)(at >> 24) : c.a;
    o.c1 = min(F / 128.0, 1.0).xxxx;
    if (fl & PF_FAULT) c.r = 0.0;
    float a = c.a;
    if ((fl & PF_FBA) && a < 128.0) a += 128.0;   // FBA: stored alpha | 0x80
    o.c0 = float4(c.rgb, a) / 255.0;
    return o;
}
