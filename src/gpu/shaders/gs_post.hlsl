// SPDX-License-Identifier: CC0-1.0
// Output post-processing of the GPU renderer (docs/GPU.md "Graphics
// settings"): presentation only, after the PCRTC display has been composed.
// Nothing here feeds back into the GS model.  All original code (no
// third-party shader was used or paraphrased).
//
//   PS_resample   one axis of a separable resampler (box / tent / Mitchell
//                 bicubic / Lanczos-2 for minification, nearest / bilinear /
//                 sharp-bilinear for magnification)
//   PS_fxaa       post-process anti-aliasing: luma edge detection, edge-end
//                 search, sub-pixel blend (FXAA-style, own implementation)
//   PS_sharpen    contrast-adaptive sharpening (cross neighbourhood)
//   PS_final      brightness / gamma, scanlines / CRT mask; writes RGBA8
//
// Every pass draws a full-viewport triangle (VS_quad of gs_util.hlsl) and
// reads its source with Load (texel exact) or SampleLevel (bilinear).

Texture2D<float4> g_src : register(t0);
SamplerState g_lin : register(s0);   // bilinear, clamp

cbuffer PostCB : register(b0)
{
    float4 P[4];
    uint4 Q[2];
};
// PS_resample: P[0] = (src_w, src_h, dst_w, dst_h)
//              Q[0] = (axis 0 = x / 1 = y, filter, 0, 0)
//   filter: 0 box, 1 tent (bilinear), 2 bicubic (Mitchell B=C=1/3),
//           3 Lanczos-2, 4 nearest, 5 sharp bilinear
// PS_fxaa:     P[0] = (w, h, 1/w, 1/h)
// PS_sharpen:  P[0] = (w, h, amount, 0)
// PS_final:    P[0] = (w, h, brightness, 1/gamma)
//              P[1] = (source lines, strength, 0, 0)
//              Q[0] = (output filter 0 off / 1 scanlines / 2 crt, 0, 0, 0)

float sinc(float x)
{
    if (abs(x) < 1e-5) return 1.0;
    float p = 3.14159265 * x;
    return sin(p) / p;
}

// kernel at distance t (in destination-pixel units when minifying)
float kern(uint f, float t)
{
    t = abs(t);
    switch (f) {
    case 1: return max(0.0, 1.0 - t);
    case 2: {
        // Mitchell-Netravali, B = C = 1/3
        const float B = 1.0 / 3.0, C = 1.0 / 3.0;
        if (t < 1.0)
            return ((12 - 9 * B - 6 * C) * t * t * t + (-18 + 12 * B + 6 * C) * t * t + (6 - 2 * B)) / 6.0;
        if (t < 2.0)
            return ((-B - 6 * C) * t * t * t + (6 * B + 30 * C) * t * t + (-12 * B - 48 * C) * t +
                    (8 * B + 24 * C)) / 6.0;
        return 0.0;
    }
    case 3: return t < 2.0 ? sinc(t) * sinc(t * 0.5) : 0.0;
    default: return t < 0.5 ? 1.0 : 0.0;
    }
}

float support(uint f)
{
    return f == 2 || f == 3 ? 2.0 : (f == 1 ? 1.0 : 0.5);
}

