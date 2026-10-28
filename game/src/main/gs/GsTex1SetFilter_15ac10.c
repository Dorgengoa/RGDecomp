/* rgp:protos */
#define RGP_SELF_GsTex1SetFilter_15ac10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x40];
    __extension__ unsigned short f0 : 2;
    unsigned short a : 3;
    unsigned short b : 1;
    unsigned short c : 3;
} __attribute__((aligned(2))) S;

void GsTex1SetFilter_15ac10(S *p, s32 arg1)
{
    if (p->a == 0) {
        switch (arg1) {
        case 0:
            p->b = 0;
            p->c = 0;
            break;
        case 1:
        case 2:
            p->b = 1;
            p->c = 1;
            break;
        }
    } else {
        switch (arg1) {
        case 0:
            p->b = 0;
            p->c = 2;
            break;
        case 1:
            p->b = 1;
            p->c = 4;
            case 2:
            p->b = 1;
            p->c = 5;
            break;
        }
    }
}
