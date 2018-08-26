#include"MusicOrganizer.h"

int main(){
	
	file=fopen("Rapport.txt","w+");
	fprintf(file,"\t\t\tRAPPORT DE FONCTIONEMENT\n");
	fprintf(file,"\t\t\t________________________\n");
		
	
	Paths=fopen("Paths.txt","r");
	ListeArtists=fopen("ListeOfArtists.txt","r");

/**/




/**/

	
	
	Pathf();
	Commandes();

	fprintf(file,"\n========================= Copier les fichiers dans le dossier convenable ============================================\n\n");	
	ArtistToArtist(cfdc);

	fprintf(file,"\n\n======================= Supprimer les fichiers indiqueés dans la liste =============================================");
	ArtistToArtist(sfi);
 
	fprintf(file,"\n=========================== Déplacer les fichiers indiqueés par faute ============================================\n\n");
	ArtistToArtist(dfifdp);
	
	
	fclose(file);
	fclose(ListeArtists);
	fclose(Paths);
	
	system("rapport.txt");
	system("cls");
	system("color 07");
	
	return 0;
}
