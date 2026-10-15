#include "types.h"

typedef struct Node_0028ea40 {
    u16 tag;   /* +0x0 */
} Node_0028ea40;

typedef struct Entry_0028ea40 {
    Node_0028ea40 *node;   /* +0x0 */
    u8 pad[0x1C];
} Entry_0028ea40;   /* sizeof 0x20 */

typedef struct Obj_0028ea40 {
    u8 pad0[0x4];
    Entry_0028ea40 *unk4;   /* +0x4 */
} Obj_0028ea40;

Entry_0028ea40 *UiEntryListFindByTag_28ea40(Obj_0028ea40 *arg0,s32 arg1){Entry_0028ea40*e;Node_0028ea40*n;s32 tag;e=arg0->unk4;if(!e)return 0;while((n=e->node)!=0){tag=n->tag;if(tag!=0&&(u16)tag==(u16)arg1)return e;e++;}return 0;}
