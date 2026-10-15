#include "types.h"

/* title.bin overlay, 0x004ECD80 -- turn a group of sub-parts on or off.  Both
 * `beql` delay slots carry the NEXT block's load, so these are ordinary
 * independent tests, not an epilogue merge.
 */

typedef struct Obj_title_FUN_004ecd80 {
    u8 pad000[0x4];
    void *field004;    /* +0x4 */
} Obj_title_FUN_004ecd80;

extern s16 D_0048419C;
extern f32 D_0047D578;

extern void func_291110(void *a, s32 b, s32 c, s32 d);
extern s32 func_207F20(void);
extern void func_2907A0(void *a, s32 b, f32 x);
extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);

s32 title_TitleMenuShow_4ecd80(Obj_title_FUN_004ecd80 *o)
{
    func_291110(o->field004, 1, 1, 1);
    if (func_207F20() != 0) {
        func_291110(o->field004, 3, 0, 1);
        func_291110(o->field004, 4, 0, 1);
        func_291110(o->field004, 5, 0, 1);
        func_291110(o->field004, 0x66, 0, 1);
    }
    if (D_0048419C != 0) {
        func_291110(o->field004, 0x66, 1, 1);
    } else {
        func_291110(o->field004, 0x66, 0, 1);
    }
    func_2907A0(o->field004, 1, 0.0f);
    func_290690(o->field004, 1, 1.0f, D_0047D578, -1.0f);
    return 1;
}
