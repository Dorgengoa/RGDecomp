/* rgp:protos */
#define RGP_SELF_ListAppendNew_18e090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T_FUN_0018e090 T_FUN_0018e090;

typedef struct Obj_FUN_0018e090 {
    T_FUN_0018e090 *f00;
} Obj_FUN_0018e090;

/*rgp*/
/*rgp*/
/*rgp*/

T_FUN_0018e090 *ListAppendNew_18e090(Obj_FUN_0018e090 *o, s32 flag)
{
    T_FUN_0018e090 *m;

    if (flag == 0) {
        return (T_FUN_0018e090 *)0;
    }
    m = ((T_FUN_0018e090 *)MemStackNew_14e230(0x18, (void *)flag));
    if (m != 0) {
        m = ((T_FUN_0018e090 *)ListNodeCtor_18e1a0(m, 0, 0, 0));
    }
    if (m == 0) {
        return (T_FUN_0018e090 *)0;
    }
    if (o->f00 == 0) {
        o->f00 = m;
    } else {
        ListLinkAtTail_18e110(o->f00, m);
    }
    return m;
}
