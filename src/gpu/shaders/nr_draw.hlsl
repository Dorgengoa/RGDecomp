// SPDX-License-Identifier: CC0-1.0
// Native model pipeline (docs/NATIVE-RENDER.md): the dominant VU1 model
// program's per-vertex math (src/native/render/nr_vu1.c is the reference)
// as a vertex shader over the mesh's raw quantised attributes, and a pixel
// shader with a hardware-sampled decoded texture, the GS texture function,
// fog and alpha test.  Blending, depth and culling are fixed-function state.

cbuffer NrCB : register(b0)
{
    float4 R[26];       // rows 24-25: the VU clipper's clip space (GS_nr; nr_scene.c nr_clip_cb)
};
cbuffer NrBones : register(b1)  // bound for skinned meshes only
{
    float4 B[256];      // VU1 qwords 768..1023: bone matrix rows
};
#ifdef NR_RT
// Ray-traced shadows (docs/RAYTRACING.md; Vulkan only, entries *_rt of nr_vulkan.cmake, SM 6.5):
// the receiver's world position (VS) and a shadow ray to light 0 against the scene's TLAS (PS)
cbuffer NrRT : register(b2)
{
    float4 RTW[4];      // object matrix columns (VU qw60-63): world = RTW0 x + RTW1 y + RTW2 z + RTW3
    float4 RTL;         // xyz light 0 direction (world, normalised, towards the light); w > 0: on
    float4 RTC;         // rgb: the colour multiplier of a shadowed pixel
    float4 RTP;         // x ray length, y origin offset, z origin offset per unit of eye distance, w debug colours
    float4 RTE;         // xyz camera position (world)
    float4 RTM;         // xy (as uint) the material table's device address (RT2b), z rays per pixel, w the light's radius (tangent)
    float4 RTS;         // x the enclosure counters' slot (-1 none), y 1: alpha-tested candidates never hit (RG_RT_ALPHA=3, a control), zw foliage fade near / far
    float4 RTX;         // x the opaque casters' instance mask, y the cut-out casters' (RT2c: map 1 / 2, characters 4 / 8), z a reflection ray's (rt5)
    float4 RTH;         // the penumbra filter (RT2f): x 1 on, y internal pixels per GS pixel, z the present's number (mod 1024), w bit 0 half rate ($RG_RT_HALF), bits 1-3 measurement ($RG_RT_FEXP)
    float4 RTQ;         // xyz the previous present's camera position, w 1: its camera is known
    float4 RTV[4];      // the previous present's world -> GS screen (homogeneous) columns
    float4 RTB[8];      // the characters' bounding spheres (xyz centre, w radius; 0 none): the characters-only ray only through one
    float4 RTA;         // ambient occlusion (RT2e): x ray length (0 off), y strength, z the history's words per pixel (1, 2 with AO)
    float4 RTR;         // (rt5) reflections: x 1 = this draw's environment / reflection map texel is the reflection's hit, 2 = water (Fresnel blend of the layer's colour), y strength, z ray length, w bit 0: one ray per 2 x 2 quad, bit 1: debug colours of the reflections only ($RG_RT_REFLDBG=1)
    float4 RTF;         // (rt6) reflections: x 1 = the hit is fogged with the game's fog (R[9], the GS fog colour) over its distance from the mirror, y the distance fade's start (fraction of RTR.z; >= 1 off), z 1 = smooth (interpolated vertex) normals, w the map draws' clip w per unit of eye distance (0: the draw's own, wn.w)
    float4 RTG;         // (rt7) x reflections' brightness floor (fraction of the painted texel's luminance; 0 off), y 1: one AO ray per 2 x 2 quad ($RG_RT_AO_QUAD), z measurement ($RG_RT_AOEXP bits: 1 no AO ray, 2 no AO history), w 1: both history words in one read ($RG_RT_HIST2)
    float4 RTI;         // (rt8) emissive lights: xy (as uint) the list's device address (32 bytes a light: xyz position, w radius;
                        // rgb colour x strength (128 = the baked full light), w reach), z count, w bit 0: debug view (the added light only), bit 1: rt7's character AO / jitter ($RG_RT_CHRPAT=0)
    float4 RTWP[4];     // (rt9) the previous present's object matrix columns of this draw (RTMV.x 1)
    float4 RTMV;        // (rt9) motion: x 1 = this receiver moves (a character part: RTWP / PB are its previous present's
                        // object rows / bones, the history is reprojected from the previous position), y 1 = PB holds
                        // the previous bones, z 1 = no previous pose (first present: no history), w the character
                        // receivers' mode bits (1 AO + soft shadow restored, 2 the 2 x 2 quad average of the noisy terms,
                        // 4 their AO rays see the characters, 8 measurement: every receiver traces RTN.z AO rays,
                        // 16 the history clamped to the quad's current samples, RTO.x margin, 32 white-noise samples)
    float4 RTN;         // (rt9) moving receivers' history: x / y the reprojected eye-distance tolerance (fraction, units),
                        // z AO rays per pixel, w the new sample's least weight
    float4 RTO;         // (rt9) x a moving receiver's history clamp margin (RTMV.w bit 4), y its shadow rays per pixel
    float4 RTJ;         // (rt9) emissive cost: xy (as uint) the draw's light mask (bit i: light i reaches its world box),
                        // z bit 0 the 2 x 2 quad shares the light loop and the shadow rays (nr_rt_emi), w 1 no mask (every light)
};
cbuffer NrRTPrev : register(b3)   // (rt9) the previous present's bones of a skinned character receiver (RTMV.y)
{
    float4 PB[256];
};
RaytracingAccelerationStructure g_tlas : register(t8);
RaytracingAccelerationStructure g_tlasc : register(t9);   // the characters' own (RT2c, the filter's characters-only ray)
// the enclosure counters (nr_vulkan.cpp rt_stat): per game frame slot RTS.x, sun-facing pixels and
// shadowed ones
RWByteAddressBuffer g_rtstat : register(u6);
// the penumbra filter's history (RT2f, nr_rt_filter): one word per pixel, mean | length << 10 |
// the eye distance (half float) << 16; written for this present (u7), read from the previous one (u8)
RWTexture2D<uint> g_rth : register(u7);
RWTexture2D<uint> g_rthp : register(u8);
#endif

Texture2D<float4> g_tex : register(t0);
SamplerState g_smp : register(s0);
#ifdef NR_ZROV
// depth targets in rasterizer-ordered views (docs/PERF-3D.md fix 1): the
// emulated path keeps its fast depth-in-ROV mode, so native draws test and
// write Z there too (u2: after SV_Target0 and the dual-source SV_Target1)
#ifdef NR_CROV_PLAIN
// a colour-view draw whose primitives cover disjoint pixels (nr_d3d11.cpp im_disjoint): no
// pixel is written twice inside the draw, so the views need no ordering (D3D11 orders draws)
RWTexture2D<float> g_zrov : register(u2);
#else
RasterizerOrderedTexture2D<float> g_zrov : register(u2);
#endif
#define PS_ZCTL asuint(R[23].w)   // bits 0-1 GpuZFunc, bit 4 Z write
#endif
#ifdef NR_ZDSV
// depth in a D32_FLOAT depth-stencil view, fixed-function test and write, with the value
// NR_ZROV tests and writes as the shader's depth output (docs/NATIVE-RENDER.md "Throughput
// (2026-10-30)"): no ordered view, so no barrier between draws and early depth rejection
// (the output never exceeds the interpolated depth: SV_DepthLessEqual)
#define PS_ZCTL asuint(R[23].w)
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
#ifdef NR_CROV_PLAIN
RWTexture2D<uint> g_crov : register(u3);
#else
RasterizerOrderedTexture2D<uint> g_crov : register(u3);
#endif   // (u0-u1: the outputs, u2: zrov)
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
#define PF_SHARPY 0x10000u // with PF_SHARPX: scaled in Y too (accessibility.ui_scale): sharp-bilinear in Y as well
#define PF_NOUV16 0x2000000u // CONTROL ONLY ($RG_NR_UV16=0): PF_SNAP without gs_uv16
#define PF_BOX 0x4000000u   // a live target minified (screen-effect "enhanced", nr_sfx.c): box filter over the
                            // pixel's whole footprint in internal-resolution texels (no snap, no native taps)
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
#if defined(NR_ZDSV) && !defined(NR_ZDSV_PLAIN)
    // a conservative depth output needs the position centroid-interpolated (one sample per
    // pixel: the pixel centre, the same values)
    noperspective centroid float4 pos : SV_Position;
#else
    float4 pos : SV_Position;
#endif
    noperspective float4 col : COLOR;     // GS Gouraud: linear in screen space
    float2 uv : TEXCOORD0;                // u, v: perspective-correct = S/Q, T/Q
    noperspective float fog : FOG;
    noperspective float2 uvs : TEXCOORD1; // refraction: STQ (u, v, 1), linear in screen space
    noperspective float3 stq : TEXCOORD2; // immediate: S, T, Q linear in screen space (GS), divided per pixel
    // a triangle with a vertex behind the eye (w <= 0) is clipped by the rasterizer; a
    // noperspective attribute at its clip point is undefined (screen-space ratio towards a
    // vertex with no screen position): such triangles take colour and fog perspective-correct
    // instead (the VU clipper's new vertices get the clip-space interpolation too).  nearf > 0:
    // this pixel's triangle has such a vertex (docs/NATIVE-RENDER.md "Near-plane depth")
    float4 colp : COLOR1;
    float fogp : FOG1;
    float nearf : TEXCOORD3;
    // the VU clipper's near plane (GS Z = R[10].w, nr_scene.c nr_near_z): Znear * w - clip.z,
    // perspective-interpolated (linear in object space); < 0 = nearer than the PS2's near plane,
    // which the clipper cuts away (the hardware's own clip is at Z = 2^32, w ~ 1/256):
    // discarded (docs/NATIVE-RENDER.md "Near-plane clip (2026-10-31)")
    float nearl : TEXCOORD4;
    // the homogeneous GS screen position before the divide (R[0..3] x p; GS_nr clips it)
    noperspective float4 hs : TEXCOORD5;
#ifdef NR_RT
    float3 wp : TEXCOORD6;                // world position (perspective-correct: linear in object space)
    float4 wn : TEXCOORD7;                // (rt6) xyz the vertex normal (world, unnormalised), w the clip w per unit of eye distance (the hit's fog)
    float3 wq : TEXCOORD8;                // (rt9) the same surface point's world position in the previous present (= wp: static)
#endif
};

float3 bone_mul(uint row, float4 p)       // VU: acc = r0 x + r1 y + r2 z + r3 w
{
    return B[row].xyz * p.x + B[row + 1].xyz * p.y + B[row + 2].xyz * p.z + B[row + 3].xyz * p.w;
}
float3 bone_mul3(uint row, float3 n)
{
    return B[row].xyz * n.x + B[row + 1].xyz * n.y + B[row + 2].xyz * n.z;
}

