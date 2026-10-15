#include "types.h"
/* normal 0x005146B0 -- object reset then three 0x4B2570 device calls. */
typedef struct Obj {
    u8   pad000[0x14];
    s8   f014;
    u8   pad015[0x18 - 0x15];
    s32  f018;
    s32  f01C;
    s32  f020;
    u8   pad024[0x40 - 0x24];
    s32  f040;
    f32  f044;
    s16  f048;
    u8   pad04A[0x62 - 0x4A];
    s16  f062;
    void *f064;
    u8   pad068[0x6C - 0x68];
    s8   f06C;
} Obj;

extern const u8 D_004B2570[];
extern f32   D_0047DD8C;
extern void  func_2912E0(Obj *p);
extern void *func_207DF0(void);
extern void  func_183960(const void *a);
extern void  func_183D50(const void *a, s32 b, s32 c, s32 d);
extern void  func_183950(const void *a, s32 b);

s32 normal_SpaceMenuObjInit_5146b0(Obj *p)
{
    f32 a;

    func_2912E0(p);
    p->f01C = -1;
    a = D_0047DD8C;
    p->f018 = -1;
    p->f020 = 0;
    p->f040 = 0;
    p->f044 = a;
    p->f014 = 0;
    p->f048 = 0;
    p->f062 = 1;
    p->f064 = func_207DF0();
    p->f06C = 0;
    func_183960(D_004B2570);
    func_183D50(D_004B2570, 0xF00C, 0xC, 7);
    func_183950(D_004B2570, 0x78);
    return 0;
}
