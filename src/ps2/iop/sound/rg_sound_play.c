/* SPDX-License-Identifier: CC0-1.0 */
/* rg-sound-play: render a bank program/SE or a sequence from the game's data to a WAV
 * file, headless, through the same HLE servers the game talks to (docs/SOUND.md).
 *
 *   rg-sound-play [--data DIR] --snd snd2\sy_000.snd --list
 *   rg-sound-play --snd snd2\sy_000.snd --prog 3 [--note N] [--vel 127] [--hold 1.0]
 *                 [--pan 0x40] [--sevol 0x7F] [--bend 0x2000] [--len 3.0] [-o out.wav]
 *     (--pan/--sevol/--bend: the key on's F9 01 pan and the 0x42 volume / 0x41 bend the
 *      EE sends after it; the title cursor is --prog 4 --note 60 --sevol 0x28)
 *   rg-sound-play --snd snd2\bgm\bg_000.snd --seq [--block 0] [--len 60] [-o out.wav]
 *
 * --data defaults to $RG_DATA, else "data". Exit 0 on success. Prints the render hash
 * (FNV-1a of the s16 output) so runs can be compared. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snd.h"
#include "snd_eesim.h"
#include "snd_hd.h"
#include "snd_pack.h"
#include "spu2.h"

static void put32(FILE *f, uint32_t v) { fputc((int)(v & 0xFF), f); fputc((int)((v >> 8) & 0xFF), f); fputc((int)((v >> 16) & 0xFF), f); fputc((int)(v >> 24), f); }
static void put16(FILE *f, uint16_t v) { fputc(v & 0xFF, f); fputc(v >> 8, f); }

static int write_wav(const char *path, const int16_t *lr, uint32_t frames)
{
    FILE *f = fopen(path, "wb");
    if (!f)
        return -1;
    uint32_t bytes = frames * 4;
    fwrite("RIFF", 1, 4, f);
    put32(f, 36 + bytes);
    fwrite("WAVEfmt ", 1, 8, f);
    put32(f, 16);
    put16(f, 1);
    put16(f, 2);
    put32(f, 48000);
    put32(f, 48000 * 4);
    put16(f, 4);
    put16(f, 16);
    fwrite("data", 1, 4, f);
    put32(f, bytes);
    for (uint32_t i = 0; i < frames * 2; i++)
        put16(f, (uint16_t)lr[i]);
    fclose(f);
    return 0;
}

static void usage(void)
{
    fprintf(stderr, "usage: rg-sound-play [--data DIR] --snd PATH (--list | --prog N [--note N] [--vel V]\n"
                    "         [--hold SEC] [--pan P] [--sevol V] [--bend B] | --seq [--block B] [--vol V])\n"
                    "         [--len SEC] [-o out.wav]\n");
}

int main(int argc, char **argv)
{
    const char *data = getenv("RG_DATA") ? getenv("RG_DATA") : "data";
    const char *snd = NULL, *out = "rg-sound-play.wav";
    int list = 0, prog = -1, note = -1, vel = 127, seq = 0, block = 0, vol = 0x80;
    int pan = 0x40, sevol = 0x7F, bend = 0x2000;
    double hold = 1.0, len = -1;
    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        const char *v = i + 1 < argc ? argv[i + 1] : NULL;
        if (!strcmp(a, "--data") && v) { data = v; i++; }
        else if (!strcmp(a, "--snd") && v) { snd = v; i++; }
        else if (!strcmp(a, "--list")) list = 1;
        else if (!strcmp(a, "--prog") && v) { prog = atoi(v); i++; }
        else if (!strcmp(a, "--note") && v) { note = atoi(v); i++; }
        else if (!strcmp(a, "--vel") && v) { vel = atoi(v); i++; }
        else if (!strcmp(a, "--hold") && v) { hold = atof(v); i++; }
        else if (!strcmp(a, "--len") && v) { len = atof(v); i++; }
        else if (!strcmp(a, "--seq")) seq = 1;
        else if (!strcmp(a, "--block") && v) { block = atoi(v); i++; }
        else if (!strcmp(a, "--vol") && v) { vol = atoi(v); i++; }
        else if (!strcmp(a, "--pan") && v) { pan = (int)strtol(v, NULL, 0); i++; }
        else if (!strcmp(a, "--sevol") && v) { sevol = (int)strtol(v, NULL, 0); i++; }
        else if (!strcmp(a, "--bend") && v) { bend = (int)strtol(v, NULL, 0); i++; }
        else if (!strcmp(a, "-o") && v) { out = v; i++; }
        else { usage(); return 2; }
    }
    if (!snd || (!list && prog < 0 && !seq)) {
        usage();
        return 2;
    }
    uint32_t size = 0;
    uint8_t *pack = snd_data_load(data, snd, &size);
    if (!pack) {
        fprintf(stderr, "rg-sound-play: %s not found under %s\n", snd, data);
        return 1;
    }
    snd_pack_entry e[64];
    int n = snd_pack_list(pack, size, e, 64);
    const snd_pack_entry *hd = snd_pack_find(e, n, ".hd"), *bd = snd_pack_find(e, n, ".bd");
    const snd_pack_entry *sq = snd_pack_find(e, n, ".sq");
    if (!hd || !bd) {
        fprintf(stderr, "rg-sound-play: %s has no .hd/.bd pair\n", snd);
        return 1;
    }
    snd_hd h;
    int pr = snd_hd_parse(&h, pack + hd->offset, hd->size);
    if (pr < 0) {
        fprintf(stderr, "rg-sound-play: HD parse error %d\n", pr);
        return 1;
    }
    if (list) {
        printf("%s: hd %u bytes, bd %u bytes, %u programs, %u samples, %u vags%s\n", snd, hd->size, bd->size,
               h.nprog, h.nsmpl, h.nvagi, sq ? ", has .sq" : "");
        for (int i = 0; i < n; i++)
            printf("  entry %-24s %8u bytes\n", e[i].name, e[i].size);
        for (uint32_t p = 0; p < h.nprog; p++) {
            snd_hd_prog pg;
            if (snd_hd_get_prog(&h, (int)p, &pg) < 0)
                continue;
            snd_hd_split sp;
            if (snd_hd_get_split(&h, &pg, 0, &sp) < 0)
                continue;
            snd_hd_layer l[4];
            int nl = snd_hd_resolve(&h, (int)p, sp.key_lo, 100, l, 4);
            printf("  prog %3u: %u split(s), keys %u..%u, vol %u", p, pg.nsplit, sp.key_lo, sp.key_hi, pg.volume);
            if (nl > 0)
                printf(", base note %u, %u Hz, adsr %04X/%04X, attr %02X", l[0].sample.base_note, l[0].vag.rate,
                       l[0].sample.adsr1, l[0].sample.adsr2, l[0].sample.spu_attr);
            printf("\n");
        }
        free(pack);
        return 0;
    }
    if (snd_ee_boot() < 0) {
        fprintf(stderr, "rg-sound-play: HLE boot failed\n");
        return 1;
    }
    snd_ee_bank b;
    int r = snd_ee_load_bank(pack + hd->offset, hd->size, pack + bd->offset, bd->size, 0x5040, 0,
                             seq && sq ? pack + sq->offset : NULL, seq && sq ? sq->size : 0, &b);
    if (r < 0) {
        fprintf(stderr, "rg-sound-play: bank load failed (%d)\n", r);
        return 1;
    }
    if (len < 0)
        len = seq ? 60.0 : hold + 2.0;
    uint32_t frames = (uint32_t)(len * 48000.0);
    int16_t *buf = (int16_t *)calloc(frames, 4);
    if (!buf)
        return 1;
    if (seq) {
        if (b.midi_track < 0) {
            fprintf(stderr, "rg-sound-play: %s has no .sq\n", snd);
            return 1;
        }
        snd_ee_seq_play(b.midi_track, block, vol);
        for (uint32_t done = 0; done < frames;) {
            uint32_t n = frames - done < 48000 ? frames - done : 48000;
            snd_render(buf + 2 * (size_t)done, n);
            done += n;
            if (getenv("RG_SOUND_VERBOSE"))
                printf("t=%5.1fs voices=%d midi_ticks=%u playing=%d\n", done / 48000.0, snd_voices_playing(),
                       snd_midi_ticks(b.midi_track), snd_midi_playing(b.midi_track));
        }
    } else {
        if (note < 0) {
            snd_hd_prog pg;
            snd_hd_split sp;
            snd_hd_layer l[4];
            note = 60;
            if (snd_hd_get_prog(&h, prog, &pg) == 0 && snd_hd_get_split(&h, &pg, 0, &sp) == 0 &&
                snd_hd_resolve(&h, prog, sp.key_lo, vel, l, 4) > 0)
                note = l[0].sample.base_note < sp.key_lo ? sp.key_lo
                       : l[0].sample.base_note > sp.key_hi ? sp.key_hi : l[0].sample.base_note;
        }
        uint32_t hf = (uint32_t)(hold * 48000.0);
        if (hf > frames)
            hf = frames;
        snd_ee_key_on_ex(b.msin_track, 0x66, 0, prog, note, vel, pan, sevol, bend);
        snd_render(buf, hf);
        snd_ee_key_off(b.msin_track, 0x66, 0, prog, note);
        snd_render(buf + 2 * (size_t)hf, frames - hf);
    }
    uint64_t hash = 1469598103934665603ull, sq_sum = 0;
    int peak = 0;
    for (uint32_t i = 0; i < frames * 2; i++) {
        uint16_t s = (uint16_t)buf[i];
        hash = (hash ^ (s & 0xFF)) * 1099511628211ull;
        hash = (hash ^ (s >> 8)) * 1099511628211ull;
        int a = buf[i] < 0 ? -buf[i] : buf[i];
        if (a > peak)
            peak = a;
        sq_sum += (uint64_t)((int64_t)buf[i] * buf[i]);
    }
    const snd_stats *st = snd_get_stats();
    printf("frames=%u peak=%d meansq=%llu key_ons=%u seq_notes=%u no_layer=%u steals=%u clips=%u hash=%016llx\n",
           frames, peak,
           (unsigned long long)(sq_sum / (frames * 2ull)), st->key_ons, st->seq_notes, st->no_layer, st->voice_steals,
           ((spu2 *)snd_spu())->stats.clips, (unsigned long long)hash);
    if (write_wav(out, buf, frames) < 0) {
        fprintf(stderr, "rg-sound-play: cannot write %s\n", out);
        return 1;
    }
    printf("wrote %s\n", out);
    free(buf);
    free(pack);
    return 0;
}
