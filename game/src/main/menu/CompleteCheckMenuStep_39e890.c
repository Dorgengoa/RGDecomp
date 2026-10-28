/* rgp:protos */
#define RGP_SELF_CompleteCheckMenuStep_39e890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Info39e890 {
    u8 pad00[4];
    s32 f4;         /* 0x04 */
    u8 pad08[2];
    u16 fA;         /* 0x0A */
} Info39e890;

typedef struct Bit39e890 {
    u8 b0 : 1;
    u8 pad[15];
} Bit39e890;

extern s16 D_004836A8;
extern u8 D_004836A4;
extern s16 D_004836AC;
extern s16 D_0047FFD0;
extern s32 D_00483688;
extern s32 D_00483694;
extern s32 D_00483698;
extern s16 D_00483690;

extern u8 D_004E96B0[0x20];
extern struct BigB8 { s32 v; s32 pad[3]; } D_004E96B8;
extern u8 D_004E96D0[0x18];
extern struct BigE8 { s32 v; s32 pad[3]; } D_004E96E8;
extern Bit39e890 D_004E96F0;
extern struct BigF1 { s8 v; s8 pad[15]; } D_004E96F1;
extern u8 D_004B2570[0x10];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CompleteCheckMenuStep_39e890(void)
{
    s32 h;
    s32 id;
    u64 t;
    Info39e890 *o;

    if (D_004836A8 != 0) {
        if (D_004836A4 != 0) {
            h = ((s32)GetMenuResGroup_206a40());
            o = ((Info39e890 *)ResGroupListFindById_42c500(h, 2));
            id = o->f4;
            t = ((u64)o->fA << 0x30) >> 0x32;
            UiWidgetListReset_2912e0(D_004E96B0);
            UiInitWidgetPool_290390(D_004E96B0, D_00483688, (int)(t));
            UiAddWidgets_2901d0(D_004E96B0, id, 0);
            D_004E96B8.v = 0x32D;
            UiTextStyleReset_290450();
            o = ((Info39e890 *)ResGroupListFindById_42c040(h, 2));
            id = o->f4;
            t = ((u64)o->fA << 0x30) >> 0x32;
            UiEntryListReset_28ec80(D_004E96D0);
            UiEntryListAlloc_28e0c0(D_004E96D0, D_00483688, (int)(t));
            UiEntryListLoad_28eb70(D_004E96D0, id, D_004E96B0);
            D_004E96E8.v = SceneSoundGetSlot0HandleCur_207df0();
            D_00483694 = 0;
            D_00483698 = 0;
            D_004E96F0.b0 = 0;
            D_004E96F1.v = 0;
            D_00483690 = 0;
            D_00483698 = MenuStateTableForId_42c950(h, 2);
            PadClearRepeatAll_183960(D_004B2570);
            PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
            PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
            D_004836A4 = 0;
        }
        if (D_004836AC == 1 && D_0047FFD0 == 1) {
            D_004836A8 = 2;
            D_0047FFD0 = 0;
            StateMachineSetState_28ede0(&D_00483690, 0x7531, 1);
        }
        CompleteCheckResPoll_39eb80();
        if (D_004836A8 == 2) {
            UiUpdateWidgets_2913a0(D_004E96B0);
            UiUpdateWidgets_2913a0(D_004E96B0);
            StateMachineUpdate_28ed70(&D_00483690);
        }
    }
}
