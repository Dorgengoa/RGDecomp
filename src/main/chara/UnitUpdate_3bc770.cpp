#include "types.h"

class Sub {
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
    virtual void f74(f32);
    u8 pad4[0x24 - 4];
};

class Obj {
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
    virtual s32 fC0();
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
    virtual void f2B0(s32, s32, s32);
    u8 pad4[0x1EC - 4];
    f32 m1EC;
    u8 pad1F0[0x234 - 0x1F0];
    u8 *m234;
    u8 pad238[0x278 - 0x238];
    Sub m278[8];
    u8 pad398[0x40C - 0x398];
    f32 m40C;
};

extern "C" {
extern s32 UnitBaseUpdate_3b0bf0(Obj *, f32);
extern s32 CharaSysHasEncounterRecMaybe_3a3950(u8 *);
extern s32 CharaSysStateFlag24Bit2Related_3a3880(u8 *);
extern f32 RandFloat_13c010(void);
extern u8 D_0045B078[0x400];
extern u8 *D_00483818;
}

extern "C" s32 UnitUpdate_3bc770(Obj *self, f32 dt) {
    s32 i;
    f32 lim;
    f32 k;
    f32 w;
    u8 *e;

    if (D_00483818 == NULL) {
        return 0;
    }
    if (!(*(*(u8 **)(D_00483818 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (self->fC0() != 0) {
        return 0;
    }
    if (!(UnitBaseUpdate_3b0bf0(self, dt) & 0xFF)) {
        return 0;
    }
    i = 0;
    do {
        self->m278[i].f74(dt);
        i++;
    } while (i < 8);
    if (self->m234 != NULL) {
        k = *(f32 *)D_0045B078;
        lim = self->m1EC / k / 2.0f;
        if (CharaSysHasEncounterRecMaybe_3a3950(*(u8 **)(D_00483818 + 0x20)) == 0 || CharaSysStateFlag24Bit2Related_3a3880(*(u8 **)(D_00483818 + 0x20)) != 0) {
            w = (f32)*(s16 *)(self->m234 + 0x8C);
            if (!(w <= 0.0f) && !((f32)*(s16 *)(self->m234 + 0x8E) <= 0.0f) && !(w <= 0.0f) && !(lim < w) &&
                !(dt <= k * RandFloat_13c010())) {
                k = 60.0f - 60.0f * ((f32)*(s16 *)(self->m234 + 0x8E) / 100.0f);
                if (!(1.0f <= k * RandFloat_13c010())) {
                    self->f2B0(0, 1, 0);
                }
            }
        }
    }
    w = self->m40C;
    if (!(w <= 0.0f)) {
        w = w - dt;
        self->m40C = w;
        if (w < 0.0f) {
            self->m40C = 0.0f;
        }
    }
    return 1;
}
