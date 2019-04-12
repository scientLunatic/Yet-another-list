#ifndef YET_ANOTHER_LIST_H_INCLUDED
#define YET_ANOTHER_LIST_H_INCLUDED

  #include <stdlib.h>

  #define newYAListNode (struct YALIST_NODE*)calloc(1, sizeof(YALIST_NODE))
  #define newYAList (struct YALIST*)calloc(1, sizeof(YALIST))

  #ifndef is_null
    #define is_null(pointer) (!pointer)
  #endif // is_null

  #define is_yalist_empty(yet_another_list) is_null(yet_another_list) || is_null(yet_another_list->head)

  #ifndef wrap_around
    #define wrap_around(var, range) (var + range) % range
  #endif // wrap_around

  #ifdef __cplusplus
  extern "C" {
  #endif //__cplusplus

    struct YALIST_NODE{
      void* el;
      struct YALIST_NODE* next[2];//!<next[0] = right<br>   next[1] = left, previous
    };

    typedef struct YALIST_NODE YALIST_NODE;

    struct YALIST{
      YALIST_NODE* head;
      int length;
    };

    typedef struct YALIST YALIST;

    YALIST* new_yalist();
      YALIST_NODE* yalnofetch(YALIST* l, int i);
      int yaladd(YALIST* l, void* item, int index);
      int yalrem(YALIST* l, int index);

      int yalnoset(YALIST_NODE* n, void* el, YALIST_NODE* next, YALIST_NODE* prev);
      int yaledit(YALIST* l, int index, void* item);
      int yalfind(YALIST* l, void* item, int* index);

      void* yalget(YALIST* l, int index);
      void* yaltake(YALIST* l, int index);


      int yalclear(YALIST* l);
  #ifdef __cplusplus
  }
  #endif //__cplusplus

    #define yalpush(YAList, item) yaladd(YAList, item, 0)
    #define yalpop(YAList) yaltake(YAList, 0)
    #define yalenqueue(YAList, item) yaladd(YAList, item, YAList->length - 1)
    #define yaldequeue(YAList) yaltake(List, 0)

  #define for_each_yalist(item, list, iterator) \
    for(iterator = 0, item = list->head; iterator < list->length; iterator++, item = item->next[0])


#endif // YET_ANOTHER_LIST_H_INCLUDED
