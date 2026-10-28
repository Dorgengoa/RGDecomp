// SPDX-License-Identifier: CC0-1.0
// Coherence and display passes of the GPU GS renderer (docs/GPU.md):
//   VS_quad            full-viewport triangle
//   PS_load_color      local-memory mirror -> colour render target
//   PS_load_depth      local-memory mirror -> depth render target (SV_Depth)
//   CS_wb_color        colour render target -> local-memory mirror
//   CS_wb_depth        depth render target  -> local-memory mirror
//   CS_merge           a host->local transfer -> local-memory mirror (masked)
//   PS_display         PCRTC: both read circuits + merge (gs_display.c)

#ifdef GS_MEM_RW_PASS
#define GS_MEM_RW 1
#endif
#include "gs_common.hlsli"

cbuffer UtilCB : register(b0)
{
    uint4 U[8];
};

float4 VS_quad(uint id : SV_VertexID) : SV_Position
{
    float2 p = float2((id << 1) & 2, id & 2);
    return float4(p * float2(2, -2) + float2(-1, 1), 0.5, 1);
}

#ifndef GS_MEM_RW_PASS
// U[0] = (bp, bw, psm, scale)
// U[1] = (phase x, phase y, 1: only the sub-samples at that phase, 0)  (a reinterpretation:
//        docs/NATIVE-RENDER.md checkpoint 12; zero = every sub-sample, the load as before)
float4 PS_load_color(float4 pos : SV_Position) : SV_Target0
{
    if (U[1].z != 0 && any(uint2(pos.xy) % U[0].w != U[1].xy)) discard;
    uint2 p = uint2(pos.xy) / U[0].w;
    uint4 c = from_stored(U[0].z, gs_read_pixel(U[0].z, U[0].x, U[0].y, p.x, p.y));
    return (float4)c / 255.0;
}

// GS_DEPTH_RT: into an R32_FLOAT render target (depth targets held as ordered
// views, docs/PERF-3D.md), the same value
#ifdef GS_DEPTH_RT
float PS_load_depth(float4 pos : SV_Position) : SV_Target0
#else
float PS_load_depth(float4 pos : SV_Position) : SV_Depth
#endif
{
    uint2 p = uint2(pos.xy) / U[0].w;
    uint z = gs_read_pixel(U[0].z, U[0].x, U[0].y, p.x, p.y);
    return (float)z * (1.0 / 4294967296.0);
}

// depth target resize: old depth -> new depth
Texture2D<float> g_src_d : register(t3);
float PS_copy_depth(float4 pos : SV_Position) : SV_Depth
{
    return g_src_d.Load(int3(pos.xy, 0));
}

// ---- display ----
// U[0] = (out_w, out_h, scale, field_sel | inter_field<<1)
// U[1] = (x0, y0, mmod | slbg<<1, alp)
// U[2] = (bgcolor, 0, 0, 0)
// U[3+2i] = (en | src_mirror<<1, fbp, fbw, psm)          circuit i
// U[4+2i] = (dbx | dby<<16, ox, oy, w | h<<16)
// U[7] = (rt scale of circuit 1, of circuit 2, af_hr 1, af_hr 2)
//        af_hr: this circuit reads one buffer row below the other (anti-
//        flicker); at scale > 1 that offset is one internal row
Texture2D<float4> g_c1 : register(t1);
Texture2D<float4> g_c2 : register(t2);

bool circ_px(uint i, int x, int y, uint2 sub, out uint4 rgba)
{
    rgba = uint4(0, 0, 0, 0);
    uint4 a = U[3 + 2 * i], b = U[4 + 2 * i];
    if (!(a.x & 1)) return false;
    int ox = (int)b.y, oy = (int)b.z, w = (int)(b.w & 0xFFFF), h = (int)(b.w >> 16);
    if (x < ox || y < oy || x >= ox + w || y >= oy + h) return false;
    uint cx = ((b.x & 0xFFFF) + (uint)(x - ox)) & 2047;
    uint cy = ((b.x >> 16) + (uint)(y - oy)) & 2047;
    uint psm = a.w;
    if (a.x & 2) {
        rgba = from_stored(psm, gs_read_pixel(psm, a.y, a.z, cx, cy));
    } else {
        uint s = i == 0 ? U[7].x : U[7].y;
        uint af = i == 0 ? U[7].z : U[7].w;
        int3 t = int3(cx * s + min(sub.x, s - 1), cy * s + min(sub.y, s - 1) - (af ? s - 1 : 0), 0);
        float4 f = i == 0 ? g_c1.Load(t) : g_c2.Load(t);
        rgba = (uint4)round(f * 255.0);
    }
    if (psm == PSMCT24) rgba.a = 0x80;
    return true;
}

