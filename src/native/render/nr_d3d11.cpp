/* SPDX-License-Identifier: CC0-1.0 */
/* Direct3D 11 backend of the GPU GS renderer (gpu_internal.h GpuBackend).
 * Feature level 11_0: hardware or WARP.  Shaders are compiled at build time
 * by the Windows SDK fxc (src/gpu/CMakeLists.txt) into byte-array headers.
 * docs/GPU.md. */
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
/* (moved from src/gpu/gpu_d3d11.cpp at checkpoint 10, docs/NATIVE-RENDER.md: rg_gpu compiles it
 * with RG_GPU_EXACT=1, the GS-exact batch path included; the native-only rg_native_render without
 * it; default rg_native_render builds compile nothing here) */
#if (defined(RG_GPU_EXACT) && RG_GPU_EXACT) || (defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY)
#if defined(RG_GPU_EXACT) && RG_GPU_EXACT
#define NR_EXACT 1
#else
#define NR_EXACT 0
#endif
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "gpu_internal.h"

#if NR_EXACT
#include "VS_main.h"
#include "PS_main.h"
#include "PS_main_x.h"
#include "PS_main_rov.h"
#include "PS_main_x_rov.h"
#include "PS_main_z.h"
#include "PS_main_x_z.h"
#include "PS_main_rov_z.h"
#include "PS_main_x_rov_z.h"
#include "PS_main_xn.h"
#include "PS_main_xn_rov.h"
#include "PS_main_xn_z.h"
#include "PS_main_xn_rov_z.h"
#endif
#include "PS_load_depth_rt.h"
#include "CS_l2l_read.h"
#include "CS_l2l_write.h"
#include "CS_xfer.h"
#include "VS_quad.h"
#include "PS_load_color.h"
#include "PS_load_depth.h"
#include "PS_copy_depth.h"
#include "PS_display.h"
#include "CS_wb_color.h"
#include "CS_wb_depth.h"
#include "CS_merge.h"
#include "CS_clut.h"
#include "CS_decode.h"
#include "PS_resample.h"
#include "PS_fxaa.h"
#include "PS_sharpen.h"
#include "PS_final.h"
#include "VS_nr.h"
#include "VS_im.h"
#include "PS_nr.h"
#include "PS_nr_z.h"
#include "PS_nr_c.h"
#include "PS_nr_cz.h"

#define REL(x) do { if (x) { (x)->Release(); (x) = NULL; } } while (0)

namespace {

struct Target {
    int used;
    int depth;
    int w, h;                       /* native */
    ID3D11Texture2D *tex;
    ID3D11RenderTargetView *rtv;
    ID3D11DepthStencilView *dsv;
    ID3D11ShaderResourceView *srv;
    ID3D11UnorderedAccessView *uav; /* colour, R32_UINT: the ordered-blend view;
                                       depth (zrov), R32_FLOAT: the ordered depth view */
    ID3D11Texture2D *snap;          /* colour snapshot for shader blending */
    ID3D11ShaderResourceView *snap_srv;
};

static const uint32_t MAX_VERTS = 65536 + 64;

/* a decoded texture (GpuDraw.dec, docs/GPU.md "Performance"): RGBA8 texels
 * of one texture rect, R32_UINT, cached by the core's content key */
struct DecTex {
    uint32_t key[8];
    GpuRect rect;
    int valid;
    int tw, th;                     /* allocated size */
    uint64_t used;                  /* LRU clock */
    ID3D11Texture2D *tex;
    ID3D11ShaderResourceView *srv;
    ID3D11UnorderedAccessView *uav;
};
static const size_t MAX_DEC = 256;

/* a post-chain surface (docs/GPU.md "Graphics settings") */
struct PostTex {
    int w = 0, h = 0;
    DXGI_FORMAT fmt = DXGI_FORMAT_UNKNOWN;
    ID3D11Texture2D *tex = NULL;
    ID3D11RenderTargetView *rtv = NULL;
    ID3D11ShaderResourceView *srv = NULL;
};

class D3D11Backend : public GpuBackend {
public:
    int scale = 1;
    ID3D11Device *dev = NULL;
    ID3D11DeviceContext *ctx = NULL;
    char devname[128] = "d3d11";
    ID3D11VertexShader *vs_main = NULL, *vs_quad = NULL;
    ID3D11PixelShader *ps_main = NULL, *ps_load_color = NULL, *ps_load_depth = NULL,
                      *ps_copy_depth = NULL, *ps_display = NULL;
    ID3D11ComputeShader *cs_wb_color = NULL, *cs_wb_depth = NULL, *cs_decode = NULL, *cs_merge = NULL;
    ID3D11ComputeShader *cs_clut = NULL;            /* GPU-side CLUT loads (CS_clut) */
    ID3D11ComputeShader *cs_l2l_read = NULL, *cs_l2l_write = NULL;   /* local->local copies (mem_copy) */
    ID3D11Buffer *l2l_buf = NULL;                   /* the copied pixels (RWBuffer<uint>, u2) */
    ID3D11ComputeShader *cs_xfer = NULL;            /* host->local transfers (mem_xfer_batch) */
    ID3D11Buffer *xdesc_buf = NULL;                 /* their descriptors (raw, t3) */
    ID3D11ShaderResourceView *xdesc_srv = NULL;
    ID3D11UnorderedAccessView *l2l_uav = NULL;
    ID3D11UnorderedAccessView *clut_uav = NULL;     /* cb_clut as RWBuffer<uint>, u1 */
    ID3D11Buffer *clut_stage = NULL;                /* clut_read */
    ID3D11Buffer *merge_buf = NULL;            /* (data, mask) per mirror word */
    ID3D11ShaderResourceView *merge_srv = NULL;
    ID3D11Buffer *cb_dec = NULL;
    std::vector<DecTex> dec;
    uint64_t dec_clock = 0;
    ID3D11InputLayout *layout = NULL;
    ID3D11Buffer *vb = NULL, *cb_draw = NULL, *cb_clut = NULL, *cb_util = NULL;
    ID3D11ShaderResourceView *clut_srv = NULL;   /* cb_clut as Buffer<uint>, t5 */
    ID3D11Buffer *mem = NULL, *mem_staging = NULL;
    ID3D11Buffer *tri_buf = NULL;            /* exact triangles (GpuTri), t4 */
    ID3D11ShaderResourceView *tri_srv = NULL;
    bool exact_ok = false;
    /* rasterizer-ordered views (D3D11.3): blended/DATE/merge batches read and
     * write the colour target in primitive order (docs/GPU.md "Performance") */
    bool rov_ok = false;
    ID3D11PixelShader *ps_rov = NULL;
    /* the float variants: batches without exact triangles/lines (sprites,
     * points) run the same code without the double-precision paths, whose
     * registers slow every pixel of the exact variant down */
    ID3D11PixelShader *ps_main_f = NULL, *ps_rov_f = NULL;
    /* depth in an ordered view (docs/PERF-3D.md): the same four with GS_ZROV */
    bool zrov_ok = false;
    ID3D11PixelShader *ps_main_z = NULL, *ps_rov_z = NULL, *ps_main_fz = NULL, *ps_rov_fz = NULL,
                      *ps_load_depth_rt = NULL;
    /* exact-triangle variants for untextured batches (GS_NOTEX, docs/PERF-3D.md):
     * [rov][zrov]; NULL: use the full shader */
    ID3D11PixelShader *ps_xn[2][2] = {};
    ID3D11ShaderResourceView *mem_srv = NULL;
    ID3D11UnorderedAccessView *mem_uav = NULL;
    /* scratch local memory for reinterpretations (rt_reinterpret; created on first use) */
    ID3D11Buffer *scr = NULL;
    ID3D11ShaderResourceView *scr_srv = NULL;
    ID3D11UnorderedAccessView *scr_uav = NULL;
    ID3D11RasterizerState *rs = NULL;
    ID3D11BlendState *bs[16] = {};
    ID3D11DepthStencilState *ds[4][2] = {};
    ID3D11DepthStencilState *ds_load = NULL;
    ID3D11Texture2D *disp_tex = NULL, *disp_staging = NULL;
    ID3D11RenderTargetView *disp_rtv = NULL;
    ID3D11ShaderResourceView *disp_srv = NULL;
    int disp_w = 0, disp_h = 0;
    /* output post chain */
    ID3D11PixelShader *ps_resample = NULL, *ps_fxaa = NULL, *ps_sharpen = NULL, *ps_final = NULL;
    ID3D11Buffer *cb_post = NULL;
    ID3D11SamplerState *smp_lin = NULL;
    PostTex post[3];                 /* 0, 1: float16 ping-pong; 2: RGBA8 output */
    ID3D11Texture2D *post_staging = NULL;
    int post_sw = 0, post_sh = 0;
    /* pipelined read-back (gpu_config.readback_lag, docs/GPU.md
     * "Performance"): two staging copies; each read returns the frame the
     * previous read queued, whose copy has long completed, so the CPU does
     * not wait for the GPU to finish the current one */
    bool lag = false;
    /* GPU time per kind of work ($RG_GPU_PROFILE=1, docs/GPU.md
     * "Performance"): timestamp queries around every draw, decode,
     * write-back, load and display; summed per category, printed at exit */
    bool prof = false;
    ID3D11Query *pq_dis = NULL;
    bool pq_active = false;
    std::vector<ID3D11Query *> pq;
    size_t pq_next = 0;
    struct PEv { int cat; size_t q0, q1; double px; };
    std::vector<PEv> pev;
    double p_ms[64] = {}, p_px[64] = {};
    uint64_t p_n[64] = {};
    enum { PC_DECODE = 32, PC_WB, PC_LOAD, PC_DISPLAY, PC_SNAP, PC_NR, PC_N };
    size_t disp_q0 = (size_t)-1;   /* display(): compose + copy, ended in readback */
    void disp_end(double px)
    {
        if (disp_q0 != (size_t)-1) pev_add(PC_DISPLAY, disp_q0, px);
        disp_q0 = (size_t)-1;
    }
    size_t pts()
    {
        if (!pq_active) { ctx->Begin(pq_dis); pq_active = true; }
        if (pq_next == pq.size()) {
            D3D11_QUERY_DESC qd = { D3D11_QUERY_TIMESTAMP, 0 };
            ID3D11Query *q = NULL;
            if (FAILED(dev->CreateQuery(&qd, &q))) return (size_t)-1;
            pq.push_back(q);
        }
        ctx->End(pq[pq_next]);
        return pq_next++;
    }
    void pev_add(int cat, size_t q0, double px)
    {
        size_t q1 = pts();
        if (q0 != (size_t)-1 && q1 != (size_t)-1) pev.push_back(PEv{ cat, q0, q1, px });
        if (pq_next > 8192) prof_collect();
    }
    void prof_collect()
    {
        if (!pq_active) return;
        ctx->End(pq_dis);
        pq_active = false;
        D3D11_QUERY_DATA_TIMESTAMP_DISJOINT dj;
        while (ctx->GetData(pq_dis, &dj, sizeof dj, 0) == S_FALSE) {}
        if (!dj.Disjoint && dj.Frequency) {
            for (const PEv &e : pev) {
                UINT64 a = 0, b = 0;
                while (ctx->GetData(pq[e.q0], &a, sizeof a, 0) == S_FALSE) {}
                while (ctx->GetData(pq[e.q1], &b, sizeof b, 0) == S_FALSE) {}
                if (b >= a) {
                    p_ms[e.cat] += (double)(b - a) * 1000.0 / (double)dj.Frequency;
                    p_n[e.cat]++;
                    p_px[e.cat] += e.px;
                }
            }
        }
        pev.clear();
        pq_next = 0;
    }
    void prof_print()
    {
        prof_collect();
        double tot = 0;
        for (int c = 0; c < PC_N; c++) tot += p_ms[c];
        fprintf(stderr, "gpu profile (GPU ms; draws by rov/direct/decoded/exact/textured):\n");
        for (int c = 0; c < PC_N; c++) {
            if (!p_n[c]) continue;
            char nm[64];
            if (c < 32)
                snprintf(nm, sizeof nm, "draw%s%s%s%s%s", c & 1 ? " rov" : "", c & 2 ? " direct" : "",
                         c & 4 ? " decoded" : "", c & 8 ? " exact" : "", c & 16 ? " tex" : " flat");
            else
                snprintf(nm, sizeof nm, "%s", c == PC_DECODE ? "decode" : c == PC_WB ? "write-back"
                         : c == PC_LOAD ? "load" : c == PC_DISPLAY ? "display+copy" : c == PC_NR ? "native model draws" : "snapshot");
            fprintf(stderr, "  %-36s %8llu calls %10.1f ms %5.1f%% %8.3f ms/call %10.1f Mpx\n", nm,
                    (unsigned long long)p_n[c], p_ms[c], tot > 0 ? 100.0 * p_ms[c] / tot : 0.0,
                    p_ms[c] / (double)p_n[c], p_px[c] / 1e6);
        }
        fprintf(stderr, "  total %.1f ms\n", tot);
    }
    struct LagSlot { ID3D11Texture2D *st = NULL; int w = 0, h = 0; bool pending = false; } lagq[2];
    int lag_cur = 0;
    std::vector<Target> targets;
    D3D11_SHADER_RESOURCE_VIEW_DESC srv_unorm = {};

    D3D11Backend()
    {
        srv_unorm.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srv_unorm.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srv_unorm.Texture2D.MipLevels = 1;
    }

    bool destroying = false;
    ~D3D11Backend() override
    {
        destroying = true;
        for (size_t i = 0; i < targets.size(); i++) rt_destroy((int)i);
        rt_pool_free();
        REL(vs_main); REL(vs_quad); REL(ps_main); REL(ps_rov); REL(ps_main_f); REL(ps_rov_f); REL(ps_main_z); REL(ps_rov_z); REL(ps_main_fz); REL(ps_rov_fz); REL(ps_load_depth_rt); for (int i = 0; i < 4; i++) REL(ps_xn[i >> 1][i & 1]); REL(ps_load_color); REL(ps_load_depth);
        REL(ps_copy_depth); REL(ps_display); REL(cs_wb_color); REL(cs_wb_depth); REL(cs_merge); REL(merge_srv); REL(merge_buf);
        REL(cs_clut); REL(clut_uav); REL(clut_stage); REL(cs_l2l_read); REL(cs_l2l_write); REL(l2l_uav); REL(l2l_buf); REL(cs_xfer); REL(xdesc_srv); REL(xdesc_buf);
        REL(cs_decode); REL(cb_dec);
        for (DecTex &e : dec) { REL(e.srv); REL(e.uav); REL(e.tex); }
        REL(layout); REL(vb); REL(cb_draw); REL(clut_srv); REL(cb_clut); REL(cb_util);
        REL(tri_srv); REL(tri_buf);
        REL(mem_srv); REL(mem_uav); REL(mem); REL(mem_staging); REL(rs); REL(scr_srv); REL(scr_uav); REL(scr);
        for (int k = 0; k < SNAP_SLOTS; k++) REL(snap[k]);
        for (int i = 0; i < 16; i++) REL(bs[i]);
        for (int i = 0; i < 4; i++) for (int j = 0; j < 2; j++) REL(ds[i][j]);
        REL(ds_load);
        REL(disp_rtv); REL(disp_srv); REL(disp_tex); REL(disp_staging);
        REL(ps_resample); REL(ps_fxaa); REL(ps_sharpen); REL(ps_final); REL(cb_post); REL(smp_lin);
        for (int i = 0; i < 3; i++) free_post(post[i]);
        REL(post_staging);
        for (int i = 0; i < 2; i++) REL(lagq[i].st);
        for (int i = 0; i < 2; i++) free_share(shs[i]);
        nr_release();
        if (prof && ctx) prof_print();
        for (ID3D11Query *q : pq) q->Release();
        REL(pq_dis);
        if (ctx) { ctx->ClearState(); ctx->Flush(); }
        REL(ctx); REL(dev);
    }

    const char *name() const override { return devname; }
    bool exact() const override { return exact_ok; }
    bool rov() const override { return rov_ok; }
    bool zrov() const override { return zrov_ok; }

