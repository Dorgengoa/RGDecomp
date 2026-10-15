#include "types.h"
/* normal 0x00506DC0 -- build the 0x527C00 widget from the current record. */
/* the `dsll32 16 / dsrl32 18` off a plain `lhu` is an UNSIGNED BITFIELD of
 * width 14 at bit 2 of the u16 container at 0x0A -- not a shift of a u16. */
typedef struct Rec { u8 pad00[4]; s32 f04; u8 pad08[2];
                     u16 pad0A : 2; u16 f0A : 14; } Rec;
typedef struct Obj { u8 pad00[0x94]; s32 f94; u8 pad98[0xA6 - 0x98]; s16 fA6; } Obj;

extern u8 D_00527C00[];
extern s32 D_00527C08[];
extern const u8 D_004BC250[];

extern void *func_206A40(void);
extern Rec  *func_42C500(void *h, s32 id);
extern void  func_2912E0(void *w);
extern void  func_290390(void *w, void *s, s32 n);
extern void  func_2901D0(void *w, s32 a, s32 b, s32 c);
extern void  func_42C040(void *h, s32 id);
extern void  normal_LeaderHudReset_506ef0(const u8 *p);
extern void  func_289C40(const u8 *p, void *s);
extern s32   func_42C950(void *h, s32 id);
extern void  func_289C10(const u8 *p, s32 v);
extern s32   func_207DF0(void);
extern void  func_289C30(const u8 *p, void *w);

extern s32 normal_LeaderHudBuild_506dc0(Obj *p, void *s);
s32 normal_LeaderHudBuild_506dc0(Obj *p, void *s)
{
    void *h;
    Rec *r;
    s32 v;
    s32 n;

    if (s != 0) {
        h = func_206A40();
        r = func_42C500(h, 0x15);
        v = r->f04;
        n = r->f0A;
        func_2912E0(D_00527C00);
        func_290390(D_00527C00, s, n);
        func_2901D0(D_00527C00, v, 0, 0);
        D_00527C08[0] = 0x32B;
        func_42C040(h, 0xA);
        normal_LeaderHudReset_506ef0(D_004BC250);
        func_289C40(D_004BC250, s);
        func_289C10(D_004BC250, func_42C950(h, 0xC));
        p->f94 = func_207DF0();
        func_289C30(D_004BC250, D_00527C00);
    }
    p->fA6 = 1;
    return 0;
}
