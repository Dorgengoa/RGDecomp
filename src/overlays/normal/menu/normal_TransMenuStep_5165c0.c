#include "types.h"
/* normal 0x005165C0 -- the gameplay scene's per-frame FADE driver.  gp-0xA24
 * is the phase, gp-0xA18 its timer, and normal_TransMenuIsQuickOpen_514a00 splits the frame
 * into a "still loading" arm (which snaps the widgets with func_2907A0) and a
 * "loaded" arm (which ramps them with func_290690 and waits for 0x7532 to
 * reach 1.0f before handing the camera to func_321xxx).  Globals and their
 * types are the ones normal_TransMenuInit_516aa0.c already proved byte-identical. */

typedef struct Act { u8 pad00[0x30]; s16 f30; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;
typedef struct Obj { u8 pad00[0x14]; } Obj;

extern const u8 D_00527F10[];

extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern Obj  *D_004846E8;          /* gp - 0xA88  */
extern Obj  *D_004846EC;          /* gp - 0xA84  */
extern Obj  *D_004846F0;          /* gp - 0xA80  */
extern Obj  *D_004846F4;          /* gp - 0xA7C  */
extern Obj  *D_004846F8;          /* gp - 0xA78  */
extern s16   D_00484700;          /* gp - 0xA70  */
extern s8    D_0048472C;          /* gp - 0xA44  */
extern s16   D_0048474C;          /* gp - 0xA24  */
extern s16   D_00484750;          /* gp - 0xA20  */
extern f32   D_00484758;          /* gp - 0xA18  */
extern f32   D_0047D958;          /* gp - 0x7818 */
extern f32   D_0047D95C;          /* gp - 0x7814 */
extern f32   D_0047D1FC;          /* gp - 0x7F74 */

extern s32   normal_TransMenuIsQuickOpen_514a00(void);
extern void  func_287B90(s32 a);
extern void  func_288340(void);
extern void  func_291110(Obj *w, u16 id, s32 c, s32 d);
extern void  func_2907A0(Obj *w, u16 id, f32 x);
extern void  func_290690(Obj *w, u16 id, f32 a, f32 b, f32 c);
extern void  func_290F60(Obj *w, u16 id, s32 a, s32 b);
extern f32   func_290770(Obj *w, u16 id);
extern void  func_1782A0(const u8 *p, s32 n, f32 x, f32 y, f32 z);
extern void  func_177F90(const u8 *p);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_28ED70(void *p);
extern Ent  *func_1FEDE0(void);
extern void *func_201A90(void);
extern void  func_1E49B0(void *p, s16 n, s32 *out);
extern s32   func_1DCB50(s32 n);
extern void *func_201A70(void);
extern void  func_321C00(void *p, s32 a);
extern void  func_321B60(void *p, s32 a, s32 b);
extern void  func_321AC0(void *p, s32 a, s32 b);
extern void  func_321A20(void *p, s32 a, s32 b);
extern void  func_321E80(void *p, f32 x);
extern void  func_322030(void *p, s32 a);
extern void  normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c);
extern void  func_1E2D10(void *p);
extern void  normal_TransMenuResPoll_5181d0(void);
extern void  normal_TransMenuSubResPoll_517d40(void);
extern void  normal_TransMenuBobIconStep_518450(void);
extern void *func_15DE40(void);
extern void  func_157CA0(void *p, s32 a, f32 x);
extern void  func_2913A0(Obj *w);

