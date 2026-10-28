#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"
#include "vec.h"

/* The camera parameter block: ten floats, saved to and restored from +0x130.
   Copied a float at a time rather than as a struct -- see the note in
   src/camera/CameraSaveParams_1601b0.c. */
typedef struct CamParams {
    f32 a, b, c, d, e, f, g, h, i, j;
    s32 k;      /* +0x28, an int, not a float */
} CamParams;

struct Camera;

typedef struct CameraVtbl {
    u8 pad00[0x10];
    f32 (*getAngle)(struct Camera *);                 /* +0x10, degrees */
    void (*setAngle)(struct Camera *, f32 degrees);   /* +0x14 */
    u8 pad18[0x4];
    void (*setMatrix)(struct Camera *, const Mtx4 *); /* +0x1C */
    /* +0x20: takes the chase float from +0x70 and the two transformed
       vectors CameraApplyLookAt_1773d0's helper builds. Named from CameraBaseApplyLookAt_15fa80,
       which is the only caller in scope. */
    void (*upload)(struct Camera *, f32 t, const Vec4 *a, const Vec4 *b);
    u8 pad24[0x4];
    void (*setPos)(struct Camera *, const Vec4 *);    /* +0x28 */
    u8 pad2c[0x4];
    void (*finish)(struct Camera *);                 /* +0x30 */
    u8 pad34[0xC];
    void (*toView)(struct Camera *);                 /* +0x40, vm40 */
    u8 pad44[0x4];
    CamParams *(*getParams)(struct Camera *);        /* +0x48 */
    u8 pad4c[0xC];
    void (*commit)(struct Camera *);                 /* +0x58 */
    void (*apply)(struct Camera *);                  /* +0x5C */
    u8 pad60[0x4];
    void (*retarget)(struct Camera *, f32 t);        /* +0x64 */
    u8 pad68[0x8];
    void (*preFrame)(struct Camera *);               /* +0x70 -> unused so far */
    u8 pad74[0x20];
    void (*getBoomA)(struct Camera *, Vec4 *);       /* +0x94 */
    void (*getBoomB)(struct Camera *, Vec4 *);       /* +0x98 */
    void (*getEye)(struct Camera *, Vec4 *);         /* +0x9C */
    void (*getAt)(struct Camera *, Vec4 *);          /* +0xA0 */
    void (*getEyeLocal)(struct Camera *, Vec4 *);    /* +0xA4 */
    void (*getAtLocal)(struct Camera *, Vec4 *);     /* +0xA8 */
    u8 padac[0x4];
    void (*setEye)(struct Camera *, const Vec4 *);   /* +0xB0 */
    void (*setAt)(struct Camera *, const Vec4 *);    /* +0xB4 */
} CameraVtbl;

typedef struct Camera {
    u8 pad000[0x50];
    Vec4 eyeNow;         /* +0x50, chases eye */
    Vec4 atNow;          /* +0x60, chases at */
    f32 unk70;           /* +0x70 */
    u8 pad074[0xC];
    Mtx4 xform;          /* +0x80, 0x40 bytes -- ends exactly at the vtbl */
    CameraVtbl *vtbl;    /* +0xC0 */
    u8 padc4[0xC];
    Vec4 base;           /* +0xD0 */
    Vec4 eye;            /* +0xE0 */
    Vec4 at;             /* +0xF0 */
    f32 lag;             /* +0x100 */
    f32 lag2;            /* +0x104 */
    s32 latch;           /* +0x108, per-frame one-shot */
    void *target;        /* +0x10C */
    u8 pad110[0x10];
    Vec4 offset;         /* +0x120 */
    CamParams saved;     /* +0x130..0x15C */
    u8 pad15c[0xA0];   /* CamParams is 0x2C, so `saved` ends at 0x15C */
    s32 skipOnce;        /* +0x1FC */
    u8 pad200[0x18];
    s32 hasRetarget;     /* +0x218 */
    f32 retargetT;       /* +0x21C */
    u8 pad220[0x2D0 - 0x220];
    f32 fadeRate;        /* +0x2D0, zero means "no fade running" */
    u8 pad2d4[0x4];
    f32 fadeLimit;       /* +0x2D8, zero means "no limit" */
    f32 fadeClock;       /* +0x2DC, advanced by dt/30 */
} Camera;

#endif
