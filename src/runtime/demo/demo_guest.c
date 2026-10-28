/* SPDX-License-Identifier: CC0-1.0
 * Guest-side smoke workload (see demo_guest.h).  Everything here runs on EE
 * guest threads and goes through the SDK surface the game uses: eekernel,
 * libpad, libcdvd, libsif + libsdr (Standard Kit blocks), libdma + libgraph.
 * No game code, no direct model access except reading the drive's due time
 * for the test's exact-timing check. */
#include <stdio.h>
#include <string.h>

#include "demo_guest.h"

#include "cdvd.h"
#include "libcdvd.h"
#include "libdma.h"
#include "libgraph.h"
#include "libpad.h"
#include "libsif.h"
#include "ps2k.h"
/* last: it #defines DMAC_* names that dmac.h declares as enumerators */
#include "eekernel.h"

#ifdef _WIN32
#include <direct.h>
#define MKDIR(d) _mkdir(d)
#else
#include <sys/stat.h>
#define MKDIR(d) mkdir(d, 0777)
#endif

static rg_demo_config G = {RG_DEMO_ALL, 0, 10, 70};
static rg_demo_result Rz;
static volatile uint32_t g_field; /* fields seen by main's sceGsSyncV loop */

void rg_demo_default_config(rg_demo_config *c)
{
    c->parts = RG_DEMO_ALL;
    c->fields = 0;
    c->keyon_field = 10;
    c->keyoff_field = 70;
}

void rg_demo_setup(const rg_demo_config *c)
{
    if (c)
        G = *c;
    else
        rg_demo_default_config(&G);
    memset(&Rz, 0, sizeof Rz);
    Rz.pad_stable_field = -1;
    g_field = 0;
}

const rg_demo_result *rg_demo_get_result(void) { return &Rz; }

static int start_thread(void (*fn)(void *), int prio)
{
    static uint8_t stacks[4][0x1000] __attribute__((aligned(16)));
    static int next;
    struct ThreadParam tp;
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)fn;
    tp.stack = stacks[next & 3];
    tp.stackSize = (int)sizeof stacks[0];
    tp.initPriority = prio;
    next++;
    int id = CreateThread(&tp);
    if (id >= 0)
        StartThread(id, NULL);
    return id;
}

/* ====================================================================== pad */
static uint8_t g_padbuf[256] __attribute__((aligned(64)));

static void pad_thread(void *arg)
{
    (void)arg;
    unsigned char data[32];
    int aligned = 0, last_cross = -1;
    scePadInit(0);
    scePadPortOpen(0, 0, g_padbuf);
    for (;;) {
        sceGsSyncV(0);
        uint32_t f = g_field;
        int st = scePadGetState(0, 0);
        if (st != 6) /* scePadStateStable */
            continue;
        if (Rz.pad_stable_field < 0)
            Rz.pad_stable_field = (int)f;
        memset(data, 0xFF, sizeof data);
        if (scePadRead(0, 0, data) <= 0 || data[0] != 0)
            continue;
        uint16_t word = (uint16_t)(0xFFFFu ^ ((uint32_t)data[2] << 8 | data[3]));
        Rz.pad_reads++;
        if (f < RG_DEMO_MAX_FIELDS) {
            Rz.pad_word[f] = word;
            Rz.pad_vblank[f] = ps2k_vblank_count();
        }
        /* vibration: analog mode -> actuator alignment -> direct on CROSS */
        if (!aligned) {
            if (scePadGetReqState(0, 0) != 0) /* busy */
                continue;
            if (aligned == 0 && scePadSetMainMode(0, 0, 1, 3) == 1) {
                aligned = -1;
                continue;
            }
        }
        if (aligned == -1) {
            static const unsigned char align[6] = {0, 1, 0xFF, 0xFF, 0xFF, 0xFF};
            if (scePadGetReqState(0, 0) == 0 && scePadSetActAlign(0, 0, align) == 1) {
                aligned = 1;
                Rz.rumble_set = 1;
            }
            continue;
        }
        int cross = (word & 0x0040u) != 0;
        if (aligned == 1 && cross != last_cross) {
            unsigned char dir[6] = {(unsigned char)cross, (unsigned char)(cross ? 0xC0 : 0), 0, 0, 0, 0};
            if (scePadSetActDirect(0, 0, dir) == 1)
                last_cross = cross;
        }
    }
}

/* ======================================================================= cd */
static uint8_t g_cdbuf[2048] __attribute__((aligned(64)));

