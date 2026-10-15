/* s41 agent10: MATCH (byte clear loop). */
#include "types.h"

void ModelSetScale_150ff0(s32, s32 *);
void GetCurrentScene_1f5be0(void);
void CharaReleaseHeldTarget_2116b0(void *, f32 , f32 , f32 , s32);
void CharaExecInfoInit_219100(void *);
void CharaHitInfoInit_219140(void *);
void CharaSquashReset_219300(void *);
void CharaMoveReqReset_2194d0(void *);
void CharaResetToBaseMode_21e830(void *);
extern s32 CharaSetSrtVec40_238760(void *, f32, f32, f32);
extern s32 CharaSetVelocity_238770(void *, f32, f32, f32);
void SwordTrailStop_2d7620(s32);
s32 GetEffectMgr_2d9040(void);
void EffectReleaseNodesByKey_2e1250(s32, s16, s32);
void TargetRefClear_2e71d0(void *);
void CharaSquashResetThunk_219300(void *);
void CharaMoveReqResetThunk_2194d0(void *);

void CharaResetStateMaybe_212c50(u8 *arg0) {
    s32 spbuf[0x4];
    u8 *var_3;
    s32 var_18;
    s32 var_17;
    u32 var_2;
    s32 a0v;

    CharaMoveReqResetThunk_2194d0(arg0 + 0x930);
    CharaSquashResetThunk_219300(arg0 + 0x950);
    CharaReleaseHeldTarget_2116b0(arg0, 0.0f, 0.0f, 0.0f, 0);
    TargetRefClear_2e71d0(arg0 + 0x9AC);
    TargetRefClear_2e71d0(arg0 + 0x97C);
    if ((*(s32 *)(arg0 + 0x428) != 0) && (*(s32 *)(arg0 + 0x3F4) != 0)) {
        *(s32 *)(arg0 + 0x3DC) = 0;
        *(u8 *)(arg0 + 0xA68) = 0;
        *(u32 *)(arg0 + 0xA88) = 0x3F800000;
        if (*(s32 *)(arg0 + 0x3F4) != 0) {
            *(s16 *)(arg0 + 0xA58) = -1;
            *(s16 *)(arg0 + 0xA5A) = -1;
        }
        GetCurrentScene_1f5be0();
        *(s16 *)(arg0 + 0xA5C) = -1;
        *(s16 *)(arg0 + 0xA5E) = -1;
        CharaMoveReqReset_2194d0(arg0 + 0x930);
        CharaSquashReset_219300(arg0 + 0x950);
        CharaHitInfoInit_219140(arg0 + 0x870);
        CharaExecInfoInit_219100(arg0 + 0x8B0);
        a0v = *(s32 *)(arg0 + 0x3F4);
        var_3 = (u8 *)spbuf;
        var_2 = 0x10;
        if (var_3 != NULL) {
            do {
                *var_3 = 0;
                var_2 -= 1;
                var_3 += 1;
            } while (var_2 != 0);
        }
        ((u32 *)spbuf)[0] = 0x3F800000;
        ((u32 *)spbuf)[1] = 0x3F800000;
        ((u32 *)spbuf)[2] = 0x3F800000;
        ModelSetScale_150ff0(a0v, spbuf);
        CharaResetToBaseMode_21e830(arg0);
        EffectReleaseNodesByKey_2e1250(GetEffectMgr_2d9040(), *(s32 *)(arg0 + 0x424), 0xBB8);
        if (*(s32 *)(arg0 + 0x3F4) != 0) {
            *(s16 *)(arg0 + 0xA58) = -1;
            *(s16 *)(arg0 + 0xA5A) = -1;
        }
        var_18 = *(s32 *)(arg0 + 0x584);
        if (var_18 != 0) {
            var_17 = 0;
            while (var_17 < *(s32 *)(arg0 + 0x588)) {
                TargetRefClear_2e71d0((u8 *)(var_18 + 0x30));
                TargetRefClear_2e71d0((u8 *)(var_18 + 0x60));
                SwordTrailStop_2d7620(var_18);
                var_17 += 1;
                var_18 += 0xB8;
            }
        }
        CharaSetVelocity_238770(arg0, 0, 0, 0);
        CharaSetSrtVec40_238760(arg0, 0, 0, 0);
    }
}
