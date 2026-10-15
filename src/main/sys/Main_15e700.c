#include "types.h"

extern s32 GetThreadId(void);
extern s32 ChangeThreadPriority(s32, s32);
extern s32 MainStaticInit_100580(void);
extern s32 SysInitHardware_15e670(void);
extern s32 SysCalcFreeHeapMaybe_15e1d0(void);
extern void FileSysInit_1818e0(void);
extern s32 FileReqThreadInit_182af0(s32);
extern s32 MainLoop_1c2c10(void);
extern s32 FileReqThreadShutdown_182a50(void);
extern s32 FileSysShutdown_181890(void);
extern void DestroyGlobalChainThunk_100d60(void);

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
    r2 = MainStaticInit_100580();
    r3 = SysInitHardware_15e670();
    r4 = SysCalcFreeHeapMaybe_15e1d0();
    FileSysInit_1818e0();
    t1 = D_0047DF30;
    r6 = FileReqThreadInit_182af0((t1 + -1));
    r7 = MainLoop_1c2c10();
    r8 = FileReqThreadShutdown_182a50();
    r9 = FileSysShutdown_181890();
    DestroyGlobalChainThunk_100d60();
    return 0;
}
