#include "types.h"
/* normal 0x0050ECC0 -- opens the item-detail page for `e`: the 0x4C name box
 * takes the entity's 0x10->0x2C string id, the 0x4A icon is centred on 0xA0
 * from its own measured width, the entity is handed the 0x527EA0 descriptor
 * through its virtual slot 17, the four 0x77..0x7A stat widgets are raised and
 * the 0x4F row is cleared and re-keyed to the entity's slot-18 value.
 *
 * TWO VIRTUAL calls (`lw $25,0($x) / lw $25,off($25) / jalr $25`), so the unit
 * is .cpp -- a struct of function pointers gives `jalr $v0`, only a real C++
 * `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable +0x08, so
 * the slots are (0x4C-8)/4 = 17 and (0x50-8)/4 = 18.
 * `bgez / sra 1 / addiu +1 / sra 1` is a SIGNED `/ 2`, not a shift.
 * `daddu $17,$2,$0` and `sd $2,0x68($16)` sit in a call's DELAY SLOT and carry
 * the PREVIOUS statement's value, not that call's.
 * `addiu $7,$0,1` is hoisted ABOVE the k==1 test and shared by both arms of
 * func_291110's fourth argument, so only the third argument differs. */

struct Desc {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void attach(const void *p);   /* slot 17 -> vtable +0x4C */
    virtual s32  kind();                  /* slot 18 -> vtable +0x50 */
    u8    pad04[0x10 - 4];
    void *f10;
};

typedef struct Name { u8 pad00[0x2C]; s16 f2C; } Name;
typedef struct Box  { u8 pad00[4]; s16 f04; s16 f06; u8 pad08[4]; s16 f0C; s16 f0E; } Box;
typedef struct Row  { u8 pad00[0x48]; s64 f48; u8 pad50[0x68 - 0x50]; s64 f68;
                      u8 pad70[0x76 - 0x70]; s16 f76; s16 f78; } Row;

extern const u8 D_00527EA0[];

extern "C" void *D_004845CC;      /* gp - 0xBA4 */
extern "C" void *D_004845F8;      /* gp - 0xB78 */

extern "C" void        func_288E50(void *p, s16 a, s32 b, s32 c);
extern "C" void        func_28A800(void *w, const void *a, s32 b, s32 c, s32 d);
extern "C" const void *func_28AA30(void *p, s32 id);
extern "C" void        func_28F300(void *p, s32 id, s32 c, s32 d);
extern "C" s32         func_28F400(void *p, s32 id, s32 c);
extern "C" void        func_28F510(void *p, s32 id, const void *q, s32 d);
extern "C" void        func_28F590(void *p, s32 id, s32 c, s32 d);
extern "C" Row        *func_28F2B0(void *p, s32 id, s32 c);
extern "C" Box        *func_28FE10(void *p, s32 id, s32 c);
extern "C" void        func_290F60(void *p, s32 id, s32 x, s32 y);
extern "C" void        func_291110(void *p, s32 id, s32 c, s32 d);
extern "C" s32         func_3D4320(Desc *e);
extern "C" void        normal_ShopMenuSellTotalPriceSet_50ec80(s32 a, s32 b);

extern "C" s32 normal_ShopMenuSellQtyPanelLayout_50ecc0(Desc *e);

s32 normal_ShopMenuSellQtyPanelLayout_50ecc0(Desc *e)
{
    Box *t;
    Box *u;
    Row *m;
    s32  k;
    s32  r;

    if (e == 0) {
        return 0;
    }
    k = e->kind();
    t = func_28FE10(D_004845CC, 0x4C, 0);
    if (t == 0) {
        return 0;
    }
    func_288E50(t, ((Name *)e->f10)->f2C, 0x28, 0x2D);
    func_28F510(D_004845CC, 0x4A, func_28AA30(D_004845F8, 4), 0);
    if (k == 1) {
        func_291110(D_004845CC, 0x4D, 0, 1);
    } else {
        func_291110(D_004845CC, 0x4D, 1, 1);
    }
    func_28F590(D_004845CC, 0x4A, 0xA0 - func_28F400(D_004845CC, 0x4A, 0) / 2, 0);
    e->attach(D_00527EA0);
    func_28F510(D_004845CC, 0x4A, D_00527EA0, 1);
    func_28F300(D_004845CC, 0x4A, 0xA8, 1);
    t = func_28FE10(D_004845CC, 0x7A, 0);
    if (t == 0) {
        return 0;
    }
    func_291110(D_004845CC, 0x77, 1, 1);
    func_291110(D_004845CC, 0x78, 1, 1);
    func_291110(D_004845CC, 0x79, 1, 1);
    func_291110(D_004845CC, 0x7A, 1, 1);
    func_28A800(t, func_28AA30(D_004845F8, 0x15), 0, 0, -2);
    func_290F60(D_004845CC, 0x77, 0x70, 0x5A);
    func_290F60(D_004845CC, 0x78, 0x3E, 0x72);
    func_290F60(D_004845CC, 0x79, 0xB4, 0x44);
    func_290F60(D_004845CC, 0x7A, 0x3E, 0x44);
    u = func_28FE10(D_004845CC, 0x4F, 0);
    if (u == 0) {
        return 0;
    }
    u->f0E = 0;
    u->f06 = 0;
    u->f0C = 0;
    u->f04 = 0;
    m = func_28F2B0(D_004845CC, 0x4F, 0);
    if (m == 0) {
        return 0;
    }
    m->f76 = 0xC;
    m->f78 = 0x10;
    m->f68 = k;
    r = func_3D4320(e);
    m->f48 = r;
    normal_ShopMenuSellTotalPriceSet_50ec80(r, 1);
    return 1;
}
