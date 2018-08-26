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
	
	//CTF
	strcpy(commande,"\0");
	acces_to_device(DevResource);
	strcat(commande," & copy *.* ");
	strcat(commande,Destination);
	system(commande);
	fprintf(file,"\nCommande de copie tous les fichier:%s\n",commande);
	
	strcpy(Resource,Destination);
	fprintf(file,"\nNew Resource:%s\n",Resource);
	
}

/*******************************************************************************************/

void ArtistToArtist(fonctions fonction){
	rewind(ListeArtists);
	char ch[2]="a";
	ch[1]='\0';
	char ArtistName[50]="\0";
	
	while(ch[0]!=EOF){
		ch[0]=fgetc(ListeArtists);
		
		if(ch[0]=='\n'){
			
			switch(fonction){
				case cfdc:		CFDC(ArtistName);	break;
				case sfi:		SFI(ArtistName);	break;
				case dfifdp:	DFIFDP(ArtistName);	break;
			}
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
		ReturnerAuDossiersPrecedent(DevDestination);
	}
	
	strcpy(commande,"\0");
	acces_to_device(DevDestination);
	strcat(commande," & mkdir ");
	strcat(commande,ArtistName);
	system(commande);	
	fprintf(file,"Make New DIR:\n\t%s\n",commande);

	AllerAuDossierSuivent(DevDestination,ArtistName);

	
	
}

/*******************************************************************************************/

void CFDC(char ArtistName[50]){
	
	MakeNewDIR(ArtistName);

	ArtistStars(ArtistName);

	strcpy(commande,"\0");
	acces_to_device(DevResource);
	strcat(commande," & copy ");
	strcat(commande,ArtistName);
	strcat(commande," ");
	strcat(commande,Destination);
	strcat(commande," & Non");
	system(commande);
	fprintf(file,"\nPrincipale commande:%s\n",commande);
}

/*******************************************************************************************/

void SFI(char ArtistName[50]){
	
	ArtistStars(ArtistName);
	
	fprintf(file,"\n\n\tSuppression de: %s",ArtistName);
	
	strcpy(commande,"\0");
	acces_to_device(DevResource);
	strcat(commande," & Del ");
	strcat(commande,ArtistName);
	system(commande);
	
	fprintf(file,"\n\t\tCommande: %s",commande);
	
}

/*******************************************************************************************/

void DFIFDP(char ArtistName[50]){

	static bool FirstTime=true;
	if(FirstTime==true){
		FirstTime=false;
		strcpy(Resource,Destination);
		ReturnerAuDossiersPrecedent(DevDestination);
		
		system("c: & mkdir ABIDsoftware_tmp");
	}
	
	ReturnerAuDossiersPrecedent(DevResource);



	AllerAuDossierSuivent(DevResource,ArtistName);

	ArtistStars(ArtistName);
	char c;
	bool AddInLeft=true;
	char artistname[50];
	for(c='a';c!='Z'+1;c++){

		strcpy(artistname,ArtistName);

		if(AddInLeft){

			artistname[0]=c;
			char name[50]="*";
			strcat(name,artistname);
			strcat(name,"*");
			strcpy(artistname,name);
			artistname[strlen(artistname)-1]='\0';
			
			strcpy(commande,"\0");
			acces_to_device(DevResource);
			strcat(commande,"move ");
			
			{
				char NameEspace[50]="\"*"; NameEspace[2]=c;	NameEspace[3]=' ';
				int i,j=4;
				for(i=1;i<strlen(artistname);i++){
					NameEspace[j]=artistname[i];
					j++;
				}
				strcat(NameEspace,"\"");
				strcat(commande,NameEspace);
			}
			
			strcat(commande," & \"c:\\ABIDsoftware_tmp\" & Non");
			system(commande);
			fprintf(file,"\n\tCommande pour Déplacer les FFI: %s",commande);
			
		}else{

			char ch[2]="\0";
			ch[0]=c;
			
			static int m=1;
			artistname[strlen(artistname)-m]=c;
			artistname[strlen(artistname)-m+1]='*';
			artistname[strlen(artistname)-m+2]='\0';
			if(m==1) m=2;
			
			strcpy(commande,"\0");
			acces_to_device(DevResource);
			strcat(commande,"move ");
			
			{
				char NameEspace[50];
				strcpy(NameEspace,"\"");
				strcat(NameEspace,artistname);
				NameEspace[strlen(artistname)-2]='\0';
				NameEspace[strlen(artistname)-1]=c;
				NameEspace[strlen(artistname)]='*';
				NameEspace[strlen(artistname)]='\"';
			}
			
			strcat(commande,"& \"c:\\ABIDsoftware_tmp\" & Non");
			system(commande);
			fprintf(file,"\n\tCommande pour Déplacer les FFI: %s",commande);
			
			
						
		}
		
		strcpy(commande,"\0");
		acces_to_device(DevResource);
		strcat(commande," & move ");
		strcat(commande,artistname);
		strcat(commande," ");
		strcat(commande,Destination);
		strcat(commande," & Non");
		system(commande);
		fprintf(file,"\nCommande pour déplacer les FIF: %s\n",commande);
		
		strcpy(commande,"c: & \"c:\\ABIDsoftware_tmp\" & move ");
		strcat(commande,artistname);
		strcat(commande," ");
		strcat(commande,Resource);
		system(commande);
		fprintf(file,"\n\tCommande pour returner FFI: %s",commande);
		
		if(c=='z'){
			c='A'-1;
		}
		
		if(c=='Z'&&AddInLeft){
			c='a'-1;
			AddInLeft=false;
		}
		
		if(c=='Z'&& !AddInLeft){
			system("del ABIDsoftware_tmp & o");
		}
	}
	


}

/*******************************************************************************************/

void ArtistStars(char ArtistName[50]){

	if(ArtistName[0]=='*') return;

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

/*******************************************************************************************/

void ArtistWithoutStars(char ArtistName[50]){
	
	if(ArtistName[0]!='*') return;
	
	char Name[256];
	strcpy(Name,ArtistName);
	
	register int i=0,j;
	for(j=1;j<strlen(Name);j++){
		if(Name[j]=='*') Name[j]='_';
		ArtistName[i]=Name[j];	
		i++;
	}
	ArtistName[strlen(ArtistName)-2]='\0';	
}

/*******************************************************************************************/

void AllerAuDossierSuivent(device dev,char ArtistName[50]){
	
	ArtistWithoutStars(ArtistName);
	
	char adresse[256];
	if(dev==DevDestination) strcpy(adresse,Destination);
	if(dev==DevResource) strcpy(adresse,Resource);
	
	
	adresse[strlen(adresse)-1]='\0';
	strcat(adresse,"\\");
	strcat(adresse,ArtistName);
	strcat(adresse,"\"");

	if(dev==DevDestination) strcpy(Destination,adresse);
	if(dev==DevResource) strcpy(Resource,adresse);	
}

/*******************************************************************************************/

void ReturnerAuDossiersPrecedent(device dev){
	char adresse[256];
		
	if(dev==DevDestination) strcpy(adresse,Destination);
	if(dev==DevResource) strcpy(adresse,Resource);
	
	register int i=strlen(adresse);
	while(adresse[i]!='\\'){		
		adresse[i]='\0';
		i--;
	}
	adresse[i]='\"';
	
	if(dev==DevDestination) strcpy(Destination,adresse);
	if(dev==DevResource) strcpy(Resource,adresse);
	
}

/*******************************************************************************************/
