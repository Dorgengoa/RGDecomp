/* rgp:protos */
#line 1
#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f128(s32 a0) { return VCM(s32, (void *, s32), 0x128, a0); }
};

extern "C" {
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
s32 GetCurrentScene_1f5be0();
u8 *GetGameData_1fede0();
void UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
s32 ActionResultSumMpHeal_3a6d00(u8 *);
s32 ActionResultSumHeal_3a6d10(u8 *);
VObj *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyFindSlotOfId_3c3070(s32, s32);
}
extern "C" f32 D_0047D35C;
extern "C" f32 D_0047D714;
extern "C" s32 D_0047EC74;
extern "C" s32 D_0047EC78;
extern "C" s32 D_00482360;

extern "C" s32 MenuItemUseFxCb_2ae7c0(u8 *arg0)
{
    s32 idA;
    s32 idB;
    u8 *h;
    s16 *q;
    s32 r10;
    u64 bit;
    u8 *t16;
    s32 t22;
    s32 snd;
    s32 a4;
    bool flag;
    s32 eff;
    u8 *ent;
    VObj *o;
    s32 x;
    s32 a;
    s32 b;
    s32 c;
    s32 idx;

    if (arg0 == NULL) {
        return 0;
    }
    h = *(u8 **)arg0;
    idA = -1;
    idB = -1;
    if (h != NULL) {
        q = *(s16 **)(h + 0xC);
        if (q != NULL) {
            idA = *(s16 *)(h + 8);
            idB = *q;
        }
    }
    r10 = ActionResultSumHeal_3a6d10(arg0);
    ActionResultSumMpHeal_3a6d00(arg0);
    bit = ((u64)((u64)arg0[0x41] << 0x38) >> 0x3F) & 0xFF;
    if (arg0[0x18] != 0) {
        t16 = GetGameData_1fede0();
        t22 = GetCurrentScene_1f5be0();
        snd = -1;
        a4 = *(s32 *)(arg0 + 4);
        flag = false;
        eff = -1;
        if ((u32)(idB - 0x40DA) < 4U) {
            CharaMgrPoolFindById_3a8c60(*(s32 *)(t16 + 0x14), a4);
            ent = ObjRecGetLiveObject_1c4a90(t22, a4);
            flag = true;
            snd = 0x2F;
        } else if ((u32)(idB - 0x40DE) < 2U) {
            CharaMgrPoolFindById_3a8c60(*(s32 *)(t16 + 0x14), idA);
            ent = ObjRecGetLiveObject_1c4a90(t22, idA);
            snd = 0x30;
        } else {
            o = CharaMgrPoolFindById_3a8c60(*(s32 *)(t16 + 0x14), a4);
            ent = ObjRecGetLiveObject_1c4a90(t22, a4);
            flag = true;
            if (o != NULL) {
                x = o->f128(1) * 3 / 4;
                if (r10 >= x || bit != 0) {
                    eff = 0x15;
                } else {
                    eff = 0x14;
                }
            }
        }
        if (flag) {
            a = PartyCountMembers_3c2010(*(s32 *)(t16 + 0x18), 1, 1);
            b = PartyCountReserve_3c1c20(*(s32 *)(t16 + 0x18), 1, 1);
            c = PartyFindSlotOfId_3c3070(*(s32 *)(t16 + 0x18), *(s32 *)(arg0 + 4));
            if (a < 3 && b > 0 && a <= c) {
                c += 3 - a;
            }
            idx = (c + 0x8F) & 0xFFFF;
            UiSetWidgetColor_2905b0(D_00482360, idx, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f);
            UiFadeWidgetColor_2904e0(D_00482360, idx, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D714);
        }
        if (snd > 0) {
            GameSceneSoundSlot0PlaySeVol_1d05f0(t22, snd, 1.0f);
            D_0047EC78 = snd;
        }
        if (eff > 0 && ent != NULL) {
            SoundPlayScaledVolume_1b9520(*(s32 *)(ent + 0x4FC), eff, 0, 1.0f);
            D_0047EC74 = eff;
        }
    }
    return 1;
}
