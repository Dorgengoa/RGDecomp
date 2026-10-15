#include "types.h"
#pragma divbyzerocheck on
/* normal 0x0050D540 -- the 0x46/0x47/0x48/0x50/0x67 widget page builder.
 * 357 instructions, frame -0x80.  C++: four `jalr $25` sites, vptr at offset 0.
 *  - func_3D4D80's object: slots 0x388 / 0x38C  = virtuals #224 / #225
 *  - the object those return: slots 0x78 / 0x90 = virtuals #28 / #34
 * `break 0, 7` at 0x0050D9F8 is the divide trap: #pragma divbyzerocheck on.
 * _gp = 0x00485170. */

class VB {
public:
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual s32 v28();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual s32 v34(s32 i);
};

class VA {
public:
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual void v045();
    virtual void v046();
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void v059();
    virtual void v060();
    virtual void v061();
    virtual void v062();
    virtual void v063();
    virtual void v064();
    virtual void v065();
    virtual void v066();
    virtual void v067();
    virtual void v068();
    virtual void v069();
    virtual void v070();
    virtual void v071();
    virtual void v072();
    virtual void v073();
    virtual void v074();
    virtual void v075();
    virtual void v076();
    virtual void v077();
    virtual void v078();
    virtual void v079();
    virtual void v080();
    virtual void v081();
    virtual void v082();
    virtual void v083();
    virtual void v084();
    virtual void v085();
    virtual void v086();
    virtual void v087();
    virtual void v088();
    virtual void v089();
    virtual void v090();
    virtual void v091();
    virtual void v092();
    virtual void v093();
    virtual void v094();
    virtual void v095();
    virtual void v096();
    virtual void v097();
    virtual void v098();
    virtual void v099();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195();
    virtual void v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void v204();
    virtual void v205();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual void v223();
    virtual VB *v224();
    virtual VB *v225();
};

struct Sub2 { u8 pad00[2]; s8 f02; };
struct P    { u8 pad00[0x10]; Sub2 *f10; };
struct Ctl  { P *f00; };
struct Rec  { void *f00; void *f04; u8 pad08[8]; s32 f10; s32 f14; s32 f18;
              s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s16 f30;
              u8 pad32[0xE]; };
struct Ent  { u8 pad00[0xC]; s16 f0C; u8 pad0E[6]; s16 f14; };

