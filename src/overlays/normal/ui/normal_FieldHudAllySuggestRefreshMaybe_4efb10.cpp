#include "types.h"
/* normal 0x004EFB10 -- retargets the 0x71.. widget row of screen `o` when its
 * 0x398 page id still matches `k`.  The active entity's slot-303 count is
 * clamped to 3, used to pick a layout id out of D_005262D6, and the resulting
 * record's 0x08 handle is written into every widget whose per-slot 0x39A state
 * is 2.
 *
 * C++ virtuals: 0x4C4 -> slot 303, 0x70 -> slot 26.
 * `daddiu $18,$0,0x71` plus the `andi 0xFFFF` wrap is a `u16` widget id.
 * ⚠ THE WHOLE RESIDUE WAS THE WIDGET ID, and it took THREE stacked levers:
 *   1. `u16 id` (not s32) -- a REGISTER-RESIDENT u8/u16 destination is what
 *      selects `daddiu $18,$0,0x71`; s32/u32/s64 all give `addiu`
 *      (levers.d/mwcc-daddiu-unsigned-narrow).
 *   2. `id++`, NOT `id = (u16)(id + 1)` -- with a u16 destination the cast is
 *      a SECOND narrowing and mwcc emits TWO `andi 0xFFFF` (one word long).
 *      `id = id + 1` gives the same object as the cast; `id++`/`++id`/`id += 1`
 *      are one object and the right length.
 *   3. func_290460's SECOND PARAMETER declared `u16` -- with an `s32` param the
 *      u16->int promotion masks AGAIN at the call (`andi $5,$18,0xFFFF` in the
 *      loop-back delay slot) where retail passes a bare `daddu $5,$18,$0`.
 *      `s16` goes one word long, `u32` is identical to `s32`
 *      (levers.d/pk-callee-param-width).
 *   Arms 1 and 2 alone read as 2 bad words that look like a SCHEDULING swap of
 *   two delay slots -- it is not scheduling, it is the mask.
 */
struct Rec;
class Ent {
public:
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
    virtual Rec *find(s16 k);
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
    virtual void s224();
    virtual void s225();
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
    virtual void s239();
    virtual void s240();
    virtual void s241();
    virtual void s242();
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual void s249();
    virtual void s250();
    virtual void s251();
    virtual void s252();
    virtual void s253();
    virtual void s254();
    virtual void s255();
    virtual void s256();
    virtual void s257();
    virtual void s258();
    virtual void s259();
    virtual void s260();
    virtual void s261();
    virtual void s262();
    virtual void s263();
    virtual void s264();
    virtual void s265();
    virtual void s266();
    virtual void s267();
    virtual void s268();
    virtual void s269();
    virtual void s270();
    virtual void s271();
    virtual void s272();
    virtual void s273();
    virtual void s274();
    virtual void s275();
    virtual void s276();
    virtual void s277();
    virtual void s278();
    virtual void s279();
    virtual void s280();
    virtual void s281();
    virtual void s282();
    virtual void s283();
    virtual void s284();
    virtual void s285();
    virtual void s286();
    virtual void s287();
    virtual void s288();
    virtual void s289();
    virtual void s290();
    virtual void s291();
    virtual void s292();
    virtual void s293();
    virtual void s294();
    virtual void s295();
    virtual void s296();
    virtual void s297();
    virtual void s298();
    virtual void s299();
    virtual void s300();
    virtual void s301();
    virtual void s302();
    virtual s32 s303();
};

typedef struct Scr  { u8 pad000[0x398]; s16 f398; s16 f39A[6]; s16 f3A6; } Scr;
typedef struct Slot { u8 pad00[4]; s32 f04; } Slot;
typedef struct Wid  { u8 pad00[0x28]; Slot *f28; } Wid;
typedef struct Rec  { u8 pad00[8]; s32 f08; } Rec;
typedef struct Own  { u8 pad00[0x14]; void *f14; } Own;
typedef struct Box  { u8 pad00[8]; Ent *f08; } Box;
typedef struct Src  { u8 pad00[0x44]; Box *f44; } Src;

extern const s16 D_005262D6[];

extern "C" {
extern Own  *func_1FEDE0(void);
extern Src  *func_1FEDF0(void);
extern Ent  *func_3A8C60(void *a, s16 k);
extern Wid  *func_290460(Scr *p, u16 id);
}

extern "C" void normal_FieldHudAllySuggestRefreshMaybe_4efb10(Scr *o, s32 k)
{
    Own  *a;
    Src  *b;
    Ent  *t;
    Rec  *m;
    Wid  *h;
    Slot *w;
    s32   n;
    u16   id;
    s32   i;

    if (o->f39A[4] == 0) {
        return;
    }
    if (o->f398 != k) {
        return;
    }
    a = func_1FEDE0();
    b = func_1FEDF0();
    t = func_3A8C60(a->f14, o->f398);
    if (t == 0) {
        return;
    }
    n = t->s303();
    if (n <= 0) {
        return;
    }
    if (n > 3) {
        n = 3;
    }
    m = b->f44->f08->find(D_005262D6[n]);
    if (m == 0) {
        return;
    }
    id = 0x71;
    for (i = 0; i < o->f3A6; i++) {
        h = func_290460(o, id);
        if (h != 0) {
            w = h->f28;
            if (w != 0) {
                if (o->f39A[i] == 2) {
                    w->f04 = m->f08;
                }
            }
        }
        id++;
    }
}
