#include "types.h"

extern u8 D_0049D390[];
extern u8 D_0049D3D0[];
extern u8 D_0049D3F0[];
extern struct { void *v; s32 pad[3]; } D_0049D3BC;
extern struct { s32 v; s32 pad[3]; } D_0049D3C0;
extern struct { void *v; s32 pad[3]; } D_0049D3C8;
extern struct { s32 v; s32 pad[3]; } D_0049D3CC;

extern void *memset(void *, s32, u32);

void StaticInitInfoCfgLoadDesc_4694a0(void)
{
    memset(D_0049D390, 0, 0x88);
    D_0049D3C0.v = 8;
    D_0049D3BC.v = D_0049D3D0;
    D_0049D3CC.v = 8;
    D_0049D3C8.v = D_0049D3F0;
}
