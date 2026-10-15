/* MATCHED -- session 32, lane nc32d.  204 words, 0 bad, BYTE-IDENTICAL.
 * Closed on ONE word pair via mwcc-branch-likely-duplication FIX 3 read from
 * the other side: the residue was @0x004FD98C ours `bnel $16,$2 / addiu $2,$0,1`
 * (threaded, target bumped past the shared tail) where retail has the plain
 * `bne $16,$2,.L004FDC28 / nop`.  mwcc threads only the FIRST predecessor of a
 * shared `return K` block; the early explicit `return 1;` in the r == 2 arm was
 * compiled as its OWN return block, so the r != 1 test became the first
 * predecessor and stole the threaded slot.  Making that early exit a
 * `goto done;` to the ONE shared `return 1` hands the threading back to it and
 * every later predecessor gets the plain branch + nop.
 * Deck: 6 arms, 1 round trip, identity arm reproduced the 2-bad baseline.
 * Four other spellings are the SAME object (71dcab2b7ec1): else-if with a
 * single trailing return, else-if + goto, goto + `if (r != 1) goto done;`
 * flattened, and `done: ; return 1;`.  The declaration order below is s31's
 * best (it took the unit 29 -> 22 -> 11 -> 2 bad) and must not be disturbed. */
#include "types.h"
/* normal 0x004FD920 -- the item/skill target confirm step of the field menu.
 * func_28E170 runs the cursor, mode 2 backs out to 0x5606, mode 1 confirms:
 * it re-reads the selected roster slot out of D_00527910[D_0048051C], builds
 * the aim matrix (func_3A7940/func_3A7430 + virtual slot 158) for the caster,
 * fires it through func_2EEF60 and then plays either the 0x4A or the 0x6 SE
 * depending on the byte func_2EEF60 wrote back.
 *
 * TWO `lw $25,0($x) / lw $25,K($25) / jalr $25` sites -> C++ virtual, vptr 0,
 * slots (0x280-8)/4 = 158 and (0xBC-8)/4 = 45.  Same Ent class, same
 * func_3A7940/func_3A7430/func_2EEF60 aim block, as normal_BtlChgMenuItemListState_4ff6c0.
 * `daddiu $3,$0,1` for the 0x40DA..0x40DF range flag is a C++ `bool` -- no
 * integer width reaches the `daddiu`.
 * `lui $5,0x4B / addiu $5,$5,0x2570` is a SYMBOL reference (D_004B2570), not
 * an integer constant: `lui/ori` would be the integer spelling. */

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
    virtual s32  kind();                           /* slot 45 -> vtable +0xBC */
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
    virtual void aim(void *m);                     /* slot 158 -> vtable +0x280 */
    u8   pad04[0x0C - 4];
    s32  f0C;
};

typedef struct Slot { s32 f00; s32 f04; s32 f08; s16 f0C; s16 f0E; } Slot;
typedef struct Info { s16 f00; } Info;
typedef struct Obj  { u8 pad00[4]; s16 f04; u8 pad06[0x10 - 6]; Info *f10; } Obj;
typedef struct Cur  { u8 pad00[0x10]; s16 f10; } Cur;
typedef struct Hdl  { u8 pad00[0x14]; s16 f14; s16 f16; u8 pad18[2]; s16 f1A; } Hdl;
typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;
typedef struct Ctx  { u8 pad000[0x44E]; s16 f44E; } Ctx;

extern const u8 D_004B2570[];
extern const u8 D_005278E0[];
extern Slot     D_00527910[];

extern s16   D_0048051C;          /* gp - 0x4C54 */
extern s32   D_00480500;          /* gp - 0x4C70 */
extern s32   D_00480504;          /* gp - 0x4C6C */
extern s32   D_00480508;          /* gp - 0x4C68 */
extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */

