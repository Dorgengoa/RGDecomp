/* SPDX-License-Identifier: CC0-1.0
 *
 * x64 start-up self-check (P7 strategy A, docs/X64-PLAN.md step 1): every
 * address of the process must lie below 2 GB, because game memory stores
 * pointers as 4-byte words (`__ptr32`, ADDR32 data relocations).  Windows
 * guarantees that for an image linked /LARGEADDRESSAWARE:NO with a low fixed
 * base (tools/x64/pecheck.py checks the headers at link time); this checks
 * the running process: the image, the stack, the CRT heap and the highest
 * address VirtualAlloc hands out (MEM_TOP_DOWN).  On failure it reports and
 * exits with code 86 before main.
 *
 * cmake/x64.cmake adds this file to every executable of an x64 build; i686
 * never compiles it.
 */
#if defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RG_X64_LIMIT 0x80000000ull

static int rg_x64_bad(const char *what, const void *p)
{
    if ((uintptr_t)p + 0ull < RG_X64_LIMIT)
        return 0;
    fprintf(stderr,
            "rg x64: %s at %p is above 2 GB: the exe must be linked /LARGEADDRESSAWARE:NO "
            "/DYNAMICBASE:NO /HIGHENTROPYVA:NO with a low /BASE (docs/X64-PLAN.md)\n",
            what, p);
    return 1;
}

int rg_x64_lowmem_selfcheck(void)
{
    volatile int local = 0;
    int bad = 0;
    void *h = malloc(64);
    void *v = VirtualAlloc(NULL, 0x10000, MEM_RESERVE | MEM_TOP_DOWN, PAGE_NOACCESS);
    bad |= rg_x64_bad("image", GetModuleHandleW(NULL));
    bad |= rg_x64_bad("stack", (const void *)&local);
    bad |= rg_x64_bad("heap", h);
    bad |= rg_x64_bad("top-down VirtualAlloc", v);
    free(h);
    if (v)
        VirtualFree(v, 0, MEM_RELEASE);
    return bad;
}

/* Graphics-driver address-space fence (docs/X64-PLAN.md 0.6).  The process's NULL-hint
 * allocations all land below 2 GB, and the NVIDIA 64-bit D3D11 driver reserves a 1 GB
 * contiguous range (its GPU virtual-address mirror, under 1 MB committed) once the device
 * is in use: with the driver's own ~256 MB that left about 650 MB of the 2 GB to the port,
 * and runs died in an out-of-memory calloc after 12,000-22,000 fields (nr_mesh_decode).
 * Given no contiguous hole that large below 2 GB, the driver puts the range above 4 GB
 * instead, which is harmless: no driver address is ever stored in game memory.  The
 * fence: one 64 KB reservation ("post") every 512 MB below 2 GB, placed before the
 * graphics device is created and kept for the life of the process (the driver reserves
 * lazily, after device creation), so no free hole below 2 GB is 512 MB or larger.
 * The port's own large reservations (save-state heap 256 MB, game RAM, arenas) are made
 * before the device.  RG_X64_VA_FENCE=0 turns the fence off (the control);
 * RG_X64_VA_LOG=1 prints the free space below 2 GB at rg_x64_va_fence(1) / (0). */
#define RG_X64_POST_STEP (512u << 20)
#define RG_X64_AFTER_STEP 0 /* off: see rg_x64_va_fence */
#define RG_X64_POSTS 512
typedef struct { void *p[RG_X64_POSTS]; int n; } rg_x64_fence;
static rg_x64_fence g_fence, g_after;

void rg_x64_va_report(const char *tag)
{
    MEMORY_BASIC_INFORMATION m;
    uintptr_t a = 0x10000, fr = 0, big = 0;
    while (a < RG_X64_LIMIT && VirtualQuery((void *)a, &m, sizeof m)) {
        if (m.State == MEM_FREE) {
            fr += m.RegionSize;
            if (m.RegionSize > big)
                big = m.RegionSize;
        }
        a = (uintptr_t)m.BaseAddress + m.RegionSize;
    }
    fprintf(stderr, "rg x64: %s: %u MB free below 2 GB (largest hole %u MB)\n", tag,
            (unsigned)(fr >> 20), (unsigned)(big >> 20));
}