static void cd_thread(void *arg)
{
    (void)arg;
    sceCdlFILE f;
    sceCdRMode mode = {0, 0, SCECdSecS2048, 0};
    if (!sceCdInit(SCECdINIT)) {
        Rz.cd_ok = -1;
        snprintf(Rz.cd_text, sizeof Rz.cd_text, "no disc (sceCdInit)");
        ExitThread();
    }
    sceCdMmode(SCECdMmodeDvd);
    if (!sceCdSearchFile(&f, "\\SYSTEM.CNF;1")) {
        Rz.cd_ok = -1;
        snprintf(Rz.cd_text, sizeof Rz.cd_text, "SYSTEM.CNF not found");
        ExitThread();
    }
    Rz.cd_lsn = f.lsn;
    struct SemaParam sp = {0, 1, 0, 0, 0, 0};
    Rz.cd_sema_before = CreateSema(&sp);
    DeleteSema(Rz.cd_sema_before);
    memset(g_cdbuf, 0xEE, sizeof g_cdbuf);
    ps2k_poll(); /* bring the drive's clock to now (a defined point) */
    Rz.cd_issue_cycles = ps2k_now();
    if (!sceCdRead(f.lsn, 1, g_cdbuf, &mode)) {
        Rz.cd_ok = -1;
        snprintf(Rz.cd_text, sizeof Rz.cd_text, "sceCdRead refused");
        ExitThread();
    }
    uint64_t due_us = 0;
    if (cdvd_next_event(&due_us))
        Rz.cd_due_cycles = (due_us * 147456u + 999u) / 1000u;
    Rz.cd_busy_after_issue = sceCdSync(1);
    if (g_cdbuf[0] != 0xEE) /* data must not land before completion */
        Rz.cd_busy_after_issue = -1;
    sceCdSync(0);
    Rz.cd_done_cycles = ps2k_now();
    Rz.cd_sema_after = CreateSema(&sp);
    DeleteSema(Rz.cd_sema_after);
    if (sceCdGetError() != SCECdErNO) {
        Rz.cd_ok = -1;
        snprintf(Rz.cd_text, sizeof Rz.cd_text, "read error 0x%02x", sceCdGetError());
        ExitThread();
    }
    size_t n = 0;
    while (n < sizeof Rz.cd_text - 1 && g_cdbuf[n] && g_cdbuf[n] != '\r' && g_cdbuf[n] != '\n') {
        Rz.cd_text[n] = (char)g_cdbuf[n];
        n++;
    }
    Rz.cd_text[n] = 0;
    Rz.cd_ok = 1;
}

/* ==================================================================== sound */
/* A synthetic SCEI HD/BD bank (one program, one split, one looping ADPCM
 * sample), the same shape tests/sound builds. */
static void w32(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24); }
static void w16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); }
static void chunk(uint8_t *p, const char *rev, uint32_t size, uint32_t maxi)
{
    memcpy(p, "IECS", 4);
    memcpy(p + 4, rev, 4);
    w32(p + 8, size);
    w32(p + 12, maxi);
}

#define HD_SIZE 0x120
#define BD_BLOCKS 8
static uint8_t g_hd[HD_SIZE + 16] __attribute__((aligned(16)));
static uint8_t g_bd[0x400] __attribute__((aligned(16)));

static void make_bank(void)
{
    uint8_t *hd = g_hd;
    memset(hd, 0, sizeof g_hd);
    chunk(hd, "sreV", 0x10, 0x00020000);
    memset(hd + 0x10, 0xFF, 0x40);
    chunk(hd + 0x10, "daeH", 0x40, HD_SIZE);
    w32(hd + 0x20, BD_BLOCKS * 16);
    w32(hd + 0x24, 0xD0);
    w32(hd + 0x28, 0xB0);
    w32(hd + 0x2C, 0x70);
    w32(hd + 0x30, 0x50);
    chunk(hd + 0x50, "igaV", 0x20, 0);
    w32(hd + 0x60, 0x14);
    w32(hd + 0x64, 0);
    w16(hd + 0x68, 48000);
    hd[0x6A] = 1;
    hd[0x6B] = 0xFF;
    chunk(hd + 0x70, "lpmS", 0x40, 0);
    w32(hd + 0x80, 0x14);
    uint8_t *sm = hd + 0x84;
    sm[2] = 1; sm[4] = 127; sm[11] = 60; sm[13] = 0x40; sm[15] = 10; sm[16] = 0x80; sm[17] = 0xFF;
    w16(sm + 0x12, 0x000F);
    w16(sm + 0x14, 0x1FC0 | 0x0A);
    sm[0x29] = 0x13;
    chunk(hd + 0xB0, "tesS", 0x20, 0);
    w32(hd + 0xC0, 0x14);
    uint8_t *ss = hd + 0xC4;
    ss[1] = 1; ss[2] = 127; ss[3] = 1;
    chunk(hd + 0xD0, "gorP", 0x50, 0);
    w32(hd + 0xE0, 0x14);
    uint8_t *pg = hd + 0xE4;
    w32(pg, 0x24);
    pg[4] = 1; pg[5] = 0x14; pg[6] = 0x80; pg[7] = 0x40;
    uint8_t *spl = pg + 0x24;
    spl[4] = 127;
    w16(spl + 6, 0x400);
    w16(spl + 8, 0x400);
    spl[16] = 0x80; spl[17] = 0x40;

    memset(g_bd, 0, sizeof g_bd);
    for (int k = 1; k < BD_BLOCKS; k++) {
        uint8_t *b = g_bd + 16 * k;
        b[1] = k == 1 ? 4 : k == BD_BLOCKS - 1 ? 3 : 0;
        for (int i = 0; i < 28; i++)
            b[2 + i / 2] |= (uint8_t)(((i < 14 ? 2 : -2) & 0xF) << ((i & 1) * 4));
    }
}

