#include "types.h"

typedef struct S00209eb0 {
    u8 pad0[0x2A];
    u16 unk2A;
} S00209eb0;

extern S00209eb0 *DebugMenuWidgetGetCurrentChild_209dd0(void);
extern s32 DebugMenuWidgetHasFlag2_209e50(S00209eb0 *);

s32 DebugMenuWidgetShouldDrawWindowMaybe_209eb0(S00209eb0 *unused)
{
    S00209eb0 *node;

    node = DebugMenuWidgetGetCurrentChild_209dd0();
    if (node == NULL) {
        return 1;
    }
    if (!(node->unk2A & 0x40)) {
        return 1;
    }
    if (DebugMenuWidgetHasFlag2_209e50(node) != 0) {
        return DebugMenuWidgetShouldDrawWindowMaybe_209eb0(node);
    }
    return 0;
}
