#include "all.h"
#include <stdio.h>
#include <stdlib.h>

#define FIN 0    /* End of clause marker */

//number of vertices
int orderG(){
return 20;}

//number of edges
int sizeG(){
return 10;}

//States if the two vertices are adjacent
int are_adjacent(int u, int v){
if(0<= u && 0<=v && u<orderG() && v<orderG()){
  return (u+v==19);
 }	
 else return 0;
}

int main() {
 FILE* source, *target;
 source = fopen("test10k2temp.cnf", "wr");
 target = fopen("10k2.cnf", "w");

 volatile int nb=0;
 volatile int nclauses=0;

 char ch;
 char text[10];
 char init[10];

 for (int u =0; u< orderG();u++)
	 for (int v =  orderG(); v > 0;v--){
		 
		 if (are_adjacent(u, v)==1 && nb < sizeG() ){
		nb++;
		//(P -> -Q) = -p v -q || -P -> Q = p v q
		sprintf(text, "%-d %-d %d\n", u+1,v+1,FIN);
		fputs(text, source);
		sprintf(text, "%d %d %d\n", u+1,v+1,FIN);
		fputs(text, source);
		nclauses +=2;		
       }
	}
 fclose(source);

 source = fopen("test10k2temp.cnf", "r");
 sprintf(init, "p cnf %d %d\n", nclauses,orderG());	
 fputs("c L'union de 10 graphes à deux sommets et une arête. χ(G) = 2\n", target);
 fputs("c\n", target);
 fputs(init, target);
 
 while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 printf("File copied successfully.\n");
 fclose(source);
 fclose(target);
 remove("test10k2temp.cnf");
 return 0;
}

