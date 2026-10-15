#include "types.h"


typedef struct {
    u8 pad0[0x8];
    s32 id;
} Info;

typedef struct {
    u8 pad0[0x1188];
    Info *info;
} Scene;

typedef struct {
    u8 pad0[0x24];
    Scene *scene;
} Ctx;

typedef struct {
    u8 pad0[4];
    u8 b0:1;
    u8 b1:7;
} Flag;

extern "C" {
extern Ctx *GetGameData_1fede0(void);
extern s32 SaveResultSetFromDataError_374070(s32);
extern void SaveFileReadInsectTeams_3e49d0(Ctx *, u8 *, s32 *, s32, s32);
extern void RecordSetBlobSize_4302c0(Scene *, s32);
extern Flag *RecordGetPayloadIfKind3E_430ad0(Scene *);
extern void *memcpy(void *, s32, s32);
extern void *memset(void *, s32, s32);
extern void *D_00483188;
extern s32 D_0048318C;
}

extern "C" s32 SaveResultInsectTeamsCb_373b40(s32 arg0, s32 arg1, s32 arg2)
{
    s32 sp6C;
    Ctx *c;
    u8 *d;
    bool ok;
    s32 v;
    Flag *f;

    if (D_00483188 != 0) {
        memset(D_00483188, 0, 0x20000);
        memcpy(D_00483188, arg1, arg2);
        D_0048318C = arg2;
    }
    c = GetGameData_1fede0();
    d = (u8 *)c->scene + 8;
    ok = 0;
    if (d != 0) {
        sp6C = 0;
        ok = 1;
        SaveFileReadInsectTeams_3e49d0(c, d, &sp6C, arg1, arg2);
        RecordSetBlobSize_4302c0(c->scene, sp6C);
    }
    v = SaveResultSetFromDataError_374070(arg0);
    if (ok && (v == 0 || v == 10)) {
        if (c->scene->info->id == 0x26E) {
            f = RecordGetPayloadIfKind3E_430ad0(c->scene);
            if (f != 0) {
                f->b0 = 1;
            }
        }
    }
    return 1;
}
