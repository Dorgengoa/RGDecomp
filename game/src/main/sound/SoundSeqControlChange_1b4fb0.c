/* rgp:protos */
#define RGP_SELF_SoundSeqControlChange_1b4fb0 1
#define RGP_SELF_valid 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: dense mixed-width struct-field switch (10/7/11 cases) over a
 * 0xC-stride array with a nested 0x30/8-offset sub-struct and constant
 * "127/127" fixed-point divides needing divbyzerocheck; 0 round trips
 * spent. Field widths (unk1/unk3/unk6/unk7/unk9/unkA all inferred from
 * m2c's arg3(s8) plumbing) need cross-checking against
 * asm/matchings/main/SoundSeqControlChange_1b4fb0.s before writing C. Not attempted. */
/* s49m: MATCH */
#pragma opt_propagation off
#pragma divbyzerocheck on
#include "types.h"

typedef struct Sub {
    s8 x0;
    s8 x1;
    s8 x2;
    s8 x3;
} Sub;

typedef struct Ent {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
    s8 b4;
    s8 b5;
    s8 b6;
    s8 b7;
    Sub sub;
} Ent;

typedef struct Obj {
    s32 m0;
    s32 m4;
    u8 pad8[0x10];
    s32 m18;
    u8 pad1C[0x10];
    s32 m2C;
    Ent ents[1];
} Obj;

/*rgp*/
/*rgp*/

static inline s32 valid(Obj *o, s32 idx)
{
    if (idx < 0 || idx >= o->m2C) {
        return 0;
    }
    return 1;
}

void SoundSeqControlChange_1b4fb0(Obj *o, s32 idx, s32 kind, s8 val)
{
    Ent *e;
    s32 ok;
    Sub *s;
    s32 vol;

    if (!valid(o, idx)) {
        return;
    }
    e = &o->ents[idx];
    ok = 1;
    switch (kind) {
    case 7:
        e->b0 = val;
        break;
    case 10:
        e->b3 = val;
        break;
    case 11:
        e->b1 = val;
        break;
    }
    if (ok) {
        if (kind == 10) {
            if (valid(o, idx) && e->b7 != 0) {
                SoundSendPan_1b7ff0(o->m0, o->m4, e->sub.x1, e->sub.x2, e->b3, e->b6);
            }
        }
        if (kind == 11 || kind == 7) {
            if (valid(o, idx) && e->b7 != 0) {
                s = &e->sub;
                vol = e->b1 * (o->m18 * e->b0) / 127 / 127;
                SoundSendVolume_1b8020(o->m0, o->m4, s->x1, s->x2, vol, e->b6);
            }
        }
    }
}
