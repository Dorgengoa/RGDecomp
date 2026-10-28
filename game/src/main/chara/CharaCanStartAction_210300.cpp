#include "types.h"

typedef struct O {
    u8 pad0[0xA2E];
    s16 a2e;
    u8 pad30[2];
    s16 a32;
    u8 pad34[2];
    s16 a36;
    s16 a38;
    u8 pad3a[0xB4C - 0xA3A];
    s16 b4c;
    u8 pad4e[2];
    s16 b50;
} O;

extern "C" s32 CharaCanStartAction_210300(O *p);

s32 CharaCanStartAction_210300(O *p)
{
    s32 a;
    s32 r;
    bool flag;
    switch (p->a36) {
    case 15:
    case 19:
    case 30:
    case 31:
        return 0;
    }
    if (p->a38 == 0) {
        switch (p->a32) {
        case 10:
        case 18:
            return 0;
        }
    }
    a = p->a2e;
    flag = 1; if (a != 2 && a != 3) flag = 0;
    if (!flag) {
        switch (p->b4c) {
        case 1:
        case 2:
            return 0;
        }
    }
    { s32 b = a == 2; if (!b) b = a == 3; if (b == 0) goto one;
    switch (p->b50) {
    case 2:
    case 3:
        return 0;
    }
    one: ;}

    return 1;
}