float4 PS_resample(float4 pos : SV_Position) : SV_Target0
{
    uint axis = Q[0].x, filt = Q[0].y;
    float sn = axis ? P[0].y : P[0].x;       // source size along the axis
    float dn = axis ? P[0].w : P[0].z;       // destination size
    int2 p = int2(pos.xy);
    float o = axis ? pos.y : pos.x;          // destination pixel centre (k + 0.5)
    float f = sn / dn;                       // source texels per destination pixel
    float c = o * f;                         // centre in source coordinates
    int lim = (int)sn - 1;
    if (filt >= 4 || (f <= 1.0 && filt == 0)) {
        // magnification (or a box at 1:1 or larger): nearest, bilinear or sharp
        float x = c - 0.5;
        float i0 = floor(x);
        float fr = x - i0;
        if (filt == 4 || filt == 0) {
            fr = fr >= 0.5 ? 1.0 : 0.0;
        } else if (filt == 5) {
            // sharp bilinear: nearest inside a source texel, linear only
            // across the last destination pixel at its edge
            float m = max(1.0 / f, 1.0);
            fr = saturate((fr - 0.5) * m + 0.5);
        }
        int a = clamp((int)i0, 0, lim), b = clamp((int)i0 + 1, 0, lim);
        int2 pa = axis ? int2(p.x, a) : int2(a, p.y);
        int2 pb = axis ? int2(p.x, b) : int2(b, p.y);
        return lerp(g_src.Load(int3(pa, 0)), g_src.Load(int3(pb, 0)), fr);
    }
    if (filt == 0) {
        // box: area of each source texel inside [c - f/2, c + f/2]
        float lo = c - 0.5 * f, hi = c + 0.5 * f;
        int i0 = (int)floor(lo), i1 = (int)ceil(hi) - 1;
        float4 acc = 0;
        float wsum = 0;
        [loop] for (int i = i0; i <= i1; i++) {
            float w = min(hi, i + 1.0) - max(lo, (float)i);
            if (w <= 0) continue;
            int j = clamp(i, 0, lim);
            acc += g_src.Load(int3(axis ? int2(p.x, j) : int2(j, p.y), 0)) * w;
            wsum += w;
        }
        return acc / max(wsum, 1e-6);
    }
    // tent / bicubic / Lanczos, widened by the minification factor
    float sc = max(f, 1.0);
    float r = support(filt) * sc;
    int i0 = (int)floor(c - r), i1 = (int)ceil(c + r);
    float4 acc = 0;
    float wsum = 0;
    [loop] for (int i = i0; i <= i1; i++) {
        float w = kern(filt, ((float)i + 0.5 - c) / sc);
        if (w == 0) continue;
        int j = clamp(i, 0, lim);
        acc += g_src.Load(int3(axis ? int2(p.x, j) : int2(j, p.y), 0)) * w;
        wsum += w;
    }
    return max(acc / (abs(wsum) > 1e-6 ? wsum : 1.0), 0.0);
}

// ---------------------------------------------------------------- FXAA-style
float luma(float3 c) { return dot(c, float3(0.299, 0.587, 0.114)); }
float4 tap(float2 uv) { return g_src.SampleLevel(g_lin, uv, 0); }

float4 PS_fxaa(float4 pos : SV_Position) : SV_Target0
{
    float2 rcp = P[0].zw;
    int2 p = int2(pos.xy);
    float2 uv = pos.xy * rcp;
    float4 cM = g_src.Load(int3(p, 0));
    float lM = luma(cM.rgb);
    float lN = luma(g_src.Load(int3(p + int2(0, -1), 0)).rgb);
    float lS = luma(g_src.Load(int3(p + int2(0, 1), 0)).rgb);
    float lW = luma(g_src.Load(int3(p + int2(-1, 0), 0)).rgb);
    float lE = luma(g_src.Load(int3(p + int2(1, 0), 0)).rgb);
    float mx = max(lM, max(max(lN, lS), max(lW, lE)));
    float mn = min(lM, min(min(lN, lS), min(lW, lE)));
    float range = mx - mn;
    if (range < max(1.0 / 32.0, mx * (1.0 / 8.0))) return cM;   // no edge
    float lNW = luma(g_src.Load(int3(p + int2(-1, -1), 0)).rgb);
    float lNE = luma(g_src.Load(int3(p + int2(1, -1), 0)).rgb);
    float lSW = luma(g_src.Load(int3(p + int2(-1, 1), 0)).rgb);
    float lSE = luma(g_src.Load(int3(p + int2(1, 1), 0)).rgb);
    // sub-pixel aliasing: how far the centre is from its neighbourhood mean
    float avg = (2.0 * (lN + lS + lW + lE) + lNW + lNE + lSW + lSE) / 12.0;
    float sub = saturate(abs(avg - lM) / range);
    sub = sub * sub * (3.0 - 2.0 * sub);
    sub = sub * sub * 0.75;
    // edge orientation: second differences across rows vs columns
    float eh = abs(lNW - 2 * lW + lSW) + 2 * abs(lN - 2 * lM + lS) + abs(lNE - 2 * lE + lSE);
    float ev = abs(lNW - 2 * lN + lNE) + 2 * abs(lW - 2 * lM + lE) + abs(lSW - 2 * lS + lSE);
    bool horz = ev >= eh;                       // the edge runs horizontally
    float lA = horz ? lN : lW, lB = horz ? lS : lE;   // the two sides
    float gA = abs(lA - lM), gB = abs(lB - lM);
    bool sideA = gA >= gB;
    float grad = max(gA, gB) * 0.25;
    float lEdge = 0.5 * (lM + (sideA ? lA : lB));
    float2 step_n = horz ? float2(0, rcp.y) : float2(rcp.x, 0);   // across the edge
    float2 step_e = horz ? float2(rcp.x, 0) : float2(0, rcp.y);   // along the edge
    float2 e0 = uv + step_n * (sideA ? -0.5 : 0.5);
    // walk both ways along the edge until the pair luma leaves the edge
    float2 a = e0 - step_e, b = e0 + step_e;
    float da = luma(tap(a).rgb) - lEdge, db = luma(tap(b).rgb) - lEdge;
    bool doneA = abs(da) >= grad, doneB = abs(db) >= grad;
    const float steps[8] = { 1.0, 1.0, 1.5, 2.0, 2.0, 4.0, 8.0, 8.0 };
    [loop] for (int k = 0; k < 8 && !(doneA && doneB); k++) {
        if (!doneA) { a -= step_e * steps[k]; da = luma(tap(a).rgb) - lEdge; doneA = abs(da) >= grad; }
        if (!doneB) { b += step_e * steps[k]; db = luma(tap(b).rgb) - lEdge; doneB = abs(db) >= grad; }
    }
    float distA = horz ? uv.x - a.x : uv.y - a.y;
    float distB = horz ? b.x - uv.x : b.y - uv.y;
    bool nearA = distA < distB;
    float dmin = min(distA, distB), span = distA + distB;
    // blend only when the closer end goes the other way than the centre
    bool centreBelow = lM - lEdge < 0.0;
    bool goodEnd = ((nearA ? da : db) < 0.0) != centreBelow;
    float edge = goodEnd ? 0.5 - dmin / max(span, 1e-6) : 0.0;
    float off = max(edge, sub);
    float2 uvf = uv + step_n * (sideA ? -off : off);
    return float4(tap(uvf).rgb, cM.a);
}

