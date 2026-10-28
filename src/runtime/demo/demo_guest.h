/* SPDX-License-Identifier: CC0-1.0
 * Guest-side smoke workload for rg-runtime-demo and tests/runtime: EE threads
 * that use the platform the way the game does, without game code
 * (docs/RUNTIME.md "rg-runtime-demo"). */
#ifndef RG_DEMO_GUEST_H
#define RG_DEMO_GUEST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RG_DEMO_PAD = 1,   /* libpad: open port 0, read every field, rumble on CROSS */
    RG_DEMO_CD = 2,    /* libcdvd: search + async read + sync of SYSTEM.CNF */
    RG_DEMO_SND = 4,   /* libsdr/SK: bank upload over SIF, SE key-on, key-off */
    RG_DEMO_GFX = 8,   /* libgraph + libdma: VIF1 MPG/UNPACK/MSCAL -> VU1 XGKICK -> GS */
    RG_DEMO_ALL = 15
};

typedef struct rg_demo_config {
    uint32_t parts;        /* RG_DEMO_* */
    uint32_t fields;       /* main returns after this many sceGsSyncV (0 = never) */
    uint32_t keyon_field;  /* SE key-on at this field (default 10) */
    uint32_t keyoff_field; /* key-off (default 70) */
} rg_demo_config;

#define RG_DEMO_MAX_FIELDS 4096
typedef struct rg_demo_result {
    /* pad */
    int pad_stable_field;          /* first field scePadGetState == STABLE (-1 never) */
    uint32_t pad_reads;
    uint16_t pad_word[RG_DEMO_MAX_FIELDS]; /* decoded word per field (0 before stable) */
    uint64_t pad_vblank[RG_DEMO_MAX_FIELDS]; /* kernel VBlank count at that read */
    int rumble_set;                /* SetActAlign done; SetActDirect follows CROSS */
    /* cd */
    int cd_ok;                     /* 1 read completed, -1 failed, 0 not run */
    char cd_text[64];              /* first bytes of SYSTEM.CNF */
    uint32_t cd_lsn;
    uint64_t cd_issue_cycles, cd_due_cycles, cd_done_cycles;
    int cd_busy_after_issue;       /* sceCdSync(1) right after sceCdRead */
    int cd_sema_before, cd_sema_after; /* a probe CreateSema id around the read */
    /* sound */
    int snd_ok;                    /* 1 key-on accepted, -1 failed */
    int snd_track, snd_entry;
    uint64_t snd_keyon_vblank;
    /* gfx */
    uint32_t gfx_frames;
    /* main */
    uint32_t fields_done;
} rg_demo_result;

void rg_demo_default_config(rg_demo_config *c);
/* Must be set before the runtime starts the EE (cfg.entry = rg_demo_entry). */
void rg_demo_setup(const rg_demo_config *c);
int rg_demo_entry(int argc, char **argv);
const rg_demo_result *rg_demo_get_result(void);

/* Write a small single-layer disc folder (MANIFEST.tsv v2 + SYSTEM.CNF +
 * DEMO.BIN) for runs without RG_DATA.  0 ok. */
int rg_demo_write_fixture(const char *dir);
#define RG_DEMO_SYSTEM_CNF "BOOT2 = cdrom0:\\SCUS_974.90;1\r\nVER = 1.01\r\nVMODE = NTSC\r\n"

#ifdef __cplusplus
}
#endif
#endif
