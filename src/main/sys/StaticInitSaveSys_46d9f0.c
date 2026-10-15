#include "types.h"

/* Two constructor registrations and a 32-entry global-to-global copy of a
   float table.

   The SOURCE table is gp-relative (`lwc1 %gp_rel(D_0047FA00)($28)`), which
   is what a plain 4-byte extern gets.  The DESTINATION table is `lui %hi`
   + `swc1 %lo`, and it is WRITTEN, so `const` -- the usual way out of small
   data -- is not available.  The escape is an INCOMPLETE ARRAY: an object
   of unknown size is not small-data addressable, so mwcc emits %hi/%lo and
   the store still writes.  See memory/levers.d/normal-s16-cast-sign-extension.md
   ("the small-data threshold is between 8 and 16 B; an incomplete array is
   the escape") and the `const` recipe in memory/subsystem-decomp-track.md. */

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void SysMsgInit_1c69e0(void *);
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);

extern s32 D_00483140;
extern s32 D_0048314C;
extern s32 D_00483150;
extern s32 D_0048315C;
extern u8  D_004E9080[];
extern s64 D_00483160;

extern s64 D_0047F9F8;
extern f32 D_0047FA00;
extern f32 D_0047FA08;
extern f32 D_0047FA0C;
extern f32 D_0047FA10;
extern f32 D_0047FA18;
extern f32 D_0047FA1C;
extern f32 D_0047FA20;
extern f32 D_0047FA28;
extern f32 D_0047FA2C;
extern f32 D_0047FA30;
extern f32 D_0047FA38;
extern f32 D_0047FA3C;
extern f32 D_0047FA40;
extern f32 D_0047FA48;
extern f32 D_0047FA4C;
extern f32 D_0047FA50;
extern f32 D_0047FA58;
extern f32 D_0047FA5C;
extern f32 D_0047FA60;
extern f32 D_0047FA68;
extern f32 D_0047FA6C;
extern f32 D_0047FA70;
extern f32 D_0047FA78;
extern f32 D_0047FA7C;
extern f32 D_0047FA80;
extern f32 D_0047FA88;
extern f32 D_0047FA8C;
extern f32 D_0047FA90;
extern f32 D_0047FA98;
extern f32 D_0047FA9C;
extern f32 D_0047FAA0;

extern s64 D_00463840[];
extern f32 D_00463848[];
extern f32 D_0046384C[];
extern f32 D_00463850[];
extern f32 D_00463854[];
extern f32 D_00463858[];
extern f32 D_0046385C[];
extern f32 D_00463860[];
extern f32 D_00463864[];
extern f32 D_00463868[];
extern f32 D_0046386C[];
extern f32 D_00463870[];
extern f32 D_00463874[];
extern f32 D_00463878[];
extern f32 D_0046387C[];
extern f32 D_00463880[];
extern f32 D_00463884[];
extern f32 D_00463888[];
extern f32 D_0046388C[];
extern f32 D_00463890[];
extern f32 D_00463894[];
extern f32 D_00463898[];
extern f32 D_0046389C[];
extern f32 D_004638A0[];
extern f32 D_004638A4[];
extern f32 D_004638A8[];
extern f32 D_004638AC[];
extern f32 D_004638B0[];
extern f32 D_004638B4[];
extern f32 D_004638B8[];
extern f32 D_004638BC[];
extern f32 D_004638C0[];

void StaticInitSaveSys_46d9f0(void)
{
    IosBaseInitCtor_102bd0(&D_0048314C);
    RegisterGlobalObject_100dc0(&D_0048314C, IosBaseInitDtor_102ee0, &D_00483140);
    WIosBaseInitCtor_103110(&D_0048315C);
    RegisterGlobalObject_100dc0(&D_0048315C, WIosBaseInitDtor_103420, &D_00483150);
    SysMsgInit_1c69e0(D_004E9080);
    D_00463848[0] = D_0047FA00;
    D_00463840[0] = D_0047F9F8;
    D_0046384C[0] = D_0047FA08;
    D_00463850[0] = D_0047FA0C;
    D_00463854[0] = D_0047FA10;
    D_00463858[0] = D_0047FA18;
    D_0046385C[0] = D_0047FA1C;
    D_00463860[0] = D_0047FA20;
    D_00463864[0] = D_0047FA28;
    D_00463868[0] = D_0047FA2C;
    D_0046386C[0] = D_0047FA30;
    D_00463870[0] = D_0047FA38;
    D_00463874[0] = D_0047FA3C;
    D_00463878[0] = D_0047FA40;
    D_00483160 = 0;
    D_0046387C[0] = D_0047FA48;
    D_00463880[0] = D_0047FA4C;
    D_00463884[0] = D_0047FA50;
    D_00463888[0] = D_0047FA58;
    D_0046388C[0] = D_0047FA5C;
    D_00463890[0] = D_0047FA60;
    D_00463894[0] = D_0047FA68;
    D_00463898[0] = D_0047FA6C;
    D_0046389C[0] = D_0047FA70;
    D_004638A0[0] = D_0047FA78;
    D_004638A4[0] = D_0047FA7C;
    D_004638A8[0] = D_0047FA80;
    D_004638AC[0] = D_0047FA88;
    D_004638B0[0] = D_0047FA8C;
    D_004638B4[0] = D_0047FA90;
    D_004638B8[0] = D_0047FA98;
    D_004638BC[0] = D_0047FA9C;
    D_004638C0[0] = D_0047FAA0;
}
