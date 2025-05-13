#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  int i,j,k;
  for(int i = 0; i < 9 ; i++){
    int usados[10] = {0};
    for(j = 0; j < 9 ; j++ ){
      int valor = n->sudo [i][j];
      if(valor != 0){
        if(usados[valor]){
          return 0;
        }
        usados[valor] = 1;
      }
    }
  }
  for (j = 0 ; j < 9 ; j++ ){
    int usados[10] = {0};
    for(i = 0 ; i < 9 ; i ++){
      int valor = n->sudo [i][j];
      if (valor != 0 ){
        if (usados[valor]){
          return 0 ;
        }
        usados[valor] = 1;
      }
    }
  }
  for (k=0 ; k < 9 ; k++){
    int usados[10] = {0};
    for(int p = 0 ; p < 9 ; p ++){
      int i = 3 * ( k / 3 ) + ( p / 3 );
      int j  = 3 * ( k % 3 ) + ( p % 3 );
      int valor = n->sudo[i][j];
      if(valor != 0 ){
        if(usados[valor]){
          return 0;
        }
        usados[valor] = 1;
      }
    }
  }

    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();

  int fila = -1;
  int columna = -1;
  for (int i = 0 ; i < 9 && fila  == -1 ; i++){
    for(int j = 0 ; j < 9 && columna == -1; j++){
      if (n->sudo[i][j] == 0 ){
        fila = i ;
        columna = j;
        break;
      }
    }
  }
  if (fila == -1 && columna == -1){
    return list;
  }
  for(int valor = 1; valor <= 9 ; valor ++){
    Node * nuevo = copy(n);
    nuevo->sudo[fila][columna] = valor;
    if(is_valid(nuevo)){
      pushBack(list, nuevo ); 
    }
    
  }

  return list;
}


int is_final(Node* n){

  for (int i = 0; i<9; i++){
    for(int j = 0 ; j < 9 ; j++){
      if(n->sudo[i][j]==0){
        return 0;
      }
    }
  }

  return 1;
}

Node* DFS(Node* initial, int* cont){

  Stack* S = createStack();
  pushFront (S , initial);
  while(!isEmpty(S)){
    Node * current = Front(S);
    popFront(S);
    (*cont)++;
    if(is_final(current)){
      return current;
    }
    List * adj = get_adj_nodes(current);
    Node * adjnode = first(adj);
    while(adjnode!=NULL){
      pushFront(S, adjnode);
      adjnode = next(adj);

    }
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/