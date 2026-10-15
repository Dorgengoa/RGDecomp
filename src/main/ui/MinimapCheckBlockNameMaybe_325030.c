#include "types.h"

typedef struct {
    u8 pad0[0x30];
    s16 unk30;
} Sub18;

typedef struct {
    u8 pad0[0x18];
    Sub18 *unk18;
} Obj001fede0;

typedef struct {
    u8 pad0[0xDC];
    f32 unkDC;
    u8 pad0xE0[0xE4 - 0xE0];
    f32 unkE4;
} Obj0Arg0;

extern s32 MapBlockGetName_1dff20(s32, s32);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32 *);
extern Obj001fede0 *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern char *MinimapGetPendingOrCurEntry_32a8f0(Obj0Arg0 *);
extern char *MinimapGetCurOrPendingEntry_32a920(Obj0Arg0 *);
extern s32 strcmp(const char *, const char *);

s32 MinimapCheckBlockNameMaybe_325030(Obj0Arg0 *arg0, s32 arg1, s32 arg2, f32 *arg3)
{
    s32 sp7C;
    s32 temp_17;
    s32 temp_2;
    s32 temp_2_2;
    char *var_16;
    s16 k;
    char *name;

    temp_17 = GetMapMgr_201a90();
    var_16 = 0;
    *arg3 = 1.0f;
    switch (arg2) {
    case 0:
        *arg3 = arg0->unkDC;
        var_16 = MinimapGetCurOrPendingEntry_32a920(arg0);
        break;
    case 1:
        *arg3 = arg0->unkE4;
        var_16 = MinimapGetPendingOrCurEntry_32a8f0(arg0);
        break;
    }
    if (temp_17 != 0) {
        sp7C = 0;
        temp_2 = MapSlotsFindBlockById_1e49b0(temp_17, arg1, &sp7C);
        if ((temp_2 != 0) && (var_16 != 0)) {
            k = GetGameData_1fede0()->unk18->unk30;
            name = var_16 + 0x54;
            temp_2_2 = MapBlockGetName_1dff20(temp_2, k);
            if ((temp_2_2 != 0) && (strcmp(name, (const char *) temp_2_2) != 0)) {
                return 0;
            }
        }
    }
    return 1;
}
