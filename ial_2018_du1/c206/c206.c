
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
	
	while(L->First != NULL){
        tDLElemPtr first_element = L->First;

        L->First = first_element->rptr;
        free(first_element);
        
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
	
    tDLElemPtr first_element = malloc(sizeof(struct tDLElem));
    if(first_element == NULL){
        DLError();
    }
    // checks if this is the first element to be added
    if(L->First == NULL){
        first_element->lptr = NULL;
        first_element->rptr = NULL;
        first_element->data = val;
        L->First = first_element;
        L->Last = first_element;
    }	
    else{
        tDLElemPtr old_element = L->First;
        first_element->data = val;
        L->First = first_element;
        first_element->rptr = old_element;
        first_element->lptr = NULL;
        old_element->lptr = first_element;
    }

}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	
	tDLElemPtr last_element = malloc(sizeof(struct tDLElem));
    if(last_element == NULL){
        DLError();
    }
    else if(L->Last == NULL){
        last_element->lptr = NULL;
        last_element->rptr = NULL;
        last_element->data = val;
        L->First = last_element;
        L->Last = last_element;
    }
    else{
        tDLElemPtr previous_element = L->Last;
        last_element->data = val;
        L->Last = last_element;
        last_element->lptr = previous_element;
        last_element->rptr = NULL;
        previous_element->rptr = last_element;

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
    }   // if not, copy data of the first element
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
	
	if(L->First == NULL){
        return;
    }
    else{
        if(L->First == L->Act){
            L->Act = NULL;
        }
        tDLElemPtr first_element = L->First;
        if(L->Last == L->First){
            L->Last = NULL;
            L->First = NULL;
            L->Act = NULL;
            free(first_element);
        }
        else{
            tDLElemPtr second_element = L->First->rptr;

            second_element->lptr = NULL;
            L->First = second_element;
            free(first_element);
        }
    }
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	
    if(L->Last == NULL){
        return;
    }
    else{
        if(L->Last == L->Act){
            L->Act = NULL;
        }
        
        tDLElemPtr last_element = L->Last;
        if(L->Last == L->First){
            L->Last = NULL;
            L->First = NULL;
            L->Act = NULL;
            free(last_element);
        }
        else{
            tDLElemPtr previous_element = L->Last->lptr;

            previous_element->rptr = NULL;
            L->Last = previous_element;
            free(last_element);
        }
    }

}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	
    if(L->Act == NULL){
        return;
    }
    else if(L->Act == L->Last){
        return;
    }
    else{
        tDLElemPtr to_delete = L->Act->rptr;

        if(to_delete == L->Last){
            L->Act->rptr = NULL;
            L->Last = L->Act;
            free(to_delete);
        }
        else{
            tDLElemPtr next_element = to_delete->rptr;

            L->Act->rptr = next_element;
            next_element->lptr = L->Act;
            free(to_delete);
        }
    }
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	
    
    if(L->Act == NULL){
        return;
    }
    else if(L->Act == L->First){
        return;
    }
    else{
        tDLElemPtr to_delete = L->Act->lptr;
        
        if(to_delete == L->First){
            L->Act->lptr = NULL;
            L->First = L->Act;
            free(to_delete);
        }
        else{
            tDLElemPtr previous_element = to_delete->lptr;

            L->Act->lptr = previous_element;
            previous_element->rptr = L->Act;
            free(to_delete);
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
	
    if(L->Act == NULL){
        return;
    }
    else{
        tDLElemPtr to_insert = malloc(sizeof(struct tDLElem));
        if(to_insert == NULL){
            DLError();
        }
        else{
            if(L->Act == L->Last){
                L->Act->rptr = to_insert;
                to_insert->lptr = L->Act;
                L->Last = to_insert;
            }
            else{
                tDLElemPtr next_element = L->Act->rptr;

                L->Act->rptr = to_insert;
                to_insert->lptr = L->Act;
                to_insert->rptr = next_element;
                next_element->lptr = to_insert;
            }
            to_insert->data = val;
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
	
    if(L->Act == NULL){
        return;
    }
    else{
        tDLElemPtr to_insert = malloc(sizeof(struct tDLElem));
        if(to_insert == NULL){
            DLError();
        }
        else{
            if(L->Act == L->First){
                L->Act->lptr = to_insert;
                to_insert->rptr = L->Act;
                L->First = to_insert;
            }
            else{
                tDLElemPtr previous_element = L->Act->lptr;

                L->Act->lptr = to_insert;
                to_insert->rptr = L->Act;
                to_insert->lptr = previous_element;
                previous_element->rptr = to_insert;
            }
            to_insert->data = val;
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
