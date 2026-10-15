#define KB 1
#define KE 1
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifndef KC
#define KC 0
#endif
#if KC == 0
#define C1(x) ((x) >= 4)
#define C2(x, y) ((x) >= (y))
#define C3(x) ((x) < 6)
#elif KC == 1
#define C1(x) ((x) > 3)
#define C2(x, y) ((y) <= (x))
#define C3(x) ((x) <= 5)
#elif KC == 2
#define C1(x) (!((x) < 4))
#define C2(x, y) (!((x) < (y)))
#define C3(x) (!((x) >= 6))
#elif KC == 4
static inline bool ge(s32 a, s32 b) { return a >= b; }
static inline bool lt(s32 a, s32 b) { return a < b; }
#define C1(x) ge((x), 4)
#define C2(x, y) ge((x), (y))
#define C3(x) lt((x), 6)
#elif KC == 5
static inline s32 ge(s32 a, s32 b) { return a >= b; }
static inline s32 lt(s32 a, s32 b) { return a < b; }
#define C1(x) ge((x), 4)
#define C2(x, y) ge((x), (y))
#define C3(x) lt((x), 6)
#else
#define C1(x) (!((x) <= 3))
#define C2(x, y) (!((y) > (x)))
#define C3(x) (!((x) > 5))
#endif
typedef struct { u8 pad[0x10]; void *sys; void *pad14; u8 *cfg; } Game;

Game *GetGameData_1fede0(void);
u8 *InsectBattleGet_31a8d0(void);
s32 func_4F4770(u8 *);
void GetCurrentScene_1f5be0(void);
s32 func_50DA40(u8 *, s32);
s32 func_50D6A0(u8 *, s32);
void func_50D7A0(u8 *, s32, s32, s32);
void func_50DAD0(u8 *, s32);
void func_50DA90(u8 *, s32);
void func_5104F0(s32);
void InsectBattleReset_31a700(void);
void InsectBattleReinit_31a5b0(void);
void StateVarSet_3cc9c0(void *, s32, s16, s32);
s32 StateVarGet_3ccac0(void *, s32);
void SoundBankFree_1b9c00(s32);
void GameReqPushWarp_285ea0(s32, s32, s32, s32);
s16 *InsectronRewardLookupMaybe_3e84f0(Game *, s32);
void InvAddItemRepeat_3c47b0(u8 *, s16, s32, s32);

