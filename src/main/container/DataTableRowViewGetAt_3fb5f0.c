#include "types.h"

typedef struct E_003FB5F0 {
    u8 pad000[0x14];
} E_003FB5F0;

typedef struct Obj_003FB5F0 {
    u8 pad000[0x9];
    s8 count : 6;
    s8 hi : 2;
    u8 pad00A[0x2];
    E_003FB5F0 *base;
} Obj_003FB5F0;

E_003FB5F0 *DataTableRowViewGetAt_3fb5f0(Obj_003FB5F0 *o, s32 n)
{
    if (n >= 0) {
        if (n < o->count) {
            return &o->base[n];
        }
    }
    return 0;
}
