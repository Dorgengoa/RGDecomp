/* SPDX-License-Identifier: CC0-1.0
 * Port save states: what each byte of the executable belongs to
 * (docs/TEST-FIXTURES.md "Save states").
 *
 * The link writes rg-game.map next to the exe (cmake/game_link.cmake /MAP).
 * Every public and static symbol is listed with its address and its
 * "lib:object" (game objects come from OBJECT libraries and are listed
 * bare).  A symbol owns the bytes up to the next symbol, so sorting them
 * gives, for .data/.bss, which ranges belong to the game, to the port's
 * models, to host code, or to a subsystem hook, and for .text which code
 * is host code (the state heap's caller classification, ss_heap.c).
 *
 * The map must belong to the running exe: its timestamp must equal the PE
 * header's TimeDateStamp, else save states are disabled.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ss_internal.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

typedef struct ss_sym {
    uint32_t rva;
    uint32_t name;   /* offset into g_text */
    uint32_t obj;    /* offset into g_text */
    uint8_t is_code;
    uint8_t dcls, ccls;
} ss_sym;

static struct {
    int ready, tried;
    ss_image img;
    char *text;             /* the map file (names point into it) */
    ss_sym *sym;
    int nsym;
    ss_range *data;
    int ndata;
    ss_range *code;         /* sorted, merged */
    int ncode;
} M;

/* ---- classification ----------------------------------------------------
 * Libraries whose data and code are host-side (never saved; their mallocs go
 * to the host heap). */
static const char *const k_host_libs[] = {
    "rg_host", "rg_gpu", "rg_settings", "rg_trace", "rg_trace_core", "rg_savestate",
    "rg_native_fs", "rg_native_fs_oracle", "rg_ps2_cdvd",
    "rg_native_render",   /* renderer-side caches and records, rebuilt on demand (docs/NATIVE-RENDER.md) */
    NULL,
};

/* Objects inside model libraries with their own policy.  dcls applies to the
 * object's data, ccls to its code (who allocates where). */
static const struct { const char *lib, *obj; int dcls, ccls; } k_obj_policy[] = {
    /* R: the runtime hook saves the guest-visible part (runtime.c rg_runtime_ss_*);
     * the rest (host handles, buffers, dump/log files) stays.  Its mallocs
     * (presentation and audio buffers) are host buffers. */
    {"rg_runtime", "runtime.c.obj", SS_HOOK, SS_HOST},
    /* memory-card files: the card model reads and writes the host saves
     * folder (docs/SAVES.md); a load keeps the loading process's cards */
    {"rg_native_saves", "mccard.c.obj", SS_HOST, SS_HOST},
    /* native fileio (docs/NATIVE-IOP.md): open host FILE handles */
    {"rg_native_iop", "rg_iop_fio.c.obj", SS_HOST, SS_HOST},
    /* the GS worker thread (struct, ring, thread handle, locks): host side,
     * rebuilt by the runtime hook after a load */
    {"rg_ps2_gs", "gs_async.c.obj", SS_HOST, SS_HOST},
    /* measurement / recording only */
    {"rg_ps2_gs", "gs_census.c.obj", SS_HOST, SS_HOST},
    {"rg_ps2_gs", "gs_rec.c.obj", SS_HOST, SS_HOST},
    {"rg_ps2_vif", "vucensus.c.obj", SS_HOST, SS_HOST},
    /* native audio: env switches, command log, compare WAV, runtime clock glue
     * (docs/NATIVE-AUDIO.md); the engine itself is model state */
    {"rg_native_audio", "ra_host.c.obj", SS_HOST, SS_HOST},
    /* the presentation mix (per-source volumes, docs/NATIVE-AUDIO.md "Source volumes"):
     * never game state; a load is detected and it resynchronises from the engine */
    {"rg_native_audio", "ra_present.c.obj", SS_HOST, SS_HOST},
    /* kernel census recorder ($RG_KCENSUS, docs/NATIVE-THREADS.md) */
    {"rg_sce_kernel", "kcensus.c.obj", SS_HOST, SS_HOST},
    {NULL, NULL, 0, 0},
};

