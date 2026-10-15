#include "types.h"

typedef struct S001ff460 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S001ff460;

typedef struct Ctx001ff460 {
    u8 pad0[0x18];
    s32 unk18;
    u8 pad1C[0x44];
    s32 unk60;
} Ctx001ff460;

typedef struct Ctx3_001ff460 {
    u8 pad0[0x30];
    s16 unk30;
} Ctx3_001ff460;

typedef struct Ctx2_001ff460 {
    u8 pad0[0x18];
    Ctx3_001ff460 *unk18;
} Ctx2_001ff460;

extern void VecCopy_1cbe30(void *, s32);
extern s32 MapGetAreaLightSetById_1e54d0(void *, s32, s32);
extern s32 MapGetAreaSlot2_1e5740(void *);
extern s32 MapGetFirstAreaSlot_1e5760(void *);
extern s32 MapDataGetLightSet_1e77c0(s32, s32);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern Ctx2_001ff460 *GetGameData_1fede0(void);
extern Ctx001ff460 *GetMapMgr_201a90(void);

void MapGetAreaBgColor_1ff460(S001ff460 *arg0) {
    s32 temp_2_2;
    s32 temp_2_3;
    Ctx001ff460 *temp_2;
    s32 var_17;

    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0x43000000;
    temp_2 = GetMapMgr_201a90();
    var_17 = MapGetAreaSlot2_1e5740(temp_2);
    if ((var_17 == 0) || (MapDataIsLoaded_1e79d0(var_17) == 0)) {
        if (temp_2->unk60 & 2) {
            temp_2_2 = MapGetAreaLightSetById_1e54d0(temp_2, GetGameData_1fede0()->unk18->unk30, 0);
            if (temp_2_2 != 0) {
                VecCopy_1cbe30(arg0, temp_2_2 + 0x10);
                return;
            }
        }
        var_17 = MapGetFirstAreaSlot_1e5760(temp_2);
        if (var_17 != 0) {
            if (MapDataIsLoaded_1e79d0(var_17) == 0) {
                return;
            }
        } else {
            return;
        }
    }
    temp_2_3 = MapDataGetLightSet_1e77c0(var_17, 0);
    if (temp_2_3 != 0) {
        VecCopy_1cbe30(arg0, temp_2_3 + 0x10);
    }
}
