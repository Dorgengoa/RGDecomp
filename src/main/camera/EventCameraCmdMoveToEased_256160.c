#include "types.h"

typedef f32 Vec[4] __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0x10];
    Vec p0;
    Vec p1;
    s32 frames;
    s32 mode;
    f32 ratio;
} Src;

typedef struct {
    u8 pad0[0x38];
    s32 count;
    u8 pad3c[0x50 - 0x3C];
    Vec pos0;
    Vec pos1;
    u8 pad70[0xD0 - 0x70];
    Vec vel0;
    Vec vel1;
    u8 padf0[0x100 - 0xF0];
    Vec cur0;
    Vec cur1;
    Vec acc0;
    Vec acc1;
    s32 total;
} Dst;

extern void VecAdd_13be20(f32 *, f32 *, f32 *);
extern void VecSub_13be40(f32 *, f32 *, f32 *);
extern void sceVu0CopyVector(f32 *, f32 *);
extern void sceVu0DivVector(f32 *, f32 *, f32);

s32 EventCameraCmdMoveToEased_256160(Src *a, Dst *b) {
    Vec d0;
    Vec d1;
    s32 mode;
    s32 n;
    s32 half;
    s32 cnt;
    s32 done;

    mode = a->mode;
    if (mode == 0) {
        half = b->total;
    } else {
        half = b->total / 2;
    }
    cnt = b->count;
    if (cnt >= a->frames + half) {
        b->count = 0;
        return 0;
    }
    if (cnt <= 0) {
        VecSub_13be40(d0, a->p0, b->pos0);
        sceVu0DivVector(b->vel0, d0, (f32)a->frames);
        b->vel0[3] = 1.0f;
        VecSub_13be40(d1, a->p1, b->pos1);
        sceVu0DivVector(b->vel1, d1, (f32)a->frames);
        b->vel1[3] = 1.0f;
        b->total = (f32)a->frames * a->ratio;
        sceVu0CopyVector(b->acc0, b->vel0);
        sceVu0CopyVector(b->acc1, b->vel1);
        sceVu0DivVector(b->acc0, b->acc0, (f32)b->total);
        sceVu0DivVector(b->acc1, b->acc1, (f32)b->total);
        if (a->mode != 2) {
            sceVu0CopyVector(b->cur0, b->acc0);
            sceVu0CopyVector(b->cur1, b->acc1);
        } else {
            sceVu0CopyVector(b->cur0, b->vel0);
            sceVu0CopyVector(b->cur1, b->vel1);
        }
    } else {
        done = 0;
        if (cnt < b->total) {
            if (mode == 0) goto doit;
            if (mode == 1) {
            doit:
            VecAdd_13be20(b->cur0, b->cur0, b->acc0);
            VecAdd_13be20(b->cur1, b->cur1, b->acc1);
            VecAdd_13be20(b->pos0, b->pos0, b->cur0);
            b->pos0[3] = 1.0f;
            VecAdd_13be20(b->pos1, b->pos1, b->cur1);
            done = 1;
            b->pos1[3] = 1.0f;
            }
        }
        if ((a->mode == 2 && b->count >= a->frames - b->total / 2) ||
            (a->mode == 0 && b->count >= a->frames)) {
            VecSub_13be40(b->cur0, b->cur0, b->acc0);
            VecSub_13be40(b->cur1, b->cur1, b->acc1);
            VecAdd_13be20(b->pos0, b->pos0, b->cur0);
            b->pos0[3] = 1.0f;
            VecAdd_13be20(b->pos1, b->pos1, b->cur1);
            done = 1;
            b->pos1[3] = 1.0f;
        }
        if (done == 0) {
            VecAdd_13be20(b->pos0, b->pos0, b->vel0);
            b->pos0[3] = 1.0f;
            VecAdd_13be20(b->pos1, b->pos1, b->vel1);
            b->pos1[3] = 1.0f;
        }
    }
    b->count++;
    return 1;
}