    bool init(const gpu_config *cfg, int s, char *err, size_t cap)
    {
        scale = s;
        lag = cfg->readback_lag != 0;
        {
            const char *pe = getenv("RG_GPU_PROFILE");
            prof = pe && pe[0] == '1';
        }
        D3D_FEATURE_LEVEL fl[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
        D3D_FEATURE_LEVEL got;
        UINT flags = cfg->debug ? D3D11_CREATE_DEVICE_DEBUG : 0;
        D3D_DRIVER_TYPE dt = cfg->warp ? D3D_DRIVER_TYPE_WARP : D3D_DRIVER_TYPE_HARDWARE;
        HRESULT hr = E_FAIL;
        for (int attempt = 0; attempt < 4 && FAILED(hr); attempt++) {
            UINT f = attempt & 1 ? 0 : flags;
            const D3D_FEATURE_LEVEL *pfl = attempt < 2 ? fl : fl + 1;
            UINT nfl = attempt < 2 ? 2 : 1;
            hr = D3D11CreateDevice(NULL, dt, NULL, f, pfl, nfl, D3D11_SDK_VERSION, &dev, &got, &ctx);
        }
        if (FAILED(hr)) {
            snprintf(err, cap, "D3D11CreateDevice(%s) failed: 0x%08lX",
                     cfg->warp ? "WARP" : "hardware", (unsigned long)hr);
            return false;
        }
        IDXGIDevice *dxgi = NULL;
        if (SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgi))) {
            IDXGIAdapter *ad = NULL;
            if (SUCCEEDED(dxgi->GetAdapter(&ad))) {
                DXGI_ADAPTER_DESC d;
                if (SUCCEEDED(ad->GetDesc(&d))) {
                    char n[128];
                    WideCharToMultiByte(CP_UTF8, 0, d.Description, -1, n, sizeof n, NULL, NULL);
                    snprintf(devname, sizeof devname, "D3D11 %s (FL %x.%x)", n,
                             (unsigned)got >> 12, ((unsigned)got >> 8) & 15);
                }
                ad->Release();
            }
            dxgi->Release();
        }
#define CHK(x, what) do { if (FAILED(x)) { snprintf(err, cap, "%s failed", what); return false; } } while (0)
        CHK(dev->CreateVertexShader(g_VS_quad, sizeof g_VS_quad, NULL, &vs_quad), "VS_quad");
#if NR_EXACT
        CHK(dev->CreateVertexShader(g_VS_main, sizeof g_VS_main, NULL, &vs_main), "VS_main");
        /* Exact triangles (docs/GPU.md "Exact triangles") need double-precision
         * shader ops including the D3D11.1 extended set (ddiv, dtoi/dtou,
         * itod); otherwise the float-interpolation pixel shader is used. */
        {
            D3D11_FEATURE_DATA_DOUBLES fd = {};
            D3D11_FEATURE_DATA_D3D11_OPTIONS fo = {};
            bool dbl = SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_DOUBLES, &fd, sizeof fd)) &&
                       fd.DoublePrecisionFloatShaderOps;
            bool ext = SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &fo, sizeof fo)) &&
                       fo.ExtendedDoublesShaderInstructions;
            exact_ok = dbl && ext &&
                       SUCCEEDED(dev->CreatePixelShader(g_PS_main_x, sizeof g_PS_main_x, NULL, &ps_main));
        }
        if (!exact_ok)
            CHK(dev->CreatePixelShader(g_PS_main, sizeof g_PS_main, NULL, &ps_main), "PS_main");
        const char *nn = getenv("RG_GPU_NO_NOTEX");   /* measurement / check: the full shader everywhere */
        if (exact_ok && !(nn && nn[0] == '1') &&
            SUCCEEDED(dev->CreatePixelShader(g_PS_main_xn, sizeof g_PS_main_xn, NULL, &ps_xn[0][0]))) {
            dev->CreatePixelShader(g_PS_main_xn_rov, sizeof g_PS_main_xn_rov, NULL, &ps_xn[1][0]);
            dev->CreatePixelShader(g_PS_main_xn_z, sizeof g_PS_main_xn_z, NULL, &ps_xn[0][1]);
            dev->CreatePixelShader(g_PS_main_xn_rov_z, sizeof g_PS_main_xn_rov_z, NULL, &ps_xn[1][1]);
        }
        CHK(dev->CreatePixelShader(g_PS_main, sizeof g_PS_main, NULL, &ps_main_f), "PS_main (float)");
        {
            D3D11_FEATURE_DATA_D3D11_OPTIONS2 o2 = {};
            bool rov = !cfg->no_rov &&
                       SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS2, &o2, sizeof o2)) &&
                       o2.ROVsSupported;
            if (rov) {
                HRESULT h = exact_ok ? dev->CreatePixelShader(g_PS_main_x_rov, sizeof g_PS_main_x_rov, NULL, &ps_rov)
                                     : dev->CreatePixelShader(g_PS_main_rov, sizeof g_PS_main_rov, NULL, &ps_rov);
                rov_ok = SUCCEEDED(h) &&
                         SUCCEEDED(dev->CreatePixelShader(g_PS_main_rov, sizeof g_PS_main_rov, NULL, &ps_rov_f));
            }
            if (rov_ok && !cfg->no_zrov) {
                zrov_ok =
                    SUCCEEDED(exact_ok ? dev->CreatePixelShader(g_PS_main_x_z, sizeof g_PS_main_x_z, NULL, &ps_main_z)
                                       : dev->CreatePixelShader(g_PS_main_z, sizeof g_PS_main_z, NULL, &ps_main_z)) &&
                    SUCCEEDED(exact_ok ? dev->CreatePixelShader(g_PS_main_x_rov_z, sizeof g_PS_main_x_rov_z, NULL, &ps_rov_z)
                                       : dev->CreatePixelShader(g_PS_main_rov_z, sizeof g_PS_main_rov_z, NULL, &ps_rov_z)) &&
                    SUCCEEDED(dev->CreatePixelShader(g_PS_main_z, sizeof g_PS_main_z, NULL, &ps_main_fz)) &&
                    SUCCEEDED(dev->CreatePixelShader(g_PS_main_rov_z, sizeof g_PS_main_rov_z, NULL, &ps_rov_fz)) &&
                    SUCCEEDED(dev->CreatePixelShader(g_PS_load_depth_rt, sizeof g_PS_load_depth_rt, NULL, &ps_load_depth_rt));
            }
        }
#else
        {
            /* native-only (no GS-exact draw path): ordered views for the native pipeline's back end
             * (PS_nr_c / PS_nr_z) when the device has them */
            D3D11_FEATURE_DATA_D3D11_OPTIONS2 o2 = {};
            rov_ok = !cfg->no_rov && SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS2, &o2, sizeof o2)) &&
                     o2.ROVsSupported;
            zrov_ok = rov_ok && !cfg->no_zrov &&
                      SUCCEEDED(dev->CreatePixelShader(g_PS_load_depth_rt, sizeof g_PS_load_depth_rt, NULL, &ps_load_depth_rt));
        }
#endif
        CHK(dev->CreatePixelShader(g_PS_load_color, sizeof g_PS_load_color, NULL, &ps_load_color), "PS_load_color");
        CHK(dev->CreatePixelShader(g_PS_load_depth, sizeof g_PS_load_depth, NULL, &ps_load_depth), "PS_load_depth");
        CHK(dev->CreatePixelShader(g_PS_copy_depth, sizeof g_PS_copy_depth, NULL, &ps_copy_depth), "PS_copy_depth");
        CHK(dev->CreatePixelShader(g_PS_display, sizeof g_PS_display, NULL, &ps_display), "PS_display");
        CHK(dev->CreatePixelShader(g_PS_resample, sizeof g_PS_resample, NULL, &ps_resample), "PS_resample");
        CHK(dev->CreatePixelShader(g_PS_fxaa, sizeof g_PS_fxaa, NULL, &ps_fxaa), "PS_fxaa");
        CHK(dev->CreatePixelShader(g_PS_sharpen, sizeof g_PS_sharpen, NULL, &ps_sharpen), "PS_sharpen");
        CHK(dev->CreatePixelShader(g_PS_final, sizeof g_PS_final, NULL, &ps_final), "PS_final");
        {
            D3D11_SAMPLER_DESC sm = {};
            sm.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            sm.AddressU = sm.AddressV = sm.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
            sm.MaxLOD = D3D11_FLOAT32_MAX;
            CHK(dev->CreateSamplerState(&sm, &smp_lin), "sampler");
        }
        CHK(dev->CreateComputeShader(g_CS_wb_color, sizeof g_CS_wb_color, NULL, &cs_wb_color), "CS_wb_color");
        CHK(dev->CreateComputeShader(g_CS_wb_depth, sizeof g_CS_wb_depth, NULL, &cs_wb_depth), "CS_wb_depth");
        CHK(dev->CreateComputeShader(g_CS_merge, sizeof g_CS_merge, NULL, &cs_merge), "CS_merge");
        CHK(dev->CreateComputeShader(g_CS_clut, sizeof g_CS_clut, NULL, &cs_clut), "CS_clut");
        CHK(dev->CreateComputeShader(g_CS_decode, sizeof g_CS_decode, NULL, &cs_decode), "CS_decode");
        CHK(dev->CreateComputeShader(g_CS_l2l_read, sizeof g_CS_l2l_read, NULL, &cs_l2l_read), "CS_l2l_read");
        CHK(dev->CreateComputeShader(g_CS_l2l_write, sizeof g_CS_l2l_write, NULL, &cs_l2l_write), "CS_l2l_write");
        CHK(dev->CreateComputeShader(g_CS_xfer, sizeof g_CS_xfer, NULL, &cs_xfer), "CS_xfer");
        D3D11_INPUT_ELEMENT_DESC ie[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "ZF", 0, DXGI_FORMAT_R32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "ZI", 0, DXGI_FORMAT_R32_UINT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "STQ", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "FOG", 0, DXGI_FORMAT_R32_FLOAT, 0, 52, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "VFLAGS", 0, DXGI_FORMAT_R32_UINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "SPRA", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 60, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "SPRB", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 76, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "SPRC", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 92, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        static_assert(sizeof(GpuVertex) == 108, "GpuVertex layout");
#if NR_EXACT
        CHK(dev->CreateInputLayout(ie, 11, g_VS_main, sizeof g_VS_main, &layout), "input layout");
#else
        (void)ie;
#endif

        D3D11_BUFFER_DESC bd = {};
        bd.ByteWidth = MAX_VERTS * sizeof(GpuVertex);
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        CHK(dev->CreateBuffer(&bd, NULL, &vb), "vertex buffer");
        bd = {};
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.ByteWidth = sizeof(GpuDrawCB);
        CHK(dev->CreateBuffer(&bd, NULL, &cb_draw), "cb draw");
        CHK(dev->CreateBuffer(&bd, NULL, &cb_dec), "cb decode");
        if (exact_ok) {
            static_assert(sizeof(GpuTri) == 128, "GpuTri layout");
            D3D11_BUFFER_DESC tb = {};
            tb.ByteWidth = (MAX_VERTS / 3 + 1) * sizeof(GpuTri);
            tb.Usage = D3D11_USAGE_DYNAMIC;
            tb.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            tb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            tb.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            tb.StructureByteStride = sizeof(GpuTri);
            CHK(dev->CreateBuffer(&tb, NULL, &tri_buf), "triangle buffer");
            CHK(dev->CreateShaderResourceView(tri_buf, NULL, &tri_srv), "triangle srv");
            D3D11_FEATURE_DATA_D3D11_OPTIONS o1 = {};
            tri_ring = SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &o1, sizeof o1)) &&
                       o1.MapNoOverwriteOnDynamicBufferSRV;
        }
        {
            D3D11_BUFFER_DESC cd = {};
            cd.ByteWidth = sizeof(GpuClutCB);
            cd.Usage = D3D11_USAGE_DEFAULT;
            cd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
            CHK(dev->CreateBuffer(&cd, NULL, &cb_clut), "clut buffer");
            D3D11_SHADER_RESOURCE_VIEW_DESC cv = {};
            cv.Format = DXGI_FORMAT_R32_UINT;
            cv.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
            cv.Buffer.NumElements = sizeof(GpuClutCB) / 4;
            CHK(dev->CreateShaderResourceView(cb_clut, &cv, &clut_srv), "clut srv");
            D3D11_UNORDERED_ACCESS_VIEW_DESC uv = {};
            uv.Format = DXGI_FORMAT_R32_UINT;
            uv.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
            uv.Buffer.NumElements = sizeof(GpuClutCB) / 4;
            CHK(dev->CreateUnorderedAccessView(cb_clut, &uv, &clut_uav), "clut uav");
            D3D11_BUFFER_DESC sd = {};
            sd.ByteWidth = sizeof(GpuClutCB);
            sd.Usage = D3D11_USAGE_STAGING;
            sd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            CHK(dev->CreateBuffer(&sd, NULL, &clut_stage), "clut staging");
        }
        bd.ByteWidth = 8 * 16;
        CHK(dev->CreateBuffer(&bd, NULL, &cb_util), "cb util");
        bd.ByteWidth = 6 * 16;
        CHK(dev->CreateBuffer(&bd, NULL, &cb_post), "cb post");

        /* the local-memory mirror: raw buffer, SRV for shaders, UAV for write-back */
        bd = {};
        bd.ByteWidth = GS_VRAM_BYTES;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
        bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
        CHK(dev->CreateBuffer(&bd, NULL, &mem), "mirror");
        D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
        sd.Format = DXGI_FORMAT_R32_TYPELESS;
        sd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
        sd.BufferEx.NumElements = GS_VRAM_BYTES / 4;
        sd.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
        CHK(dev->CreateShaderResourceView(mem, &sd, &mem_srv), "mirror srv");
        D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
        ud.Format = DXGI_FORMAT_R32_TYPELESS;
        ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
        ud.Buffer.NumElements = GS_VRAM_BYTES / 4;
        ud.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
        CHK(dev->CreateUnorderedAccessView(mem, &ud, &mem_uav), "mirror uav");
        bd = {};
        bd.ByteWidth = GS_VRAM_BYTES;
        bd.Usage = D3D11_USAGE_STAGING;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        CHK(dev->CreateBuffer(&bd, NULL, &mem_staging), "mirror staging");
        bd = {};
        bd.ByteWidth = GS_VRAM_BYTES * 2;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
        CHK(dev->CreateBuffer(&bd, NULL, &merge_buf), "merge buffer");
        sd.BufferEx.NumElements = GS_VRAM_BYTES / 2;
        CHK(dev->CreateShaderResourceView(merge_buf, &sd, &merge_srv), "merge srv");

        D3D11_RASTERIZER_DESC rd = {};
        rd.FillMode = D3D11_FILL_SOLID;
        rd.CullMode = D3D11_CULL_NONE;
        rd.DepthClipEnable = FALSE;
        rd.ScissorEnable = TRUE;
        CHK(dev->CreateRasterizerState(&rd, &rs), "rasterizer");
        for (int m = 0; m < 16; m++) {
            D3D11_BLEND_DESC b = {};
            b.RenderTarget[0].BlendEnable = FALSE;
            b.RenderTarget[0].RenderTargetWriteMask = (UINT8)m;
            CHK(dev->CreateBlendState(&b, &bs[m]), "blend");
        }
        static const D3D11_COMPARISON_FUNC zf[4] = { D3D11_COMPARISON_ALWAYS, D3D11_COMPARISON_ALWAYS,
                                                     D3D11_COMPARISON_GREATER_EQUAL, D3D11_COMPARISON_GREATER };
        for (int f = 0; f < 4; f++)
            for (int w = 0; w < 2; w++) {
                D3D11_DEPTH_STENCIL_DESC d = {};
                d.DepthEnable = f != GZ_OFF;
                d.DepthWriteMask = w ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
                d.DepthFunc = zf[f];
                CHK(dev->CreateDepthStencilState(&d, &ds[f][w]), "depth state");
            }
        {
            D3D11_DEPTH_STENCIL_DESC d = {};
            d.DepthEnable = TRUE;
            d.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
            d.DepthFunc = D3D11_COMPARISON_ALWAYS;
            CHK(dev->CreateDepthStencilState(&d, &ds_load), "depth load state");
        }
        if (prof) {
            D3D11_QUERY_DESC qd = { D3D11_QUERY_TIMESTAMP_DISJOINT, 0 };
            if (FAILED(dev->CreateQuery(&qd, &pq_dis))) prof = false;
        }
        {
            const char *nn = getenv("RG_GPU_NO_NATIVE");   /* check: native draws refused */
            nr_ok = !(nn && nn[0] == '1') && nr_init();
            if (!nr_ok) nr_release();
        }
