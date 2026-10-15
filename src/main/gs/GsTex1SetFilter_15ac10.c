#include "types.h"

typedef struct {
    u8 pad0[0x40];
    u16 f0 : 2;
    u16 a : 3;
    u16 b : 1;
    u16 c : 3;
} S;

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
