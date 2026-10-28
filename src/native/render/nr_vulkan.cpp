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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "gpu_internal.h"

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
#include "vk_VS_im.h"
#include "vk_PS_nr.h"
#include "vk_PS_nr_z.h"
#include "vk_PS_nr_c.h"
#include "vk_PS_nr_cz.h"

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
    std::unordered_map<uint32_t, uint32_t> var_type;
    size_t first_dec = 0;
    for (size_t i = 5; i < w.size();) {
        uint32_t op = w[i] & 0xFFFFu, wc = w[i] >> 16;
        if (!wc || i + wc > w.size()) return;
        const uint32_t *a = &w[i + 1];
        if (op == 71 && !first_dec) first_dec = i;
        if (op == 25 && a[6] == 2 && a[2] != 5) storage_imgs.push_back(a[0]);
        if (op == 32) ptr_to[a[0]] = a[2];
        if (op == 59 && a[2] == 0) { vars.push_back(a[1]); var_type[a[1]] = a[0]; }
        i += wc;
    }
    if (!first_dec) return;
    std::vector<uint32_t> ins;
    for (uint32_t v : vars) {
        uint32_t t = ptr_to.count(var_type[v]) ? ptr_to[var_type[v]] : 0;
        if (std::find(storage_imgs.begin(), storage_imgs.end(), t) == storage_imgs.end()) continue;
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
};

struct Slot {
    VkBuffer buf;
    VkDeviceSize off, range;
    VkBufferView bv;
    VkImageView iv;
    VkSampler smp;
};

static const int NSUB = 6;

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

    /* ---- shaders, programs, pipelines ---- */
    Shader sh_vs_quad, sh_ps_load_color, sh_ps_load_depth, sh_ps_load_depth_rt, sh_ps_copy_depth, sh_ps_display,
        sh_cs_wb_color, sh_cs_wb_depth, sh_cs_merge, sh_cs_clut, sh_cs_l2l_read, sh_cs_l2l_write, sh_cs_xfer,
        sh_cs_decode, sh_ps_resample, sh_ps_fxaa, sh_ps_sharpen, sh_ps_final, sh_vs_nr, sh_vs_im, sh_ps_nr,
        sh_ps_nr_z, sh_ps_nr_c, sh_ps_nr_cz;
    std::map<std::pair<const Shader *, const Shader *>, Prog *> progs;
    std::unordered_map<std::string, VkPipeline> gpipes;

    Slot slots[B_N];

    std::vector<Target> targets;
    std::vector<Target> rt_pool;
    int rt_pool_on = -1;
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
    enum { PC_DECODE = 32, PC_WB, PC_LOAD, PC_DISPLAY, PC_SNAP, PC_NR, PC_N };
    double p_ms[64] = {}, p_px[64] = {};
    uint64_t p_n[64] = {};
    uint64_t disp_q0 = ~0ull;      /* display(): compose + copy, ended in the read-back / share */

    /* $RG_VK_STATS=1: counters printed at exit (measurement) */
    enum { ST_SUBMIT, ST_WAIT, ST_WRAP, ST_BARRIER, ST_RP, ST_DRAW, ST_DISPATCH, ST_PIPE, ST_N };
    uint64_t st_n[ST_N] = {};

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
        {
            VmaVulkanFunctions vf = {};
            vf.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
            vf.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
            VmaAllocatorCreateInfo ai = {};
            ai.physicalDevice = pd;
            ai.device = dev;
            ai.instance = inst;
            ai.vulkanApiVersion = VK_API_VERSION_1_3;
            ai.pVulkanFunctions = &vf;
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
        }
