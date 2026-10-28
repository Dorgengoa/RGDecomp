/* Bindings test for the platform lane: the interrupt-handler overrides run as
 * real handlers under the kernel HLE (src/ps2/kernel) with HW_* going through
 * the hwbus (GS CSR, T0_COUNT, VIF1_FBRST); RegisterGlobalObject against the
 * crt's DestroyGlobalChain; the missing/ NameTableNodeSetImage stand-in
 * against hand-computed GS TEX0/TEX1 words; the MSL ostream flush/sentry
 * (src/crt) on a hand-built basic_ios.  Like overrides/, derived from the
 * game's behaviour and not covered by the repository's CC0 dedication. */
#include "types.h"
#include "bt.h"

/* ---- host side (platform_host.c) ---- */
extern int bth_kernel_run(void (*main_fn)(void *));
extern unsigned bth_violations(void);
extern int bth_create_sema(int init, int max);
extern int bth_wait_sema(int id);
extern int bth_signal_sema(int id);
extern int bth_sema_count(int id);
extern void bth_delete_sema(int id);
extern int bth_add_intc(int cause, s32 (*fn)(s32), int next);
extern void bth_remove_intc(int cause, int id);
extern void bth_raise_intc(int cause);
extern void bth_poll(void);
extern int bth_wait_vblank(void);
extern void bth_gs_set_field(int f);
extern void bth_t0_start(void);
extern u32 bth_t0_count(void);
extern void bth_vif1_set_irq(int v);
extern int bth_vif1_irq(void);
extern u64 bth_vif_writes(void);

/* ---- under test ---- */
extern s32 GfxVblankStartHandler_15df20(s32 cause);
extern s32 Vif1IntcHandler_15e170(s32 cause);
extern s32 SoundVblankIntrHandler_1bd6f0(s32 cause);
extern s32 MovieDmacHandler_1d4b10(s32 cause);
extern s32 MovieVblankHandler_1d4c90(s32 cause);
extern s32 RegisterGlobalObject_100dc0(s32 a, s32 b, void *n);
extern void DestroyGlobalChain_100d60(void *unused);
extern s32 NameTableNodeSetImage_15a640(void *tex, s32 id, char *name, s32 *mips, s32 w, s32 h,
                                        s32 bpp, s32 clut, u64 t1, s64 s36);
extern void *OstreamFlush_1040b0(void *os);
extern void *WOstreamFlush_104320(void *os);
extern void *OstreamSentryCtor_106230(void *sentry, void *os);

/* ---- game data the handlers read (the data layer emits these in the game) ---- */
s32 D_004810B0, D_004810B4, D_004810C0, D_004810C4, D_004810C8, D_004810D0, D_004810D4;
s32 D_0047DF14, D_0047DF18;
s32 D_00481504, D_00481508, D_0047E214;

static int g_fails;
static int cb_calls, cb_cause, cb_busy;
static int probe_calls;

static void gfx_cb(s32 cause)
{
    cb_calls++;
    cb_cause = cause;
    cb_busy = D_004810D4;
}

static s32 probe(s32 cause)
{
    (void)cause;
    probe_calls++;
    return 0;
}

static void wait_sound_vblank(void)
{
    s32 c = D_00481508;
    int n = 0;
    while (D_00481508 == c && n++ < 4)
        bth_wait_vblank();
}

