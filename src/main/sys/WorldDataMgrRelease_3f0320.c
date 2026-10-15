#include "types.h"

extern void MemStackReset_14d830(s32 arg0);
extern void WorldDataRequestRelease_3f08f0(void);
extern void WorldDataRequestInit_3f4060(s32 arg0);
extern void WorldSubsysRelease_3f6800(s32 arg0);
extern void WorldSubsysRelease_3fd380(s32 arg0);
extern void WorldSubsysRelease_3ff440(s32 arg0);
extern void WorldSubsysRelease_405d20(s32 arg0);
extern void WorldSubsysRelease_406ce0(s32 arg0);
extern void WorldSubsysRelease_408370(s32 arg0);
extern void WorldSubsysRelease_40b380(s32 arg0);
extern void WorldSubsysRelease_410b60(s32 arg0);
extern void WorldSubsysRelease_424670(s32 arg0);

s32 WorldDataMgrRelease_3f0320(void *arg0, s32 arg1)
{
    u8 *base;
    s32 temp_16;
    s32 temp_4;

    base = (u8 *) arg0;
    temp_16 = *(s32 *) (base + 0x28);
    if (temp_16 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        WorldDataRequestRelease_3f08f0();
    }
    temp_4 = *(s32 *) (base + 0x88);
    if (temp_4 != 0) {
        WorldSubsysRelease_410b60(temp_4);
    }
    temp_4 = *(s32 *) (base + 0x8C);
    if (temp_4 != 0) {
        WorldSubsysRelease_408370(temp_4);
    }
    temp_4 = *(s32 *) (base + 0x94);
    if (temp_4 != 0) {
        WorldSubsysRelease_3fd380(temp_4);
    }
    temp_4 = *(s32 *) (base + 0x90);
    if (temp_4 != 0) {
        WorldSubsysRelease_406ce0(temp_4);
    }
    temp_4 = *(s32 *) (base + 0x98);
    if (temp_4 != 0) {
        WorldSubsysRelease_3ff440(temp_4);
    }
    temp_4 = *(s32 *) (base + 0x9C);
    if (temp_4 != 0) {
        WorldSubsysRelease_3f6800(temp_4);
    }
    temp_4 = *(s32 *) (base + 0xA0);
    if (temp_4 != 0) {
        WorldSubsysRelease_40b380(temp_4);
    }
    temp_4 = *(s32 *) (base + 0xA4);
    if (temp_4 != 0) {
        WorldSubsysRelease_405d20(temp_4);
    }
    temp_4 = *(s32 *) (base + 0xA8);
    if (temp_4 != 0) {
        WorldSubsysRelease_424670(temp_4);
    }
    temp_4 = *(s32 *) (base + 0x24);
    if (temp_4 != 0) {
        MemStackReset_14d830(temp_4);
    }
    if (arg1 != 0) {
        WorldDataRequestInit_3f4060(temp_16);
    }
    return 1;
}
