#include "types.h"
/* normal 0x00504EA0 -- lays out the equipment compare panel.  A 5-entry s16
 * column table is copied out of small data, then whichever of the two cursor
 * columns (f74/f76) is behind drives which three slots are re-positioned and
 * which of the two 0xE rows is used; f78 records which layout was chosen.
 * The lower half resolves the highlighted item through the iterator built by
 * func_3A8180/func_370170 and fills the 0xE name row and the 0xF value row,
 * or clears both when nothing is selected.
 *
 * ONE `lw $25,0($18) / lw $25,0x2D0($25) / jalr $25` -> C++ virtual, vptr 0,
 * slot (0x2D0-8)/4 = 178.
 * `dsll32 $7,$2,0 / dsra32 $7,$7,0` (shift ZERO) is an s32->s64 widen at a call
 * argument: func_291250's fourth parameter is s64 and the value is s32.
 * Stack locals come out in REVERSE declaration order, so `tmp` is declared
 * last to land at 0x50. */

struct Ent {
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
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual s32 owns(s16 k);   /* slot 178 -> vtable +0x2D0 */
};

typedef struct Item  { s16 f00; u8 pad02; u8 f03; u8 pad04[4]; s32 f08; } Item;
typedef struct Hold  { u8 pad00[0x24]; struct Cell *f24; } Hold;
typedef struct Cell  { u8 pad00[0x16]; s16 f16; s16 f18; } Cell;
typedef struct Panel { u8 pad00[0x74]; s16 f74; s16 f76; s16 f78; } Panel;
typedef struct Top   { u8 pad00[0x18]; s32 f18; } Top;

extern s16 D_004805E0[4];         /* gp - 0x4B90, declared SHORT for small data */

extern "C" {

extern Top  *func_1FEDE0(void);
extern void  func_289090(Panel *p, u16 id, s32 c, s32 d);
extern Hold *func_290460(void *w, u16 id);
extern void  func_290A40(void *w, u16 id, u32 c, s32 d);
extern void  func_290A80(void *w, u16 id, s32 c, s32 d);
extern void  func_290B20(void *w, u16 id, s32 c, s32 d, s32 e, s32 f);
extern void  func_290F60(void *w, u16 id, s32 x, s16 y);
extern void  func_291250(void *w, u16 id, s32 c, s64 v);
extern Item *func_36FFF0(void *it, s32 k);
extern void  func_370170(void *it, void *src);
extern s32   func_3A05C0(s32 h);
extern void  func_3A8180(void *dst, Ent *o, s32 c, s32 d);
extern s32   func_3AD390(Ent *o, s16 k);
extern Ent  *func_3C2FB0(s32 a, s32 k);
extern s32   func_3F5CA0(Item *p);
extern s32 normal_BtlChgPageSetAbilityTypeIcon_505470(void *p, s32 id, s32 c);
extern s32   normal_BtlChgPageGetMember_505f90(Panel *p);
extern void *normal_UiPageGetLayout_289b60(Panel *p);

}

extern "C" s32 normal_BtlChgPageAbilityListScroll_504ea0(Panel *a)
{
    s16   tab[5];
    s32   buf[2];
    s32   tmp[6];
    void *w;
    Top  *t;
    Item *r;
    Ent  *o;
    Hold *h;
    Cell *g;
    s16  *sp;
    s16  *dp;
    s32   c;
    s32   i;
    s32   n;
    s32   v;
    s32   u;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    sp = D_004805E0;
    dp = tab;
    i = 5;
    do {
        *dp = *sp;
        sp++;
        dp++;
        i--;
    } while (i > 0);
    if (a->f74 > a->f76) {
        i = 0;
        do {
            func_290F60(w, (u16)(i * 3 + 5), 0, tab[i + 2]);
            i++;
        } while (i < 3);
        func_290F60(w, 0xE, 0, tab[0]);
        func_290F60(w, 0xE, 0, tab[1]);
        func_290F60(w, 0x18, 0xD5, 0xA);
        func_290F60(w, 0x14, 0xBF, 1);
        a->f78 = 1;
    } else if (a->f74 < a->f76) {
        i = 0;
        do {
            func_290F60(w, (u16)(i * 3 + 5), 0, tab[i]);
            i++;
        } while (i < 3);
        func_290F60(w, 0xE, 0, tab[4]);
        func_290F60(w, 0xE, 0, tab[3]);
        func_290F60(w, 0x18, 0xD5, 0xA);
        func_290F60(w, 0x14, 0xBF, 1);
        a->f78 = 2;
    }
    t = func_1FEDE0();
    if (t == 0) {
        return 0;
    }
    o = func_3C2FB0(t->f18, normal_BtlChgPageGetMember_505f90(a));
    if (o == 0) {
        return 0;
    }
    func_3A8180(tmp, o, 0, -1);
    func_370170(buf, tmp);
    r = 0;
    if (a->f78 == 1) {
        c = a->f76;
        if (c < 0) {
            c = 0;
        }
        r = func_36FFF0(buf, c);
    } else if (a->f78 == 2) {
        r = func_36FFF0(buf, a->f76 + 2);
    }
    if (r != 0) {
        func_290B20(w, 0xE, r->f08, -1, -1, 0);
        func_290A80(w, 0xE, 2, 0);
        func_290A40(w, 0xE, 0xFF202020, 0);
        if (o->owns(r->f00) != 0) {
            func_290A40(w, 0xE, 0xFF404040, 0);
        }
        h = func_290460(w, 0xF);
        if (h == 0) {
            return 0;
        }
        g = h->f24;
        if (g == 0) {
            return 0;
        }
        g->f16 = 0xC;
        g->f18 = 0xF;
        n = func_3AD390(o, r->f00);
        if (n != 0) {
            v = func_3A05C0(n);
        } else {
            v = func_3F5CA0(r);
        }
        u = r->f03;
        func_291250(w, 0xF, 0, v);
        normal_BtlChgPageSetAbilityTypeIcon_505470(a, 0x14, u);
        normal_BtlChgPageSetAbilityTypeIcon_505470(a, 0x18, -1);
        return 1;
    }
    h = func_290460(w, 0xF);
    if (h == 0) {
        return 0;
    }
    g = h->f24;
    if (g == 0) {
        return 0;
    }
    g->f18 = 0;
    g->f16 = 0;
    func_291250(w, 0xF, 0, 0);
    func_289090(a, 0x14, 0, 0);
    func_289090(a, 0x18, 5, 0);
    func_290B20(w, 0x18, 0, -1, -1, 0);
    return 1;
}