static void guest(void *arg)
{
    int f = 0, id, id4, s, sema;
    u64 w0;
    u32 t;
    (void)arg;

    /* -- GfxVblankStartHandler: VBLANK_START (cause 2) -- */
    bth_t0_start();
    D_0047DF18 = bth_create_sema(0, 1);
    D_004810D0 = (s32)(unsigned long)gfx_cb;
    D_004810C0 = 1; /* WaitVsyncCount's request */
    D_004810C4 = 0;
    D_004810C8 = -5;
    bth_gs_set_field(1);
    id = bth_add_intc(2, GfxVblankStartHandler_15df20, -1);
    BT_EQ(f, bth_wait_sema(D_0047DF18) >= 0, 1); /* the handler signals it */
    BT_EQ(f, D_004810C4, BT_WRONG(1));
    BT_EQ(f, D_004810C0, 0);
    BT_EQ(f, D_004810D4, 0);
    BT_EQ(f, D_004810C8, 0); /* CSR.FIELD = 1 -> 0 */
    BT_EQ(f, cb_calls, 1);
    BT_EQ(f, cb_cause, 2);
    BT_EQ(f, cb_busy, 1); /* busy while the callback runs */
    /* no request, no callback, field 0, counter wraps to 0 instead of negative */
    D_004810D0 = 0;
    D_004810C4 = 0x7FFFFFFF;
    bth_gs_set_field(0);
    bth_wait_vblank();
    BT_EQ(f, D_004810C4, 0);
    BT_EQ(f, D_004810C8, 1);
    BT_EQ(f, cb_calls, 1);
    BT_EQ(f, bth_sema_count(D_0047DF18), 0); /* not signalled */
    bth_wait_vblank();
    BT_EQ(f, D_004810C4, 1);
    bth_remove_intc(2, id);

    /* -- Vif1IntcHandler: INTC VIF1 (cause 5) only -- */
    sema = bth_create_sema(0, 1);
    D_0047DF14 = sema;
    D_004810B0 = 0;
    D_004810B4 = -1;
    bth_vif1_set_irq(1);
    w0 = bth_vif_writes();
    id = bth_add_intc(5, Vif1IntcHandler_15e170, -1);
    id4 = bth_add_intc(4, Vif1IntcHandler_15e170, -1); /* same function on VIF0 */
    bth_raise_intc(4);
    bth_poll();
    BT_EQ(f, D_004810B0, 0); /* cause != 5: nothing */
    BT_EQ(f, bth_vif1_irq(), 1);
    bth_raise_intc(5);
    BT_EQ(f, bth_wait_sema(sema) >= 0, 1);
    t = bth_t0_count();
    BT_EQ(f, D_004810B0, 1);
    BT_EQ(f, (u32)D_004810B4, t);           /* T0_COUNT at the interrupt */
    BT_EQ(f, bth_vif1_irq(), 0);            /* VIF1_FBRST = STC reached the VIF */
    BT_EQ(f, bth_vif_writes() - w0, 1);
    D_0047DF14 = -1;                        /* no sema: count only */
    bth_raise_intc(5);
    bth_poll();
    BT_EQ(f, D_004810B0, 2);
    BT_EQ(f, bth_vif_writes() - w0, 1);
    BT_EQ(f, bth_sema_count(sema), 0);
    bth_remove_intc(5, id);
    bth_remove_intc(4, id4);

    /* -- SoundVblankIntrHandler: VBLANK_END (cause 3) -- */
    s = bth_create_sema(0, 1);
    D_0047E214 = s;
    D_00481504 = 0;
    D_00481508 = 0;
    id = bth_add_intc(3, SoundVblankIntrHandler_1bd6f0, -1);
    BT_EQ(f, bth_wait_sema(s) >= 0, 1); /* count 0: iPollSema fails -> iSignalSema */
    BT_EQ(f, D_00481508, 1);
    BT_EQ(f, D_00481504, 0);
    bth_signal_sema(s);                 /* count 1: iPollSema takes it, no signal */
    wait_sound_vblank();
    BT_EQ(f, D_00481508, 2);
    BT_EQ(f, bth_sema_count(s), 0);
    D_00481504 = 1;                     /* busy: counter only */
    wait_sound_vblank();
    BT_EQ(f, D_00481508, 3);
    BT_EQ(f, bth_sema_count(s), 0);
    BT_EQ(f, D_00481504, 1);
    D_00481504 = 0;
    wait_sound_vblank();
    BT_EQ(f, D_00481508, 4);
    BT_EQ(f, bth_sema_count(s), 1);
    bth_remove_intc(3, id);

    /* -- movie handlers: return 0, so the chain goes on -- */
    probe_calls = 0;
    id = bth_add_intc(2, MovieVblankHandler_1d4c90, 0); /* head, as MoviePlayerStart did */
    id4 = bth_add_intc(2, MovieDmacHandler_1d4b10, -1);
    s = bth_add_intc(2, probe, -1);
    bth_wait_vblank();
    BT_EQ(f, probe_calls, 1);
    bth_remove_intc(2, id);
    bth_remove_intc(2, id4);
    bth_remove_intc(2, s);

    g_fails += f;
}

/* ---- RegisterGlobalObject + DestroyGlobalChain ---- */
extern struct { void *head; s32 pad[3]; } D_004853D0;
static int dtor_log[4], dtor_n, dtor_flag;

static void dtor_rec(void *obj, s32 flag)
{
    if (dtor_n < 4)
        dtor_log[dtor_n++] = *(s32 *)obj;
    dtor_flag = flag;
}