extern "C" {

extern void *func_1B81C0(void);
extern void  func_1B9520(void *h, s32 id, void *p, f32 v);
extern void *func_1D07B0(s32 a);
extern s32   func_1F5BE0(void);
extern Root *func_1FEDE0(void);
extern void *func_207DF0(void);
extern void  func_28DB40(const u8 *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern s32   func_28E170(void *w, const u8 *p, s32 c, s32 d);
extern Hdl  *func_28EA40(void *w, s32 id);
extern Cur  *func_28EC60(void *w);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern void  func_2EEF60(s32 a, void *m, void (*fn)(void *), s32 c, u8 *d);
extern void  func_3A7430(void *m, s32 a, s16 b, s32 c);
extern void  func_3A7940(void *m);
extern s32   func_3C2010(s32 w, s32 a, s32 b);
extern Ent  *func_3C2820(s32 w);
extern Ent  *func_3C2FB0(s32 w, s32 k);
extern s32   func_3C3120(s32 w, s16 k);
extern Obj  *func_3C8370(s32 w, s32 id, s32 c, s32 d, s32 e, s32 f);
extern s32   func_3D4F00(Obj *o);
extern void  normal_FieldHudItemUseFeedbackSeCb_4f2aa0(void *p);
extern void  normal_FieldHudItemUseSeReset_4f2d40(void);
extern void  normal_BtlChgMenuItemGridLayout_5000b0(void);
extern void  normal_BtlChgMenuItemListBuild_5002f0(void);
extern s32   normal_BtlChgPageGetMember_505f90(void *p);

}

extern "C" s32 normal_BtlChgMenuItemTargetSelectState_4fd920(void)
{
    u8    flag;
    s32   m[0x1B];
    s32   k;
    Root *t;
    Obj  *o;
    Ent  *v;
    s32   id;
    s16   n;
    Cur  *q;
    s32   r;
    void *h;
    s32   sfx;
    Ent  *e;
    bool  ok;

    r = func_28E170(D_004844A0, D_004B2570, 1, 0);
    q = func_28EC60(D_004844A0);
    if (r == 2) {
        func_28EDE0(D_00484498, 0x5606, 0);
        goto done;
    }
    if (r == 1) {
        t = func_1FEDE0();
        if (t == 0) {
            return 0;
        }
        v = func_3C2FB0(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
        if (v != 0) {
            o = func_3C8370(t->f18, D_00527910[D_0048051C].f00, 0, -1, 0, 0);
            if (o != 0) {
                n = o->f04;
                k = o->f10->f00;
                func_3C2010(t->f18, 1, 1);
                id = -1;
                if (func_3D4F00(o) == 0) {
                    id = func_3C3120(t->f18, q->f10);
                }
                func_3A7940(m);
                func_3A7430(m, v->f0C, n, 0);
                v->aim(m);
                flag = 0;
                normal_FieldHudItemUseSeReset_4f2d40();
                func_2EEF60(id, m, normal_FieldHudItemUseFeedbackSeCb_4f2aa0, 0, &flag);
                ok = true;
                if ((u32)(k - 0x40DA) < 6U) {
                    ok = false;
                }
                if (ok) {
                    sfx = func_1F5BE0();
                    if (flag != 0) {
                        h = func_1D07B0(sfx);
                        func_1B9520(h, 0x4A, func_1B81C0(), 1.0f);
                    } else {
                        h = func_207DF0();
                        func_1B9520(h, 6, func_1B81C0(), 1.0f);
                    }
                }
                normal_BtlChgMenuItemListBuild_5002f0();
                normal_BtlChgMenuItemGridLayout_5000b0();
                if (D_00484454->f44E != 0) {
                    e = func_3C2820(t->f18);
                    if (e != 0 && e->kind() != 0) {
                        D_00484454->f44E = 0;
                    }
                }
                {
                    Hdl *g = func_28EA40(D_004844A0, 0x55F3);
                    g->f1A = 0;
                    g->f16 = 0;
                    g->f14 = 0;
                }
                D_00480508 = 0;
                D_00480504 = 0;
                D_00480500 = 0;
                func_28DB40(D_005278E0, 0x28, 0x19, 0x17, 0x2A, 0x30, 0x2B, 0xD1);
                func_290F60(D_0048449C, 0x29, 0x46, 0x46);
                func_290F60(D_0048449C, 0x26, 0x1A, 0x1D);
                func_290F60(D_0048449C, 0x27, 0x3C, 0x37);
                func_290F60(D_0048449C, 0x25, 0x183, 0x1E);
                func_28EDE0(D_00484498, 0x5606, 0);
            }
        }
    }
done:
    return 1;
}