// ---------------------------------------------------------------- sharpen
float4 PS_sharpen(float4 pos : SV_Position) : SV_Target0
{
    int2 p = int2(pos.xy);
    int2 lim = int2(P[0].xy) - 1;
    float3 c = g_src.Load(int3(p, 0)).rgb;
    float3 n = g_src.Load(int3(clamp(p + int2(0, -1), 0, lim), 0)).rgb;
    float3 s = g_src.Load(int3(clamp(p + int2(0, 1), 0, lim), 0)).rgb;
    float3 w = g_src.Load(int3(clamp(p + int2(-1, 0), 0, lim), 0)).rgb;
    float3 e = g_src.Load(int3(clamp(p + int2(1, 0), 0, lim), 0)).rgb;
    float3 mn = min(c, min(min(n, s), min(w, e)));
    float3 mx = max(c, max(max(n, s), max(w, e)));
    // less sharpening where the neighbourhood already spans the range
    float3 adapt = sqrt(saturate(min(mn, 1.0 - mx) / max(mx, 1e-4)));
    float3 k = P[0].z * 2.0 * adapt;
    float3 r = c + (c - 0.25 * (n + s + w + e)) * k;   // unsharp mask, adaptive amount
    return float4(clamp(r, mn, mx), 1.0);
}

// ---------------------------------------------------------------- final
float4 PS_final(float4 pos : SV_Position) : SV_Target0
{
    int2 p = int2(pos.xy);
    float3 c = g_src.Load(int3(p, 0)).rgb;
    c = pow(saturate(c * P[0].z), P[0].w);
    uint of = Q[0].x;
    if (of != 0) {
        float lines = P[1].x, strength = P[1].y;
        float ys = (pos.y / P[0].y) * lines;          // position in source lines
        float fr = frac(ys) - 0.5;                    // 0 at a line's centre
        float l = luma(c);
        float sigma = lerp(0.16, 0.34, l);            // brighter lines bloom wider
        float beam = exp(-(fr * fr) / (2.0 * sigma * sigma));
        float3 o = c * lerp(1.0 - strength, 1.0, beam);
        if (of == 2) {
            // aperture-grille mask (RGB stripes over output columns) and a
            // brightness compensation for what the mask and beam take away
            uint m = (uint)p.x % 3u;
            float3 mask = float3(m == 0 ? 1.0 : 0.7, m == 1 ? 1.0 : 0.7, m == 2 ? 1.0 : 0.7);
            o = saturate(o * mask * 1.25);
        } else {
            o = saturate(o * (1.0 + 0.5 * strength));
        }
        c = o;
    }
    return float4(c, 1.0);
}
