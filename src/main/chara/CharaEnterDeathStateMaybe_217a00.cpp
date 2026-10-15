#include "types.h"

class Chr {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void v0C8();
    virtual void v0CC();
    virtual void v0D0();
    virtual void v0D4();
    virtual void v0D8();
    virtual void v0DC();
    virtual void v0E0();
    virtual void v0E4();
    virtual void v0E8();
    virtual void v0EC();
    virtual void v0F0();
    virtual void v0F4();
    virtual void v0F8();
    virtual void v0FC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284();
    virtual void v288();
    virtual void v28C();
    virtual void v290();
    virtual void v294();
    virtual void v298();
    virtual void v29C();
    virtual void v2A0();
    virtual void v2A4();
    virtual s32 v2A8();
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
extern void ModelMotionEventReleaseHandlers_1b02b0(s32);
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
    char buf[0x20];
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
        ModelMotionEventReleaseHandlers_1b02b0(self->m3F4);
        ParamTableSetAlpha_1cfb10(hud, CharaGetId_214a80(self), 0.0f);
        ObjRecSetFlags_1c3e00(hud, 1, CharaGetId_214a80(self), 0xA0038);
        return;
    }
    w = GetGameData_1fede0();
    c = ActorFindById_3eb870(w, CharaGetId_214a80(self));
    if (c != 0 && c->v2A8() != 0) {
        ParamTableSetAlpha_1cfb10(hud, CharaGetId_214a80(self), 0.0f);
    } else {
        ParamTableSetAlpha_1cfb10(hud, CharaGetId_214a80(self), 1.0f);
    }
    ObjRecClearFlags_1c3dc0(hud, 1, CharaGetId_214a80(self), 0xA0038);
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
