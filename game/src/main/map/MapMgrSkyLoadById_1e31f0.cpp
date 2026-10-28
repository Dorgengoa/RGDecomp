/* rgp:protos */
#line 1
#include "types.h"

class C_001E31F0 {
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ 
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04C */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05C */ 
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ 
    /* +0x070 */ s32 v70(s16 a) { return VCM(s32, (void *, s16), 0x70, a); }
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
extern "C" int MapMgrSkyLoadDef_1e31b0(Obj_001E31F0 *, s32);

extern "C" int MapMgrSkyLoadById_1e31f0(Obj_001E31F0 *o, s32 b)
{
    G_001E31F0 *g;

    g = GetGameData_1fede0();
    return MapMgrSkyLoadDef_1e31b0(o, g->f08->f34->f0C->v70((s16)b));
}
