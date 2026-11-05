/* SPDX-License-Identifier: CC0-1.0 */
/* Vulkan backend of the native device (gpu_internal.h GpuBackend; docs/NATIVE-VULKAN.md): the
 * same work as nr_d3d11.cpp's native-only build (no GS-exact draw path), for Linux and as a second
 * backend on Windows.  Vulkan 1.3 (dynamic rendering, push descriptors), the loader opened at run
 * time by volk (third_party/volk: the exe starts without Vulkan), memory from VMA
 * (third_party/vma).  Shaders: the HLSL of src/gpu/shaders compiled to SPIR-V by DXC at build time
 * (nr_vulkan.cmake), one descriptor set per pipeline with D3D's registers as bindings
 * ("Bindings" below), filled per draw / dispatch from a slot table as D3D11's Set* calls do.
 *
 * Synchronisation model (docs/NATIVE-VULKAN.md "Synchronisation"): every image stays in
 * VK_IMAGE_LAYOUT_GENERAL; one global memory barrier (all commands -> all commands) before any
 * operation that follows a write, and consecutive draws into the same attachments share one
 * dynamic-rendering instance (attachment writes are ordered by the rasterizer, ordered views by
 * fragment shader interlock).  Uploads go through a host-visible ring; read-backs submit and wait. */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_VULKAN)
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"   /* { VK_STRUCTURE_TYPE_... } initialisers */
#endif
#include "volk.h"
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include "vk_mem_alloc.h"

#include <math.h>   /* floorf / fminf / sqrtf (the RT code; MSVC headers pull it in, glibc's do not) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gpu_internal.h"
#include "nr_texrep.h"
#include "nr_emi.h"   /* (rt8) emissive surfaces (docs/RAYTRACING.md "RT8") */

#if defined(_WIN32)
extern "C" __declspec(dllimport) void *__stdcall LoadLibraryA(const char *);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *, const char *);
#else
#include <dlfcn.h>
#endif

#include "vk_VS_quad.h"
#include "vk_PS_load_color.h"
#include "vk_PS_load_depth.h"
#include "vk_PS_load_depth_rt.h"
#include "vk_PS_copy_depth.h"
#include "vk_PS_display.h"
#include "vk_CS_wb_color.h"
#include "vk_CS_load_phase.h"
#include "vk_CS_wb_depth.h"
#include "vk_CS_merge.h"
#include "vk_CS_clut.h"
#include "vk_CS_l2l_read.h"
#include "vk_CS_l2l_write.h"
#include "vk_CS_xfer.h"
#include "vk_CS_decode.h"
#include "vk_PS_resample.h"
#include "vk_PS_fxaa.h"
#include "vk_PS_sharpen.h"
#include "vk_PS_final.h"
#include "vk_VS_nr.h"
#include "vk_GS_nr.h"
#include "vk_VS_im.h"
#include "vk_PS_nr.h"
#include "vk_PS_nr_z.h"
#include "vk_PS_nr_c.h"
#include "vk_PS_nr_cz.h"
#include "vk_VS_nr_rt.h"
#include "vk_GS_nr_rt.h"
#include "vk_PS_nr_rt.h"
#include "vk_PS_nr_zrt.h"

#define pre_op() pre_op_at(__LINE__)
namespace {

/* ---- Bindings: one set, binding = D3D register + base (DXC -fvk-*-shift, nr_vulkan.cmake) */
enum { B_CB = 0, B_T = 16, B_S = 32, B_U = 48, B_N = 64 };

/* ------------------------------------------------------------ validation layer, loaded by the backend
 * $RG_VK_LAYER_DLL=path (with RG_VK_VALIDATE=1; docs/NATIVE-VULKAN.md "Validation"): the loader
 * ignores every layer path variable in an elevated process and only reads the system registry, so
 * the backend can put the layer in front of the loader itself: the layer library's
 * vkGetInstanceProcAddr creates the instance and the device with the loader's interface structures
 * (vk_layer.h, declared here: the vendored headers do not carry it) whose "next" is the loader.
 * Every call of this backend then goes through the layer; the window's renderer (SDL) calls the
 * loader directly and is not validated. */
namespace vkl {
enum { LINK_INFO = 0, DATA_CALLBACK = 1 };
struct InstanceLink { InstanceLink *pNext; PFN_vkGetInstanceProcAddr gipa; void *gpdpa; };
struct InstanceCreateInfo {
    VkStructureType sType;
    const void *pNext;
    int function;
    union { InstanceLink *link; VkResult (VKAPI_PTR *set_data)(VkInstance, void *); void *pad[2]; } u;
};
struct DeviceLink { DeviceLink *pNext; PFN_vkGetInstanceProcAddr gipa; PFN_vkGetDeviceProcAddr gdpa; };
struct DeviceCreateInfo {
    VkStructureType sType;
    const void *pNext;
    int function;
    union { DeviceLink *link; VkResult (VKAPI_PTR *set_data)(VkDevice, void *); } u;
};
struct Negotiate {
    int sType;   /* LAYER_NEGOTIATE_INTERFACE_STRUCT = 1 */
    void *pNext;
    uint32_t version;
    PFN_vkGetInstanceProcAddr gipa;
    PFN_vkGetDeviceProcAddr gdpa;
    void *gpdpa;
};
static VkResult VKAPI_PTR set_instance_data(VkInstance i, void *obj) { memcpy(obj, (void *)i, sizeof(void *)); return VK_SUCCESS; }
static VkResult VKAPI_PTR set_device_data(VkDevice d, void *obj) { memcpy(obj, (void *)d, sizeof(void *)); return VK_SUCCESS; }
/* the layer's vkGetInstanceProcAddr (NULL: not loadable) */
static PFN_vkGetInstanceProcAddr load(const char *path)
{
#if defined(_WIN32)
    void *h = LoadLibraryA(path);
    void *f = h ? GetProcAddress(h, "vkNegotiateLoaderLayerInterfaceVersion") : NULL;
    void *g = h ? GetProcAddress(h, "vkGetInstanceProcAddr") : NULL;
#else
    void *h = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    void *f = h ? dlsym(h, "vkNegotiateLoaderLayerInterfaceVersion") : NULL;
    void *g = h ? dlsym(h, "vkGetInstanceProcAddr") : NULL;
#endif
    if (f) {
        Negotiate n = {};
        n.sType = 1;
        n.version = 2;
        typedef VkResult(VKAPI_PTR * PFN_neg)(Negotiate *);
        PFN_neg neg;
        memcpy(&neg, &f, sizeof f);
        if (neg(&n) == VK_SUCCESS && n.gipa) return n.gipa;
    }
    PFN_vkGetInstanceProcAddr r = NULL;
    if (g) memcpy(&r, &g, sizeof g);
    return r;
}
} /* namespace vkl */

/* ------------------------------------------------------------ SPIR-V reflection */
struct Bind {
    uint32_t binding;
    VkDescriptorType type;
    uint32_t fmt;        /* storage image format (SPIR-V ImageFormat: 3 R32f, 33 R32ui) */
};

/* the resource variables (binding, descriptor type) and the vertex inputs (name -> location) */
static bool spv_reflect(const uint32_t *w, size_t n, std::vector<Bind> &binds,
                        std::vector<std::pair<std::string, uint32_t>> &inputs)
{
    if (n < 5 || w[0] != 0x07230203u) return false;
    std::unordered_map<uint32_t, uint32_t> binding, location, ptr_to, elem;
    std::unordered_map<uint32_t, std::string> names;
    std::unordered_map<uint32_t, std::pair<int, uint32_t>> kind;   /* type -> (descriptor type, image format) */
    std::vector<uint32_t> bufblock;
    struct Var { uint32_t type, id, sc; };
    std::vector<Var> vars;
    for (size_t i = 5; i < n;) {
        uint32_t op = w[i] & 0xFFFFu, wc = w[i] >> 16;
        if (!wc || i + wc > n) return false;
        const uint32_t *a = w + i + 1;
        switch (op) {
        case 5: /* OpName */ names[a[0]] = std::string((const char *)(a + 1)); break;
        case 71: /* OpDecorate */
            if (a[1] == 33) binding[a[0]] = a[2];
            else if (a[1] == 30) location[a[0]] = a[2];
            else if (a[1] == 3) bufblock.push_back(a[0]);
            break;
        case 25: { /* OpTypeImage result sampled-type dim depth arrayed ms sampled format */
            uint32_t dim = a[2], sampled = a[6], fmt = a[7];
            int t = dim == 5 ? (sampled == 2 ? VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER : VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER)
                             : (sampled == 2 ? VK_DESCRIPTOR_TYPE_STORAGE_IMAGE : VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE);
            kind[a[0]] = std::make_pair(t, fmt);
            break;
        }
        case 26: kind[a[0]] = std::make_pair((int)VK_DESCRIPTOR_TYPE_SAMPLER, 0u); break;
        case 5341: kind[a[0]] = std::make_pair((int)VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR, 0u); break;   /* OpTypeAccelerationStructureKHR */
        case 27: kind[a[0]] = std::make_pair((int)VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0u); break;
        case 28: case 29: elem[a[0]] = a[1]; break;                 /* arrays */
        case 32: ptr_to[a[0]] = a[2]; break;                       /* OpTypePointer result sc type */
        case 59: vars.push_back(Var{ a[0], a[1], a[2] }); break;  /* OpVariable type result sc */
        default: break;
        }
        i += wc;
    }
    for (const Var &v : vars) {
        if (v.sc == 1) {   /* Input */
            auto l = location.find(v.id);
            auto nm = names.find(v.id);
            if (l != location.end() && nm != names.end()) inputs.push_back(std::make_pair(nm->second, l->second));
            continue;
        }
        auto b = binding.find(v.id);
        if (b == binding.end()) continue;
        uint32_t t = ptr_to.count(v.type) ? ptr_to[v.type] : 0;
        while (elem.count(t)) t = elem[t];
        Bind bd = { b->second, VK_DESCRIPTOR_TYPE_MAX_ENUM, 0 };
        if (v.sc == 12) bd.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        else if (v.sc == 2)
            bd.type = std::find(bufblock.begin(), bufblock.end(), t) != bufblock.end() ? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
                                                                                    : VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        else if (kind.count(t)) { bd.type = (VkDescriptorType)kind[t].first; bd.fmt = kind[t].second; }
        else continue;
        binds.push_back(bd);
    }
    return true;
}

/* Storage images of a fragment shader (the ordered views) get the Coherent decoration: D3D's
 * rasterizer-ordered views are coherent between the ordered invocations, DXC's SPIR-V is not
 * (without it a later draw's interlocked read can see a stale cached value). */
static void spv_coherent_images(std::vector<uint32_t> &w)
{
    if (w.size() < 5) return;
    std::unordered_map<uint32_t, uint32_t> ptr_to;
    std::vector<uint32_t> storage_imgs, vars;
    std::unordered_map<uint32_t, uint32_t> var_type, bind_of;
    size_t first_dec = 0;
    for (size_t i = 5; i < w.size();) {
        uint32_t op = w[i] & 0xFFFFu, wc = w[i] >> 16;
        if (!wc || i + wc > w.size()) return;
        const uint32_t *a = &w[i + 1];
        if (op == 71 && !first_dec) first_dec = i;
        if (op == 25 && a[6] == 2 && a[2] != 5) storage_imgs.push_back(a[0]);
        if (op == 32) ptr_to[a[0]] = a[2];
        if (op == 59 && a[2] == 0) { vars.push_back(a[1]); var_type[a[1]] = a[0]; }
        if (op == 71 && wc >= 4 && a[1] == 33u) bind_of[a[0]] = a[2];   /* OpDecorate %v Binding n */
        i += wc;
    }
    if (!first_dec) return;
    std::vector<uint32_t> ins;
    for (uint32_t v : vars) {
        uint32_t t = ptr_to.count(var_type[v]) ? ptr_to[var_type[v]] : 0;
        if (std::find(storage_imgs.begin(), storage_imgs.end(), t) == storage_imgs.end()) continue;
        /* (not the ray-tracing penumbra history, u7 / u8: never read and written by the same draw
         * at one pixel in order, a cached access is enough) */
        if (bind_of.count(v) && (bind_of[v] == 48u + 7u || bind_of[v] == 48u + 8u)) continue;
        ins.push_back((3u << 16) | 71u);   /* OpDecorate %v Coherent */
        ins.push_back(v);
        ins.push_back(23u);
    }
    w.insert(w.begin() + (long)first_dec, ins.begin(), ins.end());
}

/* ------------------------------------------------------------ resources */
struct Buf {
    VkBuffer b = VK_NULL_HANDLE;
    VmaAllocation a = NULL;
    uint8_t *map = NULL;
    VkDeviceSize size = 0;
    VkBufferView view = VK_NULL_HANDLE;   /* R32_UINT texel view (when made) */
};

struct Shader {
    VkShaderModule m = VK_NULL_HANDLE;
    VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT;
    const char *entry = "";
    std::vector<Bind> binds;
    std::vector<std::pair<std::string, uint32_t>> inputs;
    uint32_t input_loc(const char *sem) const
    {
        std::string want = std::string("in.var.") + sem;
        for (const auto &p : inputs) if (p.first == want) return p.second;
        return ~0u;
    }
};

struct Prog {
    const Shader *vs = NULL, *ps = NULL, *cs = NULL;
    const Shader *gs = NULL;   /* the VU clipper (nr_draw.hlsl GS_nr), prog_gs */
    std::vector<Bind> binds;
    VkDescriptorSetLayout dsl = VK_NULL_HANDLE;
    VkPipelineLayout pl = VK_NULL_HANDLE;
    VkPipeline comp = VK_NULL_HANDLE;
};

/* fixed-function state of a graphics pipeline (all bytes significant: zero-initialised) */
struct GKey {
    const Prog *p;
    uint32_t cf, df;          /* colour / depth attachment formats (VK_FORMAT_UNDEFINED: none) */
    uint8_t vin;              /* 0 none, 1 native mesh (28-byte vertices), 2 immediate (GpuImVtx) */
    uint8_t blend, sb, db, op, cmask;
    uint8_t cull;             /* 0 none, 1 front (D3D clockwise), 2 back */
    uint8_t zt, zw, zf;       /* depth test, write, VkCompareOp */
    uint8_t clamp;            /* depth clamp (D3D DepthClipEnable FALSE) */
    int8_t bias;              /* constant depth bias */
    uint8_t brep;             /* 1: bias in the float representation (no depth attachment, VK_EXT_depth_bias_control) */
    uint8_t pad[1];
};

struct Target {
    int used = 0;
    int depth = 0;
    int dsv = 0;              /* depth: a D32 depth attachment (not an ordered view) */
    int w = 0, h = 0;         /* native */
    VkImage img = VK_NULL_HANDLE;
    VmaAllocation al = NULL;
    VkFormat fmt = VK_FORMAT_UNDEFINED;
    VkImageView view = VK_NULL_HANDLE;   /* attachment / sampled */
    VkImageView uv = VK_NULL_HANDLE;     /* storage: colour R32_UINT, depth (ordered) R32_SFLOAT */
    VkImage snap = VK_NULL_HANDLE;       /* colour snapshot (tex_snap) */
    VmaAllocation snap_al = NULL;
    VkImageView snap_view = VK_NULL_HANDLE;
};

struct Img {
    VkImage i = VK_NULL_HANDLE;
    VmaAllocation a = NULL;
    VkImageView v = VK_NULL_HANDLE, uv = VK_NULL_HANDLE;
    VkFormat fmt = VK_FORMAT_UNDEFINED;
    int w = 0, h = 0;
};

/* a destruction deferred until the command buffer that may use it completed */
struct Del {
    VkBuffer b = VK_NULL_HANDLE;
    VkImage i = VK_NULL_HANDLE;
    VmaAllocation a = NULL;
    VkImageView v[3] = { VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE };
    VkBufferView bv = VK_NULL_HANDLE;
    VkAccelerationStructureKHR as = VK_NULL_HANDLE;   /* ray tracing (docs/RAYTRACING.md) */
};

struct Slot {
    VkBuffer buf;
    VkDeviceSize off, range;
    VkBufferView bv;
    VkImageView iv;
    VkSampler smp;
    VkAccelerationStructureKHR as;
};

/* submissions in flight before the CPU waits for the oldest (with interpolated presentation
 * the GS worker submits ~10 times a field: 6 made it wait for the GPU, 19 % of its samples) */
static const int NSUB = 16;

class VkBackend : public GpuBackend {
public:
    int scale = 1;
    char devname[192] = "vulkan";
    VkInstance inst = VK_NULL_HANDLE;
    PFN_vkGetInstanceProcAddr layer_gipa = NULL, loader_gipa = NULL;   /* $RG_VK_LAYER_DLL (vkl) */
    VkDebugUtilsMessengerEXT dbg = VK_NULL_HANDLE;
    VkPhysicalDevice pd = VK_NULL_HANDLE;
    VkDevice dev = VK_NULL_HANDLE;
    VkQueue queue = VK_NULL_HANDLE;
    uint32_t qf = 0;
    VmaAllocator vma = NULL;
    VkPhysicalDeviceLimits lim = {};
    bool rov_ok = false, zrov_ok = false;
    /* ordered-depth draws: the rasterizer bias D3D11 applies to SV_Position.z without a depth view
     * (2^(e - 23) units, as for a float buffer); 0 = none (no VK_EXT_depth_bias_control) */
    int zrov_brep = 0;
    /* without the extension: a D32 attachment that is neither tested nor written, bound only so
     * the rasterizer computes the bias in the float representation (one per target size) */
    int zrov_bias_att = 0;
    std::map<std::pair<int, int>, Img> zbias_img;
    VkPipelineCache pcache = VK_NULL_HANDLE;

    /* ---- submissions ---- */
    /* GPU profile ($RG_GPU_PROFILE=1): a timestamp pair per event, both in one submission */
    enum { PQ_MAX = 4096 };
    struct PEv { int cat; uint32_t q0, q1; double px; };
    struct Sub {
        VkCommandPool pool = VK_NULL_HANDLE;
        VkCommandBuffer cb = VK_NULL_HANDLE;
        VkFence fence = VK_NULL_HANDLE;
        bool busy = false;
        uint64_t serial = 0;
        std::vector<Del> dels;
        VkQueryPool qp = VK_NULL_HANDLE;   /* timestamps (profile) */
        uint32_t qn = 0;
        std::vector<PEv> ev;
    } subs[NSUB];
    int ci = 0;               /* the sub recording (or next to record) */
    bool recording = false;
    uint64_t serial_next = 1;
    bool dirty = false;       /* a write since the last barrier */

    /* ---- upload ring (host visible, coherent) ---- */
    Buf ring;
    VkDeviceSize ring_head = 0;

    /* ---- the local-memory mirror and helpers ---- */
    Buf mem, mem_rb, merge, xdesc, l2l, scr, clut, clut_rb;
    Buf snapb[SNAP_SLOTS];
    uint64_t snap_serial[SNAP_SLOTS] = {};
    int snap_next = 0;

    /* ---- dummies for unbound slots (D3D: reads 0) ---- */
    Buf dummy_buf;
    Img dummy_rgba, dummy_r32f;
    VkSampler smp_lin = VK_NULL_HANDLE;
    VkSampler smp_nr[2][2][2] = {};
    /* graphics.anisotropic: [log2(degree) - 1][clamp u][clamp v]; NULL without the
     * samplerAnisotropy feature (the plain bilinear sampler then) */
    VkSampler smp_nr_an[4][2][2] = {};
    bool aniso_ok = false;
    float aniso_max = 16.0f;

    /* ---- shaders, programs, pipelines ---- */
    Shader sh_vs_quad, sh_ps_load_color, sh_ps_load_depth, sh_ps_load_depth_rt, sh_ps_copy_depth, sh_ps_display,
        sh_cs_wb_color, sh_cs_wb_depth, sh_cs_merge, sh_cs_clut, sh_cs_l2l_read, sh_cs_l2l_write, sh_cs_xfer,
        sh_cs_decode, sh_ps_resample, sh_ps_fxaa, sh_ps_sharpen, sh_ps_final, sh_vs_nr, sh_vs_im, sh_ps_nr,
        sh_ps_nr_z, sh_ps_nr_c, sh_ps_nr_cz, sh_cs_load_phase, sh_gs_nr;
    Shader sh_vs_nr_rt, sh_gs_nr_rt, sh_ps_nr_rt, sh_ps_nr_zrt;   /* ray tracing (docs/RAYTRACING.md) */
    bool gs_ok = false;   /* geometryShader: meshes with the VU clipper through GS_nr */
    std::map<std::pair<const Shader *, const Shader *>, Prog *> progs;
    std::map<const Shader *, Prog *> progs_gs;   /* VS_nr + GS_nr + this pixel shader */
    std::map<const Shader *, Prog *> progs_gs_rt;   /* VS_nr_rt + GS_nr_rt + this pixel shader */
    std::unordered_map<std::string, VkPipeline> gpipes;

    Slot slots[B_N];

    std::vector<Target> targets;
    std::vector<Target> rt_pool;
    int rt_pool_on = -1;
    /* bounded by bytes as nr_d3d11.cpp ($RG_GPU_RT_POOL_MB, default 512): 24 entries missed
     * several times a field with interpolated presentation (allocations + VMA frees) */
    int64_t rt_pool_cap = -1, rt_pool_bytes = 0;
    int64_t rt_bytes(const Target &t) const
    {
        int64_t b = (int64_t)t.w * scale * t.h * scale * 4;
        return b + (t.snap ? b : 0);
    }
    bool destroying = false;

    /* ---- rendering instance ---- */
    bool in_rp = false;
    struct RpKey { VkImageView c, d; int w, h, noatt; } rp = {};
    VkPipeline bound_pipe = VK_NULL_HANDLE;

    /* ---- display / post ---- */
    Img disp;
    Img post[3];
    Buf out_rb;           /* read-back of the display / post output */

    /* ---- zero-copy presentation (docs/NATIVE-VULKAN.md "Presentation") ----
     * The window's renderer shares this device (vk_present_device): display / display_post with
     * out == NULL copy the frame into one of two images (they only grow; the frame is the top-left
     * w x h), left in SHADER_READ_ONLY_OPTIMAL, and shared_out() returns its gpu_vk_frame.  The
     * presenter's acquire waits on the timeline semaphore (every submission signals its serial)
     * and marks the slot busy; release (after the presenter's GPU work read it) frees it. */
    bool surf_ok = false;          /* the instance has VK_KHR_surface + a window-system surface */
    bool pres_ok = false;          /* + swapchain extension, a second queue, timeline semaphores */
    uint32_t qi = 0;               /* the backend's queue index in qf (1 with a presenter) */
    VkSemaphore tl = VK_NULL_HANDLE;
    struct PSlot {
        Img img;
        std::atomic<int> st{ 0 };  /* 0 free, 1 handed to the presenter, 2 the presenter draws it */
        uint64_t serial = 0;       /* the submission that wrote it */
        gpu_vk_frame fr = {};
        VkBackend *be = NULL;
    } ps[2];
    int ps_cur = 0;
    void *ps_last = NULL;
    uint64_t ps_count = 0;
    struct Retired { Img img; uint64_t at; };
    std::vector<Retired> ps_retired;   /* grown-out slot images (the presenter may still wrap them) */
    /* ---- pipelined read-back (gpu_config.readback_lag, as nr_d3d11.cpp) ---- */
    bool lag = false;
    struct LagSlot { Buf b; int w = 0, h = 0; bool pending = false; uint64_t serial = 0; } lagq[2];
    int lag_cur = 0;
    /* ---- GPU profile ---- */
    bool prof = false;
    float ts_period_ns = 1.0f;
    enum { PC_DECODE = 32, PC_WB, PC_LOAD, PC_DISPLAY, PC_SNAP, PC_NR, PC_RT, PC_RTR, PC_N };
    double p_ms[64] = {}, p_px[64] = {};
    uint64_t p_n[64] = {};
    uint64_t disp_q0 = ~0ull;      /* display(): compose + copy, ended in the read-back / share */

    /* $RG_VK_STATS=1: counters printed at exit (measurement) */
    enum { ST_SUBMIT, ST_WAIT, ST_WRAP, ST_BARRIER, ST_RP, ST_DRAW, ST_DISPATCH, ST_PIPE, ST_N };
    uint64_t st_n[ST_N] = {};
    /* RG_VK_STATS=1: where rendering instances end (source line of the pre_op / end_rp that
     * ended an open one; line 0: begin_rp with other attachments) */
    std::map<int, uint64_t> st_break;
    void rp_break(int line) { if (in_rp) st_break[line]++; }

    VkBackend() { memset(slots, 0, sizeof slots); }

    /* ======================================================== setup */
    static VKAPI_ATTR VkBool32 VKAPI_CALL dbg_cb(VkDebugUtilsMessageSeverityFlagBitsEXT sev, VkDebugUtilsMessageTypeFlagsEXT,
                                                 const VkDebugUtilsMessengerCallbackDataEXT *d, void *)
    {
        static int n = 0;
        if (n < 400 && (sev & (VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT))) {
            fprintf(stderr, "vk validation: %s [ %s ] %s\n", (sev & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) ? "error" : "warning",
                    d->pMessageIdName ? d->pMessageIdName : "-", d->pMessage);
            n++;
        }
        return VK_FALSE;
    }

    bool init(const gpu_config *cfg, int s, char *err, size_t cap)
    {
        scale = s;
        if (volkInitialize() != VK_SUCCESS) {
            snprintf(err, cap, "Vulkan loader not found");
            return false;
        }
        if (volkGetInstanceVersion() < VK_API_VERSION_1_3) {
            snprintf(err, cap, "Vulkan 1.3 instance not available");
            return false;
        }
        const char *ve = getenv("RG_VK_VALIDATE");
        bool validate = ve && ve[0] == '1';
        std::vector<const char *> layers, iexts;
        if (validate) {
            uint32_t n = 0;
            vkEnumerateInstanceLayerProperties(&n, NULL);
            std::vector<VkLayerProperties> lp(n);
            vkEnumerateInstanceLayerProperties(&n, lp.data());
            for (auto &l : lp)
                if (!strcmp(l.layerName, "VK_LAYER_KHRONOS_validation")) layers.push_back("VK_LAYER_KHRONOS_validation");
            const char *ld = getenv("RG_VK_LAYER_DLL");
            if (layers.empty() && ld && *ld) {
                layer_gipa = vkl::load(ld);
                if (layer_gipa) fprintf(stderr, "rg vulkan: validation layer loaded by the backend (%s)\n", ld);
                else fprintf(stderr, "rg vulkan: RG_VK_LAYER_DLL=%s: not a layer library\n", ld);
            }
            if (layers.empty() && !layer_gipa)
                fprintf(stderr, "rg vulkan: RG_VK_VALIDATE=1 but VK_LAYER_KHRONOS_validation is not installed\n");
            else iexts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        {
            /* zero-copy presentation (docs/NATIVE-VULKAN.md "Presentation"): the window's renderer
             * creates its surface on this instance, so it gets the window-system surface extensions
             * the loader has (names only: no platform header; $RG_VK_PRESENT=0 = read-back only) */
            const char *pe = getenv("RG_VK_PRESENT");
            if (!(pe && pe[0] == '0')) {
                uint32_t n = 0;
                vkEnumerateInstanceExtensionProperties(NULL, &n, NULL);
                std::vector<VkExtensionProperties> ip(n);
                vkEnumerateInstanceExtensionProperties(NULL, &n, ip.data());
                static const char *const surf[] = { "VK_KHR_surface", "VK_KHR_win32_surface", "VK_KHR_xlib_surface",
                                                    "VK_KHR_xcb_surface", "VK_KHR_wayland_surface" };
                bool khr_surface = false;
                int nplat = 0;
                for (const char *x : surf)
                    for (auto &e : ip)
                        if (!strcmp(e.extensionName, x)) {
                            iexts.push_back(x);
                            if (x == surf[0]) khr_surface = true;
                            else nplat++;
                            break;
                        }
                surf_ok = khr_surface && nplat > 0;
            }
        }
        VkApplicationInfo app = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
        app.pApplicationName = "rg-game";
        app.pEngineName = "rg native renderer";
        app.apiVersion = VK_API_VERSION_1_3;
        VkInstanceCreateInfo ici = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
        ici.pApplicationInfo = &app;
        ici.enabledLayerCount = (uint32_t)layers.size();
        ici.ppEnabledLayerNames = layers.data();
        ici.enabledExtensionCount = (uint32_t)iexts.size();
        ici.ppEnabledExtensionNames = iexts.data();
        VkResult r;
        vkl::InstanceLink il = { NULL, vkGetInstanceProcAddr, NULL };
        vkl::InstanceCreateInfo lci[2] = {};
        VkValidationFeaturesEXT vfeat = { VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT };
        static const VkValidationFeatureEnableEXT vsync_val[] = { VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT };
        if (layer_gipa || !layers.empty()) {
            /* $RG_VK_VALIDATE_SYNC=1: synchronization validation too (hazards between commands) */
            const char *vs = getenv("RG_VK_VALIDATE_SYNC");
            if (vs && vs[0] == '1') {
                vfeat.enabledValidationFeatureCount = 1;
                vfeat.pEnabledValidationFeatures = vsync_val;
            }
            vfeat.pNext = ici.pNext;
            ici.pNext = &vfeat;
        }
        if (layer_gipa) {
            /* the layer in front of the loader (vkl above) */
            loader_gipa = vkGetInstanceProcAddr;
            lci[0].sType = lci[1].sType = VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO;
            lci[0].function = vkl::LINK_INFO;
            lci[0].u.link = &il;
            lci[0].pNext = &lci[1];
            lci[1].function = vkl::DATA_CALLBACK;
            lci[1].u.set_data = vkl::set_instance_data;
            lci[1].pNext = ici.pNext;
            ici.pNext = &lci[0];
            /* no handle wrapping: the window's renderer calls the driver with this backend's images
             * and semaphores directly (a wrapped handle there crashed in SDL's vkCreateImageView) */
            static const VkValidationFeatureDisableEXT nodis[] = { VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT };
            vfeat.disabledValidationFeatureCount = 1;
            vfeat.pDisabledValidationFeatures = nodis;
            PFN_vkCreateInstance ci = (PFN_vkCreateInstance)layer_gipa(VK_NULL_HANDLE, "vkCreateInstance");
            r = ci ? ci(&ici, NULL, &inst) : VK_ERROR_INITIALIZATION_FAILED;
            if (r == VK_SUCCESS) vkGetInstanceProcAddr = layer_gipa;   /* volk loads the rest through the layer */
        } else {
            r = vkCreateInstance(&ici, NULL, &inst);
        }
        if (r != VK_SUCCESS) {
            snprintf(err, cap, "vkCreateInstance failed (%d)", (int)r);
            return false;
        }
        volkLoadInstance(inst);
        if ((!layers.empty() || layer_gipa) && vkCreateDebugUtilsMessengerEXT) {
            VkDebugUtilsMessengerCreateInfoEXT dc = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
            dc.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            dc.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            dc.pfnUserCallback = dbg_cb;
            vkCreateDebugUtilsMessengerEXT(inst, &dc, NULL, &dbg);
        }
        /* the device: $RG_VK_DEVICE=N, else the first discrete GPU, else the first with 1.3 */
        uint32_t npd = 0;
        vkEnumeratePhysicalDevices(inst, &npd, NULL);
        std::vector<VkPhysicalDevice> pds(npd);
        vkEnumeratePhysicalDevices(inst, &npd, pds.data());
        int pick = -1;
        const char *de = getenv("RG_VK_DEVICE");
        for (int pass = 0; pass < 3 && pick < 0; pass++)
            for (uint32_t i = 0; i < npd && pick < 0; i++) {
                VkPhysicalDeviceProperties p;
                vkGetPhysicalDeviceProperties(pds[i], &p);
                if (p.apiVersion < VK_API_VERSION_1_3) continue;
                if (pass == 0 && de && *de && atoi(de) == (int)i) pick = (int)i;
                if (pass == 1 && !(de && *de) && p.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) pick = (int)i;
                if (pass == 2 && !(de && *de) && !cfg->warp) pick = (int)i;
                if (pass == 2 && cfg->warp && p.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU) pick = (int)i;
            }
        if (pick < 0) {
            snprintf(err, cap, "no Vulkan 1.3 device%s", cfg->warp ? " (CPU type for RG_GPU=warp)" : "");
            return false;
        }
        pd = pds[pick];
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(pd, &props);
        lim = props.limits;
        /* extensions */
        uint32_t nx = 0;
        vkEnumerateDeviceExtensionProperties(pd, NULL, &nx, NULL);
        std::vector<VkExtensionProperties> xp(nx);
        vkEnumerateDeviceExtensionProperties(pd, NULL, &nx, xp.data());
        auto has_ext = [&](const char *n) {
            for (auto &x : xp) if (!strcmp(x.extensionName, n)) return true;
            return false;
        };
        if (!has_ext(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME)) {
            snprintf(err, cap, "%s: no VK_KHR_push_descriptor", props.deviceName);
            return false;
        }
        bool have_il = has_ext(VK_EXT_FRAGMENT_SHADER_INTERLOCK_EXTENSION_NAME);
        bool have_dbc = has_ext(VK_EXT_DEPTH_BIAS_CONTROL_EXTENSION_NAME);
        /* graphics.raytracing (docs/RAYTRACING.md): asked for and the device has ray queries */
        const bool have_rt = cfg->raytracing > 0 && has_ext(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME) &&
                             has_ext(VK_KHR_RAY_QUERY_EXTENSION_NAME) && has_ext(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
        VkPhysicalDeviceAccelerationStructureFeaturesKHR fas = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR };
        VkPhysicalDeviceRayQueryFeaturesKHR frq = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR };
        /* features */
        VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT fil = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT };
        VkPhysicalDeviceVulkan13Features f13 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
        VkPhysicalDeviceVulkan12Features f12 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        VkPhysicalDeviceFeatures2 f2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
        f2.pNext = &f12;
        f12.pNext = &f13;
        VkPhysicalDeviceDepthBiasControlFeaturesEXT fdb = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_BIAS_CONTROL_FEATURES_EXT };
        if (have_il) f13.pNext = &fil;
        if (have_dbc) { fdb.pNext = f13.pNext; f13.pNext = &fdb; }
        if (have_rt) { frq.pNext = f13.pNext; fas.pNext = &frq; f13.pNext = &fas; }
        vkGetPhysicalDeviceFeatures2(pd, &f2);
        if (!f13.dynamicRendering || !f13.shaderDemoteToHelperInvocation || !f2.features.dualSrcBlend || !f2.features.depthClamp) {
            snprintf(err, cap, "%s: missing a required feature (dynamicRendering %d, demote %d, dualSrcBlend %d, depthClamp %d)",
                     props.deviceName, f13.dynamicRendering, f13.shaderDemoteToHelperInvocation, f2.features.dualSrcBlend,
                     f2.features.depthClamp);
            return false;
        }
        rov_ok = !cfg->no_rov && have_il && fil.fragmentShaderPixelInterlock && f2.features.fragmentStoresAndAtomics;
        zrov_ok = rov_ok && !cfg->no_zrov;
        VkPhysicalDeviceFeatures2 en2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
        VkPhysicalDeviceVulkan13Features en13 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
        VkPhysicalDeviceVulkan12Features en12 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT enil = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT };
        en2.pNext = &en13;
        en13.dynamicRendering = VK_TRUE;
        en13.shaderDemoteToHelperInvocation = VK_TRUE;
        en2.features.dualSrcBlend = VK_TRUE;
        en2.features.depthClamp = VK_TRUE;
        en2.features.fragmentStoresAndAtomics = f2.features.fragmentStoresAndAtomics;
        en2.features.fullDrawIndexUint32 = f2.features.fullDrawIndexUint32;
        /* graphics.anisotropic (optional: without it the setting keeps the bilinear sampler) */
        en2.features.samplerAnisotropy = f2.features.samplerAnisotropy;
        aniso_ok = f2.features.samplerAnisotropy != VK_FALSE;
        aniso_max = props.limits.maxSamplerAnisotropy;
        gs_ok = f2.features.geometryShader != VK_FALSE;
        en2.features.geometryShader = f2.features.geometryShader;
        std::vector<const char *> dx;
        dx.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);
        if (rov_ok) {
            en13.pNext = &enil;
            enil.fragmentShaderPixelInterlock = VK_TRUE;
            dx.push_back(VK_EXT_FRAGMENT_SHADER_INTERLOCK_EXTENSION_NAME);
        }
        VkPhysicalDeviceDepthBiasControlFeaturesEXT endb = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_BIAS_CONTROL_FEATURES_EXT };
        {
            /* $RG_VK_ZROV_BIAS (measurement; docs/NATIVE-VULKAN.md "Depth bias"): the rasterizer bias
             * of ordered-depth mesh draws.  off (default): none (the shader's own 2 units only);
             * float: VK_EXT_depth_bias_control's float representation; d32 / d24 / d16: an unused
             * depth attachment of that format sets the representation */
            const char *zb = getenv("RG_VK_ZROV_BIAS");
            if (zrov_ok && zb && !strcmp(zb, "float") && have_dbc && fdb.depthBiasControl && fdb.floatRepresentation) {
                endb.depthBiasControl = VK_TRUE;
                endb.floatRepresentation = VK_TRUE;
                endb.pNext = en13.pNext;
                en13.pNext = &endb;
                dx.push_back(VK_EXT_DEPTH_BIAS_CONTROL_EXTENSION_NAME);
                zrov_brep = 1;
            } else if (zrov_ok && zb && (!strcmp(zb, "d32") || !strcmp(zb, "d24") || !strcmp(zb, "d16"))) {
                zrov_bias_att = 1;
                if (!strcmp(zb, "d24")) zbias_fmt = VK_FORMAT_D24_UNORM_S8_UINT;
                if (!strcmp(zb, "d16")) zbias_fmt = VK_FORMAT_D16_UNORM;
            }
        }
        /* queue: graphics + compute */
        uint32_t nq = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(pd, &nq, NULL);
        std::vector<VkQueueFamilyProperties> qp(nq);
        vkGetPhysicalDeviceQueueFamilyProperties(pd, &nq, qp.data());
        qf = ~0u;
        for (uint32_t i = 0; i < nq && qf == ~0u; i++)
            if ((qp[i].queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) == (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT))
                qf = i;
        if (qf == ~0u) {
            snprintf(err, cap, "%s: no graphics+compute queue", props.deviceName);
            return false;
        }
        /* a presenter on this device (the window's SDL renderer, docs/NATIVE-VULKAN.md "Presentation")
         * takes queue 0 of the family and the backend queue 1: a queue is externally synchronised and
         * the two submit from different threads.  Also needs the swapchain extension and timeline
         * semaphores (the presenter waits for a frame on one). */
        pres_ok = surf_ok && has_ext(VK_KHR_SWAPCHAIN_EXTENSION_NAME) && qp[qf].queueCount >= 2 && f12.timelineSemaphore;
        if (pres_ok) {
            dx.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
            en12.timelineSemaphore = VK_TRUE;
            en12.pNext = en2.pNext;
            en2.pNext = &en12;
            qi = 1;
        }
        /* ray tracing: acceleration structures + ray queries + buffer device addresses (only when
         * graphics.raytracing asks: the default device is unchanged) */
        VkPhysicalDeviceAccelerationStructureFeaturesKHR enas = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR };
        VkPhysicalDeviceRayQueryFeaturesKHR enrq = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR };
        if (cfg->raytracing > 0) {
            if (have_rt && fas.accelerationStructure && frq.rayQuery && f12.bufferDeviceAddress && f2.features.shaderInt64) {
                rt_on = true;
                rt_dbg = cfg->raytracing == 2;
                rt_ao = cfg->raytracing >= 3;   /* (graphics.raytracing "shadows + AO") */
                rt_refl = cfg->raytracing >= 4;   /* (rt5: "shadows + AO + reflections") */
                dx.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
                dx.push_back(VK_KHR_RAY_QUERY_EXTENSION_NAME);
                dx.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
                enas.accelerationStructure = VK_TRUE;
                enrq.rayQuery = VK_TRUE;
                en2.features.shaderInt64 = VK_TRUE;   /* RT2b: the candidate loop's 64-bit addresses */
                enas.pNext = &enrq;
                enrq.pNext = en2.pNext;
                en2.pNext = &enas;
                en12.bufferDeviceAddress = VK_TRUE;
                if (!pres_ok) { en12.pNext = en2.pNext; en2.pNext = &en12; }
            } else {
                fprintf(stderr, "rg gpu: ray tracing unavailable on %s (%d-bit driver: %s); off\n", props.deviceName,
                        (int)(sizeof(void *) * 8), !have_rt ? "no VK_KHR_acceleration_structure / VK_KHR_ray_query"
                                                            : "a ray-tracing feature is missing");
            }
        }
        float prio[2] = { 1.0f, 1.0f };
        VkDeviceQueueCreateInfo qci = { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
        qci.queueFamilyIndex = qf;
        qci.queueCount = pres_ok ? 2 : 1;
        qci.pQueuePriorities = prio;
        VkDeviceCreateInfo dci = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
        dci.pNext = &en2;
        dci.queueCreateInfoCount = 1;
        dci.pQueueCreateInfos = &qci;
        dci.enabledExtensionCount = (uint32_t)dx.size();
        dci.ppEnabledExtensionNames = dx.data();
        vkl::DeviceLink dl = { NULL, loader_gipa, NULL };
        vkl::DeviceCreateInfo ldi[2] = {};
        if (layer_gipa) {
            dl.gdpa = (PFN_vkGetDeviceProcAddr)loader_gipa(inst, "vkGetDeviceProcAddr");
            ldi[0].sType = ldi[1].sType = VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO;
            ldi[0].function = vkl::LINK_INFO;
            ldi[0].u.link = &dl;
            ldi[0].pNext = &ldi[1];
            ldi[1].function = vkl::DATA_CALLBACK;
            ldi[1].u.set_data = vkl::set_device_data;
            ldi[1].pNext = dci.pNext;
            dci.pNext = &ldi[0];
        }
        r = vkCreateDevice(pd, &dci, NULL, &dev);
        if (r != VK_SUCCESS) {
            snprintf(err, cap, "vkCreateDevice failed (%d)", (int)r);
            return false;
        }
        volkLoadDevice(dev);
        vkGetDeviceQueue(dev, qf, qi, &queue);
        if (pres_ok) {
            VkSemaphoreTypeCreateInfo sti = { VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO };
            sti.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE;
            VkSemaphoreCreateInfo sc = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
            sc.pNext = &sti;
            if (vkCreateSemaphore(dev, &sc, NULL, &tl) != VK_SUCCESS) { tl = VK_NULL_HANDLE; pres_ok = false; }
        }
        lag = cfg->readback_lag != 0;
        {
            /* GPU time per kind of work ($RG_GPU_PROFILE=1, as nr_d3d11.cpp): timestamp queries */
            const char *pe = getenv("RG_GPU_PROFILE");
            prof = pe && pe[0] == '1' && qp[qf].timestampValidBits > 0 && props.limits.timestampPeriod > 0.0f;
            ts_period_ns = props.limits.timestampPeriod;
        }
        snprintf(devname, sizeof devname, "Vulkan %s (API %u.%u.%u%s%s)", props.deviceName, VK_API_VERSION_MAJOR(props.apiVersion),
                 VK_API_VERSION_MINOR(props.apiVersion), VK_API_VERSION_PATCH(props.apiVersion), rov_ok ? ", interlock" : "",
                 zrov_brep ? ", float bias" : zrov_bias_att ? ", bias attachment" : "");
        if (rt_on) {
            size_t dl = strlen(devname);
            snprintf(devname + dl, sizeof devname - dl, ", ray query%s%s%s", rt_dbg ? " debug" : "", rt_ao ? " + AO" : "", rt_refl ? " + reflections" : "");
            VkPhysicalDeviceAccelerationStructurePropertiesKHR asp = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR };
            VkPhysicalDeviceProperties2 p2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2, &asp };
            vkGetPhysicalDeviceProperties2(pd, &p2);
            rt_scratch_align = asp.minAccelerationStructureScratchOffsetAlignment ? asp.minAccelerationStructureScratchOffsetAlignment : 256;
        }
        {
            VmaVulkanFunctions vf = {};
            vf.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
            vf.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
            VmaAllocatorCreateInfo ai = {};
            ai.physicalDevice = pd;
            ai.device = dev;
            ai.instance = inst;
            ai.vulkanApiVersion = VK_API_VERSION_1_3;
#if defined(_WIN64)
            ai.pVulkanFunctions = &vf; static VkExternalMemoryHandleTypeFlags rg_xt[VK_MAX_MEMORY_TYPES]; if (rg_x64_vk_extmem()) { for (auto &t : rg_xt) t = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT; ai.pTypeExternalMemoryHandleTypes = rg_xt; }
#else
#line 788
            ai.pVulkanFunctions = &vf;
#endif
#line 789
            if (rt_on) ai.flags |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
            if (vmaCreateAllocator(&ai, &vma) != VK_SUCCESS) {
                snprintf(err, cap, "vmaCreateAllocator failed");
                return false;
            }
        }
        {
            VkPipelineCacheCreateInfo pc = { VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO };
            vkCreatePipelineCache(dev, &pc, NULL, &pcache);
        }
        for (int i = 0; i < NSUB; i++) {
            VkCommandPoolCreateInfo pc = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
            pc.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
            pc.queueFamilyIndex = qf;
            if (vkCreateCommandPool(dev, &pc, NULL, &subs[i].pool) != VK_SUCCESS) { snprintf(err, cap, "command pool"); return false; }
            VkCommandBufferAllocateInfo ca = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
            ca.commandPool = subs[i].pool;
            ca.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            ca.commandBufferCount = 1;
            if (vkAllocateCommandBuffers(dev, &ca, &subs[i].cb) != VK_SUCCESS) { snprintf(err, cap, "command buffer"); return false; }
            VkFenceCreateInfo fc = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
            if (vkCreateFence(dev, &fc, NULL, &subs[i].fence) != VK_SUCCESS) { snprintf(err, cap, "fence"); return false; }
            if (prof) {
                VkQueryPoolCreateInfo qc = { VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO };
                qc.queryType = VK_QUERY_TYPE_TIMESTAMP;
                qc.queryCount = PQ_MAX;
                if (vkCreateQueryPool(dev, &qc, NULL, &subs[i].qp) != VK_SUCCESS) prof = false;
            }
        }
