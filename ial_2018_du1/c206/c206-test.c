
/*
 *  PĹedmÄt: Algoritmy (IAL) - FIT VUT v BrnÄ
 *  ZĂĄkladnĂ­ testy pro pĹĂ­klad c206.c (DvousmÄrnÄ vĂĄzanĂ˝ lineĂĄrnĂ­ seznam)
 *  VytvoĹil: Martin TuÄek, zĂĄĹĂ­ 2005
 *  Ăprava: Kamil JeĹĂĄbek, ĹĂ­jen 2017
 */

#include "c206.h"
                                                         /* pracovnĂ­ promÄnnĂŠ */
tDLList TEMPLIST;		
int ElemValue=1;
int MaxListLength = 100;                     /* Handles wrongly linked lists. */


/*******************************************************************************
 * PomocnĂŠ funkce usnadĹujĂ­cĂ­ testovĂĄnĂ­ vlastnĂ­ implementace.
 ******************************************************************************/

void print_elements_of_list(tDLList TL)	{
	
	tDLList TempList=TL;
	int CurrListLength = 0;
	printf("-----------------");
	while ((TempList.First!=NULL) && (CurrListLength<MaxListLength))	{
		printf("\n \t%d",TempList.First->data);
		if ((TempList.First==TL.Act) && (TL.Act!=NULL))
			printf("\t <= toto je aktivnĂ­ prvek ");
		TempList.First=TempList.First->rptr;
		CurrListLength++;
	}
    if (CurrListLength>=MaxListLength){
        printf("\nList exceeded maximum length!");
	}
	printf("\n-----------------\n");     
}