// the output pieces' screen transform of a homogeneous screen position clip (= qw68..71 x p):
// position, Z, fog and the near-plane terms (VS_nr, and GS_nr for the clipper's new vertices)
void nr_place(float4 clip, inout VSOut o)
{
    uint var = VARIANT;
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
    // a vertex behind the eye (w <= 0, its triangle crosses the near plane): Z = clip.z / w is
    // meaningless there and the clamp above pinned it to 0 or the maximum, which bent the depth
    // of the whole triangle (interpolated in clip space) and its near-plane clip point; the
    // unclamped clip-space value keeps Z = clip.z / w exact across the visible part, as the VU
    // clipper's new vertices have it (docs/NATIVE-RENDER.md "Near-plane depth", 2026-10-31)
    if (!(w > 0.0)) {
        float zl = clip.z;
        if (var & (NRV_ZSCALE | NRV_REFRACT)) zl *= R[10].x;
        o.pos.z = zl * (1.0 / 4294967296.0);
    }
    o.pos.w = w;
    o.nearf = w > 0.0 ? 0.0 : 1.0;
    o.nearl = R[10].w != 0.0 ? (R[10].w * w - clip.z) * (1.0 / 16777216.0) : 1.0;
    o.fog = floor(fog);
    o.fogp = o.fog;
    o.hs = clip;
}

VSOut VS_nr(VSIn v)
{
    VSOut o = (VSOut)0;
    uint var = VARIANT;
    // decode (0x4392C0 / 0x4393B0): itof15 * scale
    float3 p = (float3)v.pos.xyz * (1.0 / 32768.0) * R[4].xyz;
    float3 n = (float3)v.nrm.xyz * (1.0 / 32768.0) * R[5].xyz;
#ifdef NR_RT
    const float3 p0 = p;   // (rt9: posed again with the previous bones below)
#endif
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
    nr_place(clip, o);
#ifdef NR_RT
    o.wp = RTW[0].xyz * p.x + RTW[1].xyz * p.y + RTW[2].xyz * p.z + RTW[3].xyz;
    {
        float de = length(o.wp - RTE.xyz);
        o.wn = float4(RTW[0].xyz * n.x + RTW[1].xyz * n.y + RTW[2].xyz * n.z, de > 0.0 ? clip.w / de : 0.0);
    }
    o.wq = o.wp;
    if (RTMV.x > 0.5) {
        // (rt9) a moving receiver (a character part): the same vertex at the previous present's pose
        float3 pq = p;
        if ((var & NRV_SKIN) && RTMV.y > 0.5) {
            pq = 0;
            [unroll] for (int k = 0; k < 4; k++) {
                float w = (float)v.bw[k] * asfloat(0x3B808081u);
                if (w != 0.0) {
                    const uint row = v.bi[k];
                    pq += PB[row].xyz * (p0.x * w) + PB[row + 1].xyz * (p0.y * w) + PB[row + 2].xyz * (p0.z * w) + PB[row + 3].xyz * w;
                }
            }
        }
        o.wq = RTWP[0].xyz * pq.x + RTWP[1].xyz * pq.y + RTWP[2].xyz * pq.z + RTWP[3].xyz;
    }
#endif
    o.col = floor(c);                         // VU ftoi0
    o.colp = o.col;
    o.uv = uv;
    o.uvs = uvs;
    o.stq = float3(0.0, 0.0, 1.0);
    return o;
}