/* free space below 2 GB (gpu_internal.h rg_x64_va_tight: the render backends' budgets) */
size_t rg_x64_va_free_below_2g(void)
{
    MEMORY_BASIC_INFORMATION m;
    uintptr_t a = 0x10000, fr = 0;
    while (a < RG_X64_LIMIT && VirtualQuery((void *)a, &m, sizeof m)) {
        if (m.State == MEM_FREE) fr += m.RegionSize;
        a = (uintptr_t)m.BaseAddress + m.RegionSize;
    }
    return fr;
}

/* a post at each multiple of step inside every free range below 2 GB, so no free hole
 * reaches step */
static void rg_x64_posts(rg_x64_fence *f, uintptr_t step)
{
    MEMORY_BASIC_INFORMATION m;
    uintptr_t a = 0x10000;
    while (a < RG_X64_LIMIT && f->n < RG_X64_POSTS && VirtualQuery((void *)a, &m, sizeof m)) {
        uintptr_t rb = (uintptr_t)m.BaseAddress, re = rb + m.RegionSize;
        if (m.State == MEM_FREE) {
            for (uintptr_t p = (rb + step - 1) / step * step;
                 p + 0x10000 <= re && p < RG_X64_LIMIT && f->n < RG_X64_POSTS; p += step) {
                void *q = VirtualAlloc((void *)p, 0x10000, MEM_RESERVE, PAGE_NOACCESS);
                if (q)
                    f->p[f->n++] = q;
            }
        }
        if (re <= a)
            break;
        a = re;
    }
}

static void rg_x64_unpost(rg_x64_fence *f)
{
    while (f->n > 0)
        VirtualFree(f->p[--f->n], 0, MEM_RELEASE);
}

static uintptr_t rg_x64_env_mb(const char *name, uintptr_t dflt)
{
    const char *e = getenv(name);
    if (!e || !*e)
        return dflt;
    return atoi(e) >= 2 ? (uintptr_t)atoi(e) << 20 : 0;
}

/* rg_x64_va_fence(1) before a graphics device is created, (0) after.
 * (1): the device fence (RG_X64_VA_FENCE, MB, default 512, 0 = off), kept for the life of
 *      the process; the after-device fence of an earlier device is lifted first (device
 *      creation itself needs holes larger than 32 MB: D3D11CreateDevice fails with
 *      E_OUTOFMEMORY under a 32 MB fence).
 * (0): the after-device fence (RG_X64_VA_FENCE_AFTER, MB, default off;
 *      docs/X64-PLAN.md 0.8): the NVIDIA x64 user-mode driver commits its system-memory
 *      pools in 32 MB blocks, placed by the kernel.  In this LAA:NO process they can NOT go
 *      above 4 GB (docs/X64-PLAN.md 0.10, tools/x64/d3dfence_probe.c): given no 32 MB hole
 *      the driver falls back to 4 MB blocks below 2 GB and then fails every new resource
 *      (CreateTexture2D E_OUTOFMEMORY: the "display read-back" failure of 0.8 was the
 *      display texture's creation, and native draws stop).  So it only starves the driver;
 *      kept as an experiment switch, OFF.  The real fixes: textures are created SHARED on
 *      x64 (no process-private backing, gpu_internal.h rg_x64_td) and the smaller x64
 *      state heap (ss_heap.c). */