#define CHK(x, what) do { if (!(x)) { snprintf(err, cap, "%s failed", what); return false; } } while (0)
        {
            const char *rm = getenv("RG_VK_RING_MB");
            VkDeviceSize mb = rm ? (VkDeviceSize)atoi(rm) : 96;
            if (mb < 16) mb = 16;
            CHK(buf_make(ring, mb << 20, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 1), "upload ring");
        }
        const VkBufferUsageFlags SB = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        CHK(buf_make(mem, GS_VRAM_BYTES, SB, 0), "mirror");
        CHK(buf_make(mem_rb, GS_VRAM_BYTES, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2), "mirror read-back");
        CHK(buf_make(merge, GS_VRAM_BYTES * 2, SB, 0), "merge buffer");
        CHK(buf_make(clut, sizeof(GpuClutCB), VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
                                                  VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 0), "clut buffer");
        CHK(buf_view(clut), "clut view");
        CHK(buf_make(clut_rb, sizeof(GpuClutCB), VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2), "clut read-back");
        CHK(buf_make(dummy_buf, 65536, SB | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
                                           VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT, 0), "dummy buffer");
        CHK(buf_view(dummy_buf), "dummy view");
        CHK(img_make(dummy_rgba, 1, 1, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT |
                                                                     VK_IMAGE_USAGE_TRANSFER_DST_BIT, true), "dummy image");
        CHK(img_make(dummy_r32f, 1, 1, VK_FORMAT_R32_SFLOAT, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT |
                                                                 VK_IMAGE_USAGE_TRANSFER_DST_BIT, false), "dummy image");
        pre_op();
        vkCmdFillBuffer(cb(), dummy_buf.b, 0, VK_WHOLE_SIZE, 0);
        vkCmdFillBuffer(cb(), mem.b, 0, VK_WHOLE_SIZE, 0);
        vkCmdFillBuffer(cb(), clut.b, 0, VK_WHOLE_SIZE, 0);
        clear_img(dummy_rgba.i, false);
        clear_img(dummy_r32f.i, false);
        post_op();
        {
            VkSamplerCreateInfo sc = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
            sc.magFilter = sc.minFilter = VK_FILTER_LINEAR;
            sc.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
            sc.addressModeU = sc.addressModeV = sc.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            sc.maxLod = VK_LOD_CLAMP_NONE;
            CHK(vkCreateSampler(dev, &sc, NULL, &smp_lin) == VK_SUCCESS, "sampler");
            for (int l = 0; l < 2; l++)
                for (int u = 0; u < 2; u++)
                    for (int v = 0; v < 2; v++) {
                        VkSamplerCreateInfo sn = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
                        sn.magFilter = sn.minFilter = l ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
                        sn.mipmapMode = l ? VK_SAMPLER_MIPMAP_MODE_LINEAR : VK_SAMPLER_MIPMAP_MODE_NEAREST;
                        sn.addressModeU = u ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
                        sn.addressModeV = v ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
                        sn.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
                        sn.maxLod = 0.0f;
                        CHK(vkCreateSampler(dev, &sn, NULL, &smp_nr[l][u][v]) == VK_SUCCESS, "sampler");
                    }
            for (int a = 0; a < 4 && aniso_ok; a++)
                for (int u = 0; u < 2; u++)
                    for (int v = 0; v < 2; v++) {
                        VkSamplerCreateInfo sn = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
                        sn.magFilter = sn.minFilter = VK_FILTER_LINEAR;
                        sn.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
                        sn.addressModeU = u ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
                        sn.addressModeV = v ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
                        sn.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
                        sn.maxLod = 0.0f;
                        sn.anisotropyEnable = VK_TRUE;
                        sn.maxAnisotropy = (float)(2u << a);
                        if (sn.maxAnisotropy > aniso_max) sn.maxAnisotropy = aniso_max;
                        CHK(vkCreateSampler(dev, &sn, NULL, &smp_nr_an[a][u][v]) == VK_SUCCESS, "sampler");
                    }
        }