float4 PS_display(float4 pos : SV_Position) : SV_Target0
{
    uint scale = U[0].z;
    uint2 P = uint2(pos.xy);
    uint2 o = P / scale, sub = P % scale;
    bool fsel = (U[0].w & 2) != 0;
    uint field = U[0].w & 1;
    int x = (int)U[1].x + (int)o.x;
    int y = (int)U[1].y + (int)(fsel ? o.y * 2 + field : o.y);
    uint4 p1, p2;
    bool h1 = circ_px(0, x, y, sub, p1);
    bool h2 = circ_px(1, x, y, sub, p2);
    uint mmod = U[1].z & 1, slbg = (U[1].z >> 1) & 1, alp = U[1].w;
    uint bgc = U[2].x;
    uint3 base = slbg ? uint3(bgc & 255, (bgc >> 8) & 255, (bgc >> 16) & 255)
                      : (h2 ? p2.rgb : uint3(0, 0, 0));
    uint3 res = base;
    if (h1) {
        uint a = mmod ? alp : min(p1.a * 2, 255u);
        res = (p1.rgb * a + base * (255 - a) + 127) / 255;
    }
    return float4((float3)res / 255.0, 1.0);
}
#else
// ---- write-back (render target -> mirror) ----
// U[0] = (bp, bw, psm, scale)   U[1] = (x0, y0, w, h) native
// U[2] = (phase x, phase y, 1: that sub-sample instead of the centre, 0)  (a reinterpretation)
Texture2D<float4> g_rtc : register(t0);
Texture2D<float> g_rtd : register(t1);

void mem_store_px(uint psm, uint a, uint v)
{
    uint wa = a & 0x3FFFFC;
    switch (psm) {
    case PSMCT32: case PSMZ32:
        g_mem.Store(wa, v);
        break;
    case PSMCT24: case PSMZ24: {
        uint old = g_mem.Load(wa);
        g_mem.Store(wa, (old & 0xFF000000) | (v & 0xFFFFFF));
        break;
    }
    default: {   // 16-bit: two pixels share a word -> atomics on our half only
        uint sh = (a & 2) * 8;
        uint dummy;
        g_mem.InterlockedAnd(wa, ~(0xFFFFu << sh), dummy);
        g_mem.InterlockedOr(wa, (v & 0xFFFF) << sh, dummy);
        break;
    }
    }
}

[numthreads(8, 8, 1)]
void CS_wb_color(uint3 t : SV_DispatchThreadID)
{
    if (t.x >= U[1].z || t.y >= U[1].w) return;
    uint x = U[1].x + t.x, y = U[1].y + t.y, s = U[0].w;
    uint2 ph = U[2].z != 0 ? U[2].xy : uint2(s / 2, s / 2);
    float4 f = g_rtc.Load(int3(x * s + ph.x, y * s + ph.y, 0));
    uint4 c = (uint4)round(f * 255.0);
    uint psm = U[0].z, nib;
    uint a = gs_addr(psm, U[0].x, U[0].y, x, y, nib);
    mem_store_px(psm, a, to_stored(psm, c));
}