void rg_x64_va_fence(int on)
{
    const char *lg = getenv("RG_X64_VA_LOG");
    int log = lg && lg[0] == '1';
    if (on) {
        rg_x64_unpost(&g_after);
        uintptr_t step = rg_x64_env_mb("RG_X64_VA_FENCE", RG_X64_POST_STEP);
        if (step)
            rg_x64_posts(&g_fence, step);
    } else {
        uintptr_t step = rg_x64_env_mb("RG_X64_VA_FENCE_AFTER", RG_X64_AFTER_STEP);
        if (step)
            rg_x64_posts(&g_after, step);
    }
    if (log)
        rg_x64_va_report(on ? "before the graphics device" : "after the graphics device");
}

/* Crash report for every x64 executable (docs/X64-PLAN.md 0.8; there is no debugger on
 * this machine): an unhandled exception prints its code, the faulting address and up to
 * 12 unwound frames as module + RVA (name them with tools/x64/rva2sym.py MAP RVA..).
 * Programs that install their own filter later (rg-game's crash handler) replace it. */
static void rg_x64_frame(int i, DWORD64 pc)
{
    HMODULE m = NULL;
    char name[MAX_PATH] = "?";
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCSTR)(uintptr_t)pc, &m) && m) {
        GetModuleFileNameA(m, name, sizeof name);
    }
    const char *b = strrchr(name, '\\');
    fprintf(stderr, "rg x64:   #%d %s+0x%llx\n", i, b ? b + 1 : name,
            (unsigned long long)(pc - (DWORD64)(uintptr_t)m));
}

static LONG WINAPI rg_x64_crash(EXCEPTION_POINTERS *ep)
{
    CONTEXT c = *ep->ContextRecord;
    EXCEPTION_RECORD *er = ep->ExceptionRecord;
    fprintf(stderr, "rg x64: unhandled exception 0x%08lx at %p", er->ExceptionCode, er->ExceptionAddress);
    if (er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && er->NumberParameters >= 2)
        fprintf(stderr, " (%s %p)", er->ExceptionInformation[0] ? "write" : "read",
                (void *)er->ExceptionInformation[1]);
    fprintf(stderr, "; stack (module+RVA, tools/x64/rva2sym.py):\n");
    if (!c.Rip) { /* a call through a NULL pointer: the caller's return address is at rsp */
        c.Rip = *(DWORD64 *)(uintptr_t)c.Rsp;
        c.Rsp += 8;
    }
    for (int i = 0; i < 12 && c.Rip; i++) {
        rg_x64_frame(i, c.Rip);
        DWORD64 base = 0;
        RUNTIME_FUNCTION *f = RtlLookupFunctionEntry(c.Rip, &base, NULL);
        if (!f) { /* leaf: the return address is at rsp */
            c.Rip = *(DWORD64 *)(uintptr_t)c.Rsp;
            c.Rsp += 8;
            continue;
        }
        void *hd = NULL;
        DWORD64 est = 0;
        RtlVirtualUnwind(UNW_FLAG_NHANDLER, base, c.Rip, f, &c, &hd, &est, NULL);
    }
    fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
}

/* The play-test crash report's x64 frames (2026-11-01, lane x64pt): rg-game replaces the
 * filter above with its own (rg_game_crash: rg-game-crash.txt + .dmp beside the exe), whose
 * stack scan only finds words that look like image addresses.  This adds the UNWOUND call
 * chain to that report: up to 16 frames as "module+RVA" lines through `out`, and the RVA of
 * each frame inside the exe image into rvas[k * stride] (k from `first`, at most `max`; frame
 * 0 = the faulting rip, always stored, image-relative as before) so rg_game_crash names them
 * from the link map.  Returns the next free index.  Called from one x64alt line in
 * rg_game_main.c (the i686 object is unchanged). */