extern "C" {
extern void *D_004845CC;            /* _gp - 0xBA4 */
extern void *D_004845C8;            /* _gp - 0xBA8 */
extern void *D_004845D4;            /* _gp - 0xB9C */
extern void *D_004845D0;            /* _gp - 0xBA0 */
extern void *D_004845C4;            /* _gp - 0xBAC */
extern void *D_004845F8;            /* _gp - 0xB78 */
extern Ctl  *D_00484644;            /* _gp - 0xB2C */
extern u8    D_00484640;            /* _gp - 0xB30 */
extern f32   D_0047D460;            /* _gp - 0x7D10 */
extern f32   D_0047D4BC;            /* _gp - 0x7CB4 */
extern f32   D_0047D4C0;            /* _gp - 0x7CB0 */

void  func_291110(void *w, s32 id, s32 a, s32 b);
void  func_290F60(void *w, s32 id, s32 a, s32 b);
void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
void  func_290010(void *w, s32 id, s32 a, s32 b);
void  func_2A0600(void *w, void *v, P *p, s32 a, s32 b, s32 c, s32 d);
void  func_2A0490(void *w, void *v, s32 a, s32 b, s16 *h);
void *func_3D46C0(P *p);
VA   *func_3D4D80(P *p, s32 a);
void  func_28F510(void *w, s32 id, void *a, s32 b);
void *func_28AA30(void *w, s32 id);
void  func_131B60(void *p, s32 c, s32 n);
void *func_28FE10(void *w, s32 id, s32 c);
void *func_28F620(void *w, s32 id, s32 c);
void  func_28D0C0(Rec *r, s32 a, s32 b, s32 c);
s32   func_3CE6E0(Ctl *c);
s32   func_3CE7F0(Ctl *c);
void  func_291250(void *w, s32 id, s32 a, s64 v);
void  func_28F200(void *w, s32 id, s32 x, s32 y, s32 k);
void  func_28FD10(void *w, s32 id, s32 x, s32 y, s32 k);
void  func_28FCD0(void *w, s32 id, s32 a, s32 b);
Ent  *func_28EA40(void *w, s32 id);
void  func_28EDE0(void *w, s32 id, s32 a);
void  normal_ShopMenuBuyItemStatusLayout_50be30(Ctl *c);
s32   normal_ShopMenuBuyQtyPanelLayout_50bb40(Ctl *c);

s32 normal_ShopMenuBuyQtyOpenState_50d540(s32 a0, s32 go)
{
    Rec  r;
    s16  h[6];
    P   *p;
    VA  *a;
    VB  *b;
    Ent *e;
    s32  i;
    s32  t;
    s32  n;
    s32  x;
    s32  c1;
    s32  c2;
    u8   m;
    bool ok;

    if (go != 0) {
        func_291110(D_004845CC, 0x48, 1, 1);
        func_290690(D_004845CC, 0x48, 1.0f, D_0047D460, 0.0f);
        func_290F60(D_004845CC, 0x48, 0x7A, 0x6A);
        func_290690(D_004845C8, 0x2F, 0.0f, D_0047D4BC, -1.0f);
        func_290690(D_004845C8, 0x33, 0.0f, D_0047D4C0, -1.0f);
        func_290690(D_004845CC, 0x50, 1.0f, D_0047D460, 0.0f);
        p = D_00484644->f00;
        if (func_3D46C0(p) != 0) {
            func_290010(D_004845CC, 0x67, 1, -1);
            func_2A0600(D_004845D4, D_004845CC, p, 0x6F, 0x6C, 0x68, 0x6E);
            a = func_3D4D80(p, 1);
            if (a != 0) {
                t = p->f10->f02;
                b = 0;
                if (t == 0) {
                    b = a->v224();
                } else if (t == 1) {
                    b = a->v225();
                }
                h[0] = b->v28();
                for (i = 0; i < 5; i++) {
                    h[i + 1] = b->v34(i);
                }
                func_2A0490(D_004845D4, D_004845CC, 0x6D, 0x6E, h);
            }
            func_290690(D_004845CC, 0x67, 1.0f, D_0047D460, -1.0f);
            func_290F60(D_004845CC, 0x50, 0x3C, 0x100);
            func_290F60(D_004845CC, 0x67, 0xF9, 0x100);
        } else {
            func_290F60(D_004845CC, 0x50, 0xC2, 0x100);
        }
        m = D_00484640;
        ok = false;
        if (m != 0) {
            switch (m) {
            case 1:
                func_28F510(D_004845CC, 0x46, func_28AA30(D_004845F8, 0xD), 0);
                ok = true;
                break;
            case 2:
                func_28F510(D_004845CC, 0x46, func_28AA30(D_004845F8, 0xE), 0);
                ok = true;
                break;
            case 3:
                func_28F510(D_004845CC, 0x46, func_28AA30(D_004845F8, 0xF), 0);
                ok = true;
                break;
            }
        } else {
            func_291110(D_004845CC, 0x46, 0, 1);
        }
        if (ok) {
            func_131B60(&r, 0, 0x34);
            r.f00 = func_28FE10(D_004845CC, 0x46, 0);
            r.f04 = func_28F620(D_004845CC, 0x46, 0);
            r.f10 = 0xBC;
            r.f14 = 0xC;
            r.f18 = 0x10;
            r.f1C = 8;
            r.f20 = 0x46;
            r.f24 = -0x26;
            r.f28 = 0x196;
            r.f2C = 0x104;
            r.f30 = 4;
            func_28D0C0(&r, 0, 0, 0);
            c1 = func_3CE6E0(D_00484644);
            c2 = func_3CE7F0(D_00484644);
            func_291250(D_004845CC, 0x47, 0, c2);
            func_291250(D_004845CC, 0x47, 2, c1);
            s16 v[2] = {0};
            v[1] = -2;
            m = D_00484640;
            switch (m) {
            case 1:
                v[0] = 0x16;
                break;
            case 2:
                v[0] = 0x12;
                break;
            case 3:
                v[0] = 0x21;
                break;
            }
            func_28F200(D_004845CC, 0x47, v[0] + 0x122, v[1] + 0x58, 0);
            func_28F200(D_004845CC, 0x47, v[0] + 0x12E, v[1] + 0x58, 1);
            func_28F200(D_004845CC, 0x47, v[0] + 0x140, v[1] + 0x58, 2);
            func_28FD10(D_004845CC, 0x46, v[0] + 0x12D, v[1] + 0x56, 0xD);
            n = c1;
            x = v[0] + 0x156;
            while (n >= 10) {
                n /= 10;
                x += 10;
            }
            func_28F200(D_004845CC, 0x47, x - 10, v[1] + 0x58, 3);
            func_291110(D_004845CC, 0x46, 1, 1);
            func_290690(D_004845CC, 0x46, 1.0f, D_0047D460, 0.0f);
        }
        func_28FCD0(D_004845CC, 0x50, -1, 9);
        normal_ShopMenuBuyItemStatusLayout_50be30(D_00484644);
        i = normal_ShopMenuBuyQtyPanelLayout_50bb40(D_00484644);
        e = func_28EA40(D_004845D0, 0x7533);
        e->f14 = 1;
        if (i > 0) {
            e->f0C = i;
        } else {
            e->f0C = 0x63;
        }
    }
    func_28EDE0(D_004845C4, 0x7539, 0);
    return 1;
}
}
