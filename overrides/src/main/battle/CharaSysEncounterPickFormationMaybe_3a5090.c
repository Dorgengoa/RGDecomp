/* rg-override: replaces game/src/main/battle/CharaSysEncounterPickFormationMaybe_3a5090.c sha256 5e01d2c94f7367ab59ba39d1306b6c8b0d9bdcba1515bd614c96bff0e1c12e03
 * why: test hook RG_FORCE_ENCOUNTER=GROUP (lane cactugus; docs/TEST-FIXTURES.md "Forced battles",
 * out/scenario/FORCE-API.md): a RANDOM encounter whose area table (obj, the encount_param record
 * the party's location selected) lists encount_group GROUP starts GROUP: the table's weighted
 * roll runs unchanged (same RandFloat calls), then its result is replaced by GROUP's entry, i.e.
 * one of the outcomes the game itself can roll there (the genuine battle, its assets loaded by
 * the game's own path).  A table without GROUP keeps the roll ("not found, kept").
 * RG_FORCE_ENCOUNTER_LOG=1 or the force prints one FORCEENC line per pick.  Unset = the
 * generated body (rg_force_encounter_id() reads getenv once; run hash unchanged). */
/* rgp:protos */
#define RGP_SELF_CharaSysEncounterPickFormationMaybe_3a5090 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include <stdio.h>
#include <stdint.h>

typedef struct Ent { s32 f0; s16 weight; s16 pad6; s32 pad8; } Ent;
typedef struct Obj { s16 id; u8 pad[0x2A]; s8 count; u8 pad2[3]; Ent *ents; } Obj;
typedef struct Cfg { u8 pad[0x24C]; u8 flags; } Cfg;
typedef struct Sys { u8 pad[0x20]; Cfg *cfg; } Sys;
extern Sys *D_004837C0;
extern s32 rg_force_encounter_id(void);

/*rgp*/
/*rgp*/

s32 CharaSysEncounterPickFormationMaybe_3a5090(s32 arg0, Obj *obj, s32 arg2, s32 arg3, s32 arg4) {
    Ent *ents;
    s32 i;
    f32 tmp[10] __attribute__((aligned(16)));
    f32 sum;
    s32 r;
    s16 id;
    Ent *best;
    s32 n;
    f32 f;
    s32 k;
    f32 mx;
    f32 scale;

    if (obj == 0) return 0;
    ents = obj->ents;
    if (ents == 0) return 0;
    n = obj->count;
    if (n <= 0) return 0;
    if (D_004837C0 == 0) return 0;
    id = obj->id;
    if (D_004837C0->cfg->flags & 1) return 0;
    if (n > 10) n = 10;
    if (n <= 0) return 0;
    if (n == 1) {
        best = ents;
    } else {
        sum = 0.0f;
        for (i = 0; i < n; i++) {
            f = ents[i].weight;
            sum += f;
            tmp[i] = f;
        }
        if (sum <= 0.0f) sum = 1.0f;
        scale = 100.0f / sum;
        for (i = 0; i < n; i++) {
            tmp[i] *= scale;
        }
        for (i = 0; i < n; i++) {
            tmp[i] = tmp[i] * RandFloat_13c010();
        }
        ents = obj->ents;
        mx = tmp[0];
        best = ents;
        for (i = 1; i < n; i++) {
            if (mx < tmp[i]) {
                mx = tmp[i];
                best = &ents[i];
            }
        }
        if (mx <= 0.0f) best = 0;
    }
    {
        s32 force = rg_force_encounter_id();
        if (force > 0) {
            Ent *hit = 0;
            char ids[96];
            int len = 0;
            ids[0] = 0;
            for (i = 0; i < n; i++) {   /* f0 = the encount_group record (s16 group id first) */
                s32 gid = obj->ents[i].f0 ? *(const s16 *)(uintptr_t)obj->ents[i].f0 : -1;
                if (gid == force) hit = &obj->ents[i];
                if (len < 80) len += snprintf(ids + len, sizeof ids - len, "%s%d", i ? "," : "", (int)gid);
            }
            fprintf(stderr, "FORCEENC key %d group %d -> key %d group %d (%s; table groups %s)\n", (int)arg2,
                    (int)id, (int)arg2, (int)force, hit ? "found" : "not found, kept", ids);
            if (hit) best = hit;
        } else if (force == 0) {
            fprintf(stderr, "FORCEENC area %d table %d group %d\n", (int)arg2, (int)id,
                    best && best->f0 ? (int)*(const s16 *)(uintptr_t)best->f0 : -1);
        }
    }
    if (best != 0) {
        if (best->f0 != 0) {
            r = CharaSysEncounterSetupMaybe_3a4440(arg0, best->f0, id, arg2, arg3, arg4);
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    return r;
}
