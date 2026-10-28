/* rgp:protos */
#define RGP_SELF_InvFindByInvId_3c87d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x168];
    s32 unk168;
} Obj003c87d0;

typedef struct {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
} __attribute__((aligned(4))) Elem0036acb0;

/*rgp*/
extern u8 D_00465B50[0x400];

void *InvFindByInvId_3c87d0(Obj003c87d0 *arg0, s32 arg1, s32 arg2)
{
    Elem0036acb0 *r;
    s32 n;
    s32 i;
    Elem0036acb0 *e;

    if (arg1 < 0) {
        return NULL;
    }
    if (arg0->unk168 == 0) {
        return NULL;
    }
    r = NULL;
    n = *(s32 *)D_00465B50;
    for (i = 0; i < n; i++) {
        e = ((Elem0036acb0 *)PoolGetUsedElem_36acb0(arg0->unk168, i));
        if ((e != NULL) && ((arg2 != 0) || (e->b1 == 0)) && (arg1 == e->unk6)) {
            r = e;
            break;
        }
    }
    return r;
}
