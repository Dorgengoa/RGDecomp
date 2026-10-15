#include "types.h"

typedef __int128 s128;

typedef struct Chr {
    u8 pad0[0x180];
    s128 pos;
} Chr;

typedef struct Ai {
    u8 pad0[0x50];
    s16 state;
    s16 sub;
    s16 timer2;
    s16 timer;
    s16 anim;
    s16 target;
    s16 id;
    s16 over;
} Ai;

typedef struct World {
    u8 pad0[0x4340];
    s32 id;
} World;

extern f32 VecDistance_13d3d0(s128 *, s128 *);
extern Chr *ObjRecGetLiveObject_1c4a90(World *, s32);

void XformRecProximityUpdateMaybe_1c6690(Ai *arg0, World *arg1) {
    s128 sp60;
    s128 sp50;
    f32 d;
    s32 id;
    Chr *a;
    Chr *b;
    s16 t;

    id = arg0->id;
    if (id == 0) {
        id = arg1->id;
    }
    if (arg0->over >= 0) {
        id = arg0->over;
    }
    if (arg0->state == 0 && arg0->anim != 0) {
        arg0->anim = 3;
    }
    if (arg0->state == 2) {
        a = ObjRecGetLiveObject_1c4a90(arg1, id);
        b = ObjRecGetLiveObject_1c4a90(arg1, arg0->target);
        if (a == NULL || b == NULL) {
            return;
        }
        sp50 = a->pos;
        sp60 = b->pos;
        d = VecDistance_13d3d0(&sp50, &sp60);
        if (arg0->sub == 0) {
            if (d < 40.0f) {
                arg0->timer = 120;
                arg0->anim = 1;
                arg0->sub = 1;
            } else {
                if (arg0->anim == 2) goto set3;
                if (arg0->anim != 1) goto skip3;
set3:
                arg0->anim = 3;
skip3:;
            }
        }
        if (arg0->sub == 1) {
            if (!(d <= 100.0f)) {
                arg0->anim = 3;
                arg0->sub = 0;
            } else {
                t = --arg0->timer;
                if (t <= 0) {
                    arg0->timer2 = 150;
                    arg0->anim = 3;
                    arg0->sub = 2;
                }
            }
        }
        if (arg0->sub == 2) {
            arg0->timer2--;
            if (!(d <= 100.0f)) {
                arg0->timer2 = 0;
            }
            if (arg0->timer2 <= 0) {
                arg0->anim = 3;
                arg0->sub = 0;
            }
        }
    }
    if (arg0->state == 1) {
        a = ObjRecGetLiveObject_1c4a90(arg1, id);
        b = ObjRecGetLiveObject_1c4a90(arg1, arg0->target);
        if (a == NULL || b == NULL) {
            return;
        }
        sp50 = a->pos;
        sp60 = b->pos;
        VecDistance_13d3d0(&sp50, &sp60);
        if (arg0->sub == 0) {
            arg0->anim = 1;
            arg0->sub = 1;
            arg0->timer2 = 0;
        }
    }
    if (arg0->state == 4 && ObjRecGetLiveObject_1c4a90(arg1, arg0->target) != NULL && arg0->sub == 0) {
        arg0->anim = 1;
        arg0->sub = 1;
        arg0->timer2 = 0;
    }
}