int test_DLInitList()	{
	solved=TRUE;	
	DLInitList(&TEMPLIST);
	if (!solved)	{
		printf("Operace InitList nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}	
}

int test_DLDisposeList()	{
	solved=TRUE;
	DLDisposeList(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDisposeList nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}	
}

int test_DLInsertFirst()	{
	solved=TRUE;
	DLInsertFirst(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLInsertFirst nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}	

int test_DLInsertLast()	{
	solved=TRUE;
	DLInsertLast(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLInsertLast nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}	

int test_DLFirst()	{
	solved=TRUE;
	DLFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLFirst nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLLast()	{
	solved=TRUE;
	DLLast(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLLast nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLCopyFirst()	{
	solved=TRUE;	
    int temp;
    DLCopyFirst(&TEMPLIST,&temp);	
	if (!solved)	{
		printf("Operace DLCopyFirst nebyla implementovĂĄna!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopyFirst volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}	
		else	{	 			
			printf("Operace DLCopyFirst vracĂ­ obsah %d.\n",temp);
			return(TRUE);
		}	
	}
}	

int test_DLCopyLast()	{
	solved=TRUE;
    int temp;
    DLCopyLast(&TEMPLIST,&temp);	
	if (!solved)	{
		printf("Operace DLCopyLast nebyla implementovĂĄna!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopyLast volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}	
		else	{	 			
			printf("Operace DLCopyLast vracĂ­ obsah %d.\n",temp);
			return(TRUE);
		}	
	}
}	

int test_DLDeleteFirst ()	{
	solved=TRUE;	
	DLDeleteFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDeleteFirst nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}	

int test_DLDeleteLast ()	{
	solved=TRUE;	
	DLDeleteLast(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDeleteLast nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}	

int test_DLPostDelete()	{
	solved=TRUE;	
	DLPostDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPostDelete nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}	

int test_DLPreDelete()	{
	solved=TRUE;	
	DLPreDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPreDelete nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPostInsert()	{
	solved=TRUE;
	DLPostInsert(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLPostInsert nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPreInsert()	{
	solved=TRUE;
	DLPreInsert(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLPreInsert nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLCopy()	{
	solved=TRUE;
	int temp;
  DLCopy(&TEMPLIST,&temp);	
	
	if (!solved)	{
		printf("Operace DLCopy nebyla implementovĂĄna!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopy volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}	
		else	{	 			
			printf("Operace DLCopy vracĂ­ obsah %d.\n",temp);
			return(TRUE);
		}	
	}	
}

int test_DLActualize()	{
	solved=TRUE;
	DLActualize(&TEMPLIST,ElemValue);
	if (!solved)	{
		printf("Operace DLActualize nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLSucc()	{
	solved=TRUE;
	DLSucc(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLSucc nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPred()	{
	solved=TRUE;
	DLPred(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPred nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLActive()	{
	solved=TRUE;
	int tmp=DLActive(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLActive nebyla implementovĂĄna!\n");
		return(FALSE);
	}	
	else	{
		if (tmp)
			printf("Operace DLActive vracĂ­ hodnotu true.\n");
		else
			printf("Operace DLActive vracĂ­ hodnotu false.\n");	
		return(TRUE);			
	}
}

/*******************************************************************************
 * ZĂKLADNĂ TESTY
 * -------------- 
 * Za jejich ĂşspÄĹĄnĂŠ projĂ­tĂ­ zĂ­skĂĄ student prvnĂ­ ÄĂĄst bodĹŻ za pĹĂ­klad.
 * PĹi hodnocenĂ­ vĹĄak budou pouĹžity rozĹĄĂ­ĹenĂŠ testy, kterĂŠ se zamÄĹĂ­
 * i na okrajovĂŠ situace. DoporuÄujeme proto, aby si kaĹždĂ˝ student
 * zkusitl tyto zĂĄkladnĂ­ testy rozĹĄĂ­Ĺit o dalĹĄĂ­ zajĂ­mavĂŠ situace.
 *  
 ******************************************************************************/

int main(int argc, char *argv[])	{
	
    printf("DvousmÄrnÄ vĂĄzanĂ˝ lineĂĄrnĂ­ seznam\n");
    printf("=================================\n");

    printf("\n[TEST01]\n");
    printf("Inicializace seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    test_DLInitList();

    printf("\n[TEST02]\n");
    printf("ZavolĂĄme 2x operaci DLInsertFirst a 2x operaci DLInsertLast.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");	
    ElemValue=1;
    test_DLInsertFirst();	
    ElemValue=2;
    test_DLInsertFirst();	
    ElemValue=3;
    test_DLInsertLast();
    ElemValue=4;
    test_DLInsertLast();
	
    printf("\n[TEST03]\n");
    printf("Otestujeme funkci DLFirst pĹi neaktivnĂ­m seznamu a funkci DLActive.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLActive();

    printf("\n[TEST04]\n");
    printf("Otestujeme funkci DLLast.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLActive();
	
    printf("\n[TEST05]\n");
    printf("Test funkce DLCopy pĹi aktivitÄ na poslednĂ­m prvku\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();

    printf("\n[TEST06]\n");
    printf("Test funkce DLPred -- volĂĄme 3x, aktivita zĹŻstane na prvnĂ­m prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPred();
    test_DLPred();
    test_DLPred();
    test_DLActive();

    printf("\n[TEST07]\n");
    printf("Aktualizujeme obsah aktivnĂ­ho prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");	
    ElemValue=5;
    test_DLActualize();
    test_DLActive();
    test_DLCopy();
	
    printf("\n[TEST08]\n");
    printf("Test funkce DLSucc -- volĂĄme 3x, aktivita zĹŻstane na poslednĂ­m prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLSucc();
    test_DLSucc();
    test_DLActive();
	
    printf("\n[TEST09]\n");
    printf("Provedeme jeĹĄtÄ jednou DLSucc - aktivita se ztratĂ­.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLActive();
	
    printf("\n[TEST10]\n");
    printf("NastavĂ­me aktivitu na zaÄĂĄtek a pak ji zruĹĄĂ­me operacĂ­ DLPred.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLPred();
    test_DLActive();
	
    printf("\n[TEST11]\n");
    printf("Pokus o DLCopy pĹi neaktivnĂ­m seznamu => oĹĄetĹenĂĄ chyba.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();
    
    printf("\n[TEST12]\n");
    printf("PouĹžitĂ­ operace DLCopyFirst pĹi neaktivnĂ­m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyFirst();

    printf("\n[TEST13]\n");
    printf("PouĹžitĂ­ operace DLCopyLast pĹi neaktivnĂ­m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyLast();

    printf("\n[TEST14]\n");
    printf("PouĹžitĂ­ operace DLDeleteFirst pĹi neaktivnĂ­m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteFirst();
    test_DLActive();

    printf("\n[TEST15]\n");
    printf("PouĹžitĂ­ operace DLDeleteLast pĹi neaktivnĂ­m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteLast();
      test_DLActive();
	
    printf("\n[TEST16]\n");
    printf("ZkusĂ­me DLPostDelete pĹi aktivitÄ na poslednĂ­m prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLPostDelete();
    test_DLActive();
	
    printf("\n[TEST17]\n");
    printf("Operace DLPreDelete nynĂ­ smaĹže prvnĂ­ prvek.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPreDelete();
    test_DLActive();
    
    printf("\n[TEST18]\n"); 
    printf("Seznam nakonec zruĹĄĂ­me.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDisposeList();
    test_DLActive();

    printf("\n----------------------- konec pĹĂ­kladu c206 -------------------------\n");
		
    return(0);
} 
