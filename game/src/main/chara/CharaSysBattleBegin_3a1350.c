/* rgp:protos */
#define RGP_SELF_CharaSysBattleBegin_3a1350 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct {
    u8 pad0[0x8];
    s64 unk8;
} ObjC;

typedef struct {
    u8 pad0[0x180];
    s64 unk180;
} Obj238;

typedef struct {
    u8 pad0[0x4];
    u8 g0:2;
    u8 g2:1;
    u8 g3:5;
    u8 pad5[0x238 - 0x5];
    Obj238 *unk238;
    u8 pad23C[0x24C - 0x23C];
    u8 f0:1;
    u8 f1:1;
    u8 f2:1;
    u8 f3:1;
    u8 f4:4;
} Obj;

typedef struct {
    u8 pad0[0xC];
    ObjC *unkC;
} ObjG;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern ObjG *D_004837C0;

s32 CharaSysBattleBegin_3a1350(Obj *arg0)
{
    s32 v;

    if (D_004837C0 == NULL) {
        return 0;
    }
    if (arg0->f0) {
        return 0;
    }
    arg0->f0 = 1;
    arg0->f2 = 1;
    arg0->f3 = 1;
    if (arg0->unk238 != NULL) {
        CharaStateReset_3a79b0(arg0->unk238, 0, 0, 0, 1);
        arg0->unk238->unk180 = DoubleToU64_13ab28(__builtin_bit_cast(double, (long long)(D_004837C0->unkC->unk8)));
    }
    arg0->f1 = 0;
    arg0->g2 = 0;
    CharaSysClearTable23C_3a3630(arg0);
    CharaSysBattleResultReset_3a31b0(arg0);
    CharaSysEventLogReset_3a33e0(arg0);
    return 1;
}
