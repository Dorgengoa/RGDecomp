/* rgp:protos */
#define RGP_SELF_MotionListGetPhase_171e90 1
#define RGP_SELF_at171e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct {
    s32 pad0;
    s32 count;
    u8 *data;
} Arr171e90;

static inline u8 *at171e90(Arr171e90 *a, s32 i)
{
    s32 ok;

    if (a->data == NULL) {
        ok = 0;
    } else if (i >= 0) {
        if (i >= a->count) {
            ok = 0;
        } else {
            ok = 1;
        }
    } else {
        ok = 0;
    }
    if (ok != 0) {
        return a->data + i * 0x30;
    }
    return NULL;
}

f32 MotionListGetPhase_171e90(void *arg0)
{
    u8 *o;
    Arr171e90 *a;
    u8 *e;
    s32 idx;
    f32 f;

    o = *(u8 **)((u8 *)arg0 + 4);
    if (o == NULL) {
        return 0.0f;
    }
    f = *(f32 *)(o + 0x28);
    idx = *(s32 *)(o + 0x24);
    if (*(s32 *)(o + 0x1C) == 0) {
        return 0.0f;
    }
    a = (Arr171e90 *)(*(s32 *)(o + 0x1C) + 0x10);
    if (a == NULL) {
        return 0.0f;
    }
    e = at171e90(a, idx);
    if (e != NULL) {
        return f / (*(f32 *)(e + 0x28) - *(f32 *)(e + 0x24));
    }
    return 0.0f;
}
