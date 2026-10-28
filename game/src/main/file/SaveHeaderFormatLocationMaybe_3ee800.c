/* rgp:protos */
#define RGP_SELF_SaveHeaderFormatLocationMaybe_3ee800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 v[6];
} T6;

typedef struct {
    s32 v[9];
} T9;

typedef struct {
    u8 pad0[0x33A];
    s16 x33A;
    s16 x33C;
    s16 x33E;
} Obj;

extern char *strcpy(char *, const char *);
/*rgp*/
extern s32 Sprintf_1343b8(char *, const char *, ...);
extern s32 D_00454710[6];
extern s32 D_00454730[9];

s32 SaveHeaderFormatLocationMaybe_3ee800(Obj *p, char *buf)
{
    T6 b __attribute__((aligned(16)));
    T9 a __attribute__((aligned(16)));
    char *s1;
    char *s2;
    char *s3;
    s16 k;

    b = *(T6 *)D_00454710;
    a = *(T9 *)D_00454730;
    s1 = ((char *)MsgGetTextByIndex_279040(0x29));
    s2 = ((char *)MsgGetTextByIndex_279040(0x2A));
    s3 = ((char *)MsgGetTextByIndex_279040(0x2B));
    k = p->x33A;
    if (k == 0) {
        strcpy(buf, s1);
    } else if (k >= 7) {
        Sprintf_1343b8(buf, s2, a.v[6]);
    } else if (k == p->x33C && p->x33E > 0) {
        Sprintf_1343b8(buf, s3, a.v[k], b.v[p->x33E + 1]);
    } else if (k >= 2) {
        Sprintf_1343b8(buf, s2, a.v[k - 1]);
    } else {
        Sprintf_1343b8(buf, s3, a.v[1], b.v[1]);
    }
    return 1;
}
