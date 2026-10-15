#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[0xF8 - 6];
    s16 unkF8;
} Sub;

typedef struct {
    u8 pad0[8];
    s64 unk8;
} C;

typedef struct {
    u8 pad0[0xC];
    C *unkC;
    u8 pad10[8];
    Sub *unk18;
} A;

extern f64 U64ToDouble_100370(f64);
extern f64 DoubleToU64_13ab28(s64);
extern void InvPurgeRemoved_3c8cc0(Sub *);
extern void InvFreeCategory8Items_3c8d70(Sub *);
extern void PartySetAreaTimeStampMaybe_3c9810(Sub *, s32, f64);
extern void PartySetAreaMaybe_3cab50(Sub *, s32, s32, s32);
extern void GameDataFlagsSetOrClear_3e4580(A *, s32, s32);
extern s32 SaveDataDeserialize_3e5c30(A *, s32, s32, void *);
extern void ReqListResetWithFlagMaybe_3ee640(void *, s32);
extern void ReqListResetMaybe_3ee6b0(void *);
extern void ReqEntryInit_3ee700(void *);

s32 GameDataDeserialize_3e5fe0(A *arg0, s32 arg1, s32 arg2)
{
    struct { u8 sp50[8]; u8 arr[6][0xC]; } L;
    u8 *q;
    s32 r;
    Sub *s;
    s16 k;
    f64 d;

    GameDataFlagsSetOrClear_3e4580(arg0, 1, 0);
    q = L.arr[0];
    do {
        ReqEntryInit_3ee700(q);
        q += 0xC;
    } while (q < L.arr[6]);
    ReqListResetMaybe_3ee6b0(L.sp50);
    ReqListResetWithFlagMaybe_3ee640(L.sp50, 1);
    r = SaveDataDeserialize_3e5c30(arg0, arg1, arg2, L.sp50);
    if (r <= 0) {
        return 0;
    }
    GameDataFlagsSetOrClear_3e4580(arg0, 1, 1);
    s = arg0->unk18;
    PartySetAreaMaybe_3cab50(s, s->unk4, 1, 0);
    InvFreeCategory8Items_3c8d70(arg0->unk18);
    InvPurgeRemoved_3c8cc0(arg0->unk18);
    s = arg0->unk18;
    d = -1.0;
    k = s->unkF8;
    if (k >= 0) {
        d = U64ToDouble_100370(DoubleToU64_13ab28(arg0->unkC->unk8));
    }
    PartySetAreaTimeStampMaybe_3c9810(s, k, d);
    return r;
}
