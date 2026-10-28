/* SPDX-License-Identifier: CC0-1.0 */
/* EE sound-driver stand-in for tools/tests, see snd_eesim.h. */
#include "snd_eesim.h"

#include <string.h>

#include "iop.h"
#include "sif.h"
#include "snd.h"

static int32_t sk(uint32_t mod, uint32_t sub, int n, const uint32_t *args)
{
    uint32_t b[16] = {0};
    b[0] = mod << 24;
    b[1] = sub;
    for (int i = 0; i < n && i < 14; i++)
        b[2 + i] = args[i];
    return snd_sk(b);
}

#define SK(mod, sub, ...)                                                 \
    sk(mod, sub, (int)(sizeof((uint32_t[]){__VA_ARGS__}) / sizeof(uint32_t)), \
       (const uint32_t[]){__VA_ARGS__})

int snd_ee_boot(void)
{
    sif_config sc;
    sif_default_config(&sc);
    sif_init(&sc);
    iop_reset();
    if (snd_install(NULL) != 0)
        return -1;
    snd_set_clock(NULL, NULL);
    /* SdRemoteInitMasterVolume_165608 */
    snd_sdremote(0x8000, 0, 0, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0x980, 0x3FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0xA80, 0x3FFF, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0x981, 0, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0xA81, 0, 0, 0, 0, 0);
    /* SKSOUND init values seen from the EE */
    SK(0, 2, 0, 0x8F, 0x880);
    SK(0, 2, 3, 0x82, 0);
    SK(0, 2, 3, 0x83, 0x105, 0, 0);
    SK(0, 2, 3, 0x80, 0x7F, 0x7F);
    /* SoundSpuInit_1bb710: effect off, EEA per core, mode 4 depth 0x28 on core 0 */
    snd_sdremote(0x8010, 0x800, 0xFFCC, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0x801, 0xFFCC, 0, 0, 0, 0);
    snd_sdremote(0x8070, 2, 0, 0, 0, 0, 0);
    snd_sdremote(0x8070, 3, 0, 0, 0, 0, 0);
    snd_sdremote(0x8050, 0x1D00, 0x1FFFFF, 0, 0, 0, 0);
    snd_sdremote(0x8050, 0x1D01, 0x1DFFFF, 0, 0, 0, 0);
    uint32_t attr0[16] = {0, 4 | 0x100, 0, 0}; /* sceSdEffectAttr {int core, int mode, s16 depth L/R, ..} */
    uint32_t attr1[16] = {1, 0 | 0x100, 0, 0};
    snd_sdremote(0x8130, 0, (uint32_t)(uintptr_t)attr0, 0, 0, 0, 0);
    snd_sdremote(0x8130, 1, (uint32_t)(uintptr_t)attr1, 0, 0, 0, 0);
    snd_sdremote(0x8070, 2, 1, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0xB80, 0x2800, 0, 0, 0, 0);
    snd_sdremote(0x8010, 0xC80, 0x2800, 0, 0, 0, 0);
    return 0;
}

int snd_ee_load_bank(const uint8_t *hd, uint32_t hd_size, const uint8_t *bd, uint32_t bd_size,
                     uint32_t spu_addr, int slot, const uint8_t *sq, uint32_t sq_size, snd_ee_bank *out)
{
    memset(out, 0, sizeof *out);
    out->midi_track = -1;
    uint32_t hp = iop_heap_alloc(hd_size + 4);
    if (!hp)
        return -1;
    hp = (hp + 3) & ~3u;
    iop_write(hp, hd, hd_size);
    uint32_t staging = iop_heap_alloc(0x404);
    if (!staging)
        return -1;
    for (uint32_t o = 0; o < bd_size; o += 0x400) {
        uint32_t n = bd_size - o < 0x400 ? bd_size - o : 0x400;
        uint8_t chunk[0x400] = {0};
        memcpy(chunk, bd + o, n);
        iop_write(staging, chunk, 0x400);
        if (SK(0, 0xA, 0, staging, spu_addr + o, 0x400) < 0)
            return -2;
    }
    iop_heap_free(staging);
    out->hd_iop = hp;
    out->bd_spu = spu_addr;
    out->entry = SK(1, 0, 3, (uint32_t)-1, hp, hd_size, spu_addr, bd_size);
    if (out->entry < 0)
        return -3;
    int msin = SK(3, 0, 0, (uint32_t)-1);
    if (msin < 0)
        return -4;
    out->msin_track = SK(3, 0, 5, (uint32_t)-1, (uint32_t)msin);
    if (out->msin_track < 0)
        return -5;
    if (SK(1, 0, 5, (uint32_t)out->msin_track, (uint32_t)out->entry, (uint32_t)slot) < 0)
        return -6;
    if (sq && sq_size) {
        uint32_t qp = iop_heap_alloc(sq_size + 4);
        if (!qp)
            return -7;
        qp = (qp + 3) & ~3u;
        iop_write(qp, sq, sq_size);
        int e = SK(2, 0, 0, (uint32_t)-1, qp, sq_size);
        if (e < 0)
            return -8;
        out->midi_track = SK(2, 0, 5, (uint32_t)-1, (uint32_t)e);
        if (out->midi_track < 0)
            return -9;
        if (SK(1, 0, 5, (uint32_t)out->midi_track, (uint32_t)out->entry, (uint32_t)slot) < 0)
            return -10;
    }
    return 0;
}

int snd_ee_key_on_ex(int track, int id, int slot, int prog, int note, int vel, int pan, int vol, int bend)
{
    int r = SK(3, 2, (uint32_t)track, 0x11, (uint32_t)id, (uint32_t)slot, (uint32_t)prog, 0, (uint32_t)note,
               (uint32_t)vel, (uint32_t)pan);
    SK(3, 2, (uint32_t)track, 0x42, (uint32_t)id, 0, (uint32_t)note, (uint32_t)vol);
    SK(3, 2, (uint32_t)track, 0x41, (uint32_t)id, 0, (uint32_t)note, (uint32_t)bend);
    return r;
}

int snd_ee_key_on(int track, int id, int slot, int prog, int note, int vel)
{
    return snd_ee_key_on_ex(track, id, slot, prog, note, vel, 0x40, 0x7F, 0x2000);
}

int snd_ee_key_off(int track, int id, int slot, int prog, int note)
{
    return SK(3, 2, (uint32_t)track, 0x13, (uint32_t)id, (uint32_t)slot, (uint32_t)prog, 0, (uint32_t)note, 0, 0);
}

int snd_ee_seq_play(int track, int block, int vol)
{
    SK(2, 2, (uint32_t)track, 0x30, 0, (uint32_t)vol);
    return SK(2, 2, (uint32_t)track, 0, 0, (uint32_t)block);
}

int snd_ee_seq_stop(int track) { return SK(2, 2, (uint32_t)track, 2, 0); }
