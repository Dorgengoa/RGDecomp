#include "types.h"
#pragma opt_propagation off
typedef char *va_list;

s32 SignalSema(s32);
s32 WaitSema(s32);
s32 sceSifCallRpc(void *, s32, s32, void *, s32, void *, s32, s32, s32);
extern s32 D_0047E218;
extern u8 D_004A2580[0x40];
extern u8 D_004A25C0[0x400];

s32 SoundRpcCall_1bc5e0(s32 arg0, s32 count, ...) {
    va_list ap;
    s32 *buf;
    s32 i;
    s32 n;
    s32 r;
    s32 lim;

    if (count >= 0x10) {
        return 0;
    }
    WaitSema(D_0047E218);
    n = 2;
    ap = (va_list)__builtin_next_arg(count) - (n >= 8 ? 0 : (8 - n) * 8);
    
    lim = *(volatile s32 *)&count;
    for (i = 0; i < lim; i++) {
        ap += 8;
        ((s32 *)D_004A2580)[i] = *(s32 *)(ap - 8);
    }
    sceSifCallRpc(D_004A25C0, arg0, 0, D_004A2580, 0x40, D_004A2580, 0x40, 0, 0);
    r = *(s32 *)D_004A2580;
    SignalSema(D_0047E218);
    return r;
}
