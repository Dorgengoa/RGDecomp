/* rgp:protos */
#define RGP_SELF_GameReqListPushFront_20a240 1
#define RGP_SELF_room 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct V3 {
    f32 x;
    f32 y;
    f32 z;
} V3;

typedef struct E14 {
    s32 a;
    s32 b;
    V3 v;
} E14;

/*rgp*/

static inline s32 room(u8 *arg0)
{
    return *(s16 *)(arg0 + 4) < *(s16 *)(arg0 + 6);
}

s32 GameReqListPushFront_20a240(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    E14 *e;
    E14 *src;
    E14 *dst;

    if (arg1 < 0) {
        return 0;
    }
    if (*(E14 **)arg0 == NULL || *(s16 *)(arg0 + 4) >= *(s16 *)(arg0 + 6)) {
        return 0;
    }
    {
        for (i = *(s16 *)(arg0 + 4) - 1; i >= 0; i--) {
            e = *(E14 **)arg0;
            src = &e[i];
            dst = &e[i + 1];
            dst->a = src->a;
            dst->b = src->b;
            dst->v = src->v;
        }
        e = *(E14 **)arg0;
        GameReqInit_20a570(e);
        e->a = arg1;
        e->b = arg2;
        *(s16 *)(arg0 + 4) += 1;
        return 1;
    }
    return 0;
}