int rg_x64_crash_frames(EXCEPTION_POINTERS *ep, void (*out)(const char *, ...), uint32_t *rvas, size_t stride,
                        int first, int max)
{
    CONTEXT c = *ep->ContextRecord;
    uintptr_t img = (uintptr_t)GetModuleHandleA(NULL);
    int k = first;
    out("  x64 frames (module+RVA, unwound):\n");
    *(uint32_t *)((char *)rvas + (size_t)k++ * stride) = (uint32_t)(c.Rip - img);
    if (!c.Rip) { /* a call through a NULL pointer: the caller's return address is at rsp */
        c.Rip = *(DWORD64 *)(uintptr_t)c.Rsp;
        c.Rsp += 8;
    }
    for (int i = 0; i < 16 && c.Rip; i++) {
        HMODULE m = NULL;
        char name[MAX_PATH] = "?";
        if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                               (LPCSTR)(uintptr_t)c.Rip, &m) && m)
            GetModuleFileNameA(m, name, sizeof name);
        const char *b = strrchr(name, '\\');
        out("    #%d %s+0x%llx\n", i, b ? b + 1 : name, (unsigned long long)(c.Rip - (DWORD64)(uintptr_t)m));
        if (i > 0 && m == (HMODULE)img && k < first + max)
            *(uint32_t *)((char *)rvas + (size_t)k++ * stride) = (uint32_t)(c.Rip - img);
        DWORD64 base = 0;
        RUNTIME_FUNCTION *f = RtlLookupFunctionEntry(c.Rip, &base, NULL);
        if (!f) { /* leaf: the return address is at rsp */
            MEMORY_BASIC_INFORMATION mi;
            if (!VirtualQuery((void *)(uintptr_t)c.Rsp, &mi, sizeof mi) || mi.State != MEM_COMMIT) break;
            c.Rip = *(DWORD64 *)(uintptr_t)c.Rsp;
            c.Rsp += 8;
            continue;
        }
        void *hd = NULL;
        DWORD64 est = 0;
        RtlVirtualUnwind(UNW_FLAG_NHANDLER, base, c.Rip, f, &c, &hd, &est, NULL);
    }
    return k;
}

/* D3D11 resource census (docs/X64-PLAN.md 0.10), RG_X64_D3DCENSUS=1: the exe's import of
 * d3d11!D3D11CreateDevice is redirected to a wrapper that patches the device vtable's
 * CreateTexture2D / CreateBuffer; at exit one line per (caller, usage, bind flags) with the
 * number of resources and bytes created (the caller as module+RVA: tools/x64/rva2sym.py).
 * The NVIDIA x64 driver backs every default-usage resource with process-private memory below
 * 2 GB, so creation volume is address-space volume.  Diagnostic only. */
#define COBJMACROS
#include <d3d11.h>
typedef HRESULT (WINAPI *rg_d3dcreate_fn)(IDXGIAdapter *, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL *,
                                          UINT, UINT, ID3D11Device **, D3D_FEATURE_LEVEL *, ID3D11DeviceContext **);
typedef HRESULT (STDMETHODCALLTYPE *rg_ct2d_fn)(ID3D11Device *, const D3D11_TEXTURE2D_DESC *,
                                                const D3D11_SUBRESOURCE_DATA *, ID3D11Texture2D **);
typedef HRESULT (STDMETHODCALLTYPE *rg_cbuf_fn)(ID3D11Device *, const D3D11_BUFFER_DESC *,
                                                const D3D11_SUBRESOURCE_DATA *, ID3D11Buffer **);
static rg_d3dcreate_fn rg_cen_create;
/* the originals per vtable (two device classes may exist: the game's and the presenter's) */
typedef struct { void **vt; rg_cbuf_fn cbuf; rg_ct2d_fn ct2d; } rg_cen_vt;
static rg_cen_vt rg_cen_vts[8];
static int rg_cen_nvt;
static rg_cen_vt *rg_cen_known(void *dev)
{
    void **vt = *(void ***)dev;
    for (int i = 0; i < rg_cen_nvt; i++)
        if (rg_cen_vts[i].vt == vt) return &rg_cen_vts[i];
    return NULL;
}
static rg_cen_vt *rg_cen_find(void *dev)
{
    rg_cen_vt *v = rg_cen_known(dev);
    return v ? v : &rg_cen_vts[0];   /* another interface of a known device (its vtable aliases the patched slot) */
}
typedef struct { void *ra; unsigned usage, bind, kind; unsigned long long n, bytes; } rg_cen_site;
static rg_cen_site rg_cen[512];
static int rg_cen_n;
static SRWLOCK rg_cen_lock = SRWLOCK_INIT;