[numthreads(8, 8, 1)]
void CS_wb_depth(uint3 t : SV_DispatchThreadID)
{
    if (t.x >= U[1].z || t.y >= U[1].w) return;
    uint x = U[1].x + t.x, y = U[1].y + t.y, s = U[0].w;
    float d = g_rtd.Load(int3(x * s + s / 2, y * s + s / 2, 0));
    uint psm = U[0].z, nib;
    uint a = gs_addr(psm, U[0].x, U[0].y, x, y, nib);
    // keep the stored value when it is what the depth buffer was loaded
    // from (Z32 above 2^24 does not survive float32: do not lose bits of
    // pixels that were not drawn)
    uint w = g_mem.Load(a & 0x3FFFFC);
    uint old = psm == PSMZ32 ? w : (psm == PSMZ24 ? (w & 0xFFFFFF) : ((w >> ((a & 2) * 8)) & 0xFFFF));
    if ((float)old * (1.0 / 4294967296.0) == d) return;
    float zf = d * 4294967296.0;
    uint z = zf >= 4294967295.0 ? 0xFFFFFFFFu : (uint)zf;
    mem_store_px(psm, a, z);
}
// CS_clut: a CLUT load performed on the GPU from the mirror (gs_tex.c gs_tex0_written's
// arithmetic; docs/NATIVE-RENDER.md "GPU-side CLUT loads"): one thread per CLUT word (two
// 16-bit cells), cells the load does not write are kept.
// U[0] = (cbp, read psm, csm, csa)   U[1] = (n, is32, cbw, cou)   U[2].x = cov
RWBuffer<uint> g_clut_rw : register(u1);
[numthreads(64, 1, 1)]
void CS_clut(uint3 t : SV_DispatchThreadID)
{
    uint wi = t.x;
    if (wi >= 256) return;
    uint cbp = U[0].x, rpsm = U[0].y, csm = U[0].z, csa = U[0].w;
    uint n = U[1].x, is32 = U[1].y, cbw = U[1].z, cou = U[1].w, cov = U[2].x;
    uint old = g_clut_rw[wi];
    uint cell[2] = { old & 0xFFFF, old >> 16 };
    [unroll] for (uint k = 0; k < 2; k++) {
        uint c = wi * 2 + k, i, hi = 0;
        if (is32 && csm == 0) { hi = c >= 256 ? 1 : 0; i = ((c & 255) - (csa & 15) * 16) & 255; }
        else { i = (c - csa * 16) & 511; }
        if (i >= n) continue;
        uint x, y, bw;
        if (csm == 0) {
            bw = 1;
            if (n == 256) {
                uint p = (i & 0xE7) | ((i & 8) << 1) | ((i & 0x10) >> 1);
                x = p & 15; y = p >> 4;
            } else {
                x = i & 7; y = i >> 3;
            }
        } else {
            bw = cbw; x = cou * 16 + i; y = cov;
        }
        uint v = gs_read_pixel(rpsm, cbp, bw, x, y);
        cell[k] = hi ? (v >> 16) : (v & 0xFFFF);
    }
    g_clut_rw[wi] = cell[0] | (cell[1] << 16);
}

// CS_l2l_read / CS_l2l_write: a local->local transfer (TRXDIR 2) in the mirror (native-only
// device, docs/NATIVE-RENDER.md "Checkpoint 10"): the source pixels first into g_l2l, then
// written at the destination, so the copy reads the source as it was before (the GS's result
// for the direction it is told to copy in).  U[0] = (sbp, sbw, spsm, sx)  U[1] = (sy, w, h, dbp)
// U[2] = (dbw, dpsm, dx, dy)
RWBuffer<uint> g_l2l : register(u2);
[numthreads(8, 8, 1)]
void CS_l2l_read(uint3 t : SV_DispatchThreadID)
{
    if (t.x >= U[1].y || t.y >= U[1].z) return;
    g_l2l[t.y * U[1].y + t.x] = gs_read_pixel(U[0].z, U[0].x, U[0].y, (U[0].w + t.x) & 2047, (U[1].x + t.y) & 2047);
}
// a pixel value into the mirror at (x, y) of buffer (bp, bw, psm): its bits only (atomics on
// shared words: neighbouring pixels of 4 / 8 / 16-bit formats and T8H / T4HL / T4HH)
void mem_store_any(uint psm, uint bp, uint bw, uint x, uint y, uint v)
{
    uint nib;
    uint a = gs_addr(psm, bp, bw, x, y, nib);
    uint wa = a & 0x3FFFFC, sh, m, dummy;
    switch (psm) {
    case PSMCT32: case PSMZ32: g_mem.Store(wa, v); return;
    case PSMCT24: case PSMZ24: sh = 0; m = 0xFFFFFF; break;
    case PSMT8H: sh = 24; m = 0xFF; break;
    case PSMT4HL: sh = 24; m = 0xF; break;
    case PSMT4HH: sh = 28; m = 0xF; break;
    case PSMT8: sh = (a & 3) * 8; m = 0xFF; break;
    case PSMT4: sh = (a & 3) * 8 + nib * 4; m = 0xF; break;
    default: sh = (a & 2) * 8; m = 0xFFFF; break;
    }
    g_mem.InterlockedAnd(wa, ~(m << sh), dummy);
    g_mem.InterlockedOr(wa, (v & m) << sh, dummy);
}
[numthreads(8, 8, 1)]
void CS_l2l_write(uint3 t : SV_DispatchThreadID)
{
    if (t.x >= U[1].y || t.y >= U[1].z) return;
    mem_store_any(U[2].y, U[1].w, U[2].x, (U[2].z + t.x) & 2047, (U[2].w + t.y) & 2047, g_l2l[t.y * U[1].y + t.x]);
}

