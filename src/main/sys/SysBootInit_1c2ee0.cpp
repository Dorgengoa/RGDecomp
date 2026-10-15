#include "types.h"

class VE {
    u8 pad_[0x4394];
public:
    virtual void vs0();
    virtual void f0C();
};

/* Boot sequence.  `sltiu $1,$2,0x10` after strlen means strlen is declared to
   return u32 (an s32 return gives slti).
   Indirect call: table pointer at 0x4394 of the object returned by
   GetStaticScene_1c6c70, slot 0xC (C_table shape - the pointer is not at offset 0). */


extern "C" void PadOpenPorts_1c6bf0(void);
extern "C" void SysParamTableLoadDefaults_1c6b20(void);
extern "C" void PadUpdate_1843a0(void *);
extern "C" void IopHeapInitOnce_1c2310(void);
extern "C" void SoundIopInit_1b7160(void);
extern "C" s32 SysGetSoundThreadStack_1c3530(void);
extern "C" void SoundSysInit_1b6f70(void *);
extern "C" void SoundRpcInit_1bc840(s32);
extern "C" void SoundSpuInit_1bb710(s32);
extern "C" void CdDiskWatchInit_17ff70(s32);
extern "C" void MakeCdPath_17fe90(void *);
extern "C" void CdDiskWatchSetEnabled_17fe80(s32);
extern "C" void DiscStatusInit_39eed0(void);
extern "C" void SysTickThreadStart_1c3470(void);
extern "C" void GfxSysInit_15dd20(s32);
extern "C" s32 GameDataHeapInit_1fed00(void);
extern "C" s32 MenuResStackInit_206980(void);
extern "C" void *GetMainStack_1c6dc0(void);
extern "C" void *Memalign_130ba8(s32, s32);
extern "C" void MemStackInit_14d810(void *, void *, s32);
extern "C" void MemStackReset_14d830(void *);
extern "C" void *GetStaticScene_1c6c70(void);
extern "C" void SoundSetThreadedUpdate_1c3520(s32);
extern "C" void SysStateSetFlagRelated_1c6ac0(s32);
extern "C" void FrameCounterReset_1c6b10(void);
extern "C" void SetVblankCallback_15df10(void *);
extern "C" void SysVblankCallback_1c33a0(void);
extern "C" u32 strlen(char *);
extern "C" char *strcpy(char *, char *);

extern "C" u8 D_004B2570[];
extern "C" char D_0045B028[];
extern "C" char D_0045B038[];
extern "C" s32 D_0047DF30;
extern "C" s32 D_00481550;
extern "C" s32 D_0047E224;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s8 d;
} Cfg;

extern "C" void SysBootInit_1c2ee0(void)
{
    Cfg cfg;
    s32 a;
    s32 b;
    s32 n;
    char *buf;
    void *obj;

    PadOpenPorts_1c6bf0();
    SysParamTableLoadDefaults_1c6b20();
    PadUpdate_1843a0(D_004B2570);
    PadUpdate_1843a0(D_004B2570);
    IopHeapInitOnce_1c2310();
    SoundIopInit_1b7160();
    cfg.a = 5;
    cfg.b = 0;
    cfg.c = 0;
    cfg.d = 1;
    cfg.b = SysGetSoundThreadStack_1c3530();
    cfg.c = 0x2000;
    cfg.a = D_0047DF30 - 0xA;
    SoundSysInit_1b6f70(&cfg);
    SoundRpcInit_1bc840(D_0047DF30);
    SoundSpuInit_1bb710(4);
    CdDiskWatchInit_17ff70(D_0047DF30 - 5);
    MakeCdPath_17fe90(D_0045B028);
    CdDiskWatchSetEnabled_17fe80(1);
    DiscStatusInit_39eed0();
    SysTickThreadStart_1c3470();
    GfxSysInit_15dd20(2);
    a = GameDataHeapInit_1fed00();
    b = MenuResStackInit_206980();
    n = 0x19E000 - a - b;
    buf = (char *)GetMainStack_1c6dc0();
    if (strlen(D_0045B038) < 0x10) {
        strcpy(buf, D_0045B038);
    }
    MemStackInit_14d810(buf, Memalign_130ba8(0x10, n * 0x10), n);
    MemStackReset_14d830(buf);
    obj = GetStaticScene_1c6c70();
    ((VE *)obj)->f0C();
    D_00481550 = 0;
    SoundSetThreadedUpdate_1c3520(0);
    SysStateSetFlagRelated_1c6ac0(0);
    SysStateSetFlagRelated_1c6ac0(1);
    FrameCounterReset_1c6b10();
    SetVblankCallback_15df10((void *)SysVblankCallback_1c33a0);
    D_0047E224 = 0;
}
