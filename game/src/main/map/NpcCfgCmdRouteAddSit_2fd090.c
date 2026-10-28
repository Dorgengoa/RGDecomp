/* rgp:protos */
#define RGP_SELF_NpcCfgCmdRouteAddSit_2fd090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Entry002fd090 Entry002fd090;
struct Entry002fd090 {
    u8 pad0[0x20];
    Entry002fd090 *unk20;
    s16 unk24;
    s16 unk26;
    u8 pad28[0x2E];
    s16 unk56;
};

extern s32 D_004E6628[0x10];
extern Entry002fd090 *D_004E662C[0x10];
extern s16 D_004E6632[0x10];
extern s16 D_004E6634[0x10];
/*rgp*/

s32 NpcCfgCmdRouteAddSit_2fd090(s32 arg0, s32 arg1) {
    Entry002fd090 *entry;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004E6628[0] == 0) {
        return 0;
    }
    if (D_004E6634[0] != 0) {
        return 0;
    }
    D_004E662C[0]->unk26 = 1;
    D_004E662C[0]->unk24 = VariantGetInt_15f780(arg0);
    D_004E662C[0]->unk20 = (Entry002fd090 *)((u8 *)D_004E662C[0] + 0x30);
    entry = D_004E662C[0];
    D_004E662C[0] = (Entry002fd090 *)((u8 *)D_004E662C[0] + 0x30);
    D_004E6632[0] += 1;
    entry->unk56 = 5;
    D_004E662C[0]->unk20 = NULL;
    return 1;
}
