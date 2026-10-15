#include "types.h"

/* MEASURED: the argument-pointer advance is a POST-INCREMENT in the FIRST
   call's argument (`f780(args++)`), which is what puts `addiu $18,$18,0x8`
   in that call's delay slot and leaves `daddu $4,$18,$0` at the second.
   A standalone `args += 8;` / `args = args + 8;` / `++args` at the second
   call site all fold into `addiu $4,$18,0x8` and are one object (INERT).
   `dsll32/dsra32 ..,16` on the saved return is an s32 local + an (s16) cast. */
extern s32 VariantGetInt_15f780(void *);
extern f32 VariantGetFloat_15f740(void *);
extern void EffCurveAddKey_197610(void *, s16, f32);
typedef struct Arg { s32 a; s32 b; } Arg;
s32 EffDefCmdAnimeData_19c250(Arg *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    s32 id;
    f32 t;
    if (*(void **)(o + 0x4C) == 0) {
        return 0;
    }
    id = VariantGetInt_15f780(args++);
    t = VariantGetFloat_15f740(args);
    EffCurveAddKey_197610(*(void **)(o + 0x4C), (s16)id, t);
    return 1;
}
