#include "types.h"
#pragma opt_repositioncode off
extern s32 TargetRefGetMapObj_2e7050(void *);
extern s32 EvMapObjGetModel_366bb0(void);
extern s32 EvMapObjNodeGetFrame_3673d0(s32);

s32 EvMapObjIsTargetActive_365620(u8 *arg0) {
    s32 p;
    s32 i;

    if (EvMapObjGetModel_366bb0() == 0) {
        return 0;
    }
    if (TargetRefGetMapObj_2e7050(arg0 + 0xA0) == 0) {
        return 0;
    }
    p = *(s32 *)(arg0 + 0x2F4);
    for (i = 0; i < *(s16 *)(arg0 + 0x2FC); i++, p += 0x150) {
        if (EvMapObjNodeGetFrame_3673d0(p) == 0) {
            return 0;
        }
    }
    return 1;
}
