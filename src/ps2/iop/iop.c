/* SPDX-License-Identifier: CC0-1.0 */
/* IOP RAM, sysmem-style heap, module/reboot log. See iop.h. */
#include "iop.h"
#include "rg_iop.h" /* census counters (docs/NATIVE-IOP.md) */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t g_ram[IOP_RAM_SIZE];
static uint64_t (*g_clock)(void);
static void (*g_report)(const char *msg);
static uint32_t g_reports;

static uint64_t now(void) { return g_clock ? g_clock() : 0; }

void iop_set_clock(uint64_t (*fn)(void)) { g_clock = fn; }
void iop_set_report(void (*fn)(const char *msg)) { g_report = fn; }
uint32_t iop_report_count(void) { return g_reports; }

static void report(const char *fmt, uint32_t a, uint32_t b)
{
    char msg[160];
    snprintf(msg, sizeof msg, fmt, a, b);
    g_reports++;
    if (g_report)
        g_report(msg);
    else
        fprintf(stderr, "[iop] %s\n", msg);
}

/* ---- RAM ---------------------------------------------------------------- */
uint8_t *iop_ram(void) { return g_ram; }

uint32_t iop_phys(uint32_t addr)
{
    addr &= 0x1FFFFFFFu;               /* KSEG0/KSEG1 */
    if (addr >= 0x1C000000u && addr < 0x1C800000u)
        addr -= 0x1C000000u;           /* 0xBC000000 mirror of IOP RAM (seen from the EE) */
    return addr;
}

void *iop_ptr(uint32_t addr, uint32_t len)
{
    RG_IOP_HLE("iop_ptr");
    uint32_t p = iop_phys(addr);
    if (p >= IOP_RAM_SIZE || len > IOP_RAM_SIZE - p) {
        report("IOP access out of RAM: addr=0x%08X len=0x%X", addr, len);
        return NULL;
    }
    return g_ram + p;
}

int iop_write(uint32_t addr, const void *src, uint32_t len)
{
    RG_IOP_HLE("iop_write");
    void *d = iop_ptr(addr, len);
    if (!d)
        return -1;
    if (len)
        memmove(d, src, len);
    return 0;
}

int iop_read(uint32_t addr, void *dst, uint32_t len)
{
    RG_IOP_HLE("iop_read");
    const void *s = iop_ptr(addr, len);
    if (!s)
        return -1;
    if (len)
        memmove(dst, s, len);
    return 0;
}

uint32_t iop_addr_of(const void *host_ptr)
{
    const uint8_t *p = (const uint8_t *)host_ptr;
    if (p < g_ram || p >= g_ram + IOP_RAM_SIZE)
        return 0xFFFFFFFFu;
    return (uint32_t)(p - g_ram);
}

void iop_ram_clear(void) { memset(g_ram, 0, sizeof g_ram); }

/* ---- heap ----------------------------------------------------------------
 * A sorted array of allocated blocks inside [IOP_HEAP_BASE, IOP_HEAP_END).
 * First fit from the bottom, like sysmem's default (low) allocation. */
#define HEAP_GRAN 0x100u
#define HEAP_MAX_BLOCKS 512
typedef struct { uint32_t addr, size; } hblk;
static hblk g_blk[HEAP_MAX_BLOCKS];
static int g_nblk;
static uint32_t g_static_top = IOP_STATIC_BASE;

void iop_heap_reset(void) { g_nblk = 0; }

uint32_t iop_heap_alloc(uint32_t size)
{
    RG_IOP_HLE("iop_heap_alloc");
    if (size == 0 || size > IOP_HEAP_END - IOP_HEAP_BASE || g_nblk >= HEAP_MAX_BLOCKS)
        return 0;
    size = (size + HEAP_GRAN - 1) & ~(HEAP_GRAN - 1);
    uint32_t cur = IOP_HEAP_BASE;
    int i;
    for (i = 0; i <= g_nblk; i++) {
        uint32_t lim = (i < g_nblk) ? g_blk[i].addr : IOP_HEAP_END;
        if (lim - cur >= size)
            break;
        if (i < g_nblk)
            cur = g_blk[i].addr + g_blk[i].size;
    }
    if (i > g_nblk)
        return 0;
    memmove(&g_blk[i + 1], &g_blk[i], (size_t)(g_nblk - i) * sizeof(hblk));
    g_blk[i].addr = cur;
    g_blk[i].size = size;
    g_nblk++;
    return cur;
}

static int heap_find(uint32_t addr)
{
    uint32_t p = iop_phys(addr);
    for (int i = 0; i < g_nblk; i++)
        if (g_blk[i].addr == p)
            return i;
    return -1;
}

int iop_heap_free(uint32_t addr)
{
    RG_IOP_HLE("iop_heap_free");
    int i = heap_find(addr);
    if (i < 0) {
        report("FreeSysMemory of a non-block 0x%08X (%u live blocks)", addr, (uint32_t)g_nblk);
        return -1;
    }
    memmove(&g_blk[i], &g_blk[i + 1], (size_t)(g_nblk - i - 1) * sizeof(hblk));
    g_nblk--;
    return 0;
}

uint32_t iop_heap_block_size(uint32_t addr)
{
    int i = heap_find(addr);
    return i < 0 ? 0 : g_blk[i].size;
}

int iop_heap_count(void) { return g_nblk; }

uint32_t iop_heap_free_total(void)
{
    uint32_t used = 0;
    for (int i = 0; i < g_nblk; i++)
        used += g_blk[i].size;
    return (IOP_HEAP_END - IOP_HEAP_BASE) - used;
}

