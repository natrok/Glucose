#include "all.h"
#include <stdio.h>
#include <stdlib.h>

#define FIN 0 
#define Color1 1 
#define Color2 2 
#define Color3 3 
/*
1 es rojo = 1
1 es azul = 2
1 es verde = 3
2 es rojo = 4
2 es azul = 5
.
.
10 es verde = 30
*/

//number of vertices
int orderG(){
return 10;}

//number of edges
int sizeG(){
return 15;
}

int are_adjacent(int u, int v){
 if(0<= u && 0<=v && u<10 && v<10){
  int i,j,index=0;
  int T[10];
  for(i=0;i<5;i++)
   for(j=i+1;j<5;j++)
    {
     T[index]= (1 << i) + (1 << j);
     index++;
    }
  return (!(T[u] & T[v]));
 }	
 else return 0;
}


int main() {
 FILE* source, *target;
 source = fopen("petersentemp.cnf", "wr");

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
		 
		 if (are_adjacent(u, v)==1){
		
		/*Compare neighboors  || (A -> B) = -A v B  */
		sprintf(text, "c compare neighboors %d %d \n",u,v);
		fputs(text, source);		
		
		//(p->q) v (p -> r) 
		// p = nodo1 rojo 
		// q = nodo2 verde 
		// r = nodo2 azul
		// -p v q v -p v r //FNC
		sprintf(text, "-%d %d -%d %d %d\n", (u*3)+Color1,(v*3)+Color2, (u*3)+Color1, (v*3)+Color3,FIN); 
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

 sprintf(init, "p cnf %d %d\n", orderG()*3,121);	 
 source = fopen("petersentemp.cnf", "r"); 
 target = fopen("petersen.cnf", "w");
 fputs("c Le fameux graphe de Petersen. χ(G) = 3\n", target); 
 fputs("c\n", target);
 fputs(init, target);
 
 while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
  
 printf("File copied successfully.\n");
 fclose(source);
 fclose(target);
 remove("petersentemp.cnf");
 return 0;
}