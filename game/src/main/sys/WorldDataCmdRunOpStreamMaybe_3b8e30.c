/* rgp:protos */
#define RGP_SELF_WorldDataCmdRunOpStreamMaybe_3b8e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Elem { u8 b[0x38]; } Elem;

typedef struct Lst {
    u8   pad000[0x8];
    Elem e[64];
} Lst;

typedef struct Pool {
    u8    pad000[0x9A];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
} Pool;

extern Pool *D_004830F8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldDataCmdRunOpStreamMaybe_3b8e30(R8 *a)
{
    Pool *p = D_004830F8;
    u8  buf[0x2000] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Lst)]; char m1[0xe0d]; })];
    s32 n;
    Elem *q;

    if (!p->b2) return 1;
    n = Base64Decode_36a700(buf, SlotGetInt_15f720(a));
    if (n > 0) {
        q = (*(Lst *)(rgp_blk1 + 0x0)).e;
        do {
            VariantInit_36ff00(q);
            q++;
        } while (q < (*(Lst *)(rgp_blk1 + 0x0)).e + 64);
        VariantPoolReset_3e01f0(&(*(Lst *)(rgp_blk1 + 0x0)));
        ScriptExecOpStream_3dffa0(&(*(Lst *)(rgp_blk1 + 0x0)), n, buf, 0);
    }
    return 1;
}
