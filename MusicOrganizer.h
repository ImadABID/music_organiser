#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FILE_NAME "ABID_Software"

typedef enum bool{
	false,true
}bool;

typedef enum device{
	DevDestination, DevResource
}device;

typedef enum fonctions{
	cfdc, dfifdp, sfi
}fonctions;

FILE *ListeArtists;
int nbrArtists;

FILE *Paths;
FILE *file;

char commande[256];
char Resource[256];
char Destination[256];

void Pathf();
void acces_to_device(device Dev);
void ArtistStars(char ArtistName[50]);
void ArtistWithoutStars(char ArtistName[50]);
void ReturnerAuDossiersPrecedent(device dev);
void AllerAuDossierSuivent(device dev,char ArtistName[50]);

void ArtistToArtist(fonctions fonction);
void MakeNewDIR(char ArtistName[50]);

void Commandes();
void CFDC(char ArtistName[50]);
void SFI(char ArtistName[50]);
void DFIFDP(char ArtistName[50]);



