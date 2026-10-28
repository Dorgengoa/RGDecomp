/* SPDX-License-Identifier: CC0-1.0 */
/* Game-facing glue (movie_game.h, docs/MOVIE.md).
 *   rg-movie-glue-tests game           exit 0 pass, 1 fail, 77 skipped */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie_game.h"

#define FAILF(...)                                                \
    do {                                                          \
        fprintf(stderr, "FAIL %s:%d: ", __FILE__, __LINE__);      \
        fprintf(stderr, __VA_ARGS__);                             \
        fputc('\n', stderr);                                      \
        return 1;                                                 \
    } while (0)
#define CHECK(c, ...)                 \
    do {                              \
        if (!(c)) FAILF(__VA_ARGS__); \
    } while (0)

static uint64_t g_now;
static uint64_t clk(void) { return g_now; }

static int t_game(void)
{
    const char *data = getenv("RG_DATA");
    if (!data || !*data) {
        printf("skipped: RG_DATA not set\n");
        return 77;
    }
    rg_movie_g_set_clock(clk);
    rg_movie_g_set_data_root(data);
    for (int mode = 0; mode < 2; mode++) {
        rg_movie_g_set_sync(mode);
        g_now = 0;
        CHECK(rg_movie_g_open("cdrom0:\\MOVIE\\00\\GAMEOVER.MVI;1", 1, 0) == 0, "open");
        int w, h;
        rg_movie_g_size(&w, &h);
        CHECK(w == 512 && h == 336, "size %dx%d", w, h);
        /* the game's own start condition (audio preset) holds the display start */
        CHECK(rg_movie_g_update(0) == 0, "started while the gate is closed");
        uint8_t hdr[40];
        CHECK(rg_movie_g_read_ss(hdr, 40) == 40 && !memcmp(hdr, "SShd", 4), "SS stream");
        CHECK(rg_movie_g_update(1) & 1, "started");
        uint8_t *buf = (uint8_t *)malloc((size_t)w * h * 4);
        unsigned shown = 0;
        int fl = 0;
        for (uint64_t k = 0; k < 2000 && !(fl & 2); k++) {
            g_now = k * 2460060ull;
            fl = rg_movie_g_update(1);
            if (k % 2 == 0) shown += (unsigned)rg_movie_g_take_frame(buf);
            if (k == 100) {
                unsigned before = shown;
                rg_movie_g_pause(1);
                for (int j = 0; j < 50; j++) {
                    g_now += 2460060ull;
                    rg_movie_g_update(1);
                    shown += (unsigned)rg_movie_g_take_frame(buf);
                }
                CHECK(shown == before, "frames while paused");
                rg_movie_g_pause(0);
                k += 50;
            }
        }
        CHECK(fl & 2, "finished");
        CHECK(shown >= 205 && shown <= 210 && rg_movie_g_frames_decoded() == 210, "shown %u decoded %u", shown,
              rg_movie_g_frames_decoded());
        CHECK(buf[3] == 0x80, "PS2 block alpha");
        free(buf);
        rg_movie_g_close();
        CHECK(rg_movie_g_update(1) == 2, "closed reads finished");
    }
    /* a movie that cannot be played reads as finished, never hangs */
    CHECK(rg_movie_g_open("MOVIE/00/NOPE.MVI", 1, 0) != 0, "missing movie");
    CHECK(rg_movie_g_update(1) & 2, "missing movie finished");
    rg_movie_g_close();
    rg_movie_g_set_clock(NULL);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) return 2;
    int r = !strcmp(argv[1], "game") ? t_game() : 2;
    printf("%s %s\n", argv[1], r == 0 ? "ok" : r == 77 ? "skipped" : "FAIL");
    return r;
}
