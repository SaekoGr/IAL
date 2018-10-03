
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá
** někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int errflg;
int solved;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	
    // initializes an empty list
    L->Act=NULL;
    L->First=NULL;
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	
    // action pointer is set to NULL
    L->Act = NULL;
    // remove elements until the first one points to NULL
    while(L->First != NULL){
        tElemPtr next_element = L->First->ptr;  // saves next element
        tElemPtr to_delete = L->First;          // saves first element

        free(to_delete);            // delete first
        L->First = next_element;    // set the new first
    }
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    
    // temporary variables for storing the memory pointer
    tElemPtr tmp_struct_pointer;
    // try to allocate memory
    tmp_struct_pointer = malloc(sizeof(struct tElem));
    // if unsuccesful, go to Error()
    if (tmp_struct_pointer == NULL){
        Error();
    }  
    else{
        tmp_struct_pointer->data = val; // data is saved
        tmp_struct_pointer->ptr = L->First; // original first element becomes the second
        L->First = tmp_struct_pointer;  // new element becomes the first one
    }

}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
    // set active pointer as the first one
    L->Act = L->First;
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	
    // checks whether list is empty or not
    if (L->First == NULL){
        Error();
    }   // if it exits, pointer val will points to it's data
    else{
        *val = L->First->data;  // saves the data
    }
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	
    // return if list is empty
    if(L->First == NULL){
        return;
    }
    else{
        // checks whether the first one is also the active one
        if(L->First == L->Act){
            L->Act = NULL;
        }
    
        tElemPtr new_first = L->First->ptr; // save pointer to the second element
        tElemPtr to_delete = L->First;  // save pointer to the first element
        L->First = new_first;   // second element is now the first one

        free(to_delete);    // free the pointer to the original first element

    }
}	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
	
    // check whether active
    if(L->Act == NULL){
        return;
    }   // check whether next one exists
    else if(L->Act->ptr == NULL){
        return;
    }   // it exits and it will delete it
    else{
        tElemPtr to_delete = L->Act->ptr; // save pointer to element to be deleted
        tElemPtr after_delete = L->Act->ptr->ptr; // save pointer to next element

        free(to_delete);    // delete the element
        L->Act->ptr = after_delete; // bind the list again
    }

}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
    // check whether active
    if(L->Act == NULL){
            return;
    }
    else {// temporary pointer
        tElemPtr new_element;
        // allocate memory
        new_element = malloc(sizeof(struct tElem));
        if(new_element == NULL){
            Error();
        }
        
        tElemPtr tmp_ptr = L->Act->ptr; // save the next element pointer
        L->Act->ptr = new_element;  // insert new
        new_element->ptr = tmp_ptr; // bind the new and following element
        new_element->data = val;    // save the data
    }
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	
	// check whether active
    if(L->Act == NULL){
        Error();
    } // if active, pointer val will point to its data
    else{
        *val = L->Act->data;    // points val to the active data
    }
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
	
    // check whether active
    if(L->Act == NULL){
        return;
    }
    else{
        L->Act->data = val; // saves data to the active element
    }

}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
	
	// check whether active
    if(L->Act == NULL){
        return;
    }
    else{
        tElemPtr next_element = L->Act->ptr; // save pointer to next element
        L->Act = next_element;  // move active pointer to the next element
    }
}

int Active (tList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	
    // if not active, return false, else return true
    return (L->Act == NULL ? FALSE : TRUE);	
}

/* Konec c201.c */
