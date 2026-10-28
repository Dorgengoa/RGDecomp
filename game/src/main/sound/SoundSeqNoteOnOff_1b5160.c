/* rgp:protos */
#define RGP_SELF_SoundSeqNoteOnOff_1b5160 1
#define RGP_SELF_find 1
#define RGP_SELF_findfree 1
#define RGP_SELF_valid 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimize_for_size on
#pragma divbyzerocheck on

typedef struct Slot {
    s8 on;
    s8 a;
    s8 note;
    s8 b;
} Slot;

typedef struct Chan {
    s8 x30;
    s8 x31;
    s8 x32;
    s8 x33;
    s8 x34;
    s8 x35;
    s8 x36;
    s8 x37;
    Slot slot[1];
} Chan;

typedef struct Synth {
    s32 x0;
    s32 x4;
    u8 pad8[0x10];
    s32 x18;
    u8 pad1C[0x10];
    s32 count;
    Chan ch[1];
} Synth;

/*rgp*/
/*rgp*/

static inline s32 valid(Synth *t, s32 ch) {
    if (ch < 0 || ch >= t->count) {
        return 0;
    }
    return 1;
}

static inline Slot *find(Chan *c, s32 note) {
    Slot *s;
    s32 i;
    s8 k = c->x32;
    s = c->slot;
    for (i = 0; i < 1; i++, s++) {
        if (s->on != 0 && s->a == k && s->note == note) {
            return s;
        }
    }
    return 0;
}
static inline Slot *findfree(Chan *c) {
    Slot *s;
    s32 i;
    s = c->slot;
    for (i = 0; i < 1; i++, s++) {
        if (s->on == 0) {
            return s;
        }
    }
    return 0;
}

void SoundSeqNoteOnOff_1b5160(Synth *t, s32 ch, s32 note, s32 on) {
    Slot *s;
    s32 ok;

    if (valid(t, ch) == 0) {
        return;
    }
    if (on == 0) {
        if (valid(t, ch) == 0) {
            return;
        }
        s = find(&t->ch[ch], note);
        if (s == 0) {
            ok = 0;
        } else {
            s->on = 0;
            ok = 1;
        }
        if (ok == 0) {
            goto ret;
        }
        SoundSendKeyOff_1b8090(t->x0, t->x4, t->ch[ch].x32, note, t->ch[(u32)ch].x36);
    ret:
        return;
    } else {
        s = find(&t->ch[ch], note);
        if (s != 0) {
            ok = 1;
        } else {
            s = findfree(&t->ch[ch]);
            if (s == 0) {
                ok = 0;
            } else {
                ok = 1;
                s->on = ok;
                s->note = note;
                s->a = t->ch[ch].x32;
                s->b = t->ch[(u32)ch].x36;
            }
        }
        if (ok == 0) {
            return;
        }
        {
            Chan *c = &t->ch[ch];
            s32 vel = t->x18 * c->x30 * c->x31;
            vel = vel / 127 / 127;
            SoundSendKeyOn_1b80c0(t->x0, t->x4, c->x32, note, (long long)(on), vel, (long long)(c->x33), (long long)(c->x34 + (c->x35 << 7)), c->x36);
        }
    }
}
