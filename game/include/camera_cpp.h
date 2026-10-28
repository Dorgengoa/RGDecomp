#ifndef CAMERA_CPP_H
#define CAMERA_CPP_H

#include "types.h"
#include "vec.h"

/* The camera as a REAL C++ class, which is what it has to be for the vtable
   calls to match. A struct-of-function-pointers produces `jalr v0`; a virtual
   call produces `lw t9 / lw t9 / jalr t9`, which is what retail has -- proved
   by compiling both forms side by side under b210.

   mwcc puts the vptr AFTER the leading data members, not at offset 0, which is
   why it lands at +0xC0 here. The table starts 8 bytes in -- the first declared
   virtual lands at +0x08 -- so every slot from there up to the highest one used
   has to be declared, in order, to push the named ones to the right offsets. */

typedef struct CamParams {
    f32 a, b, c, d, e, f, g, h, i, j;
    s32 k;      /* +0x28, an int, not a float */
} CamParams;

class Camera {
    u8 pad000[0x50];
public:
    Vec4 eyeNow;         /* +0x50 */
    Vec4 atNow;          /* +0x60 */
    f32 unk70;           /* +0x70 */
private:
    u8 pad074[0xC];
public:
    Mtx4 xform;          /* +0x80, 0x40 bytes -- ends exactly at the vptr */
private:
public:
    /* +0x10 */ VC_VPTR_MEMBER; void slot08() { VCM0(void, 0x8); }
    /* +0x14 */ void slot0C() { VCM0(void, 0xC); }
    /* +0x18 */ f32 getAngle() { return VCM0(f32, 0x10); }
    /* +0x1C */ void setAngle(f32 a0) { VCM(void, (void *, f32), 0x14, a0); }
    /* +0x20 */ void slot18() { VCM0(void, 0x18); }
    /* +0x24 */ void setMatrix(const Mtx4 * a0) { VCM(void, (void *, const Mtx4 *), 0x1C, a0); }
    /* +0x28 */ void slot20(f32 t, const Vec4 *a, const Vec4 *b) { VCM(void, (void *, const Vec4 *, const Vec4 *, f32), 0x20, a, b, t); }
    /* +0x2C */ void slot24() { VCM0(void, 0x24); }
    /* +0x30 */ void setPos(const Vec4 * a0) { VCM(void, (void *, const Vec4 *), 0x28, a0); }
    /* +0x34 */ void slot2C() { VCM0(void, 0x2C); }
    /* +0x38 */ void finish(f32 a0) { VCM(void, (void *, f32), 0x30, a0); }
    /* +0x3C */ void slot34() { VCM0(void, 0x34); }
    /* +0x40 */ void slot38() { VCM0(void, 0x38); }
    /* +0x44 */ void slot3C() { VCM0(void, 0x3C); }
    /* +0x48 */ void toView() { VCM0(void, 0x40); }
    /* +0x4C */ void slot44() { VCM0(void, 0x44); }
    /* +0x50 */ CamParams * getParams() { return VCM0(CamParams *, 0x48); }
    /* +0x54 */ void slot4C() { VCM0(void, 0x4C); }
    /* +0x58 */ void slot50() { VCM0(void, 0x50); }
    /* +0x5C */ void slot54() { VCM0(void, 0x54); }
    /* +0x60 */ void commit() { VCM0(void, 0x58); }
    /* +0x64 */ void apply() { VCM0(void, 0x5C); }
    /* +0x68 */ void slot60() { VCM0(void, 0x60); }
    /* +0x6C */ void retarget(f32 a0) { VCM(void, (void *, f32), 0x64, a0); }
    /* +0x70 */ void slot68() { VCM0(void, 0x68); }
    /* +0x74 */ void slot6C() { VCM0(void, 0x6C); }
    /* +0x78 */ void slot70() { VCM0(void, 0x70); }
    /* +0x7C */ void slot74() { VCM0(void, 0x74); }
    /* +0x80 */ void slot78() { VCM0(void, 0x78); }
    /* +0x84 */ void slot7C() { VCM0(void, 0x7C); }
    /* +0x88 */ void slot80() { VCM0(void, 0x80); }
    /* +0x8C */ void slot84() { VCM0(void, 0x84); }
    /* +0x90 */ void slot88() { VCM0(void, 0x88); }
    /* +0x94 */ void slot8C() { VCM0(void, 0x8C); }
    /* +0x98 */ void slot90() { VCM0(void, 0x90); }
    /* +0x9C */ void getBoomA(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x94, a0); }
    /* +0xA0 */ void getBoomB(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x98, a0); }
    /* +0xA4 */ void getEye(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x9C, a0); }
    /* +0xA8 */ void getAt(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA0, a0); }
    /* +0xAC */ void getEyeLocal(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
    /* +0xB0 */ void getAtLocal(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
    /* +0xB4 */ void slotAC() { VCM0(void, 0xAC); }
    /* +0xB8 */ void setEye(const Vec4 * a0) { VCM(void, (void *, const Vec4 *), 0xB0, a0); }
    /* +0xBC */ void setAt(const Vec4 * a0) { VCM(void, (void *, const Vec4 *), 0xB4, a0); }
    /* +0xC0 is the vptr itself; data resumes after it. */
    u8 padc4[0xC];
    Vec4 base;           /* +0xD0 */
    Vec4 eye;            /* +0xE0 */
    Vec4 at;             /* +0xF0 */
    f32 lag;             /* +0x100 */
    f32 lag2;            /* +0x104 */
    s32 latch;           /* +0x108 */
    void *target;        /* +0x10C */
    u8 pad110[0x10];
    Vec4 offset;         /* +0x120 */
    CamParams saved;     /* +0x130 */
    u8 pad15c[0xA0];   /* CamParams is 0x2C, so `saved` ends at 0x15C */
    s32 skipOnce;        /* +0x1FC */
    u8 pad200[0x18];
    s32 hasRetarget;     /* +0x218 */
    f32 retargetT;       /* +0x21C */
};

#endif
