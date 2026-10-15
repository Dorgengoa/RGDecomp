#pragma opt_propagation off
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
virtual void v8();
virtual void v12();
virtual void v16();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v32();
virtual void v36();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v52();
virtual void v56();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v72();
virtual void v76();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v92();
virtual void v96();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v112();
virtual void v116();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v132();
virtual void v136();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v152();
virtual void v156();
virtual void v160();
virtual void v164();
virtual void v168();
virtual void v172();
virtual void v176();
virtual void v180();
virtual void v184();
virtual void v188();
virtual void v192();
virtual void v196();
virtual void v200();
virtual void v204();
virtual void v208();
virtual void v212();
virtual void v216();
virtual void v220();
virtual void v224();
virtual void v228();
virtual void v232();
virtual void v236();
virtual void v240();
virtual void v244();
virtual void v248();
virtual void v252();
virtual void v256();
virtual void v260();
virtual void v264();
virtual void v268();
virtual void v272();
virtual void v276();
virtual void v280();
virtual void v284();
virtual void v288();
virtual void v292();
virtual void v296();
virtual void v300();
virtual void v304();
virtual void v308();
virtual void v312();
virtual void v316();
virtual void v320();
virtual void v324();
virtual void v328();
virtual void v332();
virtual void v336();
virtual void v340();
virtual void v344();
virtual void v348();
virtual void v352();
virtual void v356();
virtual void v360();
virtual void v364();
virtual void v368();
virtual void v372();
virtual void v376();
virtual void v380();
virtual void v384();
virtual void v388();
virtual void v392();
virtual void v396();
virtual void v400();
virtual void v404();
virtual void v408();
virtual void v412();
virtual void v416();
virtual void v420();
virtual void v424();
virtual void v428();
virtual void v432();
virtual void v436();
virtual void v440();
virtual void v444();
virtual void v448();
virtual void v452();
virtual void v456();
virtual void v460();
virtual void v464();
virtual void v468();
virtual void v472();
virtual void v476();
virtual void v480();
virtual void v484();
virtual void v488();
virtual void v492();
virtual void v496();
virtual void v500();
virtual void v504();
virtual void v508();
virtual void v512();
virtual void v516();
virtual void v520();
virtual void v524();
virtual void v528();
virtual void v532();
virtual void v536();
virtual void v540();
virtual void v544();
virtual void v548();
virtual void v552();
virtual void v556();
virtual void v560();
virtual void v564();
virtual void v568();
virtual void v572();
virtual void v576();
virtual void v580();
virtual void v584();
virtual void v588();
virtual void v592();
virtual void v596();
virtual void v600();
virtual void v604();
virtual void v608();
virtual void v612();
virtual void v616();
virtual void v620();
virtual void v624();
virtual void v628();
virtual void v632();
virtual void v636();
virtual void v640();
virtual void v644();
virtual void v648();
virtual void v652();
virtual void v656();
virtual void v660();
virtual void v664();
virtual void v668();
virtual void v672();
virtual void v676();
virtual void v680();
virtual void v684();
virtual void v688();
virtual void v692();
virtual void v696();
virtual void v700();
virtual void v704();
virtual void v708();
virtual void v712();
virtual void v716();
virtual void v720();
virtual void v724();
virtual void v728();
virtual void v732();
virtual void v736();
virtual void v740();
virtual void v744();
virtual void v748();
virtual void v752();
virtual void v756();
virtual void v760();
virtual void v764();
virtual void v768();
virtual void v772();
virtual void v776();
virtual void v780();
virtual void v784();
virtual void v788();
virtual void v792();
virtual void v796();
virtual void v800();
virtual void v804();
virtual void v808();
virtual void v812();
virtual void v816();
virtual void v820();
virtual void v824();
virtual void v828();
virtual void v832();
virtual void v836();
virtual void v840();
virtual void v844();
virtual void v848();
virtual void v852();
virtual void v856();
virtual void v860();
virtual void v864();
virtual void v868();
virtual void v872();
virtual void v876();
virtual void v880();
virtual void v884();
virtual void v888();
virtual void v892();
virtual void v896();
virtual s32 get(s32);
};
extern "C" {
#pragma opt_common_subs off

extern s32 EquipSlotGetAbilityAbltName_3a06b0(s32 arg0);
extern s32 EquipSlotGetAbilityWeaponSlot_3a06e0(s32 arg0);
extern s32 CharaSysGetEncounterIdMaybe_3a36d0(s32 arg0);
extern s32 ItemGetWeaponAbltName_3d4f60(s32 arg0);
extern s32 D_0048016C;
extern void *D_00483818;

typedef s32 (*fn384_t)(void *, s32);

s32 CharaGetWeaponAbltName_3acb10(void *arg0, s32 arg1)
{
    s32 temp_2; s32 cmp;
    s32 temp_2_2;
    s32 temp_4;
    s32 var_18;
    void *vtbl;

    void *g=D_00483818;
    if (g == NULL) {
        return 0;
    }
    if ((*(s16 *)((u8 *)arg0 + 4) == 0x2AF9) &&
        (CharaSysGetEncounterIdMaybe_3a36d0(*(s32 *)((u8 *)g + 0x20)) == 0x271B)) {
        return D_0048016C;
    }
    var_18 = 0;
    vtbl = *(void **)((u8 *)arg0 + 0);
    temp_2 = ((Self *)arg0)->get(arg1);
    if (temp_2 != 0) {
        var_18 = ItemGetWeaponAbltName_3d4f60(temp_2);
    }
    temp_4 = *(s32 *)((u8 *)arg0 + 0x498);
    if (temp_4 != 0) { cmp=EquipSlotGetAbilityWeaponSlot_3a06e0(temp_4); if (cmp == arg1) {
        temp_2_2 = EquipSlotGetAbilityAbltName_3a06b0(*(s32 *)((u8 *)arg0 + 0x498));
        if (temp_2_2 != 0) {
            var_18 = temp_2_2;
        }
    }
    } return var_18;
}

}
