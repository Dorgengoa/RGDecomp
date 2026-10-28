/* rgp:protos */
#define RGP_SELF_Main_15e700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 GetThreadId(void);
extern s32 ChangeThreadPriority(s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047DF30;

s32 Main_15e700(void)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 t1;
    s32 r6;
    s32 r7;
    s32 r8;
    s32 r9;

    r0 = GetThreadId();
    t0 = D_0047DF30;
    r1 = ChangeThreadPriority(r0, t0);
    r2 = (MainStaticInit_100580(), (s32)0);
    r3 = (SysInitHardware_15e670(), (s32)0);
    r4 = SysCalcFreeHeapMaybe_15e1d0();
    FileSysInit_1818e0();
    t1 = D_0047DF30;
    r6 = FileReqThreadInit_182af0((t1 + -1));
    r7 = (MainLoop_1c2c10(), (s32)0);
    r8 = (FileReqThreadShutdown_182a50(), (s32)0);
    r9 = FileSysShutdown_181890();
    DestroyGlobalChainThunk_100d60(0);
    return 0;
}
