#include "types.h"

class C_001E31F0 {
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void s010();
    /* +0x014 */ virtual void s014();
    /* +0x018 */ virtual void s018();
    /* +0x01C */ virtual void s01C();
    /* +0x020 */ virtual void s020();
    /* +0x024 */ virtual void s024();
    /* +0x028 */ virtual void s028();
    /* +0x02C */ virtual void s02C();
    /* +0x030 */ virtual void s030();
    /* +0x034 */ virtual void s034();
    /* +0x038 */ virtual void s038();
    /* +0x03C */ virtual void s03C();
    /* +0x040 */ virtual void s040();
    /* +0x044 */ virtual void s044();
    /* +0x048 */ virtual void s048();
    /* +0x04C */ virtual void s04C();
    /* +0x050 */ virtual void s050();
    /* +0x054 */ virtual void s054();
    /* +0x058 */ virtual void s058();
    /* +0x05C */ virtual void s05C();
    /* +0x060 */ virtual void s060();
    /* +0x064 */ virtual void s064();
    /* +0x068 */ virtual void s068();
    /* +0x06C */ virtual void s06C();
    /* +0x070 */ virtual s32 v70(s16 a);
};

struct Lvl2_001E31F0 {
    u8 pad000[0xC];
    C_001E31F0 *f0C;
};

struct Lvl1_001E31F0 {
    u8 pad000[0x34];
    Lvl2_001E31F0 *f34;
};

struct G_001E31F0 {
    u8 pad000[0x8];
    Lvl1_001E31F0 *f08;
};

struct Obj_001E31F0;

extern "C" G_001E31F0 *GetGameData_1fede0(void);
extern "C" void MapMgrSkyLoadDef_1e31b0(Obj_001E31F0 *o, s32 r);

extern "C" void MapMgrSkyLoadById_1e31f0(Obj_001E31F0 *o, s32 b)
{
    G_001E31F0 *g;

    g = GetGameData_1fede0();
    MapMgrSkyLoadDef_1e31b0(o, g->f08->f34->f0C->v70((s16)b));
}
