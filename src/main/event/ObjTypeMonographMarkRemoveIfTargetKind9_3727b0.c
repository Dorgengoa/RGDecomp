#include "types.h"

typedef struct Sub3727 {
    u8 pad000[0x4];
} Sub3727;

typedef struct S3727 {
    u8       pad000[0xA0];
    Sub3727  mA0;
    u8       pad0A4[0xD0 - 0xA4];
    s32      mD0;
} S3727;

extern s32 TargetRefGetKind_2e7130(Sub3727 *p);
extern s32 TargetRefGetId_2e7120(Sub3727 *p);

void ObjTypeMonographMarkRemoveIfTargetKind9_3727b0(S3727 *p, s32 q)
{
    if (TargetRefGetKind_2e7130(&p->mA0) == 0x9) {
        if (q == TargetRefGetId_2e7120(&p->mA0)) {
            p->mD0 |= 0x1000000;
        }
    }
}
