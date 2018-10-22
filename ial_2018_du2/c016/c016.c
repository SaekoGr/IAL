
/* c016.c: **********************************************************}
{* Téma:  Tabulka s Rozptýlenými Položkami
**                      První implementace: Petr Přikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Úpravy: Karel Masařík, říjen 2014
**                              Radek Hranický, 2014-2018
**
** Vytvořete abstraktní datový typ
** TRP (Tabulka s Rozptýlenými Položkami = Hash table)
** s explicitně řetězenými synonymy. Tabulka je implementována polem
** lineárních seznamů synonym.
**
** Implementujte následující procedury a funkce.
**
**  HTInit ....... inicializuje tabulku před prvním použitím
**  HTInsert ..... vložení prvku
**  HTSearch ..... zjištění přítomnosti prvku v tabulce
**  HTDelete ..... zrušení prvku
**  HTRead ....... přečtení hodnoty prvku
**  HTClearAll ... zrušení obsahu celé tabulky (inicializace tabulky
**                 poté, co již byla použita)
**
** Definici typů naleznete v souboru c016.h.
**
** Tabulka je reprezentována datovou strukturou typu tHTable,
** která se skládá z ukazatelů na položky, jež obsahují složky
** klíče 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na další synonymum 'ptrnext'. Při implementaci funkcí
** uvažujte maximální rozměr pole HTSIZE.
**
** U všech procedur využívejte rozptylovou funkci hashCode.  Povšimněte si
** způsobu předávání parametrů a zamyslete se nad tím, zda je možné parametry
** předávat jiným způsobem (hodnotou/odkazem) a v případě, že jsou obě
** možnosti funkčně přípustné, jaké jsou výhody či nevýhody toho či onoho
** způsobu.
**
** V příkladech jsou použity položky, kde klíčem je řetězec, ke kterému
** je přidán obsah - reálné číslo.
*/

#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovací funkce - jejím úkolem je zpracovat zadaný klíč a přidělit
** mu index v rozmezí 0..HTSize-1.  V ideálním případě by mělo dojít
** k rovnoměrnému rozptýlení těchto klíčů po celé tabulce.  V rámci
** pokusů se můžete zamyslet nad kvalitou této funkce.  (Funkce nebyla
** volena s ohledem na maximální kvalitu výsledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitně zřetězenými synonymy.  Tato procedura
** se volá pouze před prvním použitím tabulky.
*/

void htInit ( tHTable* ptrht ) {

	if((*ptrht) == NULL){ // check whether table is initialized or not
		return;
	}
	else{ // sets NULL to each element
		for(int i = 0; i < MAX_HTSIZE; i++){
			(*ptrht)[i] = NULL;
		}
	}

}

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není, 
** vrací se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {

	if((*ptrht) == NULL){ // check whether table is initialized or not
		return NULL;
	}

	int index_position = hashCode(key); // calculate the hashCode
	if((*ptrht)[index_position] == NULL){ // there is no element on this index position
		return NULL;	// therefore, search was unsuccesful
	}
	else{
		tHTItem* item = (*ptrht)[index_position]; // element at current position

		while(item != NULL){ // look throught all the synonyms
			if(strcmp(key, item->key) == 0)	// check if key equals
				return item; // return it if yes
			else	// move throught the synonyms if no
				item = item->ptrnext;
		}
		return NULL;	// search is done without any results
	}
}

/* 
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {

	if((*ptrht) == NULL){ // check whether table is initialized or not
		return;
	}

	tHTItem* new_item = htSearch(ptrht, key); // key exists in the table
	tHTItem* old_item;
	tHTItem* tmp_item;

	if(new_item == NULL){ // not found, has to add it
		int index_position = hashCode(key);

		if((*ptrht)[index_position] == NULL){ // position is available
			(*ptrht)[index_position] = malloc(sizeof(tHTable)); // allocate new
			(*ptrht)[index_position]->data = data;	// saves data
			(*ptrht)[index_position]->key = key;	// saves key
			(*ptrht)[index_position]->ptrnext = NULL;	// next element doesn't exist
		}
		else{	// position is already taken, has to add to it
			tmp_item = malloc(sizeof(tHTable)); // allocate new
			tmp_item->data = data; // saves data
			tmp_item->key = key;	// saves key

			old_item = (*ptrht)[index_position]; // save current first synonym 
			tmp_item->ptrnext = old_item; // new synonym now points to it
			(*ptrht)[index_position] = tmp_item; // new item is saved at first position
			
		}

	}
	else{
		new_item->data = data; // actualize data if the key already there
	}
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {

	if((*ptrht) == NULL){ // check whether table is initialized or not
		return NULL;
	}

	tHTItem* to_read = htSearch(ptrht, key); // search it

	if(to_read == NULL){ // not found
		return NULL;
	}
	else{	// found
		return &(to_read->data);
	}

}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulky
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {

	if((*ptrht) == NULL){ // check whether table is initialized or not
		return;
	}

	int key_result = hashCode(key); // result from key
	tHTItem* to_find = (*ptrht)[key_result]; // everything is set to the first synonym
	tHTItem* first_element = (*ptrht)[key_result];
	tHTItem* previous_element = (*ptrht)[key_result];

	
	if((*ptrht)[key_result] == NULL){ // this key is not in the table, return
		return;
	}
	else{ // key is in the table, look for it
		while(to_find != NULL){ // move throught the synonyms until the end
			if(to_find->key == key){ // key equals, has to adjust the list now
				if(previous_element->ptrnext == to_find && to_find->ptrnext == NULL){ // it is last element
					previous_element->ptrnext = NULL;
					free(to_find);
				}
				else if(first_element == to_find){ // it is first element
					if(to_find->ptrnext != NULL){ // it is not followed by synonym
						(*ptrht)[key_result] = to_find->ptrnext;
						free(to_find);
					}
					else{	// it is followed by synonym
						(*ptrht)[key_result] = NULL;
						free(to_find);
					}
				}
				else{ // it is in the middle of synonyms
					previous_element->ptrnext = to_find->ptrnext;
					free(to_find);
				}
				break; // when found and freed, break from the cycle
			}
			previous_element = to_find; // previous element is set
			to_find = to_find->ptrnext; // move to the next element
			
		}
		
	}
}

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll ( tHTable* ptrht ) {

	if((*ptrht) == NULL){ // check whether table is initialized or not
		return;
	}

	tHTItem* item = NULL;

	for(int i = 0; i < MAX_HTSIZE; i++){ // go throught all the elements
		if((*ptrht)[i] == NULL){ // it is is already NULL, continue
			continue;
		}
		else{	// it is isn't NULL, we have to free all the items
			while((*ptrht)[i] != NULL){ // continue until it is NULL
				item = (*ptrht)[i]; // save it
				(*ptrht)[i] = (*ptrht)[i]->ptrnext; // move to the next item to first place
				free(item); // free memory of first synonym in line
			}
		}
	}
	
}
