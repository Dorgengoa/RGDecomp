/* rgp:protos */
#define RGP_SELF_FileReqThreadShutdown_182a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED: the spin guard's sltu/xori/bnez is a MATERIALISED boolean.
   Six condition spellings (!(x>0), (x>0)==0, !(x!=0), x<=0, !(u32)(x!=0),
   x<1) are ONE object with a plain beqz; the (s32) cast on the ! and the
   explicit != 0 is what keeps the value. */

extern s32 D_004811F4;
extern s32 D_0047E01C;
extern s32 D_0047E020;
extern s32 D_0047E024;
extern s32 D_00481204;
extern s32 D_004811F8;
extern u32 D_004811FC;

extern s32 PollSema(s32 id);
extern s32 SignalSema(s32 id);
extern s32 WaitSema(s32 id);
extern s32 TerminateThread(s32 id);
extern s32 DeleteThread(s32 id);
extern s32 DeleteSema(s32 id);
extern void DelayThread_117618(s32 n);

void FileReqThreadShutdown_182a50(void)
{
    if (D_004811F4 != 0) {
        D_00481204 = 1;
        D_004811F8 = 0;
        if (PollSema(D_0047E020) < 0) {
            SignalSema(D_0047E020);
        }
        WaitSema(D_0047E024);
        while ((s32)!(D_004811FC > 0) != 0) {
            DelayThread_117618(10);
        }
        TerminateThread(D_0047E01C);
        DeleteThread(D_0047E01C);
        DeleteSema(D_0047E020);
        DeleteSema(D_0047E024);
        D_0047E020 = -1;
        D_0047E01C = -1;
    }
}