/* one Standard Kit command block through sceSdRemote(0x90F0), as the game's
 * sound driver sends it (docs/SOUND-PROTOCOL.md) */
static int sk(uint32_t mod, uint32_t sub, int n, const uint32_t *args)
{
    static uint32_t blk[16] __attribute__((aligned(64)));
    memset(blk, 0, sizeof blk);
    blk[0] = mod << 24;
    blk[1] = sub;
    for (int i = 0; i < n && i < 14; i++)
        blk[2 + i] = args[i];
    return sceSdRemote(1, 0x90F0, (uint32_t)(uintptr_t)blk, 0x40, 0, 0, 0, 0);
}
#define SK(mod, sub, ...) \
    sk(mod, sub, (int)(sizeof((uint32_t[]){__VA_ARGS__}) / sizeof(uint32_t)), (const uint32_t[]){__VA_ARGS__})

static int sif_upload(const void *src, uint32_t iop, uint32_t size)
{
    sceSifDmaData d = {(unsigned int)(uintptr_t)src, iop, (size + 15u) & ~15u, 0};
    unsigned int id = sceSifSetDma(&d, 1);
    if (!id)
        return -1;
    while (sceSifDmaStat(id) >= 0)
        DelayThread(100);
    return 0;
}

static void snd_thread(void *arg)
{
    (void)arg;
    const uint32_t spu = 0x5040, note = 72;
    make_bank();
    sceSifInitRpc(0);
    if (sceSdRemoteInit(0) < 0)
        goto fail;
    /* SdRemoteInitMasterVolume: sceSdInit, MVOL both cores */
    sceSdRemote(1, 0x8000, 0, 0, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0x980, 0x3FFF, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0xA80, 0x3FFF, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0x981, 0, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0xA81, 0, 0, 0, 0, 0);
    /* SKSOUND init values the game sends */
    SK(0, 2, 0, 0x8F, 0x880);
    SK(0, 2, 3, 0x82, 0);
    SK(0, 2, 3, 0x83, 0x105, 0, 0);
    SK(0, 2, 3, 0x80, 0x7F, 0x7F); /* SK master volume */
    /* SoundSpuInit_1bb710: effect off, EEA per core, mode 4 depth 0x28 on core 0 */
    sceSdRemote(1, 0x8010, 0x800, 0xFFCC, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0x801, 0xFFCC, 0, 0, 0, 0);
    sceSdRemote(1, 0x8070, 2, 0, 0, 0, 0, 0);
    sceSdRemote(1, 0x8070, 3, 0, 0, 0, 0, 0);
    sceSdRemote(1, 0x8050, 0x1D00, 0x1FFFFF, 0, 0, 0, 0);
    sceSdRemote(1, 0x8050, 0x1D01, 0x1DFFFF, 0, 0, 0, 0);
    {
        static uint16_t attr0[32] __attribute__((aligned(16))) = {0, 4 | 0x100, 0, 0};
        static uint16_t attr1[32] __attribute__((aligned(16))) = {1, 0 | 0x100, 0, 0};
        sceSdRemote(1, 0x8130, 0, (uint32_t)(uintptr_t)attr0, 0, 0, 0, 0);
        sceSdRemote(1, 0x8130, 1, (uint32_t)(uintptr_t)attr1, 0, 0, 0, 0);
    }
    sceSdRemote(1, 0x8070, 2, 1, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0xB80, 0x2800, 0, 0, 0, 0);
    sceSdRemote(1, 0x8010, 0xC80, 0x2800, 0, 0, 0, 0);
    sceSifInitIopHeap();
    uint32_t hd_iop = (uint32_t)(uintptr_t)sceSifAllocIopHeap(HD_SIZE + 16);
    uint32_t staging = (uint32_t)(uintptr_t)sceSifAllocIopHeap(0x400);
    if (!hd_iop || !staging || sif_upload(g_hd, hd_iop, HD_SIZE) < 0 || sif_upload(g_bd, staging, 0x400) < 0)
        goto fail;
    if (SK(0, 0xA, 0, staging, spu, 0x400) < 0) /* BD -> SPU2 RAM */
        goto fail;
    Rz.snd_entry = SK(1, 0, 3, (uint32_t)-1, hd_iop, HD_SIZE, spu, BD_BLOCKS * 16);
    int msin = SK(3, 0, 0, (uint32_t)-1);
    Rz.snd_track = msin < 0 ? -1 : SK(3, 0, 5, (uint32_t)-1, (uint32_t)msin);
    if (Rz.snd_entry < 0 || Rz.snd_track < 0 ||
        SK(1, 0, 5, (uint32_t)Rz.snd_track, (uint32_t)Rz.snd_entry, 0) < 0)
        goto fail;
    while (g_field < G.keyon_field)
        sceGsSyncV(0);
    int id = SK(3, 2, (uint32_t)Rz.snd_track, 0x11, 0x70, 0, 0, 0, note, 127, 0);
    SK(3, 2, (uint32_t)Rz.snd_track, 0x42, 0x70, 0, note, 0x7F);
    SK(3, 2, (uint32_t)Rz.snd_track, 0x41, 0x70, 0, note, 0x2000);
    Rz.snd_keyon_vblank = ps2k_vblank_count();
    Rz.snd_ok = id == 0x70 ? 1 : -1;
    while (g_field < G.keyoff_field)
        sceGsSyncV(0);
    SK(3, 2, (uint32_t)Rz.snd_track, 0x13, 0x70, 0, 0, 0, note, 0, 0);
    return;
fail:
    Rz.snd_ok = -1;
}

