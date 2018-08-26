#include"MusicOrganizer.h"

int main(){
	
	file=fopen("Rapport.txt","w+");
	fprintf(file,"\t\t\tRAPPORT DE FONCTIONEMENT\n");
	fprintf(file,"\t\t\t________________________\n");
		
	
	Paths=fopen("Paths.txt","r");
	ListeArtists=fopen("ListeOfArtists.txt","r");
	
	
	Pathf();
	Commandes();
	ArtistsNbr();
	
	
	fclose(file);
	fclose(ListeArtists);
	fclose(Paths);
	
	system("rapport.txt");
	
	return 0;
}
