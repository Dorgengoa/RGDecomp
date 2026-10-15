/* PARK 4/4: RIGHT LENGTH (91w), ONLY 1 bad word -- retail uses `daddiu $17,0,1` (64-bit) for `var_17=1`, ours uses plain `addiu`. Tried `s64 var_17` -- FIXED the instruction form but broke the LENGTH (92w vs 91w, extra save/restore). Reverted. Also tried `var_17 = (s32)(s64)1;` (cast at the point of assignment only) -- INERT, identical bytes to the s32 baseline. A sibling unit, HandleEntryRelease_3f2500, carries the exact same shape (`var_16 = 1;` -> daddiu vs addiu) -- worth trying whatever fixes one on the other. Still untried: check whether a DIFFERENT local needs the s64 width instead (the register mwcc gives var_17 might be shared with a genuinely-64-bit value elsewhere in retail). */
#include "types.h"

void MemStackReset_14d830(void *);
void HandleEntryFreeRes_3f2210(void);
u8 *MemStackArrayGet_3f2390(void *, s16);
u8 *MemStackArrayGet_3f23f0(void *, s16);
void HandleEntryInit_3f4160(void *);
s32 WorldSubsysZoneEntryRelease_41c400(s32, void *);
s32 WorldSubsysZoneEntryRelease_41e270(s32, void *);
s32 WorldSubsysZoneEntryRelease_426f10(s32, void *);
void *memset(void *, s32, s32);
char *strcpy(char *, const char *);
u32 strlen(const char *);
extern char D_00466D38[];

u16 HandleEntryRelease_3f1d80(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    s32 temp_6;
    u16 var_17;
    u8 *temp_2;
    u8 *temp_2_2;

    if (arg1 == NULL) {
        return 0;
    }
    var_17 = 1;
    if (arg2 != 0) {
        HandleEntryFreeRes_3f2210();
    }
    temp_4 = *(s32 *)(arg0 + 0x6C);
    if ((temp_4 != 0) && !(WorldSubsysZoneEntryRelease_41c400(temp_4, arg1) & 0xFF)) {
        var_17 = 0;
    }
    temp_4_2 = *(s32 *)(arg0 + 0x80);
    if ((temp_4_2 != 0) && !(WorldSubsysZoneEntryRelease_41e270(temp_4_2, arg1) & 0xFF)) {
        var_17 = 0;
    }
    temp_4_3 = *(s32 *)(arg0 + 0x78);
    if ((temp_4_3 != 0) && !(WorldSubsysZoneEntryRelease_426f10(temp_4_3, arg1) & 0xFF)) {
        var_17 = 0;
    }
    temp_2 = MemStackArrayGet_3f2390(arg0, *(s16 *)(arg1 + 0x10));
    if (temp_2 != NULL) {
        MemStackReset_14d830(temp_2);
        if (strlen(D_00466D38) < 0x10) {
            strcpy((char *)temp_2, D_00466D38);
        }
        temp_6 = *(s32 *)(temp_2 + 0x2C);
        memset(*(u8 **)(temp_2 + 0x28) + (temp_6 * 0x10), 0, (*(s32 *)(temp_2 + 0x34) - temp_6) * 0x10);
    }
    temp_2_2 = MemStackArrayGet_3f23f0(arg0, *(s16 *)(arg1 + 0x10));
    if (temp_2_2 != NULL) {
        MemStackReset_14d830(temp_2_2);
    }
    if (arg2 != 0) {
        HandleEntryInit_3f4160(arg1);
    }
    return var_17;
}
