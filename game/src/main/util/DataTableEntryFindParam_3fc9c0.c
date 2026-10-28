/* rgp:protos */
#define RGP_SELF_DataTableEntryFindParam_3fc9c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_003fc9c0 {
    s16 f0;
    u8 pad2[6];
} E_003fc9c0;

typedef struct S_003fc9c0 {
    u8 pad0[0x10];
    s16 f10;
    u8 pad12[2];
    E_003fc9c0 *f14;
} S_003fc9c0;

E_003fc9c0 *DataTableEntryFindParam_3fc9c0(S_003fc9c0 *self, s32 key)
{
    s32 n = self->f10;
    E_003fc9c0 *p;
    s32 j;
    s32 v;
    if (n <= 0) goto zero;
    p = self->f14;
    if (p != 0) goto ok;
zero:
    return 0;
ok:
    j = 0;
    while (j < n) {
        v = p->f0;
        if (v == key) return p;
        if (key < v) return 0;
        j++;
        p++;
    }
    return 0;
}