#define SH(var, name, stage, entry) CHK(shader_make(var, g_spv_##name, sizeof g_spv_##name, stage, entry), #name)
        SH(sh_vs_quad, VS_quad, VK_SHADER_STAGE_VERTEX_BIT, "VS_quad");
        SH(sh_ps_load_color, PS_load_color, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_load_color");
        SH(sh_ps_load_depth, PS_load_depth, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_load_depth");
        SH(sh_ps_load_depth_rt, PS_load_depth_rt, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_load_depth");
        SH(sh_ps_copy_depth, PS_copy_depth, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_copy_depth");
        SH(sh_ps_display, PS_display, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_display");
        SH(sh_cs_wb_color, CS_wb_color, VK_SHADER_STAGE_COMPUTE_BIT, "CS_wb_color");
        SH(sh_cs_load_phase, CS_load_phase, VK_SHADER_STAGE_COMPUTE_BIT, "CS_load_phase");
        SH(sh_cs_wb_depth, CS_wb_depth, VK_SHADER_STAGE_COMPUTE_BIT, "CS_wb_depth");
        SH(sh_cs_merge, CS_merge, VK_SHADER_STAGE_COMPUTE_BIT, "CS_merge");
        SH(sh_cs_clut, CS_clut, VK_SHADER_STAGE_COMPUTE_BIT, "CS_clut");
        SH(sh_cs_l2l_read, CS_l2l_read, VK_SHADER_STAGE_COMPUTE_BIT, "CS_l2l_read");
        SH(sh_cs_l2l_write, CS_l2l_write, VK_SHADER_STAGE_COMPUTE_BIT, "CS_l2l_write");
        SH(sh_cs_xfer, CS_xfer, VK_SHADER_STAGE_COMPUTE_BIT, "CS_xfer");
        SH(sh_cs_decode, CS_decode, VK_SHADER_STAGE_COMPUTE_BIT, "CS_decode");
        SH(sh_ps_resample, PS_resample, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_resample");
        SH(sh_ps_fxaa, PS_fxaa, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_fxaa");
        SH(sh_ps_sharpen, PS_sharpen, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_sharpen");
        SH(sh_ps_final, PS_final, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_final");
        SH(sh_vs_nr, VS_nr, VK_SHADER_STAGE_VERTEX_BIT, "VS_nr");
        SH(sh_vs_im, VS_im, VK_SHADER_STAGE_VERTEX_BIT, "VS_im");
        if (gs_ok) SH(sh_gs_nr, GS_nr, VK_SHADER_STAGE_GEOMETRY_BIT, "GS_nr");
        SH(sh_ps_nr, PS_nr, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
        if (zrov_ok) SH(sh_ps_nr_z, PS_nr_z, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
        if (rov_ok) SH(sh_ps_nr_c, PS_nr_c, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
        if (rov_ok && zrov_ok) SH(sh_ps_nr_cz, PS_nr_cz, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
#undef SH
        if (rt_on) {
            /* the ray-query mesh pipeline (docs/RAYTRACING.md); a failure leaves ray tracing off */
            bool ok = shader_make(sh_vs_nr_rt, g_spv_VS_nr_rt, sizeof g_spv_VS_nr_rt, VK_SHADER_STAGE_VERTEX_BIT, "VS_nr") &&
                      shader_make(sh_ps_nr_rt, g_spv_PS_nr_rt, sizeof g_spv_PS_nr_rt, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
            if (ok && gs_ok) ok = shader_make(sh_gs_nr_rt, g_spv_GS_nr_rt, sizeof g_spv_GS_nr_rt, VK_SHADER_STAGE_GEOMETRY_BIT, "GS_nr");
            if (ok && zrov_ok) ok = shader_make(sh_ps_nr_zrt, g_spv_PS_nr_zrt, sizeof g_spv_PS_nr_zrt, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
            if (!ok) { fprintf(stderr, "rg gpu: ray-tracing shaders failed; ray tracing off\n"); rt_on = false; }
            rt_params();
        }
#undef CHK
        emi.init(rt_on ? cfg->rt_emissive : 0);   /* (rt8) emissive surfaces: graphics.rt_emissive / $RG_EMI, census $RG_EMI_CENSUS (nr_emi.h) */
        {
            const char *zb = getenv("RG_NR_ZBIAS");
            nr_zbias = zb ? atoi(zb) : -2;
            const char *zv = getenv("RG_VK_ZROV_BIAS_UNITS");   /* measurement: the ordered-depth bias only */
            zrov_units = zv ? atoi(zv) : nr_zbias;
            const char *nn = getenv("RG_GPU_NO_NATIVE");
            nr_ok = !(nn && nn[0] == '1');
        }
        submit();
        return true;
    }

    ~VkBackend() override
    {
        destroying = true;
        {
            const char *e = getenv("RG_VK_STATS");
            if (e && e[0] == '1')
                fprintf(stderr, "rg vulkan: %llu submits, %llu fence waits, %llu ring wraps, %llu barriers, %llu rendering instances, "
                                "%llu draws, %llu dispatches, %zu pipelines\n",
                        (unsigned long long)st_n[ST_SUBMIT], (unsigned long long)st_n[ST_WAIT], (unsigned long long)st_n[ST_WRAP],
                        (unsigned long long)st_n[ST_BARRIER], (unsigned long long)st_n[ST_RP], (unsigned long long)st_n[ST_DRAW],
                        (unsigned long long)st_n[ST_DISPATCH], gpipes.size());
            if (e && e[0] == '1') {
                std::vector<std::pair<uint64_t, int>> v;
                for (auto &k : st_break) v.push_back(std::make_pair(k.second, k.first));
                std::sort(v.rbegin(), v.rend());
                fprintf(stderr, "rg vulkan: rendering instances ended at (nr_vulkan.cpp line: count):");
                for (size_t i = 0; i < v.size() && i < 12; i++) fprintf(stderr, " %d: %llu", v[i].second, (unsigned long long)v[i].first);
                fprintf(stderr, "\n");
            }
        }
        if (dev) {
            wait_all();
            vkDeviceWaitIdle(dev);
            if (prof) prof_print();
            for (int i = 0; i < 2; i++) img_free(ps[i].img);
            for (Retired &r : ps_retired) img_free(r.img);
            for (int i = 0; i < 2; i++) buf_free(lagq[i].b);
            if (tl) vkDestroySemaphore(dev, tl, NULL);
            for (int i = 0; i < NSUB; i++)
                if (subs[i].qp) vkDestroyQueryPool(dev, subs[i].qp, NULL);
            for (size_t i = 0; i < targets.size(); i++) free_target(targets[i]);
            for (Target &t : rt_pool) free_target(t);
            for (int i = 0; i < NSUB; i++) run_dels(subs[i]);
            for (auto &e : nr_mesh) { buf_free(e.second.vb); buf_free(e.second.ib); rt_as_free(e.second.blas); }
            rt_as_free(rt_tlas);
            buf_free(rt_scratch); buf_free(rt_ibuf); buf_free(rt_mbuf);
            for (auto &e : rt_alpha) { buf_free(e.second.b); buf_free(e.second.rb); }
            buf_free(rt_stat); buf_free(rt_statrb);
            rt_as_free(rt_ptlas); buf_free(rt_pibuf); buf_free(rt_pmbuf);
            rt_as_free(rt_ctlas); rt_as_free(rt_pctlas); buf_free(rt_cibuf); buf_free(rt_pcibuf); buf_free(rt_cdummy);
            for (auto &e : rt_dyn) { rt_as_free(e.second.blas); buf_free(e.second.vb); }
            rt_print_stats();
            emi_exit();   /* (rt8) */
            rt_hist_free();
            for (auto &e : pre) { buf_free(e.second.vb); buf_free(e.second.ib); buf_free(e.second.st); }
            for (NrTex &t : nr_tex) img_free(t.img);
            for (auto &e : nr_rep) img_free(e.second.img);
            for (int i = 0; i < 24; i++) {
                VkSampler &sm = i < 8 ? smp_rep[i >> 2][(i >> 1) & 1][i & 1] : smp_rep_an[(i - 8) >> 2][((i - 8) >> 1) & 1][(i - 8) & 1];
                if (sm) vkDestroySampler(dev, sm, NULL);
            }
            for (auto &e : zbias_img) img_free(e.second);
            img_free(disp);
            for (int i = 0; i < 3; i++) img_free(post[i]);
            img_free(dummy_rgba);
            img_free(dummy_r32f);
            buf_free(ring); buf_free(mem); buf_free(mem_rb); buf_free(merge); buf_free(xdesc); buf_free(l2l); buf_free(scr);
            buf_free(clut); buf_free(clut_rb); buf_free(dummy_buf); buf_free(out_rb);
            for (int k = 0; k < SNAP_SLOTS; k++) buf_free(snapb[k]);
            for (auto &e : gpipes) vkDestroyPipeline(dev, e.second, NULL);
            for (auto &e : progs) {
                if (e.second->comp) vkDestroyPipeline(dev, e.second->comp, NULL);
                vkDestroyPipelineLayout(dev, e.second->pl, NULL);
                vkDestroyDescriptorSetLayout(dev, e.second->dsl, NULL);
                delete e.second;
            }
            for (auto *m : { &progs_gs, &progs_gs_rt })
                for (auto &e : *m) {
                    vkDestroyPipelineLayout(dev, e.second->pl, NULL);
                    vkDestroyDescriptorSetLayout(dev, e.second->dsl, NULL);
                    delete e.second;
                }
            Shader *all[] = { &sh_vs_quad, &sh_ps_load_color, &sh_ps_load_depth, &sh_ps_load_depth_rt, &sh_ps_copy_depth, &sh_ps_display,
                              &sh_cs_wb_color, &sh_cs_wb_depth, &sh_cs_merge, &sh_cs_clut, &sh_cs_l2l_read, &sh_cs_l2l_write,
                              &sh_cs_xfer, &sh_cs_decode, &sh_ps_resample, &sh_ps_fxaa, &sh_ps_sharpen, &sh_ps_final, &sh_vs_nr,
                              &sh_vs_im, &sh_ps_nr, &sh_ps_nr_z, &sh_ps_nr_c, &sh_ps_nr_cz, &sh_cs_load_phase, &sh_gs_nr,
                              &sh_vs_nr_rt, &sh_gs_nr_rt, &sh_ps_nr_rt, &sh_ps_nr_zrt };
            for (Shader *s : all) if (s->m) vkDestroyShaderModule(dev, s->m, NULL);
            if (smp_lin) vkDestroySampler(dev, smp_lin, NULL);
            for (int i = 0; i < 8; i++) if (smp_nr[i >> 2][(i >> 1) & 1][i & 1]) vkDestroySampler(dev, smp_nr[i >> 2][(i >> 1) & 1][i & 1], NULL);
            for (int i = 0; i < 16; i++) if (smp_nr_an[i >> 2][(i >> 1) & 1][i & 1]) vkDestroySampler(dev, smp_nr_an[i >> 2][(i >> 1) & 1][i & 1], NULL);
            for (int i = 0; i < NSUB; i++) {
                if (subs[i].fence) vkDestroyFence(dev, subs[i].fence, NULL);
                if (subs[i].pool) vkDestroyCommandPool(dev, subs[i].pool, NULL);
            }
            if (pcache) vkDestroyPipelineCache(dev, pcache, NULL);
            if (vma) vmaDestroyAllocator(vma);
            vkDestroyDevice(dev, NULL);
        }
        if (dbg) vkDestroyDebugUtilsMessengerEXT(inst, dbg, NULL);
        if (inst) vkDestroyInstance(inst, NULL);
    }

    const char *name() const override { return devname; }
    bool exact() const override { return false; }
    bool rov() const override { return rov_ok; }
    bool zrov() const override { return zrov_ok; }

    /* ======================================================== memory helpers */
    /* host: 0 device-local, 1 host-visible write (ring, staging), 2 host read-back */
    bool buf_make(Buf &b, VkDeviceSize size, VkBufferUsageFlags usage, int host)
    {
        VkBufferCreateInfo bi = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bi.size = size;
#if defined(_WIN64)
        bi.usage = usage; static thread_local VkExternalMemoryBufferCreateInfo rg_xb; if (rg_x64_vk_extmem()) { rg_xb = { VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO, NULL, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT }; bi.pNext = &rg_xb; }
#else
#line 1010
        bi.usage = usage;
#endif
#line 1011
        VmaAllocationCreateInfo ai = {};
        ai.usage = VMA_MEMORY_USAGE_AUTO;
        if (host == 1) ai.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
        if (host == 2) ai.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
        if (host) ai.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
        VmaAllocationInfo inf = {};
        if (vmaCreateBuffer(vma, &bi, &ai, &b.b, &b.a, &inf) != VK_SUCCESS) { b = Buf(); return false; }
        b.map = (uint8_t *)inf.pMappedData;
        b.size = size;
        return true;
    }
    bool buf_view(Buf &b)
    {
        VkBufferViewCreateInfo vi = { VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO };
        vi.buffer = b.b;
        vi.format = VK_FORMAT_R32_UINT;
        vi.range = VK_WHOLE_SIZE;
        return vkCreateBufferView(dev, &vi, NULL, &b.view) == VK_SUCCESS;
    }
    void buf_free(Buf &b)
    {
        if (b.view) vkDestroyBufferView(dev, b.view, NULL);
        if (b.b) vmaDestroyBuffer(vma, b.b, b.a);
        b = Buf();
    }
    void buf_defer(Buf &b)
    {
        if (!b.b) return;
        Del d;
        d.b = b.b; d.a = b.a; d.bv = b.view;
        defer(d);
        b = Buf();
    }
    /* invalidate a read-back buffer's range (no-op on coherent memory) */
    void buf_inval(Buf &b) { vmaInvalidateAllocation(vma, b.a, 0, VK_WHOLE_SIZE); }

    VkImageView view_make(VkImage i, VkFormat f, VkImageAspectFlags asp)
    {
        VkImageViewCreateInfo vi = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
        vi.image = i;
        vi.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vi.format = f;
        vi.subresourceRange.aspectMask = asp;
        vi.subresourceRange.levelCount = mk_levels;
        vi.subresourceRange.layerCount = 1;
        VkImageView v = VK_NULL_HANDLE;
        if (vkCreateImageView(dev, &vi, NULL, &v) != VK_SUCCESS) return VK_NULL_HANDLE;
        return v;
    }
    uint32_t mk_levels = 1;   /* (image_raw / view_make: mip levels of the next image; HD replacements only) */
    /* image in GENERAL (the transition recorded now); r32: an R32_UINT storage view of an RGBA8 image */
    bool image_raw(VkImage *img, VmaAllocation *al, int w, int h, VkFormat f, VkImageUsageFlags usage, bool mutable_r32)
    {
        VkImageCreateInfo ii = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
        VkImageFormatListCreateInfo fl = { VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO };
        VkFormat fmts[2] = { f, VK_FORMAT_R32_UINT };
        if (mutable_r32) {
            ii.flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
            fl.viewFormatCount = 2;
            fl.pViewFormats = fmts;
            ii.pNext = &fl;
        }
        ii.imageType = VK_IMAGE_TYPE_2D;
        ii.format = f;
        ii.extent = { (uint32_t)w, (uint32_t)h, 1 };
        ii.mipLevels = mk_levels;
        ii.arrayLayers = 1;
        ii.samples = VK_SAMPLE_COUNT_1_BIT;
        ii.tiling = VK_IMAGE_TILING_OPTIMAL;
        ii.usage = usage;
#if defined(_WIN64)
        ii.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED; static thread_local VkExternalMemoryImageCreateInfo rg_xi; if (rg_x64_vk_extmem()) { rg_xi = { VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO, ii.pNext, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT }; ii.pNext = &rg_xi; }
#else
#line 1080
        ii.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
#endif
#line 1081
        VmaAllocationCreateInfo ai = {};
        ai.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
        if (vmaCreateImage(vma, &ii, &ai, img, al, NULL) != VK_SUCCESS) { *img = VK_NULL_HANDLE; *al = NULL; return false; }
        pre_op();
        VkImageMemoryBarrier b = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        b.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        b.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        b.newLayout = VK_IMAGE_LAYOUT_GENERAL;
        b.srcQueueFamilyIndex = b.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        b.image = *img;
        b.subresourceRange.aspectMask = f == VK_FORMAT_D24_UNORM_S8_UINT ? VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT
                                        : (f == VK_FORMAT_D32_SFLOAT || f == VK_FORMAT_D16_UNORM) ? VK_IMAGE_ASPECT_DEPTH_BIT
                                                                                                  : VK_IMAGE_ASPECT_COLOR_BIT;
        b.subresourceRange.levelCount = mk_levels;
        b.subresourceRange.layerCount = 1;
        vkCmdPipelineBarrier(cb(), VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, NULL, 0, NULL, 1, &b);
        return true;
    }
    bool img_make(Img &m, int w, int h, VkFormat f, VkImageUsageFlags usage, bool mutable_r32)
    {
        m = Img();
        if (!image_raw(&m.i, &m.a, w, h, f, usage, mutable_r32)) return false;
        m.fmt = f; m.w = w; m.h = h;
        m.v = view_make(m.i, f, VK_IMAGE_ASPECT_COLOR_BIT);
        if (mutable_r32) m.uv = view_make(m.i, VK_FORMAT_R32_UINT, VK_IMAGE_ASPECT_COLOR_BIT);
        else if (usage & VK_IMAGE_USAGE_STORAGE_BIT) m.uv = m.v;
        return m.v != VK_NULL_HANDLE;
    }
    VkFormat zbias_fmt = VK_FORMAT_D32_SFLOAT;
    bool img_make_depth(Img &m, int w, int h)
    {
        m = Img();
        if (!image_raw(&m.i, &m.a, w, h, zbias_fmt, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, false)) return false;
        m.fmt = zbias_fmt; m.w = w; m.h = h;
        m.v = view_make(m.i, m.fmt, VK_IMAGE_ASPECT_DEPTH_BIT);
        return m.v != VK_NULL_HANDLE;
    }
    void img_free(Img &m)
    {
        if (m.uv && m.uv != m.v) vkDestroyImageView(dev, m.uv, NULL);
        if (m.v) vkDestroyImageView(dev, m.v, NULL);
        if (m.i) vmaDestroyImage(vma, m.i, m.a);
        m = Img();
    }
    void img_defer(Img &m)
    {
        if (!m.i) return;
        Del d;
        d.i = m.i; d.a = m.a; d.v[0] = m.v; d.v[1] = m.uv != m.v ? m.uv : VK_NULL_HANDLE;
        defer(d);
        m = Img();
    }
    void clear_img(VkImage i, bool depth)
    {
        VkImageSubresourceRange r = {};
        r.levelCount = 1;
        r.layerCount = 1;
        if (depth) {
            r.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
            VkClearDepthStencilValue z = { 0.0f, 0 };
            vkCmdClearDepthStencilImage(cb(), i, VK_IMAGE_LAYOUT_GENERAL, &z, 1, &r);
        } else {
            r.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            VkClearColorValue c = {};
            vkCmdClearColorImage(cb(), i, VK_IMAGE_LAYOUT_GENERAL, &c, 1, &r);
        }
    }

    bool shader_make(Shader &s, const unsigned char *code, size_t size, VkShaderStageFlagBits stage, const char *entry)
    {
        std::vector<uint32_t> w((size + 3) / 4);
        memcpy(w.data(), code, size);
        if (!spv_reflect(w.data(), w.size(), s.binds, s.inputs)) return false;
        {
            const char *nc = getenv("RG_VK_NO_COHERENT");   /* control: DXC's SPIR-V as it is */
            if (stage == VK_SHADER_STAGE_FRAGMENT_BIT && !(nc && nc[0] == '1')) spv_coherent_images(w);
        }
        VkShaderModuleCreateInfo mi = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
        mi.codeSize = w.size() * 4;
        mi.pCode = w.data();
        if (vkCreateShaderModule(dev, &mi, NULL, &s.m) != VK_SUCCESS) return false;
        s.stage = stage;
        s.entry = entry;
        return true;
    }

    /* ======================================================== submissions */
    void run_dels(Sub &s)
    {
        for (Del &d : s.dels) {
            if (d.as) vkDestroyAccelerationStructureKHR(dev, d.as, NULL);
            for (int k = 0; k < 3; k++) if (d.v[k]) vkDestroyImageView(dev, d.v[k], NULL);
            if (d.bv) vkDestroyBufferView(dev, d.bv, NULL);
            if (d.i) vmaDestroyImage(vma, d.i, d.a);
            if (d.b) vmaDestroyBuffer(vma, d.b, d.a);
        }
        s.dels.clear();
    }
    void sub_wait(Sub &s)
    {
        if (!s.busy) return;
        st_n[ST_WAIT]++;
        vkWaitForFences(dev, 1, &s.fence, VK_TRUE, UINT64_MAX);
        vkResetFences(dev, 1, &s.fence);
        s.busy = false;
        run_dels(s);
        if (prof) prof_collect(s);
    }
    VkCommandBuffer cb()
    {
        Sub &s = subs[ci];
        if (!recording) {
            sub_wait(s);
            vkResetCommandPool(dev, s.pool, 0);
            VkCommandBufferBeginInfo bi = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
            bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            vkBeginCommandBuffer(s.cb, &bi);
            recording = true;
            s.serial = serial_next;
            if (prof && s.qp) {
                vkCmdResetQueryPool(s.cb, s.qp, 0, PQ_MAX);
                s.qn = 0;
                s.ev.clear();
            }
            bound_pipe = VK_NULL_HANDLE;
            dirty = true;   /* the previous submission's writes: ordered by the barrier below */
        }
        return s.cb;
    }
    void defer(const Del &d)
    {
        cb();
        subs[ci].dels.push_back(d);
    }
    void submit()
    {
        if (!recording) return;
        end_rp();
        Sub &s = subs[ci];
        VkMemoryBarrier mb = { VK_STRUCTURE_TYPE_MEMORY_BARRIER };
        mb.srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
        mb.dstAccessMask = VK_ACCESS_HOST_READ_BIT | VK_ACCESS_MEMORY_READ_BIT;
        vkCmdPipelineBarrier(s.cb, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_HOST_BIT | VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                             0, 1, &mb, 0, NULL, 0, NULL);
        vkEndCommandBuffer(s.cb);
        VkSubmitInfo si = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
        si.commandBufferCount = 1;
        si.pCommandBuffers = &s.cb;
        VkTimelineSemaphoreSubmitInfo tsi = { VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO };
        uint64_t tv = s.serial;
        if (tl) {
            /* the presenter's acquire waits for the serial of the submission that wrote its frame */
            tsi.signalSemaphoreValueCount = 1;
            tsi.pSignalSemaphoreValues = &tv;
            si.pNext = &tsi;
            si.signalSemaphoreCount = 1;
            si.pSignalSemaphores = &tl;
        }
        st_n[ST_SUBMIT]++;
        VkResult r = vkQueueSubmit(queue, 1, &si, s.fence);
        if (r != VK_SUCCESS) {
            static int once;
            if (!once++) fprintf(stderr, "rg vulkan: vkQueueSubmit failed (%d)\n", (int)r);
        }
        s.busy = r == VK_SUCCESS;
        recording = false;
        serial_next++;
        ci = (ci + 1) % NSUB;
        dirty = false;
    }
    /* wait for the work recorded up to serial (submitting it if it is still recording) */
    void wait_serial(uint64_t serial)
    {
        if (recording && subs[ci].serial <= serial) submit();
        for (int i = 0; i < NSUB; i++)
            if (subs[i].busy && subs[i].serial <= serial) sub_wait(subs[i]);
    }
    void wait_all()
    {
        submit();
        for (int k = 1; k <= NSUB; k++) sub_wait(subs[(ci + k) % NSUB]);   /* oldest first */
    }

    /* ---- GPU profile ($RG_GPU_PROFILE=1; categories and output as nr_d3d11.cpp) ----
     * pts() writes a timestamp into the recording submission (bottom of pipe: the work recorded
     * before it has completed) and returns (serial << 32 | index); an event whose two stamps fell
     * into different submissions is dropped. */
    uint64_t pts()
    {
        if (!prof) return ~0ull;
        VkCommandBuffer c = cb();
        Sub &s = subs[ci];
        if (!s.qp || s.qn >= PQ_MAX) return ~0ull;
        vkCmdWriteTimestamp(c, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, s.qp, s.qn);
        return (s.serial << 32) | s.qn++;
    }
    void pev_add(int cat, uint64_t q0, double px)
    {
        uint64_t q1 = pts();
        if (q0 == ~0ull || q1 == ~0ull || (q0 >> 32) != (q1 >> 32)) return;
        subs[ci].ev.push_back(PEv{ cat, (uint32_t)q0, (uint32_t)q1, px });
    }
    void prof_collect(Sub &s)
    {
        if (!s.qn) return;
        std::vector<uint64_t> t(s.qn);
        if (vkGetQueryPoolResults(dev, s.qp, 0, s.qn, t.size() * 8, t.data(), 8, VK_QUERY_RESULT_64_BIT) == VK_SUCCESS)
            for (const PEv &e : s.ev)
                if (t[e.q1] >= t[e.q0]) {
                    p_ms[e.cat] += (double)(t[e.q1] - t[e.q0]) * (double)ts_period_ns * 1e-6;
                    p_n[e.cat]++;
                    p_px[e.cat] += e.px;
                }
        s.qn = 0;
        s.ev.clear();
    }
    void prof_print()
    {
        double tot = 0;
        for (int c = 0; c < PC_N; c++) tot += p_ms[c];
        fprintf(stderr, "gpu profile (GPU ms; draws by rov/direct/decoded/exact/textured):\n");
        for (int c = 0; c < PC_N; c++) {
            if (!p_n[c]) continue;
            char nm[64];
            if (c < 32)
                snprintf(nm, sizeof nm, "draw%s%s%s%s%s", c & 1 ? " rov" : "", c & 2 ? " direct" : "", c & 4 ? " decoded" : "",
                         c & 8 ? " exact" : "", c & 16 ? " tex" : " flat");
            else
                snprintf(nm, sizeof nm, "%s", c == PC_DECODE ? "decode" : c == PC_WB ? "write-back" : c == PC_LOAD ? "load"
                                              : c == PC_DISPLAY ? "display+copy" : c == PC_NR ? "native model draws" : c == PC_RT ? "ray tracing: BLAS + TLAS builds"
                                              : c == PC_RTR ? "ray tracing: receiver draws" : "snapshot");
            fprintf(stderr, "  %-36s %8llu calls %10.1f ms %5.1f%% %8.3f ms/call %10.1f Mpx\n", nm, (unsigned long long)p_n[c], p_ms[c],
                    tot > 0 ? 100.0 * p_ms[c] / tot : 0.0, p_ms[c] / (double)p_n[c], p_px[c] / 1e6);
        }
        fprintf(stderr, "  total %.1f ms\n", tot);
    }
    void disp_end(double px)
    {
        if (disp_q0 != ~0ull) pev_add(PC_DISPLAY, disp_q0, px);
        disp_q0 = ~0ull;
    }

    /* host-visible ring: n bytes at an offset aligned to al (b, off, host pointer p; p NULL: out of
     * memory).  A request larger than a quarter of the ring gets its own staging buffer, freed
     * with the current submission. */
    struct RA { VkBuffer b; VkDeviceSize off; uint8_t *p; };
    RA ring_alloc(VkDeviceSize n, VkDeviceSize al)
    {
        if (n > ring.size / 4) {
            Buf t;
            if (!buf_make(t, n, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 1))
                return RA{ VK_NULL_HANDLE, 0, NULL };
            RA r = { t.b, 0, t.map };
            buf_defer(t);
            return r;
        }
        if (al < 16) al = 16;
        VkDeviceSize off = (ring_head + al - 1) & ~(al - 1);
        if (off + n > ring.size) {
            /* wrap: every earlier user of the ring must be done (the current recording too) */
            st_n[ST_WRAP]++;
            wait_all();
            off = 0;
        }
        ring_head = off + n;
        return RA{ ring.b, off, ring.map + off };
    }
    RA ring_put(const void *src, VkDeviceSize n, VkDeviceSize al)
    {
        RA r = ring_alloc(n, al);
        if (r.p) memcpy(r.p, src, (size_t)n);
        return r;
    }

    /* ---- synchronisation ---- */
    void barrier()
    {
        if (!dirty) return;
        st_n[ST_BARRIER]++;
        VkMemoryBarrier mb = { VK_STRUCTURE_TYPE_MEMORY_BARRIER };
        mb.srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
        mb.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        vkCmdPipelineBarrier(cb(), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 1, &mb, 0, NULL, 0, NULL);
        dirty = false;
    }
    void pre_op_at(int line)
    {
        cb();
        rp_break(line);
        end_rp();
        barrier();
        clut_flush();
    }
    /* CLUT uploads (set_clut / set_clut_part) wait here until the next operation outside a
     * rendering instance: vkCmdUpdateBuffer cannot run inside one, and native draws do not read
     * the CLUT buffer (decodes, CLUT loads and reads do, all through pre_op), so a CLUT change
     * between draws no longer ends the instance (docs/NATIVE-RENDER.md "Throughput") */
    struct ClutUp { uint32_t off, n; uint32_t w[256]; };
    std::vector<ClutUp> clut_pend;
    void clut_flush()
    {
        if (clut_pend.empty()) return;
        for (const ClutUp &u : clut_pend) vkCmdUpdateBuffer(cb(), clut.b, u.off * 4u, u.n * 4u, u.w);
        clut_pend.clear();
        dirty = true;
        barrier();
    }
    void post_op() { dirty = true; }

    void end_rp()
    {
        if (!in_rp) return;
        vkCmdEndRendering(subs[ci].cb);
        in_rp = false;
    }
    /* a rendering instance on these attachments (kept across draws with the same ones) */
    void begin_rp(VkImageView c, VkImageView d, int w, int h, int noatt)
    {
        cb();
        if (in_rp && rp.c == c && rp.d == d && rp.w == w && rp.h == h && rp.noatt == noatt) return;
        rp_break(0);
        end_rp();
        barrier();
        VkRenderingAttachmentInfo ca = { VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO };
        ca.imageView = c;
        ca.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
        ca.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        ca.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        VkRenderingAttachmentInfo da = ca;
        da.imageView = d;
        VkRenderingInfo ri = { VK_STRUCTURE_TYPE_RENDERING_INFO };
        ri.renderArea.extent = { (uint32_t)w, (uint32_t)h };
        ri.layerCount = 1;
        ri.colorAttachmentCount = c ? 1 : 0;
        ri.pColorAttachments = c ? &ca : NULL;
        ri.pDepthAttachment = d ? &da : NULL;
        vkCmdBeginRendering(subs[ci].cb, &ri);
        st_n[ST_RP]++;
        in_rp = true;
        rp.c = c; rp.d = d; rp.w = w; rp.h = h; rp.noatt = noatt;
        dirty = true;
    }

    /* ======================================================== programs and pipelines */
    /* VS_nr + GS_nr + pixel shader b (a mesh with the VU clipper) */
    Prog *prog_gs(const Shader *b)
    {
        auto it = progs_gs.find(b);
        if (it != progs_gs.end()) return it->second;
        Prog *p = prog(&sh_vs_nr, b, &sh_gs_nr);
        progs_gs[b] = p;
        return p;
    }
    Prog *prog_gs_rt(const Shader *b)   /* VS_nr_rt + GS_nr_rt + b (ray tracing) */
    {
        auto it = progs_gs_rt.find(b);
        if (it != progs_gs_rt.end()) return it->second;
        Prog *p = prog(&sh_vs_nr_rt, b, &sh_gs_nr_rt);
        progs_gs_rt[b] = p;
        return p;
    }
    Prog *prog(const Shader *a, const Shader *b, const Shader *g = NULL)
    {
        if (!g) {
            auto it = progs.find(std::make_pair(a, b));
            if (it != progs.end()) return it->second;
        }
        Prog *p = new Prog();
        if (a->stage == VK_SHADER_STAGE_COMPUTE_BIT) p->cs = a;
        else { p->vs = a; p->ps = b; p->gs = g; }
        const Shader *ss[3] = { a, b, g };
        for (const Shader *s : ss) {
            if (!s) continue;
            for (const Bind &bd : s->binds) {
                bool have = false;
                for (Bind &e : p->binds) if (e.binding == bd.binding) have = true;
                if (!have) p->binds.push_back(bd);
            }
        }
        std::vector<VkDescriptorSetLayoutBinding> lb;
        VkShaderStageFlags st = p->cs ? VK_SHADER_STAGE_COMPUTE_BIT : VK_SHADER_STAGE_ALL_GRAPHICS;
        for (const Bind &bd : p->binds) {
            VkDescriptorSetLayoutBinding x = {};
            x.binding = bd.binding;
            x.descriptorType = bd.type;
            x.descriptorCount = 1;
            x.stageFlags = st;
            lb.push_back(x);
        }
        VkDescriptorSetLayoutCreateInfo dl = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
        dl.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR;
        dl.bindingCount = (uint32_t)lb.size();
        dl.pBindings = lb.data();
        vkCreateDescriptorSetLayout(dev, &dl, NULL, &p->dsl);
        VkPipelineLayoutCreateInfo pl = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
        pl.setLayoutCount = 1;
        pl.pSetLayouts = &p->dsl;
        vkCreatePipelineLayout(dev, &pl, NULL, &p->pl);
        if (p->cs) {
            VkComputePipelineCreateInfo ci_ = { VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO };
            ci_.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            ci_.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
            ci_.stage.module = a->m;
            ci_.stage.pName = a->entry;
            ci_.layout = p->pl;
            if (vkCreateComputePipelines(dev, pcache, 1, &ci_, NULL, &p->comp) != VK_SUCCESS) p->comp = VK_NULL_HANDLE;
        }
        if (!g) progs[std::make_pair(a, b)] = p;
        return p;
    }

    VkPipeline gpipe(const GKey &k)
    {
        std::string key((const char *)&k, sizeof k);
        auto it = gpipes.find(key);
        if (it != gpipes.end()) return it->second;
        const Prog *p = k.p;
        VkPipelineShaderStageCreateInfo st[3] = {};
        const int nst = p->gs ? 3 : 2;
        for (int i = 0; i < nst; i++) {
            const Shader *s = i == 0 ? p->vs : i == 1 ? p->ps : p->gs;
            st[i].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            st[i].stage = s->stage;
            st[i].module = s->m;
            st[i].pName = s->entry;
        }
        VkVertexInputBindingDescription vb = {};
        VkVertexInputAttributeDescription va[6] = {};
        uint32_t nva = 0;
        auto attr = [&](const char *sem, VkFormat f, uint32_t off) {
            uint32_t loc = p->vs->input_loc(sem);
            if (loc == ~0u) return;
            va[nva].location = loc;
            va[nva].binding = 0;
            va[nva].format = f;
            va[nva].offset = off;
            nva++;
        };
        if (k.vin == 1) {
            vb.stride = 28;
            attr("POSITION", VK_FORMAT_R16G16B16A16_SINT, 0);
            attr("NORMAL", VK_FORMAT_R8G8B8A8_SINT, 8);
            attr("TEXCOORD0", VK_FORMAT_R16G16_SINT, 12);
            attr("COLOR", VK_FORMAT_R8G8B8A8_UINT, 16);
            attr("BLENDINDICES", VK_FORMAT_R8G8B8A8_UINT, 20);
            attr("BLENDWEIGHT", VK_FORMAT_R8G8B8A8_UINT, 24);
        } else if (k.vin == 2) {
            vb.stride = (uint32_t)sizeof(GpuImVtx);
            attr("POSITION", VK_FORMAT_R32G32_SFLOAT, 0);
            attr("BLENDINDICES", VK_FORMAT_R32_UINT, 8);
            attr("COLOR", VK_FORMAT_R8G8B8A8_UINT, 12);
            attr("TEXCOORD0", VK_FORMAT_R32G32B32_SFLOAT, 16);
            attr("TEXCOORD1", VK_FORMAT_R32_UINT, 28);
        }
        VkPipelineVertexInputStateCreateInfo vi = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
        if (k.vin) {
            vi.vertexBindingDescriptionCount = 1;
            vi.pVertexBindingDescriptions = &vb;
            vi.vertexAttributeDescriptionCount = nva;
            vi.pVertexAttributeDescriptions = va;
        }
        VkPipelineInputAssemblyStateCreateInfo ia = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
        ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        VkPipelineViewportStateCreateInfo vp = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
        vp.viewportCount = 1;
        vp.scissorCount = 1;
        VkPipelineRasterizationStateCreateInfo rs = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
        rs.depthClampEnable = k.clamp ? VK_TRUE : VK_FALSE;
        rs.polygonMode = VK_POLYGON_MODE_FILL;
        rs.cullMode = k.cull == 1 ? VK_CULL_MODE_FRONT_BIT : k.cull == 2 ? VK_CULL_MODE_BACK_BIT : VK_CULL_MODE_NONE;
        rs.frontFace = VK_FRONT_FACE_CLOCKWISE;   /* D3D FrontCounterClockwise = FALSE (the image is not flipped) */
        rs.depthBiasEnable = k.bias ? VK_TRUE : VK_FALSE;
        rs.depthBiasConstantFactor = (float)k.bias;
        VkDepthBiasRepresentationInfoEXT brep = { VK_STRUCTURE_TYPE_DEPTH_BIAS_REPRESENTATION_INFO_EXT };
        if (k.bias && k.brep) {
            brep.depthBiasRepresentation = VK_DEPTH_BIAS_REPRESENTATION_FLOAT_EXT;
            rs.pNext = &brep;
        }
        rs.lineWidth = 1.0f;
        VkPipelineMultisampleStateCreateInfo ms = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
        ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        VkPipelineDepthStencilStateCreateInfo ds = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
        ds.depthTestEnable = k.zt ? VK_TRUE : VK_FALSE;
        ds.depthWriteEnable = k.zw ? VK_TRUE : VK_FALSE;
        ds.depthCompareOp = (VkCompareOp)k.zf;
        VkPipelineColorBlendAttachmentState ba = {};
        ba.blendEnable = k.blend ? VK_TRUE : VK_FALSE;
        ba.srcColorBlendFactor = (VkBlendFactor)k.sb;
        ba.dstColorBlendFactor = (VkBlendFactor)k.db;
        ba.colorBlendOp = (VkBlendOp)k.op;
        ba.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        ba.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        ba.alphaBlendOp = VK_BLEND_OP_ADD;
        ba.colorWriteMask = k.cmask & 15u;   /* 1 R 2 G 4 B 8 A, as D3D */
        VkPipelineColorBlendStateCreateInfo cbs = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
        cbs.attachmentCount = k.cf != VK_FORMAT_UNDEFINED ? 1 : 0;
        cbs.pAttachments = &ba;
        VkDynamicState dyn[2] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
        VkPipelineDynamicStateCreateInfo dy = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
        dy.dynamicStateCount = 2;
        dy.pDynamicStates = dyn;
        VkFormat cf = (VkFormat)k.cf;
        VkPipelineRenderingCreateInfo ri = { VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO };
        ri.colorAttachmentCount = k.cf != VK_FORMAT_UNDEFINED ? 1 : 0;
        ri.pColorAttachmentFormats = &cf;
        ri.depthAttachmentFormat = (VkFormat)k.df;
        VkGraphicsPipelineCreateInfo gi = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
        gi.pNext = &ri;
        gi.stageCount = (uint32_t)nst;
        gi.pStages = st;
        gi.pVertexInputState = &vi;
        gi.pInputAssemblyState = &ia;
        gi.pViewportState = &vp;
        gi.pRasterizationState = &rs;
        gi.pMultisampleState = &ms;
        gi.pDepthStencilState = &ds;
        gi.pColorBlendState = &cbs;
        gi.pDynamicState = &dy;
        gi.layout = p->pl;
        VkPipeline pp = VK_NULL_HANDLE;
        if (vkCreateGraphicsPipelines(dev, pcache, 1, &gi, NULL, &pp) != VK_SUCCESS) pp = VK_NULL_HANDLE;
        gpipes[key] = pp;
        return pp;
    }
    static GKey key0(const Prog *p)
    {
        GKey k;
        memset(&k, 0, sizeof k);
        k.p = p;
        k.cmask = 15;
        k.zf = VK_COMPARE_OP_ALWAYS;
        return k;
    }

    /* ---- slots (D3D registers) ---- */
    void slots_clear() { memset(slots, 0, sizeof slots); }
    void set_buf(int b, VkBuffer buf, VkDeviceSize off, VkDeviceSize range) { Slot &s = slots[b]; s.buf = buf; s.off = off; s.range = range; }
    void set_ubo(int reg, const void *data, VkDeviceSize n)
    {
        RA r = ring_put(data, n, lim.minUniformBufferOffsetAlignment);
        set_buf(B_CB + reg, r.b, r.off, n);
    }
    void set_tbuf(int b, VkBufferView v) { slots[b].bv = v; }
    void set_img(int b, VkImageView v) { slots[b].iv = v; }
    void set_smp(int reg, VkSampler s) { slots[B_S + reg].smp = s; }

    void push(const Prog *p, VkPipelineBindPoint bp)
    {
        VkWriteDescriptorSet w[B_N];
        VkDescriptorBufferInfo bi[B_N];
        VkDescriptorImageInfo ii[B_N];
        VkBufferView bv[B_N];
        VkWriteDescriptorSetAccelerationStructureKHR wa[B_N];
        VkAccelerationStructureKHR asv[B_N];
        uint32_t n = 0;
        for (const Bind &b : p->binds) {
            const Slot &s = slots[b.binding];
            VkWriteDescriptorSet &x = w[n];
            memset(&x, 0, sizeof x);
            x.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            x.dstBinding = b.binding;
            x.descriptorCount = 1;
            x.descriptorType = b.type;
            switch (b.type) {
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
                bi[n].buffer = s.buf ? s.buf : dummy_buf.b;
                bi[n].offset = s.buf ? s.off : 0;
                bi[n].range = s.buf ? s.range : VK_WHOLE_SIZE;
                x.pBufferInfo = &bi[n];
                break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
                bv[n] = s.bv ? s.bv : dummy_buf.view;
                x.pTexelBufferView = &bv[n];
                break;
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
                ii[n].sampler = VK_NULL_HANDLE;
                ii[n].imageView = s.iv ? s.iv : dummy_rgba.v;
                ii[n].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
                x.pImageInfo = &ii[n];
                break;
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
                ii[n].sampler = VK_NULL_HANDLE;
                ii[n].imageView = s.iv ? s.iv : (b.fmt == 3 ? dummy_r32f.v : dummy_rgba.uv);
                ii[n].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
                x.pImageInfo = &ii[n];
                break;
            case VK_DESCRIPTOR_TYPE_SAMPLER:
                ii[n].sampler = s.smp ? s.smp : smp_lin;
                ii[n].imageView = VK_NULL_HANDLE;
                x.pImageInfo = &ii[n];
                break;
            case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
                asv[n] = s.as ? s.as : rt_tlas.as;
                if (!asv[n]) continue;
                memset(&wa[n], 0, sizeof wa[n]);
                wa[n].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
                wa[n].accelerationStructureCount = 1;
                wa[n].pAccelerationStructures = &asv[n];
                x.pNext = &wa[n];
                break;
            default:
                continue;
            }
            n++;
        }
        if (n) vkCmdPushDescriptorSetKHR(subs[ci].cb, bp, p->pl, 0, n, w);
    }

    void dispatch(const Shader &cs, uint32_t gx, uint32_t gy, uint32_t gz)
    {
        Prog *p = prog(&cs, NULL);
        if (!p->comp) return;
        pre_op();
        VkCommandBuffer c = cb();
        vkCmdBindPipeline(c, VK_PIPELINE_BIND_POINT_COMPUTE, p->comp);
        bound_pipe = VK_NULL_HANDLE;
        push(p, VK_PIPELINE_BIND_POINT_COMPUTE);
        vkCmdDispatch(c, gx, gy, gz);
        st_n[ST_DISPATCH]++;
        post_op();
    }

    void set_vp_sc(int vw, int vh, int x0, int y0, int x1, int y1, int tw, int th)
    {
        VkViewport v = { 0.0f, 0.0f, (float)vw, (float)vh, 0.0f, 1.0f };
        vkCmdSetViewport(subs[ci].cb, 0, 1, &v);
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (x1 > tw) x1 = tw;
        if (y1 > th) y1 = th;
        if (x1 < x0) x1 = x0;
        if (y1 < y0) y1 = y0;
        VkRect2D r = { { x0, y0 }, { (uint32_t)(x1 - x0), (uint32_t)(y1 - y0) } };
        vkCmdSetScissor(subs[ci].cb, 0, 1, &r);
    }
    /* a full-screen triangle (VS_quad) with the slots set; c / d: attachments of w x h */
    bool quad(const GKey &k, VkImageView c, VkImageView d, int w, int h, int vw, int vh, int x0, int y0, int x1, int y1)
    {
        if (x1 <= x0 || y1 <= y0) return true;
        VkPipeline pp = gpipe(k);
        if (!pp) return false;
        begin_rp(c, d, w, h, 0);
        VkCommandBuffer c_ = subs[ci].cb;
        if (pp != bound_pipe) { vkCmdBindPipeline(c_, VK_PIPELINE_BIND_POINT_GRAPHICS, pp); bound_pipe = pp; }
        push(k.p, VK_PIPELINE_BIND_POINT_GRAPHICS);
        set_vp_sc(vw, vh, x0, y0, x1, y1, w, h);
        vkCmdDraw(c_, 3, 1, 0, 0);
        return true;
    }

    /* ======================================================== mirror */
    void mirror_upload(uint32_t off, uint32_t len, const uint8_t *src) override
    {
        if (!len) return;
        RA ra = ring_put(src, len, 16);
        if (!ra.p) return;
        pre_op();
        VkBufferCopy c = { ra.off, off, len };
        vkCmdCopyBuffer(cb(), ra.b, mem.b, 1, &c);
        post_op();
    }

    void mirror_download(const uint32_t *runs, int nruns, uint8_t *vram) override
    {
        if (nruns <= 0) return;
        pre_op();
        std::vector<VkBufferCopy> cs((size_t)nruns);
        for (int i = 0; i < nruns; i++) cs[(size_t)i] = VkBufferCopy{ runs[2 * i], runs[2 * i], runs[2 * i + 1] };
        vkCmdCopyBuffer(cb(), mem.b, mem_rb.b, (uint32_t)nruns, cs.data());
        post_op();
        wait_serial(subs[ci].serial);
        buf_inval(mem_rb);
        for (int i = 0; i < nruns; i++) memcpy(vram + runs[2 * i], mem_rb.map + runs[2 * i], runs[2 * i + 1]);
    }

    bool can_merge() const override { return true; }
    void mirror_merge(uint32_t w0, uint32_t n, const uint32_t *dm) override
    {
        if (!n) return;
        RA ra = ring_put(dm, (VkDeviceSize)n * 8, 16);
        if (!ra.p) return;
        pre_op();
        VkBufferCopy c = { ra.off, (VkDeviceSize)w0 * 8, (VkDeviceSize)n * 8 };
        vkCmdCopyBuffer(cb(), ra.b, merge.b, 1, &c);
        post_op();
        slots_clear();
        uint32_t u[8][4] = {};
        u[0][0] = w0; u[0][1] = n;
        set_ubo(0, u, sizeof u);
        set_buf(B_U + 0, mem.b, 0, VK_WHOLE_SIZE);
        set_buf(B_T + 2, merge.b, 0, VK_WHOLE_SIZE);
        dispatch(sh_cs_merge, (n + 63) / 64, 1, 1);
    }

    /* ======================================================== targets */
    bool mk_noclear = false;
    bool make_target(Target &t, int depth, int w, int h)
    {
        for (size_t i = 0; i < rt_pool.size(); i++) {
            Target &p = rt_pool[i];
            if (p.depth != depth || p.w != w || p.h != h) continue;
            t = p;
            rt_pool_bytes -= rt_bytes(p);
            rt_pool.erase(rt_pool.begin() + (long)i);
            t.used = 1;
            n_rt_pool_hits++;
            if (mk_noclear) return true;   /* (rt_clone: overwritten whole at once) */
            pre_op();
            clear_img(t.img, t.dsv != 0);
            post_op();
            return true;
        }
        t = Target();
        t.used = 1; t.depth = depth; t.w = w; t.h = h;
        int W = w * scale, H = h * scale;
        const VkImageUsageFlags XF = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        if (depth && zrov_ok) {
            /* the D32 values (z / 2^32) in an R32_SFLOAT colour image: rendered by loads, tested and
             * written by native draws through a storage view (nr_d3d11.cpp's zrov targets) */
            t.fmt = VK_FORMAT_R32_SFLOAT;
            if (!image_raw(&t.img, &t.al, W, H, t.fmt, XF | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_STORAGE_BIT, false))
                return false;
            t.view = view_make(t.img, t.fmt, VK_IMAGE_ASPECT_COLOR_BIT);
            t.uv = t.view;
        } else if (depth) {
            t.fmt = VK_FORMAT_D32_SFLOAT;
            t.dsv = 1;
            if (!image_raw(&t.img, &t.al, W, H, t.fmt, XF | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, false)) return false;
            t.view = view_make(t.img, t.fmt, VK_IMAGE_ASPECT_DEPTH_BIT);
        } else {
            t.fmt = VK_FORMAT_R8G8B8A8_UNORM;
            if (!image_raw(&t.img, &t.al, W, H, t.fmt, XF | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | (rov_ok ? VK_IMAGE_USAGE_STORAGE_BIT : 0u),
                           rov_ok))
                return false;
            t.view = view_make(t.img, t.fmt, VK_IMAGE_ASPECT_COLOR_BIT);
            if (rov_ok) t.uv = view_make(t.img, VK_FORMAT_R32_UINT, VK_IMAGE_ASPECT_COLOR_BIT);
        }
        if (!t.view) return false;
        clear_img(t.img, t.dsv != 0);
        post_op();
        return true;
    }

    void free_target(Target &t)
    {
        if (t.uv && t.uv != t.view) vkDestroyImageView(dev, t.uv, NULL);
        if (t.view) vkDestroyImageView(dev, t.view, NULL);
        if (t.img) vmaDestroyImage(vma, t.img, t.al);
        if (t.snap_view) vkDestroyImageView(dev, t.snap_view, NULL);
        if (t.snap) vmaDestroyImage(vma, t.snap, t.snap_al);
        t = Target();
    }
    void defer_target(Target &t)
    {
        Del d;
        d.i = t.img; d.a = t.al; d.v[0] = t.view; d.v[1] = t.uv != t.view ? t.uv : VK_NULL_HANDLE;
        if (d.i) defer(d);
        if (t.snap) {
            Del e;
            e.i = t.snap; e.a = t.snap_al; e.v[0] = t.snap_view;
            defer(e);
        }
        t = Target();
    }

    int rt_create(int depth, int w, int h) override
    {
        size_t i = 0;
        while (i < targets.size() && targets[i].used) i++;
        if (i == targets.size()) targets.push_back(Target());
        Target t;
        if (!make_target(t, depth, w, h)) { defer_target(t); return -1; }
        targets[i] = t;
        return (int)i;
    }

    void rt_clear(int id) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used) return;
        pre_op();
        clear_img(targets[id].img, targets[id].dsv != 0);
        post_op();
    }

    void rt_pool_free()
    {
        for (Target &t : rt_pool) defer_target(t);
        rt_pool.clear();
        rt_pool_bytes = 0;
    }
    void rt_destroy(int id) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used) return;
        if (in_rp && (rp.c == targets[id].view || rp.d == targets[id].view)) end_rp();
        if (rt_pool_on < 0) { const char *e = getenv("RG_GPU_RT_POOL"); rt_pool_on = !(e && e[0] == '0'); }
#if defined(_WIN64)
        if (rg_x64_va_tight(0) && !rt_pool.empty()) rt_pool_free(); if (rt_pool_on && targets[id].img && !destroying && !rg_x64_va_tight(0)) {
#else
#line 1857
        if (rt_pool_on && targets[id].img && !destroying) {
#endif
#line 1858
            if (rt_pool_cap < 0) { const char *e = getenv("RG_GPU_RT_POOL_MB"); rt_pool_cap = (e ? atoll(e) : 512) << 20; }
            int64_t add = rt_bytes(targets[id]);
            while (!rt_pool.empty() && (rt_pool_bytes + add > rt_pool_cap || rt_pool.size() >= 256)) {
                rt_pool_bytes -= rt_bytes(rt_pool.front());
                defer_target(rt_pool.front());
                rt_pool.erase(rt_pool.begin());
            }
            rt_pool_bytes += add;
            rt_pool.push_back(targets[id]);
            targets[id] = Target();
            return;
        }
        defer_target(targets[id]);
    }

    void copy_img(VkImage dst, int dx, int dy, VkImage src, int sx, int sy, int w, int h, bool depth, int site = __builtin_LINE())
    {
        if (w <= 0 || h <= 0) return;
        pre_op_at(site);
        VkImageCopy c = {};
        c.srcSubresource.aspectMask = c.dstSubresource.aspectMask = depth ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
        c.srcSubresource.layerCount = c.dstSubresource.layerCount = 1;
        c.srcOffset = { sx, sy, 0 };
        c.dstOffset = { dx, dy, 0 };
        c.extent = { (uint32_t)w, (uint32_t)h, 1 };
        vkCmdCopyImage(cb(), src, VK_IMAGE_LAYOUT_GENERAL, dst, VK_IMAGE_LAYOUT_GENERAL, 1, &c);
        post_op();
    }

    void rt_resize(int id, int w, int h) override
    {
        Target &o = targets[id];
        Target n;
        if (!make_target(n, o.depth, w, h)) { defer_target(n); return; }
        int cw = (o.w < w ? o.w : w) * scale, ch = (o.h < h ? o.h : h) * scale;
        copy_img(n.img, 0, 0, o.img, 0, 0, cw, ch, o.dsv != 0);
        if (in_rp && (rp.c == o.view || rp.d == o.view)) end_rp();
        defer_target(o);
        targets[id] = n;
    }

    void rt_load(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override
    {
        uint64_t q0 = prof ? pts() : ~0ull;
        rt_load_(id, bp, bw, psm, r);
        if (prof) pev_add(PC_LOAD, q0, (double)(r.x1 - r.x0) * (r.y1 - r.y0));
    }
    void rt_load_(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r)
    {
        Target &t = targets[id];
        slots_clear();
        uint32_t u[8][4] = {};
        u[0][0] = bp; u[0][1] = bw; u[0][2] = (uint32_t)psm; u[0][3] = (uint32_t)scale;
        set_ubo(0, u, sizeof u);
        set_buf(B_T + 0, mem.b, 0, VK_WHOLE_SIZE);
        int W = t.w * scale, H = t.h * scale;
        if (t.depth && !t.dsv) {
            GKey k = key0(prog(&sh_vs_quad, &sh_ps_load_depth_rt));
            k.cf = t.fmt;
            k.clamp = 1;
            quad(k, t.view, VK_NULL_HANDLE, W, H, W, H, r.x0 * scale, r.y0 * scale, r.x1 * scale, r.y1 * scale);
        } else if (t.depth) {
            GKey k = key0(prog(&sh_vs_quad, &sh_ps_load_depth));
            k.df = t.fmt;
            k.zt = 1; k.zw = 1; k.zf = VK_COMPARE_OP_ALWAYS;
            k.clamp = 1;
            quad(k, VK_NULL_HANDLE, t.view, W, H, W, H, r.x0 * scale, r.y0 * scale, r.x1 * scale, r.y1 * scale);
        } else {
            GKey k = key0(prog(&sh_vs_quad, &sh_ps_load_color));
            k.cf = t.fmt;
            k.clamp = 1;
            quad(k, t.view, VK_NULL_HANDLE, W, H, W, H, r.x0 * scale, r.y0 * scale, r.x1 * scale, r.y1 * scale);
        }
    }

    void rt_writeback(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override
    {
        uint64_t q0 = prof ? pts() : ~0ull;
        rt_writeback_(id, bp, bw, psm, r);
        if (prof) pev_add(PC_WB, q0, (double)(r.x1 - r.x0) * (r.y1 - r.y0));
    }
    void rt_writeback_(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r)
    {
        Target &t = targets[id];
        slots_clear();
        uint32_t u[8][4] = {};
        u[0][0] = bp; u[0][1] = bw; u[0][2] = (uint32_t)psm; u[0][3] = (uint32_t)scale;
        u[1][0] = (uint32_t)r.x0; u[1][1] = (uint32_t)r.y0;
        u[1][2] = (uint32_t)(r.x1 - r.x0); u[1][3] = (uint32_t)(r.y1 - r.y0);
        set_ubo(0, u, sizeof u);
        set_buf(B_U + 0, mem.b, 0, VK_WHOLE_SIZE);
        if (t.depth) {
            set_img(B_T + 1, t.view);
            dispatch(sh_cs_wb_depth, (uint32_t)(r.x1 - r.x0 + 7) / 8, (uint32_t)(r.y1 - r.y0 + 7) / 8, 1);
        } else {
            set_img(B_T + 0, t.view);
            dispatch(sh_cs_wb_color, (uint32_t)(r.x1 - r.x0 + 7) / 8, (uint32_t)(r.y1 - r.y0 + 7) / 8, 1);
        }
    }

    int reint_cs = -1;
    uint64_t n_reint_cs = 0;
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
        if (!scr.b && !buf_make(scr, GS_VRAM_BYTES, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 0))
            return false;
        if (reint_cs < 0) { const char *e = getenv("RG_NR_REINT_CS"); reint_cs = !(e && e[0] == '0'); }   /* (0: the pixel-shader loads) */
        pre_op();
        VkBufferCopy c = { 0, 0, GS_VRAM_BYTES };
        vkCmdCopyBuffer(cb(), mem.b, scr.b, 1, &c);
        post_op();
        int W = d.w * scale, H = d.h * scale;
        for (int py = 0; py < scale; py++)
            for (int px = 0; px < scale; px++) {
                slots_clear();
                uint32_t u[8][4] = {};
                u[0][0] = sbp; u[0][1] = sbw; u[0][2] = (uint32_t)spsm; u[0][3] = (uint32_t)scale;
                u[1][0] = (uint32_t)sr.x0; u[1][1] = (uint32_t)sr.y0;
                u[1][2] = (uint32_t)(sr.x1 - sr.x0); u[1][3] = (uint32_t)(sr.y1 - sr.y0);
                u[2][0] = (uint32_t)px; u[2][1] = (uint32_t)py; u[2][2] = 1;
                set_ubo(0, u, sizeof u);
                set_buf(B_U + 0, scr.b, 0, VK_WHOLE_SIZE);
                set_img(B_T + 0, s.view);
                dispatch(sh_cs_wb_color, (uint32_t)(sr.x1 - sr.x0 + 7) / 8, (uint32_t)(sr.y1 - sr.y0 + 7) / 8, 1);
                slots_clear();
                uint32_t v[8][4] = {};
                v[0][0] = dbp; v[0][1] = dbw; v[0][2] = (uint32_t)dpsm; v[0][3] = (uint32_t)scale;
                v[1][0] = (uint32_t)px; v[1][1] = (uint32_t)py; v[1][2] = 1;
                if (reint_cs && d.uv && d.uv != d.view) {
                    /* one thread per native pixel of dr (CS_load_phase, as nr_d3d11.cpp) */
                    v[1][2] = 0;
                    v[2][0] = (uint32_t)dr.x0; v[2][1] = (uint32_t)dr.y0;
                    v[2][2] = (uint32_t)(dr.x1 - dr.x0); v[2][3] = (uint32_t)(dr.y1 - dr.y0);
                    set_ubo(0, v, sizeof v);
                    set_buf(B_T + 0, scr.b, 0, VK_WHOLE_SIZE);
                    set_img(B_U + 0, d.uv);
                    dispatch(sh_cs_load_phase, (uint32_t)(dr.x1 - dr.x0 + 7) / 8, (uint32_t)(dr.y1 - dr.y0 + 7) / 8, 1);
                    n_reint_cs++;
                    continue;
                }
                set_ubo(0, v, sizeof v);
                set_buf(B_T + 0, scr.b, 0, VK_WHOLE_SIZE);
                GKey k = key0(prog(&sh_vs_quad, &sh_ps_load_color));
                k.cf = d.fmt;
                k.clamp = 1;
                quad(k, d.view, VK_NULL_HANDLE, W, H, W, H, dr.x0 * scale, dr.y0 * scale, dr.x1 * scale, dr.y1 * scale);
            }
        return true;
    }

    bool rt_copy(int dst, int dx, int dy, int src, const GpuRect &sr) override
    {
        if (dst == src || dst < 0 || src < 0 || (size_t)dst >= targets.size() || (size_t)src >= targets.size() ||
            !targets[dst].used || !targets[src].used)
            return false;
        Target &d = targets[dst], &s = targets[src];
        if (d.depth != s.depth || (d.depth && !zrov_ok)) return false;
        if (sr.x0 < 0 || sr.y0 < 0 || sr.x1 > s.w || sr.y1 > s.h || sr.x1 <= sr.x0 || sr.y1 <= sr.y0 || dx < 0 ||
            dy < 0 || dx + (sr.x1 - sr.x0) > d.w || dy + (sr.y1 - sr.y0) > d.h)
            return false;
        copy_img(d.img, dx * scale, dy * scale, s.img, sr.x0 * scale, sr.y0 * scale, (sr.x1 - sr.x0) * scale, (sr.y1 - sr.y0) * scale,
                 false);
        return true;
    }

    /* image rect -> packed RGBA8 rows (waits) */
    int read_img(VkImage img, int x, int y, int W, int H, uint32_t *out)
    {
        VkDeviceSize need = (VkDeviceSize)W * H * 4;
        if (out_rb.size < need) {
            buf_defer(out_rb);
            if (!buf_make(out_rb, need, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2)) return -1;
        }
        pre_op();
        VkBufferImageCopy c = {};
        c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        c.imageSubresource.layerCount = 1;
        c.imageOffset = { x, y, 0 };
        c.imageExtent = { (uint32_t)W, (uint32_t)H, 1 };
        vkCmdCopyImageToBuffer(cb(), img, VK_IMAGE_LAYOUT_GENERAL, out_rb.b, 1, &c);
        post_op();
        wait_serial(subs[ci].serial);
        buf_inval(out_rb);
        memcpy(out, out_rb.map, (size_t)need);
        return 0;
    }

    int rt_read(int id, const GpuRect &r, uint32_t *out) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used || targets[id].depth) return -1;
        int W = (r.x1 - r.x0) * scale, H = (r.y1 - r.y0) * scale;
        if (W <= 0 || H <= 0) return -1;
        return read_img(targets[id].img, r.x0 * scale, r.y0 * scale, W, H, out);
    }

    /* ======================================================== CLUT, transfers */
    void set_clut(const GpuClutCB &c) override
    {
        static_assert(sizeof(GpuClutCB) == 256 * 4, "GpuClutCB: 256 words");
        if (!clut_lazy) {
            pre_op();
            vkCmdUpdateBuffer(cb(), clut.b, 0, sizeof c, &c);
            post_op();
            return;
        }
        clut_pend.clear();   /* a whole CLUT replaces every update still waiting */
        ClutUp u;
        u.off = 0;
        u.n = 256;
        memcpy(u.w, &c, sizeof c);
        clut_pend.push_back(u);
    }
    /* $RG_VK_CLUT_LAZY=0: CLUT uploads end the rendering instance at once (the old path) */
    const bool clut_lazy = !(getenv("RG_VK_CLUT_LAZY") && getenv("RG_VK_CLUT_LAZY")[0] == '0');
    void set_clut_part(const GpuClutCB &c, const uint8_t *own) override
    {
        const uint32_t *w = &c.c[0][0];
        bool any = false;
        for (uint32_t i = 0; i < 256;) {
            if (own[i]) { i++; continue; }
            uint32_t e = i;
            while (e < 256 && !own[e]) e++;
            if (!clut_lazy) {
                if (!any) { pre_op(); any = true; }
                vkCmdUpdateBuffer(cb(), clut.b, i * 4u, (e - i) * 4u, w + i);
            } else {
                ClutUp u;
                u.off = i;
                u.n = e - i;
                memcpy(u.w, w + i, (e - i) * 4u);
                clut_pend.push_back(u);
            }
            i = e;
        }
        if (any) post_op();
    }
    bool clut_load_gpu(const uint32_t u[3][4]) override
    {
        slots_clear();
        uint32_t uu[8][4] = {};
        memcpy(uu, u, 3 * 16);
        set_ubo(0, uu, sizeof uu);
        set_buf(B_U + 0, mem.b, 0, VK_WHOLE_SIZE);
        set_tbuf(B_U + 1, clut.view);
        dispatch(sh_cs_clut, 4, 1, 1);
        return true;
    }
    bool mem_copy(const uint32_t u[3][4]) override
    {
        uint32_t n = u[1][1] * u[1][2];
        if (!n || n > (1u << 22)) return false;
        if (!l2l.b) {
            if (!buf_make(l2l, (VkDeviceSize)(1u << 22) * 4u, VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT, 0) || !buf_view(l2l)) {
                buf_free(l2l);
                return false;
            }
        }
        slots_clear();
        uint32_t uu[8][4] = {};
        memcpy(uu, u, 3 * 16);
        set_ubo(0, uu, sizeof uu);
        set_buf(B_U + 0, mem.b, 0, VK_WHOLE_SIZE);
        set_tbuf(B_U + 2, l2l.view);
        dispatch(sh_cs_l2l_read, (u[1][1] + 7) / 8, (u[1][2] + 7) / 8, 1);
        dispatch(sh_cs_l2l_write, (u[1][1] + 7) / 8, (u[1][2] + 7) / 8, 1);
        return true;
    }
    bool mem_xfer_batch(const uint8_t *bytes, uint32_t nbytes, const uint32_t *desc, uint32_t ndesc, uint32_t npx) override
    {
        if (!ndesc || !npx || nbytes > XFER_BYTES || ndesc > XFER_DESCS) return false;
        if (!xdesc.b && !buf_make(xdesc, XFER_DESCS * 32u, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 0))
            return false;
        uint32_t nb = (nbytes + 15u) & ~15u;
        RA ro = ring_alloc(nb ? nb : 16u, 16);
        if (!ro.p) return false;
        memcpy(ro.p, bytes, nbytes);
        if (nb > nbytes) memset(ro.p + nbytes, 0, nb - nbytes);
        RA rd = ring_put(desc, (VkDeviceSize)ndesc * 32u, 16);
        if (!rd.p) return false;
        pre_op();
        VkBufferCopy c0 = { ro.off, 0, nb ? nb : 16u };
        VkBufferCopy c1 = { rd.off, 0, (VkDeviceSize)ndesc * 32u };
        vkCmdCopyBuffer(cb(), ro.b, merge.b, 1, &c0);
        vkCmdCopyBuffer(cb(), rd.b, xdesc.b, 1, &c1);
        post_op();
        slots_clear();
        uint32_t uu[8][4] = {};
        uu[0][0] = ndesc;
        uu[0][1] = npx;
        set_ubo(0, uu, sizeof uu);
        set_buf(B_U + 0, mem.b, 0, VK_WHOLE_SIZE);
        set_buf(B_T + 2, merge.b, 0, VK_WHOLE_SIZE);
        set_buf(B_T + 3, xdesc.b, 0, VK_WHOLE_SIZE);
        uint32_t groups = (npx + 63u) / 64u;
        dispatch(sh_cs_xfer, groups < 32768u ? groups : 32768u, (groups + 32767u) / 32768u, 1);
        return true;
    }
    bool clut_read(GpuClutCB *out) override
    {
        pre_op();
        VkBufferCopy c = { 0, 0, sizeof(GpuClutCB) };
        vkCmdCopyBuffer(cb(), clut.b, clut_rb.b, 1, &c);
        post_op();
        wait_serial(subs[ci].serial);
        buf_inval(clut_rb);
        memcpy(out, clut_rb.map, sizeof *out);
        return true;
    }

    void draw(const GpuDraw &g) override { (void)g; }   /* native-only: no GS-exact draw path */

    /* ======================================================== native draws */
    bool nr_ok = false;
    int nr_zbias = -2, zrov_units = -2;
    struct RtAS { VkAccelerationStructureKHR as = VK_NULL_HANDLE; Buf buf; VkDeviceAddress addr = 0; };
    struct NrMeshBuf { Buf vb, ib, st; uint32_t nidx = 0; uint64_t used = 0; uint32_t vbytes = 0;
                       RtAS blas; int blas_state = 0; /* ray tracing: 0 none, 1 built, -1 refused */
                       int amin = -1; /* ray tracing: the smallest vertex alpha (nr_vtx.a), -1 not yet known */ };
    std::unordered_map<uint32_t, NrMeshBuf> nr_mesh;
    uint64_t nr_clock = 0;
    struct NrTex { uint32_t key[8]; GpuRect rect; int valid; int tw, th; uint64_t used; uint64_t h; Img img;
                   uint64_t rtgen; /* ray tracing: a number per decode (the alpha copy's key, rt_alpha) */
                   nremi::Tex *etex; /* (rt8) its content record (nr_emi.h), NULL until its texels are known */ };
    /* HD texture replacements (GpuNrDraw.rep, docs/TEXTURES.md; nr_d3d11.cpp nr_rep_get): one image
     * with its mip chain per NrRepImg id, least recently used evicted past $RG_TEXREP_GPU_MB */
    std::unordered_map<uint64_t, NrTex> nr_rep;
    size_t nr_rep_bytes = 0, nr_rep_budget = 0;
    VkSampler smp_rep[2][2][2] = {}, smp_rep_an[4][2][2] = {};
    NrTex *nr_rep_last = NULL;   /* (the draw samples it with the mip samplers) */
    /* staged uploads (nr_d3d11.cpp): at most nr_texrep_upload_budget() bytes per frame through the
     * ring, rows of the mip levels in order; drawn once every level is up.  id -> next (level, row) */
    std::unordered_map<uint64_t, std::pair<int, int>> nr_rep_prog;
    size_t rep_up_bytes = 0;   /* uploaded this frame */
    double rep_up_ms = 0;
    uint32_t rep_frame = 0;    /* (nr_texrep_frame: the field the counts are for) */
    void rep_frame_end()
    {
        if (rep_up_bytes) nr_texrep_upload(rep_up_ms, rep_up_bytes);
        rep_up_bytes = 0;
        rep_up_ms = 0;
    }
    void nr_rep_clear() override
    {
        for (auto &kv : nr_rep) img_defer(kv.second.img);
        nr_rep.clear();
        nr_rep_prog.clear();
        nr_rep_bytes = 0;
        nr_rep_last = NULL;
    }
    NrTex *nr_rep_get(const NrRepImg *im)
    {
        if (!nr_texrep_valid(im)) return NULL;   /* (a freed one: replayed draw after release / eviction) */
        if (nr_texrep_frame() != rep_frame) { rep_frame_end(); rep_frame = nr_texrep_frame(); }   /* (a new field: a new budget) */
        auto it = nr_rep.find(im->id);
        if (it == nr_rep.end()) {
            if (!im->px || im->levels < 1) return NULL;
            if (!nr_rep_budget) {
                const char *mb = getenv("RG_TEXREP_GPU_MB");
                nr_rep_budget = (size_t)(mb ? atol(mb) : (sizeof(void *) >= 8 ? 2048 : 512)) << 20;
            }
            while (nr_rep_bytes + im->bytes > nr_rep_budget && !nr_rep.empty()) {
                auto o = nr_rep.begin();
                for (auto j = nr_rep.begin(); j != nr_rep.end(); ++j) if (j->second.used < o->second.used) o = j;
                img_defer(o->second.img);
                nr_rep_bytes -= (size_t)o->second.h;
                nr_rep_prog.erase(o->first);
                nr_rep.erase(o);
            }
            size_t ub = nr_texrep_upload_budget();
            if (ub && rep_up_bytes >= ub) return NULL;   /* (this frame's uploads are done: the next frame) */
            auto t0 = std::chrono::steady_clock::now();
            NrTex t;
            memset(t.key, 0, sizeof t.key);
            t.rect = GpuRect{ 0, 0, im->w, im->h };
            t.valid = 1; t.tw = im->w; t.th = im->h; t.used = 0; t.h = im->bytes;
            t.etex = NULL;   /* (rt8's content record: none for a replacement; was left uninitialised) */
            t.img = Img();
            mk_levels = (uint32_t)im->levels;
            bool ok = img_make(t.img, im->w, im->h, VK_FORMAT_R8G8B8A8_UNORM,
                               VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | (rt_on ? VK_IMAGE_USAGE_TRANSFER_SRC_BIT : 0), false);
            mk_levels = 1;
            if (!ok) { img_free(t.img); return NULL; }
            if (!ub) {   /* (whole: the hdtex behaviour) */
                RA ra = ring_put(im->px, im->bytes, 16);
                if (!ra.p) { img_free(t.img); return NULL; }
                pre_op();
                VkBufferImageCopy c[NR_REP_MAX_LEVELS] = {};
                for (int l = 0; l < im->levels; l++) {
                    c[l].bufferOffset = ra.off + (VkDeviceSize)im->off[l] * 4u;
                    c[l].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                    c[l].imageSubresource.mipLevel = (uint32_t)l;
                    c[l].imageSubresource.layerCount = 1;
                    c[l].imageExtent = { (uint32_t)im->lw[l], (uint32_t)im->lh[l], 1 };
                }
                vkCmdCopyBufferToImage(cb(), ra.b, t.img.i, VK_IMAGE_LAYOUT_GENERAL, (uint32_t)im->levels, c);
                post_op();
                rep_up_bytes += im->bytes;
            } else {
                nr_rep_prog[im->id] = std::make_pair(0, 0);
            }
            rep_up_ms += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            t.rtgen = ++rt_tex_gen;
            nr_rep_bytes += im->bytes;
            it = nr_rep.emplace(im->id, t).first;
            if (!smp_rep[0][0][0]) {
                for (int i = 0; i < 24; i++) {
                    bool an = i >= 8;
                    int j = an ? i - 8 : i;
                    VkSamplerCreateInfo sn = { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
                    bool l = an || (j >> 2);
                    sn.magFilter = sn.minFilter = l ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
                    sn.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
                    sn.addressModeU = ((j >> 1) & 1) ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
                    sn.addressModeV = (j & 1) ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
                    sn.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
                    sn.maxLod = VK_LOD_CLAMP_NONE;
                    if (an) {
                        if (!aniso_ok) continue;
                        sn.anisotropyEnable = VK_TRUE;
                        sn.maxAnisotropy = (float)(2u << (j >> 2));
                        if (sn.maxAnisotropy > aniso_max) sn.maxAnisotropy = aniso_max;
                    }
                    VkSampler &dst = an ? smp_rep_an[j >> 2][(j >> 1) & 1][j & 1] : smp_rep[j >> 2][(j >> 1) & 1][j & 1];
                    if (vkCreateSampler(dev, &sn, NULL, &dst) != VK_SUCCESS) dst = VK_NULL_HANDLE;
                }
            }
        }
        auto pg = nr_rep_prog.find(im->id);
        if (pg != nr_rep_prog.end()) {
            size_t ub = nr_texrep_upload_budget();
            if (ub && rep_up_bytes >= ub) return NULL;
            auto t0 = std::chrono::steady_clock::now();
            int &lvl = pg->second.first, &row = pg->second.second;
            /* this frame's rows: one ring piece, one copy region per level touched */
            size_t left = ub ? ub - rep_up_bytes : (size_t)-1, total = 0;
            int l0 = lvl, r0 = row;
            {
                int l = lvl, r = row;
                while (l < im->levels && total < left) {
                    size_t rb = (size_t)im->lw[l] * 4u;
                    int rows = im->lh[l] - r;
                    if ((size_t)rows * rb > left - total) rows = (int)((left - total) / rb) > 0 ? (int)((left - total) / rb) : 1;
                    total += (size_t)rows * rb;
                    r += rows;
                    if (r >= im->lh[l]) { l++; r = 0; }
                }
                lvl = l;
                row = r;
            }
            RA ra = ring_alloc(total, 16);
            if (!ra.p) { lvl = l0; row = r0; return NULL; }
            VkBufferImageCopy c[NR_REP_MAX_LEVELS + 1] = {};
            int nc = 0;
            {
                int l = l0, r = r0;
                size_t at = 0;
                while (at < total && l < im->levels && nc <= NR_REP_MAX_LEVELS) {
                    size_t rb = (size_t)im->lw[l] * 4u;
                    int rows = im->lh[l] - r;
                    if ((size_t)rows * rb > total - at) rows = (int)((total - at) / rb);
                    memcpy(ra.p + at, im->px + im->off[l] + (size_t)r * im->lw[l], (size_t)rows * rb);
                    VkBufferImageCopy &cc = c[nc++];
                    cc.bufferOffset = ra.off + at;
                    cc.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                    cc.imageSubresource.mipLevel = (uint32_t)l;
                    cc.imageSubresource.layerCount = 1;
                    cc.imageOffset = { 0, r, 0 };
                    cc.imageExtent = { (uint32_t)im->lw[l], (uint32_t)rows, 1 };
                    at += (size_t)rows * rb;
                    r += rows;
                    if (r >= im->lh[l]) { l++; r = 0; }
                }
            }
            pre_op();
            vkCmdCopyBufferToImage(cb(), ra.b, it->second.img.i, VK_IMAGE_LAYOUT_GENERAL, (uint32_t)nc, c);
            post_op();
            rep_up_bytes += total;
            rep_up_ms += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            if (lvl < im->levels) return NULL;   /* (the decoded texture until every level is up) */
            nr_rep_prog.erase(pg);
            it->second.rtgen = ++rt_tex_gen;   /* (complete: a new number for the ray-tracing copies) */
        }
        it->second.used = ++nr_clock;
        nr_rep_last = &it->second;
        return &it->second;
    }
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

    /* pre-warmed meshes (another thread): device buffers + a filled staging buffer, copied by
     * the render thread at the lookup that takes them */
    std::mutex pre_mx;
    std::vector<std::pair<uint32_t, NrMeshBuf>> pre;
    std::atomic<int> pre_n{0};
    bool mesh_bufs(NrMeshBuf &b, const gpu_nr_mesh &m)
    {
        uint32_t vbytes = m.nvtx * 28, ibytes = m.nidx * 4;
        /* ray tracing: the mesh buffers are also the BLAS build input (docs/RAYTRACING.md) */
        const VkBufferUsageFlags rtu = rt_on ? VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
                                                   VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR : 0;
        if (!buf_make(b.vb, vbytes, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | rtu, 0)) return false;
        if (!buf_make(b.ib, ibytes, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | rtu, 0)) { buf_free(b.vb); return false; }
        b.nidx = m.nidx;
        b.vbytes = vbytes;
        return true;
    }
    void nr_mesh_prewarm(const gpu_nr_mesh &m) override
    {
        if (!m.nvtx || !m.nidx || m.stride != 28) return;
        NrMeshBuf b;
        if (!mesh_bufs(b, m)) return;
        uint32_t vbytes = m.nvtx * 28, ibytes = m.nidx * 4;
        if (!buf_make(b.st, (VkDeviceSize)vbytes + ibytes, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, 1)) {
            buf_free(b.vb); buf_free(b.ib);
            return;
        }
        memcpy(b.st.map, m.vtx, vbytes);
        memcpy(b.st.map + vbytes, m.idx, ibytes);
        vmaFlushAllocation(vma, b.st.a, 0, VK_WHOLE_SIZE);
        std::lock_guard<std::mutex> lk(pre_mx);
        pre.push_back(std::make_pair(m.id, b));
        pre_n.store((int)pre.size());
    }
    void mesh_upload(NrMeshBuf &b, VkBuffer src, VkDeviceSize off, uint32_t ibytes)
    {
        pre_op();
        VkBufferCopy cv = { off, 0, b.vbytes };
        VkBufferCopy ci_ = { off + b.vbytes, 0, ibytes };
        vkCmdCopyBuffer(cb(), src, b.vb.b, 1, &cv);
        vkCmdCopyBuffer(cb(), src, b.ib.b, 1, &ci_);
        post_op();
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
                if (o != nr_mesh.end()) {
                    buf_free(e.second.vb); buf_free(e.second.ib); buf_free(e.second.st);
                    continue;
                }
                mesh_upload(e.second, e.second.st.b, 0, e.second.nidx * 4);
                buf_defer(e.second.st);
                e.second.used = nr_clock;
                NrMeshBuf &nb = (nr_mesh[e.first] = e.second);
                n_nr_mesh_pre++;
                if (e.first == m.id) hit = &nb;
            }
            if (hit) return hit;
        }
        if (!m.nvtx || !m.nidx || m.stride != 28) return NULL;
        if (nr_mesh.size() >= 8192) {
            std::vector<std::pair<uint64_t, uint32_t>> u;
            for (auto &e : nr_mesh) u.push_back(std::make_pair(e.second.used, e.first));
            std::sort(u.begin(), u.end());
            for (size_t i = 0; i < u.size() / 8; i++) {
                NrMeshBuf &b = nr_mesh[u[i].second];
                buf_defer(b.vb); buf_defer(b.ib);
                if (b.blas.as) { rt_as_defer(b.blas); rt_tlas_stale = true; }   /* the TLAS may name it: unused until rebuilt */
                nr_mesh.erase(u[i].second);
            }
        }
        NrMeshBuf b;
        if (!mesh_bufs(b, m)) return NULL;
        uint32_t ibytes = m.nidx * 4;
        RA ra = ring_alloc((VkDeviceSize)b.vbytes + ibytes, 16);
        if (!ra.p) { buf_free(b.vb); buf_free(b.ib); return NULL; }
        memcpy(ra.p, m.vtx, b.vbytes);
        memcpy(ra.p + b.vbytes, m.idx, ibytes);
        mesh_upload(b, ra.b, ra.off, ibytes);
        b.used = nr_clock;
        n_nr_mesh++;
        return &(nr_mesh[m.id] = b);
    }

    bool nr_tex_cached(const uint32_t *key, const GpuRect &rc) override { return nr_find(key, rc, nr_hash(key, rc)) != NULL; }

    int rt_clone(int src) override
    {
        if (src < 0 || (size_t)src >= targets.size() || !targets[src].used) return -1;
        int depth = targets[src].depth, w = targets[src].w, h = targets[src].h;
        mk_noclear = true;
        int id = rt_create(depth, w, h);
        mk_noclear = false;
        if (id < 0) return -1;
        copy_img(targets[id].img, 0, 0, targets[src].img, 0, 0, w * scale, h * scale, targets[src].dsv != 0);
        return id;
    }
    int rt_clone_rect(int src, const GpuRect &r) override
    {
        if (src < 0 || (size_t)src >= targets.size() || !targets[src].used) return -1;
        int depth = targets[src].depth, sw = targets[src].w, sh = targets[src].h;
        if (r.x0 < 0 || r.y0 < 0 || r.x1 > sw || r.y1 > sh || r.x1 <= r.x0 || r.y1 <= r.y0) return -1;
        mk_noclear = true;
        int id = rt_create(depth, r.x1 - r.x0, r.y1 - r.y0);
        mk_noclear = false;
        if (id < 0) return -1;
        copy_img(targets[id].img, 0, 0, targets[src].img, r.x0 * scale, r.y0 * scale, (r.x1 - r.x0) * scale, (r.y1 - r.y0) * scale,
                 targets[src].dsv != 0);
        return id;
    }
    bool rt_put(int dst, int src) override
    {
        if (dst == src || dst < 0 || src < 0 || (size_t)dst >= targets.size() || (size_t)src >= targets.size() ||
            !targets[dst].used || !targets[src].used)
            return false;
        const Target &d = targets[dst], &s = targets[src];
        if (d.depth != s.depth || d.w != s.w || d.h != s.h) return false;
        copy_img(d.img, 0, 0, s.img, 0, 0, s.w * scale, s.h * scale, s.dsv != 0);
        return true;
    }

    /* ======================================================== (rt8) emissive surfaces (nr_emi.h) */
    nremi::Emi emi;
    struct EmiRb { NrTex *t; uint64_t h; Buf b; uint64_t serial; int w, hh; };
    std::vector<EmiRb> emi_rb;   /* texel readbacks in flight */
    uint64_t emi_n_rb = 0, emi_n_cpu = 0;
    /* a decoded texture's texels to the module: the core's CPU decode now, else a readback of the
     * decoded image (the census waits for it; otherwise it is taken when done, emi_poll) */
    void emi_capture(NrTex *e, const uint32_t *cpu)
    {
        if (cpu) { emi_n_cpu++; emi_set(e, cpu); return; }
        EmiRb r;
        r.t = e; r.h = e->h; r.w = e->tw; r.hh = e->th;
        if (emi_rb.size() >= 256 || !buf_make(r.b, (VkDeviceSize)r.w * r.hh * 4, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2)) return;
        pre_op();
        VkBufferImageCopy c = {};
        c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        c.imageSubresource.layerCount = 1;
        c.imageExtent = { (uint32_t)r.w, (uint32_t)r.hh, 1 };
        vkCmdCopyImageToBuffer(cb(), e->img.i, VK_IMAGE_LAYOUT_GENERAL, r.b.b, 1, &c);
        post_op();
        r.serial = subs[ci].serial;
        emi_n_rb++;
        if (emi.census) {
            wait_serial(r.serial);
            emi_take(r);
            return;
        }
        emi_rb.push_back(r);
    }
    void emi_take(EmiRb &r)
    {
        buf_inval(r.b);
        if (r.t->valid && r.t->h == r.h && r.t->tw == r.w && r.t->th == r.hh) emi_set(r.t, (const uint32_t *)r.b.map);
        buf_defer(r.b);
    }
    void emi_poll()
    {
        for (size_t i = 0; i < emi_rb.size();) {
            if (!rt_serial_done(emi_rb[i].serial)) { i++; continue; }
            emi_take(emi_rb[i]);
            emi_rb[i] = emi_rb.back();
            emi_rb.pop_back();
        }
    }
    void emi_set(NrTex *e, const uint32_t *px)
    {
        e->etex = emi.texels(px, e->tw, e->th);
        {
            /* (rt9) the original's row travels to its HD replacement by the texture's name (nr_emi.h "HD packs") */
            char nm[64];
            if (e->etex && nr_texrep_on() && nr_texrep_key_name(e->key, nm, sizeof nm)) emi.learn_name(e->etex, nm);
        }
        static std::vector<uint32_t> ov;
        if (e->etex && emi.overlay_px(*e->etex, px, ov)) {
            /* the debug overlay: the tagged texture's emitting texels magenta, in the cached copy */
            RA ra = ring_put(ov.data(), ov.size() * 4, 16);
            if (!ra.p) return;
            pre_op();
            VkBufferImageCopy c = {};
            c.bufferOffset = ra.off;
            c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            c.imageSubresource.layerCount = 1;
            c.imageExtent = { (uint32_t)e->tw, (uint32_t)e->th, 1 };
            vkCmdCopyBufferToImage(cb(), ra.b, e->img.i, VK_IMAGE_LAYOUT_GENERAL, 1, &c);
            post_op();
        }
    }
    /* a draw: the census row; with emissive lighting a tagged draw's lights (nr_emi.h) */
    float emi_w2s[4][4] = {}, emi_cam[3] = {};
    bool emi_cam_ok = false;
    uint64_t emi_cam_frame = ~0ull;
    void emi_draw(const GpuNrDraw &g, const gpu_nr_draw *d, NrTex *tx)
    {
        if (!emi_rb.empty()) emi_poll();
        uint32_t var = 0;
        memcpy(&var, &g.cb[22][0], 4);
        /* the frame's camera: world -> GS screen of its first mesh draw with rows (as rt_vp_take) */
        if (!g.im && d && d->rt_ok == GPU_NR_RT_MAGIC && emi_cam_frame != emi.frame && !(var & (nremi::V_ZSCALE | nremi::V_SKIN)) &&
            g.rt_w >= 512) {
            if (nremi::w2s_of(d->cb, d->rt, emi_w2s)) {
                memcpy(emi_cam, d->rt[7], sizeof emi_cam);
                emi_cam_ok = true;
                emi_cam_frame = emi.frame;
            }
        }
        /* (rt8) a newer game frame: the lights collected so far (the frame before) become the list */
        if (emi.mode && rt_on && !g.im && d && d->rt_ok == GPU_NR_RT_MAGIC && d->rt_frame &&
            (!emi_lframe || (int32_t)(d->rt_frame - emi_lframe) > 0)) {
            if (emi_lframe) emi_upload();
            emi_lframe = d->rt_frame;
        }
        if (emi.census && !g.im && d && d->rt_ok == GPU_NR_RT_MAGIC && d->rt_frame) emi.frame = d->rt_frame;   /* (census frames: game frames) */
        /* (rt9) an HD replacement: its record by name / its _e map (nr_emi.h rep_tex) */
        if (g.rep && tx && tx == nr_rep_last && emi.mode && g.tme && g.tex_rt < 0) tx->etex = emi.rep_tex(g.rep);
        if (!g.tme || g.tex_rt >= 0 || !tx || !tx->etex) return;
        const nremi::Tex *t = tx->etex;
        if (emi.mode && rt_on && t->row && g.rt_w >= 512 && !rt_pass_on && !rt_prepass) {
            if (!g.im && d && d->rt_ok == GPU_NR_RT_MAGIC && d->rt_frame && g.depth_rt >= 0)
                emi.mesh_draw(*t, g.cb, d->rt, var, d->mesh.vtx, d->mesh.nvtx, d->mesh.idx, d->mesh.nidx, d->mesh.id, g.clamp_u != 0,
                              g.clamp_v != 0, emi_lframe);
            else if (g.im && emi_cam_ok)
                emi.im_draw(*t, (const uint32_t *)g.im, g.nim, emi_w2s, 1.0f);
        }
        float wp[3];
        const float *wpp = NULL;
        if (g.im && emi.census && emi_cam_ok && g.nim) {
            float x = 0, y = 0;
            double z = 0;
            for (uint32_t i = 0; i < g.nim; i++) { x += g.im[i].x; y += g.im[i].y; z += g.im[i].z; }
            if (emi.unproject(emi_w2s, x / g.nim, y / g.nim, (float)(z / g.nim), wp)) wpp = wp;
        }
        if (emi.census)
            emi.census_draw(t, g.im != NULL, g.depth_rt >= 0 && g.zfunc >= GZ_GEQUAL, g.abe, g.alpha_abcd, g.zwrite, var, g.cb, d ? d->mesh.vtx : NULL,
                            g.im ? g.nim : (d ? d->mesh.nvtx : 0), d ? d->mesh.id : 0, d ? d->mesh.nidx : 0, (const float *)g.im, wpp);
    }
    /* (rt8) the light list: device buffer (device address, transfer dst), written in the command
     * stream (vkCmdUpdateBuffer outside a rendering instance), so draws before see the old list */
    Buf emi_lbuf;
    VkDeviceAddress emi_laddr = 0;
    uint32_t emi_ln = 0, emi_lframe = 0;
    bool emi_self = false, emi_dbg = false;
    int emi_max = -1;
    /* (rt9) the lights whose reach meets a draw's world box (bit i = light i of the list in force); all
     * of them for posed characters (their bones move the vertices) or with $RG_EMI_CULL=0.  The mesh's
     * object-space box is kept per mesh id (raw int16 positions; x the draw's position scale) */
    std::vector<nremi::Light> emi_lcpu;   /* the list in force (emi_upload) */
    std::unordered_map<uint32_t, std::array<int16_t, 6>> emi_mbox;
    int emi_cull = -1, emi_quad = -1;
    uint64_t emi_st[3] = {};   /* draws with lights: masks built, lights kept, lights culled */
    uint64_t emi_mask(const gpu_nr_draw *d)
    {
        const uint64_t all = emi_ln >= 64 ? ~0ull : ((1ull << emi_ln) - 1ull);
        if (emi_cull < 0) { const char *e = getenv("RG_EMI_CULL"); emi_cull = !(e && e[0] == '0'); }
        if (!emi_cull || rt_rchr || d->nbones_rows || !d->mesh.vtx || d->mesh.stride != 28 || !d->mesh.nvtx ||
            emi_lcpu.size() != emi_ln) return all;
        auto it = emi_mbox.find(d->mesh.id);
        if (it == emi_mbox.end()) {
            std::array<int16_t, 6> b = { { 32767, 32767, 32767, -32768, -32768, -32768 } };
            const int16_t *v = (const int16_t *)d->mesh.vtx;
            for (uint32_t i = 0; i < d->mesh.nvtx; i++)
                for (int k = 0; k < 3; k++) { b[k] = std::min(b[k], v[14 * i + k]); b[3 + k] = std::max(b[3 + k], v[14 * i + k]); }
            if (emi_mbox.size() > 65536) emi_mbox.clear();
            it = emi_mbox.emplace(d->mesh.id, b).first;
        }
        float lo[3] = { 1e30f, 1e30f, 1e30f }, hi[3] = { -1e30f, -1e30f, -1e30f };
        for (int c = 0; c < 8; c++) {
            float p[3];
            for (int k = 0; k < 3; k++) p[k] = it->second[(c >> k) & 1 ? 3 + k : k] / 32768.0f * d->cb[4][k];
            for (int k = 0; k < 3; k++) {
                const float w = d->rt[0][k] * p[0] + d->rt[1][k] * p[1] + d->rt[2][k] * p[2] + d->rt[3][k];
                lo[k] = std::min(lo[k], w); hi[k] = std::max(hi[k], w);
            }
        }
        if (!(hi[0] >= lo[0] && hi[1] >= lo[1] && hi[2] >= lo[2])) return all;
        uint64_t m = 0;
        for (uint32_t i = 0; i < emi_ln && i < 64; i++) {
            const nremi::Light &L = emi_lcpu[i];
            float d2 = 0.0f;
            for (int k = 0; k < 3; k++) {
                const float e = L.p[k] < lo[k] ? lo[k] - L.p[k] : L.p[k] > hi[k] ? L.p[k] - hi[k] : 0.0f;
                d2 += e * e;
            }
            if (d2 < L.range * L.range) m |= 1ull << i;
        }
        emi_st[0]++;
        emi_st[1] += (uint64_t)__builtin_popcountll(m);
        emi_st[2] += (uint64_t)emi_ln - (uint64_t)__builtin_popcountll(m);
        return m;
    }
    void emi_upload()
    {
        if (emi_max < 0) {
            const char *e = getenv("RG_EMI_MAX");
            emi_max = e && *e ? atoi(e) : 48;
            if (emi_max > 256) emi_max = 256;
            emi_dbg = rt_dbg || ((e = getenv("RG_EMI_DBG")) && e[0] == '1');
        }
        std::vector<nremi::Light> &L = emi.frame_lights(emi_lframe, emi_cam);
        std::sort(L.begin(), L.end(), [](const nremi::Light &a, const nremi::Light &b) { return a.imp > b.imp; });
        if ((int)L.size() > emi_max) L.resize((size_t)emi_max);
        emi.n_light_frames++;
        emi.n_lights += L.size();
        emi_lcpu = L;   /* (rt9: emi_mask's copy) */
        if (L.empty()) { emi_ln = 0; return; }
        if (!emi_lbuf.b) {
            if (!buf_make(emi_lbuf, 256 * 32, VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                                  VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 0)) { emi.mode = 0; emi_ln = 0; return; }
            emi_laddr = rt_addr(emi_lbuf.b);
        }
        float w[256 * 8];
        for (size_t i = 0; i < L.size(); i++) {
            float *q = w + 8 * i;
            q[0] = L[i].p[0]; q[1] = L[i].p[1]; q[2] = L[i].p[2]; q[3] = L[i].r;
            q[4] = L[i].c[0]; q[5] = L[i].c[1]; q[6] = L[i].c[2]; q[7] = L[i].range;
        }
        pre_op();
        vkCmdUpdateBuffer(cb(), emi_lbuf.b, 0, (VkDeviceSize)L.size() * 32, w);
        rt_barrier();
        post_op();
        emi_ln = (uint32_t)L.size();
    }
    void emi_exit()
    {
        if (!emi.any()) return;
        buf_free(emi_lbuf);
        for (EmiRb &r : emi_rb) buf_free(r.b);
        emi_rb.clear();
        emi.census_write();
        fprintf(stderr, "rg emi: mode %d%s%s, %llu textures (%llu tagged; %llu read back, %llu CPU-decoded), %llu tagged draws, "
                        "%llu lights over %llu frames (%llu mesh clusters, %llu sprite lights, %llu too dim); HD replacements %llu (%llu emit, %llu by an _e map; %llu rows by name from originals); light culling %d (%llu draws, %.1f lights kept, %.1f culled a draw), quad %d\n",
                emi.mode, emi.overlay ? " + overlay" : "", emi.census ? " + census" : "", (unsigned long long)emi.n_tex,
                (unsigned long long)emi.n_tagged, (unsigned long long)emi_n_rb, (unsigned long long)emi_n_cpu,
                (unsigned long long)emi.n_draw_tagged, (unsigned long long)emi.n_lights, (unsigned long long)emi.n_light_frames,
                (unsigned long long)emi.n_mesh_clu, (unsigned long long)emi.n_im_lights, (unsigned long long)emi.n_dropped,
                (unsigned long long)emi.n_rep, (unsigned long long)emi.n_rep_tagged, (unsigned long long)emi.n_rep_emap, (unsigned long long)emi.n_bridge,
                emi_cull, (unsigned long long)emi_st[0], emi_st[0] ? (double)emi_st[1] / emi_st[0] : 0.0, emi_st[0] ? (double)emi_st[2] / emi_st[0] : 0.0, emi_quad);
    }

    NrTex *nr_tex_get(const GpuNrDraw &g)
    {
        if (g.rep) {
            if (NrTex *t = nr_rep_get(g.rep)) return t;   /* (else the decoded texture) */
        }
        const GpuRect &rc = g.dec_rect;
        nr_clock++;
        uint64_t hk = nr_hash(g.dec_key, rc);
        if (NrTex *f = nr_find(g.dec_key, rc, hk)) {
            f->used = nr_clock;
            return f;
        }
        if (g.tex_cached_only) return NULL;
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
#if defined(_WIN64)
        if (nr_tex.size() < NR_TEX_MAX && nr_tex_bytes + need <= nr_tex_budget && (nr_tex.empty() || !rg_x64_va_tight(need))) {
#else
#line 2355
        if (nr_tex.size() < NR_TEX_MAX && nr_tex_bytes + need <= nr_tex_budget) {
#endif
#line 2356
            nr_tex.push_back(NrTex());
            e = &nr_tex.back();
            memset(e->key, 0, sizeof e->key);
            e->rect = GpuRect{ 0, 0, 0, 0 };
            e->valid = 0; e->tw = e->th = 0; e->used = 0; e->h = 0;
            e->img = Img();
            e->rtgen = 0;
        } else {
            NrTex *any = NULL, *same = NULL;
            for (NrTex &c : nr_tex) {
                if (c.tw == w && c.th == h && (!same || c.used < same->used)) same = &c;
                if (!any || c.used < any->used) any = &c;
            }
            e = (same && (nr_clock - same->used) * 4 >= (nr_clock - any->used) * 3) ? same : any;
            if (e->valid) nr_map.erase(e->h);
            if (e->tw != w || e->th != h) {
                if (e->img.i) nr_tex_bytes -= (size_t)e->tw * e->th * 4;
                img_defer(e->img);
                e->tw = e->th = 0;
            } else if (e->img.i) {
                /* reused in place: earlier draws sampling it must be done before the new texels land */
                end_rp();
            }
        }
        if (!e->img.i) {
            if (!img_make(e->img, w, h, VK_FORMAT_R8G8B8A8_UNORM,
                          VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                              (rt_on ? VK_IMAGE_USAGE_TRANSFER_SRC_BIT : 0), true)) {   /* RT2b: rt_alpha copies it */
                img_free(e->img);
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
            RA ra = ring_put(g.dec_rgba, need, 16);
            if (!ra.p) return NULL;
            pre_op();
            VkBufferImageCopy c = {};
            c.bufferOffset = ra.off;
            c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            c.imageSubresource.layerCount = 1;
            c.imageExtent = { (uint32_t)w, (uint32_t)h, 1 };
            vkCmdCopyBufferToImage(cb(), ra.b, e->img.i, VK_IMAGE_LAYOUT_GENERAL, 1, &c);
            post_op();
        } else {
            GpuDrawCB c = g.dec_cb;
            c.d[3][3] = 0;
            c.d[10][2] = (uint32_t)rc.x0 | ((uint32_t)rc.y0 << 16);
            c.d[10][3] = (uint32_t)rc.x1 | ((uint32_t)rc.y1 << 16);
            slots_clear();
            set_ubo(0, &c, sizeof c);
            set_buf(B_T + 0, mem.b, 0, VK_WHOLE_SIZE);
            set_tbuf(B_T + 5, clut.view);
            set_img(B_U + 0, e->img.uv);
            dispatch(sh_cs_decode, (uint32_t)(w + 7) / 8, (uint32_t)(h + 7) / 8, 1);
        }
        memcpy(e->key, g.dec_key, sizeof e->key);
        e->rect = rc;
        e->valid = 1;
        e->rtgen = ++rt_tex_gen;
        e->used = nr_clock;
        n_nr_tex++;
        e->etex = NULL;
        if (emi.any()) emi_capture(e, g.dec_rgba);   /* (rt8) */
        return e;
    }

    /* GS blend ((A - B) * C >> 7) + D as dual-source blending (nr_d3d11.cpp nr_blend) */
    void nr_blend(GKey &k, int abe, uint32_t abcd, uint32_t cmask)
    {
        k.cmask = (uint8_t)(cmask & 15u);
        k.blend = 0;
        k.sb = VK_BLEND_FACTOR_ONE; k.db = VK_BLEND_FACTOR_ZERO; k.op = VK_BLEND_OP_ADD;
        if (!abe) return;
        int A = (int)(abcd & 3), B = (int)((abcd >> 2) & 3), D = (int)((abcd >> 6) & 3);
        int csa = D == 0, csb = (A == 0) - (B == 0), cda = D == 1, cdb = (A == 1) - (B == 1);
        auto fac = [&](int a, int bb, bool *neg) -> VkBlendFactor {
            *neg = false;
            if (a == 0 && bb == 0) return VK_BLEND_FACTOR_ZERO;
            if (a == 1 && bb == 0) return VK_BLEND_FACTOR_ONE;
            if (a == 0 && bb == 1) return VK_BLEND_FACTOR_SRC1_ALPHA;
            if (a == 1 && bb == -1) return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
            if (a == 0 && bb == -1) { *neg = true; return VK_BLEND_FACTOR_SRC1_ALPHA; }
            n_nr_blend_approx++;
            return VK_BLEND_FACTOR_ONE;
        };
        bool ns, nd;
        k.blend = 1;
        k.sb = (uint8_t)fac(csa, csb, &ns);
        k.db = (uint8_t)fac(cda, cdb, &nd);
        k.op = (uint8_t)(ns && !nd ? VK_BLEND_OP_REVERSE_SUBTRACT : nd && !ns ? VK_BLEND_OP_SUBTRACT : VK_BLEND_OP_ADD);
        if (ns && nd) n_nr_blend_approx++;
    }

    void ensure_snapshot(Target &t)
    {
        if (t.snap) return;
        if (!image_raw(&t.snap, &t.snap_al, t.w * scale, t.h * scale, t.fmt,
                       VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, false))
            return;
        t.snap_view = view_make(t.snap, t.fmt, VK_IMAGE_ASPECT_COLOR_BIT);
    }
    void snapshot_rect(Target &t, const GpuRect &r)
    {
        ensure_snapshot(t);
        int x0 = r.x0 < 0 ? 0 : r.x0, y0 = r.y0 < 0 ? 0 : r.y0;
        int x1 = r.x1 > t.w ? t.w : r.x1, y1 = r.y1 > t.h ? t.h : r.y1;
        if (x1 > x0 && y1 > y0 && t.snap)
            copy_img(t.snap, x0 * scale, y0 * scale, t.img, x0 * scale, y0 * scale, (x1 - x0) * scale, (y1 - y0) * scale, false);
    }

    /* ======================================================== ray tracing (docs/RAYTRACING.md)
     * RT1 spike: graphics.raytracing on a device with VK_KHR_acceleration_structure +
     * VK_KHR_ray_query.  Opaque, rigid native meshes drawn into a frame-sized target are the casters:
     * one BLAS per mesh, built from its own vertex / index buffers (int16 positions as
     * R16G16B16A16_SNORM), cached with the mesh; one TLAS instance per (mesh, object matrix), the
     * transform = object matrix x position scale.  The instances a frame draws are collected by
     * nr_draw and the TLAS is rebuilt when the first draw of a newer record frame arrives
     * (rt_frame): draws read the TLAS of the frame before (static geometry: exact).  Receivers
     * draw through VS_nr_rt / PS_nr_rt: shadow rays to the sun.  RT2: alpha-tested casters cut out by
     * their texture's alpha in the ray query's candidate loop (RT2b), the sun from the area light
     * set, the sticky set of culled casters (RT2a), soft penumbra (several rays in the light's cone). */
    bool rt_on = false;
    int rt_dbg = 0;
    VkDeviceSize rt_scratch_align = 256, rt_scr_off = 0;
    RtAS rt_tlas;
    uint32_t rt_tlas_cap = 0;
    bool rt_tlas_stale = false;
    Buf rt_scratch, rt_ibuf;
    /* a caster instance: the mesh, its object matrix x position scale and (RT2b) the alpha-tested
     * material: tgen = the texture's decode (rt_alpha key, 0 = opaque), mfl = ATST | AREF << 8 |
     * TFX << 16 | VCOL << 19 | clamp U << 20 | clamp V << 21 | bilinear << 23, uvs = UV scale xy +
     * scroll offset zw, ma = the material alpha, mc = its clamp (VS_nr: c = min(c, R[8])).  Zeroed
     * whole before filling: the key is a hash of the bytes */
    struct RtInst { uint32_t mesh; float m[12]; uint32_t mfl; uint64_t tgen; float uvs[4]; float ma, mc, vamin, pad; uint64_t rgen; uint32_t rfl, mcol; };   /* (rt5: rgen / rfl / mcol: the reflection hit's material) */
    std::vector<RtInst> rt_inst;
    std::vector<uint64_t> rt_keys;   /* rt_inst's keys */
    std::unordered_set<uint64_t> rt_seen;
    /* RT2b: the material table (64 bytes per TLAS instance, read through its device address by
     * the candidate loop; instanceCustomIndex = the row) and the alpha copies of the textures of
     * alpha-tested casters (RGBA8 texels, by NrTex::rtgen; freed when no instance names them) */
    Buf rt_mbuf;
    VkDeviceAddress rt_mbuf_addr = 0;
    uint64_t rt_tex_gen = 0;
    /* rb: a host read-back copy, scanned once its submission completed (serial): amin = the
     * smallest texel alpha; a material whose alpha test every texel passes is opaque */
    struct RtAlpha { Buf b, rb; uint32_t w = 0, h = 0; uint64_t ref = 0, serial = 0; VkDeviceAddress addr = 0; int amin = -1; };
    std::unordered_map<uint64_t, RtAlpha> rt_alpha;
    /* RT2a: the sticky set: casters kept after the game stops drawing them (culled off screen,
     * behind the camera), by key; only instances drawn in at least two frames at the same
     * transform (static geometry: a moving object's transforms are each seen once), aged out after
     * rt_stick_max frames unseen, cleared when a frame's casters are mostly new (a map change) */
    struct RtStick { RtInst in; uint64_t last = 0; uint32_t nseen = 0; };
    std::unordered_map<uint64_t, RtStick> rt_stick;
    /* RT2c (docs/RAYTRACING.md "Characters"): skinned casters (the composited characters' Z-scale
     * parts and directly drawn skinned meshes).  Their vertices are posed on the CPU with VS_nr's
     * math (decode x scale, the bones, the object matrix: world space, before the composite's
     * offscreen projection) at draw time; rt_frame uploads them into a per-(mesh, occurrence)
     * float3 buffer and builds its BLAS (identity instance transform), refits it while the same
     * mesh keeps the slot (topology fixed per mesh), rebuilt every RT_DYN_REBUILD frames.  Masks:
     * 4 opaque, 8 cut-out (as 1 / 2 for the map). */
    enum { RT_DYN_REBUILD = 16, RT_DYN_AGE = 90 };
    struct RtDynPend { RtInst in; size_t off; uint32_t nv; };
    std::vector<RtDynPend> rt_dynp;
    std::vector<float> rt_dynpos;
    struct RtDyn { RtAS blas; Buf vb; uint32_t nv = 0, nt = 0, mesh = 0, nbuilt = 0; uint64_t last = 0; float pc[3] = {}, pd[3] = {}; uint64_t pfr = 0;
                   std::vector<float> pp, ps; uint64_t vfr = 0; };   /* (rt7) the last frame's posed vertices and their step */
    /* (rt4) a game frame's TLAS holds the characters of the frame before (casters are collected
     * while a frame draws): each posed part is moved on by its own last step (bounding-box centre,
     * frame to frame) so its shadow does not trail by a game frame.  Steps longer than rt_xmax
     * units (cuts, warps) are not extrapolated.  $RG_RT_EXTRAP=0: off (rt3), =N: rt_xmax N */
    float rt_xmax = 40.0f;
    /* (rt7) the pose too: each vertex of a posed part moves on by its own last step (frame to frame),
     * so a limb's swing is predicted as well as the part's travel (reflections of the characters on the
     * map's metal, and their shadows).  Only when the part's whole step is under rt_xmax (as rt4);
     * a vertex step is clamped to rt_xmax.  $RG_RT_XVERT=0: the part's step only (rt4) */
    int rt_xvert = -1;
    std::unordered_map<uint64_t, RtDyn> rt_dyn;
    /* the posed world positions of a skinned draw (out: 3 floats per vertex; false: not posable) */
    static bool rt_pose(const gpu_nr_draw *d, bool skin, float *out)
    {
        const uint8_t *vb = (const uint8_t *)d->mesh.vtx;
        if (!vb || d->mesh.stride != 28) return false;
        float wk;
        { const uint32_t u = 0x3B808081u; memcpy(&wk, &u, 4); }   /* the decode pieces' LOI (1 / 255) */
        const float(*B)[4] = d->bones, (*W)[4] = d->rt;
        for (uint32_t i = 0; i < d->mesh.nvtx; i++, vb += 28) {
            int16_t q[3];
            memcpy(q, vb, 6);
            float p[3];
            for (int c = 0; c < 3; c++) p[c] = (float)q[c] * (1.0f / 32768.0f) * d->cb[4][c];
            if (skin) {
                float a[3] = { 0, 0, 0 };
                for (int k = 0; k < 4; k++) {
                    const float w = (float)vb[24 + k] * wk;
                    const unsigned r = vb[20 + k];
                    if (w == 0.0f) continue;
                    for (int c = 0; c < 3; c++) {
                        float s = 0.0f;   /* (rows past the 256 uploaded read as 0, as the cbuffer) */
                        if (r < 256) s += B[r][c] * p[0] * w;
                        if (r + 1 < 256) s += B[r + 1][c] * p[1] * w;
                        if (r + 2 < 256) s += B[r + 2][c] * p[2] * w;
                        if (r + 3 < 256) s += B[r + 3][c] * w;
                        a[c] += s;
                    }
                }
                p[0] = a[0]; p[1] = a[1]; p[2] = a[2];
            }
            for (int c = 0; c < 3; c++) out[3 * i + c] = W[0][c] * p[0] + W[1][c] * p[1] + W[2][c] * p[2] + W[3][c];
        }
        return true;
    }
    float rt_fnear = 40.0f, rt_ffar = 110.0f;   /* (rt3: 50, 160 -> 40, 110: Juraika 4x cost, the look unchanged) */
    /* enclosure (docs/RAYTRACING.md "Interiors"): receivers count their sun-facing pixels and the
     * shadowed ones (nr_draw.hlsl g_rtstat, one slot of 8 bytes per game frame, read back 8 frames
     * later); a scene where nearly every sun-facing pixel is shadowed is an interior / a covered
     * place whose key light the art already bakes in: the shadow strength fades out there */
    enum { RT_STAT_SLOTS = 64 };
    Buf rt_stat, rt_statrb;   /* device-local counters (shader atomics), host read-back copies */
    uint64_t rt_stat_serial[RT_STAT_SLOTS] = {};
    float rt_encl = 0.0f, rt_kstr = 1.0f, rt_elo = 0.6f, rt_ehi = 0.85f;
    int rt_encl_on = 1, rt_statlog = -1;
    double rt_encl_sum = 0.0;
    uint64_t rt_encl_n = 0;
    int rt_chars = 1, rt_stick_max = 1800, rt_alpha_on = 1, rt_rays = 1, rt_sunsrc = 1;
    float rt_len = 8000.0f, rt_off = 0.5f, rt_offd = 0.002f, rt_smin = 0.45f, rt_smax = 0.8f, rt_sfix = -1.0f, rt_cone = 0.02f;
    int rt_minw = 512;
    long rt_dynlog = -1;   /* $RG_RT_DYNLOG */
    bool rt_rchr = false;  /* the receiver being drawn is a character part (rt_cb: trace masks) */
    float rt_lastL[3] = { 0, 0, 0 };   /* the last receiver's light direction (stats) */
    /* the sun (RT2, docs/RAYTRACING.md "Light model"): the drawn map area's key light (rows 8-10 of
     * every record: nr_rt_area_light, from MapAreasDrawLit_1e1830's light sets); without it for 8
     * record frames, light 0 of the lit (NRV_LIGHT) draws (RT1: Character2LightBlend's copy of
     * the same set); a key light darker than RT_SUN_MIN: no shadows */
    float rt_sun[3][4] = {};   /* direction (towards the light), colour, ambient */
    bool rt_sun_ok = false;
    int rt_sun_kind = 0;       /* 1 area light set, 2 lit draws */
    uint32_t rt_sun_area_frame = 0;
    uint64_t rt_sun_n = 0;
    uint32_t rt_cur = 0;   /* the newest record frame seen (gpu_nr_draw.rt_frame) */
    int rt_class = -1;     /* $RG_RT_CLASS=1: draw-class histogram at exit */
    std::map<uint32_t, uint64_t> rt_hist;
    struct RtStats {
        uint64_t frames, tlas, blas, blas_fail, inst, inst_max, tris, recv, cast, cast_dup, sk_skin, sk_var, sk_target,
            sk_blend, sk_ate, sk_nolight, sk_stale, cast_alpha, alpha_copies, alpha_bytes, alpha_opaque, inst_cut, stick_inst, stick_clear,
            sun_area, sun_lit, sun_dark, recv_skin, recv_aoonly, recv_refl, recv_water, cast_chr, dyn_build, dyn_refit, dyn_inst, dyn_extrap, x_n, xv_n, xv_parts;
        double ms_cpu, x_err0, x_err1, xv_err0, xv_err1, xv_err2;
    } rst = {};
    void rt_params()
    {
        const char *e;
        if ((e = getenv("RG_RT_LEN"))) rt_len = (float)atof(e);
        if ((e = getenv("RG_RT_OFFSET"))) rt_off = (float)atof(e);
        if ((e = getenv("RG_RT_OFFSET_D"))) rt_offd = (float)atof(e);
        if ((e = getenv("RG_RT_SHADE"))) rt_sfix = (float)atof(e);   /* a fixed multiplier for shadowed pixels */
        if ((e = getenv("RG_RT_MINW"))) rt_minw = atoi(e);           /* casters / receivers: targets at least this wide */
        if ((e = getenv("RG_RT_ALPHA"))) rt_alpha_on = atoi(e);      /* 0: alpha-tested casters solid (RT1) */
        if ((e = getenv("RG_RT_STICKY"))) rt_stick_max = atoi(e);    /* frames a culled caster stays; 0 off */
        if ((e = getenv("RG_RT_RAYS"))) rt_rays = atoi(e);           /* shadow rays per pixel (soft penumbra) */
        if ((e = getenv("RG_RT_CONE"))) rt_cone = (float)atof(e);    /* the light's angular radius (tangent) */
        if ((e = getenv("RG_RT_SUN"))) rt_sunsrc = !strcmp(e, "lit") ? 2 : 1;   /* area (default) | lit (RT1) */
        if ((e = getenv("RG_RT_FOLIAGE"))) { rt_fnear = (float)atof(e); const char *c = strchr(e, ','); rt_ffar = c ? (float)atof(c + 1) : 0.0f; }   /* near,far; "0" off */
        if ((e = getenv("RG_RT_ENCLOSED"))) { rt_encl_on = atoi(e) != 0; const char *c = strchr(e, ','); if (c) { rt_elo = (float)atof(c + 1); c = strchr(c + 1, ','); if (c) rt_ehi = (float)atof(c + 1); } }   /* 0 off | 1,lo,hi */
        if ((e = getenv("RG_RT_CHARS"))) rt_chars = atoi(e);         /* 0: skinned meshes do not receive */
        if ((e = getenv("RG_RT_SMIN"))) rt_smin = (float)atof(e);
        if ((e = getenv("RG_RT_SMAX"))) rt_smax = (float)atof(e);
        if ((e = getenv("RG_RT_FILTER"))) rt_filt = atoi(e);         /* 0: no penumbra filter (RT2) */
        if ((e = getenv("RG_RT_HALF"))) rt_half = atoi(e);           /* 0: every pixel traces the map every present, 1 half, 2 quarter rate */
        if ((e = getenv("RG_RT_AO_LIT"))) rt_aolit = (float)atof(e);
        if ((e = getenv("RG_RT_AO_IN"))) rt_aostr_in = (float)atof(e);
        if ((e = getenv("RG_RT_AO_NOSUN"))) rt_ao_nosun = atoi(e);
        if ((e = getenv("RG_RT_REFL"))) { rt_refl = atoi(e) != 0; const char *c = strchr(e, ','); if (c) { rt_rstr = (float)atof(c + 1); c = strchr(c + 1, ','); if (c) rt_rlen = (float)atof(c + 1); } }   /* 0 | 1[,strength[,length]] */
        if ((e = getenv("RG_RT_REFL_CLASS"))) rt_rclass = atoi(e);
        if ((e = getenv("RG_RT_REFL_FOG"))) rt_rfog = atoi(e);
        if ((e = getenv("RG_RT_REFL_FADE"))) rt_rfade = (float)atof(e);
        if ((e = getenv("RG_RT_REFL_SMOOTH"))) rt_rsmooth = atoi(e);
        if ((e = getenv("RG_RT_REFL_FLOOR"))) { rt_rfloor_in = (float)atof(e); const char *c = strchr(e, ','); rt_rfloor_out = c ? (float)atof(c + 1) : rt_rfloor_in; }   /* (rt7) in[,out] */
        if ((e = getenv("RG_RT_AO"))) { rt_ao = atoi(e) != 0; const char *c = strchr(e, ','); if (c) { rt_aolen = (float)atof(c + 1); c = strchr(c + 1, ','); if (c) rt_aostr = (float)atof(c + 1); } }   /* 0 | 1[,length[,strength]] */
        if ((e = getenv("RG_RT_FEXP"))) rt_fexp = atoi(e) & 15;     /* measurement: 1 no history read, 2 no write, 4 no characters-only ray, 8 no map rays */
        rt_rays = rt_rays < 1 ? 1 : rt_rays > 16 ? 16 : rt_rays;
    }
    void rt_print_stats()
    {
        if (!rt_on) return;
        for (auto &e : rt_hist)
            fprintf(stderr, "rg rt class: abe %u zwrite %u ate %u alpha %02x tme %u var %03x: %llu draws\n", e.first & 1, (e.first >> 1) & 1,
                    (e.first >> 2) & 1, (e.first >> 8) & 0xFF, (e.first >> 3) & 1, e.first >> 16, (unsigned long long)e.second);
        fprintf(stderr, "rg rt: %llu frames, %llu TLAS builds (%llu instances, max %llu, sticky %llu, %llu clears), %llu BLAS (%llu triangles, %llu refused), "
                        "%llu receiver draws (%llu skinned), %llu caster draws (%llu repeated, %llu alpha-tested; %llu alpha copies, %.1f MB; instances cut-out %llu, alpha-tested but opaque %llu); skipped: skinned %llu, variant %llu, target %llu, "
                        "blended %llu, translucent casters %llu, no light %llu, stale TLAS %llu; sun: area %llu, lit %llu, dark %llu; CPU %.3f ms per frame; "
                        "last record frame %u, light (%.3f %.3f %.3f) from %s, %d rays\n",
                (unsigned long long)rst.frames, (unsigned long long)rst.tlas, (unsigned long long)rst.inst,
                (unsigned long long)rst.inst_max, (unsigned long long)rst.stick_inst, (unsigned long long)rst.stick_clear,
                (unsigned long long)rst.blas, (unsigned long long)rst.tris,
                (unsigned long long)rst.blas_fail, (unsigned long long)rst.recv, (unsigned long long)rst.recv_skin, (unsigned long long)rst.cast,
                (unsigned long long)rst.cast_dup, (unsigned long long)rst.cast_alpha, (unsigned long long)rst.alpha_copies,
                rst.alpha_bytes / 1048576.0, (unsigned long long)rst.inst_cut, (unsigned long long)rst.alpha_opaque, (unsigned long long)rst.sk_skin, (unsigned long long)rst.sk_var,
                (unsigned long long)rst.sk_target, (unsigned long long)rst.sk_blend, (unsigned long long)rst.sk_ate,
                (unsigned long long)rst.sk_nolight, (unsigned long long)rst.sk_stale, (unsigned long long)rst.sun_area,
                (unsigned long long)rst.sun_lit, (unsigned long long)rst.sun_dark, rst.frames ? rst.ms_cpu / (double)rst.frames : 0.0,
                rt_cur, rt_lastL[0], rt_lastL[1], rt_lastL[2], rt_sun_kind == 1 ? "area light set" : rt_sun_kind == 2 ? "lit draws" : "none", rt_rays);
        fprintf(stderr, "rg rt chars: %llu caster draws, %llu BLAS builds, %llu refits, %llu instances (%llu moved on by their last step; part position error vs the next frame %.2f units without, %.2f with), %llu receiver draws\n",
                (unsigned long long)rst.cast_chr, (unsigned long long)rst.dyn_build, (unsigned long long)rst.dyn_refit,
                (unsigned long long)rst.dyn_inst, (unsigned long long)rst.dyn_extrap, rst.x_n ? rst.x_err0 / (double)rst.x_n : 0.0,
                rst.x_n ? rst.x_err1 / (double)rst.x_n : 0.0, (unsigned long long)rst.recv_skin);
        fprintf(stderr, "rg rt chars pose: %llu parts posed on by their vertices' own last step ($RG_RT_XVERT); vertex position error vs the next frame %.3f units last pose, %.3f moved by the part's step (rt4), %.3f by each vertex's step (%llu vertices)\n",
                (unsigned long long)rst.xv_parts, rst.xv_n ? rst.xv_err0 / (double)rst.xv_n : 0.0, rst.xv_n ? rst.xv_err1 / (double)rst.xv_n : 0.0,
                rst.xv_n ? rst.xv_err2 / (double)rst.xv_n : 0.0, (unsigned long long)rst.xv_n);
        fprintf(stderr, "rg rt motion: mode %d ($RG_RT_MV), %llu moving receiver draws with their previous pose, %llu without (no history), %llu skinned\n",
                rt_mvmode, (unsigned long long)rt_mvst[0], (unsigned long long)rt_mvst[1], (unsigned long long)rt_mvst[2]);
        fprintf(stderr, "rg rt presents: %llu with their own TLAS (RT2d), %llu failed; penumbra filter %s (%llu presents, half rate %d); ambient occlusion %s (%llu receiver draws without a sun); reflections %s (%llu reflective draws, %llu of them water)\n",
                (unsigned long long)rt_npass, (unsigned long long)rt_npass_fail, rt_filt && rt_hist_ok ? "on" : "off",
                (unsigned long long)rt_npres, rt_half, rt_ao ? "on" : "off", (unsigned long long)rst.recv_aoonly, rt_refl ? "on" : "off", (unsigned long long)rst.recv_refl, (unsigned long long)rst.recv_water);
        fprintf(stderr, "rg rt sun census: key light luminance min %.2f max %.2f; draws taking it < 2 (dark) %llu, 2-8 %llu, 8-32 %llu, 32-64 %llu, 64-128 %llu, >= 128 %llu\n",
                rt_sunlum_min < 1e29f ? rt_sunlum_min : 0.0f, rt_sunlum_max, (unsigned long long)rt_sunlum[0], (unsigned long long)rt_sunlum[1],
                (unsigned long long)rt_sunlum[2], (unsigned long long)rt_sunlum[3], (unsigned long long)rt_sunlum[4], (unsigned long long)rt_sunlum[5]);
        fprintf(stderr, "rg rt enclosure: mean shadowed share %.3f over %llu frames, last %.3f, strength %.2f\n",
                rt_encl_n ? rt_encl_sum / (double)rt_encl_n : 0.0, (unsigned long long)rt_encl_n, rt_encl, rt_kstr);
    }
    VkDeviceAddress rt_addr(VkBuffer b)
    {
        VkBufferDeviceAddressInfo i = { VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO };
        i.buffer = b;
        return vkGetBufferDeviceAddress(dev, &i);
    }
    void rt_as_free(RtAS &a)
    {
        if (a.as) vkDestroyAccelerationStructureKHR(dev, a.as, NULL);
        buf_free(a.buf);
        a = RtAS();
    }
    void rt_as_defer(RtAS &a)
    {
        Del d;
        d.as = a.as;
        d.b = a.buf.b;
        d.a = a.buf.a;
        defer(d);
        a = RtAS();
    }
    bool rt_as_make(RtAS &a, VkAccelerationStructureTypeKHR type, VkDeviceSize size)
    {
        if (!buf_make(a.buf, size, VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, 0))
            return false;
        VkAccelerationStructureCreateInfoKHR ci_ = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR };
        ci_.buffer = a.buf.b;
        ci_.size = size;
        ci_.type = type;
        if (vkCreateAccelerationStructureKHR(dev, &ci_, NULL, &a.as) != VK_SUCCESS) {
            buf_free(a.buf);
            a = RtAS();
            return false;
        }
        VkAccelerationStructureDeviceAddressInfoKHR ai = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR };
        ai.accelerationStructure = a.as;
        a.addr = vkGetAccelerationStructureDeviceAddressKHR(dev, &ai);
        return true;
    }
    void rt_barrier()
    {
        VkMemoryBarrier mb = { VK_STRUCTURE_TYPE_MEMORY_BARRIER };
        mb.srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
        mb.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
        vkCmdPipelineBarrier(cb(), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 1, &mb, 0, NULL, 0, NULL);
        st_n[ST_BARRIER]++;
    }
    /* scratch for one build; builds share the buffer until it is full, then a barrier */
    bool rt_scratch_get(VkDeviceSize need, VkDeviceAddress &addr)
    {
        const VkDeviceSize al = rt_scratch_align;
        need = (need + al - 1) / al * al;
        if (rt_scratch.b && rt_scr_off + need + al > rt_scratch.size && rt_scr_off) {
            rt_barrier();
            rt_scr_off = 0;
        }
        if (!rt_scratch.b || need + al > rt_scratch.size) {
            buf_defer(rt_scratch);
            VkDeviceSize sz = (VkDeviceSize)32 << 20;
            while (sz < need + al) sz *= 2;
            if (!buf_make(rt_scratch, sz, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, 0)) return false;
            rt_scr_off = 0;
        }
        VkDeviceAddress base = rt_addr(rt_scratch.b);
        base = (base + al - 1) / al * al;
        addr = base + rt_scr_off;
        rt_scr_off += need;
        return true;
    }
    bool rt_blas(NrMeshBuf &mb)
    {
        uint32_t nv = mb.vbytes / 28, nt = mb.nidx / 3;
        mb.blas_state = -1;
        if (!nv || !nt) { rst.blas_fail++; return false; }
        VkAccelerationStructureGeometryKHR g = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR };
        g.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
        g.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;   /* (alpha-tested instances: FORCE_NO_OPAQUE, rt_frame) */
        VkAccelerationStructureGeometryTrianglesDataKHR &t = g.geometry.triangles;
        t.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
        t.vertexFormat = VK_FORMAT_R16G16B16A16_SNORM;   /* nr_vtx px, py, pz, pw (the 4th is ignored) */
        t.vertexData.deviceAddress = rt_addr(mb.vb.b);
        t.vertexStride = 28;
        t.maxVertex = nv - 1;
        t.indexType = VK_INDEX_TYPE_UINT32;
        t.indexData.deviceAddress = rt_addr(mb.ib.b);
        VkAccelerationStructureBuildGeometryInfoKHR bi = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
        bi.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
        bi.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
        bi.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
        bi.geometryCount = 1;
        bi.pGeometries = &g;
        VkAccelerationStructureBuildSizesInfoKHR sz = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
        vkGetAccelerationStructureBuildSizesKHR(dev, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &bi, &nt, &sz);
        if (!rt_as_make(mb.blas, VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR, sz.accelerationStructureSize)) { rst.blas_fail++; return false; }
        VkDeviceAddress sa;
        if (!rt_scratch_get(sz.buildScratchSize, sa)) { rt_as_free(mb.blas); rst.blas_fail++; return false; }
        bi.dstAccelerationStructure = mb.blas.as;
        bi.scratchData.deviceAddress = sa;
        VkAccelerationStructureBuildRangeInfoKHR r = {};
        r.primitiveCount = nt;
        const VkAccelerationStructureBuildRangeInfoKHR *pr = &r;
        vkCmdBuildAccelerationStructuresKHR(cb(), 1, &bi, &pr);
        mb.blas_state = 1;
        rst.blas++;
        rst.tris += nt;
        return true;
    }
    /* RT2b: the texels of a decoded texture for the candidate loop (a buffer copy of the image, by
     * its decode number: a texture decoded again gets a new copy, the old one stays valid for the
     * instances that still name it) */
    RtAlpha *rt_alpha_get(NrTex *tx)
    {
        if (!tx || !tx->rtgen || !tx->img.i) return NULL;
        auto it = rt_alpha.find(tx->rtgen);
        if (it != rt_alpha.end()) return &it->second;
        RtAlpha a;
        a.w = (uint32_t)tx->tw;
        a.h = (uint32_t)tx->th;
        if (!a.w || !a.h) return NULL;
        if (!buf_make(a.b, (VkDeviceSize)a.w * a.h * 4, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                                              VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, 0))
            return NULL;
        pre_op();
        rt_barrier();   /* the decode (compute / copy) is done */
        VkBufferImageCopy c = {};
        c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        c.imageSubresource.layerCount = 1;
        c.imageExtent = { a.w, a.h, 1 };
        vkCmdCopyImageToBuffer(cb(), tx->img.i, VK_IMAGE_LAYOUT_GENERAL, a.b.b, 1, &c);
        if (buf_make(a.rb, (VkDeviceSize)a.w * a.h * 4, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2))
            vkCmdCopyImageToBuffer(cb(), tx->img.i, VK_IMAGE_LAYOUT_GENERAL, a.rb.b, 1, &c);
        a.serial = subs[ci].serial;
        rt_barrier();   /* before the ray queries read it */
        post_op();
        a.addr = rt_addr(a.b.b);
        rst.alpha_copies++;
        rst.alpha_bytes += (uint64_t)a.w * a.h * 4;
        return &(rt_alpha[tx->rtgen] = a);
    }
    /* the submission with this serial has completed (no wait) */
    bool rt_serial_done(uint64_t sv)
    {
        if (recording && subs[ci].serial <= sv) return false;
        for (int i = 0; i < NSUB; i++)
            if (subs[i].busy && subs[i].serial <= sv && vkGetFenceStatus(dev, subs[i].fence) != VK_SUCCESS) return false;
        return true;
    }
    /* an instance's material row (RT2b; m[14] = the mesh id is set by the caller); cut: an
     * alpha-tested caster whose texels do not all pass (false: its alpha copy is gone, no caster) */
    bool rt_mat(const RtInst &r, NrMeshBuf &mb, uint64_t fr, uint32_t m[16], bool &cut)
    {
        if (r.tgen) {
            auto at = rt_alpha.find(r.tgen);
            if (at == rt_alpha.end()) return false;   /* (its copy failed: no caster rather than a solid card) */
            at->second.ref = fr;
            /* every texel passes the test (GEQUAL / GREATER with the smallest vertex alpha): opaque */
            const int amin = at->second.amin, atst = (int)(r.mfl & 7u), tfx = (int)((r.mfl >> 16) & 3u);
            const float aref = (float)((r.mfl >> 8) & 255u);
            float A = tfx == 0 ? floorf(r.vamin * (float)amin / 128.0f) : tfx == 2 ? (float)amin + r.vamin : (float)amin;
            cut = amin < 0 || !((atst == 5 && A >= aref) || (atst == 6 && A > aref));
            if (!cut) rst.alpha_opaque++;
        }
        if (cut) {
            rst.inst_cut++;
            auto at = rt_alpha.find(r.tgen);
            VkDeviceAddress vb = rt_addr(mb.vb.b), ib = rt_addr(mb.ib.b), ta = at->second.addr;
            m[0] = (uint32_t)vb; m[1] = (uint32_t)(vb >> 32);
            m[2] = (uint32_t)ib; m[3] = (uint32_t)(ib >> 32);
            m[4] = (uint32_t)ta; m[5] = (uint32_t)(ta >> 32);
            m[6] = at->second.w | (at->second.h << 16);
            m[7] = r.mfl | (1u << 24);   /* (a cut-out: hits far along the ray are foliage, nr_rt_ray) */
            memcpy(&m[8], r.uvs, 16);
            memcpy(&m[12], &r.ma, 4);
            memcpy(&m[13], &r.mc, 4);
        }
        if (rt_refl) {
            /* (rt5) the reflection hit's material (nr_draw.hlsl nr_rt_hitcol): every instance names
             * its mesh's buffers and, when textured, a texel copy; m[7] bit 25 = a material row,
             * bit 26 = textured; m[15] the material colour (RGBA8, 0x80 = 1.0) */
            if (!cut) {
                VkDeviceAddress vb = rt_addr(mb.vb.b), ib = rt_addr(mb.ib.b), ta = 0;
                uint32_t wh = 0, fl = r.rfl;
                if (r.rgen) {
                    auto at = rt_alpha.find(r.rgen);
                    if (at != rt_alpha.end()) { at->second.ref = fr; ta = at->second.addr; wh = at->second.w | (at->second.h << 16); }
                    else fl &= ~(1u << 26);
                }
                m[0] = (uint32_t)vb; m[1] = (uint32_t)(vb >> 32);
                m[2] = (uint32_t)ib; m[3] = (uint32_t)(ib >> 32);
                m[4] = (uint32_t)ta; m[5] = (uint32_t)(ta >> 32);
                m[6] = wh;
                m[7] = fl | (1u << 25);
                memcpy(&m[8], r.uvs, 16);
            } else {
                m[7] |= (1u << 25) | (1u << 26);
            }
            m[15] = r.mcol;
        }
        return true;
    }
    /* RT2c: the frame's posed characters into their BLAS (slot = mesh id + its occurrence in the
     * frame; a slot keeps its mesh's topology, so a later frame refits it) and their instances */
    bool rt_dyn_frame(uint64_t fr, std::vector<VkAccelerationStructureInstanceKHR> &ins, std::vector<uint32_t> &mats, uint64_t kbase = 0)
    {
        std::unordered_map<uint32_t, uint32_t> occ;
        /* all positions in one upload (float3, 16-aligned per draw) */
        std::vector<VkDeviceSize> doff(rt_dynp.size());
        VkDeviceSize tot = 0;
        for (size_t i = 0; i < rt_dynp.size(); i++) { doff[i] = tot; tot += ((VkDeviceSize)rt_dynp[i].nv * 12 + 15) & ~(VkDeviceSize)15; }
        RA ra = ring_alloc(tot, 16);
        if (!ra.p) return false;
        for (size_t i = 0; i < rt_dynp.size(); i++) memcpy(ra.p + doff[i], &rt_dynpos[rt_dynp[i].off], (size_t)rt_dynp[i].nv * 12);
        struct Job { RtDyn *e; NrMeshBuf *mb; size_t i; bool upd; bool vx; float ac[3]; };
        std::vector<Job> jobs;
        for (size_t i = 0; i < rt_dynp.size(); i++) {
            const RtDynPend &p = rt_dynp[i];
            auto mi = nr_mesh.find(p.in.mesh);
            if (mi == nr_mesh.end()) continue;
            NrMeshBuf &mb = mi->second;
            const uint32_t nt = mb.nidx / 3;
            if (!nt || mb.vbytes / 28 != p.nv) continue;
            const uint64_t key = kbase | (uint64_t)p.in.mesh << 16 | occ[p.in.mesh]++;
            RtDyn &e = rt_dyn[key];
            bool fresh = !e.blas.as || e.nv != p.nv || e.nt != nt || e.mesh != p.in.mesh;
            if (fresh) {
                if (e.blas.as) rt_as_defer(e.blas);
                buf_defer(e.vb);
                e = RtDyn();
                if (!buf_make(e.vb, (VkDeviceSize)p.nv * 12, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
                                                                   VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR, 0)) {
                    rt_dyn.erase(key);
                    continue;
                }
                e.nv = p.nv; e.nt = nt; e.mesh = p.in.mesh;
            }
            e.last = fr;
            Job jb = { &e, &mb, i, !fresh && (e.nbuilt % RT_DYN_REBUILD) != 0, false, { 0.0f, 0.0f, 0.0f } };
            {
                /* the part's actual box centre (rt4's step is taken from it) */
                const float *a = &rt_dynpos[p.off];
                float lo[3] = { 1e30f, 1e30f, 1e30f }, hi[3] = { -1e30f, -1e30f, -1e30f };
                for (uint32_t v = 0; v < p.nv; v++)
                    for (int c = 0; c < 3; c++) { lo[c] = a[3 * v + c] < lo[c] ? a[3 * v + c] : lo[c]; hi[c] = a[3 * v + c] > hi[c] ? a[3 * v + c] : hi[c]; }
                for (int c = 0; c < 3; c++) jb.ac[c] = 0.5f * (lo[c] + hi[c]);
            }
            if (!kbase) {
                /* (rt7) per-vertex pose extrapolation (game frames only: a present's TLAS is posed at its time) */
                if (rt_xvert < 0) { const char *ev = getenv("RG_RT_XVERT"); rt_xvert = ev && *ev ? atoi(ev) : 1; }
                static int xi = -1;
                if (xi < 0) { const char *ev = getenv("RG_RT_EXTRAP"); xi = ev && *ev ? atoi(ev) : 1; if (xi > 1) rt_xmax = (float)xi; }
                float *a = &rt_dynpos[p.off];
                const size_t n3 = (size_t)p.nv * 3;
                const bool have = e.pp.size() == n3 && e.vfr + 1 == fr;
                float d2 = 0.0f;
                for (int c = 0; c < 3; c++) { const float dl = jb.ac[c] - e.pc[c]; d2 += dl * dl; }
                const bool near_ = have && e.pfr + 1 == fr && d2 <= rt_xmax * rt_xmax;
                if (near_) {
                    /* the error of each way of predicting this frame's vertices from the last one */
                    double s0 = 0.0, s1 = 0.0, s2 = 0.0;
                    for (uint32_t v = 0; v < p.nv; v++) {
                        double q0 = 0.0, q1 = 0.0, q2 = 0.0;
                        for (int c = 0; c < 3; c++) {
                            const double d = (double)a[3 * v + c] - e.pp[3 * v + c];
                            q0 += d * d; q1 += (d - e.pd[c]) * (d - e.pd[c]); q2 += (d - e.ps[3 * v + c]) * (d - e.ps[3 * v + c]);
                        }
                        s0 += sqrt(q0); s1 += sqrt(q1); s2 += sqrt(q2);
                    }
                    rst.xv_err0 += s0; rst.xv_err1 += s1; rst.xv_err2 += s2; rst.xv_n += p.nv;
                }
                const bool vx = rt_xvert > 0 && xi != 0 && near_;
                if (e.ps.size() != n3) e.ps.assign(n3, 0.0f);
                if (e.pp.size() != n3) e.pp.assign(n3, 0.0f);
                const float xm2 = rt_xmax * rt_xmax;
                for (uint32_t v = 0; v < p.nv; v++) {
                    float st[3], l2 = 0.0f;
                    for (int c = 0; c < 3; c++) { st[c] = have ? a[3 * v + c] - e.pp[3 * v + c] : 0.0f; l2 += st[c] * st[c]; }
                    const float k = l2 > xm2 ? rt_xmax / sqrtf(l2) : 1.0f;
                    for (int c = 0; c < 3; c++) {
                        e.pp[3 * v + c] = a[3 * v + c];
                        e.ps[3 * v + c] = near_ && xi != 0 ? st[c] * k : 0.0f;   /* (kept for the error census also when not applied) */
                        if (vx) a[3 * v + c] += st[c] * k;
                    }
                }
                e.vfr = fr;
                if (vx) {
                    memcpy(ra.p + doff[i], a, n3 * 4);
                    jb.vx = true;
                    rst.xv_parts++;
                }
            }
            VkBufferCopy c = { ra.off + doff[i], 0, (VkDeviceSize)p.nv * 12 };
            vkCmdCopyBuffer(cb(), ra.b, e.vb.b, 1, &c);
            jobs.push_back(jb);
        }
        if (jobs.empty()) return false;
        rt_barrier();   /* the positions are in place */
        for (Job &j : jobs) {
            RtDyn &e = *j.e;
            VkAccelerationStructureGeometryKHR g = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR };
            g.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
            g.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
            VkAccelerationStructureGeometryTrianglesDataKHR &t = g.geometry.triangles;
            t.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
            t.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
            t.vertexData.deviceAddress = rt_addr(e.vb.b);
            t.vertexStride = 12;
            t.maxVertex = e.nv - 1;
            t.indexType = VK_INDEX_TYPE_UINT32;
            t.indexData.deviceAddress = rt_addr(j.mb->ib.b);
            VkAccelerationStructureBuildGeometryInfoKHR bi = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
            bi.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
            bi.flags = VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR;
            bi.mode = j.upd ? VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR : VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
            bi.geometryCount = 1;
            bi.pGeometries = &g;
            VkAccelerationStructureBuildSizesInfoKHR sz = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
            vkGetAccelerationStructureBuildSizesKHR(dev, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &bi, &e.nt, &sz);
            if (!e.blas.as && !rt_as_make(e.blas, VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR, sz.accelerationStructureSize)) continue;
            VkDeviceAddress sa;
            if (!rt_scratch_get(j.upd ? sz.updateScratchSize : sz.buildScratchSize, sa)) continue;
            if (j.upd) bi.srcAccelerationStructure = e.blas.as;
            bi.dstAccelerationStructure = e.blas.as;
            bi.scratchData.deviceAddress = sa;
            VkAccelerationStructureBuildRangeInfoKHR r = {};
            r.primitiveCount = e.nt;
            const VkAccelerationStructureBuildRangeInfoKHR *pr = &r;
            vkCmdBuildAccelerationStructuresKHR(cb(), 1, &bi, &pr);
            e.nbuilt++;
            if (j.upd) rst.dyn_refit++;
            else rst.dyn_build++;
            const RtInst &in = rt_dynp[j.i].in;
            uint32_t m[16] = {};
            bool cut = false;
            if (!rt_mat(in, *j.mb, fr, m, cut)) continue;
            m[14] = in.mesh;
            VkAccelerationStructureInstanceKHR x;
            memset(&x, 0, sizeof x);
            memcpy(x.transform.matrix, in.m, sizeof in.m);
            /* the part's bounding box (for the characters' spheres, rt_csph) */
            const RtDynPend &pp = rt_dynp[j.i];
            float lo[3] = { 1e30f, 1e30f, 1e30f }, hi[3] = { -1e30f, -1e30f, -1e30f };
            for (uint32_t v = 0; v < pp.nv; v++)
                for (int c = 0; c < 3; c++) {
                    const float f = rt_dynpos[pp.off + 3 * v + c];
                    lo[c] = f < lo[c] ? f : lo[c];
                    hi[c] = f > hi[c] ? f : hi[c];
                }
            {
                /* (rt4) extrapolated by the part's last step: game frames only (kbase 0); an
                 * interpolated present's TLAS (RT2d) is posed at its own time already */
                static int xi = -1;
                if (xi < 0) { const char *ev = getenv("RG_RT_EXTRAP"); xi = ev && *ev ? atoi(ev) : 1; if (xi > 1) rt_xmax = (float)xi; }
                float c[3], dl[3] = { 0.0f, 0.0f, 0.0f }, d2 = 0.0f;
                /* ((rt7) the actual centre: with per-vertex extrapolation lo / hi are the moved-on pose's) */
                for (int k = 0; k < 3; k++) { c[k] = j.ac[k]; dl[k] = c[k] - e.pc[k]; d2 += dl[k] * dl[k]; }
                const bool ok = xi != 0 && !kbase && e.pfr && e.pfr + 1 == fr && d2 <= rt_xmax * rt_xmax && d2 > 1e-8f;
                if (!kbase && e.pfr && e.pfr + 1 == fr && d2 <= rt_xmax * rt_xmax) {
                    /* (the error a shadow had: this frame's centre against last frame's TLAS
                     * position, without and with the step the last frame extrapolated) */
                    double e0 = 0.0, e1 = 0.0;
                    for (int k = 0; k < 3; k++) { e0 += (double)dl[k] * dl[k]; e1 += (double)(dl[k] - e.pd[k]) * (dl[k] - e.pd[k]); }
                    rst.x_err0 += sqrt(e0); rst.x_err1 += sqrt(e1); rst.x_n++;
                }
                if (!kbase) { memcpy(e.pc, c, sizeof c); e.pfr = fr; for (int k = 0; k < 3; k++) e.pd[k] = ok ? dl[k] : 0.0f; }
                if (ok && !j.vx) {
                    for (int k = 0; k < 3; k++) { x.transform.matrix[k][3] += dl[k]; lo[k] += dl[k]; hi[k] += dl[k]; }
                    rst.dyn_extrap++;
                }
            }
            x.mask = cut ? 0x08 : 0x04;
            x.instanceCustomIndex = (uint32_t)ins.size() & 0xFFFFFFu;
            x.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR |
                      (cut ? VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR : VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR);
            x.accelerationStructureReference = e.blas.addr;
            ins.push_back(x);
            mats.insert(mats.end(), m, m + 16);
            rst.dyn_inst++;
            rt_sph_add(lo, hi);
        }
        return true;
    }
    /* the characters' bounding spheres (at most RT_SPH; parts merged into the nearest sphere when
     * full): the filter's characters-only ray is traced only when it passes one (nr_draw.hlsl) */
    enum { RT_SPH = 8 };
    float rt_sph[RT_SPH][4] = {}, rt_csph[RT_SPH][4] = {}, rt_pcsph[RT_SPH][4] = {};
    int rt_nsph = 0;
    void rt_sph_add(const float lo[3], const float hi[3])
    {
        float c[3], r = 0.0f;
        for (int k = 0; k < 3; k++) { c[k] = 0.5f * (lo[k] + hi[k]); r += 0.25f * (hi[k] - lo[k]) * (hi[k] - lo[k]); }
        r = sqrtf(r);
        if (!(r < 1e6f)) return;
        int best = -1;
        float bd = 1e30f;
        for (int i = 0; i < rt_nsph; i++) {
            float d = sqrtf((rt_sph[i][0] - c[0]) * (rt_sph[i][0] - c[0]) + (rt_sph[i][1] - c[1]) * (rt_sph[i][1] - c[1]) +
                            (rt_sph[i][2] - c[2]) * (rt_sph[i][2] - c[2]));
            if (d + r <= rt_sph[i][3]) return;   /* (inside one already) */
            if (d < bd) { bd = d; best = i; }
        }
        if (rt_nsph < RT_SPH && (best < 0 || bd > rt_sph[best][3] + r)) {
            memcpy(rt_sph[rt_nsph], c, 12);
            rt_sph[rt_nsph++][3] = r;
            return;
        }
        if (best < 0) return;
        /* grow sphere best to hold this one */
        float *S = rt_sph[best];
        const float nr = 0.5f * (bd + r + S[3]);
        if (bd > 1e-6f) {
            const float t = (nr - S[3]) / bd;
            for (int k = 0; k < 3; k++) S[k] += (c[k] - S[k]) * t;
        }
        S[3] = nr > S[3] ? nr : S[3];
    }
    /* the characters' own TLAS (their instances of ins, masks 4 / 8; rows of the same material
     * table): the characters-only ray of the penumbra filter traverses a few instances instead of
     * the whole map's (nr_draw.hlsl g_tlasc) */
    RtAS rt_ctlas, rt_pctlas;
    Buf rt_cibuf, rt_pcibuf, rt_cdummy;
    uint32_t rt_ccap = 0, rt_pccap = 0;
    void rt_ctop(RtAS &tl, Buf &ib, uint32_t &cap, const std::vector<VkAccelerationStructureInstanceKHR> &ins)
    {
        std::vector<VkAccelerationStructureInstanceKHR> c;
        for (const auto &x : ins)
            if (x.mask & 12u) c.push_back(x);
        VkDeviceAddress da = 0;
        if (!rt_top_build(tl, ib, rt_cdummy, da, cap, c, std::vector<uint32_t>())) rt_as_free(tl);
    }
    /* a TLAS from instances + their material rows (the buffers grow by powers of two, kept) */
    bool rt_top_build(RtAS &tl, Buf &ib, Buf &mbf, VkDeviceAddress &maddr, uint32_t &cap_,
                      const std::vector<VkAccelerationStructureInstanceKHR> &ins, const std::vector<uint32_t> &mats)
    {
        uint32_t n = (uint32_t)ins.size();
        bool ok = true;
        if (!tl.as || n > cap_) {
            uint32_t cap = 1024;
            while (cap < n) cap *= 2;
            if (tl.as) rt_as_defer(tl);
            buf_defer(ib);
            buf_defer(mbf);
            ok = buf_make(ib, (VkDeviceSize)cap * sizeof(VkAccelerationStructureInstanceKHR),
                          VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
                              VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR, 0) &&
                 buf_make(mbf, (VkDeviceSize)cap * 64, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                                               VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, 0);
            maddr = ok ? rt_addr(mbf.b) : 0;
            cap_ = ok ? cap : 0;
        }
        VkAccelerationStructureGeometryKHR g = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR };
        g.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
        g.geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
        g.geometry.instances.data.deviceAddress = ok ? rt_addr(ib.b) : 0;
        VkAccelerationStructureBuildGeometryInfoKHR bi = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
        bi.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
        bi.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
        bi.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
        bi.geometryCount = 1;
        bi.pGeometries = &g;
        VkAccelerationStructureBuildSizesInfoKHR sz = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
        if (ok) vkGetAccelerationStructureBuildSizesKHR(dev, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &bi, &cap_, &sz);
        if (ok && !tl.as) ok = rt_as_make(tl, VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR, sz.accelerationStructureSize);
        VkDeviceAddress sa = 0;
        if (ok) ok = rt_scratch_get(sz.buildScratchSize, sa);
        if (ok && n) {
            RA ra = ring_put(ins.data(), (VkDeviceSize)n * sizeof ins[0], 16);
            RA rm = ra.p && !mats.empty() ? ring_put(mats.data(), (VkDeviceSize)n * 64, 16) : ra;
            if (!ra.p || !rm.p) ok = false;
            else {
                VkBufferCopy c = { ra.off, 0, (VkDeviceSize)n * sizeof ins[0] };
                vkCmdCopyBuffer(cb(), ra.b, ib.b, 1, &c);
                VkBufferCopy c2 = { rm.off, 0, (VkDeviceSize)n * 64 };
                if (!mats.empty()) vkCmdCopyBuffer(cb(), rm.b, mbf.b, 1, &c2);   /* (none: the rows are another TLAS's) */
                rt_barrier();
            }
        }
        if (ok) {
            bi.dstAccelerationStructure = tl.as;
            bi.scratchData.deviceAddress = sa;
            VkAccelerationStructureBuildRangeInfoKHR r = {};
            r.primitiveCount = n;
            const VkAccelerationStructureBuildRangeInfoKHR *pr = &r;
            vkCmdBuildAccelerationStructuresKHR(cb(), 1, &bi, &pr);
            rt_barrier();
        }
        return ok;
    }
    /* once per game frame: BLAS for new casters, the sticky set, then the TLAS + material table */
    void rt_frame()
    {
        auto t0 = std::chrono::steady_clock::now();
        rst.frames++;
        const uint64_t fr = rst.frames;
        pre_op();
        uint64_t pq0 = prof ? pts() : ~0ull;
        rt_barrier();   /* the previous frame's ray queries and builds are done with the TLAS and scratch */
        rt_scr_off = 0;
        /* RT2a: the sticky set (the frame's casters update it; the ones it keeps join them) */
        std::vector<const RtInst *> all;
        all.reserve(rt_inst.size() + rt_stick.size());
        for (const RtInst &r : rt_inst) all.push_back(&r);
        if (rt_stick_max > 0) {
            size_t known = 0;
            for (uint64_t k : rt_keys) known += rt_stick.count(k);
            if ((rt_inst.size() >= 16 && known * 10 < rt_inst.size()) || rt_stick.size() > 65536) {
                if (!rt_stick.empty()) rst.stick_clear++;
                rt_stick.clear();
            }
            for (size_t i = 0; i < rt_inst.size(); i++) {
                if (rt_inst[i].pad != 0.0f) continue;   /* (character parts move: never sticky) */
                RtStick &st = rt_stick[rt_keys[i]];
                if (!st.nseen) st.in = rt_inst[i];
                st.nseen++;
                st.last = fr;
            }
            for (auto it = rt_stick.begin(); it != rt_stick.end();) {
                if (it->second.last == fr) { ++it; continue; }
                if (fr - it->second.last > (uint64_t)rt_stick_max || !nr_mesh.count(it->second.in.mesh)) { it = rt_stick.erase(it); continue; }
                if (it->second.nseen >= 2) { all.push_back(&it->second.in); rst.stick_inst++; }
                ++it;
            }
        }
        /* enclosure: the counts of frame fr - 8 (when its submission completed) */
        if (rt_encl_on) {
            if (!rt_stat.b) {
                if (!buf_make(rt_stat, RT_STAT_SLOTS * 8, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
                                                               VK_BUFFER_USAGE_TRANSFER_DST_BIT, 0) ||
                    !buf_make(rt_statrb, RT_STAT_SLOTS * 8, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2) || !rt_statrb.map) {
                    buf_free(rt_stat); buf_free(rt_statrb);
                    rt_encl_on = 0;
                } else {
                    vkCmdFillBuffer(cb(), rt_stat.b, 0, RT_STAT_SLOTS * 8, 0);
                    rt_barrier();   /* (before the slot copy / fill below: sync validation, rt3) */
                }
            }
            if (rt_stat.b) {
                /* the previous frame's slot to the read-back buffer, this frame's slot cleared */
                const VkDeviceSize pv = 8 * ((fr + RT_STAT_SLOTS - 1) % RT_STAT_SLOTS), cu = 8 * (fr % RT_STAT_SLOTS);
                VkBufferCopy c = { pv, pv, 8 };
                vkCmdCopyBuffer(cb(), rt_stat.b, rt_statrb.b, 1, &c);
                rt_stat_serial[pv / 8] = subs[ci].serial;
                vkCmdFillBuffer(cb(), rt_stat.b, cu, 8, 0);
                rt_barrier();
            }
            const int k = (int)((fr + RT_STAT_SLOTS - 8) % RT_STAT_SLOTS);
            if (rt_statrb.map && fr > 8 && rt_stat_serial[k] && rt_serial_done(rt_stat_serial[k])) {
                buf_inval(rt_statrb);
                uint32_t c[2];
                memcpy(c, rt_statrb.map + 8 * k, 8);
                rt_stat_serial[k] = 0;
                if (c[0] >= 2000u) {
                    float r = (float)c[1] / (float)c[0];
                    rt_encl = rt_encl_n ? 0.85f * rt_encl + 0.15f * r : r;
                    rt_encl_sum += r;
                    rt_encl_n++;
                    float tgt = rt_encl <= rt_elo ? 1.0f : rt_encl >= rt_ehi ? 0.0f : (rt_ehi - rt_encl) / (rt_ehi - rt_elo);
                    rt_kstr += (tgt - rt_kstr) * 0.1f;
                    if (rt_statlog < 0) { const char *e = getenv("RG_RT_STATLOG"); rt_statlog = e && e[0] == '1'; }
                    if (rt_statlog) fprintf(stderr, "rg rt stat: frame %u tested %u shadowed %u share %.3f mean %.3f strength %.2f\n", rt_cur, c[0], c[1], r, rt_encl, rt_kstr);
                }
            }
        }
        /* alpha copies whose read-back landed: the smallest texel alpha */
        for (auto &e : rt_alpha) {
            RtAlpha &a = e.second;
            if (a.amin >= 0 || !a.rb.b || !rt_serial_done(a.serial)) continue;
            buf_inval(a.rb);
            int m = 255;
            const uint8_t *px = a.rb.map;
            for (size_t i = 0, n = (size_t)a.w * a.h; px && i < n && m; i++) m = px[4 * i + 3] < m ? px[4 * i + 3] : m;
            a.amin = m;
            buf_defer(a.rb);
        }
        std::vector<VkAccelerationStructureInstanceKHR> ins;
        std::vector<uint32_t> mats;
        ins.reserve(all.size());
        mats.reserve(all.size() * 16);
        bool built = false;
        for (const RtInst *rp : all) {
            const RtInst &r = *rp;
            auto it = nr_mesh.find(r.mesh);
            if (it == nr_mesh.end()) continue;
            NrMeshBuf &mb = it->second;
            if (mb.blas_state == 0) { rt_blas(mb); built = true; }
            if (mb.blas_state != 1) continue;
            uint32_t m[16] = {};
            bool cut = false;
            if (!rt_mat(r, mb, fr, m, cut)) continue;
            m[14] = r.mesh;
            VkAccelerationStructureInstanceKHR x;
            memset(&x, 0, sizeof x);
            memcpy(x.transform.matrix, r.m, sizeof r.m);
            x.mask = (cut ? 0x02 : 0x01) << (r.pad != 0.0f ? 2 : 0);   /* (nr_rt_ray: opaque casters, then the cut-out cards; characters 4 / 8) */
            x.instanceCustomIndex = (uint32_t)ins.size() & 0xFFFFFFu;
            x.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR |
                      (cut ? VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR : VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR);
            x.accelerationStructureReference = mb.blas.addr;
            ins.push_back(x);
            mats.insert(mats.end(), m, m + 16);
        }
        /* RT2c: the posed characters (rt_dynp): positions uploaded, BLAS built or refitted */
        rt_nsph = 0;
        if (!rt_dynp.empty()) built |= rt_dyn_frame(fr, ins, mats);
        rt_last_chr = rt_nsph;
        memset(rt_csph, 0, sizeof rt_csph);
        memcpy(rt_csph, rt_sph, sizeof rt_sph[0] * (size_t)rt_nsph);
        for (auto it = rt_dyn.begin(); it != rt_dyn.end();) {
            if (fr - it->second.last > (uint64_t)RT_DYN_AGE || !nr_mesh.count(it->second.mesh)) {
                if (it->second.blas.as) rt_as_defer(it->second.blas);
                buf_defer(it->second.vb);
                it = rt_dyn.erase(it);
            } else {
                ++it;
            }
        }
        rt_dynp.clear();
        rt_dynpos.clear();
        rt_inst.clear();
        rt_keys.clear();
        rt_seen.clear();
        /* alpha copies no instance names any more */
        for (auto it = rt_alpha.begin(); it != rt_alpha.end();) {
            if (it->second.ref != fr) { buf_defer(it->second.b); buf_defer(it->second.rb); it = rt_alpha.erase(it); }
            else ++it;
        }
        if (built) { rt_barrier(); rt_scr_off = 0; }
        uint32_t n = (uint32_t)ins.size();
        rt_ctop(rt_ctlas, rt_cibuf, rt_ccap, ins);
        if (rt_top_build(rt_tlas, rt_ibuf, rt_mbuf, rt_mbuf_addr, rt_tlas_cap, ins, mats)) {
            rt_tlas_stale = false;
            rst.tlas++;
            rst.inst += n;
            if (n > rst.inst_max) rst.inst_max = n;
        } else {
            rt_tlas_stale = true;   /* receivers draw without ray tracing until a build succeeds */
        }
        if (prof) pev_add(PC_RT, pq0, (double)n);
        post_op();
        rst.ms_cpu += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
    }
    /* RT2d (docs/RAYTRACING.md "Interpolated presents"): an interpolated present's own TLAS.  The
     * recorder (nr_iprec.cpp replay) hands the present's mesh draws at its interpolated rows to
     * rt_pass_cast before drawing them (phase 0 .. 1): they are classified as casters into a
     * collection of their own, then the TLAS of those plus the sticky set (phase 1) is what the
     * present's receivers trace (characters too, at the present's pose); phase 2 ends the present.
     * $RG_RT_PASS=0: off (presents trace the newest game frame's TLAS, as RT2) */
    RtAS rt_ptlas;
    Buf rt_pibuf, rt_pmbuf;
    VkDeviceAddress rt_pmbuf_addr = 0;
    uint32_t rt_ptlas_cap = 0;
    bool rt_prepass = false, rt_pass_on = false;
    int rt_pass_cfg = -1;
    uint64_t rt_npass = 0, rt_npass_fail = 0;
    /* (rt4) the game's plane shadows give way to ours (gpu_nr_rt_chars_shadow): ray tracing on,
     * characters cast (the last game frame's TLAS had some), a sun bright enough to shadow, a
     * TLAS, and not an interior / covered place (the enclosure fade at half strength or more) */
    int rt_last_chr = 0;
    int rt_chars_shadow() override
    {
        return rt_on && rt_chars && rt_sun_ok && !rt_tlas_stale && rt_last_chr > 0 && (!rt_encl_on || rt_kstr >= 0.5f) ? 1 : 0;
    }
    bool rt_pass(int phase) override
    {
        if (!rt_on) return false;
        if (rt_pass_cfg < 0) { const char *e = getenv("RG_RT_PASS"); rt_pass_cfg = !(e && e[0] == '0'); }
        if (phase == 0) {
            rt_pass_on = false;
            if (!rt_pass_cfg || !rt_tlas.as || rt_tlas_stale) return false;
            std::swap(rt_inst, rt_pinst); std::swap(rt_keys, rt_pkeys); std::swap(rt_seen, rt_pseen);
            std::swap(rt_dynp, rt_pdynp); std::swap(rt_dynpos, rt_pdynpos);
            rt_inst.clear(); rt_keys.clear(); rt_seen.clear(); rt_dynp.clear(); rt_dynpos.clear();
            rt_prepass = true;
            rt_pass_new();
            return true;
        }
        if (phase == 1) {
            if (!rt_prepass) return false;
            rt_prepass = false;
            auto t0 = std::chrono::steady_clock::now();
            const uint64_t fr = rst.frames;
            pre_op();
            uint64_t pq0 = prof ? pts() : ~0ull;
            rt_barrier();   /* the previous present's ray queries are done with the TLAS */
            rt_scr_off = 0;
            std::vector<VkAccelerationStructureInstanceKHR> ins;
            std::vector<uint32_t> mats;
            bool built = false;
            auto add = [&](const RtInst &r) {
                auto it = nr_mesh.find(r.mesh);
                if (it == nr_mesh.end()) return;
                NrMeshBuf &mb = it->second;
                if (mb.blas_state == 0) { rt_blas(mb); built = true; }
                if (mb.blas_state != 1) return;
                uint32_t m[16] = {};
                bool cut = false;
                if (!rt_mat(r, mb, fr, m, cut)) return;
                m[14] = r.mesh;
                VkAccelerationStructureInstanceKHR x;
                memset(&x, 0, sizeof x);
                memcpy(x.transform.matrix, r.m, sizeof r.m);
                x.mask = (cut ? 0x02 : 0x01) << (r.pad != 0.0f ? 2 : 0);
                x.instanceCustomIndex = (uint32_t)ins.size() & 0xFFFFFFu;
                x.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR |
                          (cut ? VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR : VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR);
                x.accelerationStructureReference = mb.blas.addr;
                ins.push_back(x);
                mats.insert(mats.end(), m, m + 16);
            };
            for (const RtInst &r : rt_inst) add(r);
            for (auto &kv : rt_stick)
                if (kv.second.nseen >= 2 && !rt_seen.count(kv.first)) add(kv.second.in);
            rt_nsph = 0;
            if (!rt_dynp.empty()) built |= rt_dyn_frame(fr, ins, mats, 1ull << 62);
            memset(rt_pcsph, 0, sizeof rt_pcsph);
            memcpy(rt_pcsph, rt_sph, sizeof rt_sph[0] * (size_t)rt_nsph);
            if (built) { rt_barrier(); rt_scr_off = 0; }
            rt_ctop(rt_pctlas, rt_pcibuf, rt_pccap, ins);
            rt_pass_on = rt_top_build(rt_ptlas, rt_pibuf, rt_pmbuf, rt_pmbuf_addr, rt_ptlas_cap, ins, mats);
            if (rt_pass_on) rt_npass++;
            else rt_npass_fail++;
            std::swap(rt_inst, rt_pinst); std::swap(rt_keys, rt_pkeys); std::swap(rt_seen, rt_pseen);
            std::swap(rt_dynp, rt_pdynp); std::swap(rt_dynpos, rt_pdynpos);
            if (prof) pev_add(PC_RT, pq0, (double)ins.size());
            post_op();
            rst.ms_cpu += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            return rt_pass_on;
        }
        rt_pass_on = false;
        if (rt_prepass) {   /* (a pass that never built: the game frame's collection back) */
            rt_prepass = false;
            std::swap(rt_inst, rt_pinst); std::swap(rt_keys, rt_pkeys); std::swap(rt_seen, rt_pseen);
            std::swap(rt_dynp, rt_pdynp); std::swap(rt_dynpos, rt_pdynpos);
        }
        rt_pass_new();
        return true;
    }
    /* RT2d: one of the present's mesh draws (rows interpolated), before the present draws */
    void rt_pass_cast(const GpuNrDraw &g) override
    {
        if (!rt_prepass || !g.d || g.im || g.d->rt_ok != GPU_NR_RT_MAGIC) return;
        auto it = nr_mesh.find(g.d->mesh.id);
        if (it == nr_mesh.end()) return;
        NrTex *tx = NULL;
        if (g.tme && g.tex_rt < 0) tx = nr_find(g.dec_key, g.dec_rect, nr_hash(g.dec_key, g.dec_rect));
        rt_classify(g, g.d, &it->second, tx);
    }
    std::vector<RtInst> rt_pinst;
    std::vector<uint64_t> rt_pkeys;
    std::unordered_set<uint64_t> rt_pseen;
    std::vector<RtDynPend> rt_pdynp;
    std::vector<float> rt_pdynpos;
    /* RT2f, the penumbra filter (docs/RAYTRACING.md "Penumbra filter"; nr_draw.hlsl nr_rt_filter):
     * two history images (R32_UINT, a word per pixel of the largest receiver target), written by
     * one present's receivers and read by the next one's; the previous present's camera (world ->
     * GS screen, from its first receiver: the screen rows x the inverse of the object rows) and eye
     * position reproject.  $RG_RT_FILTER=0: off (RT2's dithered ray) */
    Img rt_hst[2];
    int rt_hcur = 0, rt_hw = 0, rt_hh = 0;
    bool rt_hist_ok = false;
    int rt_filt = 1, rt_fexp = 0, rt_half = 1;
    int rt_ao = 0;   /* RT2e: graphics.raytracing 3 (shadows + AO) or $RG_RT_AO=1 */
    float rt_aolen = 40.0f, rt_aostr = 0.5f, rt_aolit = 0.5f;   /* (rt4: rt_aolit, $RG_RT_AO_LIT; 1 = rt3) */
    float rt_aostr_in = 0.3f;   /* (rt5) AO strength in interiors / at night ($RG_RT_AO_IN; 0.5 = the outdoor value, rt4: mines / Dorgenark -5..-10 % mean luminance, 0.3: -2..-4 %) */
    int rt_ao_nosun = 1;        /* (rt5) receivers without a sun trace AO only ($RG_RT_AO_NOSUN=0: rt4, none) */
    bool rt_rnosun = false;     /* (rt5) the current receiver: no sun (AO only) */
    /* (rt5) RT3 reflections spike (docs/RAYTRACING.md "RT5"): graphics.raytracing 4 or $RG_RT_REFL=1[,strength[,length]] */
    int rt_refl = 0, rt_rclass = 1;   /* $RG_RT_REFL_CLASS bits: 1 env-map / reflection-map draws (the hit replaces the map's texel), 2 water (Fresnel blend; experimental, off by default: no confirmed water in the fixtures) */
    float rt_rstr = 1.0f, rt_rlen = 3000.0f;
    /* (rt6) reflections polish: the game's fog on the hit ($RG_RT_REFL_FOG=0 off), the distance fade's
     * start as a fraction of the ray's length ($RG_RT_REFL_FADE, >= 1 off), smooth (interpolated vertex)
     * normals ($RG_RT_REFL_SMOOTH=0: the geometric normal, rt5) */
    int rt_rfog = 1, rt_rsmooth = 1;
    float rt_rfade = 0.6f;
    float rt_fk = 0.0f;         /* (rt6) clip w per unit of eye distance of the map draws (RTF.w) */
    /* (rt7) the reflection's brightness floor (nr_draw.hlsl RTG.x): a hit darker than this fraction of
     * the painted environment texel's luminance is blended toward the texel up to it; interiors
     * (the enclosure fade) take rt_rfloor_in, open places rt_rfloor_out, mixed by the fade.
     * $RG_RT_REFL_FLOOR=in[,out]; 0 = rt6 (the hit replaces the painted surroundings at any level) */
    float rt_rfloor_in = 0.9f, rt_rfloor_out = 0.0f;
    int rt_rmode = 0;           /* the current receiver: 1 = an env / reflection-map draw, 2 = water */
    bool rt_rshadow = true;     /* the current receiver takes the shadow / AO term */
    uint64_t rt_npres = 0;
    float rt_vp_cur[4][4] = {}, rt_vp_prev[4][4] = {}, rt_cam_cur[3] = {}, rt_cam_prev[3] = {};
    bool rt_vp_cur_ok = false, rt_vp_prev_ok = false;
    void rt_hist_free() { img_free(rt_hst[0]); img_free(rt_hst[1]); rt_hist_ok = false; }
    /* the history images for a receiver target of w x h native pixels (grown when needed) */
    void rt_hist_need(int w, int h)
    {
        if (!rt_filt) return;
        const int W = w * scale * (rt_ao ? 2 : 1), H = h * scale;
        if (rt_hist_ok && W <= rt_hw && H <= rt_hh) return;
        img_defer(rt_hst[0]);
        img_defer(rt_hst[1]);
        rt_hist_ok = img_make(rt_hst[0], W > rt_hw ? W : rt_hw, H > rt_hh ? H : rt_hh, VK_FORMAT_R32_UINT,
                              VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, false) &&
                     img_make(rt_hst[1], rt_hst[0].w, rt_hst[0].h, VK_FORMAT_R32_UINT,
                              VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, false);
        if (!rt_hist_ok) { img_free(rt_hst[0]); img_free(rt_hst[1]); rt_filt = 0; return; }
        rt_hw = rt_hst[0].w;
        rt_hh = rt_hst[0].h;
        rt_vp_prev_ok = false;
        pre_op();
        VkClearColorValue z = {};
        VkImageSubresourceRange rr = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        vkCmdClearColorImage(cb(), rt_hst[0].i, VK_IMAGE_LAYOUT_GENERAL, &z, 1, &rr);
        vkCmdClearColorImage(cb(), rt_hst[1].i, VK_IMAGE_LAYOUT_GENERAL, &z, 1, &rr);
        rt_barrier();
        post_op();
    }
    /* the present's camera from a receiver's rows (the first one of the present) */
    void rt_vp_take(const gpu_nr_draw *d)
    {
        if (rt_vp_cur_ok || !rt_filt) return;
        double M[4][4] = {}, I[4][4];
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 4; c++) M[r][c] = d->rt[c][r];
        M[3][3] = 1.0;
        /* inverse of the affine object matrix */
        const double a = M[0][0], b = M[0][1], c = M[0][2], e = M[1][0], f = M[1][1], g = M[1][2], h = M[2][0], i = M[2][1], j = M[2][2];
        const double det = a * (f * j - g * i) - b * (e * j - g * h) + c * (e * i - f * h);
        if (!(fabs(det) > 1e-12)) return;
        double R3[3][3] = { { (f * j - g * i) / det, (c * i - b * j) / det, (b * g - c * f) / det },
                            { (g * h - e * j) / det, (a * j - c * h) / det, (c * e - a * g) / det },
                            { (e * i - f * h) / det, (b * h - a * i) / det, (a * f - b * e) / det } };
        memset(I, 0, sizeof I);
        for (int r = 0; r < 3; r++) {
            for (int k = 0; k < 3; k++) I[r][k] = R3[r][k];
            I[r][3] = -(R3[r][0] * M[0][3] + R3[r][1] * M[1][3] + R3[r][2] * M[2][3]);
        }
        I[3][3] = 1.0;
        /* screen = C x [p; 1] (C's columns = cb rows 0-3); world -> screen = C x I; stored as columns */
        for (int col = 0; col < 4; col++)
            for (int row = 0; row < 4; row++) {
                double v = 0.0;
                for (int k = 0; k < 4; k++) v += (double)d->cb[k][row] * I[k][col];
                rt_vp_cur[col][row] = (float)v;
            }
        for (int k = 0; k < 3; k++) rt_cam_cur[k] = d->rt[7][k];
        rt_vp_cur_ok = true;
    }
    /* a new present / game frame begins: this present's history becomes the previous one */
    void rt_pass_new()
    {
        if (!rt_filt || !rt_hist_ok) return;
        if (rt_vp_cur_ok) {
            memcpy(rt_vp_prev, rt_vp_cur, sizeof rt_vp_cur);
            memcpy(rt_cam_prev, rt_cam_cur, sizeof rt_cam_cur);
            rt_vp_prev_ok = true;
            rt_vp_cur_ok = false;
            rt_hcur ^= 1;
            rt_npres++;
        }
        pre_op();
        rt_barrier();   /* the previous present's history writes before this one reads them */
        post_op();
    }
    /* the sun of a record (rows 8-10, or light 0 of a lit draw's rows 4-6) */
    uint64_t rt_sunlum[6] = {};
    float rt_sunlum_min = 1e30f, rt_sunlum_max = 0.0f;
    void rt_take_sun(const float (*rows)[4], int kind)
    {
        for (int k = 0; k < 3; k++) memcpy(rt_sun[k], rows[k], 16);
        rt_sun_kind = kind;
        const float *c = rt_sun[1];
        /* a key light this dark casts no visible shadow (night, an unlit interior): none */
        static float smin = -1.0f;   /* (rt5) $RG_RT_SUNMIN: the luminance below which the key light is dark (default 2; a huge value = a control of the no-sun path) */
        if (smin < 0.0f) { const char *e = getenv("RG_RT_SUNMIN"); smin = e && *e ? (float)atof(e) : 2.0f; }
        const float lum = 0.299f * c[0] + 0.587f * c[1] + 0.114f * c[2];
        rt_sun_ok = lum >= smin;
        rt_sun_n++;
        /* (rt6) the key lights' luminance census (exit line "rg rt sun census") */
        rt_sunlum[lum < 2.0f ? 0 : lum < 8.0f ? 1 : lum < 32.0f ? 2 : lum < 64.0f ? 3 : lum < 128.0f ? 4 : 5]++;
        if (lum < rt_sunlum_min) rt_sunlum_min = lum;
        if (lum > rt_sunlum_max) rt_sunlum_max = lum;
    }
    /* a native mesh draw: collect it as a caster; true = draw it as a receiver */
    bool rt_classify(const GpuNrDraw &g, const gpu_nr_draw *d, NrMeshBuf *mb, NrTex *tx)
    {
        uint32_t var, fl;
        memcpy(&var, &g.cb[22][0], 4);
        memcpy(&fl, &g.cb[23][0], 4);
        /* a newer game frame: the TLAS of the instances collected so far (the frame before);
         * older frames' draws (interpolated replays) only read */
        /* (RT2d prepass: the present's casters only, at its rows; during the present's draws the
         * casters are its own already: receivers only) */
        const bool stale = rt_pass_on || (!rt_prepass && d->rt_frame && rt_cur && (int32_t)(d->rt_frame - rt_cur) < 0);
        if (!rt_prepass && d->rt_frame && (!rt_cur || (int32_t)(d->rt_frame - rt_cur) > 0)) {
            if (rt_cur) rt_frame();
            rt_cur = d->rt_frame;
            rt_pass_new();
        }
        if (rt_class < 0) { const char *e = getenv("RG_RT_CLASS"); rt_class = e && e[0] == '1'; }
        if (d->rt_ok == GPU_NR_RT_MAGIC && !stale && !rt_prepass) {
            const float *A = d->rt[8], *L = d->rt[4];
            if (rt_sunsrc == 1 && A[3] > 0.5f && A[0] * A[0] + A[1] * A[1] + A[2] * A[2] > 1e-6f) {
                rt_take_sun(&d->rt[8], 1);
                rt_sun_area_frame = d->rt_frame;
                rst.sun_area++;
            } else if ((var & 0x80u) && L[0] * L[0] + L[1] * L[1] + L[2] * L[2] > 1e-6f &&
                       (rt_sun_kind != 1 || (uint32_t)(d->rt_frame - rt_sun_area_frame) > 8u)) {
                rt_take_sun(&d->rt[4], 2);
                rst.sun_lit++;
            }
        }
        if (rt_class && g.depth_rt >= 0 && g.rt_w >= rt_minw)
            rt_hist[(uint32_t)(g.abe ? 1 : 0) | (g.zwrite ? 2u : 0u) | ((fl & 4u) ? 4u : 0u) | (g.tme ? 8u : 0u) |
                    ((g.alpha_abcd & 0xFFu) << 8) | ((var & 0x1FFFu) << 16)]++;   /* (rt6: 0x1FFF, the reflection-map kind 0x1000 was cut off) */
        enum { V_SKIN = 1, V_SCROLL = 2, V_VCOL = 4, V_ZSCALE = 8, V_ENVMAP = 64, V_LIGHT = 128, V_REFRACT = 1024, V_IM = 2048, V_REFLECT = 4096,
               F_ATE = 4, F_TCC = 16, F_CT24 = 0x200, F_CT16 = 0x2000 };
        if (var & (V_REFRACT | V_IM)) { rst.sk_var++; return false; }
        /* RT2c: characters (the composite's Z-scale parts, drawn into the work buffer at their frame
         * coordinates, and directly drawn skinned meshes) cast (posed on the CPU, rt_dynp) and
         * receive; $RG_RT_CHARS=0: neither (RT2: the Z-scale parts were skipped) */
        const bool chr = (var & (V_ZSCALE | V_SKIN)) || d->nbones_rows;
        if (chr && !rt_chars) { rst.sk_var++; return false; }
        if (rt_dynlog < 0) { const char *e = getenv("RG_RT_DYNLOG"); rt_dynlog = e ? atol(e) : 0; }
        if (chr && rt_dynlog && (long)d->rt_frame >= rt_dynlog && (long)d->rt_frame < rt_dynlog + 2) {
            /* $RG_RT_DYNLOG=FRAME: the character draws of that record frame and the next */
            std::vector<float> wp((size_t)d->mesh.nvtx * 3);
            float lo[3] = { 1e30f, 1e30f, 1e30f }, hi[3] = { -1e30f, -1e30f, -1e30f };
            if (rt_pose(d, (var & V_SKIN) != 0, wp.data()))
                for (size_t i = 0; i < wp.size(); i++) { lo[i % 3] = fminf(lo[i % 3], wp[i]); hi[i % 3] = fmaxf(hi[i % 3], wp[i]); }
            fprintf(stderr, "rg rt chr: frame %u mesh %u var %03x nv %u tris %u rt %d %dx%d depth %d zw %d abe %d alpha %02x bones %d "
                            "world %.0f..%.0f %.0f..%.0f %.0f..%.0f obj %.1f %.1f %.1f\n",
                    d->rt_frame, d->mesh.id, var & 0xFFFu, d->mesh.nvtx, d->mesh.nidx / 3, g.color_rt, g.rt_w, g.rt_h, g.depth_rt, g.zwrite,
                    g.abe, g.alpha_abcd & 0xFFu, d->nbones_rows, lo[0], hi[0], lo[1], hi[1], lo[2], hi[2], d->rt[3][0], d->rt[3][1], d->rt[3][2]);
        }
        if (g.depth_rt < 0 || g.rt_w < rt_minw) { rst.sk_target++; return false; }
        if (chr) rst.sk_skin++;
        /* (rt5) a reflective draw (RT3 spike): the art's environment / reflection map (kinds 0x43EA30,
         * 0x43F100), whatever its blend: its texel becomes the ray-traced reflection where the ray
         * hits the scene (nr_draw.hlsl nr_rt_refl); not a shadow receiver unless it is one below */
        const bool rdraw1 = rt_refl && (rt_rclass & 1) && g.tme && (var & (V_ENVMAP | V_REFLECT));
        /* (rt5) water: a blended map layer without Z write with the UV-scroll kind (a sea / lake /
         * pool / puddle surface; the shader keeps level pixels only, not waterfalls); the hit
         * blends in by a Fresnel term */
        /* (rt6) $RG_RT_WATER_SEL=varmask,varval,abe,zwrite,tme (hex mask / value of the variant bits; -1 =
         * any): which draws the water class takes (investigation: with $RG_RT_REFLDBG=1 a class's pixels
         * show cyan / red); default 2,2,1,0,1 = rt5's (UV scroll, blended, no Z write, textured) */
        static int wsel[5] = { -2, 0, 0, 0, 0 };
        if (wsel[0] == -2) {
            int v[5] = { 2, 2, 1, 0, 1 };
            const char *e = getenv("RG_RT_WATER_SEL");
            if (e) sscanf(e, "%x,%x,%d,%d,%d", &v[0], &v[1], &v[2], &v[3], &v[4]);
            memcpy(wsel, v, sizeof v);
        }
        const bool wsel_ok = ((int)(var & (uint32_t)wsel[0]) == wsel[1]) && (wsel[2] < 0 || (int)g.abe == wsel[2]) &&
                             (wsel[3] < 0 || (int)g.zwrite == wsel[3]) && (wsel[4] < 0 || (int)g.tme == wsel[4]);
        const bool rdraw2 = rt_refl && (rt_rclass & 2) && !rdraw1 && !chr && wsel_ok;   /* (level surfaces only: nr_rt_refl_water's normal test) */
        const bool rdraw = rdraw1 || rdraw2;
        rt_rmode = 0;
        rt_rshadow = true;
        if (rdraw) {
            /* (rt6) $RG_RT_REFLLOG=N: the first N reflective draws' fog row (R[9]) and fog-enable bit */
            static long rl = -2;
            if (rl == -2) { const char *e = getenv("RG_RT_REFLLOG"); rl = e ? atol(e) : 0; }
            if (rl > 0) {
                rl--;
                uint32_t fcol;
                memcpy(&fcol, &g.cb[23][2], 4);
                fprintf(stderr, "rg rt refl draw: var %04x abe %d zw %d alpha %02x fge %u fog %.2f %.4f (clamp %.0f..%.0f) fogcol %06x\n", var & 0x1FFFu, (int)g.abe,
                        (int)g.zwrite, g.alpha_abcd & 0xFFu, (fl >> 1) & 1u, g.cb[9][0], g.cb[9][3], g.cb[9][2], g.cb[9][1], fcol & 0xFFFFFFu);
            }
        }
        auto refl_only = [&]() -> bool {
            if (!rdraw || stale || rt_prepass || !rt_tlas.as || rt_tlas_stale) return false;
            rt_rmode = rdraw1 ? 1 : 2;
            if (rdraw2) rst.recv_water++;
            rt_rshadow = false;
            rt_rchr = chr;
            rt_rnosun = !rt_sun_ok;
            rst.recv_refl++;
            return true;
        };
        /* (the census, RG_RT_CLASS=1: every map draw has the alpha test on and most blend
         * (Cs - Cd) As + Cd with Z write: the art's solid geometry; translucent layers do not
         * write Z; additive / other blends are effects) */
        const uint32_t ab = g.alpha_abcd & 0xFFu;
        const bool plain = !g.abe || ab == 0x44u || (ab & 3u) == ((ab >> 2) & 3u);
        if (!plain || !g.zwrite) { rst.sk_blend++; return refl_only(); }
        /* blended with (Cs - Cd) As + Cd: a caster only when the material x vertex alpha is opaque
         * (>= 0x78 of 0x80; the transporter's light beams are Z-writing, alpha-blended meshes) */
        bool solid = true;
        if (g.abe && ab == 0x44u) {
            if (mb->amin < 0) {
                int a = 255;
                const uint8_t *v = (const uint8_t *)d->mesh.vtx;
                for (uint32_t i = 0; v && d->mesh.stride == 28 && i < d->mesh.nvtx; i++) a = v[28 * i + 19] < a ? v[28 * i + 19] : a;
                mb->amin = a;
            }
            float ea = ((var & 0x80u) ? g.cb[21][3] : g.cb[7][3]) * ((var & 4u) ? (float)mb->amin / 128.0f : 1.0f);
            solid = ea >= 120.0f;
            /* a scrolling texture on a blended mesh (UV scroll kind with a non-zero offset): an effect
             * (light beams, glows, water), not geometry */
            if ((var & 2u) && (g.cb[6][2] != 0.0f || g.cb[6][3] != 0.0f)) solid = false;
        }
        uint32_t at;
        memcpy(&at, &g.cb[23][1], 4);
        if ((fl & F_ATE) && (at & 7u) == 0u) solid = false;   /* ATST NEVER (AFAIL KEEP): draws nothing */
        {
            /* $RG_RT_SKIP=id,id,..: these mesh ids never cast (classification work) */
            static std::vector<uint32_t> skip;
            static int init = 0;
            if (!init) {
                init = 1;
                const char *e = getenv("RG_RT_SKIP");
                for (const char *q = e; q && *q;) { skip.push_back((uint32_t)strtoul(q, (char **)&q, 10)); if (*q == ',') q++; else break; }
            }
            for (uint32_t s : skip) if (s == d->mesh.id) solid = false;
        }
        if (stale) {
            rst.sk_stale++;
        } else if (!solid) {
            rst.sk_ate++;
        } else {
            /* caster: object matrix x position scale (the SNORM fetch is int16 / 32767) */
            RtInst in;
            memset(&in, 0, sizeof in);
            in.mesh = d->mesh.id;
            const float k = 32767.0f / 32768.0f;
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) in.m[4 * r + c] = d->rt[c][r] * d->cb[4][c] * k;
                in.m[4 * r + 3] = d->rt[3][r];
            }
            /* (rt5) reflections: the hit's colour (texture, vertex colour, material colour) */
            if (rt_refl) {
                RtAlpha *rc = tx && g.tme && !(var & (V_ENVMAP | V_REFLECT)) && !(g.tex_rt >= 0) ? rt_alpha_get(tx) : NULL;
                in.rgen = rc ? tx->rtgen : 0;
                in.rfl = (((at >> 16) & 3u) << 16) | ((var & V_VCOL) ? 1u << 19 : 0u) | (g.clamp_u ? 1u << 20 : 0u) |
                         (g.clamp_v ? 1u << 21 : 0u) | (rc ? 1u << 26 : 0u);
                in.uvs[0] = g.cb[6][0];
                in.uvs[1] = g.cb[6][1];
                in.uvs[2] = (var & V_SCROLL) ? g.cb[6][2] : 0.0f;
                in.uvs[3] = (var & V_SCROLL) ? g.cb[6][3] : 0.0f;
                float mc4[4];
                for (int k = 0; k < 4; k++)   /* (lit meshes: ambient + light 0, a stand-in for N.L) */
                    mc4[k] = (var & V_LIGHT) ? g.cb[21][k] + (k < 3 ? 0.7f * g.cb[17][k] : 0.0f) : g.cb[7][k];
                in.mcol = 0;
                for (int k = 0; k < 4; k++) in.mcol |= (uint32_t)fminf(fmaxf(mc4[k], 0.0f), 255.0f) << (8 * k);
            }
            /* RT2b: an alpha-tested material with its texture's alpha (the GS rule in the candidate
             * loop): a texture from the decode cache, alpha from the texels (TCC), UVs from the mesh
             * (not the environment / reflection kinds) */
            const uint32_t atst = at & 7u;
            if (rt_alpha_on && tx && g.tme && (fl & F_ATE) && (fl & F_TCC) && !(fl & (F_CT24 | F_CT16)) && atst != 1u &&
                !(var & (V_ENVMAP | V_REFLECT))) {
                RtAlpha *ra = rt_alpha_get(tx);
                if (ra) {
                    in.tgen = tx->rtgen;
                    in.mfl = atst | (((at >> 8) & 255u) << 8) | (((at >> 16) & 3u) << 16) | ((var & V_VCOL) ? 1u << 19 : 0u) |
                             (g.clamp_u ? 1u << 20 : 0u) | (g.clamp_v ? 1u << 21 : 0u) | (g.lin ? 1u << 23 : 0u);
                    in.uvs[0] = g.cb[6][0];
                    in.uvs[1] = g.cb[6][1];
                    in.uvs[2] = (var & V_SCROLL) ? g.cb[6][2] : 0.0f;
                    in.uvs[3] = (var & V_SCROLL) ? g.cb[6][3] : 0.0f;
                    in.ma = (var & V_LIGHT) ? g.cb[21][3] : g.cb[7][3];
                    in.mc = g.cb[8][3];
                    if ((var & V_VCOL) && mb->amin < 0) {
                        int a = 255;
                        const uint8_t *v = (const uint8_t *)d->mesh.vtx;
                        for (uint32_t i = 0; v && d->mesh.stride == 28 && i < d->mesh.nvtx; i++) a = v[28 * i + 19] < a ? v[28 * i + 19] : a;
                        mb->amin = a;
                    }
                    in.vamin = floorf(fminf(in.ma * ((var & V_VCOL) ? (float)mb->amin / 128.0f : 1.0f), in.mc));
                }
            }
            if (chr) in.pad = 1.0f;   /* (a character part: never sticky, mask 4 / 8) */
            uint64_t h = 1469598103934665603ull;
            const uint8_t *pb = (const uint8_t *)&in;
            for (size_t i = 0; i < sizeof in; i++) { h ^= pb[i]; h *= 1099511628211ull; }
            if (chr && (var & V_SKIN)) {
                /* RT2c: posed on the CPU (the bones and object rows are part of the key); only the
                 * recorded draws (an interpolated replay's rows are a present's, rt_frame 0: RT2d) */
                const uint8_t *pq = (const uint8_t *)d->rt;
                for (size_t i = 0; i < sizeof d->rt[0] * 4; i++) { h ^= pq[i]; h *= 1099511628211ull; }
                pq = (const uint8_t *)d->bones;
                for (size_t i = 0; i < sizeof d->bones; i++) { h ^= pq[i]; h *= 1099511628211ull; }
                if ((d->rt_frame || rt_prepass) && d->mesh.nvtx && d->mesh.nidx >= 3 && rt_seen.insert(h).second) {
                    for (int r = 0; r < 3; r++)
                        for (int c = 0; c < 4; c++) in.m[4 * r + c] = r == c ? 1.0f : 0.0f;
                    RtDynPend p;
                    p.in = in;
                    p.off = rt_dynpos.size();
                    p.nv = d->mesh.nvtx;
                    rt_dynpos.resize(p.off + (size_t)p.nv * 3);
                    if (rt_pose(d, true, &rt_dynpos[p.off])) {
                        rt_dynp.push_back(p);
                        rst.cast++;
                        rst.cast_chr++;
                    } else {
                        rt_dynpos.resize(p.off);
                    }
                } else {
                    rst.cast_dup++;
                }
            } else if (rt_seen.insert(h).second) {
                rt_inst.push_back(in);
                rt_keys.push_back(h);
                rst.cast++;
                if (in.tgen) rst.cast_alpha++;
                /* $RG_RT_LOG=FRAME: the casters of that record frame (classification work) */
                static long logf = -2;
                if (logf == -2) { const char *e = getenv("RG_RT_LOG"); logf = e ? atol(e) : -1; }
                if (logf >= 0 && d->rt_frame == (uint32_t)logf) {
                    float ylo = 1e30f, yhi = -1e30f;   /* the mesh's world Y range (rotation ignored) */
                    const int16_t *v = (const int16_t *)d->mesh.vtx;
                    for (uint32_t i = 0; v && d->mesh.stride == 28 && i < d->mesh.nvtx; i++) {
                        float y = v[14 * i + 1] / 32768.0f * d->cb[4][1] * d->rt[1][1] + d->rt[3][1];
                        ylo = y < ylo ? y : ylo; yhi = y > yhi ? y : yhi;
                    }
                    fprintf(stderr, "rg rt caster: y %.0f..%.0f mesh %u tris %u var %03x abe %d alpha %02x tfx %u tcc %u fl %05x at %08x alpha-tested %d origin %.1f %.1f %.1f scale %.1f %.1f %.1f\n",
                            ylo, yhi, d->mesh.id, d->mesh.nidx / 3, var & 0xFFFu, g.abe, g.alpha_abcd & 0xFFu, (at >> 16) & 3u, (fl >> 4) & 1u, fl & 0xFFFFFu,
                            at, in.tgen ? 1 : 0, d->rt[3][0], d->rt[3][1], d->rt[3][2], d->cb[4][0], d->cb[4][1], d->cb[4][2]);
                }
            } else {
                rst.cast_dup++;
            }
        }
        if (rt_prepass) return false;
        if (!rt_tlas.as || rt_tlas_stale) { rst.sk_stale++; return false; }
        /* (rt5) without a sun (night, unlit interiors) a receiver traces ambient occlusion only
         * (graphics.raytracing = shadows + AO): rt_cb gives it no light direction */
        rt_rnosun = !rt_sun_ok;
        rt_rmode = rdraw1 ? 1 : rdraw2 ? 2 : 0;
        if (rdraw) rst.recv_refl++;
        if (rdraw2) rst.recv_water++;
        if (!rt_sun_ok && !(rt_ao && rt_ao_nosun) && !emi_ln) {   /* (rt8: emissive lights receive without a sun) */
            rst.sk_nolight++;
            if (rt_sun_kind) rst.sun_dark++;
            if (!rdraw) return false;
            rt_rshadow = false;   /* (a reflective draw without a sun: the reflection only) */
        }
        if (rt_rnosun) rst.recv_aoonly++;
        rt_rchr = chr;
        if (chr) rst.recv_skin++;
        rst.recv++;
        return true;
    }
    /* the receiver's constants (nr_draw.hlsl NrRT) */
    enum { RT_CB_ROWS = 38 };   /* (rt8: row 29 RTI, emissive lights; rt9: rows 30-33 RTWP, 34 RTMV, 35 RTN, 36 RTO, 37 RTJ) */
    void rt_cb(const gpu_nr_draw *d, float o[RT_CB_ROWS][4])
    {
        memset(o, 0, RT_CB_ROWS * 16);
        memcpy(o[0], d->rt, 4 * 16);
        const float *L = rt_sun[0];
        float l = sqrtf(L[0] * L[0] + L[1] * L[1] + L[2] * L[2]);
        /* (rt5) no sun: a zero direction (no face is sun-facing: nr_rt_shade's AO-only path) */
        for (int k = 0; k < 3; k++) o[4][k] = rt_rnosun || !(l > 0.0f) ? 0.0f : (rt_lastL[k] = L[k] / l);
        o[4][3] = rt_rshadow ? 1.0f : 0.0f;   /* (rt5: 0 = no shadow / AO term: a reflective draw only) */
        for (int k = 0; k < 3; k++) {
            /* a shadowed pixel keeps the ambient's share of ambient + the key light (true to the
             * light set), clamped; RG_RT_SHADE = a fixed multiplier */
            float a = rt_sun[2][k], c = rt_sun[1][k], m = a + c > 0.0f ? a / (a + c) : 0.6f;
            if (m < rt_smin) m = rt_smin;
            if (m > rt_smax) m = rt_smax;
            m = rt_sfix >= 0.0f ? rt_sfix : m;
            o[5][k] = 1.0f - (1.0f - m) * rt_kstr;   /* (faded in enclosed scenes) */
        }
        o[5][3] = 1.0f;
        o[6][0] = rt_len;
        o[6][1] = rt_off;
        o[6][2] = rt_offd;
        o[6][3] = rt_dbg ? (getenv("RG_RT_DBGMV") ? 5.0f : getenv("RG_RT_DBGHIST") ? 4.0f : getenv("RG_RT_DBGVIS") ? 3.0f : getenv("RG_RT_DBGID") ? 2.0f : 1.0f) : 0.0f;
        memcpy(o[7], d->rt[7], 16);
        /* RT2b / soft shadows: the material table's address, rays per pixel, the light's radius */
        const VkDeviceAddress ma = rt_pass_on ? rt_pmbuf_addr : rt_mbuf_addr;
        uint32_t lo = (uint32_t)ma, hi = (uint32_t)(ma >> 32);
        memcpy(&o[8][0], &lo, 4);
        memcpy(&o[8][1], &hi, 4);
        o[8][2] = (float)rt_rays;
        o[8][3] = rt_cone;
        {
            /* the enclosure counters' slot of this game frame (-1: none) */
            const int k = (int)(rst.frames % RT_STAT_SLOTS);
            o[9][0] = rt_stat.b ? (float)k : -1.0f;
        }
        o[9][1] = rt_alpha_on == 3 ? 1.0f : rt_alpha_on == 2 ? 2.0f : 0.0f;   /* 3: control, alpha-tested candidates never hit; 2: bilinear alpha */
        o[9][2] = rt_fnear;   /* foliage: a cut-out hit this far along the ray shadows fully, */
        o[9][3] = rt_ffar;    /* fading to nothing at this distance (0: no fade) */
        /* RT2c: the trace masks (map opaque 1, cut-out 2; characters 4, 8).  A character receiver
         * does not trace characters while their instances are a frame old (self-shadow of the last
         * pose); a present's own TLAS (RT2d) has them at this pose */
        const bool chr_ok = !rt_rchr || rt_pass_on;
        o[10][0] = chr_ok ? 5.0f : 1.0f;
        o[10][1] = chr_ok ? 10.0f : 2.0f;
        o[10][2] = rt_rchr ? 3.0f : 15.0f;   /* (rt5) a reflection ray's mask: a character part's sees the map only (its own last pose would mirror itself) */
        /* RT2f: the penumbra filter (history images of this present and the previous one, its camera) */
        rt_vp_take(d);
        const bool hf = rt_filt && rt_hist_ok;
        o[11][0] = hf ? 1.0f : 0.0f;
        o[11][1] = (float)scale;
        o[11][2] = (float)(rt_npres % 1024);
        {
            /* (rt4) one map trace per 2 x 2 pixel quad from internal resolution $RG_RT_QUAD up (default
             * 3; 0 off): nr_draw.hlsl nr_rt_shade, RTH.w bit 6 */
            static int rq = -1;
            if (rq < 0) { const char *e = getenv("RG_RT_QUAD"); rq = e && *e ? atoi(e) : 3; }
            const bool quad = rq > 0 && scale >= rq && !rt_dbg;
            o[11][3] = (float)((rt_half ? 1 : 0) | (rt_fexp << 1) | (rt_half >= 2 ? 32 : 0) | (quad ? 64 : 0));
        }
        if (hf && rt_vp_prev_ok) {
            for (int k = 0; k < 3; k++) o[12][k] = rt_cam_prev[k];
            o[12][3] = 1.0f;
            memcpy(o[13], rt_vp_prev, sizeof rt_vp_prev);
        }
        memcpy(o[17], rt_pass_on ? rt_pcsph : rt_csph, sizeof rt_csph);   /* the characters' spheres (r 0: none) */
        /* RT2e: ambient occlusion (graphics.raytracing = shadows + AO, $RG_RT_AO) */
        o[25][0] = rt_ao ? rt_aolen : 0.0f;
        /* (rt5) interiors / night (no sun, or the enclosure fade below half): their own strength
         * against the baked interior light ($RG_RT_AO_IN); the sunlit faces' share fades with the
         * enclosure (an enclosed place has no real sunlit faces) */
        const bool inside = rt_rnosun || (rt_encl_on && rt_kstr < 0.5f);
        o[25][1] = inside ? rt_aostr_in : rt_aostr;
        o[25][2] = rt_ao ? 2.0f : 1.0f;
        o[25][3] = getenv("RG_RT_AODBG") ? -1.0f : 1.0f + (rt_aolit - 1.0f) * (rt_encl_on ? rt_kstr : 1.0f);   /* (rt4) AO share on sunlit faces; < 0: the AO debug view */
        /* (rt5) reflections (nr_draw.hlsl RTR): x 1 = this draw's environment / reflection map texel
         * becomes the reflection's hit, y strength, z ray length, w bit 0 one ray per 2 x 2 quad */
        o[26][0] = (float)rt_rmode;
        o[26][1] = rt_rstr;
        o[26][2] = rt_rlen;
        {
            static int rq = -1;
            if (rq < 0) { const char *e = getenv("RG_RT_REFL_QUAD"); rq = e && *e ? atoi(e) : 3; }
            static int rdbg = -1;
            if (rdbg < 0) { const char *e = getenv("RG_RT_REFLDBG"); rdbg = e && e[0] == '1'; }
            o[26][3] = (float)((rq > 0 && scale >= rq && !rt_dbg ? 1 : 0) | (rdbg ? 2 : 0));   /* (bit 1: $RG_RT_REFLDBG=1, the reflections' debug colours only: cyan hit, red miss) */
        }
        /* (rt6) nr_draw.hlsl RTF: the hit's fog, the distance fade's start, smooth normals */
        o[27][0] = rt_rfog ? 1.0f : 0.0f;
        o[27][1] = rt_rfade;
        o[27][2] = rt_rsmooth ? 1.0f : 0.0f;
        {
            /* (rt6) the hit's fog distance: clip w per unit of eye distance, from the map draws (a
             * character part's own projection is the composite's work buffer, not the scene's) */
            if (!rt_rchr) {
                const float dx = d->rt[3][0] - d->rt[7][0], dy = d->rt[3][1] - d->rt[7][1], dz = d->rt[3][2] - d->rt[7][2];
                const float de = sqrtf(dx * dx + dy * dy + dz * dz), w0 = d->cb[3][3];
                if (de > 50.0f && w0 > 0.0f && w0 / de < 100.0f) rt_fk = rt_fk > 0.0f ? rt_fk + (w0 / de - rt_fk) * 0.1f : w0 / de;
            }
            o[27][3] = rt_fk;
        }
        {
            /* (rt7) nr_draw.hlsl RTG.x: the reflection's brightness floor, interiors -> open places by
             * the enclosure fade (rt_kstr 1 open, 0 enclosed; no sun = an interior) */
            const float k = rt_rnosun ? 0.0f : rt_encl_on ? rt_kstr : 1.0f;
            float f = rt_rfloor_in + (rt_rfloor_out - rt_rfloor_in) * k;
            o[28][0] = f < 0.0f ? 0.0f : f > 1.0f ? 1.0f : f;
            /* (rt7) one AO ray per 2 x 2 quad on map receivers from internal resolution $RG_RT_AO_QUAD up (default 3; 0 off) */
            static int aq = -1;
            if (aq < 0) { const char *e = getenv("RG_RT_AO_QUAD"); aq = e && *e ? atoi(e) : 3; }
            /* (not on a character part: it moves, its history rarely settles, and a shared ray per quad
             * showed as a 2 x 2 mesh on the skin -- shots/aoquad_ctx.png) */
            o[28][1] = aq > 0 && scale >= aq && !rt_dbg && !rt_rchr ? 1.0f : 0.0f;
            static int ax = -1;
            if (ax < 0) { const char *e = getenv("RG_RT_AOEXP"); ax = e && *e ? atoi(e) & 3 : 0; }
            o[28][2] = (float)ax;   /* (measurement: 1 no AO ray, 2 no AO history) */
            static int h2 = -1;
            if (h2 < 0) { const char *e = getenv("RG_RT_HIST2"); h2 = !(e && e[0] == '0'); }
            o[28][3] = h2 ? 1.0f : 0.0f;   /* (rt7) the shadow's and AO's history words in one read (nr_draw.hlsl nr_rt_hist2) */
        }
        /* (rt8) nr_draw.hlsl RTI: the emissive lights (xy the list's device address, z count: 0 for a draw
         * that is itself emissive, w bits: 1 debug view = the added light only) */
        if (emi_ln && !emi_self) {
            uint32_t lo2 = (uint32_t)emi_laddr, hi2 = (uint32_t)(emi_laddr >> 32);
            memcpy(&o[29][0], &lo2, 4);
            memcpy(&o[29][1], &hi2, 4);
            o[29][2] = (float)emi_ln;
            o[29][3] = (float)(emi_dbg ? 1 : 0);
            /* (rt9) RTJ: the lights that reach this draw (emi_mask), the quad sharing from internal
             * resolution $RG_EMI_QUAD up (default 2; 0 off) */
            const uint64_t m = emi_mask(d);
            const uint32_t mlo = (uint32_t)m, mhi = (uint32_t)(m >> 32);
            memcpy(&o[37][0], &mlo, 4);
            memcpy(&o[37][1], &mhi, 4);
            if (emi_quad < 0) { const char *e = getenv("RG_EMI_QUAD"); emi_quad = e && *e ? atoi(e) : 2; }
            o[37][2] = emi_quad > 0 && scale >= emi_quad && !emi_dbg ? 1.0f : 0.0f;
            o[37][3] = emi_ln > 64 || !emi_cull ? 1.0f : 0.0f;
        }
        {
            /* (rt8) $RG_RT_CHRPAT=0: rt7's character receivers (AO, jittered shadow ray; the halftone pattern) */
            static int cp = -1;
            if (cp < 0) { const char *e = getenv("RG_RT_CHRPAT"); cp = !(e && e[0] == '0'); }
            if (!cp) o[29][3] = (float)((int)o[29][3] | 2);
        }
    }
    /* (rt9) motion vectors of moving receivers (docs/RAYTRACING.md "RT9"): a character part's previous
     * present's object rows and bones (by mesh id and its occurrence among this present's character
     * receivers), so nr_draw.hlsl reprojects its history from where the same surface point was and the
     * character gets its AO and soft shadow back.  $RG_RT_MV=bits[,tol fraction[,tol units[,AO rays[,least
     * weight]]]]: bit 0 on (0 = rt8: no AO, hard shadow on characters), bit 1 the quad average of the noisy
     * terms, bit 2 the characters' AO rays see the characters too, bit 3 (measurement: the reference of
     * tools/rt/rt_ghost.py) every receiver traces RTN.z AO rays; $RG_RT_CHRPAT=1 = rt8, =0 = rt7.
     * Returns true when rt_mvb holds the previous bones (bound as b3). */
    struct RtMvEnt { uint64_t pres; bool sk; float w[4][4]; float b[256][4]; };
    std::unordered_map<uint64_t, RtMvEnt> rt_mvm;
    std::unordered_map<uint32_t, uint32_t> rt_mvocc;
    uint64_t rt_mvocc_p = ~0ull;
    float rt_mvb[256][4];
    int rt_mvmode = -1;
    float rt_mvp[4] = { 0.01f, 1.0f, 2.0f, 0.1f };
    float rt_mvclamp = 0.05f;   /* ($RG_RT_MV_CLAMP: the history clamp's margin, bit 4) */
    int rt_mvsr = 1;            /* ($RG_RT_MV_RAYS: a moving character part's shadow rays per pixel) */
    uint64_t rt_mvst[3] = {};   /* moving receivers drawn: with the previous pose, without (first present), skinned */
    bool rt_mv_rows(const gpu_nr_draw *d, float o[RT_CB_ROWS][4])
    {
        if (rt_mvmode < 0) {
            rt_mvmode = 3;
            const char *e = getenv("RG_RT_MV");
            if (e && *e) {
                float v[4] = { rt_mvp[0], rt_mvp[1], rt_mvp[2], rt_mvp[3] };
                int b = 3;
                sscanf(e, "%d,%f,%f,%f,%f", &b, &v[0], &v[1], &v[2], &v[3]);
                rt_mvmode = b;
                memcpy(rt_mvp, v, sizeof v);
            }
            if ((e = getenv("RG_RT_MV_CLAMP")) && *e) rt_mvclamp = (float)atof(e);
            if ((e = getenv("RG_RT_MV_RAYS")) && *e) rt_mvsr = atoi(e);
            const char *c = getenv("RG_RT_CHRPAT");
            if (c && (c[0] == '0' || c[0] == '1')) rt_mvmode = 0;
        }
        if (!rt_rchr && (rt_mvmode & 8)) { o[34][3] = 8.0f; memcpy(o[35], rt_mvp, sizeof rt_mvp); }   /* (measurement: every receiver RTN.z AO rays) */
        if (!rt_rchr || !(rt_mvmode & 1) || !rt_filt || !rt_hist_ok) return false;
        if (rt_mvocc_p != rt_npres) {
            rt_mvocc.clear();
            rt_mvocc_p = rt_npres;
            for (auto it = rt_mvm.begin(); it != rt_mvm.end();) it = it->second.pres + 8 < rt_npres ? rt_mvm.erase(it) : std::next(it);
        }
        const uint64_t key = ((uint64_t)d->mesh.id << 32) | rt_mvocc[d->mesh.id]++;
        const bool sk = d->nbones_rows > 0;
        bool pb = false;
        o[34][0] = 1.0f;
        o[34][3] = (float)(rt_mvmode & 63);
        memcpy(o[35], rt_mvp, sizeof rt_mvp);
        o[36][0] = rt_mvclamp;
        o[36][1] = (float)rt_mvsr;
        auto it = rt_mvm.find(key);
        if (it != rt_mvm.end() && it->second.pres + 1 == rt_npres && it->second.sk == sk) {
            memcpy(o[30], it->second.w, sizeof it->second.w);
            if (sk) { memcpy(rt_mvb, it->second.b, sizeof rt_mvb); o[34][1] = 1.0f; pb = true; }
            rt_mvst[0]++;
        } else {
            memcpy(o[30], d->rt, 4 * 16);
            o[34][2] = 1.0f;   /* (no previous pose: no history) */
            rt_mvst[1]++;
        }
        if (sk) rt_mvst[2]++;
        if (it == rt_mvm.end() || it->second.pres != rt_npres) {
            RtMvEnt &e = rt_mvm[key];
            e.pres = rt_npres;
            e.sk = sk;
            memcpy(e.w, d->rt, sizeof e.w);
            if (sk) memcpy(e.b, d->bones, sizeof e.b);
        }
        return pb;
    }

    bool nr_draw(const GpuNrDraw &g) override
    {
        if (!nr_ok) return false;
        Target &ct = targets[g.color_rt];
        Target *zt = g.depth_rt >= 0 ? &targets[g.depth_rt] : NULL;
        const bool zr = zt && !zt->dsv;
        if (zr && (!sh_ps_nr_z.m || !zt->uv)) return false;
        if (g.crov && (!g.im || !ct.uv || (zr ? !sh_ps_nr_cz.m : (!sh_ps_nr_c.m || zt)))) return false;
        const gpu_nr_draw *d = g.d;
        NrMeshBuf *mb = NULL;
        if (!g.im) {
            mb = nr_mesh_get(d->mesh);
            if (!mb) return false;
        } else if (!g.nim) {
            return false;
        }
        /* texture (may record a decode / copy: before the rendering instance) */
        VkImageView tview = VK_NULL_HANDLE;
        VkSampler tsmp = VK_NULL_HANDLE;
        NrTex *rtx = NULL;   /* ray tracing: an alpha-tested caster's texture (RT2b) */
        if (g.tme && g.tex_rt >= 0) {
            if (g.tex_snap) {
                snapshot_rect(ct, g.tex_rect);
                tview = ct.snap_view;
            } else {
                tview = targets[g.tex_rt].view;
            }
            if (!tview) return false;
            tsmp = smp_nr[g.lin ? 1 : 0][1][1];
        } else if (g.tme) {
            uint64_t q0 = prof ? pts() : ~0ull;
            uint64_t nd0 = n_nr_tex;
            NrTex *tx = nr_tex_get(g);
            rtx = tx;
            if (prof && n_nr_tex != nd0)
                pev_add(PC_DECODE, q0, (double)(g.dec_rect.x1 - g.dec_rect.x0) * (g.dec_rect.y1 - g.dec_rect.y0));
            if (!tx) return false;
            tview = tx->img.v;
            tsmp = smp_nr[g.lin ? 1 : 0][g.clamp_u ? 1 : 0][g.clamp_v ? 1 : 0];
            if (g.aniso > 1 && aniso_ok) {
                int a = g.aniso >= 16 ? 3 : g.aniso >= 8 ? 2 : g.aniso >= 4 ? 1 : 0;
                tsmp = smp_nr_an[a][g.clamp_u ? 1 : 0][g.clamp_v ? 1 : 0];
            }
            if (g.rep && tx == nr_rep_last && smp_rep[0][0][0]) {
                /* an HD replacement: its mip chain (nr_rep_get) */
                int a = g.aniso >= 16 ? 3 : g.aniso >= 8 ? 2 : g.aniso >= 4 ? 1 : 0;
                VkSampler sa = g.aniso > 1 && aniso_ok ? smp_rep_an[a][g.clamp_u ? 1 : 0][g.clamp_v ? 1 : 0] : VK_NULL_HANDLE;
                tsmp = sa ? sa : smp_rep[g.lin ? 1 : 0][g.clamp_u ? 1 : 0][g.clamp_v ? 1 : 0];
            }
        }
        if (emi.any()) emi_draw(g, d, rtx);   /* (rt8) census / emitters */
        /* immediate vertices into the ring */
        RA vra = { VK_NULL_HANDLE, 0, NULL };
        if (g.im) {
            vra = ring_put(g.im, (VkDeviceSize)g.nim * sizeof(GpuImVtx), 16);
            if (!vra.p) return false;
        }
        /* constants */
        float cbv[26][4];
        memcpy(cbv, g.cb, sizeof cbv);
        {
            uint32_t zc = (uint32_t)(zt ? g.zfunc : GZ_OFF) | (zt && g.zwrite ? 16u : 0u);
            memcpy(&cbv[23][3], &zc, 4);
        }
        /* ray tracing (docs/RAYTRACING.md): a caster is collected; a receiver draws with the shadow term */
        emi_self = rtx && rtx->etex && rtx->etex->row;   /* (rt8) an emitter is not lit by the lights */
        const bool rtr = rt_on && !g.im && !g.crov && d && mb && d->rt_ok == GPU_NR_RT_MAGIC && rt_classify(g, d, mb, rtx);
        slots_clear();
        set_ubo(0, cbv, sizeof cbv);
        if (d->nbones_rows && !g.im) set_ubo(1, d->bones, sizeof d->bones);
        if (rtr) rt_hist_need(ct.w, ct.h);
        if (rtr) {
            float rcb[RT_CB_ROWS][4];
            rt_cb(d, rcb);
            const bool mvb = rt_mv_rows(d, rcb);   /* (rt9) */
            set_ubo(2, rcb, sizeof rcb);
            if (mvb) set_ubo(3, rt_mvb, sizeof rt_mvb);
            slots[B_T + 8].as = rt_pass_on ? rt_ptlas.as : rt_tlas.as;
            slots[B_T + 9].as = rt_pass_on ? rt_pctlas.as : rt_ctlas.as;
            if (rt_stat.b) set_buf(B_U + 6, rt_stat.b, 0, VK_WHOLE_SIZE);
            if (rt_hist_ok) { set_img(B_U + 7, rt_hst[rt_hcur].uv); set_img(B_U + 8, rt_hst[rt_hcur ^ 1].uv); }
        }
        if (tview) { set_img(B_T + 0, tview); set_smp(0, tsmp); }
        if (zr) set_img(B_U + 2, zt->uv);
        if (g.crov) set_img(B_U + 3, ct.uv);
        /* pipeline */
        const Shader *ps = g.crov ? (zr ? &sh_ps_nr_cz : &sh_ps_nr_c) : zr ? &sh_ps_nr_z : &sh_ps_nr;
        if (rtr) ps = zr ? &sh_ps_nr_zrt : &sh_ps_nr_rt;
        /* a mesh with the VU clipper (rows 24-25, nr_scene.c nr_clip_cb): GS_nr cuts its triangles */
        const bool clipgs = !g.im && gs_ok && g.cb[25][2] != 0.0f;
        GKey k = key0(rtr ? (clipgs ? prog_gs_rt(ps) : prog(&sh_vs_nr_rt, ps))
                          : clipgs ? prog_gs(ps) : prog(g.im ? &sh_vs_im : &sh_vs_nr, ps));
        k.vin = g.im ? 2 : 1;
        k.cf = g.crov ? VK_FORMAT_UNDEFINED : ct.fmt;
        k.df = zt && !zr ? zt->fmt : VK_FORMAT_UNDEFINED;
        nr_blend(k, g.abe, g.alpha_abcd, g.cmask);
        if (g.crov) { k.blend = 0; k.cmask = 0; }
        k.cull = g.im ? 0 : (uint8_t)(g.cull >= 0 && g.cull <= 2 ? g.cull : 0);
        /* the rasterizer bias: with a depth attachment as D3D11; with depth in an ordered view
         * (no attachment) D3D11 still biases SV_Position.z as for a float buffer, which Vulkan
         * expresses with VK_EXT_depth_bias_control's float representation (without the
         * extension: no bias; docs/NATIVE-VULKAN.md "Depth bias") */
        k.bias = (g.im || !zt || (zr && !zrov_brep && !zrov_bias_att)) ? 0 : (int8_t)(zr ? zrov_units : nr_zbias);
        k.brep = zr && zrov_brep ? 1 : 0;
        VkImageView zbv = VK_NULL_HANDLE;
        if (zr && k.bias && !zrov_brep && !g.crov) {
            Img &zb = zbias_img[std::make_pair(ct.w * scale, ct.h * scale)];
            if (!zb.i && !img_make_depth(zb, ct.w * scale, ct.h * scale)) return false;
            zbv = zb.v;
            k.df = zbias_fmt;   /* zt / zw stay 0: never tested or written */
        } else if (zr && !zrov_brep) {
            k.bias = 0;
        }
        if (zt && !zr && g.zfunc != GZ_OFF) {
            static const uint8_t zf[4] = { VK_COMPARE_OP_ALWAYS, VK_COMPARE_OP_ALWAYS, VK_COMPARE_OP_GREATER_OR_EQUAL, VK_COMPARE_OP_GREATER };
            k.zt = 1;
            k.zf = zf[g.zfunc & 3];
            k.zw = g.zwrite ? 1 : 0;
        }
        VkPipeline pp = gpipe(k);
        if (!pp) return false;
        VkPipeline pp_sw = VK_NULL_HANDLE;
        if (g.im && g.nruns > 0) {
            GKey ks = k;
            nr_blend(ks, g.abe, (g.alpha_abcd & ~0xFu) | ((g.alpha_abcd & 3u) << 2) | ((g.alpha_abcd >> 2) & 3u), g.cmask);
            if (g.crov) { ks.blend = 0; ks.cmask = 0; }
            pp_sw = gpipe(ks);
        }
        int W = ct.w * scale, H = ct.h * scale;
        int sx0 = g.scissor.x0 * scale, sy0 = g.scissor.y0 * scale, sx1 = g.scissor.x1 * scale, sy1 = g.scissor.y1 * scale;
        if (sx0 < 0) sx0 = 0;
        if (sy0 < 0) sy0 = 0;
        if (sx1 > W) sx1 = W;
        if (sy1 > H) sy1 = H;
        if (sx1 <= sx0 || sy1 <= sy0) return true;   /* nothing inside the target */
        if (g.crov) begin_rp(VK_NULL_HANDLE, VK_NULL_HANDLE, W, H, g.color_rt + 1);
        else begin_rp(ct.view, zt && !zr ? zt->view : zbv, W, H, 0);
        VkCommandBuffer c = subs[ci].cb;
        if (pp != bound_pipe) { vkCmdBindPipeline(c, VK_PIPELINE_BIND_POINT_GRAPHICS, pp); bound_pipe = pp; }
        push(k.p, VK_PIPELINE_BIND_POINT_GRAPHICS);
        st_n[ST_DRAW]++;
        set_vp_sc(g.vp_w * scale, g.vp_h * scale, sx0, sy0, sx1, sy1, W, H);
        uint64_t pq0 = prof ? pts() : ~0ull;
        if (!g.im) {
            VkDeviceSize o = 0;
            vkCmdBindVertexBuffers(c, 0, 1, &mb->vb.b, &o);
            vkCmdBindIndexBuffer(c, mb->ib.b, 0, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(c, mb->nidx, 1, 0, 0, 0);
        } else {
            vkCmdBindVertexBuffers(c, 0, 1, &vra.b, &vra.off);
            if (g.nruns > 0) {
                uint32_t at = 0;
                int cur = 0;
                for (int i = 0; i < g.nruns; i++) {
                    uint32_t e = g.runs[2 * i], sw = g.runs[2 * i + 1];
                    if (e > g.nim) e = g.nim;
                    if (e <= at) continue;
                    if ((int)sw != cur && pp_sw) {
                        VkPipeline np = sw ? pp_sw : pp;
                        vkCmdBindPipeline(c, VK_PIPELINE_BIND_POINT_GRAPHICS, np);
                        bound_pipe = np;
                        cur = (int)sw;
                    }
                    vkCmdDraw(c, e - at, 1, at, 0);
                    at = e;
                }
            } else {
                vkCmdDraw(c, g.nim, 1, 0, 0);
            }
        }
        if (prof) pev_add(rtr ? PC_RTR : PC_NR, pq0, (double)(g.scissor.x1 - g.scissor.x0) * (g.scissor.y1 - g.scissor.y0) * scale * scale);
        return true;
    }

    void kick() override { submit(); }

    /* ======================================================== early copies */
    int snap_copy(const uint32_t *runs, int nruns) override
    {
        int k = snap_next;
        if (!snapb[k].b && !buf_make(snapb[k], SNAP_BYTES, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2)) return -1;
        uint32_t at = 0;
        std::vector<VkBufferCopy> cs;
        for (int i = 0; i < nruns; i++) {
            if (at + runs[2 * i + 1] > SNAP_BYTES) return -1;
            cs.push_back(VkBufferCopy{ runs[2 * i], at, runs[2 * i + 1] });
            at += runs[2 * i + 1];
        }
        if (!cs.empty()) {
            pre_op();
            vkCmdCopyBuffer(cb(), mem.b, snapb[k].b, (uint32_t)cs.size(), cs.data());
            post_op();
        }
        snap_serial[k] = recording ? subs[ci].serial : serial_next - 1;
        snap_next = (k + 1) % SNAP_SLOTS;
        return k;
    }
    const uint8_t *snap_map(int slot) override
    {
        if (slot < 0 || !snapb[slot].b) return NULL;
        wait_serial(snap_serial[slot]);
        buf_inval(snapb[slot]);
        return snapb[slot].map;
    }
    void snap_unmap(int slot) override { (void)slot; }

    /* ======================================================== display */
    bool compose(const GpuDisplay &d)
    {
        int W = d.out_w * d.scale, H = d.out_h * d.scale;
        if (W <= 0 || H <= 0) return false;
        if (!disp.i || disp.w != W || disp.h != H) {
            if (in_rp && rp.c == disp.v) end_rp();
            img_defer(disp);
            if (!img_make(disp, W, H, VK_FORMAT_R8G8B8A8_UNORM,
                          VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, false))
                return false;
        }
        slots_clear();
        uint32_t u[8][4] = {};
        u[0][0] = (uint32_t)d.out_w; u[0][1] = (uint32_t)d.out_h; u[0][2] = (uint32_t)d.scale;
        u[0][3] = (uint32_t)(d.field & 1) | ((uint32_t)d.field_sel << 1);
        u[1][0] = (uint32_t)d.x0; u[1][1] = (uint32_t)d.y0;
        u[1][2] = (uint32_t)d.mmod | ((uint32_t)d.slbg << 1); u[1][3] = d.alp;
        u[2][0] = d.bg;
        set_buf(B_T + 0, mem.b, 0, VK_WHOLE_SIZE);
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
            if (!mirror) set_img(B_T + 1 + i, targets[c.rt].view);
        }
        set_ubo(0, u, sizeof u);
        GKey k = key0(prog(&sh_vs_quad, &sh_ps_display));
        k.cf = VK_FORMAT_R8G8B8A8_UNORM;
        k.clamp = 1;
        return quad(k, disp.v, VK_NULL_HANDLE, W, H, W, H, 0, 0, W, H);
    }

    int display(const GpuDisplay &d, uint32_t *out) override
    {
        if (!out && !pres_ok) { ps_last = NULL; return -1; }   /* no presenter queue: the caller reads back */
        disp_q0 = prof ? pts() : ~0ull;
        if (!compose(d)) return -1;
        return out_frame(disp.i, disp.w, disp.h, out);
    }

    /* the composed frame (W x H of src, RGBA8) to the caller: read back now, read back one call
     * late (readback_lag), or left on the GPU for the presenter (out == NULL) */
    int out_frame(VkImage src, int W, int H, uint32_t *out)
    {
        if (!out) return share_out(src, W, H);
        if (lag) return read_lag(src, W, H, out);
        if (prof) disp_end((double)W * H);
        return read_img(src, 0, 0, W, H, out);
    }

    /* Lagged read-back (nr_d3d11.cpp readback_lag): queue the copy of this frame and return the
     * frame the previous read queued (same size), whose copy has long completed.  With none
     * queued (the first frame, a new size) this frame is returned now and stays queued, so the
     * next read returns it again. */
    int read_lag(VkImage src, int W, int H, uint32_t *out)
    {
        LagSlot &cur = lagq[lag_cur], &prev = lagq[lag_cur ^ 1];
        VkDeviceSize need = (VkDeviceSize)W * H * 4;
        if (!cur.b.b || cur.w != W || cur.h != H) {
            buf_defer(cur.b);
            cur.pending = false;
            if (!buf_make(cur.b, need, VK_BUFFER_USAGE_TRANSFER_DST_BIT, 2)) { cur.w = cur.h = 0; return -1; }
            cur.w = W; cur.h = H;
        }
        pre_op();
        VkBufferImageCopy c = {};
        c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        c.imageSubresource.layerCount = 1;
        c.imageExtent = { (uint32_t)W, (uint32_t)H, 1 };
        vkCmdCopyImageToBuffer(cb(), src, VK_IMAGE_LAYOUT_GENERAL, cur.b.b, 1, &c);
        post_op();
        if (prof) disp_end((double)W * H);
        cur.serial = subs[ci].serial;
        cur.pending = true;
        submit();
        lag_cur ^= 1;
        LagSlot &ret = prev.pending && prev.b.b && prev.w == W && prev.h == H ? prev : cur;
        wait_serial(ret.serial);
        buf_inval(ret.b);
        memcpy(out, ret.b.map, (size_t)need);
        prev.pending = false;
        return 0;
    }

    /* ---- zero-copy presentation ---- */
    static uint64_t h64(VkImage i)
    {
        uint64_t v = 0;
        memcpy(&v, &i, sizeof i);
        return v;
    }
    static int ps_acquire(void *arg)
    {
        PSlot *s = (PSlot *)arg;
        int e = 1;
        if (!s->st.compare_exchange_strong(e, 2)) return -1;   /* taken back by the backend */
        VkSemaphoreWaitInfo wi = { VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO };
        wi.semaphoreCount = 1;
        wi.pSemaphores = &s->be->tl;
        wi.pValues = &s->serial;
        if (vkWaitSemaphores(s->be->dev, &wi, 500000000ull) != VK_SUCCESS) {
            s->st.store(0);
            return -1;
        }
        return 0;
    }
    static void ps_release(void *arg) { ((PSlot *)arg)->st.store(0); }

    bool vk_present_device(gpu_vk_device *o) override
    {
        if (!pres_ok) return false;
        o->instance = (void *)inst;
        o->physical_device = (void *)pd;
        o->device = (void *)dev;
        o->queue_family = qf;
        return true;
    }
    void *shared_out() override { return ps_last; }

    int share_out(VkImage src, int W, int H)
    {
        ps_last = NULL;
        PSlot &s = ps[ps_cur];
        s.be = this;
        /* the slot back from the presenter: a frame it never took is taken back; one it is
         * drawing now is waited for (as D3D11's keyed mutex, 500 ms) */
        for (int spin = 0;; spin++) {
            int e = 1;
            if (s.st.compare_exchange_strong(e, 0) || e == 0) break;
            if (spin >= 5000) return -1;
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
        if (!s.img.i || s.img.w < W || s.img.h < H) {
            /* grow (never shrink: a window resize does not reallocate every frame); the old image
             * may still be wrapped by the presenter's texture cache, freed 16 presents later */
            int nw = s.img.i && s.img.w > W ? s.img.w : W, nh = s.img.i && s.img.h > H ? s.img.h : H;
            if (s.img.i) {
                if (in_rp && rp.c == s.img.v) end_rp();
                ps_retired.push_back(Retired{ s.img, ps_count });
                s.img = Img();
            }
            if (!img_make(s.img, nw, nh, VK_FORMAT_R8G8B8A8_UNORM,
                          VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, false))
                return -1;
        }
        pre_op();
        VkImageMemoryBarrier b = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        b.srcAccessMask = 0;
        b.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        b.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;   /* the whole frame is written */
        b.newLayout = VK_IMAGE_LAYOUT_GENERAL;
        b.srcQueueFamilyIndex = b.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        b.image = s.img.i;
        b.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        b.subresourceRange.levelCount = 1;
        b.subresourceRange.layerCount = 1;
        vkCmdPipelineBarrier(cb(), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &b);
        VkImageCopy c = {};
        c.srcSubresource.aspectMask = c.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        c.srcSubresource.layerCount = c.dstSubresource.layerCount = 1;
        c.extent = { (uint32_t)W, (uint32_t)H, 1 };
        vkCmdCopyImage(cb(), src, VK_IMAGE_LAYOUT_GENERAL, s.img.i, VK_IMAGE_LAYOUT_GENERAL, 1, &c);
        /* for the presenter's sampling (SDL's Vulkan renderer expects SHADER_READ_ONLY_OPTIMAL) */
        b.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        b.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_MEMORY_READ_BIT;
        b.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
        b.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        vkCmdPipelineBarrier(cb(), VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, NULL, 0, NULL, 1, &b);
        post_op();
        if (prof) disp_end((double)W * H);
        s.serial = subs[ci].serial;
        submit();
        s.fr.image = h64(s.img.i);
        s.fr.img_w = (uint32_t)s.img.w;
        s.fr.img_h = (uint32_t)s.img.h;
        s.fr.acquire = ps_acquire;
        s.fr.release = ps_release;
        s.fr.arg = &s;
        s.st.store(1);
        ps_last = &s.fr;
        ps_cur ^= 1;
        ps_count++;
        for (size_t i = 0; i < ps_retired.size();)
            if (ps_retired[i].at + 16 <= ps_count) {
                img_defer(ps_retired[i].img);
                ps_retired.erase(ps_retired.begin() + (long)i);
            } else {
                i++;
            }
        return 0;
    }

    bool ensure_post(Img &t, int w, int h, VkFormat f)
    {
        if (t.i && t.w == w && t.h == h && t.fmt == f) return true;
        if (in_rp && rp.c == t.v) end_rp();
        img_defer(t);
        return img_make(t, w, h, f, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                        false);
    }
    void post_pass(const Shader &ps, VkImageView src, Img &dst, const float pf[4][4], const uint32_t pq[2][4])
    {
        slots_clear();
        uint8_t cbd[6 * 16];
        memcpy(cbd, pf, 64);
        memcpy(cbd + 64, pq, 32);
        set_ubo(0, cbd, sizeof cbd);
        set_img(B_T + 0, src);
        set_smp(0, smp_lin);
        GKey k = key0(prog(&sh_vs_quad, &ps));
        k.cf = dst.fmt;
        k.clamp = 1;
        quad(k, dst.v, VK_NULL_HANDLE, dst.w, dst.h, dst.w, dst.h, 0, 0, dst.w, dst.h);
    }
    bool resample(VkImageView &cur, int &cw, int &ch, int &slot, int tw, int th, int down, int up)
    {
        for (int axis = 0; axis < 2; axis++) {
            int sn = axis ? ch : cw, dn = axis ? th : tw;
            if (sn == dn || dn <= 0) continue;
            int filt = dn < sn ? down : up;
            int ow = axis ? cw : tw, oh = axis ? th : ch;
            Img &dst = post[slot];
            if (!ensure_post(dst, ow, oh, VK_FORMAT_R16G16B16A16_SFLOAT)) return false;
            float pf[4][4] = { { (float)cw, (float)ch, (float)ow, (float)oh } };
            uint32_t pq[2][4] = { { (uint32_t)axis, (uint32_t)filt, 0, 0 } };
            post_pass(sh_ps_resample, cur, dst, pf, pq);
            cur = dst.v; cw = ow; ch = oh; slot ^= 1;
        }
        return true;
    }
    int display_post(const GpuDisplay &d, const GpuPost &p, uint32_t *out) override
    {
        if (!out && !pres_ok) { ps_last = NULL; return -1; }
        if (!compose(d)) return -1;
        VkImageView cur = disp.v;
        int cw = disp.w, ch = disp.h, slot = 0;
        const VkFormat F16 = VK_FORMAT_R16G16B16A16_SFLOAT;
        if (!resample(cur, cw, ch, slot, p.ssaa_w, p.ssaa_h, p.downsample, p.downsample)) return -1;
        if (p.fxaa) {
            if (!ensure_post(post[slot], cw, ch, F16)) return -1;
            float pf[4][4] = { { (float)cw, (float)ch, 1.0f / (float)cw, 1.0f / (float)ch } };
            uint32_t pq[2][4] = {};
            post_pass(sh_ps_fxaa, cur, post[slot], pf, pq);
            cur = post[slot].v; slot ^= 1;
        }
        if (p.sharpen > 0.0f) {
            if (!ensure_post(post[slot], cw, ch, F16)) return -1;
            float pf[4][4] = { { (float)cw, (float)ch, p.sharpen, 0 } };
            uint32_t pq[2][4] = {};
            post_pass(sh_ps_sharpen, cur, post[slot], pf, pq);
            cur = post[slot].v; slot ^= 1;
        }
        if (!resample(cur, cw, ch, slot, p.final_w, p.final_h, p.downsample, p.upscale)) return -1;
        if (!ensure_post(post[2], cw, ch, VK_FORMAT_R8G8B8A8_UNORM)) return -1;
        {
            float g = p.gamma > 0.01f ? p.gamma : 1.0f;
            int lines = p.src_lines > 0 ? p.src_lines : ch;
            float lpp = (float)ch / (float)lines;
            float strength = lpp >= 2.0f ? 0.55f : (lpp > 1.0f ? 0.55f * (lpp - 1.0f) : 0.0f);
            float pf[4][4] = { { (float)cw, (float)ch, p.brightness, 1.0f / g }, { (float)lines, strength, 0, 0 } };
            uint32_t pq[2][4] = { { (uint32_t)p.output_filter, 0, 0, 0 } };
            post_pass(sh_ps_final, cur, post[2], pf, pq);
        }
        return out_frame(post[2].i, cw, ch, out);
    }

    void set_scale(int s) override
    {
        end_rp();
        rt_pool_free();
        scale = s;
        img_defer(disp);
    }
};

} /* namespace */

GpuBackend *gpu_backend_vulkan_create(const gpu_config *cfg, int scale, char *err, size_t cap)
{
    VkBackend *b = new VkBackend();
    if (!b->init(cfg, scale, err, cap)) {
        delete b;
        return NULL;
    }
    return b;
}

#endif /* RG_NATIVE_ONLY && RG_HAVE_VULKAN */
