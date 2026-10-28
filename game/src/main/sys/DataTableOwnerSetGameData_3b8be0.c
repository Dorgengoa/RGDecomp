/* rgp:protos */
#define RGP_SELF_DataTableOwnerSetGameData_3b8be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S003B8BE0_src {
    u8 pad0[0x8];
    s32 f8;                   /* +0x8 */
} S003B8BE0_src;

typedef struct S003B8BE0_dst {
    u8 pad0[0x94];
    S003B8BE0_src *f94;       /* +0x94 */
} S003B8BE0_dst;

typedef struct S003B8BE0 {
    u8 pad0[0x4];
    S003B8BE0_src *f4;        /* +0x4 */
    s32 f8;                   /* +0x8 */
    S003B8BE0_dst *fC;        /* +0xC */
} S003B8BE0;

s32 DataTableOwnerSetGameData_3b8be0(S003B8BE0 *self, S003B8BE0_src *p)
{
    if (p == 0) {
        return 0;
    }
    self->f4 = p;
    self->f8 = p->f8;
    self->fC->f94 = self->f4;
    return 1;
}
