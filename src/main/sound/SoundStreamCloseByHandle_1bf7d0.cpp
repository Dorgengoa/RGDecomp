#include "types.h"
#undef NULL
#define NULL 0

extern "C" {
s32 PollSema(s32);
void SignalSema(s32);
void WaitSema(s32);
void SoundStreamShutdown_1c0b70(void *);
}

struct Ent1bf7d0 {
    u8 pad0[0x3C];
    s32 m3C;
    volatile s32 m40;
    u8 m44;
    u8 m45;
    u8 pad46[2];
    u8 m48;
    u8 pad49[3];
    s32 m4C;
    s32 m50;
    u8 m54[0x10];
    u8 pad64[0x1E];
    u16 m82;
};

struct Pool1bf7d0 {
    u32 n;
    Ent1bf7d0 s[1];
};

struct H1bf7d0 {
    u16 idx;
    u16 tag;
};

static inline bool full1bf7d0(Ent1bf7d0 *e)
{
    return e->m48 != 0 && e->m4C == e->m50;
}

extern "C" void SoundStreamCloseByHandle_1bf7d0(Pool1bf7d0 *pool, H1bf7d0 *__restrict arg1)
{
    H1bf7d0 h;
    Ent1bf7d0 *e;
    bool flag;
    s32 more;
    u32 idx;
    u32 tag;

    *(u32 *)&h = *(u32 *)arg1;
    idx = h.idx;
    tag = h.tag;
    if (tag == 0 || !(idx < pool->n)) {
        e = NULL;
    } else if (pool->s[idx].m82 != tag) {
        e = NULL;
    } else {
        e = &pool->s[idx];
    }
    if (e == NULL) {
        return;
    }
    e->m82 = 0;
    if (e->m40 > 0) {
        WaitSema(e->m40);
    }
    if (e->m48 == 0 && e->m4C == e->m50) {
        flag = false;
    } else {
        flag = true;
        e->m54[e->m50] = 2;
        e->m50 = (e->m50 + 1) & 0xF;
        e->m48 = 0;
    }
    if (e->m40 > 0) {
        SignalSema(e->m40);
    }
    if (flag) {
        if (e->m3C > 0 && PollSema(e->m3C) < 0) {
            SignalSema(e->m3C);
        }
    }
    for (;;) {
        more = 0;
        if (e->m40 > 0) {
            WaitSema(e->m40);
        }
        if (e->m45 != 0 || !full1bf7d0(e)) {
            more = 1;
        }
        if (e->m40 > 0) {
            SignalSema(e->m40);
        }
        if (!more) {
            break;
        }
        if (e->m3C > 0 && PollSema(e->m3C) < 0) {
            SignalSema(e->m3C);
        }
    }
    SoundStreamShutdown_1c0b70(e);
}
