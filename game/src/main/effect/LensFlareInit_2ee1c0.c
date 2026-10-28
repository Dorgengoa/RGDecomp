/* rgp:protos */
#define RGP_SELF_LensFlareInit_2ee1c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN LensFlareInit_2ee1c0 -- zeroes the 12-entry 0x18-stride table that
   LensFlareSetupElements_2ee040 then fills, sets the six scalars that follow it, and
   hands the object to DepthProbeSlotsReset_13fcb0 via GetDrawCtx_15de80.
   The loop is entered unconditionally (0 < 12 is a compile-time fact),
   so mwcc emits the bottom test only. */

typedef struct Ent {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    f32 e;
    f32 f;
} Ent;

typedef struct Obj {
    Ent e[12];          /* 0x000 */
    f32 m120;           /* 0x120 */
    s32 pad124[3];
    f32 m130;
    f32 m134;
    f32 m138;
    f32 m13C;
    u8  m140;
    u8  pad141[3];
    f32 m144;
    s32 m148;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void LensFlareInit_2ee1c0(Obj *o)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        /* store ORDER is retail's: b before a, f before e. */
        o->e[i].b = 0;
        o->e[i].a = 0;
        o->e[i].c = 0;
        o->e[i].d = 0;
        o->e[i].f = 0.0f;
        o->e[i].e = 0.0f;
    }
    o->m120 = 1.0f;
    o->m130 = 128.0f;
    o->m134 = 128.0f;
    o->m138 = 128.0f;
    o->m13C = 128.0f;
    o->m140 = 1;
    o->m144 = 0.0f;
    o->m148 = 1;
    LensFlareSetupElements_2ee040(o->e);
    DepthProbeSlotsReset_13fcb0(GetDrawCtx_15de80());
}