// The VU clipper (0x2620 piece 0x4371D0, docs/NATIVE-RENDER.md "VU clipper (2026-10-31)"), for
// meshes with qw81.x bit 1 (R[25].z != 0): a triangle with a vertex outside the clip volume
// |x * g.x|, |y * g.y|, |z| <= |w| (qw72-75's clip space, guard scale qw105.xy; R[24..25] map the
// homogeneous screen position to it) is not drawn by the main packet (the output pieces' ADC):
// the clipper cuts it with the planes +z -z +x -x +y -y (Sutherland-Hodgman, the attributes
// linear in clip space) and kicks the polygon as a fan from its first vertex.  The GS
// interpolates colour and fog linearly in screen space between those new vertices, so a
// triangle reaching far past the screen or the eye shades differently from the same triangle
// rasterized whole (the dim Vedan 8-A light pool).  Fully outside one plane: not drawn.
float4 nr_gclip(float4 hs)
{
    return float4(R[24].x * hs.x + R[24].y * hs.w, R[24].z * hs.y + R[24].w * hs.w,
                  R[25].x * hs.z + R[25].y * hs.w, hs.w);
}
uint nr_cflags(float4 c)   // VU CLIP: +x -x +y -y +z -z against |w|
{
    float aw = abs(c.w);
    return (c.x > aw ? 1u : 0u) | (c.x < -aw ? 2u : 0u) | (c.y > aw ? 4u : 0u) | (c.y < -aw ? 8u : 0u) |
           (c.z > aw ? 16u : 0u) | (c.z < -aw ? 32u : 0u);
}
float nr_pdist(float4 c, uint k)   // signed distance to plane k (0 +z, 1 -z, 2 +x, 3 -x, 4 +y, 5 -y): > 0 outside
{
    float v = k < 2u ? c.z : (k < 4u ? c.x : c.y);
    return (k & 1u) ? -v - c.w : v - c.w;
}
#define NR_CMAX 9
[maxvertexcount(21)]
void GS_nr(triangle VSOut v[3], inout TriangleStream<VSOut> ts)
{
    // (vertices passed through are placed again from hs: Vulkan's Y flip (-fvk-invert-y) applies
    // to the last stage before the rasterizer, here; the same values as VS_nr's)
    float4 c0 = nr_gclip(v[0].hs), c1 = nr_gclip(v[1].hs), c2 = nr_gclip(v[2].hs);
    uint f0 = nr_cflags(c0), f1 = nr_cflags(c1), f2 = nr_cflags(c2);
    if (R[25].z == 0.0 || (f0 | f1 | f2) == 0u) {
        [unroll] for (int i0 = 0; i0 < 3; i0++) { VSOut o = v[i0]; nr_place(v[i0].hs, o); ts.Append(o); }
        return;
    }
    if ((f0 & f1 & f2) != 0u) return;   // outside one plane: rejected
    // the polygon: homogeneous screen position, colour, uv, refraction uv
    float4 ph[NR_CMAX], pc[NR_CMAX];
    float2 pu[NR_CMAX], ps[NR_CMAX];
    float4 qh[NR_CMAX], qc[NR_CMAX];
    float2 qu[NR_CMAX], qs[NR_CMAX];
    [unroll] for (int z0 = 0; z0 < NR_CMAX; z0++) {
        ph[z0] = 0; pc[z0] = 0; pu[z0] = 0; ps[z0] = 0; qh[z0] = 0; qc[z0] = 0; qu[z0] = 0; qs[z0] = 0;
    }
    [unroll] for (int i = 0; i < 3; i++) { ph[i] = v[i].hs; pc[i] = v[i].col; pu[i] = v[i].uv; ps[i] = v[i].uvs; }
#ifdef NR_RT
    float3 pw[NR_CMAX], qw[NR_CMAX], pv[NR_CMAX], qv[NR_CMAX];   // (rt9 pv / qv: the previous position)
    float4 pn[NR_CMAX], qn[NR_CMAX];   // (rt6) the vertex normal + fog scale
    [unroll] for (int z1 = 0; z1 < NR_CMAX; z1++) { pw[z1] = 0; qw[z1] = 0; pn[z1] = 0; qn[z1] = 0; pv[z1] = 0; qv[z1] = 0; }
    [unroll] for (int i1 = 0; i1 < 3; i1++) { pw[i1] = v[i1].wp; pn[i1] = v[i1].wn; pv[i1] = v[i1].wq; }
#define NR_RT_GS(x) x
#else
#define NR_RT_GS(x)
#endif
    uint n = 3u;
    [loop] for (uint k = 0u; k < 6u; k++) {
        uint m = 0u;
        [loop] for (uint j = 0u; j < n; j++) {
            uint j2 = j + 1u == n ? 0u : j + 1u;
            float4 a = nr_gclip(ph[j]), b = nr_gclip(ph[j2]);
            float da = nr_pdist(a, k), db = nr_pdist(b, k);
            // the VU's flags (CLIP against |w|) decide; the cut point is signed (w as is)
            uint fa = nr_cflags(a), fb = nr_cflags(b), bit = (k < 2u ? 16u : (k < 4u ? 1u : 4u)) << (k & 1u);
            bool ina = (fa & bit) == 0u, inb = (fb & bit) == 0u;
            if (ina && m < NR_CMAX) { qh[m] = ph[j]; qc[m] = pc[j]; qu[m] = pu[j]; qs[m] = ps[j]; NR_RT_GS(qw[m] = pw[j]; qn[m] = pn[j]; qv[m] = pv[j];) m++; }
            if (ina != inb && m < NR_CMAX) {
                float t = da / (da - db);
                qh[m] = lerp(ph[j], ph[j2], t); qc[m] = lerp(pc[j], pc[j2], t);
                qu[m] = lerp(pu[j], pu[j2], t); qs[m] = lerp(ps[j], ps[j2], t);
                NR_RT_GS(qw[m] = lerp(pw[j], pw[j2], t); qn[m] = lerp(pn[j], pn[j2], t); qv[m] = lerp(pv[j], pv[j2], t);)
                m++;
            }
        }
        n = m;
        [loop] for (uint j3 = 0u; j3 < n; j3++) { ph[j3] = qh[j3]; pc[j3] = qc[j3]; pu[j3] = qu[j3]; ps[j3] = qs[j3]; NR_RT_GS(pw[j3] = qw[j3]; pn[j3] = qn[j3]; pv[j3] = qv[j3];) }
        if (n < 3u) return;
    }
    VSOut f0v = v[0];
    f0v.uv = pu[0]; f0v.uvs = ps[0]; f0v.col = floor(pc[0]); f0v.colp = f0v.col; NR_RT_GS(f0v.wp = pw[0]; f0v.wn = pn[0]; f0v.wq = pv[0];)
    nr_place(ph[0], f0v);
    VSOut prev = f0v;
    prev.uv = pu[1]; prev.uvs = ps[1]; prev.col = floor(pc[1]); prev.colp = prev.col; NR_RT_GS(prev.wp = pw[1]; prev.wn = pn[1]; prev.wq = pv[1];)
    nr_place(ph[1], prev);
    [loop] for (uint t2 = 2u; t2 < n; t2++) {
        VSOut cur = v[0];
        cur.uv = pu[t2]; cur.uvs = ps[t2]; cur.col = floor(pc[t2]); cur.colp = cur.col; NR_RT_GS(cur.wp = pw[t2]; cur.wn = pn[t2]; cur.wq = pv[t2];)
        nr_place(ph[t2], cur);
        ts.Append(f0v); ts.Append(prev); ts.Append(cur);
        ts.RestartStrip();
        prev = cur;
    }
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
#if defined(NR_ZDSV) && defined(NR_ZDSV_PLAIN)
    float zo : SV_Depth;
#elif defined(NR_ZDSV)
    float zo : SV_DepthLessEqual;
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
    o.colp = o.col;
    o.fogp = o.fog;
    o.nearf = 0.0;
    o.nearl = 1.0;
    o.hs = float4(0.0, 0.0, 0.0, 1.0);
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

#ifdef NR_RT
// RT2b (docs/RAYTRACING.md "Alpha-tested casters"): an alpha-tested caster instance (FORCE_NO_OPAQUE)
// reaches the candidate loop; its material row (64 bytes at RTM.xy + 64 x instance custom index,
// nr_vulkan.cpp rt_frame) names the mesh's vertex / index buffers and a copy of its texture's texels:
// the GS rule (texture function alpha, then ATST against AREF) at the hit point decides
//   u0-1 vertex buffer, u2-3 index buffer, u4-5 texels (RGBA8; 0 = opaque), u6 width | height << 16,
//   u7 ATST | AREF << 8 | TFX << 16 | VCOL << 19 | clamp U << 20 | clamp V << 21 | bilinear << 23,
//   u8-11 UV scale xy, scroll zw (float), u12 material alpha, u13 its clamp (float), u14 mesh id
uint64_t nr_rt_a64(uint lo, uint hi) { return ((uint64_t)hi << 32) | (uint64_t)lo; }
float nr_rt_texa(uint64_t tex, int2 q, int W, int H, uint fl)
{
    q.x = (fl & 0x100000u) ? clamp(q.x, 0, W - 1) : ((q.x % W) + W) % W;
    q.y = (fl & 0x200000u) ? clamp(q.y, 0, H - 1) : ((q.y % H) + H) % H;
    return (float)(vk::RawBufferLoad<uint>(tex + (uint64_t)(q.y * W + q.x) * 4u, 4) >> 24);
}
bool nr_rt_alpha_pass(uint inst, uint prim, float2 bc, out uint flo)
{
    uint64_t m = nr_rt_a64(asuint(RTM.x), asuint(RTM.y)) + (uint64_t)inst * 64u;
    uint4 m0 = vk::RawBufferLoad<uint4>(m, 16), m1 = vk::RawBufferLoad<uint4>(m + 16u, 16);
    uint4 m2 = vk::RawBufferLoad<uint4>(m + 32u, 16), m3 = vk::RawBufferLoad<uint4>(m + 48u, 16);
    uint64_t tex = nr_rt_a64(m1.x, m1.y);
    flo = m1.w;
    if (tex == 0u) return true;
    uint64_t vb = nr_rt_a64(m0.x, m0.y), ib = nr_rt_a64(m0.z, m0.w);
    uint fl = m1.w;
    int W = (int)(m1.z & 0xFFFFu), H = (int)(m1.z >> 16);
    uint64_t ip = ib + (uint64_t)prim * 12u;
    uint3 ix = uint3(vk::RawBufferLoad<uint>(ip, 4), vk::RawBufferLoad<uint>(ip + 4u, 4), vk::RawBufferLoad<uint>(ip + 8u, 4));
    float3 w = float3(1.0 - bc.x - bc.y, bc.x, bc.y);
    uint u0 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.x * 28u + 12u, 4);
    uint u1 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.y * 28u + 12u, 4);
    uint u2 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.z * 28u + 12u, 4);
    float2 t0 = float2((float)((int)(u0 << 16) >> 16), (float)((int)u0 >> 16));
    float2 t1 = float2((float)((int)(u1 << 16) >> 16), (float)((int)u1 >> 16));
    float2 t2 = float2((float)((int)(u2 << 16) >> 16), (float)((int)u2 >> 16));
    float2 uv = (t0 * w.x + t1 * w.y + t2 * w.z) * (1.0 / 32768.0) * asfloat(m2.xy) + asfloat(m2.zw);
    // the vertex alpha (VS_nr: material alpha x vertex alpha / 128, min R[8].a, ftoi0)
    float va = asfloat(m3.x);
    if (fl & 0x80000u) {
        float a0 = (float)(vk::RawBufferLoad<uint>(vb + (uint64_t)ix.x * 28u + 16u, 4) >> 24);
        float a1 = (float)(vk::RawBufferLoad<uint>(vb + (uint64_t)ix.y * 28u + 16u, 4) >> 24);
        float a2 = (float)(vk::RawBufferLoad<uint>(vb + (uint64_t)ix.z * 28u + 16u, 4) >> 24);
        va *= (a0 * w.x + a1 * w.y + a2 * w.z) / 128.0;
    }
    va = floor(min(va, asfloat(m3.y)));
    // the texel alpha (bilinear as the raster sampler, or nearest)
    float2 p = uv * float2((float)W, (float)H);
    float ta;
    if ((fl & 0x800000u) && RTS.y == 2.0) {   // (bilinear: $RG_RT_ALPHA=2; nearest by default, a quarter of the loads)
        p -= 0.5;
        float2 p0 = floor(p), f = p - p0;
        int2 a = (int2)p0;
        float x0 = lerp(nr_rt_texa(tex, a, W, H, fl), nr_rt_texa(tex, a + int2(1, 0), W, H, fl), f.x);
        float x1 = lerp(nr_rt_texa(tex, a + int2(0, 1), W, H, fl), nr_rt_texa(tex, a + int2(1, 1), W, H, fl), f.x);
        ta = floor(lerp(x0, x1, f.y) + 0.5);
    } else {
        ta = nr_rt_texa(tex, (int2)floor(p), W, H, fl);
    }
    uint tfx = (fl >> 16) & 3u;
    float A = tfx == 0u ? min(floor(va * ta / 128.0), 255.0) : (tfx == 2u ? min(ta + va, 255.0) : ta);
    uint atst = fl & 7u;
    float aref = (float)((fl >> 8) & 255u);
    return atst == 2u ? A < aref : atst == 3u ? A <= aref : atst == 4u ? A == aref : atst == 5u ? A >= aref
         : atst == 6u ? A > aref : atst == 7u ? A != aref : atst == 1u;
}
// one shadow ray: true = blocked; wgt = how much (1, or a foliage hit's fade).  Two traces: the
// opaque casters (instance mask 1) over the whole length, ending at the first hit; then, only when
// that found nothing, the cut-out cards (mask 2) up to RTS.w (foliage, RTS.zw: a card's hit counts
// fully up to RTS.z along the ray and fades out at RTS.w -- the canopy far above the ground is painted
// into the art's own light, the leaves near a surface give its contact shadow), the closest card
// whose texel passes the alpha test (each committed hit shortens the search)
static bool RTP_dyn = false;   // (a characters-only ray: they stand on the ground, so 400 units reach any of them)
bool nr_rt_ray(float3 o, float3 d, uint mo, uint mc, out uint hitm, out float wgt)
{
    RayDesc r;
    r.Origin = o;
    r.Direction = d;
    r.TMin = 0.0;
    r.TMax = RTP_dyn ? min(RTP.x, 400.0) : RTP.x;
    hitm = 0u;
    wgt = 0.0;
    uint64_t mt = nr_rt_a64(asuint(RTM.x), asuint(RTM.y));
    {
        RayQuery<RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH | RAY_FLAG_FORCE_OPAQUE> q;
        if (RTP_dyn) q.TraceRayInline(g_tlasc, RAY_FLAG_NONE, mo, r);
        else q.TraceRayInline(g_tlas, RAY_FLAG_NONE, mo, r);
        q.Proceed();
        if (q.CommittedStatus() == COMMITTED_TRIANGLE_HIT) {
            wgt = 1.0;
            hitm = vk::RawBufferLoad<uint>(mt + (uint64_t)q.CommittedInstanceID() * 64u + 56u, 4);   // (the mesh id: $RG_RT_DBGID)
            return true;
        }
    }
    if (RTS.y == 1.0 || mc == 0u) return false;
    bool fade = RTS.w > RTS.z;
    if (fade) r.TMax = min(r.TMax, RTS.w);
    RayQuery<RAY_FLAG_NONE> q;
    if (RTP_dyn) q.TraceRayInline(g_tlasc, RAY_FLAG_NONE, mc, r);
    else q.TraceRayInline(g_tlas, RAY_FLAG_NONE, mc, r);
    while (q.Proceed()) {
        uint mfl;
        if (q.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE &&
            nr_rt_alpha_pass(q.CandidateInstanceID(), q.CandidatePrimitiveIndex(), q.CandidateTriangleBarycentrics(), mfl)) {
            q.CommitNonOpaqueTriangleHit();
            if (!fade || q.CandidateTriangleRayT() <= RTS.z) break;   // (fully blocked: no closer hit can matter)
        }
    }
    if (q.CommittedStatus() != COMMITTED_TRIANGLE_HIT) return false;
    wgt = fade ? 1.0 - saturate((q.CommittedRayT() - RTS.z) / (RTS.w - RTS.z)) : 1.0;
    hitm = vk::RawBufferLoad<uint>(mt + (uint64_t)q.CommittedInstanceID() * 64u + 56u, 4);
    return wgt > 0.0;
}
// (rt5) reflections (docs/RAYTRACING.md "RT5", the RT3 spike): the colour of a reflection ray's hit,
// from its instance's material row (nr_vulkan.cpp rt_mat with reflections on: m[7] bit 25 = a row,
// bit 26 = textured, m[15] = the material colour RGBA8): material colour x vertex colour / 128
// (VS_nr's 0x43AEC0), then the texture function with the texel (nearest).  The hit's own light is
// the art's (baked into the vertex colours / texture); (rt6) the game's fog on the hit: nr_rt_refl_look
float4 nr_rt_texel(uint64_t tex, int2 q, int W, int H, uint fl)
{
    q.x = (fl & 0x100000u) ? clamp(q.x, 0, W - 1) : ((q.x % W) + W) % W;
    q.y = (fl & 0x200000u) ? clamp(q.y, 0, H - 1) : ((q.y % H) + H) % H;
    uint t = vk::RawBufferLoad<uint>(tex + (uint64_t)(q.y * W + q.x) * 4u, 4);
    return float4((float)(t & 255u), (float)((t >> 8) & 255u), (float)((t >> 16) & 255u), (float)(t >> 24));
}
float3 nr_rt_hitcol(uint inst, uint prim, float2 bc, out bool ok)
{
    uint64_t m = nr_rt_a64(asuint(RTM.x), asuint(RTM.y)) + (uint64_t)inst * 64u;
    uint4 m0 = vk::RawBufferLoad<uint4>(m, 16), m1 = vk::RawBufferLoad<uint4>(m + 16u, 16);
    uint4 m2 = vk::RawBufferLoad<uint4>(m + 32u, 16), m3 = vk::RawBufferLoad<uint4>(m + 48u, 16);
    uint fl = m1.w;
    ok = (fl & 0x2000000u) != 0u;
    if (!ok) return float3(0.0, 0.0, 0.0);
    uint64_t vb = nr_rt_a64(m0.x, m0.y), ib = nr_rt_a64(m0.z, m0.w), tex = nr_rt_a64(m1.x, m1.y);
    uint64_t ip = ib + (uint64_t)prim * 12u;
    uint3 ix = uint3(vk::RawBufferLoad<uint>(ip, 4), vk::RawBufferLoad<uint>(ip + 4u, 4), vk::RawBufferLoad<uint>(ip + 8u, 4));
    float3 w = float3(1.0 - bc.x - bc.y, bc.x, bc.y);
    float4 c = float4((float)(m3.w & 255u), (float)((m3.w >> 8) & 255u), (float)((m3.w >> 16) & 255u), (float)(m3.w >> 24));
    if (fl & 0x80000u) {
        uint c0 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.x * 28u + 16u, 4);
        uint c1 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.y * 28u + 16u, 4);
        uint c2 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.z * 28u + 16u, 4);
        float4 v0 = float4((float)(c0 & 255u), (float)((c0 >> 8) & 255u), (float)((c0 >> 16) & 255u), (float)(c0 >> 24));
        float4 v1 = float4((float)(c1 & 255u), (float)((c1 >> 8) & 255u), (float)((c1 >> 16) & 255u), (float)(c1 >> 24));
        float4 v2 = float4((float)(c2 & 255u), (float)((c2 >> 8) & 255u), (float)((c2 >> 16) & 255u), (float)(c2 >> 24));
        c = floor(c * (v0 * w.x + v1 * w.y + v2 * w.z) / 128.0);
    }
    if ((fl & 0x4000000u) && tex != 0u) {
        int W = (int)(m1.z & 0xFFFFu), H = (int)(m1.z >> 16);
        uint u0 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.x * 28u + 12u, 4);
        uint u1 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.y * 28u + 12u, 4);
        uint u2 = vk::RawBufferLoad<uint>(vb + (uint64_t)ix.z * 28u + 12u, 4);
        float2 t0 = float2((float)((int)(u0 << 16) >> 16), (float)((int)u0 >> 16));
        float2 t1 = float2((float)((int)(u1 << 16) >> 16), (float)((int)u1 >> 16));
        float2 t2 = float2((float)((int)(u2 << 16) >> 16), (float)((int)u2 >> 16));
        float2 uv = (t0 * w.x + t1 * w.y + t2 * w.z) * (1.0 / 32768.0) * asfloat(m2.xy) + asfloat(m2.zw);
        float4 t = nr_rt_texel(tex, (int2)floor(uv * float2((float)W, (float)H)), W, H, fl);
        uint tfx = (fl >> 16) & 3u;
        c.rgb = tfx == 1u ? t.rgb : min(floor(c.rgb * t.rgb / 128.0) + (tfx >= 2u ? c.a : 0.0), 255.0);
    }
    return min(c.rgb, 255.0);
}
// a reflection ray from the pixel (mirror: the geometric normal turned to the camera, or (rt6, RTF.z)
// the interpolated vertex normal `sn` (curved metal reflects smoothly, not in flat facets), turned
// the same way and kept facing the camera, the ray kept above the surface; no roughness, so one
// ray has no noise and needs no filter), the closest hit of the map's casters (cut-out cards
// through the candidate loop) and the characters; on a hit the art's map texel `tex` moves to the
// hit's colour by RTR.y, on a miss it stays (the environment map is the sky / far surroundings).
// RTR.w: one ray per 2 x 2 quad (the tracer rotates per present), the others take its hit unless
// their position or direction differs (an edge).  Returns the hit's colour and (rt6) its distance
// in w (0: a miss)
float4 nr_rt_refl_hit(float3 wp, float3 gn, float3 sn, float2 px, out float cosv)
{
    float ln = length(gn);
    float3 n = ln > 0.0 ? gn / ln : float3(0.0, 1.0, 0.0);
    float3 v = wp - RTE.xyz;
    float dv = max(length(v), 1e-6);
    v /= dv;
    if (dot(n, v) > 0.0) n = -n;
    float3 rn = n;
    float ls = length(sn);
    if (RTF.z > 0.5 && ls > 0.0) {
        // (rt6) the vertex normal, on the camera's side of the face as the geometric one; at a
        // silhouette (facing away) bent until it faces the camera a little
        rn = sn / ls;
        if (dot(rn, n) < 0.0) rn = -rn;
        float fv = dot(rn, v);
        if (fv > -0.05) rn = normalize(rn - v * (fv + 0.05));
    }
    float3 d = reflect(v, rn);
    {
        // (rt6) never into the surface: a ray below the face is lifted along it
        float dn = dot(d, n);
        if (dn < 0.01) d = normalize(d + n * (0.01 - dn));
    }
    cosv = saturate(-dot(v, rn));
    uint2 pxi = (uint2)px;
    uint ql = (pxi.x & 1u) + 2u * (pxi.y & 1u), qt = (uint)RTH.z & 3u;
    bool self = true;
    if (((uint)RTR.w & 1u) != 0u) {
        const float3 wt = QuadReadLaneAt(wp, qt), dt = QuadReadLaneAt(d, qt), dw = wp - wt;
        const float tl = 0.004 * dv + 0.5;
        self = ql == qt || dot(dw, dw) > tl * tl || dot(dt, d) < 0.995;
    }
    float4 h = float4(0.0, 0.0, 0.0, 0.0);
    {
        RayDesc r;
        r.Origin = wp + n * (RTP.y + RTP.z * dv);
        r.Direction = d;
        r.TMin = 0.0;
        r.TMax = RTR.z;
        RayQuery<RAY_FLAG_NONE> q;
        // (every lane runs the query when quad sharing: the tracer's result is read below; a
        // non-tracer's ray is cut to nothing)
        if (!self) r.TMax = 0.0;
        q.TraceRayInline(g_tlas, RAY_FLAG_NONE, (uint)RTX.z & 15u, r);
        while (q.Proceed()) {
            uint mfl;
            if (q.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE &&
                nr_rt_alpha_pass(q.CandidateInstanceID(), q.CandidatePrimitiveIndex(), q.CandidateTriangleBarycentrics(), mfl))
                q.CommitNonOpaqueTriangleHit();
        }
        if (self && q.CommittedStatus() == COMMITTED_TRIANGLE_HIT) {
            bool ok;
            float3 hc = nr_rt_hitcol(q.CommittedInstanceID(), q.CommittedPrimitiveIndex(), q.CommittedTriangleBarycentrics(), ok);
            if (ok) h = float4(hc, max(q.CommittedRayT(), 1e-3));
        }
    }
    if (((uint)RTR.w & 1u) != 0u) {
        const float4 ht = QuadReadLaneAt(h, qt);
        if (!self) h = ht;
    }
    return h;
}
// (rt6) the hit's colour as the mirror sees it: the game's fog (R[9]: fog = x + w * clip w,
// clamped to [z, y], 255 clear; the GS fog colour) over the hit's distance from the mirror (clip
// w per unit of eye distance: wn.w), RTF.x; and the weight of the hit (1 - the distance fade:
// from RTF.y x the ray's length to its end, where the hits stop, so their edge does not show)
float4 nr_rt_refl_look(float4 h, float fk)
{
    float3 c = h.rgb;
    if (RTF.x > 0.5) {
        float f = clamp(R[9].x + R[9].w * h.w * (RTF.w > 0.0 ? RTF.w : fk), R[9].z, R[9].y);
        uint fc = PS_FOGCOL;
        float3 fcol = float3(fc & 255u, (fc >> 8) & 255u, (fc >> 16) & 255u);
        c = floor((c * f + fcol * (255.0 - f)) / 256.0);
    }
    float wt = 1.0;
    if (RTF.y < 1.0) {
        float a = RTF.y * RTR.z;
        wt = 1.0 - smoothstep(a, RTR.z, h.w);
    }
    return float4(c, wt);
}
// RTR.x 1: an environment / reflection map's texel moves to the hit's colour x the texel / 128 (by RTR.y); a miss keeps it
float3 nr_rt_refl(float3 wp, float3 gn, float4 wn, float3 tex, float2 px)
{
    float cv;
    float4 h = nr_rt_refl_hit(wp, gn, wn.xyz, px, cv);
    if (RTP.w > 0.0 || ((uint)RTR.w & 2u) != 0u) return h.w > 0.0 ? floor(tex * 0.25 + float3(0.0, 96.0, 160.0)) : floor(tex * 0.5 + float3(96.0, 0.0, 0.0));   // (debug: cyan hit, red miss)
    // (the map's texel is the art's reflectance x its painted surroundings: the hit takes the place of
    // the surroundings at a mid grey 128 = 1.0, so the art's tint and strength stay -- a plain
    // replacement turned the blue-glass and dark-metal maps into bright copies of the floor)
    if (!(h.w > 0.0)) return tex;
    float4 lk = nr_rt_refl_look(h, wn.w);
    float3 hv = min(lk.rgb * tex / 128.0, 255.0);
    if (RTG.x > 0.0) {
        // (rt7) the brightness floor: in a dark place the hit (dark walls) would turn the art's bright
        // painted metal dull; below RTG.x x the painted texel's luminance the reflection blends
        // toward the painted texel until it reaches that level (bright hits keep the scene)
        const float3 Y = float3(0.299, 0.587, 0.114);
        const float lt = dot(tex, Y), lh = dot(hv, Y), lf = RTG.x * lt;
        if (lh < lf) hv = lerp(hv, tex, saturate((lf - lh) / max(lt - lh, 1e-3)));
    }
    return floor(lerp(tex, hv, saturate(RTR.y) * lk.w));
}
// RTR.x 2 (water: a blended, scrolling, non-Z-writing layer facing up): the layer's colour moves
// to the hit's by RTR.y x Schlick's Fresnel term (water, F0 0.02): little looking down, most at
// grazing angles; a miss keeps it (the art's water already shows the sky)
float3 nr_rt_refl_water(float3 wp, float3 gn, float4 wn, float3 col, float2 px)
{
    float cv, gl = length(gn);
    float4 h = nr_rt_refl_hit(wp, gn, wn.xyz, px, cv);   // (every lane: the quad exchange inside)
    if (!(gl > 0.0) || abs(gn.y) < 0.7 * gl) return col;   // (not a level surface: a waterfall, a bank)
    float f = 0.02 + 0.98 * pow(1.0 - cv, 5.0);
    if (RTP.w > 0.0 || ((uint)RTR.w & 2u) != 0u) return h.w > 0.0 ? floor(col * 0.25 + float3(0.0, 96.0, 160.0) * f + float3(0.0, 32.0, 0.0)) : floor(col * 0.5 + float3(96.0, 0.0, 0.0));
    if (!(h.w > 0.0)) return col;
    float4 lk = nr_rt_refl_look(h, wn.w);
    return floor(lerp(col, lk.rgb, saturate(RTR.y * f) * lk.w));
}
// RT2f, the penumbra filter (docs/RAYTRACING.md "Penumbra filter"; our own, after SVGF's temporal
// stage, CC0): the occluded fraction of the map's casters (one dithered ray per pixel) is
// accumulated over presents.  The pixel's world position is projected with the previous present's
// camera (RTV); the history there (2 x 2 taps, bilinear weights; one word per pixel: mean 10 bits,
// length 6 bits, the eye distance as a half float) counts where its stored eye distance matches
// this point's distance to that camera (2 % + 2 units: disocclusions, moving objects and other
// layers drop out).  New sample weight max(1 / length, 0.1).  Output = the accumulated mean,
// written as this present's history.  (Characters move: their shadow is traced apart, unfiltered.)
struct NrRtHist { float m1, len; bool ok; };
// (rt9) a moving receiver (RTMV.x: a character part) is reprojected from where the same surface point
// was in the previous present (RT_wq, VS_nr's wq: its previous pose and object rows), so the history
// follows the character; the stored eye distance must match that point's distance to the previous
// camera within a tighter tolerance (RTN.xy: the motion is exact, so a different surface there -- a
// disocclusion, the background a limb uncovered -- drops out); no previous pose (RTMV.z): no history
static float3 RT_wq = float3(0.0, 0.0, 0.0);
static bool RT_mv = false;
float nr_rt_htol(float dp) { return RT_mv ? dp * RTN.x + RTN.y : dp * 0.02 + 2.0; }
NrRtHist nr_rt_hist(float3 wp0, uint2 px, uint ch)
{
    NrRtHist h;
    h.m1 = 0.0; h.len = 0.0; h.ok = false;
    if (RTH.x <= 0.0 || RTQ.w <= 0.0 || RTMV.z > 0.5) return h;
    const float3 wp = RT_mv ? RT_wq : wp0;
    float4 pc = RTV[0] * wp.x + RTV[1] * wp.y + RTV[2] * wp.z + RTV[3];
    if (!(pc.w > 0.0)) return h;
    float2 pp = (pc.xy / pc.w - R[11].xy) * RTH.y - 0.5;   // (the previous present's pixel, this target's mapping)
    float dp = length(wp - RTQ.xyz), tol = nr_rt_htol(dp);
    uint W, H, st = (uint)max(RTA.z, 1.0);
    g_rthp.GetDimensions(W, H);
    W /= st;
    int2 c = (int2)floor(pp);
    float2 f = pp - (float2)c;
    float ws = 0.0, a1 = 0.0, al = 0.0;
    [unroll] for (int j = 0; j <= 1; j++)
        [unroll] for (int i = 0; i <= 1; i++) {
            int2 q = c + int2(i, j);
            if (q.x < 0 || q.y < 0 || q.x >= (int)W || q.y >= (int)H) continue;
            uint w0 = g_rthp[uint2((uint)q.x * st + ch, (uint)q.y)];
            if (!(abs(f16tof32(w0 >> 16) - dp) < tol) || (w0 & 0xFC00u) == 0u) continue;
            float wt = (i ? f.x : 1.0 - f.x) * (j ? f.y : 1.0 - f.y) + 1e-3;
            ws += wt;
            a1 += wt * (float)(w0 & 1023u);
            al += wt * (float)((w0 >> 10) & 63u);
        }
    if (ws < 0.05) return h;
    h.m1 = a1 / (ws * 1023.0);
    h.len = al / ws;
    h.ok = true;
    return h;
}
// (rt7) both words of a pixel's history (0 the shadow, 1 AO) in one pass: one projection, the same
// four taps (the AO path reads both, the shadow then takes word 0 from here)
void nr_rt_hist2(float3 wp0, uint2 px, out NrRtHist h0, out NrRtHist h1)
{
    h0.m1 = 0.0; h0.len = 0.0; h0.ok = false;
    h1 = h0;
    if (RTH.x <= 0.0 || RTQ.w <= 0.0 || RTMV.z > 0.5) return;
    const float3 wp = RT_mv ? RT_wq : wp0;
    float4 pc = RTV[0] * wp.x + RTV[1] * wp.y + RTV[2] * wp.z + RTV[3];
    if (!(pc.w > 0.0)) return;
    float2 pp = (pc.xy / pc.w - R[11].xy) * RTH.y - 0.5;
    float dp = length(wp - RTQ.xyz), tol = nr_rt_htol(dp);
    uint W, H, st = (uint)max(RTA.z, 1.0);
    g_rthp.GetDimensions(W, H);
    W /= st;
    int2 c = (int2)floor(pp);
    float2 f = pp - (float2)c;
    float2 ws = 0.0, a1 = 0.0, al = 0.0;
    [unroll] for (int j = 0; j <= 1; j++)
        [unroll] for (int i = 0; i <= 1; i++) {
            int2 q = c + int2(i, j);
            if (q.x < 0 || q.y < 0 || q.x >= (int)W || q.y >= (int)H) continue;
            float wt = (i ? f.x : 1.0 - f.x) * (j ? f.y : 1.0 - f.y) + 1e-3;
            [unroll] for (uint ch = 0u; ch < 2u; ch++) {
                uint w0 = g_rthp[uint2((uint)q.x * st + ch, (uint)q.y)];
                if (!(abs(f16tof32(w0 >> 16) - dp) < tol) || (w0 & 0xFC00u) == 0u) continue;
                ws[ch] += wt;
                a1[ch] += wt * (float)(w0 & 1023u);
                al[ch] += wt * (float)((w0 >> 10) & 63u);
            }
        }
    if (ws.x >= 0.05) { h0.m1 = a1.x / (ws.x * 1023.0); h0.len = al.x / ws.x; h0.ok = true; }
    if (ws.y >= 0.05) { h1.m1 = a1.y / (ws.y * 1023.0); h1.len = al.y / ws.y; h1.ok = true; }
}
float nr_rt_filter(float occ, bool keep, NrRtHist h, float3 wp, uint2 px, uint ch)
{
    if (RTH.x <= 0.0) return occ;
    float m1 = occ, len = 1.0;
    if (keep) {
        m1 = h.m1; len = h.len;
    } else if (h.ok) {
        m1 = lerp(h.m1, occ, max(1.0 / (h.len + 1.0), RT_mv ? RTN.w : 0.1));
        len = min(h.len + 1.0, 32.0);
    }
    uint W, H, st = (uint)max(RTA.z, 1.0);
    g_rth.GetDimensions(W, H);
    if (px.x * st + ch < W && px.y < H && !((uint)RTH.w & 4u))
        g_rth[uint2(px.x * st + ch, px.y)] = (uint)(saturate(m1) * 1023.0 + 0.5) | ((uint)len << 10) | (f32tof16(length(wp - RTE.xyz)) << 16);
    return m1;
}
// shadow rays from the receiver's pixel to the key light (docs/RAYTRACING.md "Shadows"): only surfaces
// whose visible side faces the light are tested (the baked lighting already darkens the others);
// RTM.z rays spread over the light's disc (radius RTM.w) with a per-pixel rotation (interleaved
// gradient noise) make the penumbra soft; the occluded fraction scales the colour towards RTC before
// fog, so fogged distance keeps the original look
// (rt9) the mean of a noisy per-pixel term over the pixel's 2 x 2 quad, on the same surface only (each
// neighbour within 0.4 % of the eye distance + 0.5 units and turned the same way): a moving receiver's
// one-ray samples, four independent rotations, before the history (all lanes reach it)
float nr_rt_qavg(float x, bool ok, float3 wp, float3 n, float dv, out float mn, out float mx)
{
    const float tl = 0.004 * dv + 0.5;
    float s = x, c = 1.0;
    mn = x; mx = x;
    [unroll] for (uint k = 0u; k < 3u; k++) {
        const float xo = k == 0u ? QuadReadAcrossX(x) : k == 1u ? QuadReadAcrossY(x) : QuadReadAcrossDiagonal(x);
        const float3 po = k == 0u ? QuadReadAcrossX(wp) : k == 1u ? QuadReadAcrossY(wp) : QuadReadAcrossDiagonal(wp);
        const float3 no = k == 0u ? QuadReadAcrossX(n) : k == 1u ? QuadReadAcrossY(n) : QuadReadAcrossDiagonal(n);
        const uint oo = k == 0u ? QuadReadAcrossX(ok ? 1u : 0u) : k == 1u ? QuadReadAcrossY(ok ? 1u : 0u) : QuadReadAcrossDiagonal(ok ? 1u : 0u);
        const float3 dw = po - wp;
        if (oo != 0u && dot(dw, dw) <= tl * tl && dot(no, n) >= 0.9) { s += xo; c += 1.0; mn = min(mn, xo); mx = max(mx, xo); }
    }
    return ok ? s / c : x;
}
// (rt9) a moving receiver's history clamped to its quad's current samples (+-RTN margin): what the
// history remembers of a pose that moved on (a swinging leg's AO, a shadow edge crossing an arm)
// cannot outlast the current samples -- the ghost goes, the averaging stays where they agree
void nr_rt_hclamp(inout NrRtHist h, float mn, float mx, bool on)
{
    if (on && h.ok) h.m1 = clamp(h.m1, mn - RTO.x, mx + RTO.x);
}
// (rt9) a moving receiver's samples: white noise per pixel (a hash) stepped per present by the golden
// ratio (each pixel's own sequence is stratified in time); interleaved gradient noise, the static
// receivers' pattern, left a diagonal lattice on characters once their quads were averaged and the
// history followed them
float nr_rt_hash(uint2 p, uint k)
{
    uint h = p.x * 0x8DA6B343u ^ p.y * 0xD8163841u ^ k * 0xCB1AB31Fu;
    h ^= h >> 16; h *= 0x7FEB352Du; h ^= h >> 15; h *= 0x846CA68Bu; h ^= h >> 16;
    return (float)(h >> 8) * (1.0 / 16777216.0);
}
float nr_rt_mvrand(float2 px, uint k, float step)
{
    return frac(nr_rt_hash((uint2)px, k) + step * fmod(RTH.z, 1024.0));
}
float3 nr_rt_shade(float3 wp, float3 gn, float3 col, float2 px, float3 wq)
{
    RT_wq = wq;
    RT_mv = RTMV.x > 0.5;
    // RTP.w 5 ($RG_RT_DBGMV=1, with RG_RT=2): the motion -- red = |wq - wp| (255 = 8 units), green 255 = a
    // moving receiver with its previous pose, blue 255 = one without (no history)
    if (RTP.w > 4.5) return float3(floor(saturate(length(wq - wp) / 8.0) * 255.0), RT_mv ? 255.0 : 0.0, RTMV.z > 0.5 ? 255.0 : 0.0);
    // (rt8) a character receiver (RTX.z 3: its reflection rays see the map only): characters move every
    // frame, so the penumbra filter's history (reprojected by the camera alone) rarely holds and one
    // jittered ray per pixel showed as a dither / halftone pattern on them; they take the AO-free,
    // unjittered shadow ray (a stable edge) -- docs/RAYTRACING.md "RT8", the characters' pattern
    const bool chrold = ((uint)RTI.w & 2u) != 0u;   // ($RG_RT_CHRPAT=0: rt7's behaviour, a control)
    // (rt9) with motion vectors (RTMV.w bit 0, $RG_RT_MV): the history follows the character, so its AO
    // and soft shadow come back (chrmv); bit 1: the noisy terms averaged over the quad first
    const bool chrmv = RTX.z < 7.5 && ((uint)RTMV.w & 1u) != 0u && !chrold;
    const bool chrq = chrmv && ((uint)RTMV.w & 2u) != 0u;
    const bool chrR = RTX.z < 7.5 && !chrold && !chrmv;
    float ln = length(gn);
    // (rt4: no early return before the quad exchange below -- a degenerate normal is a flag)
    const bool ngood = ln > 0.0;
    const float3 col0 = col;
    float3 n = ngood ? gn / ln : float3(0.0, 1.0, 0.0);
    float3 v = RTE.xyz - wp;
    if (dot(n, v) < 0.0) n = -n;
    if (RTP.w > 2.5) {
        // RTP.w 3 ($RG_RT_DBGVIS=1, a control of the candidate loop): a ray from the camera to this
        // pixel; green = the first hit is this surface (within 2 % of the distance), red = something
        // nearer (an alpha-tested card the raster shows as see-through: the loop disagrees with the
        // alpha test), blue = no hit (this surface is not a caster)
        float dv = length(v);
        RayDesc r;
        r.Origin = RTE.xyz;
        r.Direction = -v / dv;
        r.TMin = 0.0;
        r.TMax = dv * 1.05 + 4.0;
        RayQuery<RAY_FLAG_NONE> q;
        q.TraceRayInline(g_tlas, RAY_FLAG_NONE, 0xFF, r);
        while (q.Proceed()) {
            uint mfl;
            if (q.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE &&
                nr_rt_alpha_pass(q.CandidateInstanceID(), q.CandidatePrimitiveIndex(), q.CandidateTriangleBarycentrics(), mfl))
                q.CommitNonOpaqueTriangleHit();
        }
        if (q.CommittedStatus() != COMMITTED_TRIANGLE_HIT) return floor(col * 0.5 + float3(0.0, 0.0, 128.0));
        return q.CommittedRayT() < dv * 0.98 - 2.0 ? floor(col * 0.5 + float3(128.0, 0.0, 0.0)) : floor(col * 0.5 + float3(0.0, 128.0, 0.0));
    }
    float3 o = wp + n * (RTP.y + RTP.z * length(v));
    float aov = 0.0;   // (rt4) the occlusion, applied with the sun's shadow below
    NrRtHist hs0;      // (rt7) the shadow's history word, read with AO's (RTG.w 1: nr_rt_hist2)
    hs0.m1 = 0.0; hs0.len = 0.0; hs0.ok = false;
    bool hs0ok = false;
    if (RTA.x > 0.0 && !chrR) {
        // RT2e, ambient occlusion (first pass, off by default: graphics.raytracing = shadows + AO):
        // one cosine-weighted ray of RTA.x units around the normal against the opaque casters (map
        // and characters), occlusion falling off with the hit distance, accumulated by the
        // penumbra filter's history (word 1); the colour scales by 1 - strength x occlusion,
        // before the sun's shadow and fog
        float2 fq = floor(px) + 7.31 * fmod(RTH.z, 64.0);
        float u1 = frac(52.9829189 * frac(dot(fq, float2(0.06711056, 0.00583715))));
        float u2 = frac(52.9829189 * frac(dot(fq + float2(17.0, 3.0), float2(0.06711056, 0.00583715))));
        if (chrmv && ((uint)RTMV.w & 32u)) { u1 = nr_rt_mvrand(px, 1u, 0.6180340); u2 = nr_rt_mvrand(px, 2u, 0.7548777); }
        float z = 2.0 * u1 - 1.0, ph = 6.2831853 * u2, rr = sqrt(max(1.0 - z * z, 0.0));
        float3 ad = normalize(n + float3(rr * cos(ph), rr * sin(ph), z) * 0.999);
        // (rt7) RTG.y: one AO ray per 2 x 2 quad (as the shadow's quad trace, the tracer rotating per
        // present so the history averages the four); a pixel whose tracer is far from it or turned
        // another way traces itself.  Every lane of the quad reaches the exchange
        const bool aq = RTG.y > 0.5;
        // (the history first: a pixel shares its quad's ray only once its own history has settled --
        // a young history (a moving character's surroundings, a disocclusion) showed the shared
        // samples as a 2 x 2 dot mesh, shots/aoquad_map_juraika_4400.png)
        const bool ahist = RTH.x > 0.0 && !((uint)RTG.z & 2u);
        NrRtHist h1;
        h1.m1 = 0.0; h1.len = 0.0; h1.ok = false;
        if (ahist && ngood) {
            if (RTG.w > 0.5) { nr_rt_hist2(wp, (uint2)px, hs0, h1); hs0ok = true; }
            else h1 = nr_rt_hist(wp, (uint2)px, 1u);
        }
        bool aself = ngood;
        const uint aql = ((uint)px.x & 1u) + 2u * ((uint)px.y & 1u), aqt = (uint)RTH.z & 3u;
        if (aq) {
            const bool tw = QuadReadLaneAt(ngood, aqt);
            const float3 wt = QuadReadLaneAt(wp, aqt), nt = QuadReadLaneAt(n, aqt), dw = wp - wt;
            const float tl = 0.004 * length(v) + 0.5;
            aself = ngood && (aql == aqt || !tw || !(h1.ok && h1.len >= 8.0) || dot(dw, dw) > tl * tl || dot(nt, n) < 0.9);
        }
        float ao = 0.0;
        // (rt9) a moving character part: RTN.z rays (stratified: R2 steps from the pixel's sample);
        // RTMV.w bit 2: its AO rays see the characters too (mask 5)
        const uint nao = chrmv || ((uint)RTMV.w & 8u) ? (uint)clamp(RTN.z, 1.0, 16.0) : 1u;   // (bit 3: measurement, every receiver)
        const uint aom = chrold || (chrmv && ((uint)RTMV.w & 4u)) ? 0x05 : 0x01;
        if (aself && !((uint)RTG.z & 1u)) {
            [loop] for (uint ka = 0u; ka < nao; ka++) {
                float3 da = ad;
                if (ka > 0u) {
                    const float v1 = frac(u1 + 0.7548777 * (float)ka), v2 = frac(u2 + 0.5698403 * (float)ka);
                    const float z2 = 2.0 * v1 - 1.0, ph2 = 6.2831853 * v2, rr2 = sqrt(max(1.0 - z2 * z2, 0.0));
                    da = normalize(n + float3(rr2 * cos(ph2), rr2 * sin(ph2), z2) * 0.999);
                }
                RayDesc r;
                r.Origin = o;
                r.Direction = da;
                r.TMin = 0.0;
                r.TMax = RTA.x;
                RayQuery<RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH | RAY_FLAG_FORCE_OPAQUE> q;
                q.TraceRayInline(g_tlas, RAY_FLAG_NONE, aom, r);   // (rt8: the map only; a moving character's AO on the ground has no history: halftone dots)
                q.Proceed();
                ao += q.CommittedStatus() == COMMITTED_TRIANGLE_HIT ? 1.0 - q.CommittedRayT() / RTA.x : 0.0;
            }
            ao /= (float)nao;
        }
        float amn = 0.0, amx = 1.0;
        if (chrq) ao = nr_rt_qavg(ao, aself && !((uint)RTG.z & 1u), wp, n, length(v), amn, amx);
        nr_rt_hclamp(h1, amn, amx, chrq && ((uint)RTMV.w & 16u) != 0u);
        if (aq) {
            const float at = QuadReadLaneAt(ao, aqt);
            if (ngood && !aself) ao = at;
        }
        if (ngood) {
            if (ahist) ao = nr_rt_filter(ao, false, h1, wp, (uint2)px, 1u);
            if (RTP.w > 0.0 && RTA.w < 0.0) return floor(float3(255.0, 255.0, 255.0) * (1.0 - ao));   // ($RG_RT_AODBG=1: the occlusion alone)
            aov = ao;
        }
    }
    float3 L = RTL.xyz;
    const bool facing = ngood && dot(n, L) > 0.0;
    uint nr = (uint)max(RTM.z, 1.0);
    if (chrmv) nr = max(nr, (uint)clamp(RTO.y, 1.0, 16.0));   // (rt9) a moving character part's own shadow rays per pixel (RTO.y)
    float occ = 0.0;
    uint hitm = 0u, hm;
    uint2 pxi = (uint2)px;
    // RTH.w bits: 1 half rate ($RG_RT_HALF); $RG_RT_FEXP measurement controls: 2 no history read, 4 no history write, 8 no
    // characters-only ray, 16 no map rays
    const uint fexp = (uint)RTH.w;
    // RTP.w 4 ($RG_RT_DBGHIST=1, with RG_RT=2): green = the filter found a history, red = none
    if (RTP.w > 3.5 && facing) { NrRtHist h0 = nr_rt_hist(wp, pxi, 0u); nr_rt_filter(0.0, false, h0, wp, pxi, 0u); return h0.ok ? floor(col * 0.5 + float3(0.0, 128.0, 0.0)) : floor(col * 0.5 + float3(128.0, 0.0, 0.0)); }
    // with the filter, the map's casters (masks 1 / 2) are filtered; the characters (4 / 8) move,
    // so a history of their shadow would trail: one ray of their own, unfiltered (a hard-ish,
    // dithered edge right under them), combined after the filter
    const bool split = RTH.x > 0.0;
    uint mo = split ? ((uint)RTX.x & 3u) : (uint)RTX.x, mc = split ? ((uint)RTX.y & 3u) : (uint)RTX.y;
    // a Vogel disc over the light (golden-angle steps), rotated and offset in radius per pixel by
    // interleaved gradient noise (with the filter on, moved per present so the history averages
    // different directions): one ray dithers the penumbra, more rays average it
    float3 tb = normalize(abs(L.y) < 0.9 ? cross(L, float3(0.0, 1.0, 0.0)) : cross(L, float3(1.0, 0.0, 0.0)));
    float3 bb = cross(L, tb);
    float2 fp = floor(px);
    float fo = split ? 5.588238 * fmod(RTH.z, 64.0) : 0.0;
    float rot = 6.2831853 * frac(52.9829189 * frac(dot(fp + fo, float2(0.06711056, 0.00583715))));
    float rof = frac(52.9829189 * frac(dot(fp + float2(5.0, 11.0) + fo * 1.618034, float2(0.06711056, 0.00583715))));
    if (chrmv && ((uint)RTMV.w & 32u)) { rot = 6.2831853 * nr_rt_mvrand(px, 3u, 0.6180340); rof = nr_rt_mvrand(px, 4u, 0.5698403); }
    float3 d0 = RTM.w <= 0.0 ? L : normalize(L + (tb * cos(rot) + bb * sin(rot)) * (sqrt(rof / (float)nr) * RTM.w));
    // half rate (RTH.w bit 0, $RG_RT_HALF=1; bit 5 too: quarter rate, $RG_RT_HALF=2): in every other
    // 8 x 8 tile (alternating per present; quarter: 3 of 4) a pixel with a settled history (4
    // presents or more) reuses it instead of tracing the map
    NrRtHist hh;
    hh.m1 = 0.0; hh.len = 0.0; hh.ok = false;
    bool reuse = false;
    // (RTH.w bit 5: quarter rate, each tile of a 2 x 2 group traces every fourth present)
    const uint tq = (fexp & 32u) ? ((((pxi.x >> 3u) & 1u) + 2u * ((pxi.y >> 3u) & 1u) + (uint)RTH.z) & 3u)
                                 : (((pxi.x >> 3u) + (pxi.y >> 3u) + (uint)RTH.z) & 1u);
    if (facing && split && (fexp & 1u) && tq != 0u && !chrq) {
        if (hs0ok) hh = hs0; else hh = nr_rt_hist(wp, pxi, 0u);
        reuse = hh.ok && hh.len >= 4.0;
    }
    // RTH.w bit 6 (rt4, $RG_RT_QUAD: internal resolution 3x and up): one map trace per 2 x 2 pixel
    // quad, the tracing pixel rotating per present (the filter's history then averages the four);
    // a pixel whose tracer is far from it (an edge: 0.4 % of the eye distance + 0.5 units), faces
    // away, reuses its history or is not facing traces itself.  All lanes of a quad reach the
    // exchange (no return before it; discarded pixels are demoted helpers)
    const bool want = facing && !reuse && !(fexp & 16u);
    bool self = want;
    uint ql = (pxi.x & 1u) + 2u * (pxi.y & 1u), qt = (uint)RTH.z & 3u;
    if ((fexp & 64u) != 0u && !chrq) {
        const bool tw = QuadReadLaneAt(want, qt);
        const float3 wt = QuadReadLaneAt(wp, qt), dw = wp - wt;
        const float tl = 0.004 * length(v) + 0.5;
        self = want && (ql == qt || !tw || dot(dw, dw) > tl * tl);
    }
    if (reuse || (fexp & 16u)) {   // (16: measurement, no map rays at all)
        occ = hh.m1;
    } else if (!self) {
    } else if (RTM.w <= 0.0 || chrR) {
        float wg;
        nr_rt_ray(o, L, mo, mc, hitm, wg);
        occ = wg;
    } else {
        [loop] for (uint k = 0u; k < nr; k++) {
            float rr = sqrt(((float)k + rof) / (float)nr) * RTM.w;
            float th = rot + 2.39996323 * (float)k;
            float3 d = k == 0u ? d0 : normalize(L + (tb * cos(th) + bb * sin(th)) * rr);
            float wg;
            if (nr_rt_ray(o, d, mo, mc, hm, wg)) hitm = hm;
            occ += wg;
        }
        occ /= (float)nr;
    }
    if ((fexp & 64u) != 0u && !chrq) {
        const float ot = QuadReadLaneAt(occ, qt);
        if (want && !self) occ = ot;
    }
    float smn = 0.0, smx = 1.0;
    if (chrq) occ = nr_rt_qavg(occ, self && !reuse, wp, n, length(v), smn, smx);
    // (rt4) ambient occlusion darkens the ambient part of the baked light: full on faces turned
    // away from the sun or in its shadow, RTA.w of it where the sun lights the face (its direct
    // light is not occluded by what is near; $RG_RT_AO_LIT)
    if (!facing) { col = floor(col * (1.0 - RTA.y * aov)); return !ngood ? col0 : RTP.w > 0.0 ? floor(col * 0.75 + float3(0.0, 0.0, 64.0)) : col; }
    // (the history after the rays: nothing the rays do waits for its loads)
    if (split) {
        if (!reuse) { if (hs0ok) hh = hs0; else hh = nr_rt_hist(wp, pxi, 0u); }
        if (fexp & 2u) hh.ok = false;
        nr_rt_hclamp(hh, smn, smx, chrq && ((uint)RTMV.w & 16u) != 0u && !reuse);
        occ = nr_rt_filter(occ, reuse, hh, wp, pxi, 0u);
    }
    bool nearc = false;
    [unroll] for (uint b = 0u; b < 8u; b++) {
        // the segment o + L t, t in [0, 400], against sphere b
        float3 oc = RTB[b].xyz - o;
        float t = clamp(dot(oc, L), 0.0, 400.0);
        float3 e = oc - L * t;
        nearc = nearc || (RTB[b].w > 0.0 && dot(e, e) <= RTB[b].w * RTB[b].w);
    }
    if (split && nearc && ((uint)RTX.x & 12u) != 0u && !(fexp & 8u)) {
        float wg;
        RTP_dyn = true;
        // (along L itself: a stable hard edge; a dithered one would crawl as the character moves)
        if (nr_rt_ray(o, L, (uint)RTX.x & 12u, (uint)RTX.y & 12u, hm, wg)) { hitm = hm; occ = max(occ, wg); }
        RTP_dyn = false;
    }
    if (RTS.x >= 0.0) {
        uint nt = WaveActiveCountBits(true), ns = WaveActiveCountBits(occ > 0.5);
        if (WaveIsFirstLane()) {
            uint a = (uint)RTS.x * 8u;
            g_rtstat.InterlockedAdd(a, nt);
            g_rtstat.InterlockedAdd(a + 4u, ns);
        }
    }
    // RTP.w 2 ($RG_RT_DBGID=1): the hit instance's mesh id as colour (R low byte, G high byte, B 255)
    if (RTP.w > 1.5 && occ > 0.0) return float3((float)(hitm & 255u), (float)((hitm >> 8) & 255u), 255.0);
    if (RTP.w > 0.0) return lerp(floor(col * 0.75 + float3(0.0, 64.0, 0.0)), floor(col * 0.5 + float3(128.0, 0.0, 128.0)), occ);
    if (aov > 0.0) col = floor(col * (1.0 - RTA.y * aov * lerp(saturate(RTA.w), 1.0, occ)));
    return floor(lerp(col, col * RTC.rgb, occ));
}
#endif

