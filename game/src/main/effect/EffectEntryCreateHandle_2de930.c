/* rgp:protos */
#define RGP_SELF_EffectEntryCreateHandle_2de930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Res {
    s16 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
} Res;

/*rgp*/
/*rgp*/

void EffectEntryCreateHandle_2de930(Res *out, u8 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    Res r __attribute__((aligned(16)));
    s16 idx;
    u8 *e;
    s16 *q;
    s32 k;
    s32 v;
    s32 c;
    s16 kind;

    kind = 0;
    v = r.e;
    idx = -1;
    if (((s32)EffectFindByName_2dfe10(arg1, arg2, &idx)) == 0) {
        out->a = 0;
        out->b = r.b;
        out->c = -1;
        out->d = 0;
        out->e = v;
        return;
    }
    if (idx == -1) {
        out->a = 0;
        out->b = r.b;
        out->c = -1;
        out->d = 0;
        out->e = v;
        return;
    }
    e = arg1 + idx * 0xE0;
    q = (s16 *)(e + 0xC);
    if (*(s16 *)(e + 0x16) != 1) {
        out->a = 0;
        out->b = r.b;
        out->c = -1;
        out->d = 0;
        out->e = v;
        return;
    }
    if (q[6] != 1) {
        out->a = 0;
        out->b = r.b;
        out->c = -1;
        out->d = 0;
        out->e = v;
        return;
    }
    if (q[1] < 0) {
        out->a = 0;
        out->b = r.b;
        out->c = -1;
        out->d = 0;
        out->e = v;
        return;
    }
    k = EffectInstanceCreate_2daf00(e, arg3, arg4);
    if (k >= 0) {
        v = k;
    }
    if (q[0] == 0) {
        kind = 2;
    } else if (q[0] == 1) {
        kind = 3;
    }
    c = q[1];
    out->a = kind;
    out->b = arg4;
    out->c = c;
    out->d = 0;
    out->e = v;
}