uint32_t iop_heap_max_free(void)
{
    uint32_t best = 0, cur = IOP_HEAP_BASE;
    for (int i = 0; i <= g_nblk; i++) {
        uint32_t lim = (i < g_nblk) ? g_blk[i].addr : IOP_HEAP_END;
        if (lim - cur > best)
            best = lim - cur;
        if (i < g_nblk)
            cur = g_blk[i].addr + g_blk[i].size;
    }
    return best;
}

uint32_t iop_static_alloc(uint32_t size)
{
    RG_IOP_HLE("iop_static_alloc");
    uint32_t a = (g_static_top + 63u) & ~63u;
    if (size > IOP_HEAP_BASE - a)
        return 0;
    g_static_top = a + size;
    return a;
}

/* ---- modules / reboots -------------------------------------------------- */
static iop_module_rec g_mod[IOP_MOD_MAX];
static int g_nmod;
#define REBOOT_MAX 16
static iop_reboot_rec g_reboot[REBOOT_MAX];
static int g_nreboot;

/* Modules whose services the HLE covers (or that export none to the EE). */
static const struct { const char *name; const char *hle; } k_known[] = {
    {"SIO2MAN", "none needed (pad/mc transport)"},
    {"PADMAN", "padman placeholder 0x80000100/0x80000101"},
    {"MCMAN", "none needed (mcserv backend)"},
    {"MCSERV", "mcserv placeholder 0x80000400"},
    {"LIBSD", "none needed (sound HLE)"},
    {"SDRDRV", "sdr_driver 0x80000701 (sound HLE)"},
    {"MODHSYN", "sound HLE (SK hsynth)"},
    {"MODMIDI", "sound HLE (SK MIDI)"},
    {"MODMSIN", "sound HLE (SK MSIN)"},
    {"CDVDSTM", "none (no EE sceCdSt client linked)"},
    {"SKSOUND", "sound HLE (via sdr_driver 0x90F0)"},
    {"SKHSYNTH", "sound HLE (via sdr_driver 0x90F0)"},
    {"SKMIDI", "sound HLE (via sdr_driver 0x90F0)"},
    {"SKMSIN", "sound HLE (via sdr_driver 0x90F0)"},
    {"PCMPLAY", "pcm_mixer 0x123456 (sound HLE)"},
};

static void base_name(const char *path, char *out, size_t outsz)
{
    const char *b = path;
    for (const char *p = path; *p; p++)
        if (*p == '\\' || *p == '/' || *p == ':')
            b = p + 1;
    size_t n = 0;
    while (b[n] && b[n] != '.' && b[n] != ';' && n + 1 < outsz) {
        out[n] = (char)toupper((unsigned char)b[n]);
        n++;
    }
    out[n] = 0;
}

void iop_reset(void)
{
    RG_IOP_HLE("iop_reset");
    iop_ram_clear();
    iop_heap_reset();
    g_static_top = IOP_STATIC_BASE;
    g_nmod = 0;
}

void iop_reboot(const char *image)
{
    RG_IOP_HLE("iop_reboot");
    iop_reset();
    if (g_nreboot < REBOOT_MAX) {
        iop_reboot_rec *r = &g_reboot[g_nreboot++];
        snprintf(r->image, sizeof r->image, "%s", image ? image : "");
        r->when = now();
    }
}

int iop_module_load(const char *path, const char *args, int argsz)
{
    RG_IOP_HLE("iop_module_load");
    if (g_nmod >= IOP_MOD_MAX) {
        report("module table full (%u), dropping load #%u", IOP_MOD_MAX, (uint32_t)g_nmod + 1);
        return -1;
    }
    iop_module_rec *m = &g_mod[g_nmod];
    memset(m, 0, sizeof *m);
    m->id = g_nmod + 1;
    snprintf(m->path, sizeof m->path, "%s", path ? path : "");
    base_name(m->path, m->name, sizeof m->name);
    if (argsz < 0)
        argsz = 0;
    m->argsz = argsz;
    int n = argsz < (int)sizeof m->args - 1 ? argsz : (int)sizeof m->args - 1;
    for (int i = 0; i < n && args; i++)
        m->args[i] = args[i] ? args[i] : '|';
    m->hle = "NO HLE (unknown module)";
    for (size_t k = 0; k < sizeof k_known / sizeof k_known[0]; k++)
        if (strcmp(m->name, k_known[k].name) == 0) {
            m->known = 1;
            m->hle = k_known[k].hle;
        }
    m->when = now();
    g_nmod++;
    if (!m->known)
        report("LoadModule of a module the HLE does not know (#%u)", (uint32_t)m->id, 0);
    return m->id;
}

int iop_module_count(void) { return g_nmod; }
const iop_module_rec *iop_module_get(int i) { return (i >= 0 && i < g_nmod) ? &g_mod[i] : NULL; }

const iop_module_rec *iop_module_find(const char *name)
{
    for (int i = 0; i < g_nmod; i++)
        if (strcmp(g_mod[i].name, name) == 0)
            return &g_mod[i];
    return NULL;
}

int iop_reboot_count(void) { return g_nreboot; }
const iop_reboot_rec *iop_reboot_get(int i) { return (i >= 0 && i < g_nreboot) ? &g_reboot[i] : NULL; }
void iop_log_clear(void) { g_nmod = 0; g_nreboot = 0; }

void iop_module_dump(void *file)
{
    FILE *f = file ? (FILE *)file : stderr;
    for (int i = 0; i < g_nreboot; i++)
        fprintf(f, "[iop] reboot #%d image='%s' at %llu\n", i + 1, g_reboot[i].image,
                (unsigned long long)g_reboot[i].when);
    for (int i = 0; i < g_nmod; i++)
        fprintf(f, "[iop] module %2d %-9s %-40s args='%s' -> %s\n", g_mod[i].id, g_mod[i].name,
                g_mod[i].path, g_mod[i].args, g_mod[i].hle);
}
