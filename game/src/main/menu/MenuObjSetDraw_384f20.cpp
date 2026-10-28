/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT24d {
    u8 pad[0x24];
    void (*unk24)(void *);
} VT24d;

void DrawListAddTexLoad_1418c0(s32, s32, f32);
void ModelSetPos_151110(void *, u32 *);
s32 GetDrawCtx_15de80(void);
void GuardEffectDraw_2d50b0(u8 *);
s32 GetEffectMgr_2d9040(void);
void EffectMgrDraw_2e2f30(s32);
s32 MenuObjSlotIsActive_3849d0(void *);

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void f() { VCM0(void, 0x24); }
};
class VC_1 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void f() { VCM0(void, 0x24); }
};
class VC_2 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void f() { VCM0(void, 0x24); }
};
class VC_3 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void f() { VCM0(void, 0x24); }
};
void MenuObjSetDraw_384f20(u8 *arg0) {
    rg_u128 sp40;
    s32 var_16;
    s32 var_16_2;
    s32 var_16_3;
    s32 var_16_4;
    u8 *temp_18;
    VT24d **temp_2;
    u8 *temp_2_2;

    var_16 = 0;
    do {
        GuardEffectDraw_2d50b0(arg0 + (var_16 * 0x340) + 0x10);
        var_16 += 1;
    } while (var_16 < 6);
    DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x269, 1.0f);
    var_16_2 = 0;
    do {
        temp_18 = arg0 + (var_16_2 * 0x7A0);
        if (((unsigned char)MenuObjSlotIsActive_3849d0(temp_18 + 0x13B0)) != 0) {
            ((VC_0 *)(temp_18 + 0x13C0))->f();
        }
        var_16_2 += 1;
    } while (var_16_2 < 2);
    var_16_3 = 0;
    do {
        temp_2 = (VT24d **)(arg0 + (var_16_3 * 0x790));
        ((VC_1 *)((u8 *)temp_2 + 0x22F0))->f();
        var_16_3 += 1;
    } while (var_16_3 < 2);
    if (((unsigned char)MenuObjSlotIsActive_3849d0(arg0 + 0x3210)) != 0) {
        var_16_4 = 0;
        do {
            temp_2_2 = *(u8 **)(arg0 + (var_16_4 * 4) + 0x3210);
            if (temp_2_2 != NULL) {
            sp40 = *(rg_u128 *)(temp_2_2 + 0x180);
                ModelSetPos_151110(arg0 + 0x3220, (u32 *)&sp40);
                ((VC_2 *)(arg0 + 0x3220))->f();
            }
            var_16_4 += 1;
        } while (var_16_4 < 2);
    }
    if (((unsigned char)MenuObjSlotIsActive_3849d0(arg0 + 0x39B0)) != 0) {
        ((VC_3 *)(arg0 + 0x39C0))->f();
    }
    EffectMgrDraw_2e2f30(GetEffectMgr_2d9040());
}

}
