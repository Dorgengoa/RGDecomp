#include "types.h"

extern void EntrySetGroupId_3238e0(s32 *a, s32 b);
extern void EntrySetExploredOffset_323900(s32 *a, s32 b);
extern void EntrySetName_323910(s32 *a, s32 b);
extern void EntrySetBlockName_323960(s32 *a, s32 b);
extern void EntrySetGridSize_323bd0(s32 *a, s32 b, s32 c);
extern void EntrySetPair20Related_323be0(s32 *a, s32 b, s32 c);
extern void EntrySetRange_323bf0(s32 *a, f32 b, f32 c);
extern void EntrySetOrigin_323c00(s32 *a, f32 b, f32 c);
extern void EntrySetScale_323c10(s32 *a, f32 b);

void EntryReset_323c20(s32 *arg0) {
    EntrySetGridSize_323bd0(arg0, 0, 0);
    EntrySetScale_323c10(arg0, 0.0f);
    EntrySetOrigin_323c00(arg0, 0.0f, 0.0f);
    EntrySetRange_323bf0(arg0, 0.0f, 0.0f);
    EntrySetPair20Related_323be0(arg0, 0, 0);
    *arg0 = 0;
    EntrySetBlockName_323960(arg0, 0);
    EntrySetName_323910(arg0, 0);
    EntrySetExploredOffset_323900(arg0, 0);
    EntrySetGroupId_3238e0(arg0, -1);
}
