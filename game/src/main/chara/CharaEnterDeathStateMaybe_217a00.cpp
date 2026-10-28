/* rgp:protos */
#line 1
#include "types.h"

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v2A8() { return VCM0(s32, 0x2A8); }
};

typedef struct Unit {
    u8 pad0[0x3D0];
    u64 m3D0;
    u8 pad3D8[0x1C];
    s32 m3F4;
    u8 pad3F8[0x34];
    s32 m42C;
    u8 pad430[0x138];
    u64 m568;
    u8 pad570[0x4BC];
    s16 mA2C;
    s16 mA2E;
    u8 padA30[4];
    s16 mA34;
    s16 mA36;
    u8 padA38[0xC];
    s32 mA44;
} Unit;

extern "C" {
extern void Sprintf_1343b8(char *, const char *, s32, const char *);
extern void ModelMotionEventReleaseHandlers_1b02b0(s32, int);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ParamTableSetAlpha_1cfb10(s32, s32, f32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetGameData_1fede0(void);
extern void CharaPlayMotion_212590(Unit *, s32, char *, s32, f32);
extern s32 CharaGetId_214a80(Unit *);
extern void CharaSetActionModeDeath_217d70(Unit *);
extern void CharaResetToBaseMode_21e830(Unit *);
extern Chr *ActorFindById_3eb870(s32, s32);
extern char *strcpy(char *, const char *);
extern char D_0045CBD8[];
extern char D_0045CBF0[];
extern char D_0045CBF8[];
extern char D_0045CC00[];
extern char D_0045CC08[];
extern char D_0045CC10[];
}

static inline bool IsBusy(Unit *u) {
    return (u->m3D0 & 0x0200000000000000ULL) != 0 || (u->mA44 & 0x400000) != 0;
}

extern "C" void CharaEnterDeathStateMaybe_217a00(Unit *self)
{
    char buf[0x20] __attribute__((aligned(16)));
    s32 hud;
    s32 w;
    Chr *c;
    s16 n;
    bool free;

    CharaSetActionModeDeath_217d70(self);
    self->m42C = 0;
    self->mA34 = 10;
    self->mA36 = 27;
    hud = GetCurrentScene_1f5be0();
    free = !IsBusy(self);
    if (free) {
        ModelMotionEventReleaseHandlers_1b02b0(self->m3F4, 0);
        ParamTableSetAlpha_1cfb10(hud, ((short)CharaGetId_214a80(self)), 0.0f);
        ObjRecSetFlags_1c3e00(hud, 1, ((short)CharaGetId_214a80(self)), 0xA0038);
        return;
    }
    w = GetGameData_1fede0();
    c = ActorFindById_3eb870(w, ((short)CharaGetId_214a80(self)));
    if (c != 0 && c->v2A8() != 0) {
        ParamTableSetAlpha_1cfb10(hud, ((short)CharaGetId_214a80(self)), 0.0f);
    } else {
        ParamTableSetAlpha_1cfb10(hud, ((short)CharaGetId_214a80(self)), 1.0f);
    }
    ObjRecClearFlags_1c3dc0(hud, 1, ((short)CharaGetId_214a80(self)), 0xA0038);
    if (self->m568 & 0x0000100000000000ULL) {
        CharaResetToBaseMode_21e830(self);
        return;
    }
    if (self->mA2E == 2) {
        n = self->mA2C;
        if (n <= 0) {
            strcpy(buf, D_0045CC00);
        } else {
            Sprintf_1343b8(buf, D_0045CBD8, n + 0x60, D_0045CC08);
        }
    } else if (self->mA2E == 3) {
        n = self->mA2C;
        if (n <= 0) {
            strcpy(buf, D_0045CC10);
        } else {
            Sprintf_1343b8(buf, D_0045CBF0, n + 0x60, D_0045CC08);
        }
    } else {
        n = self->mA2C;
        if (n <= 0) {
            strcpy(buf, D_0045CC08);
        } else {
            Sprintf_1343b8(buf, D_0045CBF8, n + 0x60, D_0045CC08);
        }
        strcpy(buf, D_0045CC08);
    }
    CharaPlayMotion_212590(self, self->m3F4, buf, 4, 1.0f);
}
