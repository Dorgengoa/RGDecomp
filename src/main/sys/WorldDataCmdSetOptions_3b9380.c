#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Node {
    u8  pad000[0xC];
    s32 m0C;
} Node;

typedef struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
} Pool;

extern Pool *D_004830F8;
extern s32  VariantGetInt_15f780(R8 *q);
extern void OptionsSetFlagMaybe_3d6180(s32 h, s32 v);
extern void OptionsSetSoundOutput_3d6160(s32 h, s32 v);
extern void OptionsSetBgmVolume_3d6120(s32 h, s32 v);
extern void OptionsSetSeVolume_3d60e0(s32 h, s32 v);
extern void OptionsSetVoiceVolume_3d60a0(s32 h, s32 v);
extern void OptionsSetCameraBitMaybe_3d6080(s32 h, s32 v);
extern void OptionsSetCameraInvertY_3d6060(s32 h, s32 v);
extern void OptionsSetCameraInvertX_3d6040(s32 h, s32 v);
extern void OptionsSetDrawMessage_3d6020(s32 h, s32 v);
extern void OptionsSetFlagMaybe_3d5fe0(s32 h, s32 v);

s32 WorldDataCmdSetOptions_3b9380(R8 *a)
{
    Pool *p = D_004830F8;

    if (!p->b2) return 1;
    if (p->b0) return 1;

    if (VariantGetInt_15f780(a++) == 0) OptionsSetFlagMaybe_3d6180(p->m94->m0C, 0);
    else                        OptionsSetFlagMaybe_3d6180(p->m94->m0C, 1);

    if (VariantGetInt_15f780(a++) == 0) OptionsSetSoundOutput_3d6160(p->m94->m0C, 0);
    else                        OptionsSetSoundOutput_3d6160(p->m94->m0C, 1);

    OptionsSetBgmVolume_3d6120(p->m94->m0C, VariantGetInt_15f780(a++));
    OptionsSetSeVolume_3d60e0(p->m94->m0C, VariantGetInt_15f780(a++));
    OptionsSetVoiceVolume_3d60a0(p->m94->m0C, VariantGetInt_15f780(a++));

    if (VariantGetInt_15f780(a++) == 0) OptionsSetCameraBitMaybe_3d6080(p->m94->m0C, 0);
    else                        OptionsSetCameraBitMaybe_3d6080(p->m94->m0C, 1);

    if (VariantGetInt_15f780(a++) == 1) OptionsSetCameraInvertY_3d6060(p->m94->m0C, 2);
    else                        OptionsSetCameraInvertY_3d6060(p->m94->m0C, 0);

    if (VariantGetInt_15f780(a++) == 1) OptionsSetCameraInvertX_3d6040(p->m94->m0C, 4);
    else                        OptionsSetCameraInvertX_3d6040(p->m94->m0C, 0);

    if (VariantGetInt_15f780(a++) != 0) OptionsSetDrawMessage_3d6020(p->m94->m0C, 1);
    else                        OptionsSetDrawMessage_3d6020(p->m94->m0C, 0);

    if (VariantGetInt_15f780(a) != 0) OptionsSetFlagMaybe_3d5fe0(p->m94->m0C, 1);
    else                      OptionsSetFlagMaybe_3d5fe0(p->m94->m0C, 0);

    return 1;
}
