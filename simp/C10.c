#include "all.h"
#include <stdio.h>
#include <stdlib.h>

#define FIN 0    /* End of clause marker */

//number of vertices

int orderG(){
return 10;}

int sizeG(){
return 10;}

int are_adjacent(int u, int v){
 if(0<= u && 0<=v && u<10 && v<10){
  return (((10+u-v)%10==1)||((10+v-u)%10==1));
 }	
 else return 0;
}


int main() {
 FILE* source, *target;
 source = fopen("C10temp.cnf", "wr");


 volatile int nb=0;
 volatile int nclauses=0;

 char copy;
 char text[10];//restrictions
 char init[10];//init clauses of cnf final file

 for (int u =0; u< orderG();u++)
	 for (int v =  orderG();v > 0;v--){
		 
		if (are_adjacent(u, v)==1){
		nb++;		
			
		sprintf(text, "c compare neighboors %d %d \n",u+1,v+1);
		fputs(text, source);	
		 
		sprintf(text, "%d %d %d\n", u+1,v+1,FIN);
		fputs(text, source);		

		sprintf(text, "-%d -%d %d\n", u+1,v+1,FIN);
		fputs(text, source);

		nclauses +=2;	
       }
	}
 fclose(source);

 source = fopen("C10temp.cnf", "r");
 target = fopen("C10.cnf", "w");

 sprintf(init, "p cnf %d %d\n", orderG(),20);	
 fputs("c Cycle à 10 sommets. χ(G) = 2\n", target);
 fputs("c\n", target);
 fputs(init, target);
 
 while( ( copy = fgetc(source) ) != EOF )
      fputc(copy, target);
 printf("File copied successfully.\n");
 fclose(source);
 fclose(target);
 remove("C10temp.cnf");
 return 0;
}