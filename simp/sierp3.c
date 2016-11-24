#include "all.h"
#include <stdio.h>
#include <stdlib.h>

#define FIN 0 
#define Color1 1 
#define Color2 2 
#define Color3 3 

//number of vertices
int orderG(){
return 9;}

//number of edges
int sizeG(){
return 12;
}

//is adyacent?
int are_adjacent(int u, int v){
 if(0<= u && 0<=v && u<orderG() && v<orderG()){
  if(u/3==v/3)
   return 1; 
  if(u/3==v%3 && v/3==u%3)
   return 1;
  }
 return 0;
}

int main() {
 FILE* source, *target;
 source = fopen("sierp3temp.cnf", "wr");

 if (source == NULL) {exit(-1);}
 if (target == NULL) {exit(-1);}
  
 volatile int nb=0;
 //volatile int nclauses=0;

 char ch;
 char text[11];
 char init[10];

 
 for (int u =0; u< orderG();u++){
   /*  it could be colored in three colors but... */
	sprintf(text, "%d %d %d %d\n", (u*3)+Color1,(u*3)+Color2,(u*3)+Color3,FIN);
	fputs(text, source);

	/*it must choisir just an color*/
	sprintf(text, "-%d -%d %d\n", (u*3)+Color1,(u*3)+Color2,FIN);		
	fputs(text, source);
	
	sprintf(text, "-%d -%d %d\n", (u*3)+Color2,(u*3)+Color3,FIN);		
	fputs(text, source);

	sprintf(text, "-%d -%d %d\n", (u*3)+Color1,(u*3)+Color3,FIN);		
	fputs(text, source);

	 for (int v =  orderG(); v > 0;v--){
		 //no cliques
		 if (are_adjacent(u, v)==1 && (u!=v)){
		
		/*Compare neighboors  || (A -> B) = -A v B  */
		sprintf(text, "c compare neighboors %d %d \n",u,v);
		fputs(text, source);		

		
		//-p v (q v r)
		//(p->q) v (p -> r) 
		// p = nodo1 rojo 
		// q = nodo2 verde 
		// r = nodo2 azul
		// -p v q v -p v r //FNC
		sprintf(text, "-%d %d -%d %d %d\n", (u*3)+Color1,(v*3)+Color3, (u*3)+Color1, (v*3)+Color2,FIN); 
		fputs(text, source);		

		sprintf(text, "-%d %d -%d %d %d\n", (u*3)+Color2,(v*3)+Color3, (u*3)+Color2, (v*3)+Color1,FIN); 
		fputs(text, source);	
		
		sprintf(text, "-%d %d -%d %d %d\n", (u*3)+Color3,(v*3)+Color1, (u*3)+Color3, (v*3)+Color2,FIN); 
		fputs(text, source);
		nb+=7;
		}
	}	
 } 
 
 fclose(source); 

 sprintf(init, "p cnf %d 126\n", orderG()*3);	 
 source = fopen("sierp3temp.cnf", "r"); 
 target = fopen("sierp3.cnf", "w");
 
 fputs("c Un graphe à 9 sommets, dit de Sierpinski. χ(G) = 3\n", target); 
 fputs("c\n", target);
 fputs(init, target);
 
 while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
  
 printf("File copied successfully.\n");
 fclose(source);
 fclose(target);
 remove("sierp3temp.cnf");
 remove("sierp3");
 printf("Function resolutionSAT successfully.\n");
 return 0;
}