static void rg_cen_add(void *ra, unsigned kind, unsigned usage, unsigned bind, unsigned long long bytes)
{
    AcquireSRWLockExclusive(&rg_cen_lock);
    int i = 0;
    while (i < rg_cen_n && !(rg_cen[i].ra == ra && rg_cen[i].kind == kind && rg_cen[i].usage == usage && rg_cen[i].bind == bind))
        i++;
    if (i == rg_cen_n && rg_cen_n < 512) {
        rg_cen[i].ra = ra; rg_cen[i].kind = kind; rg_cen[i].usage = usage; rg_cen[i].bind = bind;
        rg_cen_n++;
    }
    if (i < 512) { rg_cen[i].n++; rg_cen[i].bytes += bytes; }
    ReleaseSRWLockExclusive(&rg_cen_lock);
}

static unsigned rg_cen_bpp(DXGI_FORMAT f)
{
    switch (f) {
    case DXGI_FORMAT_R32G32B32A32_TYPELESS: case DXGI_FORMAT_R32G32B32A32_FLOAT: case DXGI_FORMAT_R32G32B32A32_UINT: return 16;
    case DXGI_FORMAT_R16G16B16A16_TYPELESS: case DXGI_FORMAT_R16G16B16A16_FLOAT: case DXGI_FORMAT_R16G16B16A16_UNORM:
    case DXGI_FORMAT_R32G32_TYPELESS: case DXGI_FORMAT_R32G32_FLOAT: case DXGI_FORMAT_R32G32_UINT: return 8;
    case DXGI_FORMAT_R8_UNORM: case DXGI_FORMAT_R8_UINT: case DXGI_FORMAT_R8_TYPELESS: return 1;
    case DXGI_FORMAT_R16_TYPELESS: case DXGI_FORMAT_R16_UNORM: case DXGI_FORMAT_R16_UINT: case DXGI_FORMAT_D16_UNORM: return 2;
    default: return 4;
    }
}

static HRESULT STDMETHODCALLTYPE rg_cen_ct2d_hook(ID3D11Device *d, const D3D11_TEXTURE2D_DESC *td,
                                                  const D3D11_SUBRESOURCE_DATA *init, ID3D11Texture2D **out)
{
    HRESULT hr = rg_cen_find(d)->ct2d(d, td, init, out);
    if (td && out && SUCCEEDED(hr))
        rg_cen_add(__builtin_return_address(0), 'T', td->Usage, td->BindFlags,
                   (unsigned long long)td->Width * td->Height * td->ArraySize * td->SampleDesc.Count * rg_cen_bpp(td->Format));
    return hr;
}

static HRESULT STDMETHODCALLTYPE rg_cen_cbuf_hook(ID3D11Device *d, const D3D11_BUFFER_DESC *bd,
                                                  const D3D11_SUBRESOURCE_DATA *init, ID3D11Buffer **out)
{
    HRESULT hr = rg_cen_find(d)->cbuf(d, bd, init, out);
    if (bd && out && SUCCEEDED(hr))
        rg_cen_add(__builtin_return_address(0), 'B', bd->Usage, bd->BindFlags, bd->ByteWidth);
    return hr;
}

static void rg_cen_patch(void **slot, void *fn, void **orig)
{
    DWORD old;
    if (*slot == fn) return;
    *orig = *slot;
    VirtualProtect(slot, sizeof(void *), PAGE_READWRITE, &old);
    *slot = fn;
    VirtualProtect(slot, sizeof(void *), old, &old);
}

