#include "types.h"

typedef struct Pad {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 phase;
    s32 state;
    s32 id;
    s32 cur;
    s32 prev;
    u8 pad28[6];
    u8 act[6];
} Pad;

extern s32 WaitSema(s32);
extern s32 SignalSema(s32);
extern s32 scePadGetState(s32, s32);
extern s32 scePadInfoMode(s32, s32, s32, s32);
extern s32 scePadSetMainMode(s32, s32, s32, s32);
extern s32 scePadGetReqState(s32, s32);
extern s32 scePadInfoAct(s32, s32, s32, s32);
extern s32 scePadSetActAlign(s32, s32, u8 *);
extern s32 PadReadData_184df0(Pad *, s32, s32, s32);
extern s32 D_0047E03C;

s32 PadUpdateConnection_184a50(Pad *p, s32 port, s32 slot, s32 arg3)
{
    s32 *phase;
    s32 *state;
    s32 *id;
    s32 *cur;
    s32 *prev;
    s32 ok;
    s32 m;
    s32 n;
    s32 i;

    ok = 0;
    id = &p->id;
    phase = &p->phase;
    state = &p->state;
    cur = &p->cur;
    prev = &p->prev;
    WaitSema(D_0047E03C);
    *state = scePadGetState(port, slot);
    if (*state == 0) {
        *phase = 0;
    }
    switch (*phase) {
    case 0:
        if (*state == 6 || *state == 2) {
            m = scePadInfoMode(port, slot, 1, 0);
            if (m == 0) break;
            n = scePadInfoMode(port, slot, 2, 0);
            *id = n;
            if (n > 0) m = n;
            switch (m) {
            case 4:
                *phase = 0x28;
                break;
            case 7:
                *phase = 0x46;
                break;
            default:
                *phase = 0x63;
                break;
            }
        }
        break;
    case 0x28:
        if (scePadInfoMode(port, slot, 4, -1) == 0) {
            *phase = 0x63;
            break;
        }
        *phase = *phase + 1;
    case 0x29:
        if (scePadSetMainMode(port, slot, 1, 3) == 1) {
            *phase = *phase + 1;
        }
        break;
    case 0x2A:
        if (scePadGetReqState(port, slot) == 1) {
            *phase = *phase - 1;
        }
        if (scePadGetReqState(port, slot) == 0) {
            *phase = 0;
        }
        break;
    case 0x46:
        if (scePadInfoAct(port, slot, -1, 0) == 0) {
            *phase = 0x63;
        }
        p->act[0] = 0;
        p->act[1] = 1;
        for (i = 2; i < 6; i++) {
            p->act[i] = 0xFF;
        }
        if (scePadSetActAlign(port, slot, p->act) != 0) {
            *phase = *phase + 1;
        }
        break;
    case 0x47:
        if (scePadGetReqState(port, slot) == 1) {
            *phase = *phase - 1;
        }
        if (scePadGetState(port, slot) != 5) {
            *phase = 0x63;
        }
        break;
    default:
        if (*state == 6 || *state == 2) {
            if ((*cur = PadReadData_184df0(p, port, slot, arg3)) != 0) {
                if (*prev != 0 && *cur != *prev) {
                    *prev = 0;
                    *phase = 0;
                } else {
                    ok = 1;
                }
                *prev = *cur;
            }
        }
        break;
    }
    SignalSema(D_0047E03C);
    if (*cur != 7) {
        p->f4 = 0x80;
        p->f8 = 0x80;
        p->fC = 0x80;
        p->f10 = 0x80;
    }
    if (ok == 0) {
        p->f0 = 0;
        p->f4 = 0x80;
        p->f8 = 0x80;
        p->fC = 0x80;
        p->f10 = 0x80;
    }
    return ok;
}