#undef CHK
        return true;
    }

    /* ---------------------------------------------------------- mirror */
    void mirror_upload(uint32_t off, uint32_t len, const uint8_t *src) override
    {
        D3D11_BOX b = { off, 0, 0, off + len, 1, 1 };
        ctx->UpdateSubresource(mem, 0, &b, src, len, len);
    }

    void mirror_download(const uint32_t *runs, int nruns, uint8_t *vram) override
    {
        for (int i = 0; i < nruns; i++) {
            D3D11_BOX b = { runs[2 * i], 0, 0, runs[2 * i] + runs[2 * i + 1], 1, 1 };
            ctx->CopySubresourceRegion(mem_staging, 0, runs[2 * i], 0, 0, mem, 0, &b);
        }
        D3D11_MAPPED_SUBRESOURCE m;
        if (FAILED(ctx->Map(mem_staging, 0, D3D11_MAP_READ, 0, &m))) return;
        for (int i = 0; i < nruns; i++)
            memcpy(vram + runs[2 * i], (const uint8_t *)m.pData + runs[2 * i], runs[2 * i + 1]);
        ctx->Unmap(mem_staging, 0);
    }

    bool can_merge() const override { return cs_merge != NULL; }
    void mirror_merge(uint32_t w0, uint32_t n, const uint32_t *dm) override
    {
        if (!n) return;
        D3D11_BOX b = { w0 * 8, 0, 0, (w0 + n) * 8, 1, 1 };
        ctx->UpdateSubresource(merge_buf, 0, &b, dm, n * 8, n * 8);
        unbind_all();
        uint32_t u[8][4] = {};
        u[0][0] = w0; u[0][1] = n;
        util_cb(u);
        ctx->CSSetConstantBuffers(0, 1, &cb_util);
        ctx->CSSetUnorderedAccessViews(0, 1, &mem_uav, NULL);
        ctx->CSSetShaderResources(2, 1, &merge_srv);
        ctx->CSSetShader(cs_merge, NULL, 0);
        ctx->Dispatch((n + 63) / 64, 1, 1);
        unbind_all();
        ctx->CSSetShader(NULL, NULL, 0);
    }

    /* --------------------------------------------------------- targets */
    bool make_target(Target &t, int depth, int w, int h)
    {
        for (size_t i = 0; i < rt_pool.size(); i++) {
            Target &p = rt_pool[i];
            if (p.depth != depth || p.w != w || p.h != h) continue;
            t = p;
            rt_pool.erase(rt_pool.begin() + (long)i);
            t.used = 1;
            n_rt_pool_hits++;
            if (t.dsv) ctx->ClearDepthStencilView(t.dsv, D3D11_CLEAR_DEPTH, 0.0f, 0);
            else if (t.rtv) { float z[4] = { 0, 0, 0, 0 }; ctx->ClearRenderTargetView(t.rtv, z); }
            return true;
        }
        memset(&t, 0, sizeof t);
        t.used = 1; t.depth = depth; t.w = w; t.h = h;
        D3D11_TEXTURE2D_DESC td = {};
        td.Width = (UINT)(w * scale);
        td.Height = (UINT)(h * scale);
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.SampleDesc.Count = 1;
        td.Usage = D3D11_USAGE_DEFAULT;
        if (depth && zrov_ok) {
            /* the same values as the D32_FLOAT buffer (z / 2^32), tested and
             * written by the pixel shader through an ordered view; loads
             * render into it, write-backs and direct sampling read it as
             * before (docs/PERF-3D.md) */
            td.Format = DXGI_FORMAT_R32_TYPELESS;
            td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &t.tex))) return false;
            D3D11_RENDER_TARGET_VIEW_DESC rv = {};
            rv.Format = DXGI_FORMAT_R32_FLOAT;
            rv.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            if (FAILED(dev->CreateRenderTargetView(t.tex, &rv, &t.rtv))) return false;
            D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
            sd.Format = DXGI_FORMAT_R32_FLOAT;
            sd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            sd.Texture2D.MipLevels = 1;
            if (FAILED(dev->CreateShaderResourceView(t.tex, &sd, &t.srv))) return false;
            D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
            ud.Format = DXGI_FORMAT_R32_FLOAT;
            ud.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
            if (FAILED(dev->CreateUnorderedAccessView(t.tex, &ud, &t.uav))) return false;
            float z[4] = { 0, 0, 0, 0 };
            ctx->ClearRenderTargetView(t.rtv, z);
        } else if (depth) {
            td.Format = DXGI_FORMAT_R32_TYPELESS;
            td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &t.tex))) return false;
            D3D11_DEPTH_STENCIL_VIEW_DESC dd = {};
            dd.Format = DXGI_FORMAT_D32_FLOAT;
            dd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
            if (FAILED(dev->CreateDepthStencilView(t.tex, &dd, &t.dsv))) return false;
            D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
            sd.Format = DXGI_FORMAT_R32_FLOAT;
            sd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            sd.Texture2D.MipLevels = 1;
            if (FAILED(dev->CreateShaderResourceView(t.tex, &sd, &t.srv))) return false;
            ctx->ClearDepthStencilView(t.dsv, D3D11_CLEAR_DEPTH, 0.0f, 0);
        } else {
            /* typeless so the ordered-blend path can view it as R32_UINT */
            td.Format = rov_ok ? DXGI_FORMAT_R8G8B8A8_TYPELESS : DXGI_FORMAT_R8G8B8A8_UNORM;
            td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE |
                           (rov_ok ? D3D11_BIND_UNORDERED_ACCESS : 0u);
            if (FAILED(dev->CreateTexture2D(&td, NULL, &t.tex))) return false;
            D3D11_RENDER_TARGET_VIEW_DESC rv = {};
            rv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            rv.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            if (FAILED(dev->CreateRenderTargetView(t.tex, &rv, &t.rtv))) return false;
            if (FAILED(dev->CreateShaderResourceView(t.tex, &srv_unorm, &t.srv))) return false;
            if (rov_ok) {
                D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
                ud.Format = DXGI_FORMAT_R32_UINT;
                ud.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
                if (FAILED(dev->CreateUnorderedAccessView(t.tex, &ud, &t.uav))) return false;
            }
            float z[4] = { 0, 0, 0, 0 };
            ctx->ClearRenderTargetView(t.rtv, z);
        }
        return true;
    }

    void free_target(Target &t)
    {
        REL(t.rtv); REL(t.dsv); REL(t.srv); REL(t.uav); REL(t.tex); REL(t.snap_srv); REL(t.snap);
        t.used = 0;
    }

    int rt_create(int depth, int w, int h) override
    {
        size_t i = 0;
        while (i < targets.size() && targets[i].used) i++;
        if (i == targets.size()) targets.push_back(Target());
        if (!make_target(targets[i], depth, w, h)) { free_target(targets[i]); return -1; }
        return (int)i;
    }

    void rt_clear(int id) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used) return;
        Target &t = targets[id];
        unbind_all();
        float z[4] = { 0, 0, 0, 0 };
        if (t.dsv) ctx->ClearDepthStencilView(t.dsv, D3D11_CLEAR_DEPTH, 0.0f, 0);
        else if (t.rtv) ctx->ClearRenderTargetView(t.rtv, z);
    }

    /* destroyed targets are kept for reuse (the game's work buffers come and
     * go every frame: creating them was a stutter at every scene start and a
     * steady cost in the effect passes); $RG_GPU_RT_POOL=0 turns it off */
    std::vector<Target> rt_pool;
    int rt_pool_on = -1;
    void rt_pool_free()
    {
        for (Target &t : rt_pool) free_target(t);
        rt_pool.clear();
    }
    void rt_destroy(int id) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used) return;
        unbind_all();
        if (rt_pool_on < 0) { const char *e = getenv("RG_GPU_RT_POOL"); rt_pool_on = !(e && e[0] == '0'); }
        if (rt_pool_on && targets[id].tex && !destroying) {
            if (rt_pool.size() >= 24) { free_target(rt_pool.front()); rt_pool.erase(rt_pool.begin()); }
            rt_pool.push_back(targets[id]);
            memset(&targets[id], 0, sizeof targets[id]);
            return;
        }
        free_target(targets[id]);
    }

    /* ---- bound state of the draw path (docs/GPU.md "Performance") ----
     * draw() sets only what changed since the previous draw.  Every other
     * path (loads, write-backs, display, post) starts and ends with
     * unbind_all(), which forgets the pipeline state. */
    struct Shadow {
        bool pipe = false;                 /* IA/VS/RS/CB bindings of the draw path */
        ID3D11PixelShader *ps = NULL;
        int vp_w = -1, vp_h = -1;
        D3D11_RECT sc = { -1, -1, -1, -1 };
        ID3D11RenderTargetView *rtv = NULL;
        ID3D11DepthStencilView *dsv = NULL;
        ID3D11UnorderedAccessView *uav = NULL, *zuav = NULL;
        ID3D11ShaderResourceView *srv[7] = {};
        ID3D11Resource *srv_res[7] = {};
        ID3D11BlendState *bs = NULL;
        ID3D11DepthStencilState *ds = NULL;
        bool cb_valid = false;
        GpuDrawCB cb;
    } sh;
    uint32_t vb_pos = 0, tri_pos = 0;      /* ring offsets (vertices, triangles) */
    bool tri_ring = false;                 /* NO_OVERWRITE on the triangle SRV buffer */
    std::vector<GpuVertex> vtmp;

    void unbind_all()
    {
        ID3D11ShaderResourceView *nul[7] = {};
        ctx->PSSetShaderResources(0, 7, nul);
        ctx->CSSetShaderResources(0, 4, nul);
        ID3D11UnorderedAccessView *nu = NULL;
        ctx->CSSetUnorderedAccessViews(0, 1, &nu, NULL);
        ID3D11UnorderedAccessView *nuv[2] = {};
        ctx->OMSetRenderTargetsAndUnorderedAccessViews(0, NULL, NULL, 1, 2, nuv, NULL);
        bool cbv = sh.cb_valid;
        GpuDrawCB cb = sh.cb;
        sh = Shadow();
        sh.cb_valid = cbv;     /* cb_draw's contents are only written by draw() */
        sh.cb = cb;
    }

    void set_viewport(int w, int h)
    {
        D3D11_VIEWPORT vp = { 0, 0, (float)w, (float)h, 0.0f, 1.0f };
        ctx->RSSetViewports(1, &vp);
    }
    void set_scissor(const GpuRect &r)
    {
        D3D11_RECT rc = { r.x0 * scale, r.y0 * scale, r.x1 * scale, r.y1 * scale };
        ctx->RSSetScissorRects(1, &rc);
    }

    void util_cb(const uint32_t u[8][4])
    {
        ctx->UpdateSubresource(cb_util, 0, NULL, u, 0, 0);
    }

    void rt_resize(int id, int w, int h) override
    {
        Target &o = targets[id];
        Target n;
        if (!make_target(n, o.depth, w, h)) { free_target(n); return; }
        unbind_all();
        int cw = (o.w < w ? o.w : w) * scale, ch = (o.h < h ? o.h : h) * scale;
        if (!o.depth || zrov_ok) {
            D3D11_BOX b = { 0, 0, 0, (UINT)cw, (UINT)ch, 1 };
            ctx->CopySubresourceRegion(n.tex, 0, 0, 0, 0, o.tex, 0, &b);
        } else {
            ctx->OMSetRenderTargets(0, NULL, n.dsv);
            ctx->OMSetDepthStencilState(ds_load, 0);
            ctx->RSSetState(rs);
            set_viewport(w * scale, h * scale);
            D3D11_RECT rc = { 0, 0, cw, ch };
            ctx->RSSetScissorRects(1, &rc);
            ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            ctx->IASetInputLayout(NULL);
            ctx->VSSetShader(vs_quad, NULL, 0);
            ctx->PSSetShader(ps_copy_depth, NULL, 0);
            ctx->PSSetShaderResources(3, 1, &o.srv);
            ctx->Draw(3, 0);
            unbind_all();
        }
        free_target(o);
        targets[id] = n;
    }

    void rt_load(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override
    {
        Target &t = targets[id];
        unbind_all();
        uint32_t u[8][4] = {};
        u[0][0] = bp; u[0][1] = bw; u[0][2] = (uint32_t)psm; u[0][3] = (uint32_t)scale;
        util_cb(u);
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ctx->IASetInputLayout(NULL);
        ctx->VSSetShader(vs_quad, NULL, 0);
        ctx->RSSetState(rs);
        set_viewport(t.w * scale, t.h * scale);
        set_scissor(r);
        ctx->PSSetConstantBuffers(0, 1, &cb_util);
        ctx->PSSetShaderResources(0, 1, &mem_srv);
        if (t.depth && zrov_ok) {
            ctx->OMSetRenderTargets(1, &t.rtv, NULL);
            ctx->OMSetBlendState(bs[15], NULL, 0xFFFFFFFF);
            ctx->OMSetDepthStencilState(ds[GZ_OFF][0], 0);
            ctx->PSSetShader(ps_load_depth_rt, NULL, 0);
        } else if (t.depth) {
            ctx->OMSetRenderTargets(0, NULL, t.dsv);
            ctx->OMSetDepthStencilState(ds_load, 0);
            ctx->PSSetShader(ps_load_depth, NULL, 0);
        } else {
            ctx->OMSetRenderTargets(1, &t.rtv, NULL);
            ctx->OMSetBlendState(bs[15], NULL, 0xFFFFFFFF);
            ctx->OMSetDepthStencilState(ds[GZ_OFF][0], 0);
            ctx->PSSetShader(ps_load_color, NULL, 0);
        }
        size_t q0 = prof ? pts() : 0;
        ctx->Draw(3, 0);
        if (prof) pev_add(PC_LOAD, q0, (double)(r.x1 - r.x0) * (r.y1 - r.y0));
        unbind_all();
    }

    void rt_writeback(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override
    {
        Target &t = targets[id];
        unbind_all();
        uint32_t u[8][4] = {};
        u[0][0] = bp; u[0][1] = bw; u[0][2] = (uint32_t)psm; u[0][3] = (uint32_t)scale;
        u[1][0] = (uint32_t)r.x0; u[1][1] = (uint32_t)r.y0;
        u[1][2] = (uint32_t)(r.x1 - r.x0); u[1][3] = (uint32_t)(r.y1 - r.y0);
        util_cb(u);
        ctx->CSSetConstantBuffers(0, 1, &cb_util);
        ctx->CSSetUnorderedAccessViews(0, 1, &mem_uav, NULL);
        if (t.depth) {
            ctx->CSSetShaderResources(1, 1, &t.srv);
            ctx->CSSetShader(cs_wb_depth, NULL, 0);
        } else {
            ctx->CSSetShaderResources(0, 1, &t.srv);
            ctx->CSSetShader(cs_wb_color, NULL, 0);
        }
        size_t q0 = prof ? pts() : 0;
        ctx->Dispatch((UINT)(r.x1 - r.x0 + 7) / 8, (UINT)(r.y1 - r.y0 + 7) / 8, 1);
        if (prof) pev_add(PC_WB, q0, (double)(r.x1 - r.x0) * (r.y1 - r.y0));
        unbind_all();
        ctx->CSSetShader(NULL, NULL, 0);
    }

    bool rt_reinterpret(int dst, uint32_t dbp, uint32_t dbw, int dpsm, const GpuRect &dr, int src, uint32_t sbp, uint32_t sbw,
                        int spsm, const GpuRect &sr) override
    {
        if (dst == src || dst < 0 || src < 0 || (size_t)dst >= targets.size() || (size_t)src >= targets.size() ||
            !targets[dst].used || !targets[src].used || targets[dst].depth || targets[src].depth)
            return false;
        Target &d = targets[dst], &s = targets[src];
        if (sr.x0 < 0 || sr.y0 < 0 || sr.x1 > s.w || sr.y1 > s.h || sr.x1 <= sr.x0 || sr.y1 <= sr.y0 || dr.x0 < 0 ||
            dr.y0 < 0 || dr.x1 > d.w || dr.y1 > d.h || dr.x1 <= dr.x0 || dr.y1 <= dr.y0)
            return false;
        if (!scr) {
            D3D11_BUFFER_DESC bd = {};
            bd.ByteWidth = GS_VRAM_BYTES;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
            bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
            if (FAILED(dev->CreateBuffer(&bd, NULL, &scr))) return false;
            D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
            sd.Format = DXGI_FORMAT_R32_TYPELESS;
            sd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
            sd.BufferEx.NumElements = GS_VRAM_BYTES / 4;
            sd.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
            D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
            ud.Format = DXGI_FORMAT_R32_TYPELESS;
            ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
            ud.Buffer.NumElements = GS_VRAM_BYTES / 4;
            ud.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
            if (FAILED(dev->CreateShaderResourceView(scr, &sd, &scr_srv)) || FAILED(dev->CreateUnorderedAccessView(scr, &ud, &scr_uav))) {
                REL(scr_srv); REL(scr_uav); REL(scr);
                return false;
            }
        }
        unbind_all();
        /* bytes the source does not cover (CT24's high byte, pixels outside sr) as local memory has them */
        ctx->CopyResource(scr, mem);
        for (int py = 0; py < scale; py++)
            for (int px = 0; px < scale; px++) {
                uint32_t u[8][4] = {};
                u[0][0] = sbp; u[0][1] = sbw; u[0][2] = (uint32_t)spsm; u[0][3] = (uint32_t)scale;
                u[1][0] = (uint32_t)sr.x0; u[1][1] = (uint32_t)sr.y0;
                u[1][2] = (uint32_t)(sr.x1 - sr.x0); u[1][3] = (uint32_t)(sr.y1 - sr.y0);
                u[2][0] = (uint32_t)px; u[2][1] = (uint32_t)py; u[2][2] = 1;
                util_cb(u);
                ctx->CSSetConstantBuffers(0, 1, &cb_util);
                ctx->CSSetUnorderedAccessViews(0, 1, &scr_uav, NULL);
                ctx->CSSetShaderResources(0, 1, &s.srv);
                ctx->CSSetShader(cs_wb_color, NULL, 0);
                ctx->Dispatch((UINT)(sr.x1 - sr.x0 + 7) / 8, (UINT)(sr.y1 - sr.y0 + 7) / 8, 1);
                unbind_all();
                ctx->CSSetShader(NULL, NULL, 0);
                uint32_t v[8][4] = {};
                v[0][0] = dbp; v[0][1] = dbw; v[0][2] = (uint32_t)dpsm; v[0][3] = (uint32_t)scale;
                v[1][0] = (uint32_t)px; v[1][1] = (uint32_t)py; v[1][2] = 1;
                util_cb(v);
                ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                ctx->IASetInputLayout(NULL);
                ctx->VSSetShader(vs_quad, NULL, 0);
                ctx->RSSetState(rs);
                set_viewport(d.w * scale, d.h * scale);
                set_scissor(dr);
                ctx->PSSetConstantBuffers(0, 1, &cb_util);
                ctx->PSSetShaderResources(0, 1, &scr_srv);
                ctx->OMSetRenderTargets(1, &d.rtv, NULL);
                ctx->OMSetBlendState(bs[15], NULL, 0xFFFFFFFF);
                ctx->OMSetDepthStencilState(ds[GZ_OFF][0], 0);
                ctx->PSSetShader(ps_load_color, NULL, 0);
                ctx->Draw(3, 0);
                unbind_all();
            }
        return true;
    }

    bool rt_copy(int dst, int dx, int dy, int src, const GpuRect &sr) override
    {
        if (dst == src || dst < 0 || src < 0 || (size_t)dst >= targets.size() || (size_t)src >= targets.size() ||
            !targets[dst].used || !targets[src].used)
            return false;
        Target &d = targets[dst], &s = targets[src];
        if (d.depth != s.depth || (d.depth && !zrov_ok)) return false;   /* (as rt_resize copies) */
        if (sr.x0 < 0 || sr.y0 < 0 || sr.x1 > s.w || sr.y1 > s.h || sr.x1 <= sr.x0 || sr.y1 <= sr.y0 || dx < 0 ||
            dy < 0 || dx + (sr.x1 - sr.x0) > d.w || dy + (sr.y1 - sr.y0) > d.h)
            return false;
        unbind_all();
        D3D11_BOX b = { (UINT)(sr.x0 * scale), (UINT)(sr.y0 * scale), 0, (UINT)(sr.x1 * scale), (UINT)(sr.y1 * scale), 1 };
        ctx->CopySubresourceRegion(d.tex, 0, (UINT)(dx * scale), (UINT)(dy * scale), 0, s.tex, 0, &b);
        return true;
    }

    int rt_read(int id, const GpuRect &r, uint32_t *out) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used || targets[id].depth)
            return -1;
        Target &t = targets[id];
        int W = (r.x1 - r.x0) * scale, H = (r.y1 - r.y0) * scale;
        if (W <= 0 || H <= 0) return -1;
        D3D11_TEXTURE2D_DESC td = {};
        td.Width = (UINT)W; td.Height = (UINT)H;
        td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
        td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        td.Usage = D3D11_USAGE_STAGING;
        td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        ID3D11Texture2D *st = NULL;
        if (FAILED(dev->CreateTexture2D(&td, NULL, &st))) return -1;
        D3D11_BOX b = { (UINT)(r.x0 * scale), (UINT)(r.y0 * scale), 0,
                        (UINT)(r.x1 * scale), (UINT)(r.y1 * scale), 1 };
        ctx->CopySubresourceRegion(st, 0, 0, 0, 0, t.tex, 0, &b);
        D3D11_MAPPED_SUBRESOURCE m;
        int rc = -1;
        if (SUCCEEDED(ctx->Map(st, 0, D3D11_MAP_READ, 0, &m))) {
            for (int y = 0; y < H; y++)
                memcpy(out + (size_t)y * W, (const uint8_t *)m.pData + (size_t)y * m.RowPitch,
                       (size_t)W * 4);
            ctx->Unmap(st, 0);
            rc = 0;
        }
        st->Release();
        return rc;
    }

    /* --------------------------------------------------------- drawing */
    void set_clut(const GpuClutCB &c) override
    {
        ctx->UpdateSubresource(cb_clut, 0, NULL, &c, 0, 0);
    }
    /* the words (two cells each) whose own[] is 0; the others hold a GPU-side load */
    void set_clut_part(const GpuClutCB &c, const uint8_t *own) override
    {
        const uint32_t *w = &c.c[0][0];
        for (uint32_t i = 0; i < 256;) {
            if (own[i]) { i++; continue; }
            uint32_t e = i;
            while (e < 256 && !own[e]) e++;
            D3D11_BOX b = { i * 4u, 0, 0, e * 4u, 1, 1 };
            ctx->UpdateSubresource(cb_clut, 0, &b, w + i, 0, 0);
            i = e;
        }
    }
    bool clut_load_gpu(const uint32_t u[3][4]) override
    {
        if (!cs_clut || !clut_uav) return false;
        unbind_all();
        uint32_t uu[8][4] = {};
        memcpy(uu, u, 3 * 16);
        util_cb(uu);
        ctx->CSSetConstantBuffers(0, 1, &cb_util);
        ID3D11UnorderedAccessView *uavs[2] = { mem_uav, clut_uav };
        ctx->CSSetUnorderedAccessViews(0, 2, uavs, NULL);
        ctx->CSSetShader(cs_clut, NULL, 0);
        ctx->Dispatch(4, 1, 1);
        ID3D11UnorderedAccessView *nu[2] = {};
        ctx->CSSetUnorderedAccessViews(0, 2, nu, NULL);
        ctx->CSSetShader(NULL, NULL, 0);
        return true;
    }
    /* local->local copy (docs/NATIVE-RENDER.md "Checkpoint 10"): the source pixels into l2l_buf,
     * then written at the destination (both in the mirror: the copy reads the source as it was).
     * u: (sbp, sbw, spsm, sx) (sy, w, h, dbp) (dbw, dpsm, dx, dy) */
    bool mem_copy(const uint32_t u[3][4]) override
    {
        if (!cs_l2l_read || !cs_l2l_write) return false;
        uint32_t n = u[1][1] * u[1][2];
        if (!n || n > (1u << 22)) return false;
        if (!l2l_buf) {
            D3D11_BUFFER_DESC bd = {};
            bd.ByteWidth = (1u << 22) * 4u;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
            if (FAILED(dev->CreateBuffer(&bd, NULL, &l2l_buf))) return false;
            D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
            ud.Format = DXGI_FORMAT_R32_UINT;
            ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
            ud.Buffer.NumElements = 1u << 22;
            if (FAILED(dev->CreateUnorderedAccessView(l2l_buf, &ud, &l2l_uav))) return false;
        }
        unbind_all();
        uint32_t uu[8][4] = {};
        memcpy(uu, u, 3 * 16);
        util_cb(uu);
        ctx->CSSetConstantBuffers(0, 1, &cb_util);
        ID3D11UnorderedAccessView *uavs[3] = { mem_uav, NULL, l2l_uav };
        ctx->CSSetUnorderedAccessViews(0, 3, uavs, NULL);
        ctx->CSSetShader(cs_l2l_read, NULL, 0);
        ctx->Dispatch((u[1][1] + 7) / 8, (u[1][2] + 7) / 8, 1);
        ctx->CSSetShader(cs_l2l_write, NULL, 0);
        ctx->Dispatch((u[1][1] + 7) / 8, (u[1][2] + 7) / 8, 1);
        ID3D11UnorderedAccessView *nu[3] = {};
        ctx->CSSetUnorderedAccessViews(0, 3, nu, NULL);
        ctx->CSSetShader(NULL, NULL, 0);
        return true;
    }

    bool mem_xfer_batch(const uint8_t *bytes, uint32_t nbytes, const uint32_t *desc, uint32_t ndesc, uint32_t npx) override
    {
        if (!cs_xfer || !merge_srv || !ndesc || !npx || nbytes > XFER_BYTES || ndesc > XFER_DESCS) return false;
        if (!xdesc_buf) {
            D3D11_BUFFER_DESC bd = {};
            bd.ByteWidth = XFER_DESCS * 32u;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
            if (FAILED(dev->CreateBuffer(&bd, NULL, &xdesc_buf))) return false;
            D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
            sd.Format = DXGI_FORMAT_R32_TYPELESS;
            sd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
            sd.BufferEx.NumElements = XFER_DESCS * 8u;
            sd.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
            if (FAILED(dev->CreateShaderResourceView(xdesc_buf, &sd, &xdesc_srv))) return false;
        }
        uint32_t nb = (nbytes + 15u) & ~15u;
        D3D11_BOX b = { 0, 0, 0, nb ? nb : 16u, 1, 1 };
        ctx->UpdateSubresource(merge_buf, 0, &b, bytes, nb, nb);
        D3D11_BOX db = { 0, 0, 0, ndesc * 32u, 1, 1 };
        ctx->UpdateSubresource(xdesc_buf, 0, &db, desc, ndesc * 32u, ndesc * 32u);
        unbind_all();
        uint32_t uu[8][4] = {};
        uu[0][0] = ndesc;
        uu[0][1] = npx;
        util_cb(uu);
        ctx->CSSetConstantBuffers(0, 1, &cb_util);
        ctx->CSSetUnorderedAccessViews(0, 1, &mem_uav, NULL);
        ID3D11ShaderResourceView *srvs[2] = { merge_srv, xdesc_srv };
        ctx->CSSetShaderResources(2, 2, srvs);
        ctx->CSSetShader(cs_xfer, NULL, 0);
        uint32_t groups = (npx + 63u) / 64u;
        ctx->Dispatch(groups < 32768u ? groups : 32768u, (groups + 32767u) / 32768u, 1);
        ID3D11ShaderResourceView *nul[2] = {};
        ctx->CSSetShaderResources(2, 2, nul);
        ID3D11UnorderedAccessView *nu = NULL;
        ctx->CSSetUnorderedAccessViews(0, 1, &nu, NULL);
        ctx->CSSetShader(NULL, NULL, 0);
        return true;
    }

    bool clut_read(GpuClutCB *out) override
    {
        if (!clut_stage) return false;
        ctx->CopyResource(clut_stage, cb_clut);
        D3D11_MAPPED_SUBRESOURCE ms;
        if (FAILED(ctx->Map(clut_stage, 0, D3D11_MAP_READ, 0, &ms))) return false;
        memcpy(out, ms.pData, sizeof *out);
        ctx->Unmap(clut_stage, 0);
        return true;
    }

    void ensure_snapshot(Target &t)
    {
        if (t.snap) return;
        D3D11_TEXTURE2D_DESC td;
        t.tex->GetDesc(&td);
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        if (FAILED(dev->CreateTexture2D(&td, NULL, &t.snap))) return;
        dev->CreateShaderResourceView(t.snap, &srv_unorm, &t.snap_srv);
    }

    /* copy the native rect r of target t into its snapshot (same place) */
    void snapshot_rect(Target &t, const GpuRect &r)
    {
        ensure_snapshot(t);
        int x0 = r.x0 < 0 ? 0 : r.x0, y0 = r.y0 < 0 ? 0 : r.y0;
        int x1 = r.x1 > t.w ? t.w : r.x1, y1 = r.y1 > t.h ? t.h : r.y1;
        if (x1 > x0 && y1 > y0 && t.snap) {
            D3D11_BOX b = { (UINT)(x0 * scale), (UINT)(y0 * scale), 0,
                            (UINT)(x1 * scale), (UINT)(y1 * scale), 1 };
            ctx->CopySubresourceRegion(t.snap, 0, b.left, b.top, 0, t.tex, 0, &b);
        }
    }

    void draw(const GpuDraw &g) override
    {
#if NR_EXACT
        Target &ct = targets[g.color_rt];
        Target *zt = g.depth_rt >= 0 ? &targets[g.depth_rt] : NULL;
        const bool rov = g.rov && rov_ok && ct.uav;
        /* both snapshots hold the pre-draw contents, so they share one
         * texture (blending reads the box, texturing the texel rect).
         * Copies need nothing unbound. */
        size_t qs = prof && ((g.need_dst && !rov) || (g.tex_rt >= 0 && g.tex_snap)) ? pts() : (size_t)-1;
        if (g.need_dst && !rov) snapshot_rect(ct, g.dst);
        if (g.tex_rt >= 0 && g.tex_snap) snapshot_rect(ct, g.tex_rect);
        if (qs != (size_t)-1) pev_add(PC_SNAP, qs, 0);
        /* decoded texture: a cached copy, or decode now */
        GpuDrawCB cbx = g.cb;
        ID3D11ShaderResourceView *dsrv = NULL;
        ID3D11Resource *dres = NULL;
        int pcat = (rov ? 1 : 0) | (g.tex_rt >= 0 ? 2 : 0) | (g.ntris ? 8 : 0) | ((g.cb.d[0][3] & GF_TME) ? 16 : 0);
        if (g.dec) {
            size_t q0 = prof ? pts() : 0;
            uint64_t nd = n_decodes;
            DecTex *e = dec_get(g);
            if (prof && n_decodes != nd)
                pev_add(PC_DECODE, q0, (double)(g.dec_rect.x1 - g.dec_rect.x0) * (g.dec_rect.y1 - g.dec_rect.y0));
            if (e) pcat |= 4;
            if (e) {
                dsrv = e->srv;
                dres = e->tex;
                cbx.d[3][3] |= GD_DECODED;
                cbx.d[10][2] = (uint32_t)g.dec_rect.x0 | ((uint32_t)g.dec_rect.y0 << 16);
                cbx.d[10][3] = (uint32_t)g.dec_rect.x1 | ((uint32_t)g.dec_rect.y1 << 16);
            }
        }
        /* vertices and triangles: rings, NO_OVERWRITE until they wrap */
        D3D11_MAPPED_SUBRESOURCE m;
        uint32_t n = g.nverts > MAX_VERTS ? MAX_VERTS : g.nverts;
        uint32_t tbase = 0;
        if (g.ntris && tri_buf) {
            uint32_t nt = g.ntris > MAX_VERTS / 3 + 1 ? MAX_VERTS / 3 + 1 : g.ntris;
            D3D11_MAP mm = D3D11_MAP_WRITE_DISCARD;
            if (tri_ring && tri_pos + nt <= MAX_VERTS / 3 + 1) mm = D3D11_MAP_WRITE_NO_OVERWRITE;
            else tri_pos = 0;
            if (FAILED(ctx->Map(tri_buf, 0, mm, 0, &m))) return;
            memcpy((GpuTri *)m.pData + tri_pos, g.tris, nt * sizeof(GpuTri));
            ctx->Unmap(tri_buf, 0);
            tbase = tri_pos;
            tri_pos += nt;
        }
        {
            D3D11_MAP mm = D3D11_MAP_WRITE_NO_OVERWRITE;
            if (vb_pos + n > MAX_VERTS) { mm = D3D11_MAP_WRITE_DISCARD; vb_pos = 0; }
            if (FAILED(ctx->Map(vb, 0, mm, 0, &m))) return;
            GpuVertex *dstv = (GpuVertex *)m.pData + vb_pos;
            if (!tbase) {
                memcpy(dstv, g.verts, n * sizeof(GpuVertex));
            } else {
                /* exact primitives index their GpuTri: rebase into the ring
                 * (indices stay below 2^24, exact as floats) */
                vtmp.assign(g.verts, g.verts + n);
                for (uint32_t i = 0; i < n; i++)
                    if (vtmp[i].vflags & 64) vtmp[i].spr_u0 += (float)tbase;
                memcpy(dstv, vtmp.data(), n * sizeof(GpuVertex));
            }
            ctx->Unmap(vb, 0);
        }
        uint32_t vstart = vb_pos;
        vb_pos += n;
        if (!sh.pipe) {
            UINT stride = sizeof(GpuVertex), off = 0;
            ctx->IASetVertexBuffers(0, 1, &vb, &stride, &off);
            ctx->IASetInputLayout(layout);
            ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            ctx->VSSetShader(vs_main, NULL, 0);
            ctx->VSSetConstantBuffers(0, 1, &cb_draw);
            ctx->PSSetConstantBuffers(0, 1, &cb_draw);
            ctx->RSSetState(rs);
            sh.pipe = true;
        }
        const bool zr = zt && zrov_ok;   /* depth through its ordered view */
        ID3D11PixelShader *ps = zr ? (g.ntris ? (rov ? ps_rov_z : ps_main_z) : (rov ? ps_rov_fz : ps_main_fz))
                                   : (g.ntris ? (rov ? ps_rov : ps_main) : (rov ? ps_rov_f : ps_main_f));
        if (g.ntris && exact_ok && !(g.cb.d[0][3] & GF_TME) && ps_xn[rov ? 1 : 0][zr ? 1 : 0])
            ps = ps_xn[rov ? 1 : 0][zr ? 1 : 0];
        if (sh.ps != ps) { ctx->PSSetShader(ps, NULL, 0); sh.ps = ps; }
        if (sh.vp_w != g.vp_w * scale || sh.vp_h != g.vp_h * scale) {
            set_viewport(g.vp_w * scale, g.vp_h * scale);
            sh.vp_w = g.vp_w * scale; sh.vp_h = g.vp_h * scale;
        }
        {
            D3D11_RECT rc = { g.scissor.x0 * scale, g.scissor.y0 * scale, g.scissor.x1 * scale,
                              g.scissor.y1 * scale };
            if (memcmp(&rc, &sh.sc, sizeof rc)) { ctx->RSSetScissorRects(1, &rc); sh.sc = rc; }
        }
        /* outputs first: an input view of a texture that becomes an output
         * would otherwise be unbound by the runtime behind the shadow */
        ID3D11RenderTargetView *rtv = rov ? NULL : ct.rtv;
        ID3D11DepthStencilView *dsv = zt && !zr ? zt->dsv : NULL;
        ID3D11UnorderedAccessView *uav = rov ? ct.uav : NULL;
        ID3D11UnorderedAccessView *zuav = zr ? zt->uav : NULL;
        if (rtv != sh.rtv || dsv != sh.dsv || uav != sh.uav || zuav != sh.zuav) {
            ID3D11ShaderResourceView *nul = NULL;
            for (int i = 0; i < 7; i++)
                if (sh.srv[i] && (sh.srv_res[i] == ct.tex || (zt && sh.srv_res[i] == zt->tex))) {
                    ctx->PSSetShaderResources((UINT)i, 1, &nul);
                    sh.srv[i] = NULL; sh.srv_res[i] = NULL;
                }
            if (uav || zuav || sh.uav || sh.zuav) {
                /* u1: the colour target's ordered view, u2: the depth target's */
                ID3D11UnorderedAccessView *uv[2] = { uav, zuav };
                ctx->OMSetRenderTargetsAndUnorderedAccessViews(1, &rtv, dsv, 1, 2, uv, NULL);
            } else {
                ctx->OMSetRenderTargets(1, &rtv, dsv);
            }
            sh.rtv = rtv; sh.dsv = dsv; sh.uav = uav; sh.zuav = zuav;
        }
        ID3D11ShaderResourceView *srv[7] = { mem_srv, g.need_dst && !rov ? ct.snap_srv : NULL, NULL, NULL,
                                             g.ntris ? tri_srv : NULL, clut_srv, dsrv };
        ID3D11Resource *sres[7] = { mem, g.need_dst && !rov ? ct.snap : NULL, NULL, NULL,
                                    g.ntris ? tri_buf : NULL, cb_clut, dres };
        if (g.tex_rt >= 0) {
            /* direct sampling: colour targets at t2, depth targets at t3 */
            Target &st = targets[g.tex_rt];
            int slot = st.depth ? 3 : 2;
            srv[slot] = g.tex_snap ? ct.snap_srv : st.srv;
            sres[slot] = g.tex_snap ? ct.snap : st.tex;
        }
        {
            int lo = 7, hi = -1;
            for (int i = 0; i < 7; i++)
                if (srv[i] != sh.srv[i]) { if (i < lo) lo = i; hi = i; }
            if (hi >= lo) ctx->PSSetShaderResources((UINT)lo, (UINT)(hi - lo + 1), srv + lo);
            for (int i = 0; i < 7; i++) { sh.srv[i] = srv[i]; sh.srv_res[i] = sres[i]; }
        }
        if (rov) {
            /* one draw: both alpha-test passes are resolved per pixel in the
             * shader (ROVCTL); a depth target only with a test that always
             * passes and one Z write mask (the core checks) */
            if (zr) {
                uint32_t zc = (uint32_t)g.zfunc;
                for (int p = 0; p < g.npass; p++)
                    if (g.pass[p].zwrite) zc |= g.pass[p].failpass ? 8u : 4u;
                cbx.d[11][2] = zc;
            }
            put_cb(cbx);
            set_om_state(bs[0], ds[zt && !zr ? g.zfunc : GZ_OFF][zt && !zr && g.pass[0].zwrite ? 1 : 0]);
            size_t q0 = prof ? pts() : 0;
            ctx->Draw(n, vstart);
            if (prof) pev_add(pcat, q0, (double)(g.dst.x1 - g.dst.x0) * (g.dst.y1 - g.dst.y0) * scale * scale);
            return;
        }
        for (int p = 0; p < g.npass; p++) {
            GpuDrawCB cb = cbx;
            if (g.pass[p].failpass) cb.d[0][3] |= GF_FAILPASS;
            if (zr) cb.d[11][2] = (uint32_t)g.zfunc | (g.pass[p].zwrite ? 4u : 0u);
            put_cb(cb);
            set_om_state(bs[g.pass[p].cmask & 15],
                         ds[zt && !zr ? g.zfunc : GZ_OFF][zt && !zr && g.pass[p].zwrite ? 1 : 0]);
            size_t q0 = prof ? pts() : 0;
            ctx->Draw(n, vstart);
            if (prof) pev_add(pcat, q0, (double)(g.dst.x1 - g.dst.x0) * (g.dst.y1 - g.dst.y0) * scale * scale);
        }
#else
        (void)g;   /* (native-only: no GS-exact draw path) */
#endif
    }

    /* ------------------------------------------------ native draws
     * docs/NATIVE-RENDER.md: model meshes with their own pipeline
     * (nr_draw.hlsl) into the core's render targets.  Hardware depth (DSV),
     * blend and cull state, a hardware-sampled decoded texture. */
    bool nr_ok = false;
    ID3D11VertexShader *vs_nr = NULL, *vs_im = NULL;
    ID3D11PixelShader *ps_nr = NULL, *ps_nr_z = NULL, *ps_nr_c = NULL, *ps_nr_cz = NULL;
    ID3D11InputLayout *layout_nr = NULL, *layout_im = NULL;
    /* immediate primitives (gpu_nr_im_submit): a dynamic vertex ring, no depth bias */
    ID3D11Buffer *im_vb = NULL;
    uint32_t im_vb_bytes = 0, im_vb_off = 0;
    ID3D11RasterizerState *rs_im = NULL;
    ID3D11Buffer *cb_nr = NULL, *cb_nr_bones = NULL;
    ID3D11RasterizerState *rs_nr[3] = {};
    ID3D11SamplerState *smp_nr[2][2][2] = {};
    struct NrMeshBuf { ID3D11Buffer *vb = NULL, *ib = NULL; uint32_t nidx = 0; uint64_t used = 0; };
    std::unordered_map<uint32_t, NrMeshBuf> nr_mesh;
    uint64_t nr_clock = 0;
    struct NrTex { uint32_t key[8]; GpuRect rect; int valid; int tw, th; uint64_t used; uint64_t h;
                   ID3D11Texture2D *tex; ID3D11ShaderResourceView *srv; ID3D11UnorderedAccessView *uav; };
    /* the native texture cache (docs/NATIVE-RENDER.md "Native texture cache"): up to
     * NR_TEX_MAX entries / nr_tex_budget bytes, found through nr_map (hash of key + rect),
     * least recently used evicted.  (Was a 512-entry list searched linearly: the battle's and
     * the town's working sets are larger, 88 % of the decodes were textures evicted earlier.) */
    enum { NR_TEX_MAX = 4096 };
    std::vector<NrTex> nr_tex;
    std::unordered_map<uint64_t, uint32_t> nr_map;
    size_t nr_tex_bytes = 0, nr_tex_budget = 0;
    static uint64_t nr_hash(const uint32_t *key, const GpuRect &rc)
    {
        uint64_t h = 1469598103934665603ull;
        const uint8_t *p = (const uint8_t *)key;
        for (int i = 0; i < 32; i++) { h ^= p[i]; h *= 1099511628211ull; }
        p = (const uint8_t *)&rc;
        for (size_t i = 0; i < sizeof rc; i++) { h ^= p[i]; h *= 1099511628211ull; }
        return h;
    }
    NrTex *nr_find(const uint32_t *key, const GpuRect &rc, uint64_t h)
    {
        auto it = nr_map.find(h);
        if (it == nr_map.end()) return NULL;
        NrTex &e = nr_tex[it->second];
        if (e.valid && !memcmp(e.key, key, sizeof e.key) && !memcmp(&e.rect, &rc, sizeof rc)) return &e;
        return NULL;
    }
    std::unordered_map<uint32_t, ID3D11BlendState *> nr_bs;

    bool nr_init()
    {
        if (FAILED(dev->CreateVertexShader(g_VS_nr, sizeof g_VS_nr, NULL, &vs_nr))) return false;
        if (FAILED(dev->CreatePixelShader(g_PS_nr, sizeof g_PS_nr, NULL, &ps_nr))) return false;
        if (zrov_ok && FAILED(dev->CreatePixelShader(g_PS_nr_z, sizeof g_PS_nr_z, NULL, &ps_nr_z))) return false;
        if (rov_ok && FAILED(dev->CreatePixelShader(g_PS_nr_c, sizeof g_PS_nr_c, NULL, &ps_nr_c))) return false;
        if (rov_ok && zrov_ok && FAILED(dev->CreatePixelShader(g_PS_nr_cz, sizeof g_PS_nr_cz, NULL, &ps_nr_cz))) return false;
        D3D11_INPUT_ELEMENT_DESC ie[] = {
            { "POSITION", 0, DXGI_FORMAT_R16G16B16A16_SINT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL", 0, DXGI_FORMAT_R8G8B8A8_SINT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R16G16_SINT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "BLENDWEIGHT", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        if (FAILED(dev->CreateInputLayout(ie, 6, g_VS_nr, sizeof g_VS_nr, &layout_nr))) return false;
        if (FAILED(dev->CreateVertexShader(g_VS_im, sizeof g_VS_im, NULL, &vs_im))) return false;
        {
            D3D11_INPUT_ELEMENT_DESC ii[] = {
                { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "BLENDINDICES", 0, DXGI_FORMAT_R32_UINT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD", 1, DXGI_FORMAT_R32_UINT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            };
            if (FAILED(dev->CreateInputLayout(ii, 5, g_VS_im, sizeof g_VS_im, &layout_im))) return false;
            D3D11_RASTERIZER_DESC rd = {};
            rd.FillMode = D3D11_FILL_SOLID;
            rd.CullMode = D3D11_CULL_NONE;
            rd.DepthClipEnable = TRUE;
            rd.ScissorEnable = TRUE;
            if (FAILED(dev->CreateRasterizerState(&rd, &rs_im))) return false;
        }
        D3D11_BUFFER_DESC bd = {};
        /* dynamic, written with MAP_WRITE_DISCARD per draw (the driver renames
         * them; UpdateSubresource of the whole 2.5 KB block per draw cost a
         * runtime copy and allocator waits on the GS worker) */
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bd.ByteWidth = 24 * 16;           /* NrCB: 24 rows */
        if (FAILED(dev->CreateBuffer(&bd, NULL, &cb_nr))) return false;
        bd.ByteWidth = 256 * 16;          /* NrBones: the bone rows 768..1023 (skinned meshes) */
        if (FAILED(dev->CreateBuffer(&bd, NULL, &cb_nr_bones))) return false;
        for (int c = 0; c < 3; c++) {
            D3D11_RASTERIZER_DESC rd = {};
            rd.FillMode = D3D11_FILL_SOLID;
            rd.CullMode = c == 0 ? D3D11_CULL_NONE : c == 1 ? D3D11_CULL_FRONT : D3D11_CULL_BACK;
            rd.FrontCounterClockwise = FALSE;
            rd.DepthClipEnable = TRUE;
            rd.ScissorEnable = TRUE;
            /* native depth is interpolated in float, the emulated path's
             * exactly (docs/GPU.md "Exact triangles"): a bias of a few ULP
             * toward "far" lets coplanar emulated draws over native surfaces
             * (plane shadows, decals) pass their GEQUAL test as on the GS */
            {
                const char *zb = getenv("RG_NR_ZBIAS");
                rd.DepthBias = zb ? atoi(zb) : -2;
            }
            if (FAILED(dev->CreateRasterizerState(&rd, &rs_nr[c]))) return false;
        }
        for (int l = 0; l < 2; l++)
            for (int u = 0; u < 2; u++)
                for (int v = 0; v < 2; v++) {
                    D3D11_SAMPLER_DESC sm = {};
                    sm.Filter = l ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
                    sm.AddressU = u ? D3D11_TEXTURE_ADDRESS_CLAMP : D3D11_TEXTURE_ADDRESS_WRAP;
                    sm.AddressV = v ? D3D11_TEXTURE_ADDRESS_CLAMP : D3D11_TEXTURE_ADDRESS_WRAP;
                    sm.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
                    sm.MaxLOD = 0.0f;
                    if (FAILED(dev->CreateSamplerState(&sm, &smp_nr[l][u][v]))) return false;
                }
        return true;
    }

    void nr_release()
    {
        REL(vs_nr); REL(ps_nr); REL(ps_nr_z); REL(ps_nr_c); REL(ps_nr_cz); REL(layout_nr); REL(cb_nr); REL(cb_nr_bones);
        REL(vs_im); REL(layout_im); REL(im_vb); REL(rs_im);
        im_vb_bytes = im_vb_off = 0;
        for (int c = 0; c < 3; c++) REL(rs_nr[c]);
        for (int i = 0; i < 8; i++) REL(smp_nr[i >> 2][(i >> 1) & 1][i & 1]);
        for (auto &e : nr_mesh) { REL(e.second.vb); REL(e.second.ib); }
        nr_mesh.clear();
        for (NrTex &t : nr_tex) { REL(t.srv); REL(t.uav); REL(t.tex); }
        nr_tex.clear();
        nr_map.clear();
        nr_tex_bytes = 0;
        for (auto &e : nr_bs) REL(e.second);
        nr_bs.clear();
    }

    /* pre-warmed meshes (nr_mesh_prewarm, created on another thread: the device is
     * free-threaded), taken into nr_mesh by the GS thread at the next lookup that misses */
    std::mutex pre_mx;
    std::vector<std::pair<uint32_t, NrMeshBuf>> pre;
    std::atomic<int> pre_n{0};
    void nr_mesh_prewarm(const gpu_nr_mesh &m) override
    {
        if (!m.nvtx || !m.nidx || m.stride != 28) return;
        NrMeshBuf b;
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_IMMUTABLE;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.ByteWidth = m.nvtx * 28;
        D3D11_SUBRESOURCE_DATA sd = { m.vtx, 0, 0 };
        if (FAILED(dev->CreateBuffer(&bd, &sd, &b.vb))) return;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.ByteWidth = m.nidx * 4;
        sd.pSysMem = m.idx;
        if (FAILED(dev->CreateBuffer(&bd, &sd, &b.ib))) { REL(b.vb); return; }
        b.nidx = m.nidx;
        std::lock_guard<std::mutex> lk(pre_mx);
        pre.push_back(std::make_pair(m.id, b));
        pre_n.store((int)pre.size());
    }
    NrMeshBuf *nr_mesh_get(const gpu_nr_mesh &m)
    {
        nr_clock++;
        auto it = nr_mesh.find(m.id);
        if (it != nr_mesh.end()) { it->second.used = nr_clock; return &it->second; }
        if (pre_n.load()) {
            std::vector<std::pair<uint32_t, NrMeshBuf>> got;
            {
                std::lock_guard<std::mutex> lk(pre_mx);
                got.swap(pre);
                pre_n.store(0);
            }
            NrMeshBuf *hit = NULL;
            for (auto &e : got) {
                auto o = nr_mesh.find(e.first);
                if (o != nr_mesh.end()) { REL(e.second.vb); REL(e.second.ib); continue; }
                e.second.used = nr_clock;
                NrMeshBuf &nb = (nr_mesh[e.first] = e.second);
                n_nr_mesh_pre++;
                if (e.first == m.id) hit = &nb;
            }
            if (hit) return hit;
        }
        if (!m.nvtx || !m.nidx || m.stride != 28) return NULL;
        if (nr_mesh.size() >= 8192) {   /* LRU: drop the least recently used eighth */
            std::vector<std::pair<uint64_t, uint32_t>> u;
            for (auto &e : nr_mesh) u.push_back(std::make_pair(e.second.used, e.first));
            std::sort(u.begin(), u.end());
            for (size_t i = 0; i < u.size() / 8; i++) {
                NrMeshBuf &b = nr_mesh[u[i].second];
                REL(b.vb); REL(b.ib);
                nr_mesh.erase(u[i].second);
            }
        }
        NrMeshBuf b;
        D3D11_BUFFER_DESC bd = {};
        bd.Usage = D3D11_USAGE_IMMUTABLE;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.ByteWidth = m.nvtx * 28;
        D3D11_SUBRESOURCE_DATA sd = { m.vtx, 0, 0 };
        if (FAILED(dev->CreateBuffer(&bd, &sd, &b.vb))) return NULL;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.ByteWidth = m.nidx * 4;
        sd.pSysMem = m.idx;
        if (FAILED(dev->CreateBuffer(&bd, &sd, &b.ib))) { REL(b.vb); return NULL; }
        b.nidx = m.nidx;
        b.used = nr_clock;
        n_nr_mesh++;
        return &(nr_mesh[m.id] = b);
    }

    bool nr_tex_cached(const uint32_t *key, const GpuRect &rc) override
    {
        return nr_find(key, rc, nr_hash(key, rc)) != NULL;
    }

    /* interpolated presentation (nr_interp.h): whole-target copies (pre-images, saved state) */
    int rt_clone(int src) override
    {
        if (src < 0 || (size_t)src >= targets.size() || !targets[src].used) return -1;
        int depth = targets[src].depth, w = targets[src].w, h = targets[src].h;
        int id = rt_create(depth, w, h);   /* (may grow `targets`) */
        if (id < 0) return -1;
        unbind_all();
        ctx->CopyResource(targets[id].tex, targets[src].tex);
        return id;
    }
    bool rt_put(int dst, int src) override
    {
        if (dst == src || dst < 0 || src < 0 || (size_t)dst >= targets.size() || (size_t)src >= targets.size() ||
            !targets[dst].used || !targets[src].used)
            return false;
        const Target &d = targets[dst], &s = targets[src];
        if (d.depth != s.depth || d.w != s.w || d.h != s.h) return false;
        unbind_all();
        ctx->CopyResource(d.tex, s.tex);
        return true;
    }

    /* the decoded level-0 texture (CS_decode into RGBA8 viewed as R32_UINT) */
    NrTex *nr_tex_get(const GpuNrDraw &g)
    {
        const GpuRect &rc = g.dec_rect;
        nr_clock++;
        uint64_t hk = nr_hash(g.dec_key, rc);
        if (NrTex *f = nr_find(g.dec_key, rc, hk)) {
            f->used = nr_clock;
            return f;
        }
        if (g.tex_cached_only) return NULL;   /* replay: never from local memory */
        {
            /* $RG_NR_TEXLOG=FIRST:COUNT: log misses FIRST .. FIRST + COUNT - 1 (key, rect, cache size) */
            static long lg0 = -2, lgn, nmiss;
            if (lg0 == -2) {
                const char *e = getenv("RG_NR_TEXLOG");
                lg0 = -1;
                if (e) { lg0 = atol(e); const char *c = strchr(e, ':'); lgn = c ? atol(c + 1) : 100; }
            }
            if (lg0 >= 0 && nmiss >= lg0 && nmiss < lg0 + lgn)
                fprintf(stderr, "nr tex miss %ld: key %08x %08x %08x %08x %08x %08x %08x %08x rect %d,%d-%d,%d cache %zu%s\n", nmiss,
                        g.dec_key[0], g.dec_key[1], g.dec_key[2], g.dec_key[3], g.dec_key[4], g.dec_key[5], g.dec_key[6],
                        g.dec_key[7], rc.x0, rc.y0, rc.x1, rc.y1, nr_tex.size(), g.dec_rgba ? " (core-decoded)" : "");
            nmiss++;
        }
        int w = rc.x1 - rc.x0, h = rc.y1 - rc.y0;
        if (w <= 0 || h <= 0 || w > 1024 || h > 1024) return NULL;
        NrTex *e = NULL;
        if (!nr_tex_budget) {
            const char *mb = getenv("RG_NR_TEXCACHE_MB");
            nr_tex_budget = (size_t)(mb ? atol(mb) : 384) << 20;
            if (nr_tex_budget < (8u << 20)) nr_tex_budget = 8u << 20;
            nr_tex.reserve(NR_TEX_MAX);
        }
        size_t need = (size_t)w * h * 4;
        if (nr_tex.size() < NR_TEX_MAX && nr_tex_bytes + need <= nr_tex_budget) {
            nr_tex.push_back(NrTex());
            e = &nr_tex.back();
            memset(e, 0, sizeof *e);
        } else {
            /* full: the least recently used entry of this size when it is among the least
             * recently used quarter, else the least recently used one (its texture recreated) */
            NrTex *any = NULL, *same = NULL;
            for (NrTex &c : nr_tex) {
                if (c.tw == w && c.th == h && (!same || c.used < same->used)) same = &c;
                if (!any || c.used < any->used) any = &c;
            }
            e = (same && (nr_clock - same->used) * 4 >= (nr_clock - any->used) * 3) ? same : any;
            if (e->valid) nr_map.erase(e->h);
            if (e->tw != w || e->th != h) {
                if (e->tex) nr_tex_bytes -= (size_t)e->tw * e->th * 4;
                REL(e->srv); REL(e->uav); REL(e->tex);
                e->tw = e->th = 0;
            }
        }
        if (!e->tex) {
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = (UINT)w; td.Height = (UINT)h;
            td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
            td.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
            td.Usage = D3D11_USAGE_DEFAULT;
            td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
            D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
            ud.Format = DXGI_FORMAT_R32_UINT;
            ud.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &e->tex)) ||
                FAILED(dev->CreateShaderResourceView(e->tex, &srv_unorm, &e->srv)) ||
                FAILED(dev->CreateUnorderedAccessView(e->tex, &ud, &e->uav))) {
                REL(e->srv); REL(e->uav); REL(e->tex);
                e->valid = 0;
                return NULL;
            }
            e->tw = w; e->th = h;
            nr_tex_bytes += need;
        }
        if (e->valid) nr_map.erase(e->h);
        e->valid = 0;
        e->h = hk;
        nr_map[hk] = (uint32_t)(e - nr_tex.data());
        if (g.dec_rgba) {
            /* decoded by the core (a pending transfer's data) */
            ctx->UpdateSubresource(e->tex, 0, NULL, g.dec_rgba, (UINT)w * 4u, 0);
            memcpy(e->key, g.dec_key, sizeof e->key);
            e->rect = rc;
            e->valid = 1;
            e->used = nr_clock;
            n_nr_tex++;
            return e;
        }
        GpuDrawCB c = g.dec_cb;
        c.d[3][3] = 0;
        c.d[10][2] = (uint32_t)rc.x0 | ((uint32_t)rc.y0 << 16);
        c.d[10][3] = (uint32_t)rc.x1 | ((uint32_t)rc.y1 << 16);
        ctx->UpdateSubresource(cb_dec, 0, NULL, &c, 0, 0);
        ctx->CSSetShader(cs_decode, NULL, 0);
        ctx->CSSetConstantBuffers(0, 1, &cb_dec);
        ctx->CSSetShaderResources(0, 1, &mem_srv);
        ctx->CSSetShaderResources(5, 1, &clut_srv);
        ctx->CSSetUnorderedAccessViews(0, 1, &e->uav, NULL);
        ctx->Dispatch((UINT)(w + 7) / 8, (UINT)(h + 7) / 8, 1);
        ID3D11UnorderedAccessView *nu = NULL;
        ID3D11ShaderResourceView *ns = NULL;
        ctx->CSSetUnorderedAccessViews(0, 1, &nu, NULL);
        ctx->CSSetShaderResources(0, 1, &ns);
        ctx->CSSetShaderResources(5, 1, &ns);
        ctx->CSSetShader(NULL, NULL, 0);
        memcpy(e->key, g.dec_key, sizeof e->key);
        e->rect = rc;
        e->valid = 1;
        e->used = nr_clock;
        n_nr_tex++;
        return e;
    }

    /* GS blend ((A - B) * C >> 7) + D as D3D11 dual-source blending: the
     * shader outputs F = C / 128 in SV_Target1 (As or FIX); each of Cs and
     * Cd gets a coefficient a + b F (a in {0, 1}, b in {-1, 0, 1}) */
    ID3D11BlendState *nr_blend(int abe, uint32_t abcd, uint32_t cmask)
    {
        uint32_t key = (abe ? 0x100u : 0u) | (abe ? (abcd & 0xCFu) : 0u) | ((cmask & 15u) << 12);
        auto it = nr_bs.find(key);
        if (it != nr_bs.end()) return it->second;
        D3D11_BLEND_DESC b = {};
        D3D11_RENDER_TARGET_BLEND_DESC &t = b.RenderTarget[0];
        t.RenderTargetWriteMask = (UINT8)(cmask & 15u);
        if (abe) {
            int A = (int)(abcd & 3), B = (int)((abcd >> 2) & 3), D = (int)((abcd >> 6) & 3);
            int csa = D == 0, csb = (A == 0) - (B == 0), cda = D == 1, cdb = (A == 1) - (B == 1);
            auto fac = [&](int a, int bb, bool *neg) -> D3D11_BLEND {
                *neg = false;
                if (a == 0 && bb == 0) return D3D11_BLEND_ZERO;
                if (a == 1 && bb == 0) return D3D11_BLEND_ONE;
                if (a == 0 && bb == 1) return D3D11_BLEND_SRC1_ALPHA;
                if (a == 1 && bb == -1) return D3D11_BLEND_INV_SRC1_ALPHA;
                if (a == 0 && bb == -1) { *neg = true; return D3D11_BLEND_SRC1_ALPHA; }
                n_nr_blend_approx++;            /* 1 + F: not expressible */
                return D3D11_BLEND_ONE;
            };
            bool ns, nd;
            t.BlendEnable = TRUE;
            t.SrcBlend = fac(csa, csb, &ns);
            t.DestBlend = fac(cda, cdb, &nd);
            t.BlendOp = ns && !nd ? D3D11_BLEND_OP_REV_SUBTRACT : nd && !ns ? D3D11_BLEND_OP_SUBTRACT : D3D11_BLEND_OP_ADD;
            if (ns && nd) n_nr_blend_approx++;
            t.SrcBlendAlpha = D3D11_BLEND_ONE;
            t.DestBlendAlpha = D3D11_BLEND_ZERO;
            t.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        }
        ID3D11BlendState *s = NULL;
        if (FAILED(dev->CreateBlendState(&b, &s))) return NULL;
        nr_bs[key] = s;
        return s;
    }

    /* RG_NR_CPUTIME=1 (measurement): CPU time of nr_draw's phases, printed
     * every 4,000 native draws */
    int nrt_on = -1;
    double nrt_acc[5] = {}, nrt_freq = 0;
    uint64_t nrt_n = 0;
    double nrt_now()
    {
        LARGE_INTEGER c;
        if (nrt_freq == 0) { LARGE_INTEGER f; QueryPerformanceFrequency(&f); nrt_freq = (double)f.QuadPart / 1000.0; }
        QueryPerformanceCounter(&c);
        return (double)c.QuadPart / nrt_freq;
    }
    bool nr_draw(const GpuNrDraw &g) override
    {
        if (!nr_ok) return false;
        if (nrt_on < 0) { const char *e = getenv("RG_NR_CPUTIME"); nrt_on = e && atoi(e) != 0; }
        double nt0 = nrt_on ? nrt_now() : 0, nt1 = 0, nt2 = 0, nt3 = 0;
        Target &ct = targets[g.color_rt];
        Target *zt = g.depth_rt >= 0 ? &targets[g.depth_rt] : NULL;
        const bool zr = zt && !zt->dsv;            /* depth in an ordered view (zrov) */
        if (zr && (!ps_nr_z || !zt->uav)) return false;
        if (g.crov && (!g.im || !ct.uav || (zr ? !ps_nr_cz : (!ps_nr_c || zt)))) return false;
        const gpu_nr_draw *d = g.d;
        NrMeshBuf *mb = NULL;
        if (!g.im) {
            mb = nr_mesh_get(d->mesh);
            if (!mb) return false;
        } else if (!g.nim || !vs_im) {
            return false;
        }
        ID3D11BlendState *bst = nr_blend(g.abe, g.alpha_abcd, g.cmask);
        if (!bst) return false;
        unbind_all();
        NrTex *tx = NULL;
        /* a live colour target sampled directly (immediate primitives): the
         * target itself, or a copy of the texels read when it is drawn into */
        ID3D11ShaderResourceView *tsrv = NULL;
        if (g.tme && g.tex_rt >= 0) {
            if (g.tex_snap) {
                snapshot_rect(ct, g.tex_rect);
                tsrv = ct.snap_srv;
            } else {
                tsrv = targets[g.tex_rt].srv;
            }
            if (!tsrv) return false;
        } else if (g.tme) {
            size_t q0 = prof ? pts() : 0;
            uint64_t nd0 = n_nr_tex;
            tx = nr_tex_get(g);
            if (prof && n_nr_tex != nd0)
                pev_add(PC_DECODE, q0, (double)(g.dec_rect.x1 - g.dec_rect.x0) * (g.dec_rect.y1 - g.dec_rect.y0));
            if (!tx) return false;
        }
        if (nrt_on) nt1 = nrt_now();
        if (!g.im) {
            UINT stride = 28, off = 0;
            ctx->IASetVertexBuffers(0, 1, &mb->vb, &stride, &off);
            ctx->IASetIndexBuffer(mb->ib, DXGI_FORMAT_R32_UINT, 0);
            ctx->IASetInputLayout(layout_nr);
        } else {
            /* immediate vertices into the dynamic ring (NO_OVERWRITE, DISCARD at the wrap) */
            uint32_t bytes = g.nim * (uint32_t)sizeof(GpuImVtx);
            if (bytes > im_vb_bytes) {
                REL(im_vb);
                uint32_t nb = im_vb_bytes ? im_vb_bytes : (1u << 20);
                while (nb < bytes) nb *= 2;
                D3D11_BUFFER_DESC bd = {};
                bd.Usage = D3D11_USAGE_DYNAMIC;
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                bd.ByteWidth = nb;
                if (FAILED(dev->CreateBuffer(&bd, NULL, &im_vb))) { im_vb_bytes = 0; return false; }
                im_vb_bytes = nb;
                im_vb_off = nb;     /* the first map discards */
            }
            D3D11_MAPPED_SUBRESOURCE ms;
            D3D11_MAP mode = D3D11_MAP_WRITE_NO_OVERWRITE;
            if (im_vb_off + bytes > im_vb_bytes) { mode = D3D11_MAP_WRITE_DISCARD; im_vb_off = 0; }
            if (FAILED(ctx->Map(im_vb, 0, mode, 0, &ms))) return false;
            memcpy((uint8_t *)ms.pData + im_vb_off, g.im, bytes);
            ctx->Unmap(im_vb, 0);
            UINT stride = (UINT)sizeof(GpuImVtx), off = im_vb_off;
            im_vb_off += (bytes + 255u) & ~255u;
            ctx->IASetVertexBuffers(0, 1, &im_vb, &stride, &off);
            ctx->IASetInputLayout(layout_im);
        }
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        {
            D3D11_MAPPED_SUBRESOURCE ms;
            if (FAILED(ctx->Map(cb_nr, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms))) return false;
            {
                float (*all)[4] = (float (*)[4])ms.pData;
                uint32_t zc = (uint32_t)(zt ? g.zfunc : GZ_OFF) | (zt && g.zwrite ? 16u : 0u);
                memcpy(all, g.cb, sizeof g.cb);
                memcpy(&all[23][3], &zc, 4);
            }
            ctx->Unmap(cb_nr, 0);
            if (d->nbones_rows && !g.im) {
                if (FAILED(ctx->Map(cb_nr_bones, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms))) return false;
                memcpy(ms.pData, d->bones, sizeof d->bones);
                ctx->Unmap(cb_nr_bones, 0);
            }
        }
        if (nrt_on) nt2 = nrt_now();
        ctx->VSSetShader(g.im ? vs_im : vs_nr, NULL, 0);
        {
            ID3D11Buffer *cbs[2] = { cb_nr, cb_nr_bones };
            ctx->VSSetConstantBuffers(0, d->nbones_rows && !g.im ? 2 : 1, cbs);
        }
        ctx->PSSetShader(g.crov ? (zr ? ps_nr_cz : ps_nr_c) : zr ? ps_nr_z : ps_nr, NULL, 0);
        ctx->PSSetConstantBuffers(0, 1, &cb_nr);
        ctx->RSSetState(g.im ? rs_im : rs_nr[g.cull >= 0 && g.cull <= 2 ? g.cull : 0]);
        set_viewport(g.vp_w * scale, g.vp_h * scale);
        set_scissor(g.scissor);
        ID3D11RenderTargetView *rtv = ct.rtv;
        if (g.crov) {
            /* no render target: depth (u2, zrov) and colour (u3) through ordered views */
            ID3D11UnorderedAccessView *uv[2] = { zr ? zt->uav : NULL, ct.uav };
            ctx->OMSetRenderTargetsAndUnorderedAccessViews(0, NULL, NULL, 2, 2, uv, NULL);
        } else if (zr) ctx->OMSetRenderTargetsAndUnorderedAccessViews(1, &rtv, NULL, 2, 1, &zt->uav, NULL);
        else ctx->OMSetRenderTargets(1, &rtv, zt ? zt->dsv : NULL);
        if (tsrv) {
            ctx->PSSetShaderResources(0, 1, &tsrv);
            ID3D11SamplerState *sm = smp_nr[g.lin ? 1 : 0][1][1];
            ctx->PSSetSamplers(0, 1, &sm);
        } else if (tx) {
            ctx->PSSetShaderResources(0, 1, &tx->srv);
            ID3D11SamplerState *sm = smp_nr[g.lin ? 1 : 0][g.clamp_u ? 1 : 0][g.clamp_v ? 1 : 0];
            ctx->PSSetSamplers(0, 1, &sm);
        }
        float bf[4] = { 0, 0, 0, 0 };
        ctx->OMSetBlendState(bst, bf, 0xFFFFFFFFu);
        ctx->OMSetDepthStencilState(ds[zt && !zr ? g.zfunc : GZ_OFF][zt && !zr && g.zwrite ? 1 : 0], 0);
        size_t q0 = prof ? pts() : 0;
        static int dbg_stats = -1, dbg_n;
        if (dbg_stats < 0) { const char *e = getenv("RG_NR_STATS"); dbg_stats = e ? atoi(e) : 0; }
        static long dbg_skip = -1, dbg_seen;
        if (dbg_skip < 0) { const char *e = getenv("RG_NR_STATS_SKIP"); dbg_skip = e ? atol(e) : 0; }
        if (g.im && g.nruns > 0) {
            /* runs of alternating ALPHA (A, B swapped): one blend state each */
            ID3D11BlendState *bsw = nr_blend(g.abe, (g.alpha_abcd & ~0xFu) | ((g.alpha_abcd & 3u) << 2) | ((g.alpha_abcd >> 2) & 3u),
                                             g.cmask);
            uint32_t at = 0;
            int cur = 0;
            for (int i = 0; i < g.nruns; i++) {
                uint32_t e = g.runs[2 * i], sw = g.runs[2 * i + 1];
                if (e > g.nim) e = g.nim;
                if (e <= at) continue;
                if ((int)sw != cur && bsw) { ctx->OMSetBlendState(sw ? bsw : bst, bf, 0xFFFFFFFFu); cur = (int)sw; }
                ctx->Draw(e - at, at);
                at = e;
            }
        } else if (g.im) {
            ctx->Draw(g.nim, 0);
        } else if (dbg_stats && dbg_seen++ >= dbg_skip && dbg_n < 4000) {
            /* debugging: pipeline statistics of each native draw (stalls) */
            D3D11_QUERY_DESC qd = { D3D11_QUERY_PIPELINE_STATISTICS, 0 };
            ID3D11Query *q = NULL;
            dev->CreateQuery(&qd, &q);
            if (q) ctx->Begin(q);
            ctx->DrawIndexed(mb->nidx, 0, 0);
            if (q) {
                D3D11_QUERY_DATA_PIPELINE_STATISTICS st = {};
                ctx->End(q);
                while (ctx->GetData(q, &st, sizeof st, 0) == S_FALSE) {}
                if ((d->nbones_rows != 0) == (dbg_stats == 1) || dbg_stats == 3)
                    fprintf(stderr, "nr gpu: mesh %u idx %u bones %d cull %d z %d/%d tex %d: VS %llu prims %llu clipped-in %llu out %llu PS %llu\n",
                            d->mesh.id, mb->nidx, d->nbones_rows, g.cull, (int)g.zfunc, g.zwrite, g.tme,
                            (unsigned long long)st.VSInvocations, (unsigned long long)st.IAPrimitives,
                            (unsigned long long)st.CInvocations, (unsigned long long)st.CPrimitives,
                            (unsigned long long)st.PSInvocations);
                q->Release();
                dbg_n++;
            }
        } else {
            ctx->DrawIndexed(mb->nidx, 0, 0);
        }
        if (prof) pev_add(PC_NR, q0, (double)(g.scissor.x1 - g.scissor.x0) * (g.scissor.y1 - g.scissor.y0) * scale * scale);
        if (nrt_on) nt3 = nrt_now();
        unbind_all();
        ID3D11Buffer *nulcb[1] = {};
        ctx->VSSetConstantBuffers(0, 1, nulcb);
        ctx->OMSetBlendState(NULL, bf, 0xFFFFFFFFu);
        ctx->OMSetDepthStencilState(NULL, 0);
        if (nrt_on) {
            double nt4 = nrt_now();
            nrt_acc[0] += nt1 - nt0; nrt_acc[1] += nt2 - nt1; nrt_acc[2] += nt3 - nt2; nrt_acc[3] += nt4 - nt3;
            if (++nrt_n % 4000 == 0)
                fprintf(stderr, "nr_draw cpu ms per 4000 draws: mesh/tex/blend %.2f, IA+CB %.2f, state+draw %.2f, unbind %.2f\n",
                        nrt_acc[0], nrt_acc[1], nrt_acc[2], nrt_acc[3]);
            if (nrt_n % 4000 == 0) memset(nrt_acc, 0, sizeof nrt_acc);
        }
        return true;
    }

    void kick() override { ctx->Flush(); }

    /* $RG_GPU_SNAP_FLUSH=1: flush after every early copy (the old behaviour) */
    const bool snap_flush = getenv("RG_GPU_SNAP_FLUSH") && getenv("RG_GPU_SNAP_FLUSH")[0] == '1';

    ID3D11Buffer *snap[SNAP_SLOTS] = {};
    int snap_next = 0;
    int snap_copy(const uint32_t *runs, int nruns) override
    {
        int k = snap_next;
        if (!snap[k]) {
            D3D11_BUFFER_DESC bd = {};
            bd.ByteWidth = SNAP_BYTES;
            bd.Usage = D3D11_USAGE_STAGING;
            bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            if (FAILED(dev->CreateBuffer(&bd, NULL, &snap[k]))) return -1;
        }
        uint32_t at = 0;
        for (int i = 0; i < nruns; i++) {
            if (at + runs[2 * i + 1] > SNAP_BYTES) return -1;
            D3D11_BOX b = { runs[2 * i], 0, 0, runs[2 * i] + runs[2 * i + 1], 1, 1 };
            ctx->CopySubresourceRegion(snap[k], 0, at, 0, 0, mem, 0, &b);
            at += runs[2 * i + 1];
        }
        /* no Flush here: a frame takes many early copies (one after every batch
         * run that wrote the region), and each flush cost the GS worker driver
         * time; the copy goes with the next kick, snap_map submits it if not */
        if (snap_flush) ctx->Flush();
        snap_next = (k + 1) % SNAP_SLOTS;
        return k;
    }
    const uint8_t *snap_map(int slot) override
    {
        D3D11_MAPPED_SUBRESOURCE m;
        if (slot < 0 || !snap[slot] || FAILED(ctx->Map(snap[slot], 0, D3D11_MAP_READ, 0, &m))) return NULL;
        return (const uint8_t *)m.pData;
    }
    void snap_unmap(int slot) override { if (slot >= 0 && snap[slot]) ctx->Unmap(snap[slot], 0); }

    /* The decoded copy of g's texture rect: cached under the same key and
     * rect, or decoded now (g.dec_new) into the least recently used slot.
     * NULL: sample the mirror. */
    DecTex *dec_get(const GpuDraw &g)
    {
        const GpuRect &rc = g.dec_rect;
        dec_clock++;
        for (DecTex &e : dec)
            if (e.valid && !memcmp(e.key, g.dec_key, sizeof e.key) && !memcmp(&e.rect, &rc, sizeof rc)) {
                e.used = dec_clock;
                n_decode_hits++;
                return &e;
            }
        if (!g.dec_new || !cs_decode) return NULL;
        int w = rc.x1 - rc.x0, h = rc.y1 - rc.y0;
        if (w <= 0 || h <= 0 || w > 1024 || h > 1024) return NULL;
        DecTex *e = NULL;
        if (dec.size() < MAX_DEC) {
            dec.push_back(DecTex());
            e = &dec.back();
            memset(e, 0, sizeof *e);
        } else {
            e = &dec[0];
            for (DecTex &c : dec) if (c.used < e->used) e = &c;
        }
        e->valid = 0;
        if (e->srv && sh.srv[6] == e->srv) {
            /* about to be a UAV: unbind it from the draw path first */
            ID3D11ShaderResourceView *nul = NULL;
            ctx->PSSetShaderResources(6, 1, &nul);
            sh.srv[6] = NULL; sh.srv_res[6] = NULL;
        }
        if (!e->tex || e->tw < w || e->th < h) {
            REL(e->srv); REL(e->uav); REL(e->tex);
            int tw = e->tw > w ? e->tw : w, th = e->th > h ? e->th : h;
            tw = (tw + 63) & ~63; th = (th + 63) & ~63;
            if (tw > 1024) tw = 1024;
            if (th > 1024) th = 1024;
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = (UINT)tw; td.Height = (UINT)th;
            td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
            td.Format = DXGI_FORMAT_R32_UINT;
            td.Usage = D3D11_USAGE_DEFAULT;
            td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &e->tex)) ||
                FAILED(dev->CreateShaderResourceView(e->tex, NULL, &e->srv)) ||
                FAILED(dev->CreateUnorderedAccessView(e->tex, NULL, &e->uav))) {
                REL(e->srv); REL(e->uav); REL(e->tex);
                e->tw = e->th = 0;
                return NULL;
            }
            e->tw = tw; e->th = th;
        }
        GpuDrawCB c = g.cb;
        c.d[3][3] = 0;
        c.d[10][2] = (uint32_t)rc.x0 | ((uint32_t)rc.y0 << 16);
        c.d[10][3] = (uint32_t)rc.x1 | ((uint32_t)rc.y1 << 16);
        ctx->UpdateSubresource(cb_dec, 0, NULL, &c, 0, 0);
        ctx->CSSetShader(cs_decode, NULL, 0);
        ctx->CSSetConstantBuffers(0, 1, &cb_dec);
        ctx->CSSetShaderResources(0, 1, &mem_srv);
        ctx->CSSetShaderResources(5, 1, &clut_srv);
        ctx->CSSetUnorderedAccessViews(0, 1, &e->uav, NULL);
        ctx->Dispatch((UINT)(w + 7) / 8, (UINT)(h + 7) / 8, 1);
        ID3D11UnorderedAccessView *nu = NULL;
        ID3D11ShaderResourceView *ns = NULL;
        ctx->CSSetUnorderedAccessViews(0, 1, &nu, NULL);
        ctx->CSSetShaderResources(0, 1, &ns);
        ctx->CSSetShaderResources(5, 1, &ns);
        ctx->CSSetShader(NULL, NULL, 0);
        memcpy(e->key, g.dec_key, sizeof e->key);
        e->rect = rc;
        e->valid = 1;
        e->used = dec_clock;
        n_decodes++;
        return e;
    }

    void put_cb(const GpuDrawCB &cb)
    {
        if (sh.cb_valid && !memcmp(&cb, &sh.cb, sizeof cb)) return;
        ctx->UpdateSubresource(cb_draw, 0, NULL, &cb, 0, 0);
        sh.cb = cb;
        sh.cb_valid = true;
    }

    void set_om_state(ID3D11BlendState *b, ID3D11DepthStencilState *d)
    {
        if (b != sh.bs) { ctx->OMSetBlendState(b, NULL, 0xFFFFFFFF); sh.bs = b; }
        if (d != sh.ds) { ctx->OMSetDepthStencilState(d, 0); sh.ds = d; }
    }

    /* --------------------------------------------------------- display */
    /* the PCRTC composition into disp_tex ((out_w*scale) x (out_h*scale)) */
    bool compose(const GpuDisplay &d)
    {
        int W = d.out_w * d.scale, H = d.out_h * d.scale;
        if (!disp_tex || disp_w != W || disp_h != H) {
            REL(disp_rtv); REL(disp_srv); REL(disp_tex); REL(disp_staging);
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = (UINT)W; td.Height = (UINT)H;
            td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
            td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            td.Usage = D3D11_USAGE_DEFAULT;
            td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &disp_tex))) return false;
            if (FAILED(dev->CreateRenderTargetView(disp_tex, NULL, &disp_rtv))) return false;
            if (FAILED(dev->CreateShaderResourceView(disp_tex, NULL, &disp_srv))) return false;
            td.Usage = D3D11_USAGE_STAGING;
            td.BindFlags = 0;
            td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &disp_staging))) return false;
            disp_w = W; disp_h = H;
        }
        unbind_all();
        uint32_t u[8][4] = {};
        u[0][0] = (uint32_t)d.out_w; u[0][1] = (uint32_t)d.out_h; u[0][2] = (uint32_t)d.scale;
        u[0][3] = (uint32_t)(d.field & 1) | ((uint32_t)d.field_sel << 1);
        u[1][0] = (uint32_t)d.x0; u[1][1] = (uint32_t)d.y0;
        u[1][2] = (uint32_t)d.mmod | ((uint32_t)d.slbg << 1); u[1][3] = d.alp;
        u[2][0] = d.bg;
        ID3D11ShaderResourceView *srv[3] = { mem_srv, NULL, NULL };
        for (int i = 0; i < 2; i++) {
            const GpuCircuit &c = d.c[i];
            int mirror = c.rt < 0;
            u[3 + 2 * i][0] = (uint32_t)(c.en && c.w > 0 && c.h > 0) | ((uint32_t)mirror << 1);
            u[3 + 2 * i][1] = c.fbp; u[3 + 2 * i][2] = c.fbw ? c.fbw : 1;
            u[3 + 2 * i][3] = (uint32_t)c.psm;
            u[4 + 2 * i][0] = (c.dbx & 0xFFFF) | (c.dby << 16);
            u[4 + 2 * i][1] = (uint32_t)c.ox; u[4 + 2 * i][2] = (uint32_t)c.oy;
            u[4 + 2 * i][3] = ((uint32_t)c.w & 0xFFFF) | ((uint32_t)c.h << 16);
            u[7][i] = (uint32_t)(c.rt_scale > 0 ? c.rt_scale : 1);
            u[7][2 + i] = (uint32_t)c.af_hr;
            if (!mirror) srv[1 + i] = targets[c.rt].srv;
        }
        util_cb(u);
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ctx->IASetInputLayout(NULL);
        ctx->VSSetShader(vs_quad, NULL, 0);
        ctx->PSSetShader(ps_display, NULL, 0);
        ctx->PSSetConstantBuffers(0, 1, &cb_util);
        ctx->PSSetShaderResources(0, 3, srv);
        ctx->RSSetState(rs);
        set_viewport(W, H);
        D3D11_RECT rc = { 0, 0, W, H };
        ctx->RSSetScissorRects(1, &rc);
        ctx->OMSetRenderTargets(1, &disp_rtv, NULL);
        ctx->OMSetBlendState(bs[15], NULL, 0xFFFFFFFF);
        ctx->OMSetDepthStencilState(ds[GZ_OFF][0], 0);
        ctx->Draw(3, 0);
        unbind_all();
        return true;
    }

    int map_copy(ID3D11Texture2D *staging, int W, int H, uint32_t *out)
    {
        D3D11_MAPPED_SUBRESOURCE m;
        if (FAILED(ctx->Map(staging, 0, D3D11_MAP_READ, 0, &m))) return -1;
        for (int y = 0; y < H; y++)
            memcpy(out + (size_t)y * W, (const uint8_t *)m.pData + (size_t)y * m.RowPitch, (size_t)W * 4);
        ctx->Unmap(staging, 0);
        return 0;
    }

    /* Lagged read-back: queue the copy of this frame and return the frame
     * the previous read queued (same size).  With none queued (the first
     * frame, a new size) this frame is returned now and stays queued, so
     * the next read returns it again. */
    int readback_lag(ID3D11Texture2D *src, int W, int H, uint32_t *out)
    {
        LagSlot &cur = lagq[lag_cur], &prev = lagq[lag_cur ^ 1];
        if (!cur.st || cur.w != W || cur.h != H) {
            REL(cur.st);
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = (UINT)W; td.Height = (UINT)H;
            td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
            td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            td.Usage = D3D11_USAGE_STAGING;
            td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            cur.pending = false;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &cur.st))) { cur.w = cur.h = 0; return -1; }
            cur.w = W; cur.h = H;
        }
        ctx->CopyResource(cur.st, src);
        if (prof) disp_end((double)W * H);
        cur.pending = true;
        ctx->Flush();
        lag_cur ^= 1;
        LagSlot &ret = prev.pending && prev.st && prev.w == W && prev.h == H ? prev : cur;
        int rc = map_copy(ret.st, W, H, out);
        prev.pending = false;
        return rc;
    }

    /* zero-copy presentation (docs/PERF-3D.md): two shared textures with a
     * keyed mutex (the producer acquires key 0 and releases key 1, the
     * presenter's device acquires 1 and releases 0), alternating */
    struct ShareSlot {
        ID3D11Texture2D *tex = NULL;
        IDXGIKeyedMutex *km = NULL;
        HANDLE h = NULL;
        int w = 0, ht = 0;
    } shs[2];
    int sh_cur = 0;
    void *sh_last = NULL;
    void free_share(ShareSlot &s) { REL(s.km); REL(s.tex); s.h = NULL; s.w = s.ht = 0; }
    int share_out(ID3D11Texture2D *src, int W, int H)
    {
        sh_last = NULL;
        ShareSlot &s = shs[sh_cur];
        if (!s.tex || s.w != W || s.ht != H) {
            free_share(s);
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = (UINT)W; td.Height = (UINT)H;
            td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
            td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            td.Usage = D3D11_USAGE_DEFAULT;
            td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
            td.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &s.tex))) return -1;
            IDXGIResource *res = NULL;
            if (FAILED(s.tex->QueryInterface(__uuidof(IDXGIKeyedMutex), (void **)&s.km)) ||
                FAILED(s.tex->QueryInterface(__uuidof(IDXGIResource), (void **)&res)) ||
                FAILED(res->GetSharedHandle(&s.h))) {
                if (res) res->Release();
                free_share(s);
                return -1;
            }
            res->Release();
            s.w = W; s.ht = H;
        }
        /* the presenter released it (key 0) after drawing it, at most two
         * frames ago */
        HRESULT hr = s.km->AcquireSync(0, 500);
        if (hr != S_OK) return -1;
        ctx->CopyResource(s.tex, src);
        if (prof) disp_end((double)W * H);
        s.km->ReleaseSync(1);
        ctx->Flush();
        sh_last = (void *)s.h;
        sh_cur ^= 1;
        return 0;
    }
    void *shared_out() override { return sh_last; }

    int readback(ID3D11Texture2D *staging, ID3D11Texture2D *src, int W, int H, uint32_t *out)
    {
        if (!out) return share_out(src, W, H);
        if (lag) return readback_lag(src, W, H, out);
        ctx->CopyResource(staging, src);
        if (prof) disp_end((double)W * H);
        D3D11_MAPPED_SUBRESOURCE m;
        if (FAILED(ctx->Map(staging, 0, D3D11_MAP_READ, 0, &m))) return -1;
        for (int y = 0; y < H; y++)
            memcpy(out + (size_t)y * W, (const uint8_t *)m.pData + (size_t)y * m.RowPitch, (size_t)W * 4);
        ctx->Unmap(staging, 0);
        return 0;
    }

    int display(const GpuDisplay &d, uint32_t *out) override
    {
        disp_q0 = prof ? pts() : (size_t)-1;
        if (!compose(d)) return -1;
        int rc = readback(disp_staging, disp_tex, disp_w, disp_h, out);
        if (prof && pq_next > 1024) prof_collect();
        return rc;
    }

    /* ------------------------------------------------------ post chain */
    void free_post(PostTex &t)
    {
        REL(t.rtv); REL(t.srv); REL(t.tex);
        t.w = t.h = 0;
    }

    bool ensure_post(PostTex &t, int w, int h, DXGI_FORMAT fmt)
    {
        if (t.tex && t.w == w && t.h == h && t.fmt == fmt) return true;
        free_post(t);
        D3D11_TEXTURE2D_DESC td = {};
        td.Width = (UINT)w; td.Height = (UINT)h;
        td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
        td.Format = fmt;
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        if (FAILED(dev->CreateTexture2D(&td, NULL, &t.tex))) return false;
        if (FAILED(dev->CreateRenderTargetView(t.tex, NULL, &t.rtv))) return false;
        if (FAILED(dev->CreateShaderResourceView(t.tex, NULL, &t.srv))) return false;
        t.w = w; t.h = h; t.fmt = fmt;
        return true;
    }

    /* one full-viewport pass: src -> dst */
    void post_pass(ID3D11PixelShader *ps, ID3D11ShaderResourceView *src, PostTex &dst,
                   const float pf[4][4], const uint32_t pq[2][4])
    {
        unbind_all();
        uint8_t cbd[6 * 16];
        memcpy(cbd, pf, 64);
        memcpy(cbd + 64, pq, 32);
        ctx->UpdateSubresource(cb_post, 0, NULL, cbd, 0, 0);
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ctx->IASetInputLayout(NULL);
        ctx->VSSetShader(vs_quad, NULL, 0);
        ctx->PSSetShader(ps, NULL, 0);
        ctx->PSSetConstantBuffers(0, 1, &cb_post);
        ctx->PSSetShaderResources(0, 1, &src);
        ctx->PSSetSamplers(0, 1, &smp_lin);
        ctx->RSSetState(rs);
        set_viewport(dst.w, dst.h);
        D3D11_RECT rc = { 0, 0, dst.w, dst.h };
        ctx->RSSetScissorRects(1, &rc);
        ctx->OMSetRenderTargets(1, &dst.rtv, NULL);
        ctx->OMSetBlendState(bs[15], NULL, 0xFFFFFFFF);
        ctx->OMSetDepthStencilState(ds[GZ_OFF][0], 0);
        ctx->Draw(3, 0);
        unbind_all();
    }

    /* separable resample of the current image (cw x ch) to tw x th */
    bool resample(ID3D11ShaderResourceView *&cur, int &cw, int &ch, int &slot, int tw, int th,
                  int down, int up)
    {
        for (int axis = 0; axis < 2; axis++) {
            int sn = axis ? ch : cw, dn = axis ? th : tw;
            if (sn == dn || dn <= 0) continue;
            int filt = dn < sn ? down : up;
            int ow = axis ? cw : tw, oh = axis ? th : ch;
            PostTex &dst = post[slot];
            if (!ensure_post(dst, ow, oh, DXGI_FORMAT_R16G16B16A16_FLOAT)) return false;
            float pf[4][4] = { { (float)cw, (float)ch, (float)ow, (float)oh } };
            uint32_t pq[2][4] = { { (uint32_t)axis, (uint32_t)filt, 0, 0 } };
            post_pass(ps_resample, cur, dst, pf, pq);
            cur = dst.srv; cw = ow; ch = oh; slot ^= 1;
        }
        return true;
    }

    int display_post(const GpuDisplay &d, const GpuPost &p, uint32_t *out) override
    {
        if (!compose(d)) return -1;
        ID3D11ShaderResourceView *cur = disp_srv;
        int cw = disp_w, ch = disp_h, slot = 0;
        const DXGI_FORMAT F16 = DXGI_FORMAT_R16G16B16A16_FLOAT;
        /* 1. supersampling: down to the wanted size */
        if (!resample(cur, cw, ch, slot, p.ssaa_w, p.ssaa_h, p.downsample, p.downsample)) return -1;
        /* 2. FXAA, then sharpening, on the anti-aliased image */
        if (p.fxaa) {
            if (!ensure_post(post[slot], cw, ch, F16)) return -1;
            float pf[4][4] = { { (float)cw, (float)ch, 1.0f / (float)cw, 1.0f / (float)ch } };
            uint32_t pq[2][4] = {};
            post_pass(ps_fxaa, cur, post[slot], pf, pq);
            cur = post[slot].srv; slot ^= 1;
        }
        if (p.sharpen > 0.0f) {
            if (!ensure_post(post[slot], cw, ch, F16)) return -1;
            float pf[4][4] = { { (float)cw, (float)ch, p.sharpen, 0 } };
            uint32_t pq[2][4] = {};
            post_pass(ps_sharpen, cur, post[slot], pf, pq);
            cur = post[slot].srv; slot ^= 1;
        }
        /* 3. to the window rectangle */
        if (!resample(cur, cw, ch, slot, p.final_w, p.final_h, p.downsample, p.upscale)) return -1;
        /* 4. brightness/gamma, output filter -> RGBA8 */
        if (!ensure_post(post[2], cw, ch, DXGI_FORMAT_R8G8B8A8_UNORM)) return -1;
        if (!post_staging || post_sw != cw || post_sh != ch) {
            REL(post_staging);
            D3D11_TEXTURE2D_DESC td = {};
            td.Width = (UINT)cw; td.Height = (UINT)ch;
            td.MipLevels = 1; td.ArraySize = 1; td.SampleDesc.Count = 1;
            td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            td.Usage = D3D11_USAGE_STAGING;
            td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            if (FAILED(dev->CreateTexture2D(&td, NULL, &post_staging))) return -1;
            post_sw = cw; post_sh = ch;
        }
        {
            float g = p.gamma > 0.01f ? p.gamma : 1.0f;
            int lines = p.src_lines > 0 ? p.src_lines : ch;
            float lpp = (float)ch / (float)lines;     /* output rows per source line */
            /* scanlines need >= 2 output rows per line; fade in from 1 to 2 */
            float strength = lpp >= 2.0f ? 0.55f : (lpp > 1.0f ? 0.55f * (lpp - 1.0f) : 0.0f);
            float pf[4][4] = { { (float)cw, (float)ch, p.brightness, 1.0f / g },
                               { (float)lines, strength, 0, 0 } };
            uint32_t pq[2][4] = { { (uint32_t)p.output_filter, 0, 0, 0 } };
            post_pass(ps_final, cur, post[2], pf, pq);
        }
        return readback(post_staging, post[2].tex, cw, ch, out);
    }

    void set_scale(int s) override
    {
        unbind_all();
        rt_pool_free();
        scale = s;
        REL(disp_rtv); REL(disp_srv); REL(disp_tex); REL(disp_staging);
        disp_w = disp_h = 0;
    }
};

} /* namespace */

GpuBackend *gpu_backend_d3d11_create(const gpu_config *cfg, int scale, char *err, size_t cap)
{
    D3D11Backend *b = new D3D11Backend();
    if (!b->init(cfg, scale, err, cap)) {
        delete b;
        return NULL;
    }
    return b;
}

#endif /* RG_GPU_EXACT || RG_NATIVE_ONLY */