/* Single data symbols with their own policy (by object and decorated name). */
static const struct { const char *obj, *name; int cls; } k_sym_policy[] = {
    {"kcore.c.obj", "_K", SS_HOOK},          /* kernel state: kstate_ss.c */
    {"kcore.c.obj", "_k_tap", SS_HOST},      /* census tap ($RG_KCENSUS) */
    /* the native kernel table (docs/NATIVE-THREADS.md "Native kernel table"): saved by the
     * same "kernel" hook (ps2k_ss_*, rg_nk_ss.c) */
    {"rg_nk.c.obj", "_NK", SS_HOOK},
    {"rg_nk.c.obj", "_nk_tap", SS_HOST},
    {"rg_spin_native.c.obj", "_g_hook", SS_HOST},
    {"rg_spin_native.c.obj", "_g_hook_user", SS_HOST},
    {"dmac.c.obj", "_vdump", SS_HOST},       /* $RG_VIF_DUMP file */
    {"gs_core.c.obj", "_g_census", SS_HOST}, /* $RG_GS_CENSUS counters */
    {"gs_core.c.obj", "_gs__fx_on", SS_HOST}, /* $RG_NR_FXCENSUS (docs/NATIVE-RENDER.md) */
    {"gs_core.c.obj", "_g_fx_marker", SS_HOST},
    {"gs_core.c.obj", "_g_fx_reg", SS_HOST},
    {"gs_core.c.obj", "_g_fx_prim", SS_HOST},
    {"gs_core.c.obj", "_g_fx_priv", SS_HOST},
    {"gs_core.c.obj", "_g_fx_xfer", SS_HOST},
    {"gs_core.c.obj", "_g_fx_clut", SS_HOST},
    {"gs_mem.c.obj", "_g_elide_host", SS_HOST}, /* upload elision switch + counters (docs/NATIVE-RENDER.md) */
    {"gs_mem.c.obj", "_fastxfer_on", SS_HOST},     /* $RG_GS_FASTXFER */
    {"gs_mem.c.obj", "_fastxfer_check", SS_HOST},
    {"gs_mem.c.obj", "_elide_log", SS_HOST},
    {"vif.c.obj", "_g_vcen", SS_HOST},       /* VIF census (heap table) */
    {"vif.c.obj", "_g_nvcen", SS_HOST},
    {"vif.c.obj", "_g_vcen_on", SS_HOST},
    /* callbacks host code (the timing record, tests) installs into models:
     * the loading process keeps its own */
    {"mv_game.c.obj", "_g_hook", SS_HOST},
    {"mv_game.c.obj", "_g_hook_user", SS_HOST},
    {"mv_game.c.obj", "_g_clock", SS_HOST},
    {"ovl.c.obj", "_g_load_hook", SS_HOST},
    {"ovl.c.obj", "_g_load_hook_user", SS_HOST},
    {"ovl_native.c.obj", "_g_load_hook", SS_HOST},      /* native module table (src/native/ovl) */
    {"ovl_native.c.obj", "_g_load_hook_user", SS_HOST},
    {"libpad.c.obj", "_g_read_hook", SS_HOST},
    {"libpad.c.obj", "_g_read_hook_user", SS_HOST},
    {"libcdvd.c.obj", "_g_read_hook", SS_HOST},
    {"libcdvd.c.obj", "_g_read_hook_user", SS_HOST},
    {"spin.c.obj", "_g_hook", SS_HOST},
    {"spin.c.obj", "_g_hook_user", SS_HOST},
    {NULL, NULL, 0},
};

