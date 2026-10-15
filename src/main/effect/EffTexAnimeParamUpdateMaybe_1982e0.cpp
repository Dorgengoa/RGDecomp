#include "types.h"
#pragma divbyzerocheck on

typedef struct Key {
    u8 type;
    u8 pad01[3];
    s32 mode;
    f32 x08;
    f32 x0C;
    u16 x10;
    u16 x12;
    u16 *cells;
} Key;

typedef struct Track {
    f32 time;
    f32 dur;
    s32 frame;
    s32 sub;
} Track;

typedef struct Anim {
    u8 pad00[4];
    s32 idx;
    f32 x08;
    f32 x0C;
    s32 x10;
    s32 x14;
    u8 pad18[4];
    u8 loop;
    u8 pad1D[3];
    s32 count;
    Key **keys;
} Anim;

typedef struct Obj {
    u8 pad00[4];
    u8 x04[0x4C];
    f32 x50;
    f32 x54;
    u8 pad58[0x5C];
    Track *tracks;
} Obj;

extern "C" {
f32 RandGaussian_197d70(u8 *);
f32 RandFloat_1980f0(u8 *);
extern f32 D_0047D34C;
extern f32 D_0047D420;
void EffTexAnimeParamUpdateMaybe_1982e0(Anim *a, Obj *o, f32 dt);
}

static inline Key *getKey(Anim *a, s32 i) {
    if (i < 0 || i >= a->count) {
        return 0;
    }
    return a->keys[i];
}

void EffTexAnimeParamUpdateMaybe_1982e0(Anim *a, Obj *o, f32 dt) {
    Track *t;
    Key *key;
    bool done;
    bool cont;
    s32 n;
    s32 pos;
    s32 cell;
    f32 val;
    f32 mn;

    t = &o->tracks[a->idx];
    if (t->frame < a->count) {
        do {
            key = getKey(a, t->frame);
            if (key == 0) {
                return;
            }
            done = false;
            cont = false;
            switch (key->type) {
            case 3:
                cont = true;
                if (key->mode <= 0) {
                    val = key->x08;
                } else if (key->mode == 1) {
                    val = key->x08 + key->x0C * (2.0f * (RandFloat_1980f0(o->x04) - 0.5f));
                } else if (key->mode == 2) {
                    val = key->x08 + D_0047D420 * (key->x0C * RandGaussian_197d70(o->x04));
                } else {
                    val = key->x08;
                }
                mn = D_0047D34C;
                t->dur = val;
                if (val < mn) {
                    t->dur = mn;
                }
                break;
            case 1:
                n = key->x12 - key->x10;
                pos = key->x10 + t->sub;
                if (n < 0) {
                    pos = key->x10 - t->sub;
                    n = -n;
                }
                cell = pos % (a->x10 * a->x14);
                o->x50 = a->x08 * (f32)(cell % a->x10);
                o->x54 = -a->x0C * (f32)(cell / a->x10);
                t->time = t->time + dt;
                while (t->time >= t->dur) {
                    t->sub++;
                    t->time = t->time - t->dur;
                }
                if (t->sub <= n) {
                    done = true;
                }
                break;
            case 2:
                cell = key->cells[t->sub] % (a->x10 * a->x14);
                o->x50 = a->x08 * (f32)(cell % a->x10);
                o->x54 = -a->x0C * (f32)(cell / a->x10);
                t->time = t->time + dt;
                while (t->time >= t->dur) {
                    t->sub++;
                    t->time = t->time - t->dur;
                }
                if (t->sub <= key->x10) {
                    done = true;
                }
                break;
            }
            if (done) {
                return;
            }
            t->frame++;
            t->sub = 0;
            if (a->loop != 0 && t->frame >= a->count) {
                t->frame = 0;
            }
        } while (cont);
    }
}
