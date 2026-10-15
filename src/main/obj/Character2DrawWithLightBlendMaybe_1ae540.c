#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;
typedef struct {
    u128 v0;
    u128 v1;
    s32 id;
    s32 z;
    u8 pad[0xF0 - 0x28];
    u128 vF0;
    u8 pad2[0x1C0 - 0x100];
} Big;

extern void LightStateSetCurrent_142920(s32 arg0, s32 arg1);
extern s32 LightStatePush_1429f0(s32 arg0, s32 *arg1, s32 arg2);
extern void DrawListAddLightPacket_148120(s32 arg0);
extern void LightStateInit_156b50(s32 *arg0);
extern void LightStateSetAmbient_15cb30(Big *arg0);
extern void LightStateSetMatrices_15cc00(void * arg0, void * arg1);
extern s32 GetDrawCtx_15de80(void);
extern s32 ModelObjExDraw_1ad7a0(u8 * arg0);
extern void sceVu0InterVector(u128 *v0, u128 * v1, void * v2, f32 t);

s32 Character2DrawWithLightBlendMaybe_1ae540(u8 * arg0, u128 * arg1, f32 fparg0)
{
    Big b;
    u128 *pa;
    u128 * pb;
    u8 * pc;
    s32 temp_18;
    s32 temp_17;
    s32 temp_16;

    temp_18 = GetDrawCtx_15de80();
    b.z = 0;
    b.id = -1;
    LightStateInit_156b50(&b.id);
    temp_17 = LightStatePush_1429f0(temp_18, &b.id, 1);
    LightStateSetMatrices_15cc00(arg0 + 0x630, arg0 + 0x6F0);
    sceVu0InterVector(&b.v1, arg1, arg0 + 0x5D0, fparg0);
    pb = arg1;
    pa = &b.v0;
    pc = arg0 + 0x5A0;
    sceVu0InterVector(pa, pb, pc, fparg0);
    b.vF0 = b.v1;
    LightStateSetAmbient_15cb30(&b);
    DrawListAddLightPacket_148120(temp_18);
    temp_16 = ModelObjExDraw_1ad7a0(arg0);
    LightStateSetCurrent_142920(temp_18, temp_17);
    return temp_16;
}