void normal_TransMenuStep_5165c0(void)
{
    f32   t;
    Ent  *e;
    void *ob;
    void *pl;
    void *fb;
    s32   n;
    s32   m;

    if (D_0048474C != 0) {
        t = D_00484758 + D_0047D958;
        D_00484758 = t;
        if (!(t <= 0.0f)) {
            D_00484758 = t - D_0047D1FC;
        }
        if (normal_TransMenuIsQuickOpen_514a00() != 0) {
            if (D_00484750 == 1) {
                if (D_004806C8 == 1) {
                    func_287B90(0);
                    func_288340();
                    func_291110(D_004846EC, 0x84D1, 1, 1);
                    func_2907A0(D_004846EC, 0x84D1, 1.0f);
                    func_291110(D_004846E8, 0x7532, 1, 1);
                    func_2907A0(D_004846E8, 0x7532, 1.0f);
                    func_291110(D_004846E8, 0x7533, 1, 1);
                    func_2907A0(D_004846E8, 0x7533, 1.0f);
                    func_291110(D_004846E8, 0x75D1, 0, 1);
                    D_0048474C = 2;
                    D_004806C8 = 0;
                    func_1782A0(D_00527F10, 1, 1.0f, 1.0f, 1.0f);
                    func_177F90(D_00527F10);
                    func_28EDE0(&D_00484700, 2, 1);
                }
            }
        } else {
            if (D_00484750 == 1) {
                if (D_004806C8 == 1) {
                    func_291110(D_004846EC, 0x84D1, 1, 1);
                    func_290690(D_004846EC, 0x84D1, 1.0f, D_0047D95C, -1.0f);
                    func_291110(D_004846EC, 0x7532, 1, 1);
                    func_290690(D_004846E8, 0x7532, 1.0f, D_0047D95C, -1.0f);
                    func_291110(D_004846E8, 0x7533, 1, 1);
                    func_290690(D_004846E8, 0x7533, 1.0f, D_0047D95C, -1.0f);
                    func_290F60(D_004846E8, 0x7556, 0x26, 0x6A);
                }
            }
            if (D_004806C8 == 1) {
                if (!(func_290770(D_004846E8, 0x7532) < 1.0f)) {
                    D_0048474C = 2;
                    D_004806C8 = 0;
                    func_28EDE0(&D_00484700, 1, 1);
                    e = func_1FEDE0();
                    ob = func_201A90();
                    if (ob != NULL) {
                        n = 0;
                        func_1E49B0(ob, e->f18->f30, &n);
                        if (n != 0) {
                            if (func_1DCB50(n) != 0) {
                                pl = func_201A70();
                                if (pl != NULL) {
                                    func_321C00(pl, 1);
                                    func_321B60(pl, 0x10, 0x20);
                                    func_321AC0(pl, 0x1E0, 0x1A0);
                                    func_321A20(pl, 0x1E0, 0x180);
                                    func_321E80(pl, 15.0f);
                                }
                                D_0048472C = 1;
                            }
                        }
                    }
                    func_291110(D_004846E8, 0x75D1, 1, 1);
                    func_290690(D_004846E8, 0x75D1, 1.0f, D_0047D95C, 0.0f);
                    normal_TransMenuBobIconMoveTo_518420(0xF4, 0xBE, -1);
                    if (ob != NULL) {
                        func_1E2D10(ob);
                    }
                }
            }
        }
        normal_TransMenuResPoll_5181d0();
        normal_TransMenuSubResPoll_517d40();
        ob = func_201A90();
        if (ob != NULL) {
            e = func_1FEDE0();
            m = 0;
            func_1E49B0(ob, e->f18->f30, &m);
            if (m != 0) {
                if (D_0048472C != 0) {
                    func_1DCB50(m);
                    pl = func_201A70();
                    if (pl != NULL) {
                        func_322030(pl, 0);
                    }
                }
            }
        }
        normal_TransMenuBobIconStep_518450();
        fb = func_15DE40();
        if (fb != NULL) {
            func_157CA0(fb, 0x32C, 1.0f);
        }
        func_2913A0(D_004846E8);
        func_2913A0(D_004846EC);
        func_2913A0(D_004846F0);
        func_2913A0(D_004846F4);
        func_2913A0(D_004846F8);
        func_28ED70(&D_00484700);
        func_177F90(D_00527F10);
    }
}
