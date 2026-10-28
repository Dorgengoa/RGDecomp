#include "types.h"

extern "C" void MemStackHeapFree_14dcb0(void *arg0, s32 arg1);
extern "C" void MemStackHeapReinit_14de90(void *arg0);
extern "C" void EffTableUnlinkAll_1a0120(void *arg0);
extern "C" void EffTableDestroyAll_1a0240(void *arg0);
extern "C" void LoaderReleaseById_1cd340(s32 arg0, s32 arg1);
extern "C" s32 GetLoaderMgr_1f59d0(void);
extern "C" void EffectEntriesReleaseAll_2de210(void *arg0);

inline s32 chk(u8 *p) { return *(s32 *)(p + 0x28) != 0; }

extern "C" void EffectMgrReleaseAll_2e2af0(void *arg0) {
    u8 *p;
    s32 temp_2;
    u8 *rec;
    s32 i;
    s32 temp_5;
    s32 temp_5_2;
    u8 *temp_4;

    p = (u8 *)arg0;
    if (*(s16 *)(p + 0x4078) != 0) {
        temp_2 = GetLoaderMgr_1f59d0();
        if (temp_2 != 0) {
            EffectEntriesReleaseAll_2de210(p + 0x1674);
            EffTableUnlinkAll_1a0120(p + 0x58);
            EffTableDestroyAll_1a0240(p + 0x58);
            rec = p + 0x174;
            i = 0;
            do {
                temp_5 = *(s32 *)(rec + 0x60);
                if (temp_5 != -1) {
                    LoaderReleaseById_1cd340(temp_2, temp_5);
                }
                temp_4 = *(u8 **)(rec + 8);
                if ((temp_4 != 0) && !chk(temp_4)) {
                    temp_5_2 = *(s32 *)(rec + 0xC);
                    if (temp_5_2 != 0) {
                        MemStackHeapFree_14dcb0(temp_4, temp_5_2);
                    }
                }
                i += 1;
                rec += 0x70;
            } while (i < 0x30);
            MemStackHeapReinit_14de90(p);
        }
    }
}
