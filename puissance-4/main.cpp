#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <Windows.h>


int gagne(int c,int l,int J,int tab[7][6])
{
	//optimisation du nombre de variables
	
	int j[4];
	int k[3];

	//initialisation des tableaux
	for(int i=0;i<4;i++)
	{
		j[i]=1;
	}
	for(int i=0;i<3;i++)
	{
		k[i]=1;
	}


	for (int i=1; i<4; i++)
	{
		if (c-i>-1)
		{
			if ((tab[c-i][l]==J)&&(j[0]==i)) 
				j[0]++;
			if ((l-i>-1)&&(j[1]==i)) 
			{
				if(tab[c-i][l-i]==J) 
					j[1]++;
			}
			if ((l+i<6)&&(j[2]==i)) 
			{
				if(tab[c-i][l+i]==J) 
					j[2]++;
			}
		}
		if ((l-i>-1)&&(j[3]==i)) 
		{
			if(tab[c][l-i]==J) 
				j[3]++;
		}
	}
	for (int i=1; i<4; i++)
	{
		if (c+i<7)
		{
			if ((tab[c+i][l]==J)&&(k[0]==i)) 
				k[0]++;
			if ((l-i>-1)&&(k[2]==i)) 
			{
				if(tab[c+i][l-i]==J) 
					k[2]++;
			}
			if ((l+i<6)&&(k[1]==i)) 
			{
				if(tab[c+i][l+i]==J) 
					k[1]++;
			}
		}
	}
	
	//Modification de la valeur si aucun joueur ne gagne.
	if ((k[0]+j[0]>=5)||(k[1]+j[1]>=5)||(k[2]+j[2]>=5)||(j[3]==4)) 
		return J;
	else
		return -1;
}

void affichageTab(int tab[7][6])
{
	//Modification de l'affichage.
	system("cls");
	std::cout<<std::endl<<std::endl<<std::endl;
	for (int i=5;i>=0;i--)
	{
		std::cout<<"          | ";
		for (int j=0;j<7;j++)
		{
			if (tab[j][i]==-1) 
				std::cout<<" ";
			if (tab[j][i]==0) 
				std::cout<<"X";
			if (tab[j][i]==1) 
				std::cout<<"O";
			std::cout<<" ";
		}
		std::cout<<"|"<<std::endl<<"          |---------------|"<<std::endl;
	}
	std::cout<<"          # 0 1 2 3 4 5 6 #"<<std::endl<<std::endl;
}


//Création d'une méthode pour jouer.
void jeu(int mode)
{
	//Optimisation du nombre de variables utilisées.
	int nbJetonsByColonne[7];   // donne le nombre de jetons sur chaque colonne

	//Ajout pour contenir le nom du ou des joueurs.
	std::string tabJoueurs[2];
	int tab[7][6];
	int J;
	int g=-1,c,l,compteur=0;


	//Ajout pour gérer si on est en mode 2 joueurs
	bool mode2joueurs=false;
	for (int i=0; i<7; i++)  // mise a zéro du tableau et des colonnes
	{
		nbJetonsByColonne[i]=0;
		for (int j=0; j<6; j++)
		{
			tab[i][j]=-1;
		}
	}
	system("cls");

	//Ajout pour obtenir le nom du ou des joueurs qui joueront la partie.
	if(mode==1)
	{
		mode2joueurs=true;
		std::cout	<< "Entrer le nom du premier joueur ?" << std::endl;
		std::cin>>tabJoueurs[0];
		std::cout<<std::endl<<std::endl <<"Entrer le nom du second joueur ?" << std::endl;
		std::cin>>tabJoueurs[1];  
		system("cls");
	}
	else
	{
		
	}

	//Détermine qui débute la partie au hasard au lieu de choisir.
	srand(time(NULL));
	J=rand()%2;
	if(J==0)
		std::cout<<"C'est " << tabJoueurs[0] << " qui debute"<<std::endl;
	else
	{
		if(mode2joueurs)
			std::cout<<"C'est " << tabJoueurs[1] << " qui debute"<<std::endl;
		else {
		}
		
	}
	system("pause");

	while (g==-1)         //  tant que personne n'a gagné
	{
		if (compteur==42)  // égalité
		{
			g=-1;
			break;
		} 
		affichageTab(tab);

		//Ajout pour la gestion des joueurs joueurs.
		if (J==0 || mode2joueurs)           
		{
			std::cout<<std::endl<<"C'est au tour de "<<tabJoueurs[J]<< " ! \nDans quel colonne veux-tu placer ton jeton ? (0 a 6) (Tes jetons sont les ";
			if(J==0)
				std::cout<<"X)"<<std::endl;
			else
				std::cout<<"O)"<<std::endl;
			do
			{
				std::cin>>c;             //nbJetonsByColonne
				if(nbJetonsByColonne[c]>5) 
				{
					std::cout<<"Cette colonne est deja pleine."<<std::endl;
				}
			}
			while(nbJetonsByColonne[c]>5);
		}
		else
		{
			
		}

		l=nbJetonsByColonne[c];         //ligne
		tab [c][l]=J;
		nbJetonsByColonne[c]++;
		g=gagne(c,l,J,tab);

		//Modification pour gestion plus logique des tours des joueurs.
		if (J==1) 
			J--;
		else
			J++;
		compteur++;
	}

	affichageTab(tab);

	//Modification des messages affichés
	switch(g)
	{
		case -1 :std::cout<<std::endl<<"Partie nulle !"<<std::endl;
				break;
		case 0:std::cout<<std::endl<<"Bravo ! Tu as gagne "<<tabJoueurs[0]<<std::endl;
				break;

		//Ajout pour la gestion du mode 2 joueurs
		case 1:if(mode2joueurs)
					std::cout<<std::endl<<"Bravo ! Tu as gagne "<<tabJoueurs[1]<<std::endl;
				else
				break;
	}

	system("PAUSE");
}

int main()
{
		int c;

		//Dimension de la fenêtre console pour l'affichage.
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console,&r);

		MoveWindow(console,r.left,r.top,800,500,TRUE);

		//Ajout d'un menu pour lancer une partie et pour quitter.
		std::cout << std::endl << "     //////////////////////" << std::endl << "     //    PUISSANCE 4   //" << std::endl << "     //////////////////////" << std::endl << std::endl;
		std::cout<<"1: Lancer une partie\n0: Quitter"<<std::endl;
		do
		{
			std::cin>>c;
		}while(c<0 || c>2);
		system("cls");

		if(c!=0)
		{
			jeu(c);
		}
		
	return 0;
}
