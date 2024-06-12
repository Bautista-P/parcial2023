
#include <stdio.h>

typedef struct node
{
   char* elem;
   struct node * tail;

}TNode;

typedef TNode * TList;


int
main(void)
{


}


int countGroups(TList l, char * elem)
{
    if(l == NULL)
        return 0;
    TList aux = countGroups(l->tail , elem);
    if((l->elem == elem && l->tail == NULL) ||(l->elem == elem && l->tail->elem != elem))
        return 1 + aux;
    return aux;
}