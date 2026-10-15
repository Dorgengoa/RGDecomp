#include "types.h"
/* normal 0x004FAAC0 -- the gameplay panel/roster builder.  1,120 bytes.
 *
 * D_005278xx / D_005250xx / D_005263xx are OVERLAY data, far outside the gp
 * window (_gp 0x00485170 +/- 0x8000), so every one of them is `const` to take
 * %hi/%lo; the two that are WRITTEN go through the documented
 * `*(s32 *)&D_x = v` cast form.  The gp globals at 0x004844xx are inside the
 * window and are plain.
 *
 * The parameter is stored to D_00484444 immediately and every later use reads
 * the GLOBAL back -- retail reloads it at each site rather than holding it. */
typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    u16   fA_lo : 2;
    u16   fA_hi : 14;
} Rec;
typedef struct Hdl { u8 pad00[0x16]; s16 f16; } Hdl;

extern const u8  D_00527820[];
extern const s32 D_00527828;
extern const u8  D_00527840[];
extern const s32 D_00527848;
extern const u8  D_00525030[];
extern const u8  D_00525050[];
extern const u8  D_005263B8[];
extern const u8  D_005263D0[];
extern const u8  D_005263E8[];
extern const u8  D_005263F0[];

extern void *D_00484444;
extern s32   D_0048444C;
extern void *D_00484450;
extern void *D_00484454;
extern void *D_00484458;
extern s16   D_00484464;
extern s16   D_00484468;
extern u8    D_00484470;
extern s16   D_004804DC;

extern void *func_206A40(void);
extern Rec  *func_42C500(void *a, s32 b);
extern Rec  *func_42C040(void *a, s32 b);
extern void  func_2912E0(const void *a);
extern void  func_290390(const void *a, void *b, s32 c);
extern void  func_2901D0(const void *a, void *b, s32 c, s32 d);
extern void *func_207DF0(void);
extern u8   *func_14D950(void *a, s32 b);
extern void  func_290B90(const void *a, s32 id, void *b);
extern void  func_28EEC0(const void *a, s32 id, void *b);
extern void  func_1319A8(void *a, const void *b, s32 c);
extern void *func_28C2A0(void *a);
extern void *func_14E230(s32 size, void *heap);
extern void  normal_BtlChgPageInit_5062f0(void *a);
extern void  normal_BtlChgPageSetMemStack_506270(void *a, void *b);
extern void  normal_BtlChgPageEntryListLoad_506210(void *a, void *b, void *c, s32 d);
extern void  normal_BtlChgPageSetLayout_506250(void *a, const void *b);
extern void *normal_UiPageGetList_289b50(void *a);
extern Hdl  *func_28EA40(void *a, s32 b);
extern void *func_28FE10(const void *a, s32 id, s32 c);
extern void  func_28A800(void *a, const void *b, s32 c, s32 d, s32 e);
extern s32   func_134BB0(const void *a);
extern void  func_28FC90(const void *a, s32 id, s32 c, s32 k);

void normal_BtlChgMenuInit_4faac0(void *p)
{
    void *g;
    Rec *r;
    void *t;
    s32 n;
    u8 *a;
    u8 *b;
    u8 *c;
    s32 i;
    s32 k;
    s32 m;

    g = func_206A40();
    r = func_42C500(g, 0x13);
    t = r->f04;
    n = r->fA_hi;
    D_00484444 = p;
    D_0048444C = 0;
    func_2912E0(D_00527820);
    func_290390(D_00527820, D_00484444, n);
    func_2901D0(D_00527820, t, 0, 0);
    *(s32 *)&D_00527828 = 0x32B;
    D_00484450 = func_207DF0();

    r = func_42C500(g, 0x14);
    t = r->f04;
    n = r->fA_hi;
    func_2912E0(D_00527840);
    func_290390(D_00527840, D_00484444, n);
    func_2901D0(D_00527840, t, 0, 0);
    *(s32 *)&D_00527848 = 0x32B;

    a = func_14D950(D_00484444, 0x52);
    b = func_14D950(D_00484444, 0x52);
    c = func_14D950(D_00484444, 0x52);

    func_290B90(D_00527840, 0x26, a);
    for (i = 0; i < 0x28; i++) {
        func_1319A8(a, D_00525030, 0x20);
        a += 0x20;
    }
    *(s16 *)a = -1;
    func_290B90(D_00527840, 0x55, b);
    for (i = 0; i < 0x28; i++) {
        func_1319A8(b, D_00525030, 0x20);
        b += 0x20;
    }
    *(s16 *)b = -1;
    func_28EEC0(D_00527840, 0x27, c);
    for (i = 0; i < 0x28; i++) {
        func_1319A8(c, D_00525050, 0x20);
        c += 0x20;
    }
    *(s16 *)c = -1;

    D_00484458 = func_28C2A0(D_00484444);
    r = func_42C040(g, 0xA);
    t = r->f04;
    n = r->fA_hi;
    D_00484454 = func_14E230(0x518, D_00484444);
    normal_BtlChgPageInit_5062f0(D_00484454);
    normal_BtlChgPageSetMemStack_506270(D_00484454, D_00484444);
    normal_BtlChgPageEntryListLoad_506210(D_00484454, t, D_00484450, n);
    normal_BtlChgPageSetLayout_506250(D_00484454, D_00527840);
    func_28EA40(normal_UiPageGetList_289b50(D_00484454), 0x55F2)->f16 = 0;

    func_28A800(func_28FE10(D_00527840, 0x51, 0), D_005263B8, 0, 0, -2);
    m = func_134BB0(D_005263B8);
    for (k = 0; k < m; k++) {
        func_28FC90(D_00527840, 0x51, 0, k);
    }
    func_28A800(func_28FE10(D_00527840, 0x52, 0), D_005263D0, 0, 0, -2);
    m = func_134BB0(D_005263D0);
    for (k = 0; k < m; k++) {
        func_28FC90(D_00527840, 0x52, 0x19, k);
    }
    func_28A800(func_28FE10(D_00527840, 0x53, 0), D_005263E8, 0, 0, -2);
    m = func_134BB0(D_005263E8);
    for (k = 0; k < m; k++) {
        func_28FC90(D_00527840, 0x53, 0x32, k);
    }
    func_28A800(func_28FE10(D_00527840, 0x54, 0), D_005263F0, 0, 0, -2);
    m = func_134BB0(D_005263F0);
    for (k = 0; k < m; k++) {
        func_28FC90(D_00527840, 0x54, 0x4B, k);
    }

    D_00484464 = 0;
    D_004804DC = -1;
    D_00484468 = 0;
    D_00484470 = 0;
}
