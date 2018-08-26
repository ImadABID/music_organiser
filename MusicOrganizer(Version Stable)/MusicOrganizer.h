#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FILE_NAME "ABID_Software"

typedef enum device{
	DevDestination,
	DevResource
}device;

typedef enum bool{
	false,true
}bool;

typedef struct charlist{
	char name[25];
}charliste;

FILE *ListeArtists;
charliste *Artists;
int nbrArtists;

FILE *Paths;
FILE *file;

char commande[256];
char Resource[256];
char Destination[256];

void Pathf();
void acces_to_device(device Dev);

void ArtistsNbr();
void MakeNewDIR(char ArtistName[50]);

void Commandes();
void PrincipaleCommande(char ArtistName[50]);



