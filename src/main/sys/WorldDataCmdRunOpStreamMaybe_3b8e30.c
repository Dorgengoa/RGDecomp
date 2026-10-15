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
extern s32  SlotGetInt_15f720(R8 *q);
extern s32  Base64Decode_36a700(void *buf, s32 h);
extern void VariantInit_36ff00(Elem *e);
extern void VariantPoolReset_3e01f0(Lst *l);
extern void ScriptExecOpStream_3dffa0(Lst *l, s32 n, void *buf, s32 d);

s32 WorldDataCmdRunOpStreamMaybe_3b8e30(R8 *a)
{
    Pool *p = D_004830F8;
    u8  buf[0x2000];
    Lst l;
    s32 n;
    Elem *q;

    if (!p->b2) return 1;
    n = Base64Decode_36a700(buf, SlotGetInt_15f720(a));
    if (n > 0) {
        q = l.e;
        do {
            VariantInit_36ff00(q);
            q++;
        } while (q < l.e + 64);
        VariantPoolReset_3e01f0(&l);
        ScriptExecOpStream_3dffa0(&l, n, buf, 0);
    }
    return 1;
}
