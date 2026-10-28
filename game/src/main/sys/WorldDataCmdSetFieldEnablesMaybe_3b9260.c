/* rgp:protos */
#define RGP_SELF_WorldDataCmdSetFieldEnablesMaybe_3b9260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Obj {
    u8  pad000[0x4];
    u8  b0 : 1;
    u8  b1 : 7;
} Obj;

typedef struct Node {
    u8   pad000[0x20];
    Obj *m20;
} Node;

typedef struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
} Pool;

extern Pool *D_004830F8;
extern u8    D_00483998;
extern u8    D_004839A0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldDataCmdSetFieldEnablesMaybe_3b9260(R8 *a)
{
    Pool *p = D_004830F8;
    Obj *q;

    if (!p->b2) return 1;
    if (VariantGetInt_15f780(a++) != 0) {
        q = p->m94->m20;
        q->b0 = 1;
        CharaSysEncounterDistRoll_3a59d0(q, 1);
    } else {
        p->m94->m20->b0 = 0;
    }
    if (VariantGetInt_15f780(a++) != 0) D_00483998 = 1; else D_00483998 = 0;
    if (VariantGetInt_15f780(a++) != 0) D_004839A0 = 1; else D_004839A0 = 0;
    if (VariantGetInt_15f780(a) != 0) {
        CharaSysFlag4Bit1SetRelated_3a5300(p->m94->m20);
        D_00483998 = 1;
    } else {
        CharaSysFlag4Bit1SetArg0Related_3a5310(p->m94->m20);
    }
    SoundCmdNopRelated_207eb0();
    return 1;
}
