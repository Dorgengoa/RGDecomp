/* SPDX-License-Identifier: CC0-1.0 */
/* Native copy of the bring-up HLE parser (src/ps2/iop/sound/snd_hd.c). Sony Standard Kit "SCEI HD" sound-bank header (the .hd part of the game's snd2\*.snd
 * packs; the BD part is raw PS-ADPCM kept in host memory by the engine). Layout worked out from the
 * game's banks and the MODHSYN.IRX code that reads them (docs/SOUND.md "HD format").
 *
 *   chunk = { "IECS", name reversed ("sreV" = Vers), u32 chunk size, ... }
 *   Vers @0, Head @0x10: { .., u32 hd size @+0xC, u32 bd size @+0x10, u32 offsets of the
 *     Prog @+0x14, Sset @+0x18, Smpl @+0x1C, Vagi @+0x20 chunks (from the HD start) }
 *   Prog/Sset/Smpl/Vagi: { "IECS", name, u32 size, u32 max index, u32 off[max+1] }
 *     record offsets are relative to the chunk start; 0xFFFFFFFF = no record. */
#ifndef RG_NATIVE_RA_HD_H
#define RG_NATIVE_RA_HD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ra_hd_vag {     /* Vagi record, 8 bytes */
    uint32_t offset;            /* from the BD start */
    uint16_t rate;              /* sample rate (Hz) */
    uint8_t loop;
} ra_hd_vag;

typedef struct ra_hd_sample {  /* Smpl record, 0x2A bytes */
    uint16_t vag;
    uint8_t vel_lo, vel_xfade, vel_hi;
    int8_t vel_follow_pitch;
    uint8_t vel_follow_pitch_center, vel_follow_pitch_curve;
    int8_t vel_follow_amp;
    uint8_t vel_follow_amp_center, vel_follow_amp_curve;
    uint8_t base_note;          /* +0x0B: the note that plays at the VAG's own rate */
    int8_t detune;              /* +0x0C, 1/128 semitone */
    uint8_t pan;                /* +0x0D, 0x40 = centre */
    uint8_t group, priority, volume; /* +0x0E/+0x0F/+0x10 (0x80 = unity) */
    uint16_t adsr1, adsr2;      /* +0x12/+0x14, raw SPU2 registers */
    uint8_t lfo_attr;           /* +0x28 */
    uint8_t spu_attr;           /* +0x29: bit0 dry L, bit1 dry R, bit2 wet L, bit3 wet R,
                                   bits 4-5 core (0x10 core 0, 0x20 core 1, else either) */
} ra_hd_sample;

typedef struct ra_hd_sset {    /* Sset record: velocity window + sample list */
    uint8_t vel_curve, vel_lo, vel_hi, nsample;
    uint32_t samples_off;       /* byte offset (in the HD) of the u16 sample index list */
} ra_hd_sset;

typedef struct ra_hd_split {   /* split block inside a Prog record, 0x14 bytes */
    uint16_t sset;
    uint8_t key_lo, key_xfade, key_hi, number;
    uint16_t bend_lo, bend_hi;  /* pitch-bend range, 1/128 semitone at full deflection x2 */
    int8_t kf_pitch;
    uint8_t kf_pitch_center;
    int8_t kf_amp;
    uint8_t kf_amp_center;
    int8_t kf_pan;
    uint8_t kf_pan_center;
    uint8_t volume, pan;        /* 0x80 = unity, 0x40 = centre */
    int8_t transpose, detune;
} ra_hd_split;

typedef struct ra_hd_prog {    /* Prog record header, 0x24 bytes */
    uint32_t split_off;         /* from the record start */
    uint8_t nsplit, split_size, volume, pan;
    int8_t transpose, detune;
    int8_t kf_pan;              /* +0x0A, +0x0B: key-follow pan and its centre note (MODHSYN */
    uint8_t kf_pan_center;      /*   sub_41dc adds (note - centre) * kf / 12 to the pan) */
    uint32_t rec_off;           /* byte offset of the record in the HD */
} ra_hd_prog;

typedef struct ra_hd {
    const uint8_t *d;
    uint32_t size;
    uint32_t hd_size, bd_size;
    uint32_t prog, sset, smpl, vagi; /* chunk offsets (0 = absent) */
    uint32_t nprog, nsset, nsmpl, nvagi; /* max index + 1 */
} ra_hd;

/* Parse (validate) a header held in caller memory. 0 ok, < 0 error code. */
int ra_hd_parse(ra_hd *hd, const uint8_t *data, uint32_t size);
int ra_hd_get_prog(const ra_hd *hd, int prog, ra_hd_prog *out);          /* 0 ok, -1 absent */
int ra_hd_get_split(const ra_hd *hd, const ra_hd_prog *p, int i, ra_hd_split *out);
int ra_hd_get_sset(const ra_hd *hd, int index, ra_hd_sset *out);
int ra_hd_sset_sample(const ra_hd *hd, const ra_hd_sset *s, int i);      /* sample index or -1 */
int ra_hd_get_sample(const ra_hd *hd, int index, ra_hd_sample *out);
int ra_hd_get_vag(const ra_hd *hd, int index, ra_hd_vag *out);

/* Everything a key on needs for one sounding layer. */
typedef struct ra_hd_layer {
    ra_hd_prog prog;
    ra_hd_split split;
    ra_hd_sset sset;
    ra_hd_sample sample;
    ra_hd_vag vag;
} ra_hd_layer;
/* Resolve (prog, note, velocity) to up to `max` layers like MODHSYN's key on (sub_6cac):
 * every split whose key range (bit 7 of key lo/hi = crossfade flag, masked) holds the
 * note, its sample set if the velocity is in the set's window and the set is not empty,
 * and every sample of the set whose velocity range (bit 7 masked likewise) holds the
 * velocity. Returns the layer count (0 = silent). */
int ra_hd_resolve(const ra_hd *hd, int prog, int note, int vel, ra_hd_layer *out, int max);

#ifdef __cplusplus
}
#endif
#endif
