#include "types.h"
/* normal 0x00504030 -- the 0x4F/0x4B/0x4D widget triple for one roster slot.
 *
 * FIVE `jalr $25` sites, so this is C++ VIRTUAL DISPATCH and the unit is a
 * .cpp (see levers.d/jalr-is-cpp-virtual.md).  Every vptr load here is
 * `lw $25,0x0($obj)` -> vptr offset 0, and slot = 8 + 4*N:
 *   0x4C  -> 17    0x60  -> 22    0x388 -> 224   0x38C -> 225   0x3C4 -> 239
 * so the placeholder class carries 240 declared-and-never-defined virtuals.
 * The class is never constructed, so no vtable lands in the object.
 *
 * The data side of the same objects is reached through a separate `ObjD`
 * view rather than data members inside the virtual class -- the vptr must
 * stay at offset 0 and the cast costs nothing.
 *
 * `(x % 8) * 32` / `(x / 8) * 32` are the andi-7 + `-8` correction and the
 * sra-3 + `+7` correction; both are plain SIGNED % and / by 8.
 * D_005259C0 is copied halfword-at-a-time into a 0x21-entry stack table
 * (11 rows of 3), and the search runs over the first 10 rows only. */

struct Obj {
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
    virtual void s017(void *dst);  /* slot 17 -> vtable +0x4C */
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual s32 s022();  /* slot 22 -> vtable +0x60 */
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
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual Obj *s224();  /* slot 224 -> vtable +0x388 */
    virtual Obj *s225();  /* slot 225 -> vtable +0x38C */
    virtual void s226();
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual void s234();
    virtual void s235();
    virtual void s236();
    virtual void s237();
    virtual void s238();
    virtual Obj *s239();  /* slot 239 -> vtable +0x3C4 */
};

typedef struct Info {
    u8   pad000[2];
    s8   f002;
    u8   pad003[0x2E - 3];
    s16  f02E;
} Info;

typedef struct ObjD {
    u8    pad000[0x10];
    Info *f010;
} ObjD;

typedef struct Host {
    u8    pad000[0x7C];
    Obj  *f07C[1];
    u8    pad080[0x450 - 0x80];
    s16   f450;
    s16   f452;
} Host;

typedef struct W {
    u8   pad000[4];
    s16  f004;
    s16  f006;
    s16  f008;
    s16  f00A;
    s16  f00C;
    s16  f00E;
    u8   pad010[0xC];
    u16  f01C;
    u8   pad01E[6];
    s16  f024;
    s16  f026;
    s16  f028;
    s16  f02A;
    s16  f02C;
    s16  f02E;
    u8   pad030[0xC];
    u16  f03C;
} W;

typedef struct T {
    u8    pad000[4];
    void *f004;
    u8    pad008[0xC];
    void *f014;
    u8    pad018[0xC];
    void *f024;
} T;

typedef struct Head {
    u8   pad000[0x2C];
    s16  f02C;
} Head;

extern const s16 D_005259C0[];
extern s32       D_0044B710[][2];
extern "C" void *D_00481BBC;          /* gp - 0x35B4 */

extern "C" void *normal_UiPageGetLayout_289b60(Host *a);
extern "C" Obj  *func_3D4D80(Obj *o, s32 a);
extern "C" Head *func_3AE3E0(Obj *h);
extern "C" W    *func_28FE10(void *ctx, s32 id, s32 a);
extern "C" T    *func_28F620(void *ctx, s32 id, s32 a);
extern "C" s32   func_28AA30(void *p, s32 id);
extern "C" void  func_1343B8(void *dst, s32 a, s32 b);
extern "C" void  func_290AC0(void *ctx, s32 id, s32 v);
extern "C" s32   func_28F400(void *ctx, s32 id, s32 k);
extern "C" void  func_28FCD0(void *ctx, s32 id, s32 v, s32 k);

extern "C" s32 normal_BtlChgPageWeaponConfirmLayout_504030(Host *a, s16 idx);

s32 normal_BtlChgPageWeaponConfirmLayout_504030(Host *a, s16 idx)
{
    s16        buf[0x21];
    const s16 *src;
    s16       *dst;
    s32        n;
    Obj       *o;
    void      *ctx;
    Obj       *h;
    s32        key;
    W         *q;
    W         *u;
    T         *t;
    Obj       *v;
    s32        c;
    s32        x;
    s32        i;
    s32        p1;
    s32        p2;

    src = D_005259C0;
    n = 0x21;
    dst = buf;
    do {
        n--;
        *dst = *src;
        src++;
        dst++;
    } while (n > 0);

    o = a->f07C[idx];
    if (o == NULL) {
        return 0;
    }
    ctx = normal_UiPageGetLayout_289b60(a);
    if (ctx == NULL) {
        return 0;
    }
    h = func_3D4D80(o, 0);
    if (h == NULL) {
        return 0;
    }
    key = func_3AE3E0(h)->f02C;
    q = func_28FE10(ctx, 0x4F, 0);
    if (q == NULL) {
        return 0;
    }
    for (i = 0; i < 0xA; i++) {
        if (key == buf[i * 3]) {
            q->f008 = buf[i * 3 + 1];
            q->f00A = buf[i * 3 + 2];
            q->f00C = 0x36;
            q->f004 = 0x36;
            q->f00E = 0x42;
            q->f006 = 0x42;
            break;
        }
    }
    t = func_28F620(ctx, 0x4B, 0);
    if (t == NULL) {
        return 0;
    }
    func_1343B8((u8 *)a + 0x4D7, func_28AA30(D_00481BBC, 0x5D), h->s022());
    t->f004 = (void *)((s32)a + 0x4D7);
    c = ((ObjD *)o)->f010->f002;
    v = (Obj *)0;
    if (c == 0) {
        v = h->s224();
    } else if (c == 1) {
        v = h->s225();
    } else if (c == 2) {
        v = h->s239();
    }
    if (v == NULL) {
        return 0;
    }
    v->s017((u8 *)a + 0x457);
    o->s017((u8 *)a + 0x497);
    t->f014 = (void *)((s32)a + 0x457);
    t->f024 = (void *)((s32)a + 0x497);
    func_290AC0(ctx, 0x4D, D_0044B710[a->f450][a->f452]);
    u = func_28FE10(ctx, 0x4D, 0);
    if (u == NULL) {
        return 0;
    }
    x = ((ObjD *)v)->f010->f02E;
    u->f004 = 0x28;
    u->f006 = 0x2D;
    u->f00C = 0x20;
    u->f00E = 0x20;
    u->f008 = (x % 8) * 32;
    u->f00A = (x / 8) * 32;
    u->f01C |= 2;
    x = (*(Info **)((u8 *)o + 0x10))->f02E;
    u->f024 = 0x28;
    u->f026 = 0x2D;
    u->f02C = 0x20;
    u->f02E = 0x20;
    u->f028 = (x % 8) * 32;
    u->f02A = (x / 8) * 32;
    u->f03C |= 2;
    p1 = func_28F400(ctx, 0x4B, 1);
    p2 = func_28F400(ctx, 0x4B, 2);
    func_28FCD0(ctx, 0x4A, (p1 / 2 + p2 / 2) / 2 + 0x69, 2);
    return 1;
}
