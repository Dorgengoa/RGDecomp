/* rgp:protos */
#define RGP_SELF_CharaSysEncounterPickFormationMaybe_3a5090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { s32 f0; s16 weight; s16 pad6; s32 pad8; } Ent;
typedef struct Obj { s16 id; u8 pad[0x2A]; s8 count; u8 pad2[3]; Ent *ents; } Obj;
typedef struct Cfg { u8 pad[0x24C]; u8 flags; } Cfg;
typedef struct Sys { u8 pad[0x20]; Cfg *cfg; } Sys;
extern Sys *D_004837C0;
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