s32 InsectBattleMatchUpdateMaybe_319800(void)
{
    Game *g;
    u8 *e;
    s32 a;
    s32 k;
    s16 *t;
#if KV
    s32 n;
    s16 v;
#else
    s16 v;
    s32 n;
#endif
    s32 i;
    s32 r;

    g = GetGameData_1fede0();
    e = InsectBattleGet_31a8d0();
#if KE
    if (e == 0) return 0;
    if (func_4F4770(e) != 0) {
#else
    if (e != 0 && func_4F4770(e) != 0) {
#endif
    GetCurrentScene_1f5be0();
    if (func_50DA40(e, 2) != 0) {
        if (func_50DA40(e, 3) != 0) return 1;
        switch (func_50D6A0(e, 0)) {
        case 1:
            StateVarSet_3cc9c0(g->sys, 7, 0, 0);
            StateVarSet_3cc9c0(g->sys, 6, 0, 0);
            StateVarSet_3cc9c0(g->sys, 11, func_50DA40(e, 0x3F), 0);
            SoundBankFree_1b9c00(5);
            GameReqPushWarp_285ea0(-1, 0x1F7, *(s16 *)(g->cfg + 6), 0);
            func_50D7A0(e, 2, 0, -1);
            break;
        case 2:
#if KB
            if (*(s8 *)(e + 0x5FC3) == 0) {
                func_50DAD0(e, 0x4D);
                InsectBattleReset_31a700();
                InsectBattleReinit_31a5b0();
                return 0;
            }
            return 1;
#else
            if (*(s8 *)(e + 0x5FC3) != 0) return 1;
            func_50DAD0(e, 0x4D);
            InsectBattleReset_31a700();
            InsectBattleReinit_31a5b0();
            return 0;
#endif
        }
    } else if (func_50DA40(e, 0x3E) != 0) {
        switch (func_50D6A0(e, 0)) {
        case 1:
            a = StateVarGet_3ccac0(g->sys, 5);
            if (StateVarGet_3ccac0(g->sys, 7) >= 4) {
                k = -1;
                if (StateVarGet_3ccac0(g->sys, 6) >= a) {
                    k = 0;
                } else if (StateVarGet_3ccac0(g->sys, 6) >= 6) {
                    switch (a) {
                    case 7:
                        k = 1;
                        break;
                    case 8:
                        k = 2;
                        break;
                    case 9:
                        k = 2;
                        break;
                    }
                } else {
                    k = 1;
                }
                if (k >= 0) {
                    t = InsectronRewardLookupMaybe_3e84f0(g, *(s16 *)(e + 0x5EFC));
                    if (t != 0) {
                        v = t[k * 2 + 1];
                        n = t[k * 2 + 2];
                        StateVarSet_3cc9c0(g->sys, 0x73, v, 0);
                        StateVarSet_3cc9c0(g->sys, 0x74, n, 0);
                        for (i = 0; i < n; i++) {
                            InvAddItemRepeat_3c47b0(g->cfg, v, 0, 1);
                        }
                    }
                }
            }
            StateVarSet_3cc9c0(g->sys, 11, 1, 0);
            SoundBankFree_1b9c00(5);
            GameReqPushWarp_285ea0(-1, 0x1F5, *(s16 *)(g->cfg + 6), 0);
            func_50D7A0(e, 10, 0, -1);
            break;
        case 10:
            a = StateVarGet_3ccac0(g->sys, 5);
            if (StateVarGet_3ccac0(g->sys, 7) >= 4) {
                StateVarSet_3cc9c0(g->sys, 7, 0, 0);
                if (StateVarGet_3ccac0(g->sys, 6) >= a) {
                    StateVarSet_3cc9c0(g->sys, 5, StateVarGet_3ccac0(g->sys, 6) + 1, 0);
                } else if (StateVarGet_3ccac0(g->sys, 6) >= 6) {
                    switch (a) {
                    case 7:
                        StateVarSet_3cc9c0(g->sys, 5, StateVarGet_3ccac0(g->sys, 5) + 1, 0);
                        break;
                    case 8:
                        StateVarSet_3cc9c0(g->sys, 5, StateVarGet_3ccac0(g->sys, 5) + 1, 0);
                        break;
                    case 9:
                        break;
                    }
                }
                func_5104F0(1);
                StateVarSet_3cc9c0(g->sys, 6, 0, 0);
                func_50D7A0(e, 11, 0, -1);
            } else {
                StateVarSet_3cc9c0(g->sys, 7, StateVarGet_3ccac0(g->sys, 7) + 1, 0);
                switch (StateVarGet_3ccac0(g->sys, 0x7F)) {
                case 0:
                    func_50D7A0(e, 11, 0, -1);
                    break;
                case 1:
                    func_50DAD0(e, 0x4D);
                    InsectBattleReset_31a700();
                    InsectBattleReinit_31a5b0();
                    return 0;
                }
            }
            break;
        case 11:
            func_50DA90(e, 0x3E);
            return 1;
        }
    } else {
    switch (func_50D6A0(e, 0)) {
    case 1:
        StateVarSet_3cc9c0(g->sys, 11, 0, 0);
        SoundBankFree_1b9c00(5);
        GameReqPushWarp_285ea0(-1, 0x1F5, *(s16 *)(g->cfg + 6), 0);
        func_50D7A0(e, 10, 0, -1);
        break;
    case 10:
        func_5104F0(0);
        StateVarSet_3cc9c0(g->sys, 7, 0, 0);
        StateVarSet_3cc9c0(g->sys, 6, 0, 0);
        func_50D7A0(e, 11, 0, -1);
        break;
    case 11:
        return 1;
    }
    }
    }
    return 0;
}
#ifdef __cplusplus
}
#endif
