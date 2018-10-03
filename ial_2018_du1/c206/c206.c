
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int errflg;
int solved;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    
	// initializes all the pointers to NULL
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
	
    // delete all elements 
	while(L->First != NULL){
        tDLElemPtr first_element = L->First; // save to the variable
        L->First = first_element->rptr; // First points to next element
        free(first_element); // free the memory
    }
    // sets all pointers to NULL
    L->Act = NULL;
    L->First = NULL;
    L->Last = NULL;
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
    // allocates new memory
    tDLElemPtr first_element = malloc(sizeof(struct tDLElem));
    if(first_element == NULL){ // error at allocating
        DLError();
    }
    // if list is empty
    if(L->First == NULL){
        first_element->lptr = NULL; // both sides are NULL
        first_element->rptr = NULL;
        first_element->data = val; // saves the data
        L->First = first_element; // first element is saves as first
        L->Last = first_element; // and also the last
    } // this is not the first element	
    else{
        tDLElemPtr old_element = L->First; // first element is temporarily stored
        first_element->data = val; // saves the data
        L->First = first_element; // pointer is set to new element
        first_element->rptr = old_element; // binds the elements
        old_element->lptr = first_element;
        first_element->lptr = NULL; // left pointer of first is set to NULL

    }

}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	
    // allocates new memory
	tDLElemPtr last_element = malloc(sizeof(struct tDLElem));
    if(last_element == NULL){ // error at allocating
        DLError();
    } // if list is empty
    else if(L->Last == NULL){
        last_element->lptr = NULL; // both sides are set to NULL
        last_element->rptr = NULL;
        last_element->data = val; // saves the data
        L->First = last_element; // new element is first
        L->Last = last_element; // and also the last
    } // adds to the list
    else{
        tDLElemPtr previous_element = L->Last; // tmp variable
        last_element->data = val; // new data is saved
        L->Last = last_element; // new element is saved as last
        last_element->lptr = previous_element; // binds the elements
        previous_element->rptr = last_element;
        last_element->rptr = NULL; // right pointer of last is set to NULL
    }
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	
    // set activity to the first element
    L->Act = L->First;
    return;
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	
    // set activity to the last element
    L->Act = L->Last;
    return;
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    // checks whether list is empty
	if(L->First == NULL){
        DLError();
    } // if not, copy data of the first element
    else{
        *val = L->First->data;
    }
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	
    // checks wheter empty or not
	if(L->First == NULL){
        DLError();
    } // if not, copty the last value
    else{
        *val = L->Last->data;
    }
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	
    // checks whether list is empty
	if(L->First == NULL){
        return;
    } //if not empty
    else{
        if(L->First == L->Act){ // if first is active
            L->Act = NULL; // it loses the activity
        }
        tDLElemPtr first_element = L->First; // tmp variable
        if(L->Last == L->First){ // if only one element exists
            L->Last = NULL; // all pointers are set to NULL
            L->First = NULL;
            L->Act = NULL;
            free(first_element); // memory is freed
        }
        else{ // there are more elements
            tDLElemPtr second_element = L->First->rptr; // second element is saved
            second_element->lptr = NULL; // its left poitners is set to NULL
            L->First = second_element; // and it becomes the new first element
            free(first_element); // frees the memory of previous first element
        }
    }
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	
    // checks whether list is empty
    if(L->Last == NULL){
        return;
    } // if not empty
    else{
        if(L->Last == L->Act){ // if last is active
            L->Act = NULL; // it loses the activity
        }
        tDLElemPtr last_element = L->Last; // tmp variable
        if(L->Last == L->First){ //if only one element exists
            L->Last = NULL; // all pointers are set to NULL
            L->First = NULL;
            L->Act = NULL;
            free(last_element); // memory is freed
        }
        else{ // there are more elements
            tDLElemPtr previous_element = L->Last->lptr; // second last element is saved
            previous_element->rptr = NULL; // its right pointer is set to NULL
            L->Last = previous_element; // and it becomes the new last element
            free(last_element); // frees the memory of previous last element
        }
    }
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	
    // checks whether list is empty
    if(L->Act == NULL){
        return;
    } // checks whether last element is active
    else if(L->Act == L->Last){
        return;
    } // if not empty
    else{
        tDLElemPtr to_delete = L->Act->rptr; // tmp variable of right element
        if(to_delete == L->Last){ // if the one to be deleted is last
            L->Act->rptr = NULL; // right pointer is set to NULL
            L->Last = L->Act; // last one is now the active one
            free(to_delete); // frees the memory of last element
        }
        else{ // if the one to be deleted is not the last
            tDLElemPtr next_element = to_delete->rptr; // tmp variable
            L->Act->rptr = next_element; // binds the two elements
            next_element->lptr = L->Act;
            free(to_delete); // the middle one is freed
        }
    }
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	
    // checks whether list is empty
    if(L->Act == NULL){
        return;
    } // checks whether first element is active
    else if(L->Act == L->First){
        return;
    } // if not empty
    else{
        tDLElemPtr to_delete = L->Act->lptr; // the previous element is saved
        if(to_delete == L->First){ // if the one to be deleted is the first one
            L->Act->lptr = NULL; // left pointer is set to NULL
            L->First = L->Act; // first one becomes the active one
            free(to_delete); // frees the memory of the first element
        }
        else{ // if the one to be deleted is not the first one
            tDLElemPtr previous_element = to_delete->lptr; // tmp variable
            L->Act->lptr = previous_element; // binds the two elements
            previous_element->rptr = L->Act;
            free(to_delete); // the middle one is freed
        }
    }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
    // checks whether list is empty
    if(L->Act == NULL){
        return;
    }
    else{
        // allocates new element
        tDLElemPtr to_insert = malloc(sizeof(struct tDLElem));
        if(to_insert == NULL){ // if not allocated, there is error
            DLError();
        }
        else{
            if(L->Act == L->Last){ // active element is also the last
                L->Act->rptr = to_insert; // insert it after that
                to_insert->lptr = L->Act; // bind it together
                L->Last = to_insert; // new element is now the last one
            }
            else{ // active element is not last
                tDLElemPtr next_element = L->Act->rptr; // tmp variable
                L->Act->rptr = to_insert; // binds new and old elements
                to_insert->lptr = L->Act;
                to_insert->rptr = next_element;
                next_element->lptr = to_insert;
            }
            to_insert->data = val; // saves the new data
        }
    }
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
    // checks whether list is empty
    if(L->Act == NULL){
        return;
    }
    else{
        // allocates new element
        tDLElemPtr to_insert = malloc(sizeof(struct tDLElem));
        if(to_insert == NULL){ // if not allocated, there is error
            DLError();
        }
        else{
            if(L->Act == L->First){ // active element is also the first
                L->Act->lptr = to_insert; // binds the new element
                to_insert->rptr = L->Act;
                L->First = to_insert; // inserted one is set to first
            }
            else{ // active element is not first
                tDLElemPtr previous_element = L->Act->lptr; // tmp variable
                L->Act->lptr = to_insert; // binds new and old elements
                to_insert->rptr = L->Act;
                to_insert->lptr = previous_element;
                previous_element->rptr = to_insert;
            }
            to_insert->data = val; // saves the new data
        }
    }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

    // if not active, there is error
	if(L->Act == NULL){
        DLError();
    } // else point the pointer to the active data
    else{
        *val = L->Act->data;
    }
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	
    // if not active, return
	if(L->Act == NULL){
        return;
    } // else, rewrite the data with val
    else{
        L->Act->data = val;
    }
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	
    // if non active, return
    if(L->Act == NULL){
        return;
    } // if next element doesn't exist, activity disappears
    else if(L->Act->rptr == NULL){
        L->Act = NULL;
    } // moves the activity to the next one
    else{
        L->Act = L->Act->rptr;
    }

}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	
    // if non active, return
    if(L->Act == NULL){
        return;
    } // if previous element doesn't exist (it is on the first one) activity disappears
    if(L->Act->lptr == NULL){
        L->Act = NULL;
    } // moves the activity to the previous one
    else{
        L->Act = L->Act->lptr;
    }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	
	// check whether list is active and returns a boolean
    return (L->Act != NULL);
}

/* Konec c206.c*/
