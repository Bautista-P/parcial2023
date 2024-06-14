#include "ticketsADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


typedef struct node
{
    char * visitor;
    struct node * next;
}TNode;

typedef TNode * TList;


//los tickets del dia los puedo usar como size a su vez
typedef struct dayly
{
    TList visitors;
    TList begin;
    int tickets;

}dayly;



typedef struct museumTicketCDT
{
    dayly day[366];
    int count;
   
}museumTicketCDT;



/**
 * Reserva los recursos para administrar las ventas de tickets para visitar un museo en
 * un año determinado
 * Nota: Como no se indica el año para el que se lo utilizará se asume que el
 * año será siempre bisiesto
 */
museumTicketADT newMuseumTicket(void)
{
    museumTicketADT aux = calloc(1, sizeof(museumTicketCDT));
    return aux;

}

TList addTicketRec(TList l , const char * visitor, int*flag)
{
    if(l == NULL || strcasecmp(l->visitor, visitor) > 0)
    {
        TList aux = malloc(sizeof(*aux));
        aux->visitor = malloc((strlen(visitor)+1)*sizeof(char));
        strcpy(aux->visitor, visitor);
        aux->next = l;
        *flag = 1;
        return aux;
    }
    if(strcasecmp(l->visitor, visitor) < 0)
    {
        l->next = addTicketRec(l->next, visitor, flag);
    }
    return l;
    
}

/**
 * Se registra un ticket para que #visitor visite el museo el día #dayOfYear del año 
 * Retorna la cantidad actual de tickets registrados para visitar el museo ese día
 * Retorna 0 si #dayOfYear es igual a 0 o mayor a 366
 * Retorna 0 si ya se había registrado un ticket para ese #visitor y 
 * ese #dayOfYear
 */
int addTicket(museumTicketADT m, size_t dayOfYear, const char * visitor)
{
    if (dayOfYear == 0 || dayOfYear > 366)
        return 0;
    int flag = 0;
    m->day[dayOfYear-1].visitors = addTicketRec(m->day[dayOfYear-1].visitors, visitor, &flag);
    m->day[dayOfYear-1].tickets +=flag;
    m->count += flag;
    if(!flag)
        return flag;
    
    return m->day[dayOfYear-1].tickets;
    
    

}

/**
 * Retorna la cantidad de tickets registrados para visitar el museo el día #dayOfYear
 * del año
 * Retorna -1 si #dayOfYear es igual a 0 o mayor a 366
 */
int dayTickets(const museumTicketADT museumTicketADT, size_t dayOfYear)
{
    if(dayOfYear == 0 || dayOfYear > 366)
        return -1;
    return museumTicketADT->day[dayOfYear-1].tickets;
}

/**
 * Retorna la cantidad total de tickets registrados para visitar el museo (todos los
 * días del año)
 */
int yearTickets(const museumTicketADT museumTicketADT)
{
    return museumTicketADT->count;
}

/**
 * Funciones de iteración para poder consultar, para un día #dayOfYear del año,
 * los nombres de los visitantes de los tickets registrados para visitar el museo
 * ese día en orden alfabético por nombre de visitante.
 * IMPORTANTE: Permitir utilizar estas funciones para distintos días del año 
 * EN SIMULTANEO (ver ejemplo en programa de prueba)
 * Abortar si cualquiera de las funciones es invocada con un #dayOfYear igual a 0 
 * o mayor a 366
 */
void toBeginByDay(museumTicketADT museumTicketADT, size_t dayOfYear)
{
    if(dayOfYear == 0 || dayOfYear > 366)
        exit(1);
    museumTicketADT->day[dayOfYear-1].begin = museumTicketADT->day[dayOfYear-1].visitors;
}

size_t hasNextByDay(museumTicketADT museumTicketADT, size_t dayOfYear)
{
    return (museumTicketADT->day[dayOfYear-1].begin != NULL);
}

char * nextByDay(museumTicketADT museumTicketADT, size_t dayOfYear)
{
    char * aux = museumTicketADT->day[dayOfYear-1].begin->visitor;
    museumTicketADT->day[dayOfYear-1].begin = museumTicketADT->day[dayOfYear-1].begin->next;
    return aux;
}

/**
 * Libera los recursos utilizados para administrar las ventas de tickets para visitar
 * un museo en un año determinado
 */

void freeRec(TList l)
{
    if (l == NULL)
        return ;
    free(l->visitor);
    freeRec(l->next);
    free(l);
}


void freeMuseumTicket(museumTicketADT museumTicketADT)
{
    for(int i = 0; i < 366 ; i++)
    {
        freeRec(museumTicketADT->day[i].visitors);
        freeRec(museumTicketADT->day[i].begin);
    }
    free(museumTicketADT);
}