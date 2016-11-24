#include "all.h"
#include <stdio.h>
#include <stdlib.h>

#define FIN 0 

int orderG(){
    return 95;}

    int sizeG(){
        return  755;
    }

int adj(int u, int v, int n){
    int x,y;
    if (u==v)
        return 0;
    if(u>v){
        x=u;
        y=v;
    }
    else{
        x=v;
        y=u;
    }
    if(x==1)
        return 1;
    if(x<n/2)
        return adj(x,y,n/2);
    if(x==n-1){
        if(y>=n/2) 
            return 1;
        else return 0;
    }
    if(x>=n/2 && y<n/2)
        return adj(x-n/2,y,n/2);
    return 0;
}




int are_adjacent(int u, int v){
    if(0<=u && 0<=v && u<orderG() && v<orderG())
        return adj(u,v,orderG());
    return 0;
}




void resolutionSAT(int numberColors){
	FILE* sourceTemp, *targetTemp;

	int myMatrixColor[numberColors] ;
    char colorText[40];
	
	//initialize le matrix of colors
	for (int i =0; i< numberColors; i++)
		myMatrixColor[i] = i+1;
	
	sourceTemp = fopen("kcolortemp.cnf", "wt");
	sprintf(colorText, "c number of colors %d \n",numberColors);
	fputs(colorText, sourceTemp);

    //The color condition is evaluated for every node
	for (int u =0; u< orderG();u++){
		
		sprintf(colorText, "c just 1 color condition for node %d\n",u);
		fputs(colorText, sourceTemp);
		
		//just a color of all
		for (int i = 0; i< numberColors; i++){
			sprintf(colorText, "%d ",(u*numberColors)+ myMatrixColor[i]);
			fputs(colorText, sourceTemp);
		}		
		sprintf(colorText, "%d\n",FIN);
		fputs(colorText, sourceTemp);
		//Just a color for the node
		for (int d = 0; d< numberColors; d++)
			for (int l=numberColors-1;l>0;l--){
				
				if (d != l && l>d){					
					sprintf(colorText, "-%d -%d %d\n",(u*numberColors)+ myMatrixColor[d],
					(u*numberColors)+ myMatrixColor[l],
					FIN);
					fputs(colorText, sourceTemp);				
				}
			}
		

		for (int v =  orderG()-1; v > 0;v--){	

		//Conditions color voisins		
			if (are_adjacent(u, v)==1 && (u!=v)){
				
			sprintf(colorText, "c compare neighboors %d %d \n",u,v);
			fputs(colorText, sourceTemp);
			
				for (int i = 0; i< numberColors; i++){
				// p -> -q = -p v -q
				// p node in coleur k
				// q voisin in coloeur k				
					sprintf(colorText, "-%d -%d %d\n", (u*numberColors)+ myMatrixColor[i],
					(v*numberColors)+ myMatrixColor[i],
					FIN);					
					fputs(colorText, sourceTemp);	

				}			
			}		
		}
	}
	fclose(sourceTemp);
} 


int main() {
	
 FILE* source, *target;  
 int numberColors;//par defaut

 char ch;
 char text[20];
 char init[20];

  printf("What is the number of colors.\n");
  scanf("%d",&numberColors);
 
 resolutionSAT(numberColors);
 
 sprintf(init, "p cnf %d 126\n", orderG()*numberColors);	 
 source = fopen("kcolortemp.cnf", "r"); 
 target = fopen("kcolor.cnf", "w");
 if (source == NULL) {exit(-1);}
 if (target == NULL) {exit(-1);}
 
 fputs("c test of my graphe\n", target); 
 fputs("c\n", target);
 fputs(init, target);
 
 while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
  
 printf("File copied successfully.\n");
 fclose(source);
 fclose(target);
 remove("kcolortemp.cnf");
 remove("kcolor");

 printf("Function resolutionSAT successfully created with %d colors.\n",numberColors);
 return 0;
}
