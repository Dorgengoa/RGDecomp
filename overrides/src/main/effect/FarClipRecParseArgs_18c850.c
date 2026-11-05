/* rg-override: replaces game/src/main/effect/FarClipRecParseArgs_18c850.c sha256 8e9bc73f90c2e784782af4e7b6596c499c572a6dfd1f30eaf2e9a6957ff0a26c
 * why: draw-distance research spike (docs/P6-STATUS.md "Draw distance / LOD bias", investigation
 * only, like RG_CULL_WIDEN): $RG_FARCLIP_SCALE=K multiplies every far-clip record's far distance
 * (map defaults, map parts, map models: the per-object distance fade) as the map script sets
 * it ($RG_FARCLIP_NEAR=1: the near distance too, i.e. the near / far model swaps move as well);
 * $RG_FARCLIP_LOG=1 prints each record parsed.  Unset = the generated body unchanged.  NOT presentation-only: objects drawn beyond
 * retail's far clip draw lit-light flicker / fire-flare numbers from the game's shared
 * Rand_133710, so the run hash moves in scenes that have them (the spike measures it). */
/* rgp:protos */
#define RGP_SELF_FarClipRecParseArgs_18c850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

typedef struct T18c850 {
    s32 f00;
    s32 f04;
    s32 f08;
    f32 f0C;
    f32 f10;
    s32 f14;
} T18c850;

extern char D_00459CF8[];
extern char *getenv(const char *);
extern double atof(const char *);
#include <stdio.h>

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);
/*rgp*/

void FarClipRecParseArgs_18c850(T18c850 *self, Cur8 *q, s32 mode)
{
    char *s;

    self->f0C = VariantGetFloat_15f740(q++);
    self->f14 = VariantGetInt_15f780(q++);
    if (mode >= 3) {
        self->f10 = VariantGetFloat_15f740(q++);
    }
    if (self->f0C > 0.0f || self->f10 > 0.0f) {
        self->f04 = 1;
    }
    if (mode >= 4) {
        s = ((char *)SlotGetInt_15f720(q++));
        if (s != 0) {
            if (strcmp(s, D_00459CF8) == 0) {
                self->f08 = 1;
            }
        }
    }
    if (mode >= 5) {
        FarClipRecApplyPreset_18c950(self, VariantGetInt_15f780(q));
    }
    {
        static float k = -1.0f;
        if (k < 0.0f) {
            const char *e = getenv("RG_FARCLIP_SCALE");
            k = e && *e ? (float)atof(e) : 0.0f;
        }
        if (getenv("RG_FARCLIP_LOG"))
            fprintf(stderr, "FARCLIP mode=%d far=%.1f near=%.1f fade=%d flag=%d\n", (int)mode, (double)self->f0C,
                    (double)self->f10, (int)self->f14, (int)self->f08);
        if (k > 0.0f) {
            self->f0C = self->f0C * k;      /* far: shown while nearer than this */
            if (getenv("RG_FARCLIP_NEAR"))
                self->f10 = self->f10 * k;  /* near: shown while farther (a near/far model swap) */
        }
    }
}
