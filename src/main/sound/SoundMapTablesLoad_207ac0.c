#include "types.h"

extern void MemStackAlign64_14d8e0(s32 v);
extern void MemStackReturnToOwnerMaybe_14dad0(s32 v);
extern s32 MemStackHeapAlloc_14db10(s32 a, s32 b, s32 c, s32 d);
extern void MemStackHeapFree_14dcb0(s32 a, s32 b);
extern void PadWaitReady_1849e0(void *p);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(void *a, s32 b, s32 *c);
extern void GameSceneSoundEnvParseMapIndex_1d15c0(s32 a, s32 b, s32 c);
extern void GameSceneSoundRevTableSet_1d19f0(s32 a, s32 b, s32 c);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetReadBuffHeap_2025e0(void);
extern void GetSystemMemStack_202600(void);

extern u8 D_0045C5E0[];
extern u8 D_0045C5F0[];
extern u8 D_004B2570[];

void SoundMapTablesLoad_207ac0(s32 arg0)
{
    s32 sp5C;
    s32 t2;
    s32 t22;
    s32 t23;

    GetSystemMemStack_202600();
    t2 = GetReadBuffHeap_2025e0();
    t22 = MemStackHeapAlloc_14db10(t2, 2, 0, 0x40);
    if (t22 != 0) {
        MemStackAlign64_14d8e0(t2);
        t23 = GetCurrentScene_1f5be0();
        if (t23 != 0) {
            if (ResidentFileReadLocalizedMaybe_1c2860(D_0045C5E0, t22, &sp5C) != 0) {
                GameSceneSoundRevTableSet_1d19f0(t23, t22, sp5C);
            }
            if (arg0 != 0) {
                PadWaitReady_1849e0(D_004B2570);
            }
            if (ResidentFileReadLocalizedMaybe_1c2860(D_0045C5F0, t22, &sp5C) != 0) {
                GameSceneSoundEnvParseMapIndex_1d15c0(t23, t22, sp5C);
            }
            if (arg0 != 0) {
                PadWaitReady_1849e0(D_004B2570);
            }
        }
        MemStackReturnToOwnerMaybe_14dad0(t2);
        MemStackHeapFree_14dcb0(t2, t22);
    }
}