static HRESULT WINAPI rg_cen_create_hook(IDXGIAdapter *a, D3D_DRIVER_TYPE dt, HMODULE sw, UINT fl, const D3D_FEATURE_LEVEL *pfl,
                                         UINT nfl, UINT sdk, ID3D11Device **dev, D3D_FEATURE_LEVEL *got,
                                         ID3D11DeviceContext **ctx)
{
    HRESULT hr = rg_cen_create(a, dt, sw, fl, pfl, nfl, sdk, dev, got, ctx);
    if (SUCCEEDED(hr) && dev && *dev && !rg_cen_known(*dev) && rg_cen_nvt < 8) {
        void **vt = *(void ***)*dev;
        rg_cen_vt *v = &rg_cen_vts[rg_cen_nvt];
        v->vt = vt;
        rg_cen_patch(&vt[3], (void *)rg_cen_cbuf_hook, (void **)&v->cbuf);   /* ID3D11Device::CreateBuffer */
        rg_cen_patch(&vt[5], (void *)rg_cen_ct2d_hook, (void **)&v->ct2d);   /* ::CreateTexture2D */
        rg_cen_nvt++;
    }
    return hr;
}

static void rg_cen_report(void)
{
    HMODULE me = GetModuleHandleW(NULL);
    unsigned long long tot = 0;
    for (int i = 0; i < rg_cen_n; i++) tot += rg_cen[i].bytes;
    fprintf(stderr, "rg x64 d3dcensus: %d sites, %.1f MB created\n", rg_cen_n, tot / 1048576.0);
    for (int i = 0; i < rg_cen_n; i++)
        fprintf(stderr, "rg x64 d3dcensus: %c rva 0x%llx usage %u bind 0x%x: %llu created, %.1f MB\n", rg_cen[i].kind,
                (unsigned long long)((uintptr_t)rg_cen[i].ra - (uintptr_t)me), rg_cen[i].usage, rg_cen[i].bind, rg_cen[i].n,
                rg_cen[i].bytes / 1048576.0);
    fflush(stderr);
}

static void rg_x64_d3dcensus_arm(void)
{
    uint8_t *b = (uint8_t *)GetModuleHandleW(NULL);
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(b + ((IMAGE_DOS_HEADER *)b)->e_lfanew);
    IMAGE_DATA_DIRECTORY d = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!d.VirtualAddress) return;
    for (IMAGE_IMPORT_DESCRIPTOR *id = (IMAGE_IMPORT_DESCRIPTOR *)(b + d.VirtualAddress); id->Name; id++) {
        if (_stricmp((const char *)(b + id->Name), "d3d11.dll")) continue;
        IMAGE_THUNK_DATA *names = (IMAGE_THUNK_DATA *)(b + id->OriginalFirstThunk);
        IMAGE_THUNK_DATA *iat = (IMAGE_THUNK_DATA *)(b + id->FirstThunk);
        for (; names->u1.AddressOfData; names++, iat++) {
            if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal)) continue;
            IMAGE_IMPORT_BY_NAME *nm = (IMAGE_IMPORT_BY_NAME *)(b + names->u1.AddressOfData);
            if (strcmp((const char *)nm->Name, "D3D11CreateDevice")) continue;
            rg_cen_patch((void **)&iat->u1.Function, (void *)rg_cen_create_hook, (void **)&rg_cen_create);
            atexit(rg_cen_report);
            fprintf(stderr, "rg x64 d3dcensus: armed\n");
        }
    }
}

__attribute__((constructor)) static void rg_x64_lowmem_ctor(void)
{
    if (rg_x64_lowmem_selfcheck()) {
        fflush(stderr);
        ExitProcess(86);
    }
    SetUnhandledExceptionFilter(rg_x64_crash);
    {
        const char *c = getenv("RG_X64_D3DCENSUS");
        if (c && c[0] == '1') rg_x64_d3dcensus_arm();
    }
}
#endif
