#include "types.h"

extern s32 CharaSysGetEncounterIdMaybe_3a36d0(void *);
extern void CharaSysDeactivateMaybe_3a3760(void *);
extern void HandleEntryRelease_3f2500(void *, s32, s32);
extern void *D_00483890;
extern void *D_00483894;

void PartyResetZoneListsMaybe_3cb210(void *arg0, s32 arg1) {
    s32 var_2;
    s32 var_7;
    s32 var_7_2;
    void *temp_2;
    void *temp_4;
    void *temp_6;
    void *temp_6_2;

    var_7 = 0;
    *(s16 *)((u8 *)arg0 + 0x3A) = 0;
    do {
        temp_6 = (u8 *)arg0 + (var_7 * 4);
        var_7 += 1;
        *(s16 *)((u8 *)temp_6 + 0x3E) = -1;
        *(s16 *)((u8 *)temp_6 + 0x40) = -1;
    } while (var_7 < 8);
    *(s16 *)((u8 *)arg0 + 0x3C) = 0;
    var_7_2 = 0;
    do {
        temp_6_2 = (u8 *)arg0 + (var_7_2 * 4);
        var_7_2 += 1;
        *(s16 *)((u8 *)temp_6_2 + 0x5E) = -1;
        *(s16 *)((u8 *)temp_6_2 + 0x60) = -1;
    } while (var_7_2 < 8);
    *(s16 *)((u8 *)arg0 + 0x7E) = -1;
    *(s16 *)((u8 *)arg0 + 0x80) = -1;
    *(s16 *)((u8 *)arg0 + 0x82) = -1;
    if (D_00483890 != NULL) {
        temp_4 = *(void **)((u8 *)D_00483890 + 0x20);
        temp_2 = *(void **)((u8 *)temp_4 + 0x238);
        if (temp_2 != NULL) {
            var_2 = *(s16 *)((u8 *)temp_2 + 0x168);
        } else {
            var_2 = 0;
        }
        if (var_2 != 0 || CharaSysGetEncounterIdMaybe_3a36d0(temp_4) < 0) {
            CharaSysDeactivateMaybe_3a3760(*(void **)((u8 *)D_00483890 + 0x20));
        }
    }
    if (arg1 != 0 && D_00483894 != NULL) {
        HandleEntryRelease_3f2500(D_00483894, *(s32 *)((u8 *)D_00483894 + 0xC) + 0x1C, 1);
    }
}
