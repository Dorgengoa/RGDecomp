/* rgp:protos */
#define RGP_SELF_DebugMenuWidgetShouldDrawWindowMaybe_209eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00209eb0 {
    u8 pad0[0x2A];
    u16 unk2A;
} S00209eb0;

/*rgp*/
/*rgp*/

s32 DebugMenuWidgetShouldDrawWindowMaybe_209eb0(S00209eb0 *unused)
{
    S00209eb0 *node;

    node = ((S00209eb0 *)DebugMenuWidgetGetCurrentChild_209dd0((void *)unused));
    if (node == NULL) {
        return 1;
    }
    if (!(node->unk2A & 0x40)) {
        return 1;
    }
    if (((unsigned char)DebugMenuWidgetHasFlag2_209e50(node)) != 0) {
        return DebugMenuWidgetShouldDrawWindowMaybe_209eb0(node);
    }
    return 0;
}