static void classify(const char *obj, size_t objlen, int *dcls, int *ccls)
{
    const char *colon = memchr(obj, ':', objlen);
    *dcls = *ccls = SS_MODEL;
    if (!colon) {
        if (objlen && obj[0] == '<') {           /* <absolute>, <linker defined> */
            *dcls = *ccls = SS_HOST;
            return;
        }
        if ((objlen == 18 && !memcmp(obj, "rg_game_main.c.obj", 18)) ||
            (objlen == 14 && !memcmp(obj, "rg_slots.c.obj", 14)) ||
            (objlen == 16 && !memcmp(obj, "rg_game_ss.c.obj", 16))) {
            *dcls = *ccls = SS_HOST;             /* the exe's host entry, instance limiter, CLI */
            return;
        }
        *dcls = *ccls = SS_GAME;                 /* game/overrides/missing/generated */
        return;
    }
    size_t ll = (size_t)(colon - obj);
    const char *o = colon + 1;
    size_t ol = objlen - ll - 1;
    if (ll < 3 || memcmp(obj, "rg_", 3)) {       /* SDL, CRT, C++ runtime, import libs */
        *dcls = *ccls = SS_HOST;
        return;
    }
    for (int i = 0; k_host_libs[i]; i++)
        if (strlen(k_host_libs[i]) == ll && !memcmp(obj, k_host_libs[i], ll)) {
            *dcls = *ccls = SS_HOST;
            return;
        }
    if (ll == 12 && !memcmp(obj, "rg_ovl_arena", 12)) {
        *dcls = *ccls = SS_GAME;                 /* overlay data/bss arena */
        return;
    }
    for (int i = 0; k_obj_policy[i].lib; i++)
        if (strlen(k_obj_policy[i].lib) == ll && !memcmp(obj, k_obj_policy[i].lib, ll) &&
            strlen(k_obj_policy[i].obj) == ol && !memcmp(o, k_obj_policy[i].obj, ol)) {
            *dcls = k_obj_policy[i].dcls;
            *ccls = k_obj_policy[i].ccls;
            return;
        }
}

static int sym_policy(const char *obj, size_t objlen, const char *name, size_t namelen, int dflt)
{
    const char *colon = memchr(obj, ':', objlen);
    const char *o = colon ? colon + 1 : obj;
    size_t ol = objlen - (size_t)(o - obj);
#if defined(_WIN64)
    /* the table spells the i686 decorated names (`_K`); x64 C names carry no `_` */
    for (int i = 0; k_sym_policy[i].obj; i++)
        if (strlen(k_sym_policy[i].obj) == ol && !memcmp(o, k_sym_policy[i].obj, ol) &&
            strlen(k_sym_policy[i].name + 1) == namelen && !memcmp(name, k_sym_policy[i].name + 1, namelen))
            return k_sym_policy[i].cls;
#else
    for (int i = 0; k_sym_policy[i].obj; i++)
        if (strlen(k_sym_policy[i].obj) == ol && !memcmp(o, k_sym_policy[i].obj, ol) &&
            strlen(k_sym_policy[i].name) == namelen && !memcmp(name, k_sym_policy[i].name, namelen))
            return k_sym_policy[i].cls;
#endif
    return dflt;
}

static int cmp_sym(const void *a, const void *b)
{
    const ss_sym *x = (const ss_sym *)a, *y = (const ss_sym *)b;
    return x->rva < y->rva ? -1 : x->rva > y->rva;
}

/* ---- PE header ---------------------------------------------------------- */
static int read_image(ss_image *im, char *err, size_t cap)
{
#ifdef _WIN32
    HMODULE m = GetModuleHandleA(NULL);
    const uint8_t *b = (const uint8_t *)m;
    const IMAGE_NT_HEADERS32 *nt = (const IMAGE_NT_HEADERS32 *)(b + ((const IMAGE_DOS_HEADER *)b)->e_lfanew);
    const IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
    memset(im, 0, sizeof *im);
    im->base = (uintptr_t)b;
    im->timestamp = nt->FileHeader.TimeDateStamp;
    im->size_of_image = nt->OptionalHeader.SizeOfImage;
    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        char n[9] = {0};
        memcpy(n, s[i].Name, 8);
        if (!strcmp(n, ".text")) {
            im->text_lo = im->base + s[i].VirtualAddress;
            im->text_hi = im->text_lo + s[i].Misc.VirtualSize;
        } else if (!strcmp(n, ".data")) {
            im->data_lo = im->base + s[i].VirtualAddress;
            im->data_hi = im->data_lo + s[i].Misc.VirtualSize;
        }
    }
    GetModuleFileNameA(NULL, im->exe_path, sizeof im->exe_path);
    if (!im->text_lo || !im->data_lo) {
        snprintf(err, cap, "no .text/.data section in the exe");
        return -1;
    }
    return 0;
