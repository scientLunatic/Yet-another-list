#include "yet_another_list.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

YALIST* new_yalist()
{
    YALIST* newl = newYAList;
    return newl;
}

YALIST_NODE* yalnofetch(YALIST* l, int i)
{
    if(is_yalist_empty(l)) return NULL;

    YALIST_NODE* seeker = l->head;

    for(i %= l->length; i != 0; i -= (abs(i)/i))
      seeker = seeker->next[(i < 0)];
    return seeker;
}

int yalnoset(YALIST_NODE* n, void* el, YALIST_NODE* next, YALIST_NODE* prev)
{
    return (n)?
                n->el      = el,
                n->next[0] = next,
                n->next[1] = prev,
                1
              :
                0;
}

int yaladd(YALIST* l, void* item, int index)                                  //test, &b, -1
{
    if(is_null(l)) return 0;                                                  //notnull
    YALIST_NODE* n = newYAListNode, *seeker = yalnofetch(l, index+(index < 0));//n = newnode, seeker = head(hopefully, but actually since I'm inserting before, it should be head)
    if(is_null(n)) return 0;                                                  //notnull

    if(is_null(seeker)){                        //Empty head(like my own).    //false
        seeker     = n;                                                       //...
        n->next[1] = n;                                                       //...
        l->head    = n;                                                       //...
    }else if(index == 0)                        //Push.                       //no
        l->head    = n;                                                       //...

    yalnoset(n, item, seeker, seeker->next[1]); //Insert n before seeker      //n = {&b, {seeker, seeker}}

    seeker->next[1]->next[0] = n;                                             //seeker->left->right = n
    seeker->next[1]          = n;                                             //seeker->left = n
    return ++l->length;                                                       //length = 2
}

int yalrem(YALIST* l, int index)//remove at index
{
    if(is_yalist_empty(l)) return 0;

    if(l->length == 1){ //remove only node
        free(l->head);
        l->head = NULL;
        return (l->length = 0);
    }

    YALIST_NODE* seeker = yalnofetch(l, index);

    if(seeker == l->head)
      l->head = l->head->next[0];

    seeker->next[0]->next[1] = seeker->next[1];
    seeker->next[1]->next[0] = seeker->next[0];
    free(seeker);

    return --l->length;
}

void* yalget(YALIST* l, int index)//find at index and return el
{
    YALIST_NODE* seeker = yalnofetch(l, index);

    return (seeker)? seeker->el: NULL;
}

int yalfind(YALIST* l, void* item, int* index)
{
    if(is_null(l->head)) return 0;
    int dump;
    if(is_null(index)) index = &dump;

    YALIST_NODE  *indexWise = l->head,
                 *ctrIdWise = l->head;

    if( indexWise->el == item ){*index =  0;  return 1;}//first

    int i;
    for(i = 1; i <= ((l->length)/2); i++){//worst case middle, but index makes access faster later.
      indexWise = indexWise->next[0];
      ctrIdWise = ctrIdWise->next[1];
      if(indexWise->el == item){*index =  i;  return 1;}
      if(ctrIdWise->el == item){*index = -i;  return 1;}//0xfeeefeee error
    }

    return 0;
}

int yalclear(YALIST* l)
{
    if(l->length == 0) return 0;

    while(l->length > 0)
      yalrem(l, 0);

    return 1;
}

void* yaltake(YALIST* l, int index)//find at index, remove and return el
{
    void* tempElPtr = yalget(l, index);
    yalrem(l, index);

    return tempElPtr;
}

int yaledit(YALIST* l, int index, void* item)
{
    YALIST_NODE* temp = yalnofetch(l, index);

    if(!temp)
      return 0;

    temp->el = item;
    return 1;
}

#ifdef __cplusplus
}
#endif //__cplusplus