/* ====================================================================== gfx */
/* VU1 microprogram: XGKICK vi00 (the packet at VU1 data qword 0), end. */
#define UNOP 0x000002FFu
#define LNOP 0x8000033Cu
#define U_E 0x40000000u
#define XGKICK(is) (0x80000000u | (uint32_t)(is) << 11 | (0x6Cu >> 2) << 6 | 0x3C | (0x6Cu & 3))
#define VC(cmd, num, imm) (((uint32_t)(cmd) << 24) | ((uint32_t)(num) << 16) | ((uint32_t)(imm) & 0xFFFF))
#define UNPACK_V4_32(num, addr) VC(0x6C, num, addr)

static sceGsDBuff g_db;
static uint32_t g_chain[2][64] __attribute__((aligned(16)));

/* one VIF1 packet: MPG the program, UNPACK a 2-sprite GIF packet, MSCAL */
static int build_chain(uint32_t *w, uint32_t frame, uint16_t pad)
{
    int n = 0;
    /* DMAtag END, QWC filled in below (TTE off: the tag's upper half is skipped) */
    w[n++] = 0;
    w[n++] = 0;
    w[n++] = 0;
    w[n++] = 0;
    int data0 = n;
    w[n++] = VC(0x00, 0, 0);      /* NOP */
    w[n++] = VC(0x4A, 2, 0);      /* MPG 2 instructions at 0 */
    w[n++] = XGKICK(0);
    w[n++] = UNOP | U_E;
    w[n++] = LNOP;
    w[n++] = UNOP;
    w[n++] = UNPACK_V4_32(9, 0);  /* 9 qwords to VU1 data 0 */
    /* GIF tag: NLOOP 2, EOP, PACKED, NREG 4: PRIM RGBAQ XYZ2 XYZ2 */
    w[n++] = 2 | 0x8000u;
    w[n++] = 4u << 28;
    w[n++] = 0x5510;
    w[n++] = 0;
    uint32_t ox = 1728, oy = 1824;
    /* a box that hides the last position, then the moving sprite */
    uint32_t bx = 220, by = 150;
    uint32_t sx = bx + 8 + (frame * 3) % 180, sy = by + 8 + (frame * 2) % 100;
    int held = (pad & 0x0040u) != 0;
    const uint32_t box[4] = {0x20, 0x20, 0x30, 0x80};
    const uint32_t spr[4] = {held ? 0x30u : 0xF0u, held ? 0xF0u : 0x40u, 0x40, 0x80};
    const uint32_t *col[2] = {box, spr};
    uint32_t x0[2] = {bx, sx}, y0[2] = {by, sy}, x1[2] = {bx + 220, sx + 32}, y1[2] = {by + 140, sy + 24};
    for (int i = 0; i < 2; i++) {
        w[n++] = 6; w[n++] = 0; w[n++] = 0; w[n++] = 0;                 /* PRIM sprite */
        for (int c = 0; c < 4; c++) w[n++] = col[i][c];                 /* RGBAQ */
        w[n++] = (ox + x0[i]) << 4; w[n++] = (oy + y0[i]) << 4; w[n++] = 0; w[n++] = 0;
        w[n++] = (ox + x1[i]) << 4; w[n++] = (oy + y1[i]) << 4; w[n++] = 0; w[n++] = 0;
    }
    w[n++] = VC(0x14, 0, 0);      /* MSCAL 0 */
    while ((n - data0) & 3)
        w[n++] = 0;               /* NOP padding to a whole qword */
    uint32_t qwc = (uint32_t)(n - data0) / 4;
    w[0] = qwc | (7u << 28);      /* id END */
    return n;
}

