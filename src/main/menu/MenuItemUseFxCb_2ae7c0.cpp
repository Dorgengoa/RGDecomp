#include "types.h"

class VObj {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual s32 f128(s32);
};

extern "C" {
s32 SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
s32 GetCurrentScene_1f5be0();
u8 *GetGameData_1fede0();
s32 UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
s32 UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
s32 ActionResultSumMpHeal_3a6d00(u8 *);
s32 ActionResultSumHeal_3a6d10(u8 *);
VObj *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyFindSlotOfId_3c3070(s32, s32);
}
extern f32 D_0047D35C;
extern f32 D_0047D714;
extern s32 D_0047EC74;
extern s32 D_0047EC78;
extern s32 D_00482360;

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
