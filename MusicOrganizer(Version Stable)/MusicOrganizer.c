#include"MusicOrganizer.h"

/*******************************************************************************************/

void Pathf(){
	
	//	Resource
	{	rewind(Paths);
		strcpy(Resource,"\"");
		char ch[2]="a";
		while(ch[0]!='\n'){
			ch[0]=fgetc(Paths);
			ch[1]='\0';
			strcat(Resource,ch);	
		}
		Resource[strlen(Resource)-1]='\"';
	}
	fprintf(file,"\nResource: %s\n",Resource);
	
	//Destination:
	{	strcpy(Destination,"\"");
		char ch[2]="a";
		while(ch[0]!=EOF){
			ch[0]=fgetc(Paths);
			ch[1]='\0';
			strcat(Destination,ch);	
		}
		Destination[strlen(Destination)-1]='\"';

	}
	fprintf(file,"Destination: %s\n",Destination);
}
/*******************************************************************************************/

void acces_to_device(device Dev){
	
	char charPath[256];
	
	if(Dev==DevResource){
		strcpy(charPath,Resource);
	}else{
		strcpy(charPath,Destination);
	}
	
	char c[2];
	c[1]='\0';
	c[0]=charPath[1];
	strcat(commande,c);
	strcat(commande,": & cd ");
	strcat(commande,charPath);


}

/*******************************************************************************************/

void Commandes(){
	
	system("Color 8F");
	
	strcpy(commande,"\0");
	acces_to_device(DevDestination);
	strcat(commande," & mkdir ");
	strcat(commande,FILE_NAME);
	system(commande);
	fprintf(file,"\n1er Commande: %s\n",commande);
	
	Destination[strlen(Destination)-1]='\0';
	strcat(Destination,"\\");
	strcat(Destination,FILE_NAME);
	strcat(Destination,"\"");
	fprintf(file,"\nNew Destination:%s\n",Destination);
	

	strcpy(commande,"\0");
	acces_to_device(DevResource);
	strcat(commande," & copy *.* ");
	strcat(commande,Destination);
	system(commande);
	fprintf(file,"\nCommande de copie les fichier:%s\n",commande);
	
	strcpy(Resource,Destination);
	fprintf(file,"\nNew Resource:%s\n",Resource);
	
}

/*******************************************************************************************/

void ArtistsNbr(){
	rewind(ListeArtists);
	char ch[2]="a";
	ch[1]='\0';
	char ArtistName[50]="\0";
	
	while(ch[0]!=EOF){
		ch[0]=fgetc(ListeArtists);
		
		if(ch[0]=='\n'){
			
			PrincipaleCommande(ArtistName);
			
			strcpy(ArtistName,"\0");
		}else{
			if(ch[0]==' ') ch[0]='_';
			strcat(ArtistName,ch);
		}
	}

}
/*******************************************************************************************/

void MakeNewDIR(char ArtistName[50]){
	static bool FirstTime=true;
	if(FirstTime==true){
		FirstTime=false;
	}else{
		register int i=strlen(Destination);
		while(Destination[i]!='\\'){
			Destination[i]='\0';
			i--;
		}
		Destination[i]='\"';
	}
	
	strcpy(commande,"\0");
	acces_to_device(DevDestination);
	strcat(commande," & mkdir ");
	strcat(commande,ArtistName);
	system(commande);	
	fprintf(file,"Make New DIR:\n\t%s\n",commande);

	Destination[strlen(Destination)-1]='\0';
	strcat(Destination,"\\");
	strcat(Destination,ArtistName);
	strcat(Destination,"\"");
	
}

/*******************************************************************************************/

void PrincipaleCommande(char ArtistName[50]){
	
	MakeNewDIR(ArtistName);
{//Artist Etoil:
	char Name[50]="*";
	register int i=0;
	register int j=1;
	
	while(i<strlen(ArtistName)){
		if(ArtistName[i]=='_'){
			Name[j]='*';

		}else{
			Name[j]=ArtistName[i];
		}
		
		i++;
		j++;
	}
	strcat(Name,"*");
	strcpy(ArtistName,Name);
}

	strcpy(commande,"\0");
	acces_to_device(DevResource);
	strcat(commande," & move ");
	strcat(commande,ArtistName);
	strcat(commande," ");
	strcat(commande,Destination);
	strcat(commande," & Non");
	system(commande);
	fprintf(file,"\nPrincipale commande:%s\n",commande);
}

/*******************************************************************************************/



/*******************************************************************************************/


/*******************************************************************************************/
