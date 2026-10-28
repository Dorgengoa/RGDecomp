/* SPDX-License-Identifier: CC0-1.0
 *
 * Stack-guard census runtime (RG_SBGUARD=ON builds of a game tree ingested
 * with RG_PROTOS_SB_GUARD=1; docs/PROTOS.md "Stack-block census").
 *
 * The protos stage puts every local whose address a call receives inside
 *     unsigned char g[16 + sizeof(T) + 48]   (16-aligned, object at g + 16)
 * initialised here (meta + 0xA5 canaries) and checked by the cleanup
 * attribute when it goes out of scope.  A callee that wrote before or past
 * the C object leaves a changed canary: logged once per site to stderr and
 * appended to $RG_SBGUARD_LOG (default sbguard_census.tsv):
 *     site  side(pre|post|meta)  first_bad_off  last_bad_off  hits
 * (offsets relative to the object start; post offsets >= sizeof(T)).
 * Reads past the object are not seen.  Never a shipping build.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <process.h>
#define sbg_getpid() ((long)_getpid())
#else
#include <unistd.h>
#define sbg_getpid() ((long)getpid())
#endif

typedef struct rg_sbguard_site {
    const char *site;
    unsigned size;
    unsigned hits;
} rg_sbguard_site;

#define SBG_PRE 16
#define SBG_POST 48
#define SBG_PAT 0xA5
#define SBG_MAGIC 0x5B9D17C3u

static FILE *sbg_log;
/* the process that opened sbg_log: save states capture these statics, so after --load-state
 * sbg_log may be the saving process's FILE * (ubsan_census.c has the same guard, soak 2026-10-25) */
static long sbg_log_pid;
static unsigned sbg_total;

static void sbg_report(rg_sbguard_site *s, const char *side, int first, int last)
{
    const char *site = s ? s->site : "?";
    if (s && s->hits++)
        return;
    sbg_total++;
    fprintf(stderr, "SBGUARD %s %s overrun bytes [%d, %d] (object size %u)\n", site, side, first,
            last, s ? s->size : 0u);
    if (!sbg_log || sbg_log_pid != sbg_getpid()) {
        const char *p = getenv("RG_SBGUARD_LOG");
        sbg_log = fopen(p && *p ? p : "sbguard_census.tsv", "a");
        sbg_log_pid = sbg_getpid();
    }
    if (sbg_log) {
        fprintf(sbg_log, "%s\t%s\t%d\t%d\t%u\n", site, side, first, last, s ? s->size : 0u);
        fflush(sbg_log);
    }
}

int rg_sbguard_init(unsigned char *g, rg_sbguard_site *s)
{
    unsigned m = SBG_MAGIC ^ (unsigned)(size_t)s;
    memcpy(g, &s, 4);
    memcpy(g + 4, &m, 4);
    memset(g + 8, SBG_PAT, SBG_PRE - 8);
    memset(g + SBG_PRE + s->size, SBG_PAT, SBG_POST);
    return 0;
}

void rg_sbguard_chk(void *pv)
{
    unsigned char *g = (unsigned char *)pv;
    rg_sbguard_site *s;
    unsigned m;
    int i, first = -1, last = -1;
    memcpy(&s, g, 4);
    memcpy(&m, g + 4, 4);
    if ((m ^ (unsigned)(size_t)s) != SBG_MAGIC) {
        sbg_report(NULL, "meta", -SBG_PRE, -SBG_PRE + 7);
        return;
    }
    for (i = 8; i < SBG_PRE; i++)
        if (g[i] != SBG_PAT) {
            if (first < 0)
                first = i - SBG_PRE;
            last = i - SBG_PRE;
        }
    if (first >= 0) {
        sbg_report(s, "pre", first, last);
        memset(g + 8, SBG_PAT, SBG_PRE - 8);
    }
    first = last = -1;
    for (i = 0; i < SBG_POST; i++)
        if (g[SBG_PRE + s->size + i] != SBG_PAT) {
            if (first < 0)
                first = (int)s->size + i;
            last = (int)s->size + i;
        }
    if (first >= 0)
        sbg_report(s, "post", first, last);
}
