/* rgp:protos */
#define RGP_SELF_SeventhMysteryMenuStep_395260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Info395260 {
    u8 pad00[4];
    s32 f4;         /* 0x04 */
    u8 pad08[2];
    u16 fA;         /* 0x0A */
} Info395260;

typedef struct Bit395260 {
    u8 b0 : 1;
    u8 pad[15];
} Bit395260;

extern s16 D_00483488;
extern u8 D_00483484;
extern s16 D_0048348C;
extern s16 D_0047FF20;
extern s32 D_0048346C;
extern s32 D_00483474;
extern s32 D_00483478;
extern s16 D_00483470;

extern u8 D_004E9550[0x20];
extern struct BigB8 { s32 v; s32 pad[3]; } D_004E9558;
extern u8 D_004E9570[0x18];
extern struct BigE8 { s32 v; s32 pad[3]; } D_004E9588;
extern Bit395260 D_004E9590;
extern struct BigF1 { s8 v; s8 pad[15]; } D_004E9591;
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
extern s32 D_00483468;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void SeventhMysteryMenuStep_395260(void)
{
    s32 h;
    s32 id;
    u64 t;
    Info395260 *o;

    if (D_00483488 != 0) {
        if (D_00483484 != 0) {
            h = ((s32)GetMenuResGroup_206a40());
            o = ((Info395260 *)ResGroupListFindById_42c500(h, 4));
            id = o->f4;
            t = ((u64)o->fA << 0x30) >> 0x32;
            UiWidgetListReset_2912e0(D_004E9550);
            UiInitWidgetPool_290390(D_004E9550, D_0048346C, (int)(t));
            UiAddWidgets_2901d0(D_004E9550, id, 0);
            D_004E9558.v = 0x32D;
            UiTextStyleReset_290450();
            o = ((Info395260 *)ResGroupListFindById_42c040(h, 4));
            id = o->f4;
            t = ((u64)o->fA << 0x30) >> 0x32;
            UiEntryListReset_28ec80(D_004E9570);
            UiEntryListAlloc_28e0c0(D_004E9570, D_0048346C, (int)(t));
            UiEntryListLoad_28eb70(D_004E9570, id, D_004E9550);
            D_004E9588.v = D_00483468;
            D_00483474 = 0;
            D_00483478 = 0;
            D_004E9590.b0 = 0;
            D_004E9591.v = 0;
            D_00483470 = 0;
            D_00483478 = MenuStateTableForId_42c950(h, 4);
            PadClearRepeatAll_183960(D_004B2570);
            PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
            PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
            D_00483484 = 0;
        }
        if (D_0048348C == 1 && D_0047FF20 == 1) {
            D_00483488 = 2;
            D_0047FF20 = 0;
            StateMachineSetState_28ede0(&D_00483470, 0x7531, 1);
        }
        SeventhMysteryResPoll_395560();
        if (D_00483488 == 2) {
            UiUpdateWidgets_2913a0(D_004E9550);
            UiUpdateWidgets_2913a0(D_004E9550);
            StateMachineUpdate_28ed70(&D_00483470);
        }
    }
}
