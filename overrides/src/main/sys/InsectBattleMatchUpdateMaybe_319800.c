/* rg-override: replaces game/src/main/sys/InsectBattleMatchUpdateMaybe_319800.c sha256 8e41cb942fe8bce0a4a5b95b8987d036f3debde5de3c8e4b0a437b7b5be76bbb
 * why: the stage dropped the key argument of InsectronRewardLookupMaybe_3e84f0 and zeroed its value (void definition; retail returns the slot-0x70 record), so a story Insectron rank reward was never granted */
/* rgp:protos */
#define RGP_SELF_InsectBattleMatchUpdateMaybe_319800 1
#define RGP_SELF_InsectronRewardLookupMaybe_3e84f0 1
#define RGP_SELF_ge 1
#define RGP_SELF_lt 1
#include "port/game_protos.h"
/* real signature (asm 003E84F0, override): key in $a1, returns the slot-0x70 record */
void *InsectronRewardLookupMaybe_3e84f0(void *, int);
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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

    g = ((Game *)GetGameData_1fede0());
    e = ((u8 *)InsectBattleGet_31a8d0());
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
            a = ((short)StateVarGet_3ccac0(g->sys, 5));
            if (((short)StateVarGet_3ccac0(g->sys, 7)) >= 4) {
                k = -1;
                if (((short)StateVarGet_3ccac0(g->sys, 6)) >= a) {
                    k = 0;
                } else if (((short)StateVarGet_3ccac0(g->sys, 6)) >= 6) {
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
                    t = (s16 *)InsectronRewardLookupMaybe_3e84f0(g, *(s16 *)(e + 0x5EFC));
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
            a = ((short)StateVarGet_3ccac0(g->sys, 5));
            if (((short)StateVarGet_3ccac0(g->sys, 7)) >= 4) {
                StateVarSet_3cc9c0(g->sys, 7, 0, 0);
                if (((short)StateVarGet_3ccac0(g->sys, 6)) >= a) {
                    StateVarSet_3cc9c0(g->sys, 5, ((short)StateVarGet_3ccac0(g->sys, 6)) + 1, 0);
                } else if (((short)StateVarGet_3ccac0(g->sys, 6)) >= 6) {
                    switch (a) {
                    case 7:
                        StateVarSet_3cc9c0(g->sys, 5, ((short)StateVarGet_3ccac0(g->sys, 5)) + 1, 0);
                        break;
                    case 8:
                        StateVarSet_3cc9c0(g->sys, 5, ((short)StateVarGet_3ccac0(g->sys, 5)) + 1, 0);
                        break;
                    case 9:
                        break;
                    }
                }
                func_5104F0(1);
                StateVarSet_3cc9c0(g->sys, 6, 0, 0);
                func_50D7A0(e, 11, 0, -1);
            } else {
                StateVarSet_3cc9c0(g->sys, 7, ((short)StateVarGet_3ccac0(g->sys, 7)) + 1, 0);
                switch (((short)StateVarGet_3ccac0(g->sys, 0x7F))) {
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
