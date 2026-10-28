/* rgp:protos */
#define RGP_SELF_ViBufModifyPts_1d3ca0 1
#define RGP_SELF_imax 1
#define RGP_SELF_imax2 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_propagation off

typedef struct { s64 a; s64 b; s32 pos; s32 len; } Ent;
typedef struct { u8 pad[8]; s32 unk8; u8 pad2[0x50 - 0xc]; Ent *ents; s32 n; s32 count; s32 head; } Q;
typedef struct { u8 pad[0x10]; s32 pos; s32 len; } Req;

static inline s32 imax(s32 a, s32 b) { return a > b ? a : b; }
static inline s32 imax2(s32 a, s32 b) { return a < b ? b : a; }

s32 ViBufModifyPts_1d3ca0(Q *q, Req *r) {
    s32 c = q->count;
    s32 idx = (q->n + (q->head - c)) % q->n;
    s32 mod = q->unk8 << 11;
    s32 flag = 1;
    if (c > 0) {
        while (flag) {
            Ent *e = &q->ents[idx];
            s32 len = e->len;
            s32 rlen;
            s32 pos;
            s32 rpos;
            s32 ok;
            if (len == 0) break;
            rlen = r->len;
            if (rlen == 0) break;
            pos = e->pos;
            rpos = r->pos;
            ok = (pos + mod - rpos) % mod < rlen;
            if (ok) {
                s32 d = rpos + rlen - pos;
                s32 t;
                len = len < d ? len : d;
                e->pos = (pos + len) % mod;
                t = e->len - len;
                e->len = t;
                if (t == 0) {
                    if (e->a >= 0) {
                        e->a = -1;
                        e->b = -1;
                        e->pos = 0;
                        e->len = 0;
                    }
                    t = q->count - 1;
                    q->count = (t < 0) ? 0 : t;
                }
            } else {
                flag = 0;
            }
            idx = (idx + 1) % q->n;
        }
    }
    return 0;
}
