/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_SoundStreamQueueStop_1bff30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

extern s32 PollSema(s32 arg0);
extern s32 SignalSema(s32 arg0);
extern s32 WaitSema(s32 arg0);

typedef struct {
    u8 pad0[0x3C];
    s32 unk3C;
    s32 unk40;
    u8 pad44;
    u8 unk45;
    u8 pad46[2];
    u8 unk48;
    u8 pad49[3];
    s32 unk4C;
    s32 unk50;
    u8 buf[16];
} T1bff30_arg0;

void SoundStreamQueueStop_1bff30(T1bff30_arg0 *p)
{
    s32 f;
    u8 g;
    s32 t;
    s32 v;

    goto B;
A: rg_spin_hint(0x001BFF4C);
    f = 0;
    if (p->unk40 > 0) {
        WaitSema(p->unk40);
    }
    if (p->unk45 != 0 || !(v = (p->unk48 != 0 && p->unk4C == p->unk50))) {
        f = 1;
    }
    if (p->unk40 > 0) {
        SignalSema(p->unk40);
    }
    if (f == 0) {
        goto B;
    }
    t = p->unk3C;
    if (t > 0) {
        if (PollSema(t) < 0) {
            SignalSema(p->unk3C);
        }
    }
    goto A;
B:
    if (p->unk40 > 0) {
        WaitSema(p->unk40);
    }
    if (!(p->unk48 != 0 || p->unk4C != p->unk50)) {
        g = 0;
    } else {
        p->buf[p->unk50] = 5;
        g = 1;
        p->unk50 = (p->unk50 + 1) & 0xF;
        p->unk48 = 0;
    }
    if (p->unk40 > 0) {
        SignalSema(p->unk40);
    }
    if (g) {
        t = p->unk3C;
        if (t > 0) {
            if (PollSema(t) < 0) {
                SignalSema(p->unk3C);
            }
        }
    }
    if (!g) {
        goto A;
    }
}
