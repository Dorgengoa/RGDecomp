#pragma optimization_level 3
#include "types.h"

#pragma divbyzerocheck on
#pragma opt_propagation off

typedef struct {
    s64 a;
    s64 b;
    s32 t;
    s32 dur;
} Ent;

typedef struct {
    s32 base0;
    s32 pad4;
    s32 f8;
    u8 padC[0x38 - 0xC];
    s32 f38;
    s32 pad3C;
    s32 sema;
    u8 pad44[0x50 - 0x44];
    Ent *ents;
    s32 cap;
    s32 count;
    s32 head;
} Q;

typedef struct {
    s64 a;
    s64 b;
} Out;

s32 SignalSema(s32);
s32 WaitSema(s32);

s32 ViBufGetTs_1d3990(Q *q, Out *out)
{
    s32 i;
    s32 h;
    s32 idx;
    s32 t1;
    s32 n;
    u32 t2;
    u32 per;
    u32 now;
    s32 found;
    s32 off;
    s32 t;

    found = 0;
    t1 = *(volatile s32 *)0x1000B410;
    h = q->f38 & 0x7F;
    t2 = *(volatile u32 *)0x10002020;
    per = q->f8 << 11;
    WaitSema(q->sema);
    out->a = -1;
    out->b = -1;
    {
        s32 c_ = t1 - (((t2 >> 16) & 3) + ((t2 >> 8) & 0xF)) * 16;
        t1 = (per + (c_ + (h >> 3)) - q->base0) % per;
        n = q->count;
        off = q->head - n;
        now = t1 + per;
    }
    for (i = 0; i < n && found == 0; i++) {
        idx = (i + (q->cap + off)) % q->cap;
        t = (s32)(now - q->ents[idx].t) % (s32)per < q->ents[idx].dur;
        if (t) {
            out->a = q->ents[idx].a;
            out->b = q->ents[idx].b;
            q->ents[idx].a = -1;
            q->ents[idx].b = -1;
            found = 1;
            q->count -= (q->count < 1) ? q->count : found;
        }
    }
    SignalSema(q->sema);
    return 1;
}
