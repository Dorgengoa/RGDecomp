#include "types.h"

extern void SoundPlayDefault_1b9ae0(s32, s32, s32);

typedef struct {
    s32 h;
    s8 f4;
    s8 f5;
} T;

void InsectCageSePlay_3844b0(T *arg0, s32 arg1) {
    if (arg1 == 0) {
        if (arg0->f4 == 0) {
            SoundPlayDefault_1b9ae0(arg0->h, 0, 0);
            arg0->f4 = 1;
        }
    } else if (arg1 == 2) {
        if (arg0->f5 == 0) {
            SoundPlayDefault_1b9ae0(arg0->h, 2, 0);
            arg0->f5 = 1;
        }
    } else {
        SoundPlayDefault_1b9ae0(arg0->h, arg1, 0);
    }
}