#define SH(var, name, stage, entry) CHK(shader_make(var, g_spv_##name, sizeof g_spv_##name, stage, entry), #name)
        SH(sh_vs_quad, VS_quad, VK_SHADER_STAGE_VERTEX_BIT, "VS_quad");
        SH(sh_ps_load_color, PS_load_color, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_load_color");
        SH(sh_ps_load_depth, PS_load_depth, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_load_depth");
        SH(sh_ps_load_depth_rt, PS_load_depth_rt, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_load_depth");
        SH(sh_ps_copy_depth, PS_copy_depth, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_copy_depth");
        SH(sh_ps_display, PS_display, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_display");
        SH(sh_cs_wb_color, CS_wb_color, VK_SHADER_STAGE_COMPUTE_BIT, "CS_wb_color");
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
        SH(sh_ps_nr, PS_nr, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
        if (zrov_ok) SH(sh_ps_nr_z, PS_nr_z, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
        if (rov_ok) SH(sh_ps_nr_c, PS_nr_c, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
        if (rov_ok && zrov_ok) SH(sh_ps_nr_cz, PS_nr_cz, VK_SHADER_STAGE_FRAGMENT_BIT, "PS_nr");
#undef SH
#undef CHK
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
            for (auto &e : nr_mesh) { buf_free(e.second.vb); buf_free(e.second.ib); }
            for (auto &e : pre) { buf_free(e.second.vb); buf_free(e.second.ib); buf_free(e.second.st); }
            for (NrTex &t : nr_tex) img_free(t.img);
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
            Shader *all[] = { &sh_vs_quad, &sh_ps_load_color, &sh_ps_load_depth, &sh_ps_load_depth_rt, &sh_ps_copy_depth, &sh_ps_display,
                              &sh_cs_wb_color, &sh_cs_wb_depth, &sh_cs_merge, &sh_cs_clut, &sh_cs_l2l_read, &sh_cs_l2l_write,
                              &sh_cs_xfer, &sh_cs_decode, &sh_ps_resample, &sh_ps_fxaa, &sh_ps_sharpen, &sh_ps_final, &sh_vs_nr,
                              &sh_vs_im, &sh_ps_nr, &sh_ps_nr_z, &sh_ps_nr_c, &sh_ps_nr_cz };
            for (Shader *s : all) if (s->m) vkDestroyShaderModule(dev, s->m, NULL);
            if (smp_lin) vkDestroySampler(dev, smp_lin, NULL);
            for (int i = 0; i < 8; i++) if (smp_nr[i >> 2][(i >> 1) & 1][i & 1]) vkDestroySampler(dev, smp_nr[i >> 2][(i >> 1) & 1][i & 1], NULL);
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
        bi.usage = usage;
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
        vi.subresourceRange.levelCount = 1;
        vi.subresourceRange.layerCount = 1;
        VkImageView v = VK_NULL_HANDLE;
        if (vkCreateImageView(dev, &vi, NULL, &v) != VK_SUCCESS) return VK_NULL_HANDLE;
        return v;
    }
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
        ii.mipLevels = 1;
        ii.arrayLayers = 1;
        ii.samples = VK_SAMPLE_COUNT_1_BIT;
        ii.tiling = VK_IMAGE_TILING_OPTIMAL;
        ii.usage = usage;
        ii.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
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
        b.subresourceRange.levelCount = 1;
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
                                              : c == PC_DISPLAY ? "display+copy" : c == PC_NR ? "native model draws" : "snapshot");
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
    void pre_op() { cb(); end_rp(); barrier(); }
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
    Prog *prog(const Shader *a, const Shader *b)
    {
        auto it = progs.find(std::make_pair(a, b));
        if (it != progs.end()) return it->second;
        Prog *p = new Prog();
        if (a->stage == VK_SHADER_STAGE_COMPUTE_BIT) p->cs = a;
        else { p->vs = a; p->ps = b; }
        const Shader *ss[2] = { a, b };
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
        progs[std::make_pair(a, b)] = p;
        return p;
    }

    VkPipeline gpipe(const GKey &k)
    {
        std::string key((const char *)&k, sizeof k);
        auto it = gpipes.find(key);
        if (it != gpipes.end()) return it->second;
        const Prog *p = k.p;
        VkPipelineShaderStageCreateInfo st[2] = {};
        for (int i = 0; i < 2; i++) {
            const Shader *s = i ? p->ps : p->vs;
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
        gi.stageCount = 2;
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
    bool make_target(Target &t, int depth, int w, int h)
    {
        for (size_t i = 0; i < rt_pool.size(); i++) {
            Target &p = rt_pool[i];
            if (p.depth != depth || p.w != w || p.h != h) continue;
            t = p;
            rt_pool.erase(rt_pool.begin() + (long)i);
            t.used = 1;
            n_rt_pool_hits++;
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
    }
    void rt_destroy(int id) override
    {
        if (id < 0 || (size_t)id >= targets.size() || !targets[id].used) return;
        if (in_rp && (rp.c == targets[id].view || rp.d == targets[id].view)) end_rp();
        if (rt_pool_on < 0) { const char *e = getenv("RG_GPU_RT_POOL"); rt_pool_on = !(e && e[0] == '0'); }
        if (rt_pool_on && targets[id].img && !destroying) {
            if (rt_pool.size() >= 24) { defer_target(rt_pool.front()); rt_pool.erase(rt_pool.begin()); }
            rt_pool.push_back(targets[id]);
            targets[id] = Target();
            return;
        }
        defer_target(targets[id]);
    }

    void copy_img(VkImage dst, int dx, int dy, VkImage src, int sx, int sy, int w, int h, bool depth)
    {
        if (w <= 0 || h <= 0) return;
        pre_op();
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
        pre_op();
        vkCmdUpdateBuffer(cb(), clut.b, 0, sizeof c, &c);
        post_op();
    }
    void set_clut_part(const GpuClutCB &c, const uint8_t *own) override
    {
        const uint32_t *w = &c.c[0][0];
        bool any = false;
        for (uint32_t i = 0; i < 256;) {
            if (own[i]) { i++; continue; }
            uint32_t e = i;
            while (e < 256 && !own[e]) e++;
            if (!any) { pre_op(); any = true; }
            vkCmdUpdateBuffer(cb(), clut.b, i * 4u, (e - i) * 4u, w + i);
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
    struct NrMeshBuf { Buf vb, ib, st; uint32_t nidx = 0; uint64_t used = 0; uint32_t vbytes = 0; };
    std::unordered_map<uint32_t, NrMeshBuf> nr_mesh;
    uint64_t nr_clock = 0;
    struct NrTex { uint32_t key[8]; GpuRect rect; int valid; int tw, th; uint64_t used; uint64_t h; Img img; };
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
        if (!buf_make(b.vb, vbytes, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 0)) return false;
        if (!buf_make(b.ib, ibytes, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 0)) { buf_free(b.vb); return false; }
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
        int id = rt_create(depth, w, h);
        if (id < 0) return -1;
        copy_img(targets[id].img, 0, 0, targets[src].img, 0, 0, w * scale, h * scale, targets[src].dsv != 0);
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

    NrTex *nr_tex_get(const GpuNrDraw &g)
    {
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
        if (nr_tex.size() < NR_TEX_MAX && nr_tex_bytes + need <= nr_tex_budget) {
            nr_tex.push_back(NrTex());
            e = &nr_tex.back();
            memset(e->key, 0, sizeof e->key);
            e->rect = GpuRect{ 0, 0, 0, 0 };
            e->valid = 0; e->tw = e->th = 0; e->used = 0; e->h = 0;
            e->img = Img();
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
                          VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, true)) {
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
        e->used = nr_clock;
        n_nr_tex++;
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
            if (prof && n_nr_tex != nd0)
                pev_add(PC_DECODE, q0, (double)(g.dec_rect.x1 - g.dec_rect.x0) * (g.dec_rect.y1 - g.dec_rect.y0));
            if (!tx) return false;
            tview = tx->img.v;
            tsmp = smp_nr[g.lin ? 1 : 0][g.clamp_u ? 1 : 0][g.clamp_v ? 1 : 0];
        }
        /* immediate vertices into the ring */
        RA vra = { VK_NULL_HANDLE, 0, NULL };
        if (g.im) {
            vra = ring_put(g.im, (VkDeviceSize)g.nim * sizeof(GpuImVtx), 16);
            if (!vra.p) return false;
        }
        /* constants */
        float cbv[24][4];
        memcpy(cbv, g.cb, sizeof cbv);
        {
            uint32_t zc = (uint32_t)(zt ? g.zfunc : GZ_OFF) | (zt && g.zwrite ? 16u : 0u);
            memcpy(&cbv[23][3], &zc, 4);
        }
        slots_clear();
        set_ubo(0, cbv, sizeof cbv);
        if (d->nbones_rows && !g.im) set_ubo(1, d->bones, sizeof d->bones);
        if (tview) { set_img(B_T + 0, tview); set_smp(0, tsmp); }
        if (zr) set_img(B_U + 2, zt->uv);
        if (g.crov) set_img(B_U + 3, ct.uv);
        /* pipeline */
        const Shader *ps = g.crov ? (zr ? &sh_ps_nr_cz : &sh_ps_nr_c) : zr ? &sh_ps_nr_z : &sh_ps_nr;
        GKey k = key0(prog(g.im ? &sh_vs_im : &sh_vs_nr, ps));
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
        if (prof) pev_add(PC_NR, pq0, (double)(g.scissor.x1 - g.scissor.x0) * (g.scissor.y1 - g.scissor.y0) * scale * scale);
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
