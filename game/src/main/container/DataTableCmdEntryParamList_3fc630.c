/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryParamList_3fc630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef union V { s32 i; f32 f; } V;

typedef struct It {
    s16 f000;
    s16 f002;
    V   f004;
} It;

typedef struct Ent {
    u8  pad000[0x10];
    s16 f010;
    u8  pad012[0x2];
    It *f014;
    u8  pad018[0x8];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdEntryParamList_3fc630(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    It  *q;
    s32  k;
    s32  t0;
    s32  a;
    s32  b;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src++);
    e->f010 = t0;
    if ((s16)t0 > 0) e->f014 = ((It *)ArenaNew_3fca20((s16)t0 * 0x8, p->m6C, 0x4, -1));
    else e->f014 = 0;
    for (k = 0; k < e->f010; k++) {
        q = &e->f014[k];
        a = VariantGetInt_15f780(src++);
        b = VariantGetInt_15f780(src++);
        q->f000 = a;
        switch (b) {
        case 1:
            q->f002 = b;
            q->f004.i = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
            break;
        case 2:
            q->f002 = b;
            q->f004.i = VariantGetInt_15f780(src++);
            break;
        case 3:
            q->f002 = b;
            q->f004.f = (f32)VariantGetInt_15f780(src++);
            break;
        default:
            q->f002 = -1;
            break;
        }
    }
    return 1;
}