#ifdef NR_RT
// (rt8) emissive lights (docs/RAYTRACING.md "RT8"): the frame's list of emitters (tagged lamps,
// screens, crystals, glow sprites; nr_emi.h) as spheres: each adds colour x r^2 / (d^2 + r^2) x the
// cosine (wrapped past the horizon by the sphere's size r / d) x a window to its reach.  The two
// strongest are tested with a shadow ray to the emitter's sphere (map opaque casters and the
// characters, RTX.x's masks); the rest add unshadowed.  No noise, so no history.
// one light's contribution at (wp, n); a.xyz position, a.w radius, c.rgb colour, c.w reach
float3 nr_rt_emi_one(float4 a, float4 c, float3 wp, float3 n)
{
    const float3 d = a.xyz - wp;
    const float d2 = dot(d, d);
    if (d2 >= c.w * c.w) return float3(0.0, 0.0, 0.0);
    const float dl = sqrt(d2);
    const float3 l = d / max(dl, 0.001);
    const float sr = a.w / max(dl, a.w);
    const float cw = saturate((dot(n, l) + sr) / (1.0 + sr));
    const float q = d2 / (c.w * c.w);
    return c.rgb * (a.w * a.w / (d2 + a.w * a.w) * cw * (1.0 - q) * (1.0 - q));
}
// a shadow ray from o to light a's sphere: 1 = blocked
float nr_rt_emi_ray(float4 a, float3 o)
{
    const float3 d = a.xyz - o;
    const float dl = length(d);
    const float tmax = dl - a.w;
    if (!(tmax > 1.0)) return 0.0;
    RayDesc r;
    r.Origin = o;
    r.Direction = d / dl;
    r.TMin = 0.0;
    r.TMax = tmax;
    RayQuery<RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH | RAY_FLAG_FORCE_OPAQUE> qr;
    qr.TraceRayInline(g_tlas, RAY_FLAG_NONE, (uint)RTX.x & 5u, r);
    qr.Proceed();
    return qr.CommittedStatus() == COMMITTED_TRIANGLE_HIT ? 1.0 : 0.0;
}
// the two strongest of (y0, i0) / (y1, i1) and another pair (the quad merge below)
void nr_rt_emi_top2(inout float b0, inout uint i0, inout float b1, inout uint i1, float c0, uint j0, float c1, uint j1)
{
    [unroll] for (uint k = 0u; k < 2u; k++) {
        const float y = k == 0u ? c0 : c1;
        const uint j = k == 0u ? j0 : j1;
        if (j == 0xFFFFFFFFu || j == i0 || j == i1) continue;
        if (y > b0) { b1 = b0; i1 = i0; b0 = y; i0 = j; }
        else if (y > b1) { b1 = y; i1 = j; }
    }
}
// (rt9) the cost (docs/RAYTRACING.md "RT9"): RTJ.xy (as uint) the draw's light mask (lights whose reach
// meets the draw's world box, nr_vulkan.cpp emi_mask; all set: no culling); RTJ.z bit 0: the quad
// shares the work -- each of the 2 x 2 pixels sums a quarter of the lights at its own position, the
// sums and the two strongest lights are exchanged, and each strongest light gets two shadow rays
// (the diagonal pixels) instead of four; a quad whose pixels lie on different surfaces (an edge:
// farther apart than 4 x 0.4 % of the eye distance + 0.5 units, or turned another way) evaluates
// every light per pixel as rt8.  Every lane reaches the exchanges (no early return)
float3 nr_rt_emi(float3 wp, float3 gn, float2 px)
{
    const uint cnt = (uint)RTI.z;
    const float ln = length(gn);
    const bool ok = cnt > 0u && ln > 0.0;
    float3 n = ln > 0.0 ? gn / ln : float3(0.0, 1.0, 0.0);
    const float3 v = RTE.xyz - wp;
    if (dot(n, v) < 0.0) n = -n;
    const uint64_t base = nr_rt_a64(asuint(RTI.x), asuint(RTI.y));
    const uint2 msk = uint2(asuint(RTJ.x), asuint(RTJ.y));
    const bool mk = RTJ.w < 0.5 && cnt <= 64u;   // (RTJ.w 1: no mask -- culling off or a list over 64)
    const float3 Y = float3(0.299, 0.587, 0.114);
    bool quad = ((uint)RTJ.z & 1u) != 0u;
    if (quad) {
        const float tl = 4.0 * (0.004 * length(v) + 0.5);
        uint same = ok ? 1u : 0u;
        [unroll] for (uint k = 0u; k < 3u; k++) {
            const float3 po = k == 0u ? QuadReadAcrossX(wp) : k == 1u ? QuadReadAcrossY(wp) : QuadReadAcrossDiagonal(wp);
            const float3 no = k == 0u ? QuadReadAcrossX(n) : k == 1u ? QuadReadAcrossY(n) : QuadReadAcrossDiagonal(n);
            const uint oo = k == 0u ? QuadReadAcrossX(ok ? 1u : 0u) : k == 1u ? QuadReadAcrossY(ok ? 1u : 0u) : QuadReadAcrossDiagonal(ok ? 1u : 0u);
            const float3 dw = po - wp;
            if (oo == 0u || dot(dw, dw) > tl * tl || dot(no, n) < 0.9) same = 0u;
        }
        same = min(same, QuadReadAcrossX(same));
        same = min(same, QuadReadAcrossY(same));
        quad = same != 0u;
    }
    const uint lane = ((uint)px.x & 1u) + 2u * ((uint)px.y & 1u);
    const uint i0s = quad ? lane : 0u, step = quad ? 4u : 1u;
    float3 sum = float3(0.0, 0.0, 0.0);
    float b0 = 0.0, b1 = 0.0;
    uint i0 = 0xFFFFFFFFu, i1 = 0xFFFFFFFFu;
    if (ok) {
        [loop] for (uint i = i0s; i < cnt; i += step) {
            if (mk && ((i < 32u ? msk.x >> i : msk.y >> (i - 32u)) & 1u) == 0u) continue;
            const float4 a = vk::RawBufferLoad<float4>(base + (uint64_t)i * 32u, 16);
            const float4 c = vk::RawBufferLoad<float4>(base + (uint64_t)i * 32u + 16u, 16);
            const float3 e = nr_rt_emi_one(a, c, wp, n);
            const float y = dot(e, Y);
            if (!(y > 0.0)) continue;
            sum += e;
            if (y > b0) { b1 = b0; i1 = i0; b0 = y; i0 = i; }
            else if (y > b1) { b1 = y; i1 = i; }
        }
    }
    const float3 o = wp + n * (RTP.y + RTP.z * length(v));
    float sh0 = 0.0, sh1 = 0.0;
    if (quad) {
        sum += QuadReadAcrossX(sum);
        sum += QuadReadAcrossY(sum);
        {
            const float c0 = QuadReadAcrossX(b0), c1 = QuadReadAcrossX(b1);
            const uint j0 = QuadReadAcrossX(i0), j1 = QuadReadAcrossX(i1);
            nr_rt_emi_top2(b0, i0, b1, i1, c0, j0, c1, j1);
        }
        {
            const float c0 = QuadReadAcrossY(b0), c1 = QuadReadAcrossY(b1);
            const uint j0 = QuadReadAcrossY(i0), j1 = QuadReadAcrossY(i1);
            nr_rt_emi_top2(b0, i0, b1, i1, c0, j0, c1, j1);
        }
        // (the merge order differs per lane only on ties: take lane 0's pair for every lane)
        i0 = QuadReadLaneAt(i0, 0u);
        i1 = QuadReadLaneAt(i1, 0u);
        // lanes 0 / 3 trace the strongest light, 1 / 2 the second; each pixel takes the pair's mean
        const uint mine = (lane == 0u || lane == 3u) ? i0 : i1;
        float h = 0.0;
        if (mine != 0xFFFFFFFFu) h = nr_rt_emi_ray(vk::RawBufferLoad<float4>(base + (uint64_t)mine * 32u, 16), o);
        const float hx = QuadReadAcrossX(h), hy = QuadReadAcrossY(h), hd = QuadReadAcrossDiagonal(h);
        // (lane 0: itself + diagonal for i0, X / Y neighbours for i1; the others alike)
        const bool a0 = lane == 0u || lane == 3u;
        sh0 = 0.5 * (a0 ? h + hd : hx + hy);
        sh1 = 0.5 * (a0 ? hx + hy : h + hd);
    } else if (ok) {
        if (i0 != 0xFFFFFFFFu) sh0 = nr_rt_emi_ray(vk::RawBufferLoad<float4>(base + (uint64_t)i0 * 32u, 16), o);
        if (i1 != 0xFFFFFFFFu) sh1 = nr_rt_emi_ray(vk::RawBufferLoad<float4>(base + (uint64_t)i1 * 32u, 16), o);
    }
    if (!ok) return float3(0.0, 0.0, 0.0);
    // the shadowed strongest lights' light at this pixel (re-evaluated here: exact per pixel)
    [unroll] for (uint k = 0u; k < 2u; k++) {
        const uint ii = k == 0u ? i0 : i1;
        const float sv = k == 0u ? sh0 : sh1;
        if (ii == 0xFFFFFFFFu || !(sv > 0.0)) continue;
        const float4 a = vk::RawBufferLoad<float4>(base + (uint64_t)ii * 32u, 16);
        const float4 c = vk::RawBufferLoad<float4>(base + (uint64_t)ii * 32u + 16u, 16);
        const float3 e = nr_rt_emi_one(a, c, wp, n);
        if (dot(e, Y) < 1.0) continue;
        sum -= e * sv;
    }
    // a soft ceiling (many lights, or one too near): at most +RTI_K of the baked full light, smoothly
    sum = max(sum, float3(0.0, 0.0, 0.0));
    const float ys = dot(sum, Y), K = 160.0;
    return sum * (K / (K + ys));
}
#endif

