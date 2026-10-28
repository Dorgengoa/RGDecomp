/* rgp:protos */
#line 1
#include "types.h"

class ObjC0 {
    u8 pad[0xC0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void vA4(f32 * a0) { VCM(void, (void *, f32 *), 0xA4, a0); }
};

extern "C" {
s32 GetDrawCtx_15de80(void);
ObjC0 *ObjRecGetLiveObject_1c3bc0(void *, s32);
void *GetCurrentScene_1f5be0(void);
s32 GetGameData_1fede0(void);
void ObjRecUpdateDistLightMaybe_319f60(void *, f32 *, s32);
s32 InsectBattleGet_31a8d0(void);
void func_50A520(void);
extern f32 D_0047F250;
extern f32 D_0047F254;
extern f32 D_0047F258;
extern f32 D_0047F25C;
}

extern "C" void InsectDrawPre_319e70(void) {
    f32 v[4] __attribute__((aligned(16)));
    s32 i;
    s32 r;
    void *temp_17;
    ObjC0 *temp_2;

    temp_17 = GetCurrentScene_1f5be0();
    GetDrawCtx_15de80();
    GetGameData_1fede0();
    v[0] = D_0047F250;
    v[1] = D_0047F254;
    v[2] = D_0047F258;
    v[3] = D_0047F25C;
    temp_2 = ObjRecGetLiveObject_1c3bc0(temp_17, *(s32 *)((u8 *)temp_17 + 0x4344));
    if (temp_2 != NULL) {
        temp_2->vA4(v);
    }
    i = 0x80;
    do {
        ObjRecUpdateDistLightMaybe_319f60(temp_17, v, i);
        i += 1;
    } while (i <= 0x9B);
    i = 0xC0;
    do {
        ObjRecUpdateDistLightMaybe_319f60(temp_17, v, i);
        i += 1;
    } while (i <= 0xDF);
    r = InsectBattleGet_31a8d0();
    if (r != 0) {
        func_50A520();
    }
}