/* ---- NameTableNodeReset (game C) stand-in ---- */
static int reset_calls;
void NameTableNodeReset_15ada0(void *node)
{
    reset_calls++;
    __builtin_memset(node, 0, 0x68);
}

typedef struct {
    s16 id, w, h, bpp;
    char name[0x20];
    u16 size;
    u8 pad2A[2];
    s32 total;
    s16 stride;
    u8 count;
    u8 pad33[3];
    s16 s36;
    u64 tex0;
    u64 tex1;
    u8 pad48[8];
    s32 mip[4];
    s32 clut;
    u8 tail[0x10];
} BtTex;

/* ---- ostream fixtures ---- */
static int sync_calls, sync_ret;
static s32 bt_pubsync(void *sb)
{
    (void)sb;
    sync_calls++;
    return sync_ret;
}

int bt_ovr_platform(void)
{
    int f = 0;
    g_fails = 0;

    /* handlers under the kernel + hwbus models */
    BT_EQ(f, bth_kernel_run(guest), 0); /* PS2K_RUN_MAIN_EXIT */
    BT_EQ(f, bth_violations(), 0);      /* every kernel call in the right context */
    f += g_fails;

    /* RegisterGlobalObject pushes {next, dtor, obj} at D_004853D0 */
    {
        static struct { void *next; s32 b, a; } n1, n2;
        static s32 o1 = 11, o2 = 22;
        D_004853D0.head = 0;
        BT_EQ(f, RegisterGlobalObject_100dc0((s32)(unsigned long)&o1, (s32)(unsigned long)dtor_rec, &n1),
              (s32)(unsigned long)&o1);
        RegisterGlobalObject_100dc0((s32)(unsigned long)&o2, (s32)(unsigned long)dtor_rec, &n2);
        BT_EQ(f, D_004853D0.head == (void *)&n2, 1);
        BT_EQ(f, n2.next == (void *)&n1, 1);
        BT_EQ(f, n1.next == 0, 1);
        dtor_n = 0;
        DestroyGlobalChain_100d60(0);
        BT_EQ(f, dtor_n, 2);
        BT_EQ(f, dtor_log[0], 22); /* last registered first */
        BT_EQ(f, dtor_log[1], 11);
        BT_EQ(f, dtor_flag, -1);
        BT_EQ(f, D_004853D0.head == 0, 1);
    }

    /* NameTableNodeSetImage_15a640 (hand-computed from the retail listing) */
    {
        BtTex t;
        s32 mips[4];
        char nm[] = "TEX";
        char empty[] = "";
        reset_calls = 0;
        /* 256x256 32 bpp, no mip list */
        __builtin_memset(&t, 0xAA, sizeof t);
        BT_EQ(f, NameTableNodeSetImage_15a640(&t, 3, nm, 0, 256, 256, 32, 0x1234, 0, 7), 1);
        BT_EQ(f, reset_calls, 1);
        BT_EQ(f, t.id, 3);
        BT_EQ(f, t.w, 256);
        BT_EQ(f, t.h, 256);
        BT_EQ(f, t.bpp, 32);
        BT_EQ(f, t.s36, 7);
        BT_EQ(f, t.name[0] == 'T' && t.name[3] == 0, 1);
        BT_EQ(f, t.total, 1024);
        BT_EQ(f, t.size, 1024);
        BT_EQ(f, t.clut, 0);
        BT_EQ(f, t.tex0, 0x620010000ull); /* TBW 4, PSMCT32, TW 8, TH 8, TCC */
        BT_EQ(f, t.tex1, 0x260);
        /* 100x50 8 bpp, two mip levels, caller TEX1 with L = 2, K = 0x123 */
        mips[0] = 0x1000; mips[1] = 0x2000; mips[2] = 0; mips[3] = 0;
        BT_EQ(f, NameTableNodeSetImage_15a640(&t, -10, nm, mips, 100, 50, 8, 0x5555,
                                              (2ull << 19) | (0x123ull << 32), 0), 1);
        BT_EQ(f, t.total, 31);     /* 25 + 6 (size /4 per level) */
        BT_EQ(f, t.size, 32);      /* rounded up to 32 */
        BT_EQ(f, t.mip[0], 0x1000);
        BT_EQ(f, t.mip[1], 0x2000);
        BT_EQ(f, t.clut, 0x5555);
        BT_EQ(f, t.stride, 0x400);
        BT_EQ(f, t.count, 1);
        BT_EQ(f, t.id, -10);
        BT_EQ(f, t.tex0, 0x200000059D308000ull); /* TBW 2, PSMT8, TW 7, TH 6, TCC, CLD */
        BT_EQ(f, t.tex1, 0x12300100364ull);      /* MXL 1, MMIN 5, L 2, K 0x123 */
        /* same without the caller's TEX1: K = -0x78 sign-extended */
        NameTableNodeSetImage_15a640(&t, 0, nm, mips, 100, 50, 8, 0, 0, 0);
        BT_EQ(f, t.tex1, 0xFFFFFF8800000368ull);
        /* 4 bpp: CLUT stride 0x40 */
        NameTableNodeSetImage_15a640(&t, 0, nm, 0, 64, 64, 4, 1, 0, 0);
        BT_EQ(f, t.stride, 0x40);
        BT_EQ(f, (s32)((t.tex0 >> 20) & 0x3F), 0x14);
        /* all four levels given: retail leaves last = -1, total 0 */
        mips[2] = 0x3000; mips[3] = 0x4000;
        NameTableNodeSetImage_15a640(&t, 0, nm, mips, 64, 64, 16, 0, 0, 0);
        BT_EQ(f, t.total, 0);
        BT_EQ(f, t.tex1, 0x260);
        /* rejected: empty name (before the reset), unknown depth (after it) */
        reset_calls = 0;
        BT_EQ(f, NameTableNodeSetImage_15a640(&t, 0, empty, 0, 64, 64, 32, 0, 0, 0), 0);
        BT_EQ(f, reset_calls, 0);
        BT_EQ(f, NameTableNodeSetImage_15a640(&t, 0, nm, 0, 64, 64, 12, 0, 0, 0), 0);
        BT_EQ(f, reset_calls, 1);
    }

    /* MSL ostream flush / sentry on a hand-built basic_ios */
    {
        static u32 vtbl[8];
        static u32 sbuf[4];
        static u8 ios[0x48];
        static u8 ios2[0x48];
        static void *os[1], *os2[1], *os_null[1];
        u8 sentry[8];
        vtbl[6] = (u32)(unsigned long)bt_pubsync; /* +0x18 */
        sbuf[0] = (u32)(unsigned long)vtbl;
        __builtin_memset(ios, 0, sizeof ios);
        *(u32 *)(ios + 0x20) = (u32)(unsigned long)sbuf;
        os[0] = ios;
        sync_calls = 0;
        sync_ret = 0;
        BT_EQ(f, OstreamFlush_1040b0(os) == (void *)os, 1);
        BT_EQ(f, sync_calls, 1);
        BT_EQ(f, ios[0x3A], 0);
        sync_ret = -1; /* pubsync fails: badbit */
        OstreamFlush_1040b0(os);
        BT_EQ(f, ios[0x3A], 1);
        /* sentry on a failed stream: not ok, failbit added */
        OstreamSentryCtor_106230(sentry, os);
        BT_EQ(f, sentry[0], 0);
        BT_EQ(f, ios[0x3A], 5);
        /* tie: a good stream's sentry flushes its tie first */
        __builtin_memset(ios, 0, sizeof ios);
        *(u32 *)(ios + 0x20) = (u32)(unsigned long)sbuf;
        __builtin_memset(ios2, 0, sizeof ios2);
        *(u32 *)(ios2 + 0x40) = (u32)(unsigned long)os; /* os2 tied to os */
        *(u32 *)(ios2 + 0x20) = (u32)(unsigned long)sbuf;
        os2[0] = ios2;
        sync_calls = 0;
        sync_ret = 0;
        OstreamSentryCtor_106230(sentry, os2);
        BT_EQ(f, sentry[0], 1);
        BT_EQ(f, sentry[1], 0);
        BT_EQ(f, sync_calls, 1);
        /* no rdbuf: nothing to sync, state untouched */
        *(u32 *)(ios + 0x20) = 0;
        sync_calls = 0;
        WOstreamFlush_104320(os);
        BT_EQ(f, sync_calls, 0);
        BT_EQ(f, ios[0x3A], 0); /* retail: rdbuf 0 skips straight to ~sentry */
        /* never-constructed standard stream (ios pointer 0): left alone */
        os_null[0] = 0;
        BT_EQ(f, OstreamFlush_1040b0(os_null) == (void *)os_null, 1);
    }
    return f;
}
