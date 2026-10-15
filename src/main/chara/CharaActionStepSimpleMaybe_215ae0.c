/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: RIGHT LENGTH (90w), 65 bad -- large residue, needs a fresh read, not attempted further. */
#include "types.h"

s32 CharaPlayedMotionIsCurrent_2124c0(void);
void CharaPlayMotion_212590(void *, s32, s32, s32, f32);
s32 CharaGetId_214a80(void *);
void CharaClearActionEffects_214ce0(void *);
s32 CharaTableEntryAt_225420(s32, s32);
void ActDataRunEvnts_225b70(s32, s32);
s32 CharaTableEntryGetMotionFlags_226240(s32);
s32 CharaTableDataGetMotionName_2269e0(s32);
f32 CharaGetMotionFrame_238570(void *);

void CharaActionStepSimpleMaybe_215ae0(u8 *arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_17;
    s32 temp_19;
    s32 temp_5;

    *(s32 *)(arg0 + 0x42C) = 0;
    temp_16 = *(s32 *)(arg0 + 0xA14);
    temp_19 = *(s32 *)(arg0 + 0xA18);
    switch (*(s16*)(arg0 + 0xA34)) {
    case 0x3E7:
    if ((CharaPlayedMotionIsCurrent_2124c0() != 0) && (temp_19 != 0) && (CharaTableEntryGetMotionFlags_226240(temp_19) & 2) && !(CharaGetMotionFrame_238570(arg0) < 1.0f)) {
        temp_5 = *(s32*)(arg0 + 0xA20) + 1;
        *(s32*)(arg0 + 0xA20) = temp_5;
        if (CharaTableEntryAt_225420(temp_16, temp_5) == 0) {
            *(s16*)(arg0 + 0xA34) = -1;
            *(s16*)(arg0 + 0xA38) = 0;
            return;
        }
        *(s16*)(arg0 + 0xA34) = -1;
        CharaActionStepSimpleMaybe_215ae0(arg0, arg1);
        return;
    }
    break;
    default:
        if (temp_19 != 0) {
            temp_17 = CharaTableDataGetMotionName_2269e0(temp_19);
            CharaPlayMotion_212590(arg0, *(s32*)(arg0 + 0x3F4), temp_17, CharaTableEntryGetMotionFlags_226240(temp_19), *(f32 *)(arg0 + 0xA10));
        }
        *(s16*)(arg0 + 0xA34) = 0x3E7;
        *(s32*)(arg0 + 0xAD0) = 0;
        *(s32*)(arg0 + 0xAD4) = 0;
        CharaClearActionEffects_214ce0(arg0);
        ActDataRunEvnts_225b70(temp_16, CharaGetId_214a80(arg0));
        break;
    }
    *(s64*)(arg0 + 0x3D0) = *(s64*)(arg0 + 0x3D0) | ((s64) 0x04000000 << 0x20);
    *(s64*)(arg0 + 0x568) = 0;
    *(s64*)(arg0 + 0x570) = 0;
}