PSOut PS_nr(VSOut i)
{
    PSOut o;
#ifdef NR_RT
    float3 rt_gn = cross(ddx(i.wp), ddy(i.wp));   // (before any discard: derivatives of the whole quad)
    float3 rt_alb = float3(128.0, 128.0, 128.0);    // (rt8) the texel the emissive light multiplies
#endif
    if (i.nearl < 0.0) discard;
    uint fl = PS_FLAGS, at = PS_ATEST;
    float4 vc = i.nearf > 0.0 ? i.colp : i.col;  // 0..255 (GS units, alpha 0x80 = 1.0)
    float4 c = vc;
    if (fl & PF_TME) {
        float3 stq = i.stq;
        if (fl & PF_SNAP) {
            // the GS evaluates a sprite's texture coordinates once per (native)
            // pixel: every sub-sample takes the value at the pixel's centre
            float sc = R[22].y;
            float2 c = (floor(i.pos.xy / sc) + 0.5) * sc;
            if (R[22].w != 0.0) c.x = i.pos.x;   // squeezed 2D (gpu_set_im_xfree): Y only
            if (R[22].w >= 2.0) c.y = i.pos.y;   // UI-scaled 2D: neither
            stq += ddx(i.stq) * (c.x - i.pos.x) + ddy(i.stq) * (c.y - i.pos.y);
        }
        float2 tuv = (VARIANT & NRV_IM) ? stq.xy / (stq.z != 0.0 ? stq.z : 1e-30)
                   : (VARIANT & NRV_REFRACT) ? i.uvs : i.uv;
        if (VARIANT & NRV_IM) tuv *= R[12].xy;      // GS-normalised -> the sampled texture (a live target: its size)
        float4 t;
        if ((fl & PF_BOX) && R[22].z > 0.0) {
            // a twin draw (nr_dev.cpp gpu_set_im_hires: depth of field at the internal resolution):
            // the footprint of R[22].z x R[13].w of this pixel (a box as wide as the work buffer's own
            // pixels), centred on it, by a grid of at most 12 x 12 bilinear taps; colour and alpha
            // averaged as below
            uint W, H;
            g_tex.GetDimensions(W, H);
            float2 q = i.stq.xy / (i.stq.z != 0.0 ? i.stq.z : 1e-30) * R[12].xy * float2((float)W, (float)H);
            // (R[13].w < 0: colour and alpha averaged apart, the GS's minifying taps' way: the bloom's
            // bright pass Cs * As of the averages, the PS2's strength; else alpha colour-weighted)
            float2 fw = max(float2(abs(ddx(q.x)) + abs(ddy(q.x)), abs(ddx(q.y)) + abs(ddy(q.y))) * float2(R[22].z, abs(R[13].w)), 1.0);
            int2 nt = (int2)min(ceil(fw), 12.0);
            float2 st = fw / (float2)nt, lo = q - 0.5 * fw;
            float3 cs = 0.0, ca = 0.0;
            float wa = 0.0;
            [loop] for (int y = 0; y < nt.y; y++) {
                [loop] for (int x = 0; x < nt.x; x++) {
                    float2 pp = lo + (float2((float)x, (float)y) + 0.5) * st;
                    float4 tx = nr_expand(round(g_tex.SampleLevel(g_smp, pp / float2((float)W, (float)H), 0) * 255.0), fl);
                    cs += tx.rgb;
                    ca += tx.rgb * tx.a;
                    wa += tx.a;
                }
            }
            float nn = (float)(nt.x * nt.y), sc_ = cs.r + cs.g + cs.b;
            t.rgb = floor(cs / nn + 0.5);
            t.a = floor((sc_ > 0.0 && R[13].w > 0.0 ? (ca.r + ca.g + ca.b) / sc_ : wa / nn) + 0.5);
        } else if (fl & PF_BOX) {
            // every internal-resolution texel under the pixel's footprint, weighted by its covered
            // area (the effect's reduced buffer filled from the full-resolution frame; nr_sfx.c)
            uint W, H;
            g_tex.GetDimensions(W, H);
            float2 q = i.stq.xy / (i.stq.z != 0.0 ? i.stq.z : 1e-30) * R[12].xy * float2((float)W, (float)H);
            float2 fw = clamp(float2(abs(ddx(q.x)) + abs(ddy(q.x)), abs(ddx(q.y)) + abs(ddy(q.y))), 1.0, 8.0);
            float2 lo = q - 0.5 * fw, hi = q + 0.5 * fw;
            int2 a = (int2)floor(lo), b = (int2)ceil(hi) - 1;
            int2 wm = int2((int)W - 1, (int)H - 1);
            // colour = the plain average; alpha = the colour-weighted average of alpha, so that both
            // c and c * a (what the passes use next: the glare's bright pass is Cs * As - k * Cs)
            // keep their averages over the footprint (no colour / alpha decorrelation at edges)
            float3 cs = 0.0, ca = 0.0;
            float ws = 0.0, wa = 0.0;
            [loop] for (int y = a.y; y <= b.y; y++) {
                float wy = min(hi.y, (float)y + 1.0) - max(lo.y, (float)y);
                [loop] for (int x = a.x; x <= b.x; x++) {
                    float wx = min(hi.x, (float)x + 1.0) - max(lo.x, (float)x);
                    int2 p = clamp(int2(x, y), int2(0, 0), wm);
                    float4 tx = nr_expand(round(g_tex.Load(int3(p, 0)) * 255.0), fl);
                    float w = wx * wy;
                    cs += tx.rgb * w;
                    ca += tx.rgb * (tx.a * w);
                    ws += w;
                    wa += tx.a * w;
                }
            }
            float sc_ = cs.r + cs.g + cs.b;
            t.rgb = floor(cs / max(ws, 1e-6) + 0.5);
            t.a = floor((sc_ > 0.0 ? (ca.r + ca.g + ca.b) / sc_ : wa / max(ws, 1e-6)) + 0.5);
        } else if (fl & (PF_NATTAP | PF_SUBPH)) {
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
            if (fl & PF_SHARPY) {
                // the same in Y (a scaled glyph: every texel row as tall as its share, no
                // doubled rows); at 1:1 the weight is 0 or 1, i.e. the nearest texel
                float v = tuv.y * (float)H;
                float fh = max(abs(ddy(v)), 1e-6);
                float seamv = floor(v + 0.5);
                float wv = saturate((v - seamv) / fh + 0.5);
                float v0 = (seamv - 0.5) / (float)H, v1 = (seamv + 0.5) / (float)H;
                float4 t2 = nr_expand(floor(g_tex.SampleLevel(g_smp, float2((seam - 0.5) / (float)W, v1), 0) * 255.0 + 0.5), fl);
                float4 t3 = nr_expand(floor(g_tex.SampleLevel(g_smp, float2((seam + 0.5) / (float)W, v1), 0) * 255.0 + 0.5), fl);
                t0 = nr_expand(floor(g_tex.SampleLevel(g_smp, float2((seam - 0.5) / (float)W, v0), 0) * 255.0 + 0.5), fl);
                t1 = nr_expand(floor(g_tex.SampleLevel(g_smp, float2((seam + 0.5) / (float)W, v0), 0) * 255.0 + 0.5), fl);
                t = floor(lerp(lerp(t0, t1, w), lerp(t2, t3, w), wv) + 0.5);
            } else {
                t = floor(lerp(t0, t1, w) + 0.5);
            }
        } else {
            t = nr_expand(floor(g_tex.Sample(g_smp, tuv) * 255.0 + 0.5), fl);
        }
#ifdef NR_RT
        rt_alb = t.rgb;
        if (RTR.x > 0.5 && RTR.x < 1.5) t.rgb = nr_rt_refl(i.wp, rt_gn, i.wn, t.rgb, i.pos.xy);   // (rt5) reflections
#endif
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
#ifdef NR_RT
    if (RTR.x > 1.5) c.rgb = nr_rt_refl_water(i.wp, rt_gn, i.wn, c.rgb, i.pos.xy);   // (rt5) water reflections
#endif
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
#ifdef NR_ZDSV
    {
        uint zfn = PS_ZCTL & 3u;
        float zf = i.pos.z;
        if (zfn >= 2u) {
            zf = ((VARIANT & NRV_IM) || (PS_ZCTL & 32u)) ? i.pos.z : i.pos.z - 2.0 / 4294967296.0;   // as NR_ZROV
            if (zf < 0.0) discard;   // below every stored value (NR_ZROV's test fails); the view would clamp it to 0
        }
        o.zo = zf;
    }
#endif
#ifdef NR_RT
    if (RTL.w > 0.0) c.rgb = nr_rt_shade(i.wp, rt_gn, c.rgb, i.pos.xy, i.wq);
    if (RTI.z > 0.5) {   // (rt8) emissive lights, added on the texel before fog
        float3 E = nr_rt_emi(i.wp, rt_gn, i.pos.xy);
        c.rgb = ((uint)RTI.w & 1u) ? min(floor(E), 255.0) : min(c.rgb + floor(rt_alb * E / 128.0), 255.0);
    }
#endif
    if (fl & PF_FGE) {
        uint fc = PS_FOGCOL;
        float3 fcol = float3(fc & 255u, (fc >> 8) & 255u, (fc >> 16) & 255u);
        float f = i.nearf > 0.0 ? i.fogp : i.fog;
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
