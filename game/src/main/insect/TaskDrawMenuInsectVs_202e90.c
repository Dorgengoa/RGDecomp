/* rgp:protos */
#define RGP_SELF_TaskDrawMenuInsectVs_202e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* A tail-call thunk into the loaded overlay: `j func_4F3030` with an empty
   delay slot and no argument fixup.  The callee has no listing in
   asm/matchings/main -- it is overlay text -- so w1_arity cannot read its
   arity and every generator refuses the shape.  Its ADDRESS is written in
   its own name, which is what bytecheck's NAME_ADDR resolves. */

void TaskDrawMenuInsectVs_202e90(void)
{
    func_4F3030();
}
