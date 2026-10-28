/* rgp:protos */
#define RGP_SELF_SpatialMgrListItemNew_315bd0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41a5): arg0 is a byte POINTER (`u8 *`, heap at +4) and the
   allocator's second parameter a `void *`.  As an `s32 arg0 + 4` the first
   call's argument setup came out a1-before-a0 (the old 2-bad residue). */
#include "types.h"

typedef struct Node315bd0 Node315bd0;
struct Node315bd0 {
    Node315bd0 *unk0;
    s32 unk4;
    void *unk8;
};

/*rgp*/

Node315bd0 *SpatialMgrListItemNew_315bd0(u8 *arg0, void ***arg1) {
    void **temp_16;
    void **temp_2;
    Node315bd0 *var_2;

    if (*arg1 == NULL) {
        temp_2 = (void **)MemStackNew_14e230(4, arg0 + 4);
        if (temp_2 != NULL) {
            *temp_2 = NULL;
        }
        *arg1 = temp_2;
    }
    temp_16 = *arg1;
    if (temp_16 != NULL) {
        var_2 = (Node315bd0 *)MemStackNew_14e230(0xC, arg0 + 4);
        if (var_2 != NULL) {
            var_2->unk0 = NULL;
            var_2->unk4 = 0;
            var_2->unk8 = NULL;
        }
        if (var_2 != NULL) {
            var_2->unk8 = *temp_16;
            *temp_16 = var_2;
        }
        return var_2;
    }
    var_2 = NULL;
    return var_2;
}
