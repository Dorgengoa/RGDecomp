/* SPDX-License-Identifier: CC0-1.0 */
/* A stand-in for the game's EE sound driver, for tools and tests: it sends the same
 * requests the game sends (docs/SOUND-PROTOCOL.md "What the game sends" and "Flow")
 * through the SIF RPC path to the HLE servers. Not used by the game build. */
#ifndef RG_SND_EESIM_H
#define RG_SND_EESIM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* sif_init + iop_reset + snd_install, no clock (pull with snd_render), then the
 * game's init sequence: sceSdInit, MVOL, SK master volume/effect/SPDIF,
 * SoundSpuInit's effect areas (EEA 0x1FFFFF / 0x1DFFFF), reverb mode/depth. */
int snd_ee_boot(void);

typedef struct snd_ee_bank {
    int entry;          /* SKHSYNTH bank entry */
    int msin_track;     /* SK track with the MSIN input (SE key ons) */
    int midi_track;     /* SK track with the MIDI input (-1 if no sequence) */
    uint32_t hd_iop, bd_spu;
} snd_ee_bank;

/* Upload an HD/BD pair (HD to IOP heap, BD through a 0x400 staging buffer with
 * G0/0xA), register it (G1/0/3), create an MSIN input (G3/0/0, G3/0/5) and attach
 * the bank at `slot` (G1/0/5). If sq != NULL also register the sequence (G2/0/0),
 * attach a MIDI track (G2/0/5) and attach the bank there too. 0 ok. */
int snd_ee_load_bank(const uint8_t *hd, uint32_t hd_size, const uint8_t *bd, uint32_t bd_size,
                     uint32_t spu_addr, int slot, const uint8_t *sq, uint32_t sq_size,
                     snd_ee_bank *out);

/* G3/2/0x11 key on (+ the 0x42 volume and 0x41 pitch bend the game sends after it), as
 * SoundThreadCmdKeyOn_1b6800 sends them: x (F9 01) = pan, then volume, then bend.
 * snd_ee_key_on uses pan 0x40, volume 0x7F, bend 0x2000. */
int snd_ee_key_on_ex(int track, int id, int slot, int prog, int note, int vel, int pan, int vol, int bend);
int snd_ee_key_on(int track, int id, int slot, int prog, int note, int vel);
int snd_ee_key_off(int track, int id, int slot, int prog, int note);
/* G2/2/0 play (block), 0x30 volume, 2 stop. */
int snd_ee_seq_play(int track, int block, int vol);
int snd_ee_seq_stop(int track);

#ifdef __cplusplus
}
#endif
#endif