static void gfx_thread(void *arg)
{
    (void)arg;
    sceGsResetGraph(0, 1, 2, 1);  /* interlaced, NTSC, FRAME */
    sceGsResetPath();
    sceGsSetDefDBuff(&g_db, 0 /*CT32*/, 640, 448, 1 /*ZTST always*/, 0x31 /*Z24*/, 0);
    sceDmaChan *vif1 = sceDmaGetChan(1);
    for (uint32_t frame = 0;; frame++) {
        uint32_t f = g_field;
        uint16_t pad = f < RG_DEMO_MAX_FIELDS ? Rz.pad_word[f ? f - 1 : 0] : 0;
        uint32_t *w = g_chain[frame & 1];
        build_chain(w, frame, pad);
        sceGsSwapDBuff(&g_db, (int)(frame & 1));
        sceDmaSend(vif1, w);
        sceDmaSync(vif1, 0, 0);
        Rz.gfx_frames++;
        sceGsSyncV(0);
    }
}

/* ===================================================================== main */
int rg_demo_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    /* as the game: drop main below the workers it starts */
    ChangeThreadPriority(GetThreadId(), 60);
    if (G.parts & RG_DEMO_GFX)
        start_thread(gfx_thread, 20);
    if (G.parts & RG_DEMO_PAD)
        start_thread(pad_thread, 30);
    if (G.parts & RG_DEMO_SND)
        start_thread(snd_thread, 35);
    if (G.parts & RG_DEMO_CD)
        start_thread(cd_thread, 40);
    for (;;) {
        sceGsSyncV(0);
        g_field++;
        Rz.fields_done = g_field;
        if (G.fields && g_field >= G.fields)
            break;
    }
    return 0;
}

/* ================================================================== fixture */
static int put(const char *dir, const char *name, const void *data, size_t n)
{
    char p[600];
    snprintf(p, sizeof p, "%s/%s", dir, name);
    FILE *f = fopen(p, "wb");
    if (!f)
        return -1;
    size_t w = fwrite(data, 1, n, f);
    fclose(f);
    return w == n ? 0 : -1;
}

int rg_demo_write_fixture(const char *dir)
{
    static uint8_t bin[3 * 2048];
    char man[1024];
    const char *cnf = RG_DEMO_SYSTEM_CNF;
    MKDIR(dir);
    for (size_t i = 0; i < sizeof bin; i++)
        bin[i] = (uint8_t)(i * 7 + (i >> 11));
    snprintf(man, sizeof man,
             "# rg-extract manifest v2\n"
             "# source_sha1\t0000000000000000000000000000000000000000\n"
             "# source_size\t81920\n"
             "# source_serial\tSCUS-97490\tVER 1.01\n"
             "# volume\t0\t0\t40\n"
             "path\tsize\tsha256\tlba\tcopies\n"
             "DEMO.BIN\t%u\tx\t21\tL0:21\n"
             "SYSTEM.CNF\t%u\tx\t20\tL0:20\n",
             (unsigned)sizeof bin, (unsigned)strlen(cnf));
    if (put(dir, "SYSTEM.CNF", cnf, strlen(cnf)) || put(dir, "DEMO.BIN", bin, sizeof bin) ||
        put(dir, "MANIFEST.tsv", man, strlen(man)))
        return -1;
    return 0;
}