#else
    (void)im;
    snprintf(err, cap, "save states need Windows (i686) for now");
    return -1;
#endif
}

/* ---- the map ------------------------------------------------------------ */
static int is_hex(const char *p, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (!((p[i] >= '0' && p[i] <= '9') || (p[i] >= 'a' && p[i] <= 'f') || (p[i] >= 'A' && p[i] <= 'F')))
            return 0;
    return 1;
}

int ss_map_load(char *err, size_t cap)
{
    char dummy[8];
    if (!err) {
        err = dummy;
        cap = sizeof dummy;
    }
    if (M.ready)
        return 0;
    if (M.tried) {
        snprintf(err, cap, "link map unavailable (see the first message)");
        return -1;
    }
    M.tried = 1;
    if (read_image(&M.img, err, cap) != 0)
        return -1;
    char path[600];
    snprintf(path, sizeof path, "%s", M.img.exe_path);
    char *dot = strrchr(path, '.');
    if (!dot || strchr(dot, '\\') || strchr(dot, '/'))
        dot = path + strlen(path);
    strcpy(dot, ".map");
    FILE *f = fopen(path, "rb");
    if (!f) {
        snprintf(err, cap, "no link map %s next to the exe", path);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    M.text = (char *)malloc((size_t)n + 1);
    if (!M.text || fread(M.text, 1, (size_t)n, f) != (size_t)n) {
        fclose(f);
        snprintf(err, cap, "cannot read %s", path);
        return -1;
    }
    fclose(f);
    M.text[n] = 0;

    const char *ts = strstr(M.text, "Timestamp is ");
    const char *pl = strstr(M.text, "Preferred load address is ");
    if (!ts || !pl) {
        snprintf(err, cap, "%s: not an MSVC-style link map", path);
        return -1;
    }
    uint32_t stamp = (uint32_t)strtoul(ts + 13, NULL, 16);
    uint64_t pref = strtoull(pl + 26, NULL, 16);
    if (stamp != M.img.timestamp) {
        snprintf(err, cap, "%s belongs to another link (map timestamp %08x, exe %08x)", path,
                 (unsigned)stamp, (unsigned)M.img.timestamp);
        return -1;
    }

    int cap_sym = 1 << 17;
    M.sym = (ss_sym *)malloc(sizeof(ss_sym) * (size_t)cap_sym);
    if (!M.sym)
        return -1;
    const uintptr_t tlo = M.img.text_lo - M.img.base, thi = M.img.text_hi - M.img.base;
    const uintptr_t dlo = M.img.data_lo - M.img.base, dhi = M.img.data_hi - M.img.base;
    for (char *l = M.text; l && *l;) {
        char *e = strchr(l, '\n');
        if (e)
            *e = 0;
        /* " SSSS:OOOOOOOO       name   VVVVVVVVVVVVVVVV  [f] [i]  lib:obj" */
        if (l[0] == ' ' && l[5] == ':' && is_hex(l + 1, 4) && is_hex(l + 6, 8)) {
            char *tok[8];
            int nt = 0;
            for (char *p = l; *p && nt < 8;) {
                while (*p == ' ' || *p == '\t' || *p == '\r')
                    *p++ = 0;
                if (!*p)
                    break;
                tok[nt++] = p;
                while (*p && *p != ' ' && *p != '\t' && *p != '\r')
                    p++;
            }
            if (nt >= 4 && strlen(tok[2]) == 16 && is_hex(tok[2], 16)) {
                uint64_t va = strtoull(tok[2], NULL, 16);
                uintptr_t rva = (uintptr_t)(va - pref);
                int code = rva >= tlo && rva < thi, data = rva >= dlo && rva < dhi;
                if ((code || data) && va >= pref) {
                    if (M.nsym == cap_sym) {
                        cap_sym *= 2;
                        ss_sym *ns = (ss_sym *)realloc(M.sym, sizeof(ss_sym) * (size_t)cap_sym);
                        if (!ns)
                            return -1;
                        M.sym = ns;
                    }
                    ss_sym *s = &M.sym[M.nsym++];
                    const char *obj = tok[nt - 1];
                    int dc, cc;
                    classify(obj, strlen(obj), &dc, &cc);
                    s->rva = (uint32_t)rva;
                    s->name = (uint32_t)(tok[1] - M.text);
                    s->obj = (uint32_t)(obj - M.text);
                    s->is_code = (uint8_t)code;
                    s->dcls = (uint8_t)(data ? sym_policy(obj, strlen(obj), tok[1], strlen(tok[1]), dc) : dc);
                    s->ccls = (uint8_t)cc;
                }
            }
        }
        l = e ? e + 1 : NULL;
    }
    qsort(M.sym, (size_t)M.nsym, sizeof *M.sym, cmp_sym);

    /* merged ranges */
    M.data = (ss_range *)malloc(sizeof(ss_range) * ((size_t)M.nsym + 2));
    M.code = (ss_range *)malloc(sizeof(ss_range) * ((size_t)M.nsym + 2));
    if (!M.data || !M.code)
        return -1;
    int first_data = 1, first_code = 1;
    for (int i = 0; i < M.nsym; i++) {
        const ss_sym *s = &M.sym[i];
        uintptr_t a = M.img.base + s->rva;
        if (s->is_code) {
            int c = s->ccls;
            if (first_code) {
                M.code[0].lo = M.img.text_lo;
                M.code[0].cls = SS_HOST;
                M.ncode = 1;
                first_code = 0;
            }
            if (M.code[M.ncode - 1].cls != c) {
                M.code[M.ncode - 1].hi = a;
                M.code[M.ncode].lo = a;
                M.code[M.ncode].cls = c;
                M.ncode++;
            }
        } else {
            int c = s->dcls;
            if (first_data) {
                /* bytes before the first named data symbol: not ours */
                M.data[0].lo = M.img.data_lo;
                M.data[0].cls = SS_HOST;
                M.ndata = 1;
                first_data = 0;
            }
            if (M.data[M.ndata - 1].cls != c) {
                M.data[M.ndata - 1].hi = a;
                M.data[M.ndata].lo = a;
                M.data[M.ndata].cls = c;
                M.ndata++;
            }
        }
    }
    if (M.ndata)
        M.data[M.ndata - 1].hi = M.img.data_hi;
    if (M.ncode)
        M.code[M.ncode - 1].hi = M.img.text_hi;
    /* drop empty ranges (two symbols at one address) */
    int w = 0;
    for (int i = 0; i < M.ndata; i++)
        if (M.data[i].hi > M.data[i].lo)
            M.data[w++] = M.data[i];
    M.ndata = w;
    if (!M.ndata || !M.ncode) {
        snprintf(err, cap, "%s: no symbols in .text/.data", path);
        return -1;
    }
    M.ready = 1;
    return 0;
}

int ss_map_ready(void) { return M.ready; }
const ss_image *ss_map_image(void) { return &M.img; }

int ss_map_code_class(uintptr_t a)
{
    if (!M.ready || a < M.img.text_lo || a >= M.img.text_hi)
        return SS_HOST;
    int lo = 0, hi = M.ncode - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (M.code[mid].lo <= a)
            lo = mid;
        else
            hi = mid - 1;
    }
    return M.code[lo].cls;   /* read-only after load: safe from any thread */
}

int ss_map_data_ranges(const ss_range **out)
{
    *out = M.data;
    return M.ready ? M.ndata : 0;
}

const char *ss_map_describe(uintptr_t a, char *buf, size_t cap)
{
    if (!M.ready || !M.nsym) {
        snprintf(buf, cap, "0x%08lx", (unsigned long)a);
        return buf;
    }
    uint32_t rva = (uint32_t)(a - M.img.base);
    int lo = 0, hi = M.nsym - 1;
    if (a < M.img.base || a >= M.img.base + M.img.size_of_image || rva < M.sym[0].rva) {
        snprintf(buf, cap, "0x%08lx", (unsigned long)a);
        return buf;
    }
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (M.sym[mid].rva <= rva)
            lo = mid;
        else
            hi = mid - 1;
    }
    snprintf(buf, cap, "%s+0x%x (%s)", M.text + M.sym[lo].name, (unsigned)(rva - M.sym[lo].rva),
             M.text + M.sym[lo].obj);
    return buf;
}
