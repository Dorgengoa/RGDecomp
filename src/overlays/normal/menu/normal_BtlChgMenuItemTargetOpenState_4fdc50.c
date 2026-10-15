#include "types.h"
/* normal 0x004FDC50 -- the 0x5605 phase's open.  Five 0x21/0x26/0x27/0x25/0x23
 * widget fades share one (0.0f, gp-0x7C4C, -1.0f) triple; the 0x2A holder's
 * 0x20 node is reset to -1; then the 0x44 holder's 0x28 object takes one of
 * three string ids (0x68 / 0x69 / 0x6A) chosen by func_3D4F00 on the
 * gp-0xCAC handle, and the 0x43 widget is faded in. */

typedef struct Node   { u8 pad00[0x20]; s16 f20; } Node;
typedef struct Holder { u8 pad00[0x20]; Node *f20; } Holder;
typedef struct HolderB{ u8 pad00[0x28]; s32 f28; } HolderB;
typedef struct Obj    { u8 pad00[4]; s32 f04; } Obj;
typedef struct Rec    { u8 pad00[8]; s16 f08; } Rec;
typedef struct Ctx    { u8 pad00[0x18]; s32 f18; } Ctx;

extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern void *D_00484498;          /* gp - 0xCD8  */
extern s32   D_004844B8;          /* gp - 0xCB8  */
extern void *D_004844C4;          /* gp - 0xCAC  */
extern void *D_00481BB8;          /* gp - 0x35B8 */
extern f32   D_0047D524;          /* gp - 0x7C4C */
extern f32   D_0047D518;          /* gp - 0x7C58 */
extern s32   D_00525100[];
extern s32   D_00525104[];

extern void    func_290690(void *p, u16 id, f32 a, f32 b, f32 c);
extern void    func_291110(void *p, u16 id, s32 c, s32 d);
extern Holder *func_290460(void *p, u16 id);
extern void    func_290F60(void *p, u16 id, s32 c, s32 d);
extern void    func_28EA90(void *p, s32 id, s32 a);
extern Rec    *func_28EC60(void *p);
extern s32     func_3D4F00(void *p);
extern Ctx    *func_1FEDE0(void);
extern s32     func_3C2010(s32 a, s32 b, s32 c);
extern s32     func_28AA30(void *p, s32 id);
extern void    func_2907A0(void *p, u16 id, f32 x);
extern void    func_28EDE0(void *p, s32 id, s32 a);

s32 normal_BtlChgMenuItemTargetOpenState_4fdc50(void *unused, s32 show)
{
    Holder *h;
    HolderB *hb;
    Obj *obj;
    Rec *rec;
    Ctx *ctx;

    if (show != 0) {
        func_290690(D_0048449C, 0x21, 0.0f, D_0047D524, -1.0f);
        func_290690(D_0048449C, 0x26, 0.0f, D_0047D524, -1.0f);
        func_290690(D_0048449C, 0x27, 0.0f, D_0047D524, -1.0f);
        func_290690(D_0048449C, 0x25, 0.0f, D_0047D524, -1.0f);
        func_290690(D_0048449C, 0x23, 0.0f, D_0047D524, -1.0f);
        func_291110(D_0048449C, 0x2A, 1, 1);
        h = func_290460(D_0048449C, 0x2A);
        if (h != NULL) {
            if (h->f20 != NULL) {
                h->f20->f20 = -1;
            }
        }
        func_290F60(D_0048449C, 0x2A, D_00525100[0], D_00525104[0]);
        func_28EA90(D_004844A0, 0x55F5, 1);
        D_004844B8 = 0;
        rec = func_28EC60(D_004844A0);
        if (D_004844C4 == NULL) {
            return 0;
        }
        hb = (HolderB *)func_290460(D_0048449C, 0x44);
        if (hb != NULL) {
            obj = (Obj *)hb->f28;
            if (obj == NULL) {
                return 0;
            }
        }
        if (func_3D4F00(D_004844C4) == 0) {
            ctx = func_1FEDE0();
            if (ctx == NULL) {
                return 0;
            }
            rec->f08 = func_3C2010(ctx->f18, 1, 1) - 1;
            obj->f04 = func_28AA30(D_00481BB8, 0x68);
        } else {
            rec->f08 = 0;
            if (func_3D4F00(D_004844C4) == 2) {
                obj->f04 = func_28AA30(D_00481BB8, 0x69);
            } else {
                obj->f04 = func_28AA30(D_00481BB8, 0x6A);
            }
        }
        func_291110(D_0048449C, 0x43, 1, 1);
        func_2907A0(D_0048449C, 0x43, 0.0f);
        func_290690(D_0048449C, 0x43, 1.0f, D_0047D518, -1.0f);
        func_290F60(D_0048449C, 0x43, 0x6C, 0x12D);
    }
    func_28EDE0(D_00484498, 0x5605, 0);
    return 1;
}
