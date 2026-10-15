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
    /* +0x10 */ virtual void slot08();
    /* +0x14 */ virtual void slot0C();
    /* +0x18 */ virtual f32 getAngle();
    /* +0x1C */ virtual void setAngle(f32);
    /* +0x20 */ virtual void slot18();
    /* +0x24 */ virtual void setMatrix(const Mtx4 *);
    /* +0x28 */ virtual void slot20(f32 t, const Vec4 *a, const Vec4 *b);
    /* +0x2C */ virtual void slot24();
    /* +0x30 */ virtual void setPos(const Vec4 *);
    /* +0x34 */ virtual void slot2C();
    /* +0x38 */ virtual void finish(f32);
    /* +0x3C */ virtual void slot34();
    /* +0x40 */ virtual void slot38();
    /* +0x44 */ virtual void slot3C();
    /* +0x48 */ virtual void toView();
    /* +0x4C */ virtual void slot44();
    /* +0x50 */ virtual CamParams *getParams();
    /* +0x54 */ virtual void slot4C();
    /* +0x58 */ virtual void slot50();
    /* +0x5C */ virtual void slot54();
    /* +0x60 */ virtual void commit();
    /* +0x64 */ virtual void apply();
    /* +0x68 */ virtual void slot60();
    /* +0x6C */ virtual void retarget(f32);
    /* +0x70 */ virtual void slot68();
    /* +0x74 */ virtual void slot6C();
    /* +0x78 */ virtual void slot70();
    /* +0x7C */ virtual void slot74();
    /* +0x80 */ virtual void slot78();
    /* +0x84 */ virtual void slot7C();
    /* +0x88 */ virtual void slot80();
    /* +0x8C */ virtual void slot84();
    /* +0x90 */ virtual void slot88();
    /* +0x94 */ virtual void slot8C();
    /* +0x98 */ virtual void slot90();
    /* +0x9C */ virtual void getBoomA(Vec4 *);
    /* +0xA0 */ virtual void getBoomB(Vec4 *);
    /* +0xA4 */ virtual void getEye(Vec4 *);
    /* +0xA8 */ virtual void getAt(Vec4 *);
    /* +0xAC */ virtual void getEyeLocal(Vec4 *);
    /* +0xB0 */ virtual void getAtLocal(Vec4 *);
    /* +0xB4 */ virtual void slotAC();
    /* +0xB8 */ virtual void setEye(const Vec4 *);
    /* +0xBC */ virtual void setAt(const Vec4 *);
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
