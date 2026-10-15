#include "types.h"
typedef struct T00142d90 {
    s32 f0;
    u8 pad04[0x4];
    s32 f8;
    s32 fC;
} T00142d90;

typedef struct S00142d90 {
    u8 pad[0xF20];
    T00142d90 *fF20;
} S00142d90;

void CameraRecSetFieldByIndexMaybe_142d90(S00142d90 *s, u8 k, s32 v)
{
    T00142d90 *p;

    p = s->fF20;
    switch (k) {
    case 0:
        p->f0 = v;
        break;
    case 1:
        p->f8 = v;
        break;
    case 2:
        p->fC = v;
        break;
    }
}
