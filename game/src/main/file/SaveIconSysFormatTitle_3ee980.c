/* rgp:protos */
#define RGP_SELF_SaveIconSysFormatTitle_3ee980 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 id;
    u8 pad12[2];
    s16 val;
    u8 pad16[0x28 - 0x16];
} Ent;

typedef struct {
    s16 unk0;
    u8 pad2[0x50 - 0x2];
    u8 clock[0x10];
    s16 count;
    u8 pad62[2];
    Ent ents[1];
} Obj;

typedef struct {
    s32 d[10];
} Tbl;

extern s32 Sprintf_1343b8();
/*rgp*/
/*rgp*/
extern s32 strlen(s8 *);
extern u8 D_004546E0[40];

s32 SaveIconSysFormatTitle_3ee980(Obj *arg0, s8 *arg1, s32 *arg2, s32 *arg3)
{
    s32 h;
    s32 m;
    s32 s;
    s32 f;
    Tbl t __attribute__((aligned(16)));
    s32 v;
    Ent *e;
    s32 i;
    s32 fmt1;
    s32 fmt2;
    s32 n;
    s8 *p;

    if (arg1 == NULL) {
        return 0;
    }
    SavePlayTimeSplit_3eebf0(arg0->clock, &h, &m, &s, &f);
    if (h > 0x63) {
        h = 0x63;
        m = 0x3B;
    }
    v = *(s16 *)((u8 *)arg0 + 0x78);
    e = arg0->ents;
    for (i = 0; i < arg0->count; i++, e++) {
        if (e->id == 0x2AF9) {
            v = e->val;
            break;
        }
    }
    *arg1 = 0;
    t = *(Tbl *)D_004546E0;
    fmt1 = MsgGetTextByIndex_279040(0x27);
    fmt2 = MsgGetTextByIndex_279040(0x28);
    n = arg0->unk0 + 1;
    p = &arg1[Sprintf_1343b8(arg1, fmt1, t.d[n / 10 % 10], t.d[n % 10])];
    *arg2 = strlen(arg1);
    Sprintf_1343b8(p, fmt2, t.d[v / 10 % 10], t.d[v % 10], t.d[h / 10 % 10], t.d[h % 10], t.d[m / 10 % 10], t.d[m % 10]);
    *arg3 = strlen(p);
    return 1;
}
