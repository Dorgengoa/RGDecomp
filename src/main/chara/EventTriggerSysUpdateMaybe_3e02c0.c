#include "types.h"

typedef struct Fx {
    s16 id;
    u8 pad02[0x2C];
    s16 x2E;
    u8 pad30[0x10];
    u8 flags;
    u8 pad41[3];
    f32 time;
} Fx;

typedef struct Timer {
    s16 id;
    u8 pad02[6];
    f32 time;
    f32 t0;
    f32 t1;
    f32 t2;
} Timer;

typedef struct Clock {
    u8 pad[8];
    s64 x8;
} Clock;

typedef struct PartyA {
    u8 pad[0x1A4];
    u8 x1A4;
} PartyA;

typedef struct PartyB {
    u8 pad[0x24C];
    u8 x24C;
} PartyB;

typedef struct Game {
    u8 pad00[0xC];
    Clock *clock;
    u8 pad10[8];
    PartyA *party;
    u8 pad1C[4];
    PartyB *mode;
} Game;

typedef struct Ctx {
    u8 b[0x30];
} Ctx;

extern Game *D_00483990;
extern s32 D_0048399C;
extern s16 D_004839AC;
extern Fx D_004E9770[2];
extern Timer D_004E9800[64];
extern f32 D_0045B078[0x100];

extern s32 GetGameMode_1f59c0(void);
extern void EventRunPendingTriggerAction_3e0630(void);
extern void SkillActionReset_3e3dd0(Fx *p);
extern void SkillTimerReset_3e3d20(Timer *p);
extern s32 DoubleToU64_13ab28(s64 t);
extern s32 FloatToU64_13acb8(f32 f);
extern s16 UModDi3_13a430(s32 a, s32 b);
extern s32 GetCurrentScene_1f5be0(void);
extern void ActionPacketReset_3e3d00(Ctx *c);
extern void ActionPacketInitTickMaybe_3e2b90(Ctx *c, s32 who, s32 kind);
extern void EventFireTriggers_3e2660(Ctx *c, s32 x);
extern s32 PartyCountMembers_3c2010(PartyA *p, s32 a, s32 b);
extern s32 PartyGetLeaderChara_3c2820(PartyA *p);
extern s32 PartyGetNonLeaderChara_3c2700(PartyA *p, s32 i);
extern s32 SkillTriggerEvalMaybe_3e1200(Ctx *c, s32 e);

void EventTriggerSysUpdateMaybe_3e02c0(f32 dt) {
    s32 list[4];
    Ctx ctx;
    Fx *p;
    Timer *q;
    s32 i;
    s32 t;
    s16 lv;
    s32 who;
    s32 j;
    s32 n;
    s32 e;

    if (D_00483990 == 0) {
        return;
    }
    if (GetGameMode_1f59c0() == 6 && D_0048399C != 0) {
        EventRunPendingTriggerAction_3e0630();
    }
    p = D_004E9770;
    for (i = 0; i < 2; i++, p++) {
        if (p->id < 0) {
            continue;
        }
        if (p->flags & 1) {
            continue;
        }
        p->time += dt;
        if (p->time < (f32)p->x2E) {
            continue;
        }
        SkillActionReset_3e3dd0(p);
    }
    q = D_004E9800;
    for (i = 0; i < 64; i++, q++) {
        if (q->id < 0) {
            continue;
        }
        q->time += dt;
        if (q->time < q->t0) {
            continue;
        }
        if (q->time < q->t1) {
            continue;
        }
        if (q->time < q->t2) {
            continue;
        }
        SkillTimerReset_3e3d20(q);
    }
    t = DoubleToU64_13ab28(D_00483990->clock->x8);
    lv = UModDi3_13a430(t, FloatToU64_13acb8(D_0045B078[0]));
    if (lv == 0 || lv < D_004839AC) {
        who = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&ctx);
        if (D_00483990->mode->x24C & 1) {
            ActionPacketInitTickMaybe_3e2b90(&ctx, who, 0x39);
            EventFireTriggers_3e2660(&ctx, 0);
        } else if (D_00483990->party->x1A4 & 1) {
            ActionPacketInitTickMaybe_3e2b90(&ctx, who, 0x3A);
            EventFireTriggers_3e2660(&ctx, 0);
        } else {
            ActionPacketInitTickMaybe_3e2b90(&ctx, who, 0x38);
            EventFireTriggers_3e2660(&ctx, 0);
        }
        t = PartyCountMembers_3c2010(D_00483990->party, 1, 1);
        n = t;
        list[0] = PartyGetLeaderChara_3c2820(D_00483990->party);
        for (i = 1; i < n; i++) {
            list[i] = PartyGetNonLeaderChara_3c2700(D_00483990->party, i - 1);
        }
        for (j = 0; j < n; j++) {
            e = list[j];
            if (e == 0) {
                continue;
            }
            if (D_00483990->mode->x24C & 1) {
                ActionPacketInitTickMaybe_3e2b90(&ctx, who, 0x39);
                if ((u8)SkillTriggerEvalMaybe_3e1200(&ctx, e)) {
                    break;
                }
            } else if (D_00483990->party->x1A4 & 1) {
                ActionPacketInitTickMaybe_3e2b90(&ctx, who, 0x3A);
                if ((u8)SkillTriggerEvalMaybe_3e1200(&ctx, e)) {
                    break;
                }
            } else {
                ActionPacketInitTickMaybe_3e2b90(&ctx, who, 0x38);
                if ((u8)SkillTriggerEvalMaybe_3e1200(&ctx, e)) {
                    break;
                }
            }
        }
    }
    D_004839AC = lv;
}
