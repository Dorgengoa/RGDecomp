#include "types.h"

typedef struct Node {
    s32 key;
    s32 pad4;
    struct Node *child;
    struct Node *next;
} Node;

extern s32 NameEqualBeforeDashes_14a050(s32, s32);

extern Node *FrameGetChild_149cf0(Node*);
extern Node *FrameGetNext_149ce0(Node*);
extern Node *FrameFindByName_149ed0(Node*,s32);
#pragma auto_inline off
#pragma inline_depth(20)
static inline Node *level0(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=FrameGetChild_149cf0(n);c!=0;c=FrameGetNext_149ce0(c)){r=FrameFindByName_149ed0(c,key);if(r!=0)return r;}return 0;}
static inline Node *level1(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level0(c,key);if(r!=0)return r;}return 0;}
static inline Node *level2(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level1(c,key);if(r!=0)return r;}return 0;}
static inline Node *level3(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level2(c,key);if(r!=0)return r;}return 0;}
Node *FrameFindByName_149ed0(Node*n,s32 key){Node *c,*r;if(NameEqualBeforeDashes_14a050(n->key,key)!=0)return n;for(c=n->child;c!=0;c=c->next){r=level3(c,key);if(r!=0)return r;}return 0;}
