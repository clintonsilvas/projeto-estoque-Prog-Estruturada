#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char descricao[30];
  float preco_venda;
  char unidade;
  char fornecedor[40];
  char status;
  int quant_est;
} produto;

int tamanho(FILE *);
void cadastro(FILE *);
void consultar(FILE *arquivoBin);
void consulta_codigo(FILE *arquivoBin);
void consulta_descricao(FILE *arquvoBin);

int main(void) {
  int op;
  FILE *arquivoBin;
  if ((arquivoBin = fopen("arquivo.dat", "rb+")) == NULL) {

    if ((arquivoBin = fopen("arquivo.dat", "wb+")) == NULL) {
      printf("Erro ao abrir o arquivo");
      system("pause");
    }
  }

  do {
    system("clear");
    printf("\n========= ESTOQUE =========== \n");
    printf("1.Cadastrar produto\n");
    printf("2.Consultar produto\n");
    printf("3.Gerar arquivo\n");
    printf("4.Excluir registro\n");
    printf("5.Sair\n");
    printf("======= Produtos Cadastrados:%d=\n", tamanho(arquivoBin));
    printf("Opcao:");
    scanf("%d", &op);
    switch (op) {
    case 1:
      cadastro(arquivoBin);
      break;
      case 2:
      consultar(arquivoBin);
      break;
  }
}while (op != 5);

  
    return 0;
}

//=======================================================================//
int tamanho(FILE *arquivo) {
  fseek(arquivo, 0, SEEK_END);
  return ftell(arquivo) / sizeof(produto);
}

void cadastro(FILE *arquivoBin) {
  produto produto;
  char confirma;
  produto.status = ' ';
  fflush(stdin);

  printf("Cadastrando produto:\n");
  printf("\nNúmero do registro: %d\n", tamanho(arquivoBin) + 1);
  printf("Nome..........:");
  getchar();
  gets(produto.descricao);
  printf("Preço de venda:");
  scanf("%f", &produto.preco_venda);
  printf("Unidade.......:");
  scanf("%s", &produto.unidade);
  printf("Fornecedor....:");
  gets(produto.fornecedor);
  getchar();
  printf("Quantidade....:");
  scanf("%d", &produto.quant_est);
  printf("\nConfirma cadastro? (s/n)");
  fflush(stdin); // limpar buffer
  scanf(" %c", &confirma);

  if (confirma == 's' || confirma == 'S') {
    printf("\ngravando...\n\n");
    fseek(arquivoBin, 0, SEEK_END);
    fwrite(&produto, sizeof(produto), 1, arquivoBin);
    printf("==Produto cadastrado com sucesso==");
  }
  system("pause");
}

void consultar(FILE *arquivoBin) {
  produto produto;
  int id_consultar;
  char produto_consultar, opcao;
  printf("\n==Consulta de produtos cadastrados.==\n");
  do {
    printf("\nDejesa consultar por:");
    printf("\n1.Código");
    printf("\n2.Descrição");
    printf("\n3.Voltar");
    printf("\nOpção:");
    scanf("%c", &opcao);
    switch (opcao) {
      case 1:
        consulta_codigo(arquivoBin);
        break;
      case 2:
        consulta_descricao(arquivoBin); 
        break;
    }    
  }while (opcao != '3');
}

void consulta_codigo(FILE *arquivoBin){
  produto produto;
  int id_consultar;  
  printf("\n=== Digite o código do produto: ===\n");
  scanf("%d", &id_consultar);
  if ((id_consultar <= tamanho(arquivoBin)) && (id_consultar > 0)) {
    fseek(arquivoBin, (id_consultar - 1) * sizeof(produto), SEEK_SET);
    fread(&produto, sizeof(produto), 1, arquivoBin);
    if (produto.status == ' ') {            
      printf("\nDescrição:.......:%s", produto.descricao);
      printf("\nPreço de venda:..:%f", produto.preco_venda);
      printf("\nUnidade:.........:%c", produto.unidade);
      printf("\nFornecedor:......:%s", produto.fornecedor);
      printf("\nEstique:.........:%d", produto.quant_est);
    } else
      printf("\nProduto inativo.\n");
  } else
    printf("\nProduto não encontado;");
  
}

void consulta_descricao(FILE *arquvoBin){
  produto produto;
  char produto_consultar;
  printf("==Digite a descrição do produto==\n");          
  fseek(arquvoBin, 0, SEEK_SET); // Posicionar o ponteiro no início do arquivo
  while (fread(&produto, sizeof(produto), 1, arquvoBin) == 1) {
    if (strcmp(produto.descricao, produto_consultar) == 0) {//procura pela descricao
      if (produto.status == ' ') {
        printf("\nDescrição:.......:%s", produto.descricao);
        printf("\nPreço de venda:..:%f", produto.preco_venda);
        printf("\nUnidade:.........:%c", produto.unidade);
        printf("\nFornecedor:......:%s", produto.fornecedor);
        printf("\nEstoque:.........:%d", produto.quant_est);
      } else {
        printf("\nProduto inativo.\n");
      }
      break; // Produto encontrado, encerra o loop
    }
  }
  if (feof(arquvoBin)) {
      // Chegou ao final do arquivo sem encontrar o produto
      printf("\nProduto não encontrado.\n");
  }
  
}

