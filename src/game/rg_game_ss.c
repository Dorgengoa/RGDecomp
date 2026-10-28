/* SPDX-License-Identifier: CC0-1.0
 * rg-game's save-state CLI (docs/TEST-FIXTURES.md, src/savestate):
 *
 *   --save-state FIELD:FILE   write a state after FIELD (repeatable)
 *   --state-note TEXT         free text stored in the states written (milestone)
 *   --load-state FILE         start from a state (--fields stays absolute)
 *   RG_SS=1                   save-state machinery on without either flag
 *                             (a power-on baseline in the same mode)
 *   RG_SS_AUDIT=1             host-pointer audit after each save / load
 *
 * Host code: ss_map.c classifies this object as HOST (never restored).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "movie_game.h"
#include "ps2k.h"
#include "ps2k_ss.h"
#include "rg_game_ss.h"
#include "rg_runtime.h"
#include "rg_savestate.h"

extern uint32_t D_004810C4[]; /* the game's VBlank counter (input scripts key on it) */

#define RG_MAX_SAVE_STATES 16
static struct {
    uint64_t field;
    const char *path;
} g_save[RG_MAX_SAVE_STATES];
static int g_nsave;
static const char *g_load;
static const char *g_note = "";
static int g_on;

void rg_game_ss_early(int argc, char **argv)
{
    const char *e = getenv("RG_SS");
    int want = e && *e && *e != '0';
    for (int i = 1; i < argc; i++)
        if (!strcmp(argv[i], "--save-state") || !strcmp(argv[i], "--load-state"))
            want = 1;
    if (!want)
        return;
    if (rg_ss_init() != 0) {
        fprintf(stderr, "rg-game: save states unavailable: %s\n", rg_ss_error());
        return;
    }
    g_on = 1;
}

int rg_game_ss_arg(const char *a, const char *v)
{
    if (!strcmp(a, "--save-state")) {
        const char *c = v ? strchr(v, ':') : NULL;
        if (!c || g_nsave == RG_MAX_SAVE_STATES || !strtoull(v, NULL, 0) || !c[1])
            return -1;
        g_save[g_nsave].field = strtoull(v, NULL, 0);
        g_save[g_nsave].path = c + 1;
        g_nsave++;
        return 1;
    }
    if (!strcmp(a, "--state-note")) {
        if (!v)
            return -1;
        g_note = v;
        return 1;
    }
    if (!strcmp(a, "--load-state")) {
        if (!v)
            return -1;
        g_load = v;
        return 1;
    }
    return 0;
}

int rg_game_ss_saving(void) { return g_nsave; }

int rg_game_ss_before_init(void)
{
    if (!g_on) {
        if (g_nsave || g_load) {
            fprintf(stderr, "rg-game: save states requested but unavailable\n");
            return -1;
        }
        return 0;
    }
    void *base;
    size_t size;
    rg_ss_arena(&base, &size);
    if (ps2k_fiber_arena_set(base, size) != 0) {
        fprintf(stderr, "rg-game: save states: cannot use the fiber arena at %p\n", base);
        return -1;
    }
    rg_crt0_set_ram_provider(rg_ss_ram_alloc);
    /* subsystem hooks beyond the kernel and the runtime (one per subsystem) */
    static const rg_ss_hook movie = {
        "movie", NULL, NULL, rg_movie_g_ss_size, rg_movie_g_ss_save, NULL, rg_movie_g_ss_load, NULL,
    };
    if (rg_ss_register_default_hooks() != 0 || rg_ss_add_hook(&movie) != 0) {
        fprintf(stderr, "rg-game: save states: hook registration failed\n");
        return -1;
    }
    return 0;
}

int rg_game_ss_after_init(uint64_t *first_field)
{
    *first_field = 0;
    if (!g_on)
        return 0;
    rg_ss_mark_init_done();
    if (!g_load)
        return 0;
    rg_ss_meta m;
    char err[768];
    err[0] = 0;
    /* every check runs before a byte is written back: a refused state (other
     * build, corrupt, other options) leaves the process as it was */
    clock_t t0 = clock();
    if (rg_ss_load(g_load, &m, err, sizeof err) != 0) {
        int mid = strstr(err, "refused the state") || strstr(err, "cannot commit") != NULL;
        fprintf(stderr, "rg-game: --load-state %s: %s\n", mid ? "FAILED" : "refused", err);
        fflush(stderr);
        return mid ? -2 : -1;
    }
    *first_field = m.field;
    fprintf(stderr, "LOADSTATE field=%llu vbl=%u run_hash=%016llx ms=%ld note=\"%s\" %s\n",
            (unsigned long long)m.field, m.game_vbl, (unsigned long long)m.run_hash,
            (long)((clock() - t0) * 1000 / CLOCKS_PER_SEC), m.note, g_load);
    if (getenv("RG_SS_AUDIT"))
        rg_ss_audit(stderr, 40);
    return 0;
}

void rg_game_ss_field_done(uint64_t field, const char *input)
{
    for (int i = 0; i < g_nsave; i++) {
        if (g_save[i].field != field)
            continue;
        rg_ss_meta m;
        memset(&m, 0, sizeof m);
        m.field = field;
        m.game_vbl = D_004810C4[0];
        m.kernel_vblank = ps2k_vblank_count();
        m.kernel_now = ps2k_now();
        m.run_hash = rg_runtime_get_stats()->run_hash;
        m.created = (uint64_t)time(NULL);
        if (g_note[0]) {
            snprintf(m.note, sizeof m.note, "%s", g_note);
        } else {
            /* default note: the file's name without directory and extension */
            const char *bn = g_save[i].path, *q;
            for (q = bn; *q; q++)
                if (*q == '/' || *q == '\\')
                    bn = q + 1;
            snprintf(m.note, sizeof m.note, "%s", bn);
            char *dot = strrchr(m.note, '.');
            if (dot)
                *dot = 0;
        }
        snprintf(m.input, sizeof m.input, "%s", input ? input : "");
        char err[512];
        clock_t t0 = clock();
        if (rg_ss_save(g_save[i].path, &m, err, sizeof err) != 0) {
            fprintf(stderr, "rg-game: --save-state %llu: %s\n", (unsigned long long)field, err);
            continue;
        }
        long bytes = -1;
        FILE *f = fopen(g_save[i].path, "rb");
        if (f) {
            fseek(f, 0, SEEK_END);
            bytes = ftell(f);
            fclose(f);
        }
        fprintf(stderr, "SAVESTATE field=%llu vbl=%u run_hash=%016llx bytes=%ld ms=%ld %s\n",
                (unsigned long long)field, m.game_vbl, (unsigned long long)m.run_hash, bytes,
                (long)((clock() - t0) * 1000 / CLOCKS_PER_SEC), g_save[i].path);
        if (getenv("RG_SS_AUDIT"))
            rg_ss_audit(stderr, 40);
    }
}
