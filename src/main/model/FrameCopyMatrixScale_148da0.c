#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8   pad00[0x1C];
    Vec4 *unk1C;
    u8   pad20[0x09];
    u8   unk29;
    u8   pad2A;
    u8   unk2B;
    u8   unk2C;
    u8   pad2D[0x23];
    Vec4 unk50;
    Vec4 unk60;
    Vec4 unk70;
    Vec4 unk80;
    Vec4 unk90;
} Obj;

void FrameCopyMatrixScale_148da0(Obj *arg0, Obj *arg1)
{
    Vec4 *d;
    Vec4 *s;

    if (arg0->unk1C != NULL) {
        arg1->unk60 = arg0->unk60;
        arg1->unk70 = arg0->unk70;
        arg1->unk80 = arg0->unk80;
        arg1->unk90 = arg0->unk90;
        arg1->unk29 = 1;
        d = arg1->unk1C;
        s = arg0->unk1C;
        if (d == NULL) {
            if (1.0f != s->x || 1.0f != s->y || 1.0f != s->z) {
                arg1->unk1C = &arg1->unk50;
                arg1->unk2B = 1;
                arg1->unk29 = 1;
                arg1->unk2C = 0;
                *(u128 *)arg1->unk1C = *(u128 *)s;
                arg1->unk29 = 1;
            }
        } else {
            if (d->x != s->x || d->y != s->y || d->z != s->z) {
                *(u128 *)d = *(u128 *)s;
                arg1->unk29 = 1;
            }
        }
    } else {
        arg1->unk60 = arg0->unk60;
        arg1->unk70 = arg0->unk70;
        arg1->unk80 = arg0->unk80;
        arg1->unk90 = arg0->unk90;
        arg1->unk29 = 1;
    }
}
