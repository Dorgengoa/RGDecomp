/* rgp:protos */
#define RGP_SELF_FrameFindByName_149ed0 1
#define RGP_SELF_level0 1
#define RGP_SELF_level1 1
#define RGP_SELF_level2 1
#define RGP_SELF_level3 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    s32 key;
    s32 pad4;
    struct Node *child;
    struct Node *next;
} Node;

/*rgp*/

/*rgp*/
/*rgp*/
extern Node *FrameFindByName_149ed0(Node*,s32);
#pragma auto_inline off
#pragma inline_depth(20)
static inline Node *level0(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=((Node *)FrameGetChild_149cf0(n));c!=0;c=((Node *)FrameGetNext_149ce0(c))){r=FrameFindByName_149ed0(c,key);if(r!=0)return r;}return 0;}
static inline Node *level1(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level0(c,key);if(r!=0)return r;}return 0;}
static inline Node *level2(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level1(c,key);if(r!=0)return r;}return 0;}
static inline Node *level3(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level2(c,key);if(r!=0)return r;}return 0;}
Node *FrameFindByName_149ed0(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level3(c,key);if(r!=0)return r;}return 0;}
