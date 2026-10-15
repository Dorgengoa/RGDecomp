#include "types.h"

typedef struct {
    s32 type;
    f32 x4;
    f32 speed;
    f32 cur;
    f32 lim;
    f32 timer;
    f32 x18;
    s32 x1C;
} Sub1b5f20;

typedef struct {
    s32 n;
    Sub1b5f20 s[1];
} Arr1b5f20;

void SoundSetCategoryVolume_1bb230(s32, s32, f32);

void SoundCategoryFadeUpdate_1b5f20(Arr1b5f20 *arr, f32 f)
{
    s32 i;
    Sub1b5f20 *s;
    s32 type;
    s32 done;
    f32 spd;
    f32 t;
    f32 v;
    s32 on;

    for (i = 0; i < arr->n; i++) {
        s = &arr->s[i];
        type = s->type;
        done = 0;
        on = type != 0;
        if ((u8)on) {
            t = s->timer;
            spd = s->speed;
            if (!(t <= 0.0f)) {
                t = t - f / 60.0f;
                s->timer = t;
                if (t < 0.0f) {
                    s->timer = 0.0f;
                } else {
                    spd = 0.0f;
                }
            }
            if (type == 1) {
                s->cur += spd;
                if (!(s->cur < s->lim)) {
                    s->cur = s->lim;
                    done = 1;
                }
            } else if (type == 2) {
                s->cur += spd;
                if (s->cur <= s->lim) {
                    s->cur = s->lim;
                    done = 1;
                }
            } else {
                s->type = 0;
                s->cur = 1.0f;
                s->x18 = -1.0f;
            }
        }
        v = s->cur * s->x4;
        if (s->x18 != v) {
            SoundSetCategoryVolume_1bb230(i, type, v);
            s->x18 = v;
        }
        if (done != 0) {
            if (s->x1C != 0) {
                s->type = 0;
            } else {
                s->type = 0;
                s->cur = 1.0f;
                s->x18 = -1.0f;
            }
        }
    }
}