// CS_merge: a host->local transfer the CPU model wrote into pages the mirror
// holds newer data for (docs/GPU.md "Performance", checkpoint 3): per
// 32-bit word, mirror = (mirror & ~mask) | (data & mask), mask = exactly the
// bits the transfer wrote (gs_xfer_mask).  g_merge holds (data, mask) per
// word at twice the word's mirror offset.  U[0] = (first word, words)
ByteAddressBuffer g_merge : register(t2);
// CS_xfer: host->local transfers into the mirror (native-only device, docs/NATIVE-RENDER.md
// "Checkpoint 10"): a batch of transfers, their bytes in g_merge (each 4-byte aligned) and
// one descriptor per transfer in g_xdesc (psm, bp, bw, x, y, w, first pixel of the batch,
// byte offset); one thread per pixel (no two transfers of a batch share a block).
// U[0] = (descriptors, pixels)
ByteAddressBuffer g_xdesc : register(t3);
[numthreads(64, 1, 1)]
void CS_xfer(uint3 g : SV_GroupID, uint3 l : SV_GroupThreadID)
{
    uint t = (g.y * 32768 + g.x) * 64 + l.x;
    if (t >= U[0].y) return;
    uint lo = 0, hi = U[0].x;
    while (hi - lo > 1) {
        uint mid = (lo + hi) >> 1;
        if (g_xdesc.Load(mid * 32 + 24) <= t) lo = mid;
        else hi = mid;
    }
    uint4 a = g_xdesc.Load4(lo * 32), b = g_xdesc.Load4(lo * 32 + 16);
    uint psm = a.x, j = t - b.z, off = b.w, v, bo;
    uint x = (a.w + j % b.y) & 2047, y = (b.x + j / b.y) & 2047;
    switch (psm) {
    case PSMCT32: case PSMZ32: v = g_merge.Load(off + j * 4); break;
    case PSMCT24: case PSMZ24: {
        bo = off + j * 3;
        uint w0 = g_merge.Load(bo & ~3u), w1 = g_merge.Load((bo & ~3u) + 4), s = (bo & 3) * 8;
        v = (s ? ((w0 >> s) | (w1 << (32 - s))) : w0) & 0xFFFFFF;
        break;
    }
    case PSMT8: case PSMT8H: bo = off + j; v = (g_merge.Load(bo & ~3u) >> ((bo & 3) * 8)) & 0xFF; break;
    case PSMT4: case PSMT4HL: case PSMT4HH:
        bo = off + (j >> 1); v = (g_merge.Load(bo & ~3u) >> ((bo & 3) * 8 + (j & 1) * 4)) & 0xF; break;
    default: bo = off + j * 2; v = (g_merge.Load(bo & ~3u) >> ((bo & 2) * 8)) & 0xFFFF; break;
    }
    mem_store_any(psm, a.y, a.z, x, y, v);
}

[numthreads(64, 1, 1)]
void CS_merge(uint3 t : SV_DispatchThreadID)
{
    if (t.x >= U[0].y) return;
    uint w = U[0].x + t.x;
    uint2 dm = g_merge.Load2(w * 8);
    if (dm.y == 0) return;
    uint old = g_mem.Load(w * 4);
    g_mem.Store(w * 4, (old & ~dm.y) | (dm.x & dm.y));
}
#endif
