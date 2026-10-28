/* rgp:protos */
#define RGP_SELF_Get 1
#define RGP_SELF_MotionPlayerGetState_1729d0 1
#define RGP_SELF_Valid 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Key { u8 pad[0x24]; f32 start; f32 end; u8 pad2[4]; } Key;
typedef struct KeyArr { s32 f0; s32 count; Key *data; } KeyArr;
typedef struct Anim { u8 pad[0xC]; s32 id; KeyArr keys; } Anim;
typedef struct Player { u8 pad[0xC]; Anim *anim; s32 pad10; s32 idx; f32 f18; f32 f1C; s32 f20; s32 f24; s32 f28; u8 pad2[0x44 - 0x2C]; f32 f44; } Player;
typedef struct Out { s32 id; Key *key; f32 f8; f32 fC; f32 f10; f32 f14; f32 f18; f32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; } Out;

static inline s32 Valid(KeyArr *a, s32 i) {
    if (a->data == 0) return 0;
    if (i < 0 || i >= a->count) return 0;
    return 1;
}
static inline Key *Get(KeyArr *a, s32 i) {
    if (!Valid(a, i)) return 0;
    return &a->data[i];
}

s32 MotionPlayerGetState_1729d0(Player *arg0, Out *arg1) {
    KeyArr *arr;
    Key *k;
    f32 f;
    f32 r;
    f32 s;

    if (arg0->anim != 0) {
        arg1->id = arg0->anim->id;
        arr = &arg0->anim->keys;
        arg1->key = Get(arr, arg0->idx);
        f = arg0->f18;
        k = Get(arr, arg0->idx);
        if (k) f = f + k->start;
        else f = f;
        arg1->f8 = f;
        f = arg0->f1C;
        k = Get(arr, arg0->idx);
        if (k) f = f + k->start;
        else f = f;
        arg1->fC = f;
        arg1->f10 = arg0->f44;
        if (arg0->f28 != 0) {
            arg1->fC = arg1->f8;
            arg1->f10 = 0.0f;
            arg1->f28 = 1;
        } else {
            arg1->f2C = 0;
            arg1->f28 = 0;
        }
        f = arg1->f8;
        k = Get(arr, arg0->idx);
        if (k == 0) f = 0.0f;
        else f = (f - k->start) / (k->end - k->start);
        arg1->f14 = f;
        f = arg1->fC;
        k = Get(arr, arg0->idx);
        if (k == 0) f = 0.0f;
        else f = (f - k->start) / (k->end - k->start);
        arg1->f18 = f;
        f = arg1->f10;
        k = Get(arr, arg0->idx);
        if (k != 0) r = f / (k->end - k->start);
        else r = 0.0f;
        arg1->f1C = r;
    } else {
        arg1->id = -1;
        arg1->key = 0;
        arg1->f8 = 0.0f;
        arg1->fC = 0.0f;
        arg1->f10 = 0.0f;
        arg1->f14 = 0.0f;
        arg1->f18 = 0.0f;
        arg1->f1C = 0.0f;
        arg1->f2C = 0;
        arg1->f28 = 0;
    }
    arg1->f20 = arg0->f24;
    arg1->f24 = arg0->f20;
    return arg0->anim != 0;
}
