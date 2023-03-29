////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"
void convertirNenChaine4(int N,char *N4);

/*Client : DUPONT
10 crayon  (PU=1.20€) :: 12.00€
25 agrafeuse (PU=5.60€) :: 140.00€  
35 ramette_feuillesA4 (PU=9.90) :: 346.50€
60 boite_100enveloppes11*21 (PU=8.70€) :: 522.00€
50 boite_100enveloppes30*21 (PU=14.70€) :: 735.00€

			TOTAL = 1755,50€ */


/*

void lireCommande(char *N, char * nb2){
	char nom[99] ;
	int numArticle1, numArticle2;
	int qtefloat ;
	float prixUnit;
	int i ;
	int qte ;
	int nb;
	int j=0;
	float prixTot, TOTAL ;
	char car;
	char NNNN[5];
	char nomCommande[29];
	char nomArticle[99] ;
	FILE *ficCommande;
	FILE *ficFacture;
	ficCommande=fopen(N,"rt");


	strcpy(nomCommande,"./factures/facture");
	
	strcat(nomCommande,nb2);
	strcat(nomCommande,".txt");
	ficFacture=fopen(nomCommande,"w");
	
	fscanf(ficCommande, "%s", nom);
	fprintf(ficFacture,"client: %s\n",nom);
	
	
	
	

	//ecrire le nom de l acheteur
	

	//lire et comp pour avec les prix
		FILE * produit;
		produit=fopen("produits.txt","r");

	do{
		//lire ligne sauf premiere ?
		fscanf(ficCommande, "%d %d", &numArticle1, &qte);
		rewind(produit);
		//comparer 
		do{
			fscanf(produit, "%d %s %f", &numArticle2, nomArticle, &prixUnit);
			if(numArticle1==numArticle2){
				prixTot=(prixUnit*qte);
				fprintf(ficFacture, "%d %s (PU=%f$) :: %f$ \n", qte, nomArticle, prixUnit, prixTot);
				TOTAL=TOTAL+prixTot ; 
			}

		} while(!feof(produit));

	} while (!feof(ficCommande));
	
	fprintf(ficFacture, "\t\tTOTAL = %f\n", TOTAL);

	fclose(ficCommande);
	fclose(ficFacture);
	fclose(produit);
	
}
*/







void lireCommande2(char *N, char * nb2){
	char nom[99] ;
	int numArticle1, numArticle2;
	int qtefloat ;
	float prixUnit;
	int i ;
	int qte ;
	int nb;
	int j=0;
	float prixTot, TOTAL ;
	char car;
	char NNNN[5];
	char nomCommande[29];
	char nomArticle[99] ;
	FILE *ficCommande;
	FILE *ficFacture;
	ficCommande=fopen(N,"rt");
	//partie stock
	int Nomcmd;
	int qte_stock;


	strcpy(nomCommande,"./factures/facture");
	
	strcat(nomCommande,nb2);
	strcat(nomCommande,".txt");
	ficFacture=fopen(nomCommande,"w");
	
	fscanf(ficCommande, "%s", nom);
	fprintf(ficFacture,"client: %s\n",nom);
	
	
	
	

	//ecrire le nom de l acheteur
	

	//lire et comp pour avec les prix
	    FILE * alerte;
	    alerte=fopen("alertes.txt","w");
		FILE * produit;
		produit=fopen("produits.txt","r");
		FILE * stock;	
		stock=fopen("stock.txt","r+");
	do{
		//lire ligne sauf premiere ?
		fscanf(ficCommande, "%d %d", &numArticle1, &qte);
		rewind(produit);
		//comparer 
		do{
			fscanf(produit, "%d %s %f", &numArticle2, nomArticle, &prixUnit);
			if(numArticle1==numArticle2){
				prixTot=(prixUnit*qte);
				fprintf(ficFacture, "%d %s (PU=%f$) :: %f$ \n", qte, nomArticle, prixUnit, prixTot);
				TOTAL=TOTAL+prixTot ; 
				//gestion stok
				rewind(stock);
				do{
					fscanf(stock, "%d %d", &Nomcmd, &qte_stock);
					 printf("\n ======================>>   %d %d ",Nomcmd, qte_stock);
					if(Nomcmd==numArticle1){
						qte_stock=qte_stock-qte;
						if(qte_stock<0){
							int tempqte;
							tempqte= abs(qte_stock);
							fprintf(alerte,"%d %d \n", Nomcmd, tempqte);
						}
						else{
							 printf("\n coucouuuuuuuuuuuuuuuuuuuuuuuuu   %d %d ",Nomcmd, qte_stock);
						fprintf(stock, "\n%d %d\n", Nomcmd, qte_stock);

					printf("stockqte %d\n", qte_stock);
					printf("stock %d\n", Nomcmd);
						 }
					}
				}while(!feof(stock));

				
			}

		} while(!feof(produit));

	} while (!feof(ficCommande));
	
	fprintf(ficFacture, "\t\tTOTAL = %f\n", TOTAL);

	fclose(ficCommande);
	fclose(ficFacture);
	fclose(produit);
	fclose(stock);
	
}







int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
FILE *f;
int N;
f=fopen("nextFact","r");
fread(&N,sizeof(int),1,f);
fclose(f);
//printf("\n--->lu N=%d",N);
return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
int m,c,d,u;
char cm,cc,cd,cu;
m=N/1000;cm=48+m;
N%=1000;
c=N/100;cc=48+c;
N%=100;
d=N/10;cd=48+d;
u=N%10;
cu=48+u;
N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}

/*
void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
FILE *ficCommande=NULL;
int FINI=0;
int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
char NNNN[5];
char nomCommande[29];

do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present",nomCommande);
			lireCommande(nomCommande,NNNN); // à vous de coder cette fonction lors de ce TP9
			fclose(ficCommande);
		}
	else
		{
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		



}*/


void lireLesCommandes2() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
FILE *ficCommande=NULL;
int FINI=0;
int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
char NNNN[5];
char nomCommande[29];

do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present",nomCommande);
			lireCommande2(nomCommande,NNNN); // à vous de coder cette fonction lors de ce TP9
			fclose(ficCommande);
		}
	else
		{
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		

}


int main()
{
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	
	FILE *f;int N=5;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);
	

	//PARTIE 1 du TP : sans Gestion de stock
	//lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	

	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	lireLesCommandes2(); 	

	return 0;
}
