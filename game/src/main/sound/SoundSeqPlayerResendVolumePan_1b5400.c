/* rgp:protos */
#define RGP_SELF_SoundSeqPlayerResendVolumePan_1b5400 1
#define RGP_SELF_valid 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s8 v8, v9, vA, vB;
} Sub;

typedef struct {
    s8 v0, v1, v2, v3, v4, v5, v6, on;
    Sub s;
} Ent;

typedef struct {
    s32 a;
    s32 b;
    u8 pad8[0x10];
    s32 vol;
    u8 pad1C[0x10];
    s32 count;
    Ent e[1];
} Obj;

/*rgp*/
/*rgp*/

static inline s32 valid(Obj *o, s32 i)
{
    s32 r;
    if (i < 0 || i >= o->count) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

void SoundSeqPlayerResendVolumePan_1b5400(Obj *o)
{
    s32 i;
    Ent *e;

    for (i = 0; i < o->count; i++) {
        if (valid(o, i)) {
            e = &o->e[i];
            if (e->on) {
                Sub *s = &e->s;
                SoundSendVolume_1b8020(o->a, o->b, s->v9, s->vA, e->v1 * (o->vol * e->v0) / 127 / 127, e->v6);
            }
        }
        if (valid(o, i)) {
            e = &o->e[i];
            if (e->on) {
                SoundSendPan_1b7ff0(o->a, o->b, e->s.v9, e->s.vA, e->v3, e->v6);
            }
        }
    }
}
