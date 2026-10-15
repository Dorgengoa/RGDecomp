#include "types.h"

typedef struct E_004049A0 {
    u8 pad000[0xC];
} E_004049A0;

typedef struct Obj_004049A0 {
    u8 pad000[0x16];
    s8 count : 4;
    s8 hi : 4;
    u8 pad017[0x1];
    E_004049A0 *base;
} Obj_004049A0;

E_004049A0 *DataTableRowViewGetAt_4049a0(Obj_004049A0 *o, s32 n)
{
    if (n >= 0) {
        if (n < o->count) {
            return &o->base[n];
        }
    }
    return 0;
}
