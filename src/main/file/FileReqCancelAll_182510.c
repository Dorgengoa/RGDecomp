#include "types.h"

extern s32 PollSema(s32);
extern s32 SignalSema(s32);
extern s32 WaitSema(s32);
extern s32 FileSlotCloseThunk_180540(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E020;
extern s32 D_0047E024;
extern s32 D_004811E8;
extern s32 D_004811EC;
extern s32 D_004811F0;
extern s32 D_00481204;
extern u8 D_00495FD0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    u8 pad00C[0x114];
    s32 m120;
    s32 m124;
};

void FileReqCancelAll_182510(void)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 rv3;
    s32 t1;
    s32 r1;
    s32 t2;
    s32 t3;
    s32 r4;
    struct Obj0 *l6;
    s32 l5;
    s32 t4;
    s32 rv9;
    s32 t5;
    s32 rv8;
    s32 t6;
    s32 r7;
    s32 l10;

    t0 = D_0047E020;
    D_00481204 = 1;
    r0 = PollSema(t0);
    rv2 = r0;
    if (r0 < 0) {
        t1 = D_0047E020;
        r1 = SignalSema(t1);
        t2 = D_0047E024;
        rv2 = r1;
        rv3 = t2;
    } else {
        t3 = D_0047E024;
        rv2 = r0;
        rv3 = t3;
    }
    r4 = WaitSema(rv3);
    l6 = (struct Obj0 *)D_00495FD0;
    l5 = 0;
    do {
        t4 = l6->m120;
        rv9 = r4;
        if (t4 != 0) {
            t5 = l6->m08;
            rv8 = r4;
            if (t5 == 0) {
                t6 = l6->m124;
                r7 = FileSlotCloseThunk_180540(t6);
                l6->m124 = -1;
                rv8 = r7;
            }
            rv9 = rv8;
        }
        l5 = (l5 + 1);
        l6 = (struct Obj0 *)((u8 *)l6 + 0x128);
    } while (l5 < 0x20);
    l10 = 0;
    do {
        *(s32 *)((u8 *)D_00495FD0 + l10 * 296 + 0x120) = 0;
        l10 = (l10 + 1);
    } while (l10 < 0x20);
    D_004811F0 = 0;
    D_004811EC = -1;
    D_004811E8 = 0;
}
