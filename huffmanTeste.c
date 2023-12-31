/*  IFMT - CAMPUS CUIABÁ - CEL. OCTAYDE JORGE DA SILVA
    CUIABÁ, 22 DE NOVEMBRO DE 2023
    PROFº JOÃO PAULO PRETI
    DISCIPLINA: ESTRUTURA DE DADOS II
    CURSO E PERIODO: ENGENHARIA DA COMPUTAÇÃO - 4º SEMESTRE
    ALUNOS: ARTHUR OCTÁVIO OLIVEIRA CONFESSOR E NICOLAS FALCÃO HEEMANN
*/

//OBS: Este código funciona melhor quando o arquivo lido .txt não contém carácteres com acentos e o 'ç'
#include "huffman.c"

int main() {
    int resp;
    printf("Olá usuário, seja bem vindo ao software COMPACTHANOS :D\n\n");
    printf("Você deseja compactar o seu arquivo txt?\n\n1-> Sim\n2-> Nao\n\nDigite: ");
    scanf(" %d",&resp);
    if(resp == 1){
        system("clear");
        unsigned char *texto;
        unsigned int tabela_frequencia[TAM];
        Lista lista;
        No *arvore;
        int colunas, tam;
        char **dicionario;
        char *codificado, *decodificado;

        FILE *arq = fopen("teste.txt", "r");

        tam = descobrir_tamanho(); 
        printf("QUANTIDADE DE CARACTERES: %d\n", tam); //QUANTIDADE DE CARACTER 
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        texto = calloc(tam + 2, sizeof(unsigned char));
        ler_texto(texto);

        inicializaTabela(tabela_frequencia);
        preencherTabelaFrequencia(texto, tabela_frequencia);

    //Lista Encadeada Ordenada
        criar_lista(&lista);
        preencher_lista(tabela_frequencia, &lista);
        imprimir_lista(&lista);

    //Árvore de Huffman 
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        arvore = montar_arvore(&lista);
        printf("ARVORE DE HUFFMAN\n");
        imprimir_arvore(arvore, 0);

        colunas = altura_arvore(arvore) + 1;
        dicionario = aloca_dicionario(colunas);
        gerar_dicionario(dicionario, arvore, "", colunas);

    //CODIFICAÇÃO E IMPRESSÃO DE ARQUIVO
        codificado = codificar(dicionario, texto);
        imprimir_em_arquivo("saida.txt", codificado); //IMPRIME UM ARQUIVO COMPACTADO DO ARQUIVO 
    //COMPACTAÇÃO
        compactar(codificado);

    //TABELA COMPARATIVA ENTRE ASCII E HUFFMAN
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        imprimirTabelaComparativa(dicionario);
    //Para fazer comparação de tamanho, transformei o arquivo teste.txt em binário, seguindo a tabela ASCII
    //Primeiro valor é o arquivo forncedio original, e o segundo é o arquivo com conteudo binário gerado
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    if (ler_converter_escrever_binario("teste.txt", "original_binario.txt") == 0) {
        printf("O arquivo .txt fornecido por você, foi transformado em binário com sucesso!\n");
    }
    //Compara o tamanho dos dois arquivos em binario. Sendo o primeiro o arquivo em binário gerado pelo arquivo dado pelo usuário
    // O segundo é o arquivo compactado gerado pelo codigo.

    comparar_tamanhos("original_binario.txt", "compactado.txt");
    //LIBERAR MEMÓRIA
        free(texto);
        free(codificado);
        liberar_lista(arvore);
        liberar_dicionario(dicionario, colunas);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("\nObrigado por usar COMPACTHANOS!! :D\n\n");
        return 0;
    }else{
        system("clear");
        printf("Obrigado por acessar o COMPACTHANOS, o melhor software de compactação de Cuiaba\n");
    }
}