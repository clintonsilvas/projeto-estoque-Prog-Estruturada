#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int id;
  char nome[30];
  float preco_venda; 
  char fornecedor;
  char status;
}produto;

void cadastro(FILE*);

int main(void) {
  int op; 
  FILE *arquivo;
  if ((arquivo=fopen("arquivo.dat","rb+"))==NULL){
    
  if ((arquivo=fopen("arquivo.dat", "wb+"))==NULL){
    printf("Erro ao abrir o arquivo");
    system ("pause");
    
    }
  }
  printf("Escolha uma opção: ");
  printf("\nCadastrar produto: ");
  
  
  do{
    
  }while(op!=5);
  return 0;
}

void cadastro(FILE*arquivo){
  reg contato; 
  char confima;
  fflush(stdin);
  printf("Cadastrando novo registrado: \n");
  printf("Digite o numero do registro:%d\n", ta  manho(arquivo)+1 );
  printf("Nome:");
  scanf("%[^\n]c", contato.nome);
  printf("Telefone:");
  
}