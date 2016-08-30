//  ALUNO: Thiago Anderson Martins  |  MATRICULA: UC11010081
//               ________      ________     _______          __      _________    _____________     ________
//              |   ___  |    |   ___  |   |  ___  |        |  |    |   ______|  |____    _____|   |  ____  |
//              |  |___| |    |  |___| |   | |   | |    _   |  |    |  |______        |  |         | |    | |
//              |   _____|    |     ___|   | |   | |   | |  |  |    |   ______|       |  |         | |    | | 
//              |  |          | | \ \      | |___| |   | |_/  /     |  |______        |  |         | |____| |
//              |__|          |_|  \_\     |_______|   \_____/      |_________|       |__|         |________|
//                        
//                                                        F I N A L
//    
//===============================================================================================================================         
//                                                        SÍNTESE   
//                  -------------------------------------------------------------------------------------------------------------                                                                                                                            
//       Objetivo   : Permitir o cadastramento de frequentadores,séries de exercicios e atividades, disponibilizar a alteração
//                    e exclusão de qualquer dado e realizar relatórios sob todos os dados da academia.
//                  -------------------------------------------------------------------------------------------------------------
//       Entrada    : CPF,nome do cliente,peso,sexo, nome da série,duração da série,descrição,data e calorias.
//                  -------------------------------------------------------------------------------------------------------------
//       Saida      : Nome,Cpf,peso,sexo,Nome da série,Duração da série,Descrição,data,hora,calorias.
//=============================================================================================================================== 
#include <conio.c>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>
#define MAX_FRASE 202
#define MAX_NOME 42
#define TAM_NOME 42
#define MAXHORA 9
#define MAX_CPF 42 
#define MAXDATACOMPARAR 2
#define NOMEARQCLIENTE "cadastroClientes.txt"
#define NOMEARQSERIE "cadastroSeries.txt"
#define NOMEARQATIVIDADE "Atividades.txt"

//                                                    E S T R U T U R A S
//                      ESTRUTURA SERIES
struct dadosSerie
{
    int codigo;               
    int duracao;              
    char frase[MAX_FRASE];   
    char nomeSerie[MAX_NOME]; 
    float calorias;          
};
//                  ESTRUTURA FREQUENTADORES
/*struct cliente
{
	char nome[TAM_NOME];      
	char cpf[TAM_NOME];
	float peso;
	char sexo;
	int dia;
	int mes;
	int ano; 
};*/
struct cliente
{
        char cpf[TAM_NOME];
        char nome[TAM_NOME];
        float peso;
        char sexo;
        int dia,mes,ano;
};
//                     ESTRUTURA ATIVIDADES
struct dadosAtividades
{
       char cpf[MAX_CPF];
       int codigo;
       int dia;
       int mes;
       int ano;
       char hora[MAXHORA];
};
typedef struct cliente tipoFrequentador;
typedef struct dadosSerie tipoSerie;
typedef struct dadosAtividades tipoAtividade;
//                                                   P R O T Ó T I P O S 

// -----------------------------------------------------------A-------------------------------------------------------------------------
FILE * abreArquivo (char *nomeArq, char *modo, char *msgErro);                      // F)
void alteraDescricaoSerie(FILE *arq, long posicao,char opcao, int codigoDigitado);  // T) Alterar a descrição da série.
void alteraCaloriasSerie(FILE *arq, long posicao,char opcao, int codigoDigitado);   // T) Alterar Calorias da série.
void alteraNomeSerie(FILE *arq,long posicao,char opcao, int codigoDigitado);        // T) Alterar o nome da série.
long achaRegistroAtividades(int qualRegistro, char *pCpf, FILE *arq);               // T)
void alteraMinutosSerie(FILE *arq, long posicao,char opcao, int codigoDigitado);    // T) Alterar a duração de uma série.
void apontaParaEscolhaLista(int contador);                                          // T)
void abreTodosOsArquivos(FILE *arqSerie,FILE *arqCliente,FILE *arqAtividade);       // T)
void achaClientesComSerie(FILE *arqAtividades, FILE *arqCliente,int *pCodigoDigitado);   // T)
void achaMostraAtividadesData(char *pCpfDigitado, FILE *arqAtividades,FILE *arqSeries,int *pDia,int *pMes,int *pAno);
void achaMostraClientesData(int *pAno,int *pMes,int *pDia,FILE *arqAtividades,FILE *arqClientes);
void achaTempoEcalorias(FILE *arqSeries,int *pTempo, float *pCalorias,int codigo);
void achaClientesAusentes(FILE *arq,int *pDia,int *pMes,int *pAno,int diasAusente,FILE *arqCliente);
int achaClientePorCpf(FILE *arqCliente,char *cpfComparar,int contador2);
//void apresentaDadosClientes(char *pCpf,char *pNome,float *pPeso,char *pSexo,int *pDia,int *pMes,int *pAno);
void apresentaDadosClientes(struct cliente *pEstrutura);
void alteraNomeCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado);
void alteraPesoCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado);
void alteraSexoCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado);
void alteraDiaCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado);
void alteraMesCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado);
void alteraAnoCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado);
void achaEmostraRegistroDeletar(FILE *arq,char *pCpfDigitado);
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------C-------------------------------------------------------------------------
void capsLock(char *pCaracteres);                                     // T) tranformar caracteres em maiusculo.
int ctoi(char ch);                                                    // F)
void cadastroConcluido(int cor);                                      // T) Apresentar a mensagem "cadastro concluido"
void chamaFuncoesAlterar(char opcao,int qualFuncao, FILE *arq,FILE *arqAtividades,char modo);// T)
int confirmaDadosAcima();                                             // T)
void criaTempComResumo(FILE *temp,int tempo,float calorias,int dia,int mes,int ano);
void chamaListagemTemp(FILE *temp);
int comparaString(const void *stringA,const void *stringB);
void criaTempCpf(FILE *temp, char *pCpfAchado);
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------D-------------------------------------------------------------------------
void deletarRegistroAtividades(FILE *arq,long apontador,int tamanhoStruct);   //T)
int deletarRegistro(FILE *arq,long apontador,int tamanhoStruct);              //T) Deletar um registro.
void digiteAserie();                                                          //T) 
void digiteAdescricao(char *descricao);                                       //T)
void digiteOsMinutos();                                                       //T)
void digiteAsCalorias();                                                      //T)
void deletarRegistroClientes(FILE *arq,long apontador,int tamanhoStruct);
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------E-------------------------------------------------------------------------
void excluiAtividade(FILE *arq, char *pCpf); // T)
void escreveQualquerCoisa(char *pFrase,int cor,int cordenadaX,int cordenadaY);
void escreveQualquerInteiro(int *pInt,int cor,int cordenadaX,int cordenadaY);
void escreveQualquerString(char *pString,int cor,int cordenadaX,int cordenadaY);
void escreveNomeCliente(FILE *arq,char *pCpfDigitado,int cor,int cordenadaX,int cordenadaY);
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------G-------------------------------------------------------------------------
void gravaDados(FILE *arqClientes,struct cliente *cadastro);                       // T)
void gravaDadosSeries(FILE *arqSeries,struct dadosSerie *series);                  // T)
void gravaDadosAtividades(FILE *arqAtividades,struct dadosAtividades *atividades); // T)
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------L-------------------------------------------------------------------------
void leValidaString (char *string);                                      // F)
void leValidaFloat(float *nro, float minimo, float maximo);              // F)
void leValidaMenuAlterarSeries(char opcao,int codigoDigitado,FILE *arq); // T)
void leValidaSexo(char *pSexo);                                          // T)
void leCharPorChar(char *pNomeFrase, int maximo);                        // T)
void limpaTelaCordenada(int x, int y, int tamanho,char parametro);       // T) Função util para limpar uma certa linha.
void leCharPorCharDescricao(char *pNomeFrase, int maximo);               // T)
int leValidaNumeros(int min, int max,int maximo);                        // T)
void limpaTelaEfeito();                                                  // T)
void limpaTelaEfeitoVertical();                                          // T)
void limpaTelaCordenadaVertical(int x, int y, int tamanho,char parametro); // T)
char leValidaNumeroLista(int min, int max,int maximo);
int leValidaDia(int *pAno, int *pMes, int *pDia);                    // T);
int leValidaMes(int *pMes);
int leValidaAno(int *pAno);
int leValidaDataDeAte(int *pAno, int *pMes, int *pDia);
void listaTempResumo(int *pDia,int *pMes, int *pAno, float *pCalorias,int *pTempo,int linha);
void leValidaMenuAlterarClientes(char opcao,char *pCpfDigitado,FILE *arq);
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------M-------------------------------------------------------------------------
//void apresentaDadosSeries(int *pCodigo,int *pDuracao,char *pFrase,char *pNomeSerie,float *pCalorias);
void apresentaDadosSeries(struct dadosSerie *pEstrutura);
void maiusculo(char *string);                                               // F)
long mostraRegistroPesquisado(FILE *arq, long tamanho, int codigoDigitado); // T)
int mostraAtividades(FILE *arq, long apontador,char *pCpf);                 // T)
void molduraNumeros();                                                      // T)
void mostraCodigoGerado(int contador);                                      // T)
void mostraDigiteF11();                                                     // T)
char mostraMenuF11();                                                       // T)
char mostraMenuF11Atividades();                                             // T)
void mostraImpossivelDeletar();                                             // T)
void mostraDadosFrequentador(char *pCpfDigitado, FILE *arq,char modo);      // T)
void mostraDadosSeries(int *pCodigoDigitado, FILE *arq,char modo);          // T)
void mostraDadosAtividades(char *pCpfDigitado, FILE *arq,char modo);        //  T)
long mostraRegistroPesquisadoClientes(FILE *arq, long tamanho,char *pCpfDigitado);
void mostraImpossivelDeletarClientes();
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------V-------------------------------------------------------------------------
int validaCPF(char nroCpf[12]);                                                  // F)
int validaCpfRepetido(FILE *arq,struct cliente cadastro);                        // T)
int verificaCodigoSerie(FILE *arq,int codigoDigitado,struct dadosSerie series);  // T) verifica se o codigo digitado existe.
void validaSerieRepetida2(FILE *arq,char *pNomeDigitado);                        // T)
void validaCodigoRepetido(FILE *arq,int *pCodigoDigitado,int tamanhoStruct);     // T) validar código repetido.
int verificaSeFezAtividade(int codigo,FILE *arq, int tamanhoStruct);             // T)
int verificaCpfAtividades(char *pCpf, FILE *arq);                                // T)
void naoRepeteCpf(FILE *arq,char *pCpfDigitado,int tamanho);                     // T)
int verificaCpfExiste(FILE *arq,char *pCpfDigitado,int tamanho);                 // T)
void voltarAoMenu0();                                                            // T)
int verificaSeFezAtividadeHoje (struct dadosAtividades *atividades, FILE *arq);  // T)
void verificaNomeSerieSemelhante(char *pNomeDigitado, FILE *arq,char modo,FILE *arqAtividades);                // T)
int verificaAnoBisexto(int ano);                                                     // T)
int validaDia (int dia, int mes, int bisexto);
int verificaCpfFezAtividade(char *pCpfDigitado,FILE *arqAtividades);
int verificaEntreDatas(int anoLido,int mesLido,int diaLido,int *pAno,int *pMes, int *pDia);
//--------------------------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------O-------------------------------------------------------------------------o
void operacaoCancelada();                           // T) mostrar a mensagem "operação cancelada"
void obtemDataAtual(int *dia, int * mes, int *ano); // F) PEGAR A DATA (funcionando!) 
long obtemTamanhoArquivo(FILE *arq,char *pNomeArquivo);// T)
void ordenaPorNome(FILE *arq,char *pNomeDigitado);
//--------------------------------------------------------------------------------------------------------------------------------------
int leValidaMenuPrincipal(int opcao);
void mostraMenu();
void fazMoldura();
void fazMolduraEscolha(int x,int y, int cor);
int leValidaMenu(char opcao, int escolha);
void mostraVoltarAoMenu();
int quantidadeSetasMenu(char opcao, int maximo, int aux);
void paraSairDigiteSair();
void fazMolduraCadastros(int cor);
void molduraNomes(int cor);
void molduraDescricao();
int simOuNao(int cor,int x, int y);
void fazMolduraF11();
void criaMiniTelaAzul(int cor);
void criaGrandeTelaAzul(int cor);
//void fazListagemSeries(char *pNome,int codigo,int duracao,float calorias,char *pFrase, int linha);
void fazListagemSeries(struct dadosSerie *pEstrutura,int lista);
void fazMolduraListagemSeries(int linha);
int pedeNumeroSerieAlterar(int linha);
void nenhumDadoEncontrado();
void verificaDuracaoSerieSemelhante(int duracaoSerie, FILE *arq,char modo,FILE *arqAtividades);
void verificaCaloriaSerieSemelhante(float caloriaDigitada, FILE *arq,char modo,FILE *arqAtividades);
void verificaDescricaoSerieSemelhante(char *pNomeDigitado, FILE *arq,char modo,FILE *arqAtividades);
int leValidaOpcao1Relatorio(int contador);
int menuEscolhaTipoPesquisa();
//void fazListagemClientes(char *pCpf,char *pNome,float peso,char sexo,int dia,int mes,int ano, int linha);
void fazListagemClientes(struct cliente *pEstrutura,int lista);
void fazMolduraListagemClientes(int linha);
//void fazListagemAtividades(char *pCpf,int codigo,int dia,int mes,int ano,char *pHora, int linha);
void fazListagemAtividades(tipoAtividade *estrutura,int linha);
void fazMolduraListagemAtividades(int linha);
int quantidadeSetasMenuHorizontal(char opcao, int maximo, int aux); 
//void leUmaStructClientesCpf(char *pCpfDigitado,FILE *arqClientes,char *pCpfLido,char *pNomeLido,float *pPesoLido,char *pSexoLido,int *pDiaLido,int *pMesLido,int *pAnoLido);
void leUmaStructClientesCpf(char *pCpfDigitado,FILE *arqClientes,tipoFrequentador *estrutura);
void fazMolduraData();
void fazMolduraListagemResumo(int linha);
int retornaMaxDiasMes(int mes,int ano);
void subtraiData(int *pDia,int *pMes,int *pAno,int qntDias);
//----------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
// Declaracoes
              char stringComparar[MAX_NOME],cpfDigitado[TAM_NOME],opcaoChar, *pNome=NULL, *pOutro=NULL, nomeDigitado[TAM_NOME];
              int contSeries=0,verdadeiroContSeries=0,opcao,codigoDigitado,cont=0,bytesSeries,deletou,verdadeiroValor,bytesAtividades;
              int achou,bytesClientes,escolha,escolha2,confirmou=0,fezAtividade=0,aux=0,diaComp[MAXDATACOMPARAR],mesComp[MAXDATACOMPARAR],anoComp[MAXDATACOMPARAR];
              struct cliente cadastro;
              struct dadosSerie series;
              struct dadosAtividades atividades;
              FILE *arqSerie;                          
              FILE *arqCont;                            
              FILE *arqClientes;                     
              FILE *arqAtividades;
              long apontador;
// Instrucoes
  bytesSeries = sizeof(series);                              
  fflush(stdin);
  bytesAtividades = sizeof(atividades);                       
  fflush(stdin);
  bytesClientes = 101;
  abreTodosOsArquivos(arqSerie,arqClientes,arqAtividades);
  if (arqCont = fopen("contadores.txt","rb"))                 
  {                                                                                                                                 
      fread(&contSeries,sizeof(int), 1, arqCont);                                                     
      fclose(arqCont);                                       
      verdadeiroContSeries = contSeries + verdadeiroValor;
  }
  escolha = 1;
  do
  {
      escolha = leValidaMenuPrincipal(escolha);
      switch(escolha) // Escolha do primeiro menu.
      {
//--------------------------------------------------------------------------------------------------------------------------------------
//                                                    F R E Q U E N T A D O R E S              cc1
//--------------------------------------------------------------------------------------------------------------------------------------
                     case 1: // FREQUENTADORES
                     {
                           clrscr();
                           escolha2 = leValidaMenu(escolha2,escolha);
                           switch(escolha2) 
                           {
                                           case 1: // CADASTRO DE FREQUENTADORES                
                                           {
                                                    limpaTelaEfeitoVertical();
                                                    fazMolduraCadastros(49999);
                                                    paraSairDigiteSair();
                                                    do
                                                    {
                                                        escreveQualquerCoisa("INFORME O CPF DO NOVO FREQUENTADOR",15,24,11);
                                                        leCharPorChar(cadastro.cpf,10);
                                                        limpaTelaCordenada(27,17,29,' ');
                                                        limpaTelaCordenada(22,14,40,' ');
                                                        escreveQualquerCoisa("   PARA VOLTAR AO MENU DIGITE ESQ   ",79,23,25);
                                                        escreveQualquerCoisa("   CPF INVALIDO! DIGITE NOVAMENTE   ",79,23,24);
                                                        if (cadastro.cpf[0] == 27)
                                                        {
                                                           limpaTelaEfeito();
                                                           break;
                                                        }
                                                    }while(!validaCPF(cadastro.cpf));
                                                    if (cadastro.cpf[0] == 27)
                                                    {
                                                       limpaTelaEfeito();
                                                       break;
                                                    }
                                                    do
                                                    {
                                                        if (!validaCPF(cadastro.cpf))
                                                           leCharPorChar(cadastro.cpf,10);
                                                        naoRepeteCpf(arqClientes,cadastro.cpf,bytesClientes);
                                                        limpaTelaCordenada(27,17,29,' ');
                                                        limpaTelaCordenada(22,14,40,' ');
                                                        escreveQualquerCoisa("   PARA VOLTAR AO MENU DIGITE ESQ   ",79,23,25);
                                                        escreveQualquerCoisa("   CPF INVALIDO! DIGITE NOVAMENTE   ",79,23,24);
                                                        if (cadastro.cpf[0] == 27)
                                                        {
                                                           limpaTelaEfeito();
                                                           break;
                                                        }
                                                    }while(!validaCPF(cadastro.cpf));
                                                    if (cadastro.cpf[0] == 27)
                                                    {
                                                       limpaTelaEfeito();
                                                       break;
                                                    }
                                                    clrscr();
                                                    fazMolduraCadastros(49999);
                                                    paraSairDigiteSair();
                                                    escreveQualquerCoisa("INFORME O NOME DO CLIENTE:",15,28,11);
                                                    leCharPorChar(cadastro.nome,10);
                                                    if (cadastro.nome[0] == 27)
                                                    {
                                                       limpaTelaEfeito();
                                                       break;
                                                    }
                                                    clrscr();
                                                    fazMolduraCadastros(49999);
                                                    paraSairDigiteSair();
                                                    leValidaSexo(&cadastro.sexo);
                                                    if (cadastro.sexo == '0')
                                                    {
                                                       limpaTelaEfeito();
                                                       break;
                                                    }
                                                    clrscr();
                                                    fazMolduraCadastros(49999);
                                                    paraSairDigiteSair();
                                                    escreveQualquerCoisa("INFORME O PESO EM KG:",15,31,11);
                                                    cadastro.peso = leValidaNumeros(0,290,5); //N FLOAT
                                                    if (cadastro.peso == -1)
                                                    {
                                                       limpaTelaEfeito();
                                                       break;
                                                    }
                                                    clrscr();
                                                    obtemDataAtual(&cadastro.dia,&cadastro.mes,&cadastro.ano);
                                                    //apresentaDadosClientes(cadastro.cpf,cadastro.nome,&cadastro.peso,&cadastro.sexo,&cadastro.dia,&cadastro.mes,&cadastro.ano);
                                                    apresentaDadosClientes(&cadastro);
                                                    opcao = confirmaDadosAcima();
                                                    if (opcao == 1)
                                                    {
                                                         gravaDados(arqClientes,&cadastro); 
                                                         criaMiniTelaAzul(31);
                                                         escreveQualquerCoisa("CADASTRO CONCLUIDO!",31,30,15);
                                                         escreveQualquerCoisa("Digite qualquer coisa...",31,29,20);
                                                         getch();
                                                         break;
                                                    }
                                                    else
                                                        operacaoCancelada();
                                                    break;
                                           }
                                           case 2: //  ALTERAÇÕES DE FREQUENTADORES            <- cc1
                                           {
                                                limpaTelaEfeitoVertical();
                                                fazMolduraCadastros(49999); 
                                                textcolor(WHITE); 
                                                paraSairDigiteSair();  
                                                gotoxy(19,12);
                                                escreveQualquerCoisa("DIGITE O CPF DO CLIENTE QUE DESEJA ALTERAR",15,19,12);
                                                do
                                                {
                                                    leCharPorChar(cpfDigitado,10);
                                                    limpaTelaCordenada(17,17,47,' ');
                                                    if (cpfDigitado[0] != 27)
                                                       aux = verificaCpfExiste(arqClientes,cpfDigitado,101);
                                                    else
                                                        aux=-1;
                                                }while(aux==0);
                                                if (aux == -1)
                                                   break;
                                                if (cpfDigitado[0] == 27)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }  
                                                clrscr();
                                                leValidaMenuAlterarClientes(opcaoChar,cpfDigitado,arqClientes);
                                                limpaTelaEfeitoVertical();
                                                break;
                                           }   
                                           case 3: // DELETAR FREQUENTADORES.                  <-
                                           {
                                                limpaTelaEfeitoVertical();
                                                fazMolduraCadastros(49999); 
                                                textcolor(WHITE); 
                                                paraSairDigiteSair();  
                                                gotoxy(19,12);
                                                escreveQualquerCoisa("DIGITE O CPF DO CLIENTE QUE DESEJA DELETAR",15,19,12);
                                                do
                                                {
                                                    leCharPorChar(cpfDigitado,10);
                                                    limpaTelaCordenada(17,17,47,' ');
                                                    if (cpfDigitado[0] != 27)
                                                       aux = verificaCpfExiste(arqClientes,cpfDigitado,101);
                                                    else
                                                        aux=-1;
                                                }while(aux==0);
                                                if (aux == -1)
                                                   break;
                                                if (cpfDigitado[0] == 27)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }  
                                                limpaTelaEfeito();
                                                aux = verificaCpfFezAtividade(cpfDigitado,arqAtividades);
                                                if (aux)
                                                {
                                                        mostraImpossivelDeletarClientes();
                                                        break;
                                                }
                                                else
                                                {
                                                    achaEmostraRegistroDeletar(arqClientes,cpfDigitado);
                                                }
                                                break;
                                           }       
                           }
                           break;
                     }
//--------------------------------------------------------------------------------------------------------------------------------------
//                                                            S É R I E S                     ss1 
//--------------------------------------------------------------------------------------------------------------------------------------
                     case 2: // SERIES
                     {
                           clrscr();
                           escolha2 = leValidaMenu(escolha2,escolha);    
                           switch(escolha2)
                           {
                                           case 1:      // CADASTRO DE SERIES  [ ok ]             
                                           {       
                                                 limpaTelaEfeitoVertical();
                                                 fazMolduraCadastros(49999); // parâmetro é a cor
                                                 paraSairDigiteSair();                                                             
                                                 digiteAserie();
                                                 molduraNomes(15);
                                                 leCharPorChar(&series.nomeSerie[0],MAX_NOME);
                                                 strcpy(stringComparar,series.nomeSerie);
                                                 capsLock(stringComparar);
                                                 validaSerieRepetida2(arqSerie,series.nomeSerie);
                                                 if (series.nomeSerie[0] == 27)
                                                 {
                                                    limpaTelaEfeito();
                                                    break;
                                                 }
                                                 strcpy(stringComparar,series.nomeSerie);
                                               	 capsLock(stringComparar);
                                                 clrscr();
                                                 digiteAdescricao(stringComparar);
                                                 leCharPorCharDescricao(&series.frase[0],MAX_FRASE);
                                                 if (series.frase[0] == 27)
                                                 {
                                                    limpaTelaEfeito();
                                                    break;
                                                 }
                                                 clrscr();
                                                 digiteOsMinutos();
                                                 series.duracao = leValidaNumeros(0,120,4);
                                                 if (series.duracao == -1)
                                                 {
                                                    limpaTelaEfeito();
                                                    break;
                                                 }
                                                 digiteAsCalorias();
                                                 series.calorias = leValidaNumeros(0,400,4);
                                                 if (series.calorias == -1)
                                                 {
                                                    limpaTelaEfeito();
                                                    break;
                                                 }
                                                 limpaTelaEfeito();
                                                // apresentaDadosSeries(&series.codigo,&series.duracao,series.frase,series.nomeSerie,&series.calorias); 
                                                 apresentaDadosSeries(&series); 
                                                 opcao = confirmaDadosAcima();
                                                 if (opcao == 1)
                                                 {
                                                           mostraCodigoGerado(contSeries);
                                                           series.codigo = (1000 + contSeries);// Geração de um código que sempre será unico.
                                                           gravaDadosSeries(arqSerie,&series);// já fecha o arquivo
                                                           contSeries++;
                                                           verdadeiroContSeries++;
                                                           arqCont = abreArquivo("Contadores.txt","wb","Erro ao tentar abrir o arquivo de contadores!");
                                                           fwrite(&contSeries,sizeof(int),1,arqCont);
                                                           fclose(arqCont);
                                                           getch();   
                                                           limpaTelaEfeito(); 
                                                 }else
                                                  {
                                                      operacaoCancelada();
                                                  }                                       
                                                break;
                                           }
                                           case 2:     // ALTERAÇÃO DE SERIES           [ ok ] 
                                           {
                                                limpaTelaEfeitoVertical();
                                                fazMolduraCadastros(49999); // parâmetro é a cor
                                                textcolor(WHITE); 
                                                paraSairDigiteSair(); 
                                                mostraDigiteF11(); 
                                                gotoxy(19,12);
                                                printf("DIGITE O CODIGO DA SERIE QUE DESEJA ALTERAR:");
                                                codigoDigitado = leValidaNumeros(999,9999,5);
                                                if (codigoDigitado == -1) // -1 quando apertar ESQ
                                                {
                                                       limpaTelaEfeito();
                                                       break;;
                                                }
                                                if (codigoDigitado == -2) // -2 quando apertar F11
                                                {
                                                        opcaoChar = mostraMenuF11();
                                                        chamaFuncoesAlterar(opcaoChar,1,arqSerie,arqAtividades,'A');
                                                        break;
                                                }
                                                validaCodigoRepetido(arqSerie,&codigoDigitado,bytesSeries);
                                                if (codigoDigitado == -1)
                                                {
                                                       limpaTelaEfeito();
                                                       break;
                                                }
                                                if (codigoDigitado == -2) // -2 quando apertar F11
                                                {
                                                        opcaoChar = mostraMenuF11();
                                                        chamaFuncoesAlterar(opcaoChar,1,arqSerie,arqAtividades,'A');
                                                        break;
                                                }
                                                limpaTelaEfeito();
                                                clrscr();
                                                leValidaMenuAlterarSeries(escolha2,codigoDigitado,arqSerie);
                                                break;
                                           }
                                           case 3:   // DELETAR SERIES     [ ok ]  
                                           {
                                                limpaTelaEfeitoVertical();
                                                mostraDigiteF11();
                                                fazMolduraCadastros(49999); // parâmetro é a cor
                                                textcolor(WHITE); 
                                                gotoxy(19,10);
                                                printf("DIGITE O CODIGO DA SERIE QUE DESEJA DELETAR:");
                                                gotoxy(39,15);
                                                textcolor(10);
                                                codigoDigitado = leValidaNumeros(999,9999,5);
                                                textcolor(WHITE);
                                                fflush(stdin);
                                                if (codigoDigitado == -1)
                                                {
                                                   limpaTelaEfeito();
                                                   clrscr();
                                                   break;
                                                }
                                                if (codigoDigitado == -2) // -2 quando apertar F11
                                                {
                                                        opcaoChar = mostraMenuF11();
                                                        chamaFuncoesAlterar(opcaoChar,1,arqSerie,arqAtividades,'D');
                                                        break;
                                                        
                                                }
                                                validaCodigoRepetido(arqSerie,&codigoDigitado,bytesSeries);
                                                if (codigoDigitado == -1)// ESQ
                                                {
                                                   limpaTelaEfeito();
                                                   clrscr();
                                                   break;
                                                }
                                                if (codigoDigitado == -2) // -2 quando apertar F11
                                                {
                                                        opcaoChar = mostraMenuF11();
                                                        chamaFuncoesAlterar(opcaoChar,1,arqSerie,arqAtividades,'D'); 
                                                        break;
                                                }
                                                clrscr();
                                                achou = verificaSeFezAtividade(codigoDigitado,arqAtividades,bytesAtividades);
                                                if (!achou)
                                                {
                                                   apontador = mostraRegistroPesquisado(arqSerie,apontador,codigoDigitado);
                                                   deletou = deletarRegistro(arqSerie,apontador,bytesSeries);
                                                   if (deletou)
                                                   {
                                                            verdadeiroValor--;
                                                            verdadeiroContSeries = verdadeiroContSeries + verdadeiroValor;
                                                   }
                                                   break;
                                                }else
                                                 {
                                                     mostraImpossivelDeletar();
                                                 }
                                           }
                           }
                           break;
                     }
//--------------------------------------------------------------------------------------------------------------------------------------
//                                                     A T I V I D A D E S                  aa1
//--------------------------------------------------------------------------------------------------------------------------------------
                     case 3: // ATIVIDADES
                     {
                           clrscr();
                           escolha2 = leValidaMenu(escolha2,escolha);
                           switch(escolha2)
                           {
                                           case 1:    // INCLUIR NOVA ATIVIDADE.
                                           {
                                                limpaTelaEfeitoVertical();
                                                textcolor(WHITE); 
                                                paraSairDigiteSair();
                                                gotoxy(26,10);
                                                printf("INFORME O CPF DO FREQUENTADOR:");
                                                leCharPorChar(atividades.cpf,10);
                                                if (atividades.cpf[0] == 27)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }
                                                clrscr();
                                                achou = verificaCpfExiste(arqClientes,atividades.cpf,101);
                                                if (!achou)
                                                {
                                                  do
                                                  {
                                                     leCharPorChar(atividades.cpf,10);
                                                     clrscr();
                                                     if (atividades.cpf[0] == 27)
                                                     {
                                                          
                                                            achou = 0;
                                                            break;
                                                     }
                                                     achou = verificaCpfExiste(arqClientes,atividades.cpf,101);
                                                     
                                                  }while(achou == 0);
                                                }
                                                if (!achou)
                                                {
                                                   operacaoCancelada();
                                                   break;
                                                }
                                                clrscr();
                                                fazMolduraCadastros(49999);
                                                paraSairDigiteSair();
                                                gotoxy(24,10);
                                                printf("DIGITE O CODIGO DA SERIE REALIZADA:");
                                                textcolor(10);
                                                atividades.codigo = leValidaNumeros(999,9999,5);
                                                if (atividades.codigo == -1)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }
                                                validaCodigoRepetido(arqSerie,&atividades.codigo,bytesSeries);
                                                if (atividades.codigo == -1)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }
                                                obtemDataAtual(&atividades.dia,&atividades.mes,&atividades.ano);
                                                strcpy(atividades.hora,__TIME__);
                                                atividades.hora[MAXHORA-1] = '\0';
                                                fezAtividade = verificaSeFezAtividadeHoje(&atividades,arqAtividades);
                                                if (fezAtividade)
                                                {
                                                      clrscr();
                                                      fazMolduraCadastros(49999);
                                                      textcolor(LIGHTRED);
                                                      gotoxy(20,15);
                                                      printf("O CLIENTE JA REALIZOU ESSA ATIVIDADE HOJE!");
                                                      gotoxy(16,21);
                                                      textcolor(YELLOW);
                                                      printf("Digite qualquer coisa para voltar ao menu!");
                                                      textcolor(WHITE);
                                                      getch();
                                                      limpaTelaEfeito();
                                                      break;
                                                }
                                                gravaDadosAtividades(arqAtividades,&atividades);
                                                cadastroConcluido(31);
                                                limpaTelaEfeito();
                                                break;
                                           }
                                           case 2:   // EXCLUSAO DE ATIVIDADE   XX4
                                           {
                                                limpaTelaEfeitoVertical();
                                                mostraDigiteF11();
                                                textcolor(WHITE); 
                                                paraSairDigiteSair();
                                                gotoxy(26,10);
                                                printf("INFORME O CPF DO FREQUENTADOR:");
                                                leCharPorChar(cpfDigitado,10);
                                                if (cpfDigitado[0] == 27)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }
                                                if (cpfDigitado[0] == -123)
                                                {
                                                    opcaoChar = mostraMenuF11Atividades();
                                                    chamaFuncoesAlterar(opcaoChar,2,arqSerie,arqAtividades,'D');
                                                    break;
                                                }
                                                clrscr();
                                                mostraDadosAtividades(cpfDigitado,arqAtividades,'A'); 
                                                excluiAtividade(arqAtividades,cpfDigitado);
                                                system("CLS");
                                                break;
                                           }
                           }
                           break;
                     }
//--------------------------------------------------------------------------------------------------------------------------------------
//                                           R E L A T Ó R I O S      E      P E S Q U I S A S      rr1
//--------------------------------------------------------------------------------------------------------------------------------------
                     case 4: //  RELATORIOS E PESQUISAS
                     {
                           clrscr();
                           escolha2 = leValidaMenu(escolha2,escolha);
                           switch(escolha2)
                           {
                                           case 1: // PESQUISA SIMPLES E TODOS OS DADOS 
                                           {
                                                aux = 1;
                                                clrscr();
                                                fazMoldura();
                                                do
                                                {
                                                   do
                                                   {
                                                     aux = leValidaOpcao1Relatorio(aux);
                                                     switch(aux)
                                                     {
                                                           clrscr();
                                                           case 1: //REGISTRO UNICO ss1
                                                           {
                                                                escreveQualquerCoisa("                     ",32,29,10);
                                                                escreveQualquerCoisa("   REGISTRO UNICO    ",32,29,11);
                                                                escreveQualquerCoisa("                     ",32,29,12);
                                                                aux=menuEscolhaTipoPesquisa();
                                                                switch(aux)
                                                                {
                                                                           case 1: // FREQUENTADORES
                                                                           {
                                                                                clrscr();
                                                                                escreveQualquerCoisa("DIGITE O CPF DO FREQUENTADOR",15,29,10);
                                                                                leCharPorChar(cpfDigitado,10);
                                                                                if (cpfDigitado[0] == 27)
                                                                                {
                                                                                    limpaTelaEfeito();
                                                                                    aux=1;
                                                                                    break;
                                                                                }  
                                                                                clrscr();    
                                                                                mostraDadosFrequentador(cpfDigitado,arqClientes,'A');                                                                                         
                                                                                getch();
                                                                                limpaTelaEfeitoVertical();
                                                                                system("CLS");
                                                                                
                                                                                break;
                                                                           }
                                                                           case 2: // SERIES 
                                                                           {
                                                                                clrscr();
                                                                                escreveQualquerCoisa("DIGITE O CODIGO DA SERIE A PESQUISAR",15,23,10);
                                                                                codigoDigitado = leValidaNumeros(999,9999,5);
                                                                                if (codigoDigitado == -1) // -1 quando apertar ESQ
                                                                                {
                                                                                    limpaTelaEfeito();
                                                                                    aux=1;
                                                                                    break;
                                                                                }
                                                                                clrscr();
                                                                                mostraDadosSeries(&codigoDigitado,arqSerie,'A');
                                                                                getch();
                                                                                limpaTelaEfeitoVertical();
                                                                                system("CLS");
                                                                                aux=1;
                                                                                break;
                                                                           }
                                                                           case 3: // ATIVIDADES XX4
                                                                           {
                                                                                clrscr();
                                                                                escreveQualquerCoisa("DIGITE O CPF DO FREQUENTADOR",15,29,10);
                                                                                leCharPorChar(cpfDigitado,10);
                                                                                if (cpfDigitado[0] == 27)
                                                                                {
                                                                                    limpaTelaEfeito();
                                                                                    aux=1;
                                                                                    break;
                                                                                }  
                                                                                clrscr();                            
                                                                                mostraDadosAtividades(cpfDigitado,arqAtividades,'A'); 
                                                                                getch();
                                                                                limpaTelaEfeitoVertical();
                                                                                system("CLS");
                                                                                aux=1;
                                                                                break;
                                                                           }
                                                                           case 0:
                                                                           {
                                                                                clrscr();
                                                                                aux=1;
                                                                                break;
                                                                           }      
                                                                }
                                                                break;
                                                           }
                                                           case 2: // TODOS OS REGISTROS
                                                           {
                                                                escreveQualquerCoisa("                     ",63,29,10);
                                                                escreveQualquerCoisa(" TODOS OS REGISTROS  ",63,29,11);
                                                                escreveQualquerCoisa("                     ",63,29,12);
                                                                aux=menuEscolhaTipoPesquisa();
                                                                switch(aux)
                                                                {
                                                                           case 1: // FREQUENTADORES
                                                                           {
                                                                                clrscr();
                                                                                mostraDadosFrequentador(" ",arqClientes,'B');                                                                                         
                                                                                getch();
                                                                                limpaTelaEfeitoVertical();
                                                                                system("CLS");
                                                                                aux=2;
                                                                                break;
                                                                           }
                                                                           case 2: // SERIES
                                                                           {
                                                                                clrscr();
                                                                                mostraDadosSeries(0,arqSerie,'B');
                                                                                getch();
                                                                                limpaTelaEfeitoVertical();
                                                                                system("CLS");
                                                                                aux=2;
                                                                                break;
                                                                           }
                                                                           case 3: // ATIVIDADES
                                                                           {
                                                                                clrscr();
                                                                                mostraDadosAtividades(" ",arqAtividades,'B');    
                                                                                getch();                                                                                     
                                                                                limpaTelaEfeitoVertical();
                                                                                system("CLS");
                                                                                aux=2;
                                                                                break;
                                                                           }
                                                                           case 0:
                                                                           {
                                                                                clrscr();
                                                                                aux=2;
                                                                                break;
                                                                           }      
                                                                }
                                                                break;
                                                                getch();
                                                                break;
                                                           }
                                                           clrscr();
                                                     }
                                                   }while(aux != 0);
                                                }while(aux != 0);
                                                break;
                                           }
                                           case 2:   // PESQUISA POR NOME ORDENADA            NÃO ESQUEÇER DE DAR FREE ! YYC
                                           {
                                                limpaTelaEfeito();
                                                paraSairDigiteSair();
                                                escreveQualquerCoisa("DIGITE O NOME A PESQUISAR",15,28,13);
                                                fazMolduraCadastros(49999);
                                                leCharPorChar(nomeDigitado,10);
                                                clrscr();
                                                ordenaPorNome(arqClientes,nomeDigitado);  
                                                break;
                                           }
                                           case 3: // PESQUISA POR SÉRIE EXECUTADA
                                           {
                                                clrscr();
                                                escreveQualquerCoisa("DIGITE O CODIGO DA SERIE QUE FOI EXECUTADA",15,20,10);
                                                codigoDigitado = leValidaNumeros(999,9999,5);
                                                if (codigoDigitado == -1) // -1 quando apertar ESQ
                                                {
                                                    limpaTelaEfeito();
                                                    aux=1;
                                                    break;
                                                }
                                                achaClientesComSerie(arqAtividades,arqClientes,&codigoDigitado);
                                                getch();
                                                limpaTelaEfeitoVertical();
                                                break;
                                           }
                                           case 4: // PESQUISA POR DATA E RESUMOS... YY1
                                           {
                                                clrscr();
                                                paraSairDigiteSair();
                                                escreveQualquerCoisa("                                                   ",31,15,3);
                                                escreveQualquerCoisa("           RESUMO DE ATIVIDADES POR DATA           ",31,15,4);
                                                escreveQualquerCoisa("                                                   ",31,15,5);
                                                escreveQualquerCoisa("DIGITE O CPF DO FREQUENTADOR A PESQUISAR",15,21,10);
                                                do
                                                {
                                                    leCharPorChar(cpfDigitado,10);
                                                    limpaTelaCordenada(17,17,47,' ');
                                                    if (cpfDigitado[0] != 27)
                                                       aux = verificaCpfExiste(arqClientes,cpfDigitado,101);
                                                    else
                                                        aux=-1;
                                                }while(aux==0);
                                                if (aux == -1)
                                                   break;
                                                if (cpfDigitado[0] == 27)
                                                {
                                                    limpaTelaEfeito();
                                                    break;
                                                }  
                                                clrscr();
                                                aux = verificaCpfFezAtividade(cpfDigitado,arqAtividades);
                                                if (!aux)
                                                {
                                                         nenhumDadoEncontrado();
                                                         escreveQualquerCoisa("ESSE CLIENTE NAO REALIZOU",74,28,11);
                                                         escreveQualquerCoisa("        ATIVIDADES",74,28,12);
                                                         getch();
                                                         break;
                                                }
                                                escreveQualquerCoisa(" CLIENTE:                                          ",240,15,2);
                                                escreveNomeCliente(arqClientes,cpfDigitado,249,25,2);
                                                escreveQualquerCoisa("                                                   ",31,15,3);
                                                escreveQualquerCoisa("           RESUMO DE ATIVIDADES POR DATA           ",31,15,4);
                                                escreveQualquerCoisa("                                                   ",31,15,5);
                                                aux = leValidaDataDeAte(&anoComp[0],&mesComp[0],&diaComp[0]);
                                                if (!aux)
                                                {
                                                   limpaTelaEfeitoVertical();
                                                   break;
                                                }
                                                escreveQualquerCoisa("                 DADOS VALIDOS!                  ",159,16,15);
                                                escreveQualquerCoisa("                                                 ",160,16,16);
                                                escreveQualquerCoisa("  DIGITE QUALQUER COISA PARA INICIAR A PESQUISA  ",160,16,17);
                                                escreveQualquerCoisa("                                                 ",160,16,18);
                                                escreveQualquerCoisa("                                                 ",1,16,8);
                                                getch(); 
                                                limpaTelaEfeito();
                                                achaMostraAtividadesData(cpfDigitado,arqAtividades,arqSerie,&diaComp[0],&mesComp[0],&anoComp[0]);
                                                getch();
                                                break;
                                           }
                                           case 5:  // FREQUENTADORES POR DATA
                                           {
                                                clrscr();
                                                escreveQualquerCoisa("                                                   ",47,15,3);
                                                escreveQualquerCoisa("         LISTA DE FREQUENTADORES POR DATA          ",47,15,4);
                                                escreveQualquerCoisa("                                                   ",47,15,5);
                                                aux = leValidaDataDeAte(&anoComp[0],&mesComp[0],&diaComp[0]);
                                                if (!aux)
                                                {
                                                   limpaTelaEfeitoVertical();
                                                   break;
                                                }
                                                escreveQualquerCoisa("                 DADOS VALIDOS!                  ",159,16,15);
                                                escreveQualquerCoisa("                                                 ",160,16,16);
                                                escreveQualquerCoisa("  DIGITE QUALQUER COISA PARA INICIAR A PESQUISA  ",160,16,17);
                                                escreveQualquerCoisa("                                                 ",160,16,18);
                                                escreveQualquerCoisa("                                                 ",1,16,8);
                                                getch(); 
                                                limpaTelaEfeito();
                                                achaMostraClientesData(&anoComp[0],&mesComp[0],&diaComp[0],arqAtividades,arqClientes);
                                                getch();
                                                break;
                                           }
                                           case 6://YY4
                                           {
                                                clrscr();
                                                escreveQualquerCoisa("     DIGITE A QUANTIDADE DE DIAS DE AUSENCIA     ",159,16,15);
                                                aux = leValidaNumeros(0,999999,5);
                                                obtemDataAtual(&diaComp[1],&mesComp[1],&anoComp[1]);
                                                subtraiData(&diaComp[0],&mesComp[0],&anoComp[0],aux);
                                                clrscr();
                                                achaClientesAusentes(arqAtividades,&diaComp[0],&mesComp[0],&anoComp[0],aux,arqClientes);
                                                getch();
                                                break;
                                           }
                           }
                           break;
                     }
                     
      }
      clrscr();
  }while(escolha != 5);
  free(pNome);
  free(pOutro);
  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------
//                                                    S U B P R O G R A M A S
//--------------------------------------------------------------------------------------------------------------------------------------
// Subprograma x
//     Objetivo  : Ler um nome ou frase caractere por caractere.
//     Parâmetro : Ponteiro do Nome ou frase e maximo de caracteres aceitos.
//     Retorno   : Nenhum.
void leCharPorChar(char *pNomeFrase, int maximo)
{  
  int aux=0, contador=0, posicao=27;
  maximo = 29; // teste de maximo
  textcolor(10);
  do
  {
     molduraNomes(15);
     fazMolduraCadastros(49999);
     if (aux == 1)
     {
        gotoxy(15,24);
        printf("Quantidade de caracteres invalida! Digite novamente:");
        limpaTelaCordenada(27,17,maximo-1,' ');
        limpaTelaCordenada(22,14,40,' ');
        textcolor(10);
     }
     aux=0;
     gotoxy(27,17);
     for (contador=0;contador<maximo;contador++)
     {
         gotoxy(27+contador,17);
         pNomeFrase[contador] = getch();
         if (pNomeFrase[contador] == -123)
         {
                    pNomeFrase[0] = -123;
                    return;
         }
         if (pNomeFrase[contador] == 27)
         {
                    pNomeFrase[0] = 27;
                    return;
         }
         if (pNomeFrase[contador] == 13)
         {
                 pNomeFrase[contador] = '\0';
                 break;
         } 
         if (pNomeFrase[contador] == '\b')
         {
                 if (contador > 0)
                 {
                   pNomeFrase[contador-1] = ' ';
                   contador = contador - 2;
                   gotoxy(27+contador+1,17);
                   printf(" ");
                 }else
                      contador = -1;
                      
         }else
               printf("%c",pNomeFrase[contador]);
     }
     fflush(stdin);
     aux++;
  }while((strlen(pNomeFrase) >= maximo-1) || (pNomeFrase[0] == '\0')); 
  textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Ler e validar a descrição ou nome da série.
//     Parâmetro : Ponteiro do Nome ou descrição da série e quantidade maxima de caracteres.
//     Retorno   : Nenhum.
void leCharPorCharDescricao(char *pNomeFrase, int maximo)
{  
  int aux=0, contador=0, posicao=27;
  maximo = 47; // teste de maximo
  molduraDescricao();
  textcolor(10);
  paraSairDigiteSair();
  do
  {
     fazMolduraCadastros(49999);
     if (aux == 1)
     {
        gotoxy(15,24);
        printf("Quantidade de caracteres invalida! Digite novamente:");
        limpaTelaCordenada(17,17,maximo-1,' ');
       // limpaTelaCordenada(22,14,30,'z');
        textcolor(10);
     }
     aux=0;
     gotoxy(17,17);
     for (contador=0;contador<maximo;contador++)
     {
         gotoxy(17+contador,17);
         pNomeFrase[contador] = getch();
         if (pNomeFrase[contador] == 27)
         {
                 pNomeFrase[0] = 27;
                 return;
         }
         if (pNomeFrase[contador] == 13)
         {
                 pNomeFrase[contador] = '\0';
                 break;
         } 
         if (pNomeFrase[contador] == '\b')
         {
                 if (contador > 0)
                 {
                   pNomeFrase[contador-1] = ' ';
                   contador = contador - 2;
                   gotoxy(17+contador+1,17);
                   printf(" ");
                 }else
                      contador = -1;
                      
         }else
               printf("%c",pNomeFrase[contador]);
     }
     fflush(stdin);
     aux++;
  }while((strlen(pNomeFrase) >= maximo-1) || (pNomeFrase[0] == '\0')); 
  textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Ler e validar valores númericos.
//     Parâmetro : Validação minima, maxima e maximo de Números.
//     Retorno   : Número válido.
int leValidaNumeros(int min, int max,int maximo)
{  
  int aux=0, contador=0, posicao=27;
  int valorAtoi=10000, apertouEnter=0; 
  char valor[maximo];
  //clrscr();
  molduraNumeros();
  textcolor(10);
  paraSairDigiteSair();
  do
  {
     fazMolduraCadastros(49999);
     do
     {
       if (contador == maximo)
          contador = maximo-1;
       if (((valorAtoi <= min) || (valorAtoi > max) && (apertouEnter == 1)))
       {
              limpaTelaCordenada(38,17,4,' ');
              contador = 0;
              apertouEnter = 0;
              gotoxy(25,20);
              printf("Valor invalido! informe novamente:");
       }
       for (contador=contador;contador<maximo;contador++)
       {
         gotoxy(38+contador,17);
         valor[contador] = getch();
         aux++;
         if (valor[contador] == -123) // digitou F11
         {
                  return -2;              
         }
         if (valor[contador] == 13)
         {
                 apertouEnter = 1;
                 valor[contador] = '\0';
                 break;
         } 
         if (valor[contador] == 27)
         {
                return -1;
         }
         if (valor[contador] == '\b')
         {
                 if (contador > 0)
                 {
                   valor[contador-1] = ' ';
                   contador = contador - 2;
                   gotoxy(38+contador+1,17);
                   printf(" ");
                 }else
                      contador = -1;
                      
         }else
               printf("%c",valor[contador]);
       }
       fflush(stdin);
       valorAtoi = atoi(valor);
       if (maximo == 4)
          limpaTelaCordenada(41,17,1,' ');
       else
           limpaTelaCordenada(42,17,0,' ');
     }while((valorAtoi <= min) || (valorAtoi > max));
  }while((strlen(valor) >= maximo) || (valor[0] == '\0')); 
  limpaTelaCordenada(25,20,34,' ');
  limpaTelaCordenada(38,17,4,' ');
  return valorAtoi;
}
int confirmaDadosAcima()
{
    char opcao;
    do
    {
          textcolor(WHITE);
          gotoxy(20,20);
          printf("     Deseja confirmar os dados acima?");
          opcao = simOuNao(10,17,22);
    }while ((opcao != 1) && (opcao != 0));
    return opcao;
}
//                                SEQUENCIA ESTRUTURA CLIENTES:
//CPF    (CHAR * TAM_NOME)
//NOME  (CHAR * TAM_NOME)
//PESO (FLOAT)                      
//SEXO (CHAR)
//DIA (INT)                          TAMANHO = 101 bytes
//MES (INT)
//ANO (INT)
// Subprograma x
//     Objetivo  : Reapresentar os dados de um Cliente. YYA
//     Parâmetro : Estrutura de dados do cliente.
//     Retorno   : Nenhum.
void apresentaDadosClientes(struct cliente *pEstrutura)
{
          fazMolduraCadastros(49999);
          textcolor(10);
          gotoxy(32,7);
          printf("DADOS DO FREQUENTADOR");
          textcolor(WHITE);
          gotoxy(20,8);
          printf("NOME: ");
          textcolor(YELLOW);
         // printf("%s.",pNome);
          printf("%s.",pEstrutura->nome);
          textcolor(WHITE);
          gotoxy(20,10);
          printf("PESO: ");
          textcolor(YELLOW);
          //printf("%3.1f Kg.",*pPeso);
          printf("%3.1f Kg.",pEstrutura->peso);
          textcolor(WHITE);
          gotoxy(20,12);
          printf("SEXO: ");
          textcolor(YELLOW);
          //if (*pSexo == 'M')
          if (pEstrutura->sexo == 'M')
             printf("MASCULINO");
          else
              printf("FEMININO");
          escreveQualquerCoisa("DATA DE INGRESSO:",15,20,14);
          gotoxy(38,14);
          textcolor(YELLOW);
          //printf("%d/%d/%d",*pDia,*pMes,*pAno);
          printf("%d/%d/%d",pEstrutura->dia,pEstrutura->mes,pEstrutura->ano);
          textcolor(WHITE);
          molduraDescricao();
       //   gotoxy(39,15);
       //   printf("CPF");
          escreveQualquerCoisa(" CPF ",79,38,15);
          textcolor(YELLOW);
          gotoxy(17,17);
          printf("%s.",pEstrutura->cpf);
     /*fwrite(cadastro->cpf,(sizeof(char) * TAM_NOME),1,arqClientes);
     fwrite(cadastro->nome,(sizeof(char) * TAM_NOME),1,arqClientes);
     fwrite(&cadastro->peso,sizeof(float),1,arqClientes);
     fwrite(&cadastro->sexo,sizeof(char),1,arqClientes);
     fwrite(&cadastro->dia,sizeof(int),1,arqClientes);
     fwrite(&cadastro->mes,sizeof(int),1,arqClientes);                      
     fwrite(&cadastro->ano,sizeof(int),1,arqClientes);*/
}       
// Subprograma x
//     Objetivo  : Reapresentar os dados de uma série.
//     Parâmetro : Estrutura de dados da série.
//     Retorno   : Nenhum.
//void apresentaDadosClientes(struct cliente *pEstrutura);
//void apresentaDadosSeries(int *pCodigo,int *pDuracao,char *pFrase,char *pNomeSerie,float *pCalorias)
void apresentaDadosSeries(struct dadosSerie *pEstrutura)
{
          fazMolduraCadastros(49999);
          textcolor(10);
          gotoxy(33,7);
          printf("DADOS DA SERIE:");
          textcolor(WHITE);
          gotoxy(20,9);
          printf("NOME DA SERIE     : ");
          textcolor(YELLOW);
          //printf("%s.",pNomeSerie);
          printf("%s.",pEstrutura->nomeSerie);
          textcolor(WHITE);
          gotoxy(20,11);
          printf("DURACAO           : ");
          textcolor(YELLOW);
          //printf("%d minutos.",*pDuracao);
          printf("%d minutos",pEstrutura->duracao);
          textcolor(WHITE);
          gotoxy(20,13);
          printf("CALORIAS PERDIDAS : ");
          textcolor(YELLOW);
          //printf("%3.2f calorias.",*pCalorias);
          printf("%3.2f calorias",pEstrutura->calorias);
          textcolor(WHITE);
          molduraDescricao();
          gotoxy(28,15);
          printf("   DESCRICAO DA SERIE: ");
          textcolor(YELLOW);
          gotoxy(17,17);
          //printf("%s.",pFrase);
          printf("%s.",pEstrutura->frase);
}       
// Subprograma x
//     Objetivo  : Gravar a estrutura de séries em um arquivo binario.
//     Parâmetro : Endereço do arquivo de séries e estrutura das séries.
//     Retorno   : Nenhum.
void gravaDadosSeries(FILE *arqSeries,struct dadosSerie *series)
{
     arqSeries=abreArquivo("cadastroSeries.txt","a+b","-Erro ao tentar abrir o arquivo de Series!");
     //fwrite(series->nomeSerie,(sizeof(char) * MAX_NOME),1,arqSeries);
     //fwrite(&series->codigo,(sizeof(int)),1,arqSeries); // não tenho certeza se tem & nessa linha...
     //fwrite(&series->duracao,sizeof(int),1,arqSeries);
     //fwrite(&series->calorias,sizeof(float),1,arqSeries);
     //fwrite(series->frase,(sizeof(char) * MAX_FRASE),1,arqSeries);
     fwrite(series,sizeof(tipoSerie),1,arqSeries);
     fclose(arqSeries);
}    
// Subprograma x
//     Objetivo  : Abrir qualquer  arquivo.
//     Parâmetro : Ponteiro do nome do arquivo do modo de abertura e da mensagem de erro.
//     Retorno   : Endereço do arquivo.
FILE * abreArquivo (char *nomeArq, char *modo, char *msgErro)
{
     FILE *arq;
     arq=fopen(nomeArq,modo);
     if (arq==NULL)
     {
        printf("%s",msgErro);
        getch();
        exit(1);
     }
     return arq;

}
// Subprograma x
//     Objetivo  : Ler e validar nomes.
//     Parâmetro : Nome (string).
//     Retorno   : Nenhum.
void leValidaString (char *string)
{
	do
	{
		fgets(string,TAM_NOME,stdin);
		fflush(stdin);
		if(string[strlen(string)-1]=='\n')
			string[strlen(string)-1]='\0';
	//	maiusculo(string);
		if(!strlen(string))
			printf("\n-Erro, informe novamente:");
    }while(!strlen(string));
}
// Subprograma x
//     Objetivo  : Transformar string para caixa ALTA.
//     Parâmetro : Nome (string).
//     Retorno   : Nenhum.
void maiusculo(char *string)
{
	int cont;
	for(cont=0;cont<strlen(string);cont++)
	    string[cont]=toupper(string[cont]);
}
// Subprograma x
//     Objetivo  : Validar valores float.
//     Parâmetro : Valor numerico, valor mínimo, valor máximo.
//     Retorno   : Nenhum.
void leValidaFloat(float *nro, float minimo, float maximo)
{
	do
	{
	    scanf("%f",nro);
	    if(*nro<=minimo || *nro>=maximo)
	    	printf("\n- Valor invalido, digite novamente:");
    }while(*nro<=minimo || *nro>=maximo);
}
// Subprograma x
//     Objetivo  : Obter a data atual do sistema.
//     Parâmetro : Ponteiro de dia, mês e ano.
//     Retorno   : Nenhum.
void obtemDataAtual(int *dia, int *mes, int *ano)
{
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900+dataAtual->tm_year;
}
// Subprograma x
//     Objetivo  : Gravar uma estrutura de clientes em um arquivo.txt.
//     Parâmetro : Endereço do arquivo de clientes e estrutura de clientes.
//     Retorno   : Nenhum.
void gravaDados(FILE *arqClientes,struct cliente *cadastro)
{
     arqClientes = abreArquivo("cadastroClientes.txt","a+b","ERRO AO GRAVAR DADOS DO CLIENTE");
     //int simbolico1=20, simbolico2=9, simbolico3=1993;
     /*fwrite(cadastro->cpf,(sizeof(char) * TAM_NOME),1,arqClientes);
     fwrite(cadastro->nome,(sizeof(char) * TAM_NOME),1,arqClientes);
     fwrite(&cadastro->peso,sizeof(float),1,arqClientes);
     fwrite(&cadastro->sexo,sizeof(char),1,arqClientes);
     fwrite(&cadastro->dia,sizeof(int),1,arqClientes);
     fwrite(&cadastro->mes,sizeof(int),1,arqClientes);                      
     fwrite(&cadastro->ano,sizeof(int),1,arqClientes);*/
     fwrite(cadastro,sizeof(tipoFrequentador),1,arqClientes);
     fflush(stdin);
     fclose(arqClientes);
}
// Subprograma x
//     Objetivo  : Validar o Cpf.
//     Parâmetro : Endereço inicial do cpf.
//     Retorno   : Nenhum.
int validaCPF(char nroCpf[12])
{
  /*int i,total1,total2,nro1,nro2,cont,cont2=0;
  
  if(strlen(nroCpf) != 11) 
    return 0; 
  for(cont=0;cont<10;cont++)
  {
		if(nroCpf[0]==nroCpf[cont2])
		{
			cont2++;
		    if((strlen(nroCpf)-1)==cont2)
        	    return 0; 
	    }
  }
  
  //Calcula primeiro dígito
  total1 = 0;
  for(i=0; i<=8; i++)
    total1 = total1 + ctoi(nroCpf[i]) * (10 - i);    
  if(total1 % 11 < 2)
    nro1 = 0;
  else
    nro1 = 11 - (total1 % 11);
  
  //Calcula segundo dígito  
  total2 = 0;
  for(i=0; i<=9; i++)
    total2 = total2 + ctoi(nroCpf[i]) * (11 - i);  
  if(total2 % 11 < 2)
    nro2 = 0;
  else
    nro2 = 11 - (total2 % 11);
    
    //Se os dígitos forem compatíveis retorna TRUE
    if((nro1 == ctoi(nroCpf[9])) && (nro2 == ctoi(nroCpf[10])))
      return 1;
  
  return 0;
}

int ctoi(char ch)
{
  switch (ch) {
    case '0':
         return 0;
         break; 
    case '1':
         return 1;
         break; 
    case '2':
         return 2;
         break; 
    case '3':
         return 3;
         break; 
    case '4':
         return 4;
         break; 
    case '5':
         return 5;
         break; 
    case '6':
         return 6;
         break; 
    case '7':
         return 7;
         break; 
    case '8':
         return 8;
         break; 
    case '9':
         return 9;
         break; 
  }
  return -1;  */
}
// Subprograma x
//     Objetivo  : Validar CPF para que não haja repetição.
//     Parâmetro : struct com CPF's e posição do cadastro (contador).
//     Retorno   : 0 para CPF já cadastrado e 1 para não cadastrado.
int validaCpfRepetido(FILE *arq,struct cliente cadastro)
{
	char string[TAM_NOME];
	arq=abreArquivo("cadastroClientes.txt","a+b","\nErro ao abrir arquivo de CPF's");
	while(fread(string,sizeof(arq),1,arq)!= 0)
	{
		if (strcmp(string,cadastro.cpf)==0)
		{
            fclose(arq);
			return 1;
        }
	}
	fclose(arq);
    return 0;
}
// Subprograma x
//     Objetivo  : tranformar todos os caracteres em maiusculo.
//     Parâmetro : ponteiro da string.
//     Retorno   : string toda em maiusculo.
void capsLock(char *pCaracteres)
{
     int aux=0;
     for(aux=0;aux<strlen(pCaracteres);aux++)
     {
             pCaracteres[aux] = toupper(pCaracteres[aux]);                               
     }
}
// Subprograma x
//     Objetivo  : Verificar se o código unico existe.
//     Parâmetro : endereço do arquivo e estrutura de séries.
//     Retorno   : verdadeiro ou falso.
int verificaCodigoSerie(FILE *arq,int codigoDigitado,struct dadosSerie series)
{
    int aux=0;
	int codigo;
	arq=abreArquivo("cadastroSeries.txt","a+b","\nErro ao abrir arquivo de Series");
	fseek(arq,(sizeof(char) * MAX_NOME),1);
	while(fread(&codigo,sizeof(int),1,arq)!= 0)
	{
        fseek(arq,sizeof(series)-sizeof(int),1);
		if (codigo == codigoDigitado)
		{
            fclose(arq);
			return 1;
        }
	}
	fclose(arq);
    return 0;
}
// Subprograma x 
//     Objetivo  : Apresentar o menu de alteração e redirecionar para as funçoes corretas.
//     Parâmetro : Opção, código e endereço do arquivo de series.
//     Retorno   : Nenhum.
void leValidaMenuAlterarSeries(char opcao,int codigoDigitado,FILE *arq)
{
     int aux=0,codigo,duracao, contador=1;
     //float calorias;
     //char nomeSerie[MAX_NOME],frase[MAX_FRASE],novoNome[MAX_NOME];
     long tamanho;
     system("CLS");
     do
     {
                 tamanho = mostraRegistroPesquisado(arq,tamanho,codigoDigitado);
                 gotoxy(23,1);
                 textcolor(31);
                 printf("SELECIONE O QUE VOCE DESEJA ALTERAR:");
                 textcolor(WHITE);
                 if (contador == 1)
                 {    
                    textcolor(47);
                    gotoxy(9,2);
                    printf("            ");
                    gotoxy(9,4);
                    printf("            ");
                 }
                 gotoxy(9,3);
                 printf("    NOME    ");   
                 textcolor(WHITE);
                 if (contador == 2)
                 {
                    textcolor(47);   
                    gotoxy(22,2);
                    printf("            ");
                    gotoxy(22,4);
                    printf("            ");
                 }
                 gotoxy(22,3); 
                 printf(" DESCRICAO  ");
                 textcolor(WHITE);
                 if (contador == 3)
                 {
                    textcolor(47);
                    gotoxy(35,2);
                    printf("            ");
                    gotoxy(35,4);
                    printf("            ");
                 }
                 gotoxy(35,3);
                 printf("  CALORIAS  ");
                 textcolor(WHITE);
                 if (contador == 4)
                 {
                    textcolor(47);
                    gotoxy(47,2);
                    printf("            ");
                    gotoxy(47,4);
                    printf("            ");
                 }
                 gotoxy(47,3);
                 printf("  MINUTOS   ");
                 textcolor(WHITE);
                 if (contador == 5)
                 {
                    textcolor(79);
                    gotoxy(59,2);
                    printf("                  ");
                    gotoxy(59,4);
                    printf("                  ");
                 }
                 gotoxy(59,3);
                 printf("  VOLTAR AO MENU  "); 
                 textcolor(WHITE);    
                 opcao = getch();
                 limpaTelaCordenada(1,2,75,' ');
                 limpaTelaCordenada(1,3,75,' ');
                 limpaTelaCordenada(1,4,75,' ');
                 contador = quantidadeSetasMenuHorizontal(opcao,5,contador);  // ss1
     }while(opcao != 13);
     switch(contador)
     {
                  case 1:
                  {
                       clrscr();
                       alteraNomeSerie(arq, tamanho, opcao, codigoDigitado);
                       break;
                  }
                  case 2:
                  {
                       clrscr();
                       alteraDescricaoSerie(arq,tamanho, opcao, codigoDigitado);
                       break;
                  }
                  case 3:
                  {
                       clrscr();
                       alteraCaloriasSerie(arq,tamanho, opcao, codigoDigitado);
                       break;
                  }
                  case 4:
                  {
                       clrscr();
                       alteraMinutosSerie(arq,tamanho, opcao, codigoDigitado);
                       break;
                  }
                  default:
                  {
                       limpaTelaEfeitoVertical();
                       return;
                  }
     }    
}
// Subprograma x
//     Objetivo  : Apresentar o menu de alteração e redirecionar para as funçoes corretas.
//     Parâmetro : Opção, código e endereço do arquivo de series.
//     Retorno   : Nenhum.     //YYA
void leValidaMenuAlterarClientes(char opcao,char *pCpfDigitado,FILE *arq) // CC1
{
     int aux=0,codigo,duracao, contador=1;
     long tamanho;
     system("CLS");
     do
     {
                 tamanho = mostraRegistroPesquisadoClientes(arq,tamanho,pCpfDigitado);
                 gotoxy(23,1);
                 textcolor(31);
                 printf("SELECIONE O QUE VOCE DESEJA ALTERAR:");
                 textcolor(WHITE);
                 if (contador == 1)
                 {    
                    textcolor(47);
                    gotoxy(9,2);
                    printf("            ");
                    gotoxy(9,4);
                    printf("            ");
                 }
                 gotoxy(9,3);
                 printf("    NOME    ");   
                 textcolor(WHITE);
                 if (contador == 2)
                 {
                    textcolor(47);   
                    gotoxy(22,2);
                    printf("            ");
                    gotoxy(22,4);
                    printf("            ");
                 }
                 gotoxy(22,3); 
                 printf("    PESO    ");
                 textcolor(WHITE);
                 if (contador == 3)
                 {
                    textcolor(47);
                    gotoxy(35,2);
                    printf("            ");
                    gotoxy(35,4);
                    printf("            ");
                 }
                 gotoxy(35,3);
                 printf("    SEXO    ");
                 textcolor(WHITE);
                 if (contador == 4)
                 {
                    textcolor(47);
                    gotoxy(47,2);
                    printf("     ");
                    gotoxy(47,4);
                    printf("     ");
                 }
                 gotoxy(47,3);
                 printf(" DIA ");
                 textcolor(WHITE);
                 if (contador == 5)
                 {
                    textcolor(47);
                    gotoxy(54,2);
                    printf("     ");
                    gotoxy(54,4);
                    printf("     ");
                 }
                 gotoxy(54,3);
                 printf(" MES ");
                 textcolor(WHITE);
                 if (contador == 6)
                 {
                    textcolor(47);
                    gotoxy(60,2);
                    printf("     ");
                    gotoxy(60,4);
                    printf("     ");
                 }
                 gotoxy(60,3);
                 printf(" ANO ");
                 textcolor(WHITE);
                 if (contador == 7)
                 {
                    textcolor(79);
                    gotoxy(65,2);
                    printf("                ");
                    gotoxy(65,4);
                    printf("                ");
                 }
                 gotoxy(65,3);
                 printf(" VOLTAR AO MENU "); 
                 textcolor(WHITE);    
                 opcao = getch();
                 limpaTelaCordenada(1,2,79,' ');
                 limpaTelaCordenada(1,3,79,' ');
                 limpaTelaCordenada(1,4,79,' ');
                 contador = quantidadeSetasMenuHorizontal(opcao,7,contador);  // cc2
     }while(opcao != 13);
     switch(contador)
     {
                  case 1:
                  {
                       clrscr();
                       alteraNomeCliente(arq, tamanho, opcao, pCpfDigitado);
                       break;
                  }
                  case 2:
                  {
                       clrscr();
                       alteraPesoCliente(arq,tamanho, opcao, pCpfDigitado);
                       break;
                  }
                  case 3:
                  {
                       clrscr();
                       alteraSexoCliente(arq,tamanho, opcao, pCpfDigitado);
                       break;
                  }
                  case 4:
                  {
                       clrscr();
                       alteraDiaCliente(arq,tamanho, opcao, pCpfDigitado);
                       break;
                  }
                  case 5:
                  {
                       clrscr();
                       alteraMesCliente(arq,tamanho, opcao, pCpfDigitado);
                       break;
                  }
                  case 6:
                  {
                       clrscr();
                       alteraAnoCliente(arq,tamanho, opcao, pCpfDigitado);
                       break;
                  }
                  case 7:
                  {
                       return;
                  }
     }    
}
// Subprograma x
//     Objetivo  : Alterar o nome do Cliente
//     Parâmetro : Endereço do arquivo de Clientes,apontador do arquivo e cpf Digitado.
//     Retorno   : nenhum. YYB
void alteraNomeCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado)   
{
     char nomeDigitado[TAM_NOME];
     tipoFrequentador estrutura;
     clrscr();
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     paraSairDigiteSair();
     fazMolduraCadastros(49999);
     gotoxy(37,15);
     printf("NOVO NOME:");
     molduraNomes(15);
     leCharPorChar(nomeDigitado,TAM_NOME);
     if (nomeDigitado[0] == 27)
     {
            fclose(arq);
            clrscr();
            fflush(stdin);
            leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
            return;
     }
    // fseek(arq,posicao - ((sizeof(char)*MAX_CPF)+(sizeof(char)*MAX_NOME)+sizeof(float)+sizeof(char)+(sizeof(int)*3)),1);
    // fseek(arq,posicao - ((sizeof(tipoFrequentador))),1);
     fseek(arq,posicao+MAX_CPF,1);
     fwrite(nomeDigitado,sizeof(char)*MAX_NOME,1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("NOME MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
} 
// Subprograma x cc2
//     Objetivo  : Alterar o Peso do Cliente
//     Parâmetro : Endereço do arquivo de Clientes,apontador do arquivo e cpf Digitado.
//     Retorno   : nenhum. YYB
void alteraPesoCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado)
{
     float pesoLido;
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     gotoxy(25,10);
     printf("DIGITE O NOVO PESO DO FREQUENTADOR");
     pesoLido = leValidaNumeros(0,250,4);
     if (pesoLido == -1)
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
        return;
     }
     //fseek(arq,posicao - ( (sizeof(int)*3)+sizeof(char)+sizeof(float)),1);
     //fseek(arq,posicao - (sizeof(tipoFrequentador)-MAX_CPF-TAM_NOME),1);
     fseek(arq,posicao+sizeof(char)*MAX_CPF+sizeof(char)*TAM_NOME,1);
     fwrite(&pesoLido,sizeof(float),1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("PESO MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
}   
// Subprograma x
//     Objetivo  : Alterar o Sexo do Cliente
//     Parâmetro : Endereço do arquivo de Clientes,apontador do arquivo e cpf Digitado.
//     Retorno   : nenhum. YYB
void alteraSexoCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado)
{
     char sexoLido;
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     gotoxy(25,10);
     fazMolduraCadastros(49999);
     leValidaSexo(&sexoLido);
     if (sexoLido == '0')
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
        return;
     }
    // fseek(arq,posicao - ((sizeof(int)*3)+sizeof(char)),1);
    // fseek( arq,posicao - (sizeof(tipoFrequentador)-MAX_CPF-TAM_NOME-sizeof(float)),1);
     fseek(arq,posicao+MAX_CPF+TAM_NOME+sizeof(float),1);
     fwrite(&sexoLido,sizeof(char),1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("SEXO MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
}   
// Subprograma x
//     Objetivo  : Alterar o Dia de inscrição do cliente na academia.
//     Parâmetro : Endereço do arquivo de Clientes,apontador do arquivo e cpf Digitado.
//     Retorno   : nenhum. YYB
void alteraDiaCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado)
{
     int intLido;
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     gotoxy(25,10);
     printf("DIGITE O NOVO DIA DE INSCRICAO");
     intLido = leValidaNumeros(0,31,4);
     if (intLido == -1)
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
        return;
     }
   //  fseek(arq,posicao - (sizeof(int)*3),1);
 //  fseek( arq,posicao - (sizeof(tipoFrequentador)-MAX_CPF-TAM_NOME-sizeof(float)),1);
  //   fseek(arq,posicao -(sizeof(tipoFrequentador)-(sizeof(tipoFrequentador)-(sizeof(int)*3))),1);
     fseek(arq,posicao+sizeof(tipoFrequentador)-(sizeof(int)*3),1);
     fwrite(&intLido,sizeof(int),1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("DIA MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
}   
// Subprograma x
//     Objetivo  : Alterar o Mes de inscrição do cliente na academia.
//     Parâmetro : Endereço do arquivo de Clientes,apontador do arquivo e cpf Digitado.
//     Retorno   : nenhum. YYB
void alteraMesCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado)
{
     int intLido;
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     gotoxy(25,10);
     printf("DIGITE O NOVO MES DE INSCRICAO");
     intLido = leValidaNumeros(0,12,4);
     if (intLido == -1)
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
        return;
     }
    // fseek(arq,posicao - (sizeof(int)*2),1);
    // fseek(arq,posicao -(sizeof(tipoFrequentador)-(sizeof(tipoFrequentador)-(sizeof(int)*3))),1);
    // fseek(arq,posicao -(sizeof(tipoFrequentador)-(sizeof(tipoFrequentador)-(sizeof(int)*2))),1);
     fseek(arq,posicao+sizeof(tipoFrequentador)-(sizeof(int)*2),1);
     fwrite(&intLido,sizeof(int),1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("MES MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
          /*struct cliente
{
        char cpf[TAM_NOME];
        char nome[TAM_NOME];
        float peso;
        char sexo;
        int dia,     mes,ano;
};*/
}   
// Subprograma x
//     Objetivo  : Alterar o Ano de inscrição do cliente na academia.
//     Parâmetro : Endereço do arquivo de Clientes,apontador do arquivo e cpf Digitado.
//     Retorno   : nenhum. YYB
void alteraAnoCliente(FILE *arq,long posicao,char opcao,char *pCpfDigitado)
{
     int intLido;
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     gotoxy(25,10);
     printf("DIGITE O NOVO ANO DE INSCRICAO");
     intLido = leValidaNumeros(2011,99999,5);
     if (intLido == -1)
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
        return;
     }
    // fseek(arq,posicao - (sizeof(int)*1),1);
    //fseek(arq,posicao -(sizeof(tipoFrequentador)-(sizeof(tipoFrequentador)-(sizeof(int)*2))),1);
    // fseek(arq,posicao -(sizeof(tipoFrequentador)-(sizeof(tipoFrequentador)-(sizeof(int)))),1);
     fseek(arq,posicao+sizeof(tipoFrequentador)-(sizeof(int)),1);
     fwrite(&intLido,sizeof(int),1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("ANO MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarClientes(opcao,pCpfDigitado,arq);
}   
// Subprograma x
//     Objetivo  : Alterar o nome da série.
//     Parâmetro : Endereço do arquivo de séries e apontador do arquivo.
//     Retorno   : nenhum.
void alteraNomeSerie(FILE *arq,long posicao,char opcao, int codigoDigitado)   
{
     char nomeDigitado[MAX_NOME];
     tipoSerie estrutura;
     arq=abreArquivo("cadastroSeries.txt","r+b","\nErro ao abrir arquivo de Series");
     paraSairDigiteSair();
     digiteAserie();
     gotoxy(37,15);
     printf("NOVO NOME:");
     molduraNomes(15);
     leCharPorChar(nomeDigitado,MAX_NOME);
     validaSerieRepetida2(arq,nomeDigitado);
     if (nomeDigitado[0] == 27)
     {
            fclose(arq);
            clrscr();
            fflush(stdin);
            leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
            return;
     }
    // fseek(arq,posicao-256,1);
     //fseek(arq,posicao -sizeof(tipoSerie),1);
     //fseek(arq,sizeof(tipoSerie)-MAX_NOME-sizeof(float),1);
     fseek(arq,posicao+(sizeof(tipoSerie)-MAX_NOME-sizeof(float)),1);
     fwrite(nomeDigitado,sizeof(char)*MAX_NOME,1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("NOME MODIFICADO COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
}    
// Subprograma x
//     Objetivo  : Validar nome de series repetidas.
//     Parâmetro : Endereço do arquivo de séries e string do nome digitado.
//     Retorno   : nenhum. 
void validaSerieRepetida2(FILE *arq,char *pNomeDigitado)
{
    int aux=0, logico=0;
	char string[MAX_NOME],serieCapsLock[MAX_NOME];
	tipoSerie estrutura;
	strcpy(serieCapsLock,pNomeDigitado);
	capsLock(serieCapsLock);
	arq=abreArquivo("cadastroSeries.txt","a+b","\nErro ao abrir arquivo de Series");
	while(logico == 0)
    {
       if (aux > 0)
       {
               paraSairDigiteSair();
               gotoxy(38,14);
               textcolor(10);
               printf("%s",pNomeDigitado);
               molduraNomes(15);
               limpaTelaCordenada(27,17,28,' ');
               limpaTelaCordenada(21,12,38,' ');
               limpaTelaCordenada(14,24,55,' ');
               gotoxy(22,12);
               textcolor(LIGHTRED);
               printf("ESTA SERIE JA EXISTE! DIGITE NOVAMENTE:");
               leCharPorChar(pNomeDigitado,MAX_NOME);
               limpaTelaCordenada(16,14,48,' ');
               strcpy(serieCapsLock,pNomeDigitado);
	           capsLock(serieCapsLock);
               rewind(arq); 
               aux=0;      
       }
	  // while(fread(string,sizeof(char)*MAX_NOME,1,arq)!= 0)
	   while(fread(&estrutura,sizeof(tipoSerie),1,arq)!= 0)
	   {
         // fseek(arq,256-sizeof(char)*MAX_NOME,1);
         // capsLock(string);
          capsLock(estrutura.nomeSerie);
	    //  if (strcmp(string,serieCapsLock)==0)
	      if (strcmp(estrutura.nomeSerie,serieCapsLock)==0)
		  {
			logico = 0;
			aux++;
          }
       }
       if (aux == 0)
       {
          logico = 1;
       }
    }
	fclose(arq);  
}   
// Subprograma x
//     Objetivo  : Alterar a descrição da série.
//     Parâmetro : Endereço do arquivo de séries e apontador do arquivo.
//     Retorno   : nenhum.
void alteraDescricaoSerie(FILE *arq, long posicao, char opcao, int codigoDigitado)
{
     char nomeDigitado[MAX_FRASE],stringCopia[MAX_FRASE];
     tipoSerie estrutura;
     arq=abreArquivo("cadastroSeries.txt","r+b","\nErro ao abrir arquivo de Series");
     printf("\n\n\n\n\n\n\n\n\n\t\t\t      DIGITE A NOVA DESCRICAO:\n\n\t\t\t\t   ");
     leCharPorCharDescricao(nomeDigitado,MAX_FRASE);
     strcpy(stringCopia,nomeDigitado);
     capsLock(stringCopia);
     if (nomeDigitado[0] == 27)
     {
                fclose(arq);
                clrscr();
                leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
                return;
     }
     //fseek(arq,posicao-MAX_FRASE,1);
     //fseek(arq,posicao - sizeof(tipoSerie),1);
     //fseek(arq,sizeof(tipoSerie)-MAX_FRASE-MAX_NOME-sizeof(float),1);
     fseek(arq,posicao+(sizeof(int)*2),1);
     fwrite(nomeDigitado,sizeof(char)*MAX_FRASE,1,arq); 
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("DESCRICAO MODIFICADA COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
}  
// Subprograma x
//     Objetivo  : Alterar as calorias de uma série.
//     Parâmetro : Endereço do arquivo de séries e apontador do arquivo.
//     Retorno   : nenhum.
void alteraCaloriasSerie(FILE *arq, long posicao, char opcao, int codigoDigitado)
{
     float calorias;
     arq=abreArquivo("cadastroSeries.txt","r+b","\nErro ao abrir arquivo de Series");
     gotoxy(22,10);
     printf("DIGITE A NOVA QUANTIDADE DE CALORIAS:");
     calorias = leValidaNumeros(0,400,4);
     if (calorias == -1)
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
        return;
     }
     //fseek(arq,posicao-(MAX_FRASE+sizeof(float)),1);
     //fseek(arq,posicao - sizeof(tipoSerie),1);
     //fseek(arq,sizeof(tipoSerie)-sizeof(float),1);
     fseek(arq,posicao+(sizeof(tipoSerie)-sizeof(float)),1);
     fwrite(&calorias,sizeof(float),1,arq);  
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("CALORIA MODIFICADA COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
}

// Subprograma x
//     Objetivo  : Alterar a duração de uma série.
//     Parâmetro : Endereço do arquivo de séries e apontador do arquivo.
//     Retorno   : nenhum.
void alteraMinutosSerie(FILE *arq, long posicao, char opcao, int codigoDigitado)
{
     int minutos;
     arq=abreArquivo("cadastroSeries.txt","r+b","\nErro ao abrir arquivo de Series");
     gotoxy(25,10);
     printf("DIGITE A NOVA DURACAO EM MINUTOS:");
     minutos = leValidaNumeros(0,120,4);
     if (minutos == -1)
     {
        fclose(arq);
        clrscr();
        leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
        return;
     }
     //fseek(arq,posicao-(MAX_FRASE+sizeof(float)+sizeof(int)),1);
    // fseek(arq,posicao - sizeof(tipoSerie),1);
    // fseek(arq,sizeof(int),1);
     fseek(arq,posicao+sizeof(int),1);
     fwrite(&minutos,sizeof(int),1,arq);    
     fclose(arq);
     clrscr();
     textcolor(10);
     gotoxy(28,12);
     printf("DURACAO MODIFICADA COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para continuar!");
     getch();
     clrscr();
     leValidaMenuAlterarSeries(opcao,codigoDigitado,arq);
/*struct dadosSerie
{
    int codigo;     
               
    int duracao;      
    char frase[MAX_FRASE];   
    char nomeSerie[MAX_NOME]; 
    float calorias;          
};*/
}
// Subprograma x
//     Objetivo  : Apresentar uma mensagem de operação cancelada.
//     Parâmetro : nenhum.
//     Retorno   : nenhum.
void operacaoCancelada()
{
      int aux=0;
      textcolor(287);
      for (aux=0;aux<3;aux++)
      {
          gotoxy(1,12+aux);  
          printf("                                                                                ");
      }
      gotoxy(10,13);
      printf("OPERACAO CANCELADA! DIGITE QUALQUER COISA PARA VOLTAR AO MENU!\n");
      textcolor(WHITE);
      getch();
      limpaTelaEfeitoVertical();   
}
// Subprograma x
//     Objetivo  : Apresentar todos os dados de uma struct de clientes
//     Parâmetro : Endereço do arquivo de clientes, localização do apontador e cpf digitado.
//     Retorno   : Localização do apontador. YYA
long mostraRegistroPesquisadoClientes(FILE *arq, long tamanho,char *pCpfDigitado)
{
                 int aux=0;
                 /*char cpfLido[TAM_NOME],nomeLido[TAM_NOME],sexoLido;
                 float pesoLido;
                 int diaLido,mesLido,anoLido;*/
                 tipoFrequentador estrutura;
                 arq=abreArquivo("cadastroclientes.txt","rb","\nErro ao abrir arquivo de Clientes!");
	             //while(fread(cpfLido,sizeof(char)*MAX_CPF,1,arq)!= 0)
	            // while(fread(&estrutura.cpf,sizeof(char)*MAX_CPF,1,arq)!= 0)
	             while(fread(&estrutura.cpf,sizeof(tipoFrequentador),1,arq)!= 0)
	             {
		              //if (strcmp(cpfLido,pCpfDigitado)==0)
		              if (strcmp(estrutura.cpf,pCpfDigitado)==0)
		              {
                          /*fread(nomeLido,sizeof(char)*TAM_NOME,1,arq);
                          fread(&pesoLido,sizeof(float),1,arq);
                          fread(&sexoLido,sizeof(char),1,arq);
                          fread(&diaLido,sizeof(int),1,arq);
                          fread(&mesLido,sizeof(int),1,arq);
                          fread(&anoLido,sizeof(int),1,arq);*/
                          //fseek(arq,-1*(sizeof(char)*MAX_CPF),1); //novo
                         // fread(&estrutura,sizeof(tipoFrequentador),1,arq);
                         // apresentaDadosClientes(cpfLido,nomeLido,&pesoLido,&sexoLido,&diaLido,&mesLido,&anoLido);
                          apresentaDadosClientes(&estrutura);
                          tamanho = ftell(arq) - sizeof(tipoFrequentador);
                          break;
                      }
                     // fseek(arq,(sizeof(char)*TAM_NOME)+sizeof(float)+sizeof(char)+(sizeof(int)*3),1);
                 }
                 fclose(arq);
                 gotoxy(1,25);
                 printf("posicao = %lu, tamanhoStruct = %d",tamanho,sizeof(tipoFrequentador));
              //   getch();
                 return tamanho;
}
//CPF    (CHAR * TAM_NOME)
//NOME  (CHAR * TAM_NOME)
//PESO (FLOAT)                      
//SEXO (CHAR)
//DIA (INT)                          TAMANHO = 101 bytes
//MES (INT)
//ANO (INT)
// Subprograma x ss1
//     Objetivo  : Apresentar todos os dados de um certo registro.
//     Parâmetro : Endereço do arquivo de séries, localização do apontador e código digitado.
//     Retorno   : Localização do apontador.
long mostraRegistroPesquisado(FILE *arq, long tamanho, int codigoDigitado)
{
                 int aux=0,codigo,duracao;
                 float calorias;
                 char nomeSerie[MAX_NOME],frase[MAX_FRASE],novoNome[MAX_NOME];
                 tipoSerie estrutura;
                 arq=abreArquivo("cadastroSeries.txt","rb","\nErro ao abrir arquivo de Series");
                // fseek(arq,(sizeof(char) * MAX_NOME),1);
	           //  while(fread(&codigo,sizeof(int),1,arq)!= 0)
	             while(fread(&estrutura,sizeof(tipoSerie),1,arq)!= 0)
	             {
		              //if (codigo == codigoDigitado)
		              if (estrutura.codigo == codigoDigitado)
		              {
                          
                          //fseek(arq,-(sizeof(int) + sizeof(char)*MAX_NOME),1);
                          //fread(nomeSerie,sizeof(char)*MAX_NOME,1,arq);
                          //fread(&codigo,sizeof(int),1,arq);
                          //fread(&duracao,sizeof(int),1,arq);
                          //fread(&calorias,sizeof(float),1,arq);
                          //fread(frase,sizeof(char)*MAX_FRASE,1,arq);
                         // apresentaDadosSeries(&codigo,&duracao,frase,nomeSerie,&calorias);
                          apresentaDadosSeries(&estrutura);
                          tamanho = ftell(arq) - sizeof(tipoSerie);
                          break;
                      }
                     // fseek(arq,256-sizeof(int),1);
                 }
                 fclose(arq);
                 return tamanho;
}
// Subprograma x
//     Objetivo  : Deletar um registro de um arquivo.
//     Parâmetro : Endereço do arquivo de séries e localização do apontador.
//     Retorno   : Nenhum.
int deletarRegistro(FILE *arq,long apontador,int tamanhoStruct)
{
     //protótipos.
     void mostraMenuDeletar();
     //Declaraçoes
     FILE *arqTemporario;
     int confirmou;
     long bytes=0, tamanhoArquivo;
     char nomeSerie[MAX_NOME];
     int codigo,duracao;
     float calorias;
     char frase[MAX_FRASE];
     tipoSerie estrutura;
     //instruções:       
     mostraMenuDeletar();
     confirmou = simOuNao(202,15,4);
     if (!confirmou)
     {
        operacaoCancelada();
        return 0;
     }
     arq=abreArquivo("cadastroSeries.txt","r+b","\nErro ao abrir arquivo de Series");
     arqTemporario=abreArquivo("temp.txt","wb","\nErro ao abrir arquivo Temporario");
     fseek(arq,0,2);
     tamanhoArquivo = ftell(arq);
     rewind(arq);
     //while(bytes < (apontador-tamanhoStruct))
     while(bytes < tamanhoArquivo)
     {
                 
                 /*fread(nomeSerie,sizeof(char)*MAX_NOME,1,arq);
                 fwrite(nomeSerie,sizeof(char)*MAX_NOME,1,arqTemporario); 
                 fread(&codigo,sizeof(int),1,arq);
                 fwrite(&codigo,sizeof(int),1,arqTemporario);           
                 fread(&duracao,sizeof(int),1,arq);
                 fwrite(&duracao,sizeof(int),1,arqTemporario);
                 fread(&calorias,sizeof(float),1,arq);
                 fwrite(&calorias,sizeof(float),1,arqTemporario);
                 fread(frase,sizeof(char)*MAX_FRASE,1,arq);
                 fwrite(frase,sizeof(char)*MAX_FRASE,1,arqTemporario);*/
                 if (bytes == apontador)
                    fseek(arq,sizeof(tipoSerie),1);
                 bytes = ftell(arq);
                 if (bytes == tamanhoArquivo)
                    break;
                 fread(&estrutura,sizeof(tipoSerie),1,arq);
                 fwrite(&estrutura,sizeof(tipoSerie),1,arqTemporario);
                 bytes = ftell(arq);
                 /*if (bytes == apontador)
                    fseek(arq,sizeof(tipoFrequentador),1);
                 if (bytes == tamanhoArquivo-sizeof(tipoFrequentador))
                    break;
                 fread(&estrutura,sizeof(tipoFrequentador),1,arq); //New
                 fwrite(&estrutura,sizeof(tipoFrequentador),1,arqTemporario);// New
                 bytes = ftell(arq);*/
                 
                 
     }
     //fseek(arq,tamanhoStruct,1);
     /*fseek(arq,sizeof(tipoSerie),1);
     bytes = ftell(arq);
     while(bytes < tamanhoArquivo)
     {
                 /*fread(nomeSerie,sizeof(char)*MAX_NOME,1,arq);
                 fwrite(nomeSerie,sizeof(char)*MAX_NOME,1,arqTemporario); 
                 fread(&codigo,sizeof(int),1,arq);
                 fwrite(&codigo,sizeof(int),1,arqTemporario);           
                 fread(&duracao,sizeof(int),1,arq);
                 fwrite(&duracao,sizeof(int),1,arqTemporario);
                 fread(&calorias,sizeof(float),1,arq);
                 fwrite(&calorias,sizeof(float),1,arqTemporario);
                 fread(frase,sizeof(char)*MAX_FRASE,1,arq);
                 fwrite(frase,sizeof(char)*MAX_FRASE,1,arqTemporario);
                 fread(&estrutura,sizeof(tipoSerie),1,arq);
                 fwrite(&estrutura,sizeof(tipoSerie),1,arqTemporario);
                 bytes = ftell(arq);
     }*/
     fclose(arq);
     fclose(arqTemporario);
     remove("cadastroSeries.txt");
     rename("temp.txt","cadastroSeries.txt");
     clrscr();
     gotoxy(27,13);
     textcolor(LIGHTRED);
     printf("SERIE DELETADA COM SUCESSO!");
     gotoxy(20,24);
     textcolor(10);
     printf("Digite qualquer coisa para voltar ao menu!");
     getch();
     system("CLS");
     return 1;    
}
// Subprograma x
//     Objetivo  : Apresentar um menu de confirmação de exclusão de dados.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraMenuDeletar()
{
     textcolor(207);
     gotoxy(15,3);
     printf(" TEM CERTEZA QUE DESEJA DELETAR O REGISTRO ABAIXO? ");
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Ler a opção SIM ou NÃO.
//     Parâmetro : opção.
//     Retorno   : Verdadeiro ou Falso.
int simOuNao(int cor,int x, int y)
{
    int aux=1;
    char opcao;
    do
    {
                  gotoxy(x,y);
                  textcolor(cor);
                  printf("  Pressione ENTER p/ confirmar ou ESQ p/ sair  ");
                //  printf("  Pressione ENTER p/ confirmar ou ESQ p/ cancelar  ");
                  opcao = getch();
                  textcolor(WHITE);
                  if (opcao == 13)
                  {
                     return 1;
                  }
                  if (opcao == 27)
                  {
                     return 0;
                  }
                  
    }while((opcao != 13) && (opcao != 27)); 
}
// Subprograma x
//     Objetivo  : Validar código repetidos.
//     Parâmetro : Endereço do arquivo de séries, Código digitado e tamanho da estrutura de séries.
//     Retorno   : nenhum. 
void validaCodigoRepetido(FILE *arq,int *pCodigoDigitado,int tamanhoStruct)
{
    int aux=0, logico=0,codigoComparar;
	arq=abreArquivo("cadastroSeries.txt","a+b","\nErro ao abrir arquivo de Series");
	tipoSerie estrutura;
	while(logico == 0)
    {
       if (aux > 0)
       {
               fclose(arq);
               return;
               
       }
       //fseek(arq,sizeof(char)*MAX_NOME,1);
	  // while(fread(&codigoComparar,sizeof(int),1,arq)!= 0)
	   while(fread(&estrutura,sizeof(tipoSerie),1,arq)!= 0)
	   {
          //fseek(arq,tamanhoStruct-sizeof(int),1);
	      if (*pCodigoDigitado == estrutura.codigo)
		  {
			logico = 1;
			aux++;
			
          }
       }
       if (aux == 0)
       {
          fazMolduraCadastros(49999);
          paraSairDigiteSair();
          gotoxy(23,14);
          textcolor(LIGHTRED);
          printf("CODIGO INEXISTENTE, DIGITE NOVAMENTE:");
          textcolor(WHITE);
          *pCodigoDigitado = leValidaNumeros(999,9999,5);
          textcolor(WHITE);
          fflush(stdin);
          if(*pCodigoDigitado == -1)
          {
                              fclose(arq);
                              return;
          }
          if (*pCodigoDigitado == -2) 
          {
                fclose(arq);
                return;
          }
          rewind(arq);
          logico = 0;
       }
    }
	fclose(arq);   
}   
// Subprograma x
//     Objetivo  : Ler e validar o sexo.
//     Parâmetro : Ponteiro de sexo.
//     Retorno   : Nenhum.             YYA
void leValidaSexo(char *pSexo)
{
     char opcao;
     int contador=1;
     paraSairDigiteSair();
     do
     {

                       escreveQualquerCoisa("SELECIONE O SEXO DO CLIENTE:",15,28,11);
                       escreveQualquerCoisa("           ",15,28,15);
                       escreveQualquerCoisa(" MASCULINO ",15,28,16);
                       escreveQualquerCoisa("           ",15,28,17);
                       if (contador == 1)
                       {
                            escreveQualquerCoisa("           ",31,28,15);
                            escreveQualquerCoisa(" MASCULINO ",31,28,16);
                            escreveQualquerCoisa("           ",31,28,17);
                       }
                       escreveQualquerCoisa("          ",15,44,15);
                       escreveQualquerCoisa(" FEMININO ",15,44,16);
                       escreveQualquerCoisa("          ",15,44,17);
                       if (contador == 2)
                       {
                            escreveQualquerCoisa("          ",208,44,15);
                            escreveQualquerCoisa(" FEMININO ",208,44,16);
                            escreveQualquerCoisa("          ",208,44,17);
                       }
                       opcao = getch();
                       if (opcao == 27)
                       {
                                 *pSexo = '0';
                                 return;
                       }
                       contador = quantidadeSetasMenuHorizontal(opcao,2,contador);
     }while(opcao != 13);
     if (contador == 1)
        *pSexo = 'M';
     else
         *pSexo = 'F';
}
// Subprograma x
//     Objetivo  : Gravar uma estrutura de atividades em um arquivo binário.
//     Parâmetro : Ponteiro do arquivo de atividades e endereço da estrutura de atividades.
//     Retorno   : Nenhum.
void gravaDadosAtividades(FILE *arqAtividades,struct dadosAtividades *atividades)
{
     arqAtividades=abreArquivo("Atividades.txt","a+b","\nErro ao abrir arquivo de Atividades");
     /*fwrite(atividades->cpf,(sizeof(char) * TAM_NOME),1,arqAtividades);
     fwrite(&atividades->codigo,sizeof(int),1,arqAtividades);
     fwrite(&atividades->dia,sizeof(int),1,arqAtividades);
     fwrite(&atividades->mes,sizeof(int),1,arqAtividades);
     fwrite(&atividades->ano,sizeof(int),1,arqAtividades);
     fwrite(atividades->hora,sizeof(char)*MAXHORA,1,arqAtividades);*/
     fwrite(atividades,sizeof(tipoAtividade),1,arqAtividades);
     fflush(stdin);
     fclose(arqAtividades);
}  
// Subprograma x
//     Objetivo  : Verificar se uma série já foi executada.
//     Parâmetro : Código digitado, Endereço do arquivo de Atividades e tamanho da estrutura de atividades.
//     Retorno   : Verdadeiro ou falso.
int verificaSeFezAtividade(int codigo,FILE *arq, int tamanhoStruct)
{
     int codigoComparar;
     arq=abreArquivo("Atividades.txt","rb","\nErro ao abrir arquivo de Atividades");
     rewind(arq);
     fseek(arq,sizeof(char)*TAM_NOME,1);
     while(fread(&codigoComparar,sizeof(int),1,arq)!= 0)
     {
          fseek(arq,67-sizeof(int),1);
          if (codigoComparar == codigo)
          {
                     fclose(arq);
                     return 1;
          }
     }
     fclose(arq);
     return 0;   
}
// Subprograma x
//     Objetivo  : Verificar se o Cpf informado já efetuou alguma atividade
//     Parâmetro : Ponteiro do Cpf digitado e endereço do arquivo.
//     Retorno   : Verdadeiro ou falso.
int verificaCpfAtividades(char *pCpf, FILE *arq)
{
     char cpfComparar[TAM_NOME];
     arq=abreArquivo("Atividades.txt","rb","\nErro ao abrir arquivo de Atividades");
     while(fread(cpfComparar,sizeof(char)*TAM_NOME,1,arq)!= 0)
     {
          if (strcmp(cpfComparar,pCpf)==0)
          {
                     fclose(arq);
                     return 1;
          }
          fseek(arq,67 -(sizeof(char)*TAM_NOME),1);
     }
     fclose(arq);
     return 0;
     
}
// Subprograma x
//     Objetivo  : Validar nome de series repetidas.
//     Parâmetro : Endereço do arquivo de séries, string do nome digitado e tamanho da struct.
//     Retorno   : nenhum. 
void naoRepeteCpf(FILE *arq,char *pCpfDigitado,int tamanho)
{
    int aux=0, logico=0;
	char string[TAM_NOME],serieCapsLock[TAM_NOME];
	tipoFrequentador estrutura;
	strcpy(serieCapsLock,pCpfDigitado);
	capsLock(serieCapsLock);
	arq=abreArquivo("cadastroClientes.txt","rb","\nErro ao abrir arquivo de CPF's");
	while(logico == 0)
    {
       if (aux > 0)
       {
               limpaTelaCordenada(25,17,35,' ');
               escreveQualquerCoisa("ESTE CPF JA EXISTE! DIGITE NOVAMENTE:",15,24,3);
               leCharPorChar(pCpfDigitado,10);
               strcpy(serieCapsLock,pCpfDigitado);
	           capsLock(serieCapsLock);
               rewind(arq); 
               aux=0;
       }
	  // while(fread(string,sizeof(char)*MAX_NOME,1,arq)!= 0)
      // while(fread(&estrutura.cpf,sizeof(char)*MAX_CPF,1,arq)!= 0)
        while(fread(&estrutura,sizeof(tipoFrequentador),1,arq)!= 0)
	   {
        //  fseek(arq,tamanho-sizeof(char)*MAX_NOME,1);
        //capsLock(string);
          capsLock(estrutura.cpf);
	      if (strcmp(estrutura.cpf,serieCapsLock)==0)
		  {
			logico = 0;
			aux++;
          }
       }
       if (aux == 0)
       {
          logico = 1;
       }
    }
	fclose(arq);
}   
// Subprograma x
//     Objetivo  : Verificar e validar se o CPF existe
//     Parâmetro : Endereço do arquivo de Clientes, string do nome digitado e tamanho da struct.
//     Retorno   : Nenhum. 
int verificaCpfExiste(FILE *arq,char *pCpfDigitado,int tamanho)
{
    int aux=0, logico=0;
	char string[TAM_NOME],serieCapsLock[TAM_NOME];
	tipoFrequentador estrutura;
	strcpy(serieCapsLock,pCpfDigitado);
	capsLock(serieCapsLock);
	arq=abreArquivo("cadastroClientes.txt","rb","\nErro ao abrir arquivo de CPF's");
	while(logico == 0)
    {
	//   while(fread(string,sizeof(char)*MAX_NOME,1,arq)!= 0)
	   while(fread(&estrutura,sizeof(tipoFrequentador),1,arq)!= 0)
	   {
         // fseek(arq,tamanho-sizeof(char)*MAX_NOME,1);
         // capsLock(string);
          capsLock(estrutura.cpf);
	    //  if (strcmp(string,serieCapsLock)==0) 
	      //printf("estrutura.cpf = %s , serieCapsLock = %s",estrutura.cpf,serieCapsLock);
	      //getch();
	      if (strcmp(estrutura.cpf,serieCapsLock)==0) 
		  {
			fclose(arq);   // achou!
			tamanho = ftell(arq) - sizeof(tipoFrequentador);
			//return 1;
			return tamanho;
          }
       }
       if (aux == 0)          // não achou!
       {
          logico = 0;
          escreveQualquerCoisa("   PARA VOLTAR AO MENU DIGITE ESQ   ",79,23,25);
          escreveQualquerCoisa(" CPF INEXISTENTE! DIGITE NOVAMENTE! ",79,23,24);
          //leValidaString(pCpfDigitado);
          //if (strcmp(pCpfDigitado,"0")==0)
          //{
          //   return 0;
          //}
          //system("CLS");
          fclose(arq);
          return 0;
          strcpy(serieCapsLock,pCpfDigitado);
          capsLock(serieCapsLock);
          rewind(arq); 
          aux=0;
       }
    }
	fclose(arq);
    
}   
// Subprograma x
//     Objetivo  : Encontrar o cpf de uma atividade para chamar a função de deletar.
//     Parâmetro : Ponteiro do arquivo de atividades e ponteiro do CPF procurado.
//     Retorno   : Nenhum. 
void excluiAtividade(FILE *arq, char *pCpf)
{
     //Declarações
     char cpfComparar[TAM_NOME];
     long apontador;
     int opcao;
     tipoAtividade estrutura;
     //Instruções
     arq=abreArquivo("Atividades.txt","rb","\nErro ao abrir arquivo de Atividades");
  //   while(fread(cpfComparar,sizeof(char)*TAM_NOME,1,arq)!= 0)
     while(fread(&estrutura,sizeof(tipoAtividade),1,arq)!= 0)
     {
       //   if (strcmp(cpfComparar,pCpf)==0)
          if (strcmp(estrutura.cpf,pCpf)==0)
          {
                     apontador = ftell(arq) - sizeof(tipoAtividade);  
                     fclose(arq);                  
                     opcao = mostraAtividades(arq,apontador,pCpf);
                     if (!opcao)
                        return;
                   //  fseek(arq,apontador-(sizeof(char)*TAM_NOME),1);
                     return;
                     
          }
         // fseek(arq,67 -(sizeof(char)*TAM_NOME),1);
     }
     fclose(arq);
} 

// Subprograma x
//     Objetivo  : Apresentar todos os dados de um certo registro.
//     Parâmetro : Endereço do arquivo de Atividades, localização do apontador e código digitado.
//     Retorno   : Localização do apontador.
int mostraAtividades(FILE *arq, long apontador,char *pCpf)
{
                 // Protótipos
                 int leValidaMenuExcluirAtividade(int aux);
                 // Declarações
                 char cpf[TAM_NOME], horas[MAXHORA];
                 int codigo,dia,mes,ano;
                 int saltar=1;
                 int aux=0, listagem=0;
                 int opcao;
                 tipoAtividade estrutura;
                 // Instruções
                 arq=abreArquivo("Atividades.txt","rb","\nErro ao abrir arquivo de Atividades");
	            // while(fread(cpf,sizeof(char)*TAM_NOME,1,arq)!= 0)
                 while(fread(&estrutura,sizeof(tipoAtividade),1,arq)!= 0)
	             {
		             // if (strcmp(cpf,pCpf)==0)
		              if (strcmp(estrutura.cpf,pCpf)==0)
		              {
                          aux++;
                         // fseek(arq,(sizeof(int)*4)+MAXHORA,1);
                          fflush(stdin);
                          listagem++;
                          if (listagem == 10)
                          {
                                       system("PAUSE");
                                       listagem=0;
                                       system("CLS");
                          }
                          saltar=0;
                      }
                      if (saltar)
                        // fseek(arq,67-(sizeof(char)*TAM_NOME),1); aa1
                      saltar=1;
                 }
                 fclose(arq);
                 opcao = leValidaMenuExcluirAtividade(aux); 
                 apontaParaEscolhaLista(opcao);
                 if (opcao == 0)
                 {
                    limpaTelaEfeitoVertical();
                    return;
                 }
                 apontador = achaRegistroAtividades(opcao, pCpf, arq);
                 deletarRegistroAtividades(arq,apontador,67);
                 return opcao;
}
// Subprograma x
//     Objetivo  : Ler e validar a opção de atividades.
//     Parâmetro : quantidade de registros.
//     Retorno   : opção válida.
int leValidaMenuExcluirAtividade(int aux)
{
    int cont=0, opcao;
    printf("\n\n\t\t   DIGITE O NUMERO DA ATIVIDADE QUE DESEJA EXCLUIR:");
    printf("\t\t\t                      (para voltar digite 0):\n\n");
    do
    {
              if (cont > 0)
                 printf("Opcao invalida! Digite novamente:\n");
              
              scanf("%d",&opcao);
              fflush(stdin);
              cont++;
    }while((opcao < 0) || (opcao > aux));
    return opcao;
}
// Subprograma x
//     Objetivo  : Encontrar o apontador para o registro a ser deletado.
//     Parâmetro : número do registro, cpf digitado e endereço de memória do arquivo de Atividades.
//     Retorno   : Apontador em bytes.
long achaRegistroAtividades(int qualRegistro, char *pCpf, FILE *arq)
{
                 //Declarações
                 int saltar=1,aux=0;
                 char cpf[MAX_NOME];
                 long contBytes;
                 tipoAtividade estrutura;
                 //Instruções
                 arq=abreArquivo("Atividades.txt","rb","\nErro ao abrir arquivo de Atividades");
	            // while(fread(cpf,sizeof(char)*TAM_NOME,1,arq)!= 0)
	             while(fread(&estrutura,sizeof(tipoAtividade),1,arq)!= 0)
	             {
		              //if (strcmp(cpf,pCpf)==0)
	                  if (strcmp(estrutura.cpf,pCpf)==0)
		              {
                          aux++;
                          //fseek(arq,67-(sizeof(char)*TAM_NOME),1);
                          contBytes = ftell(arq);
                          if (aux == qualRegistro)
                          {
                                  fclose(arq);
                                  return contBytes - sizeof(tipoAtividade);
                          }
                          saltar=0;
                      }
                      if (saltar)
                        // fseek(arq,67 -(sizeof(char)*TAM_NOME),1);
                      saltar=1;
                 }
                 fclose(arq);
}
//CPF    (CHAR * TAM_NOME)
//NOME  (CHAR * TAM_NOME)
//PESO (FLOAT)                      
//SEXO (CHAR)
//DIA (INT)                          TAMANHO = 101 bytes
//MES (INT)
//ANO (INT)
//  long mostraRegistroPesquisadoClientes(FILE *arq, long tamanho,char *pCpfDigitado)
// Subprograma x
//     Objetivo  : Achar o Cliente a ser deletado.
//     Parâmetro : 
//     Retorno   : Endereço do registro.
void achaEmostraRegistroDeletar(FILE *arq,char *pCpfDigitado)
{
     long apontador;
     apontador = mostraRegistroPesquisadoClientes(arq,apontador,pCpfDigitado);
     deletarRegistroClientes(arq,apontador,101);
     return;
}

// Subprograma x
//     Objetivo  : Deletar um registro de Clientes.
//     Parâmetro : Endereço de memória do arquivo de Clientes, apontador do registro a ser deletado e tamanho de cada registro.
//     Retorno   : Nenhum. YYC
void deletarRegistroClientes(FILE *arq,long apontador,int tamanhoStruct)
{
     //protótipos.
     void mostraMenuDeletar();
     //Declaraçoes
     FILE *arqTemporario;
     int confirmou;
     long bytes=0, tamanhoArquivo;
     char nomeLido[TAM_NOME],sexoLido,cpfLido[MAX_CPF];
     int diaLido,mesLido,anoLido;
     float pesoLido;
     tipoFrequentador estrutura;
     //instruções:       
     mostraMenuDeletar();
     confirmou = simOuNao(202,15,4);
     if (!confirmou)
     {
        operacaoCancelada();
        limpaTelaEfeitoVertical();
        return;
     }
     arq=abreArquivo("cadastroClientes.txt","r+b","\nErro ao abrir arquivo de Clientes");
     arqTemporario=abreArquivo("temp.txt","wb","\nErro ao abrir arquivo Temporario");
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroClientes.txt");
     rewind(arq);
     //while(bytes < (apontador-tamanhoStruct))
     //while(bytes < (apontador-sizeof(tipoFrequentador)))
    // while(bytes < (apontador))
     while(bytes < tamanhoArquivo)
     {
                 
                 /*fread(cpfLido,sizeof(char)*MAX_CPF,1,arq);
                 fwrite(cpfLido,sizeof(char)*MAX_CPF,1,arqTemporario); 
                 fread(nomeLido,sizeof(char)*TAM_NOME,1,arq);
                 fwrite(nomeLido,sizeof(char)*TAM_NOME,1,arqTemporario);           
                 fread(&pesoLido,sizeof(float),1,arq);
                 fwrite(&pesoLido,sizeof(float),1,arqTemporario);
                 fread(&sexoLido,sizeof(char),1,arq);
                 fwrite(&sexoLido,sizeof(char),1,arqTemporario);
                 fread(&diaLido,sizeof(int),1,arq);
                 fwrite(&diaLido,sizeof(int),1,arqTemporario);
                 fread(&mesLido,sizeof(int),1,arq);
                 fwrite(&mesLido,sizeof(int),1,arqTemporario);
                 fread(&anoLido,sizeof(int),1,arq);
                 fwrite(&anoLido,sizeof(int),1,arqTemporario);*/
                 if (bytes == apontador)
                    fseek(arq,sizeof(tipoFrequentador),1);
                 bytes = ftell(arq);
                 if (bytes == tamanhoArquivo)
                    break;
                 fread(&estrutura,sizeof(tipoFrequentador),1,arq); //New
                 fwrite(&estrutura,sizeof(tipoFrequentador),1,arqTemporario);// New
                 bytes = ftell(arq);
                 
     }
     /*fseek(arq,sizeof(tipoFrequentador),1);
     bytes = ftell(arq);
     while(bytes < tamanhoArquivo)
     {
                 /*fread(cpfLido,sizeof(char)*MAX_CPF,1,arq);
                 fwrite(cpfLido,sizeof(char)*MAX_CPF,1,arqTemporario); 
                 fread(nomeLido,sizeof(char)*TAM_NOME,1,arq);
                 fwrite(nomeLido,sizeof(char)*TAM_NOME,1,arqTemporario);           
                 fread(&pesoLido,sizeof(float),1,arq);
                 fwrite(&pesoLido,sizeof(float),1,arqTemporario);
                 fread(&sexoLido,sizeof(char),1,arq);
                 fwrite(&sexoLido,sizeof(char),1,arqTemporario);
                 fread(&diaLido,sizeof(int),1,arq);
                 fwrite(&diaLido,sizeof(int),1,arqTemporario);
                 fread(&mesLido,sizeof(int),1,arq);
                 fwrite(&mesLido,sizeof(int),1,arqTemporario);
                 fread(&anoLido,sizeof(int),1,arq);
                 fwrite(&anoLido,sizeof(int),1,arqTemporario);
                 fread(&estrutura,sizeof(tipoFrequentador),1,arq);//new
                 fwrite(&estrutura,sizeof(tipoFrequentador),1,arqTemporario);//new
                 bytes = ftell(arq);
     }*/
     fclose(arq);
     fclose(arqTemporario);
     remove("cadastroClientes.txt");
     rename("temp.txt","cadastroClientes.txt");
     clrscr();
     gotoxy(27,13);
     textcolor(LIGHTRED);
     printf("CLIENTE DELETADO COM SUCESSO!");
     gotoxy(20,24);
     textcolor(10);
     printf("Digite qualquer coisa para voltar ao menu!");
     getch();
     system("CLS");  
}
// Subprograma x aa1
//     Objetivo  : Deletar um registro de Atividade.
//     Parâmetro : Endereço de memória do arquivo de Atividades, apontador do registro a ser deletado e tamanho de cada registro.
//     Retorno   : Nenhum.
void deletarRegistroAtividades(FILE *arq,long apontador,int tamanhoStruct)
{
     //protótipo.
     void mostraMenuDeletar();
     //Declaraçoes
     FILE *arqTemporario;
     int confirmou;
     long bytes=0, tamanhoArquivo;
     char cpf[MAX_NOME], horas[MAXHORA];
     int codigo,dia,mes,ano;
     tipoAtividade estrutura;
     //instruções:       
     criaMiniTelaAzul(79);
     escreveQualquerCoisa("DESEJA DELETAR ESSA ATIVIDADE?",79,25,15);
     confirmou = simOuNao(74,18,21);
     if (!confirmou)
     {
        limpaTelaEfeito();
        system("CLS");
        operacaoCancelada();
        return;
     }
     arq=abreArquivo("Atividades.txt","r+b","\nErro ao abrir arquivo de Atividades");
     arqTemporario=abreArquivo("tempAtividade.txt","wb","\nErro ao abrir arquivo Temporario");
     fseek(arq,0,2);
     tamanhoArquivo = ftell(arq);
     rewind(arq);
     //while(bytes < (apontador-tamanhoStruct))
     while(bytes < tamanhoArquivo)
     {
                 /*fread(cpf,sizeof(char)*MAX_NOME,1,arq);
                 fwrite(cpf,sizeof(char)*MAX_NOME,1,arqTemporario); 
                 fread(&codigo,sizeof(int),1,arq);
                 fwrite(&codigo,sizeof(int),1,arqTemporario);        
                 fread(&dia,sizeof(int),1,arq);
                 fwrite(&dia,sizeof(int),1,arqTemporario);
                 fread(&mes,sizeof(int),1,arq);
                 fwrite(&mes,sizeof(int),1,arqTemporario);
                 fread(&ano,sizeof(int),1,arq);
                 fwrite(&ano,sizeof(int),1,arqTemporario);
                 fread(horas,sizeof(char)*MAXHORA,1,arq);
                 fwrite(horas,sizeof(char)*MAXHORA,1,arqTemporario);*/
                 if (bytes == apontador)
                    fseek(arq,sizeof(tipoAtividade),1);
                 bytes = ftell(arq);
                 if (bytes == tamanhoArquivo)
                    break;
                 fread(&estrutura,sizeof(tipoAtividade),1,arq);
                 fwrite(&estrutura,sizeof(tipoAtividade),1,arqTemporario);
                 fflush(stdin);
                 bytes = ftell(arq);
                 
                 /*if (bytes == apontador)
                    fseek(arq,sizeof(tipoFrequentador),1);
                 bytes = ftell(arq);
                 if (bytes == tamanhoArquivo)
                    break;
                 fread(&estrutura,sizeof(tipoFrequentador),1,arq); //New
                 fwrite(&estrutura,sizeof(tipoFrequentador),1,arqTemporario);// New
                 bytes = ftell(arq);*/
     }
     /*fseek(arq,tamanhoStruct,1);
     bytes = ftell(arq);
     fflush(stdin);
     while(bytes < tamanhoArquivo)
     {
                 fread(cpf,sizeof(char)*MAX_NOME,1,arq);
                 fwrite(cpf,sizeof(char)*MAX_NOME,1,arqTemporario); 
                 fread(&codigo,sizeof(int),1,arq);
                 fwrite(&codigo,sizeof(int),1,arqTemporario);        
                 fread(&dia,sizeof(int),1,arq);
                 fwrite(&dia,sizeof(int),1,arqTemporario);
                 fread(&mes,sizeof(int),1,arq);
                 fwrite(&mes,sizeof(int),1,arqTemporario);
                 fread(&ano,sizeof(int),1,arq);
                 fwrite(&ano,sizeof(int),1,arqTemporario);
                 fread(horas,sizeof(char)*MAXHORA,1,arq);
                 fwrite(horas,sizeof(char)*MAXHORA,1,arqTemporario);
                 fflush(stdin);
                 bytes=ftell(arq);
     }*/
     fclose(arq);
     fclose(arqTemporario);
     remove("Atividades.txt");
     rename("tempAtividade.txt","Atividades.txt");
     clrscr();
     gotoxy(25,12);
     printf("ATIVIDADE DELETADA COM SUCESSO!");
     gotoxy(1,24);
     printf("Digite qualquer coisa para voltar ao menu!");
     getch();
     system("CLS");
     return;     
}
// Subprograma x
//     Objetivo  : Apresentar uma mensagem de voltar ao menu.
//     Parâmetro : nenhum.
//     Retorno   : nenhum.
void voltarAoMenu0()
{
     gotoxy(25,7);
     textcolor(WHITE);
     printf("  para voltar ao menu digite");
     textcolor(10);
     printf(" 0");
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Apresentar as opções do menu principal.
//     Parâmetro : Opção.
//     Retorno   : Opção válida.
int leValidaMenuPrincipal(int opcao)
{
     int aux;
     aux = opcao;
     do
     {
                        if (aux == 1)
                        {
                             fazMolduraEscolha(30,9,10);
                             gotoxy(15,24);
                             printf("Incluir, alterar ou excluir dados de um frequentador!");
                        }
                        if (aux == 2)
                        {
                             fazMolduraEscolha(30,11,10);
                             gotoxy(15,24);
                             printf("Incluir, alterar ou excluir uma serie de exercicios!");
                        }
                        if (aux == 3)
                        {
                             fazMolduraEscolha(30,13,10);
                             gotoxy(23,24);
                             printf("Incluir ou excluir uma atividade!");
                        }
                        if (aux == 4)
                        {
                             fazMolduraEscolha(30,15,10);
                             gotoxy(18,24);
                             printf("Fazer diversas pesquisas nos dados da academia!");
                        }
                        if (aux == 5)
                        {
                             fazMolduraEscolha(30,17,12);
                             gotoxy(31,24);
                             textcolor(LIGHTRED);
                             printf("Sair do programa!");
                        }
                        mostraMenu();
                        gotoxy(38,20);
                        opcao = getch();
                        if (opcao == 13)
                        {
                            return aux;
                        }
                        if (opcao == 27)
                           aux = 5;
                        clrscr();
                        aux = quantidadeSetasMenu(opcao,5,aux);
                        clrscr();
     }while(opcao != 13);
     return opcao;
}
// Subprograma x
//     Objetivo  : Apresentar o menu principal.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraMenu()
{
     fazMoldura();
     textcolor(WHITE);
     gotoxy(38,7);
     printf("MENU");
     gotoxy(33,10);
     printf("FREQUENTADORES");
     gotoxy(33,12);
     printf("SERIES");
     gotoxy(33,14);
     printf("ATIVIDADES");
     gotoxy(33,16);
     printf("RELATORIOS");
     gotoxy(33,18);
     printf("SAIR");
}
// Subprograma x
//     Objetivo  : Fazer uma moldura pequena.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void fazMoldura()
{
     textcolor(WHITE);
     int aux=0;
     for (aux=0; aux < 15; aux++)
     {
       gotoxy(28,aux+6);
       printf("%c",219);
     }
     for (aux=0; aux < 15; aux++)
     {
       gotoxy(50,aux+6);
       printf("%c",219);
     }
     for (aux=0; aux < 21; aux++)
     {
       gotoxy(29+aux,6);
       printf("%c",223);
     }
     for (aux=-1; aux < 22; aux++)
     {
       gotoxy(29+aux,21);
       printf("%c",223);
     }
}
// Subprograma x
//     Objetivo  : Fazer uma moldura média.
//     Parâmetro : Cor da moldura.
//     Retorno   : Nenhum.
void fazMolduraCadastros(int cor)
{
     textcolor(cor); 
     int aux=0;
     for (aux=0; aux < 17; aux++)
     {
       gotoxy(15,aux+6);
       printf("%c",219);
     }
     for (aux=0; aux < 17; aux++)
     {
       gotoxy(65,aux+6);
       printf("%c",219);
     }
     for (aux=0; aux < 49; aux++)
     {
       gotoxy(16+aux,6);
       printf("%c",223);
     }
     for (aux=-2; aux < 49; aux++)
     {
       gotoxy(17+aux,23);
       printf("%c",223);
     }
     textcolor(10);
}
// Subprograma x
//     Objetivo  : Fazer uma Moldura em volta das opções do menu principal.
//     Parâmetro : Cordenadas e cor.
//     Retorno   : Nenhum.
void fazMolduraEscolha(int x,int y,int cor)
{
     int aux=0;
     textcolor(cor);
     gotoxy(x,y);
     printf("%c",201);
     for (aux=0; aux < 17; aux++)
     {
         printf("%c",205);
     }
     printf("%c",187);
     gotoxy(x,y+1);
     printf("%c",186);
     gotoxy(x+18,y+1);
     printf("%c",186);
     gotoxy(x,y+2);
     printf("%c",200);
     for (aux=0; aux < 17; aux++)
     {
         printf("%c",205);
     }
     printf("%c",188);
}
// Subprograma x
//     Objetivo  : Apresentar o sub-menu dos frequentadores.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraMenuFrequentadores()
{
     textcolor(LIGHTGRAY);
     gotoxy(52,9);
     printf("INCLUIR NOVO FREQUENTADOR");
     gotoxy(52,10);
     printf("ALTERAR DADOS");
     gotoxy(52,11);
     printf("DELETAR FREQUENTADORES");
}
// Subprograma x
//     Objetivo  : Apresentar o sub-menu de Séries.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraMenuSeries()
{
     textcolor(LIGHTGRAY);
     gotoxy(52,11);
     printf("INCLUIR NOVA SERIE");
     gotoxy(52,12);
     printf("ALTERAR DADOS");
     gotoxy(52,13);
     printf("DELETAR SERIES");
}
// Subprograma x
//     Objetivo  : Mostrar o sub-menu de atividades.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraMenuAtividades()
{
     textcolor(LIGHTGRAY);
     gotoxy(52,13);
     printf("INCLUIR NOVA ATIVIDADE");
     gotoxy(52,14);
     printf("EXCLUIR ATIVIDADE\n\n");
}
// Subprograma x
//     Objetivo  : Mostrar o sub-menu de relatórios.
//     Parâmetro : Nenhum.              
//     Retorno   : Nenhum.
void mostraMenuRelatorios()
{
     textcolor(LIGHTGRAY);
     gotoxy(52,15);
     printf("CONSULTAR TODOS OS DADOS");
     gotoxy(52,16);
     printf("PESQUISA POR NOME");
     gotoxy(52,17);
     printf("PESQUISA POR SERIE");
     gotoxy(52,18);
     printf("RESUMO POR DATA");
     gotoxy(52,19);
     printf("FREQUENTADORES POR DATA");
     gotoxy(52,20);
     printf("CLIENTES AUSENTES");
}
// Subprograma x
//     Objetivo  : Apresentar as molduras dos submenus em suas respectivas cordenadas.
//     Parâmetro : Opção e escolha feita.
//     Retorno   : Escolha feita.
int leValidaMenu(char opcao, int escolha)//MUDAR NOMEX
{
     // protótipos
     void mostraMenuFrequentadores();
     void mostraMenuSeries();
     void mostraMenuAtividades();
     void mostraMenuRelatorios();
     // Declarações
     int aux=1;
     // Instruções
     do
     {
                        switch(escolha) 
                        {
                               case 1:
                               {
                                     gotoxy(51,8+aux);
                                     textcolor(42);
                                     printf("%c",254);
                                     fazMolduraEscolha(30,9,2);
                                     mostraMenuFrequentadores();
                                     break;
                               }
                               case 2:
                               {
                                     gotoxy(51,10+aux);
                                     textcolor(42);
                                     printf("%c",254);
                                     fazMolduraEscolha(30,11,2);
                                     mostraMenuSeries();
                                     break;
                               }
                               case 3:
                               {
                                     gotoxy(51,12+aux);
                                     textcolor(42);
                                     printf("%c",254);
                                     fazMolduraEscolha(30,13,2);
                                     mostraMenuAtividades();
                                     break;
                               }
                               case 4:
                               {
                                     gotoxy(51,14+aux);
                                     textcolor(42);
                                     printf("%c",254);     
                                     fazMolduraEscolha(30,15,2);
                                     mostraMenuRelatorios();
                                     break;
                               }
                        }
                        mostraMenu();
                        mostraVoltarAoMenu();
                        gotoxy(38,20);
                        opcao = getch();
                        if (opcao == 27)
                        {
                                  return opcao;
                        }
                        if (opcao == 13)
                        {
                           return aux;
                        }
                        if ((escolha != 3) && (escolha != 4))
                        {
                           clrscr();
                           aux = quantidadeSetasMenu(opcao,3,aux);
                          
                        }
                        if (escolha == 3)
                        {
                           clrscr();
                           aux = quantidadeSetasMenu(opcao,2,aux);         
                        }
                        if (escolha == 4)
                        {
                           clrscr();
                           aux = quantidadeSetasMenu(opcao,6,aux);         
                        }
     }while(opcao != 27);
     return aux;
}
// Subprograma x
//     Objetivo  : Aumentar o contador(escolha do usuario) de acordo com as setas do teclado VERTICALMENTE.
//     Parâmetro : Opção digitada, maximo de opções e auxiliar.
//     Retorno   : Auxiliar válido.
int quantidadeSetasMenu(char opcao, int maximo, int aux) 
{
                           if (opcao == 72)
                           {
                              if (aux > 1)
                                   aux--;
                              else
                                  aux = maximo;
                           }
                           if (opcao == 80)
                           {
                              if (aux < maximo)
                                    aux++;
                              else
                                  aux = 1;
                           }
                           return aux;
}
// Subprograma x
//     Objetivo  : Aumentar o contador(escolha do usuario) de acordo com as setas do teclado HORIZONTALMENTE.
//     Parâmetro : Opção digitada, maximo de opções e auxiliar.
//     Retorno   : Auxiliar válido.
int quantidadeSetasMenuHorizontal(char opcao, int maximo, int aux) 
{
                          // clrscr();
                           if (opcao == 75)
                           {
                              if (aux > 1)
                                   aux--;
                              else
                                  aux = maximo;
                           }
                           if (opcao == 77)
                           {
                              if (aux < maximo)
                                    aux++;
                              else
                                  aux = 1;
                           }
                           return aux;
}
// Subprograma x
//     Objetivo  : Mostrar a mensagem de voltar ao menu com molduras.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraVoltarAoMenu()
{
     gotoxy(23,24);
     textcolor(YELLOW);
     printf("para voltar ao menu pressione ESC%c",179);
     gotoxy(52,24);
     printf("%c",179);
     gotoxy(56,23);
     printf("%c",191);
     gotoxy(53,23);
     printf("%c%c%c",196,196,196);
     gotoxy(53,25);
     printf("%c%c%c",196,196,196);
     gotoxy(52,23);
     printf("%c",218);
     gotoxy(52,25);
     printf("%c",192);
     gotoxy(56,25);
     printf("%c",217);
}    
// Subprograma x
//     Objetivo  : Apresentar uma moldura do tamanho maximo de nomes.
//     Parâmetro : Cor.
//     Retorno   : Nenhum.
void molduraNomes(int cor)
{
     int aux=0;
     textcolor(cor);
     gotoxy(26,16);
     for (aux=0;aux<30;aux++)
     {
         printf("%c",196);
     }
     gotoxy(26,18);
     for (aux=0;aux<30;aux++)
     {
         printf("%c",196);
     }
     gotoxy(56,16);
     printf("%c",191); // superior direito
     gotoxy(56,18);
     printf("%c",217); // inferior direito
     gotoxy(26,16);
     printf("%c",218); // superior esquerdo
     gotoxy(26,18);
     printf("%c",192); // inferior esquerdo
     gotoxy(56,17); 
     printf("%c",179);// vertical direito
     gotoxy(26,17); 
     printf("%c",179);// vertical direito
     textcolor(WHITE);  
}            
// Subprograma x
//     Objetivo  : Criar uma moldura para descrições.
//     Parâmetro : Nenhum.  
//     Retorno   : Nenhum.
void molduraDescricao() 
{
     int aux=0;
     textcolor(WHITE);
     gotoxy(17,16);
     for (aux=0;aux<47;aux++)
     {
         printf("%c",196);
     }
     gotoxy(17,18);
     for (aux=0;aux<47;aux++)
     {
         printf("%c",196);
     }
     gotoxy(64,16);
     printf("%c",191); // superior direito
     gotoxy(64,18);
     printf("%c",217); // inferior direito
     gotoxy(16,16);
     printf("%c",218); // superior esquerdo
     gotoxy(16,18);
     printf("%c",192); // inferior esquerdo
     gotoxy(64,17); 
     printf("%c",179);// vertical direito
     gotoxy(16,17); 
     printf("%c",179);// vertical direito 
}    
// Subprograma x
//     Objetivo  : Criar uma moldura especifica para números.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void molduraNumeros() 
{
     int aux=0;
     textcolor(WHITE);
     gotoxy(38,16);
     for (aux=0;aux<5;aux++)
     {
         printf("%c",196);
     }
     gotoxy(38,18);
     for (aux=0;aux<5;aux++)
     {
         printf("%c",196);
     }
     gotoxy(43,16);
     printf("%c",191); // superior direito
     gotoxy(43,18);
     printf("%c",217); // inferior direito
     gotoxy(37,16);
     printf("%c",218); // superior esquerdo
     gotoxy(37,18);
     printf("%c",192); // inferior esquerdo
     gotoxy(43,17); 
     printf("%c",179);// vertical direito
     gotoxy(37,17); 
     printf("%c",179);// vertical direito   
}        
// Subprograma x
//     Objetivo  : Apresentar a mensagem de digitar a serie
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void digiteAserie()//APAGARX
{
     textcolor(WHITE);                                                                
     gotoxy(21,12);
     printf("DIGITE O NOME DA SERIE A SER CADASTRADA:");
     gotoxy(35,15);
}
// Subprograma x
//     Objetivo  : Apresentar a mensagem de digitar a descrição.
//     Parâmetro : Nome da série.
//     Retorno   : Nenhum.
void digiteAdescricao(char *nome)
{
     textcolor(WHITE);
     gotoxy(24,10);
     printf("AGORA DIGITE A DESCRICAO DA SERIE");
     gotoxy(24,12);
     printf("DE");
     gotoxy(27,12);
     textcolor(10);
     printf("%s",nome);
}
// Subprograma x
//     Objetivo  : Apresentar a mensagem de digitar os minutos.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void digiteOsMinutos()
{
     textcolor(WHITE);
     gotoxy(24,10);
     printf("DIGITE A DURACAO DA SERIE EM MINUTOS:");
     gotoxy(27,12);
     textcolor(10);
}
// Subprograma x
//     Objetivo  : Apresentar a mensagem de digitar as calorias.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void digiteAsCalorias()
{
     textcolor(WHITE);
     gotoxy(19,10);
     printf("DIGITE A QUANTIDADE DE CALORIAS A SER GASTA:");
     textcolor(10);
}
// Subprograma x
//     Objetivo  : Apresentar a mensagem "para sair pressione ESQ".
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void paraSairDigiteSair()// MUDAR NOMEX
{
     textcolor(WHITE);
     gotoxy(25,8);
     printf("para voltar ao menu pressione");
     textcolor(10);
     printf(" ESC");
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Colocar caracteres em uma cordenada qualquer.
//     Parâmetro : cordenadas, tamanho do conjunto e caractere.
//     Retorno   : Nenhum.
void limpaTelaCordenada(int x, int y, int tamanho,char parametro)
{
     int aux=0;
     gotoxy(x,y);
     for (aux=0;aux<=tamanho;aux++)
     {
         printf("%c",parametro);
     }
}
// Subprograma x
//     Objetivo  : Limpar a tela com um efeito horizontal.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void limpaTelaEfeito()
{
     int aux=0, cont=14;
     for (aux=14;aux>0;aux--)
     {
         limpaTelaCordenada(1,aux,79,' ');
         if (aux > 2)
            limpaTelaCordenada(1,cont,79,' ');
         cont++;
         sleep(25);
     }
}       
// Subprograma x
//     Objetivo  : Apresentar o codigo gerado.
//     Parâmetro : Contador de series.
//     Retorno   : Nenhum.
void mostraCodigoGerado(int contador)
{
      int aux=0;
      textcolor(287);
      for (aux=0;aux<11;aux++)
      {
          gotoxy(20,10+aux);                                             
          printf("                                          ");
          sleep(15);
      }
      gotoxy(30,15);
      printf("CODIGO DA SERIE : %d",contador+1000);
      gotoxy(21,20);
      printf("Digite qualquer coisa p/ voltar ao menu!");
      textcolor(WHITE);    
}
// Subprograma x
//     Objetivo  : Verificar se uma certa atividade ja foi feita na data atual.
//     Parâmetro : Endereço da estrutura de atividades e do arquivo de atividades.
//     Retorno   : Valor lógico da exclusão.
int verificaSeFezAtividadeHoje (struct dadosAtividades *atividades, FILE *arq)
{
    char cpfComparar[TAM_NOME];
    int diaComparar,mesComparar,anoComparar,codigoComparar;
    long tamanhoArquivo,contBytes=0;
    tamanhoArquivo = obtemTamanhoArquivo(arq,"Atividades.txt");
    tipoAtividade estrutura; 
    arq=abreArquivo("Atividades.txt","rb","\nErro ao abrir arquivo de Atividades");
    while(contBytes < tamanhoArquivo)
    {
       //fread(cpfComparar,sizeof(char)*TAM_NOME,1,arq);
       //fread(&codigoComparar,sizeof(int),1,arq);
       fread(&estrutura,sizeof(tipoAtividade),1,arq);
      // if ((strcmp(atividades->cpf,cpfComparar) == 0) && (codigoComparar == atividades->codigo))
       if ((strcmp(atividades->cpf,estrutura.cpf) == 0) && (estrutura.codigo == atividades->codigo))
       {
            //fread(&diaComparar,sizeof(int),1,arq);
            //fread(&mesComparar,sizeof(int),1,arq);
            //fread(&anoComparar,sizeof(int),1,arq);
            //if (((diaComparar == atividades->dia) && (mesComparar == atividades->mes) && (anoComparar == atividades->ano)))
            if (((estrutura.dia == atividades->dia) && (estrutura.mes == atividades->mes) && (estrutura.ano == atividades->ano)))
            {
                  fclose(arq);
                  return 1;
            }
           // fseek(arq,-12,1);
       }
      // fseek(arq,21,1);
       contBytes = ftell(arq);
    }
    fclose(arq);
    return 0;
}
// Subprograma x
//     Objetivo  : Apresentar uma mensagem de cadastro concluido.
//     Parâmetro : Cor.
//     Retorno   : Nenhum.
void cadastroConcluido(int cor)
{
      int aux=0;
      textcolor(cor);
      for (aux=0;aux<11;aux++)
      {
          gotoxy(23,10+aux);
          printf("                                  ");
          sleep(15);
      }
      gotoxy(24,15);
      printf("CADASTRO CONCLUIDO COM SUCESSO!\n\n\n\n");
      textcolor(WHITE);
      getch();      
}
// Subprograma x
//     Objetivo  : Limpar a tela com um efeito VERTICAL.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void limpaTelaEfeitoVertical()
{
     int aux=0, cont=41;
     for (aux=40;aux>0;aux--)
     {
         limpaTelaCordenadaVertical(aux,25,25,' ');
         if (aux > 0)
            limpaTelaCordenadaVertical(cont,25,25,' ');
         cont++;
         sleep(7); 
     }
}    
// Subprograma x
//     Objetivo  : Insetir caracteres em qualquer lugar da tela verticalmente.
//     Parâmetro : Cordenadas, tamanho do conjunto e caractere a ser inserido.
//     Retorno   : Nenhum.
void limpaTelaCordenadaVertical(int x, int y, int tamanho,char parametro)
{
     int aux=0;
     gotoxy(x,y);
     for (aux=0;aux<=tamanho;aux++)
     {
         gotoxy(x,y-aux);
         printf("%c",parametro);
     }   
}   
// Subprograma x
//     Objetivo  : Apresentar uma mensagem de digite F11
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void mostraDigiteF11()
{
     int aux=0;
     textcolor(244);
     for (aux=0;aux<2;aux++)
     {
          gotoxy(15,24+aux);
          printf("                                                   ");
     }
     gotoxy(18,25);
     textcolor(244);
     printf(" PARA ENTRAR COM OUTRA INFORMACAO DIGITE F11 ");
     textcolor(WHITE);
}   
// Subprograma x
//     Objetivo  : Mostrar as opções de alteração de atividades.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
char mostraMenuF11Atividades()
{
     int contador=1;
     int aux=0,coluna=25;
     char opcao;
     criaMiniTelaAzul(287);
     fazMolduraF11();
     textcolor(287);
     do
     {
        gotoxy(32,10);
        textcolor(287);
        printf("INFORME O:");
        gotoxy(coluna,13);
        if (contador == 1)
          textcolor(240);
        else
            textcolor(287);
        printf("      CODIGO DA SERIE         ");
        gotoxy(coluna,15);
        if (contador == 2)
           textcolor(240);
        else
            textcolor(287);
        printf("      DIA DA REALIZACAO       ");
        gotoxy(coluna,17);
        if (contador == 3)
           textcolor(240);
        else
            textcolor(287);
        printf("      MES DA REALIZACAO       ");
        gotoxy(coluna,19);
        if (contador == 4)
           textcolor(240);
        else
            textcolor(287);
        printf("      ANO DA REALIZACAO       ");
        textcolor(WHITE);
        opcao = getch();
        contador = quantidadeSetasMenu(opcao,4,contador);
     }while((opcao != 27) && (opcao != 13));
     if (opcao == 27)
         return opcao;
     switch(contador)
     {
                     case 1:
                     {
                          return '1';
                          break;
                     }
                     case 2:
                     {
                          return '2';
                          break;
                     }
                     case 3:
                     {
                          return '3';
                          break;
                     }
                     case 4:
                     {
                          return '4';
                          break;
                     }
     }
}
// Subprograma x
//     Objetivo  : Criar uma tela pequena de qualquer cor no centro da tela.
//     Parâmetro : Cor.
//     Retorno   : Nenhum.
void criaMiniTelaAzul(int cor) // MUDAR NOMEX
{
     int aux=0;
     textcolor(cor);
     for (aux=0;aux<11;aux++)
     {
          gotoxy(23,10+aux);
          printf("                                  ");
          sleep(15);
     }
}
// Subprograma x
//     Objetivo  : Apresentar as opções de alteração de series.
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
char mostraMenuF11() // MUDAR NOMEX        = mostraMenuF11Series
{
     int contador=1;
     int aux=0,coluna=25;
     char opcao;
     criaMiniTelaAzul(287);
     fazMolduraF11();
     textcolor(287);
     do
     {
        gotoxy(32,10);
        textcolor(287);
        printf("INFORME PARTE DO:");
        gotoxy(coluna,13);
        if (contador == 1)
          textcolor(240);
        else
            textcolor(287);
        printf("      NOME DA SERIE           ");
        gotoxy(coluna,15);
        if (contador == 2)
           textcolor(240);
        else
            textcolor(287);
        printf("      TEMPO EM MINUTOS        ");
        gotoxy(coluna,17);
        if (contador == 3)
           textcolor(240);
        else
            textcolor(287);
        printf("      QUANTIDADE DE CALORIAS  ");
        gotoxy(coluna,19);
        if (contador == 4)
           textcolor(240);
        else
            textcolor(287);
        printf("      DESCRICAO DA SERIE      ");
        textcolor(WHITE);
        opcao = getch();
        contador = quantidadeSetasMenu(opcao,4,contador);
     }while((opcao != 27) && (opcao != 13));
     if (opcao == 27)
         return opcao;
     switch(contador)
     {
                     case 1:
                     {
                          return '1';
                          break;
                     }
                     case 2:
                     {
                          return '2';
                          break;
                     }
                     case 3:
                     {
                          return '3';
                          break;
                     }
                     case 4:
                     {
                          return '4';
                          break;
                     }
     }
}
// Subprograma x
//     Objetivo  : Chamar as funções necessarias para a alteração de series e atividades por diversos parametros.
//     Parâmetro : Opção, qual função a ser chamada, Ponteiro do arquivo de atividades e de series e o modo (ALTERAR OU DELETAR)
//     Retorno   : Nenhum.
void chamaFuncoesAlterar(char opcao,int qualFuncao,FILE *arq,FILE *arqAtividaes,char modo)//MUDAR NOMEX
{
     //Declarações
     char nomeSerie[MAX_NOME], descricaoSerie[MAX_FRASE]; 
     int duracaoSerie;
     float caloriaSerie;
     //Instruções:
     if (qualFuncao == 1)
     {
       switch(opcao)
       {
          case 27:
          {
            limpaTelaEfeitoVertical();
            break;
          }
          case '1': // Alterar/Deletar Serie por nome...
          {
            limpaTelaCordenada(15,24,50,' ');
            limpaTelaCordenada(15,25,50,' ');
            criaGrandeTelaAzul(15);
            textcolor(15);
            gotoxy(23,10);
            printf("DIGITE O NOME DA SERIE OU PARTE DELE");
            paraSairDigiteSair();
            molduraNomes(15);
            textcolor(287);
            leCharPorChar(nomeSerie,MAX_NOME);
            limpaTelaEfeito();
            if (nomeSerie[0] == 27)
            {
                    operacaoCancelada();
                    return;
            }
           // verificaNomeSerieSemelhante(nomeSerie,arq,modo,arqAtividaes);
            textcolor(WHITE);
            break;
          }
          case '2': // por duração...
          {
            limpaTelaCordenada(15,24,50,' ');
            limpaTelaCordenada(15,25,50,' ');   
            criaGrandeTelaAzul(15);
            gotoxy(28,10);
            printf("DIGITE A DURACAO DA SERIE");
            duracaoSerie = leValidaNumeros(0,120,4);
            limpaTelaEfeito();
            if (duracaoSerie == -1)
            {
                    operacaoCancelada();
                    return;
            }
           // verificaDuracaoSerieSemelhante(duracaoSerie,arq,modo,arqAtividaes);
            textcolor(WHITE);
            break;
          }
          case '3': // Por Calorias...
          {
            limpaTelaCordenada(15,24,50,' ');
            limpaTelaCordenada(15,25,50,' ');   
            criaGrandeTelaAzul(15);
            gotoxy(28,10);
            printf("DIGITE AS CALORIAS DA SERIE");
            caloriaSerie = leValidaNumeros(0,400,4);
            limpaTelaEfeito();
            if (caloriaSerie == -1)
            {
                    operacaoCancelada();
                    return;
            }
           // verificaCaloriaSerieSemelhante(caloriaSerie,arq,modo,arqAtividaes);
            textcolor(WHITE);
            break;
          }
          case '4': // Por Descrição...
          {
            limpaTelaCordenada(15,24,50,' ');
            limpaTelaCordenada(15,25,50,' ');
            criaGrandeTelaAzul(15);
            textcolor(15);
            gotoxy(23,10);
            printf("DIGITE A DESCRICAO OU PARTE DELA");
            paraSairDigiteSair();
            molduraNomes(15);
            textcolor(287);
            leCharPorChar(descricaoSerie,MAX_FRASE);
            limpaTelaEfeito();
            if (descricaoSerie[0] == 27)
            {
                    operacaoCancelada();
                    return;
            }
            verificaDescricaoSerieSemelhante(descricaoSerie,arq,modo,arqAtividaes);
            textcolor(WHITE);
            break;
          }
       }
     }
     else
     {
       switch(opcao)
       {
          case 27:
          {
            limpaTelaEfeitoVertical();
            break;
          }
          case '1':
          {
            clrscr();
            printf("opcao 1 ATIVIDADES sucesso!\n");
            getch();
            break;
          }
          case '2':
          {
            clrscr();
            printf("opcao 2 ATIVIDADES sucesso!\n");
            getch();
            break;
          }
          case '3':
          {
            clrscr();
            printf("opcao 3 ATIVIDADES sucesso!\n");
            getch();
            break;
          }
          case '4':
          {
             clrscr();
             printf("opcao 4 ATIVIDADES sucesso!\n");
             getch();
             break;
          }
       }
     }
     return;
}
// Subprograma x
//     Objetivo  : Criar uma moldura com efeito em volta do menu F11
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void fazMolduraF11() 
{
     textcolor(WHITE);
     int aux=0;
     for (aux=0; aux < 11; aux++) // 15 = vertical
     {
       gotoxy(22,aux+10);
       printf("%c",219);
       sleep(1);
     }
     for (aux=0; aux < 11; aux++)    // vertical
     {
       gotoxy(57,aux+10);
       printf("%c",219);
       sleep(1);
     }
     for (aux=0; aux < 36; aux++)  // horizontal
     {
       gotoxy(22+aux,9);
       printf("%c",220);
       sleep(1);
     }
     for (aux=0; aux < 36; aux++) // horizontal
     {
       gotoxy(22+aux,21);
       printf("%c",223);
       sleep(1);
     }
}
// Subprograma x
//     Objetivo  : Criar uma tela grande de qualquer cor no centro da tela.
//     Parâmetro : Cor.
//     Retorno   : Nenhum.
void criaGrandeTelaAzul(int cor)
{
     int aux=0;
     textcolor(cor);
     for (aux=0;aux<16;aux++)
     {
          gotoxy(16,7+aux);
          printf("                                                 ");
          sleep(15);
     }
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Achar o endereço de uma serie atravez de sua descrição.
//     Parâmetro : Descrição digitada, escolha feita e ponteiro de arquivo.
//     Retorno   : Endereço da estrutura seguinte.
long enderecoPesquisaSerieDescricao(char *pDescricaoDigitada, int escolha,FILE *arq)
{
     int tamanhoArquivo,contBytes=0,contador=0;
     char nomeComparar[MAX_FRASE];
     char nomeCompararMaiusculo[MAX_FRASE];
     long achou;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     capsLock(pDescricaoDigitada);
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fseek(arq,MAX_NOME+sizeof(int)+sizeof(int)+sizeof(float),1);
             fread(nomeComparar,MAX_FRASE,1,arq);
             strcpy(nomeCompararMaiusculo,nomeComparar);
             capsLock(nomeComparar);
             if (strstr(nomeComparar,pDescricaoDigitada))
             {
                   contador++;
                   if (contador == escolha)
                   {
                          achou = ftell(arq);
                          fclose(arq);
                          return achou;
                   }
             } 
             contBytes = ftell(arq);
     }
     fclose(arq);
}
// Subprograma x
//     Objetivo  : Encontrar series com descrição semelhante e chamar a função de fazer a listagem delas.
//     Parâmetro : Descrição digitada, endereço do arquivo de Series, modo(ALTERAR OU DELETAR) e endereço do arquivo de atividades.
//     Retorno   : Nenhum.
void verificaDescricaoSerieSemelhante(char *pDescricaoDigitada, FILE *arq,char modo,FILE *arqAtividades)
{
     //Protótipos:
     long enderecoPesquisaSerieDescricao(char *pDescricaoDigitada, int escolha,FILE *arq);
     //Declarações:
     int contador=0,contBytes=0,tamanhoArquivo=0,codigo,duracao,escolha,flag=0;
     float calorias;
     char nomeComparar[MAX_FRASE],fraseComparar[MAX_FRASE];
     char nomeCompararMaiusculo[MAX_FRASE],nome[MAX_NOME];
     long enderecoAlterar;
     tipoSerie estrutura;
     //Instruções:
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     capsLock(pDescricaoDigitada);
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
            // fseek(arq,MAX_NOME+sizeof(int)+sizeof(int)+sizeof(float),1);
            // fread(nomeComparar,MAX_FRASE,1,arq);
             fread(&estrutura,sizeof(tipoSerie),1,arq);
            // strcpy(nomeCompararMaiusculo,nomeComparar);
            // strcpy(nomeCompararMaiusculo,estrutura.nomeSerie);
            // capsLock(nomeCompararMaiusculo);
             capsLock(estrutura.nomeSerie);
           //  if (strstr(nomeCompararMaiusculo,pDescricaoDigitada))
             if (strstr(estrutura.nomeSerie,pDescricaoDigitada))
             {
                   //fseek(arq,-1*(MAX_FRASE+sizeof(float)+sizeof(int)+sizeof(int)+MAX_NOME),1);
                   //fread(&nome,sizeof(char)*MAX_NOME,1,arq);
                   //fread(&codigo,sizeof(int),1,arq);
                   //fread(&duracao,sizeof(int),1,arq);
                   //fread(&calorias,sizeof(float),1,arq);
                   //fread(fraseComparar,MAX_FRASE,1,arq);
                  // fazListagemSeries(nome,codigo,duracao,calorias,fraseComparar,contador);
                   fazListagemSeries(&estrutura,contador);
                   contador++;
             }
            // else
            // {
            //        fseek(arq,0,1);
            // }
             contBytes = ftell(arq);
     }
     if (contador == 0)
     {
                  nenhumDadoEncontrado();
                  getch();
                  fclose(arq);
                  return;
     }
     escolha = pedeNumeroSerieAlterar(contador);
     apontaParaEscolhaLista(escolha);
     enderecoAlterar = enderecoPesquisaSerieDescricao(pDescricaoDigitada,escolha,arq);
     rewind(arq);
     fseek(arq,enderecoAlterar,1);
     fseek(arq,-1*(MAX_FRASE + sizeof(float) + sizeof(int) + sizeof(int)),1);
     fread(&codigo,sizeof(int),1,arq);
     fclose(arq); 
     if (escolha != -1)
     {
        if (modo == 'A')
           leValidaMenuAlterarSeries(' ',codigo,arq);
        else
        {
              flag = verificaSeFezAtividade(codigo,arqAtividades,67);
              if (!flag)
              {
                        flag = deletarRegistro(arq,enderecoAlterar,256);
              }
              else
              {
                  mostraImpossivelDeletar();
              }
        }
             
     }
     else
         operacaoCancelada();
}
// Subprograma x
//     Objetivo  : Verificar se existem nomes de séries semelhates, e caso existir chamar a função para fazer a listagem delas.
//     Parâmetro : Nome digitado, endereço do arquivo de series, modo(ALTERAR OU DELETAR) e endereo do arquivo de atividades.
//     Retorno   : Nenhum.
/*void verificaNomeSerieSemelhante(char *pNomeDigitado, FILE *arq,char modo,FILE *arqAtividades)
{
     //Protótipos:
     long enderecoPesquisaSerieNome(char *pNomeDigitado, int escolha,FILE *arq);
     //Declarações:
     int contador=0,codigo,duracao,escolha,flag=0;
     float calorias;
     char nomeComparar[MAX_NOME],fraseComparar[MAX_FRASE];
     char nomeCompararMaiusculo[MAX_NOME];
     long enderecoAlterar,tamanhoArquivo,contBytes=0;
     tipoSerie estrutura;
     //Instruções:
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     capsLock(pNomeDigitado);
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fread(nomeComparar,MAX_NOME,1,arq);
             strcpy(nomeCompararMaiusculo,nomeComparar);
             capsLock(nomeCompararMaiusculo);
             if (strstr(nomeCompararMaiusculo,pNomeDigitado))
             {
                   //fread(&codigo,sizeof(int),1,arq);
                   //fread(&duracao,sizeof(int),1,arq);
                   //fread(&calorias,sizeof(float),1,arq);
                   //fread(fraseComparar,MAX_FRASE,1,arq);
                   fazListagemSeries(nomeComparar,codigo,duracao,calorias,fraseComparar,contador);
                   contador++;
             }
             else
             {
                    fseek(arq,sizeof(int)+sizeof(int)+sizeof(float)+MAX_FRASE,1);
             }
             contBytes = ftell(arq);
     }
     if (contador == 0)
     {
                  nenhumDadoEncontrado();
                  getch();
                  fclose(arq);
                  return;
     }
     escolha = pedeNumeroSerieAlterar(contador);
     apontaParaEscolhaLista(escolha);
     enderecoAlterar = enderecoPesquisaSerieNome(pNomeDigitado,escolha,arq); 
     rewind(arq);
     fseek(arq,enderecoAlterar,1);
     fseek(arq,-1*(MAX_FRASE+12),1);
     fread(&codigo,sizeof(int),1,arq);
     fclose(arq); 
     if (escolha != -1)
     {
        if (modo == 'A')
           leValidaMenuAlterarSeries(' ',codigo,arq);
        else
        {
              flag = verificaSeFezAtividade(codigo,arqAtividades,67);
              if (!flag)
              {
                        flag = deletarRegistro(arq,enderecoAlterar,256);
              }
              else
              {
                  mostraImpossivelDeletar();
              }
        }      
     }
     else
         operacaoCancelada();
}*/
// Subprograma x
//     Objetivo  : Verificar se existem durações de séries semelhates, e caso existir chamar a função para fazer a listagem delas.
//     Parâmetro : duração digitada, endereço do arquivo de series, modo(ALTERAR OU DELETAR) e endereo do arquivo de atividades.
//     Retorno   : Nenhum.
/*void verificaDuracaoSerieSemelhante(int duracaoSerie, FILE *arq,char modo,FILE *arqAtividades)
{
     long enderecoPesquisaSerieDuracao(int duracaoDigitada, int escolha, FILE *arq);
     int contador=0,codigo,duracaoComparar,escolha,flag;
     float calorias;
     char nomeComparar[MAX_NOME],fraseComparar[MAX_FRASE];
     long enderecoAlterar,contBytes=0,tamanhoArquivo;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fseek(arq,(sizeof(char)*MAX_NOME)+sizeof(int),1);
             fread(&duracaoComparar,sizeof(int),1,arq);
             if (duracaoSerie == duracaoComparar)
             {
                   fseek(arq,(sizeof(int)+MAX_NOME+sizeof(int))*-1,1);
                   fread(nomeComparar,MAX_NOME,1,arq);
                   fread(&codigo,sizeof(int),1,arq);
                   fseek(arq,sizeof(int),1);
                   fread(&calorias,sizeof(float),1,arq);
                   fread(fraseComparar,MAX_FRASE,1,arq);
                   fazListagemSeries(nomeComparar,codigo,duracaoComparar,calorias,fraseComparar,contador);
                   contador++;
             }
             else
             {
                    fseek(arq,sizeof(float)+MAX_FRASE,1);
             }
             contBytes = ftell(arq);
     }
     if (contador == 0)
     {
                  nenhumDadoEncontrado();
                  getch();
                  fclose(arq);
                  return;
     }
     escolha = pedeNumeroSerieAlterar(contador);
     apontaParaEscolhaLista(escolha);
     enderecoAlterar = enderecoPesquisaSerieDuracao(duracaoSerie,escolha,arq); 
     rewind(arq);
     fseek(arq,enderecoAlterar,1);
     fseek(arq,-1*(MAX_FRASE+12),1);
     fread(&codigo,sizeof(int),1,arq);
     fclose(arq); 
     if (escolha != -1)
     {
        if (modo == 'A')
           leValidaMenuAlterarSeries(' ',codigo,arq);
        else
        {
              flag = verificaSeFezAtividade(codigo,arqAtividades,67);
              if (!flag)
              {
                        flag = deletarRegistro(arq,enderecoAlterar,256);
              }
              else
              {
                  mostraImpossivelDeletar();
              }
        }
     }
     else
         operacaoCancelada();
}*/
// Subprograma x
//     Objetivo  : Verificar se existem Calorias de séries semelhates, e caso existir chamar a função para fazer a listagem delas.
//     Parâmetro : Caloria digitada, endereço do arquivo de series, modo(ALTERAR OU DELETAR) e endereo do arquivo de atividades.
//     Retorno   : Nenhum.
/*void verificaCaloriaSerieSemelhante(float caloriaDigitada, FILE *arq,char modo,FILE *arqAtividades)
{
     long enderecoPesquisaSerieCaloria(float caloriaDigitada, int escolha, FILE *arq);
     int contador=0,codigo,escolha,duracao,flag=0;
     float caloriaComparar;
     char nomeComparar[MAX_NOME],fraseComparar[MAX_FRASE];
     long enderecoAlterar,contBytes=0,tamanhoArquivo;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fseek(arq,(sizeof(char)*MAX_NOME)+sizeof(int)+sizeof(int),1);
             fread(&caloriaComparar,sizeof(float),1,arq);
             if (caloriaDigitada == caloriaComparar)
             {
                   fseek(arq,(sizeof(int)+MAX_NOME+sizeof(int)+sizeof(float))*-1,1);
                   fread(nomeComparar,MAX_NOME,1,arq);
                   fread(&codigo,sizeof(int),1,arq);
                   fread(&duracao,sizeof(int),1,arq);
                   fread(&caloriaComparar,sizeof(float),1,arq);
                   fread(fraseComparar,MAX_FRASE,1,arq);
                   fazListagemSeries(nomeComparar,codigo,duracao,caloriaComparar,fraseComparar,contador);
                   contador++;
             }
             else
             {
                    fseek(arq,MAX_FRASE,1);
             }
             contBytes = ftell(arq);
     }
     if (contador == 0)
     {
                  nenhumDadoEncontrado();
                  getch();
                  fclose(arq);
                  return;
     }
     escolha = pedeNumeroSerieAlterar(contador);
     apontaParaEscolhaLista(escolha);
     enderecoAlterar = enderecoPesquisaSerieCaloria(caloriaDigitada,escolha,arq); 
     rewind(arq);
     fseek(arq,enderecoAlterar,1);
     fseek(arq,-1*(MAX_FRASE+12),1);
     fread(&codigo,sizeof(int),1,arq);
     fclose(arq); 
     if (escolha != -1)
     {
        if (modo == 'A')
            leValidaMenuAlterarSeries(' ',codigo,arq);
        else
        {
              flag = verificaSeFezAtividade(codigo,arqAtividades,67);
              if (!flag)
              {
                        flag = deletarRegistro(arq,enderecoAlterar,256);
              }
              else
              {
                  mostraImpossivelDeletar();
              } 
        }
     }
     else
         operacaoCancelada();
}*/
// Subprograma x
//     Objetivo  : Encontrar o endereço de uma serie atravez de uma caloria.
//     Parâmetro : Caloria digitada, escolha e ponteiro do arquivo de Séries.
//     Retorno   : Endereço da estrutura de séries.
long enderecoPesquisaSerieCaloria(float caloriaDigitada, int escolha, FILE *arq)
{
     int contador=0;
     float caloriaComparar;
     long achou,contBytes=0,tamanhoArquivo;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fseek(arq,(sizeof(char)*MAX_NOME)+sizeof(int)+sizeof(int),1);
             fread(&caloriaComparar,sizeof(float),1,arq);
             if (caloriaDigitada == caloriaComparar)
             {
                   contador++;
                   if (contador == escolha)
                   {
                          fseek(arq,MAX_FRASE,1);
                          achou = ftell(arq);
                          fclose(arq);
                          return achou;
                   }
             } 
             fseek(arq,MAX_FRASE,1);
             contBytes = ftell(arq);
     }
     fclose(arq);
}
// Subprograma x
//     Objetivo  : Encontrar o endereço de uma serie atravez de uma Duração.
//     Parâmetro : Duração digitada, escolha e ponteiro do arquivo de Séries.
//     Retorno   : Endereço da estrutura de séries.
long enderecoPesquisaSerieDuracao(int duracaoDigitada, int escolha, FILE *arq)
{
     int contador=0;
     int duracaoComparar;
     long achou,tamanhoArquivo,contBytes=0;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fseek(arq,(sizeof(char)*MAX_NOME)+sizeof(int),1);
             fread(&duracaoComparar,sizeof(int),1,arq);
             if (duracaoDigitada == duracaoComparar)
             {
                   contador++;
                   if (contador == escolha)
                   {
                          fseek(arq,sizeof(float)+MAX_FRASE,1);
                          achou = ftell(arq);
                          fclose(arq);
                          return achou;
                   }
             } 
             fseek(arq,sizeof(float)+MAX_FRASE,1);
             contBytes = ftell(arq);
     }
     fclose(arq);
}
// Subprograma x
//     Objetivo  : Encontrar o endereço de uma serie atravez de um nome.
//     Parâmetro : nome digitado, escolha e ponteiro do arquivo de Séries.
//     Retorno   : Endereço da estrutura de séries.
long enderecoPesquisaSerieNome(char *pNomeDigitado, int escolha,FILE *arq)
{
     int contador=0;
     char nomeComparar[MAX_NOME];
     char nomeCompararMaiusculo[MAX_NOME];
     long achou,tamanhoArquivo,contBytes=0;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
     capsLock(pNomeDigitado);
     arq = abreArquivo("cadastroSeries.txt","rb","-Erro ao tentar abrir o arquivo de Series!");
     while(contBytes < tamanhoArquivo)
     {
             fread(nomeComparar,MAX_NOME,1,arq);
             strcpy(nomeCompararMaiusculo,nomeComparar);
             capsLock(nomeComparar);
             if (strstr(nomeComparar,pNomeDigitado))
             {
                   contador++;
                   if (contador == escolha)
                   {
                          fseek(arq,sizeof(int)+sizeof(int)+sizeof(float)+MAX_FRASE,1);
                          achou = ftell(arq);
                          fclose(arq);
                          return achou;
                   }
             } 
             fseek(arq,sizeof(int)+sizeof(int)+sizeof(float)+MAX_FRASE,1);
             contBytes = ftell(arq);
     }
     fclose(arq);
}
// Subprograma x
//     Objetivo  : Fazer uma lista dos dados de séries.
//     Parâmetro : Estrutura de séries.
//     Retorno   : Nenhum.
//void fazListagemSeries(char *pNome,int codigo,int duracao,float calorias,char *pFrase, int linha)
void fazListagemSeries(struct dadosSerie *pEstrutura,int linha)
{
     int aux=25;
     int opcao;
     textcolor(240);//128 48
     gotoxy(1,1);
     printf("    |        NOME DA SERIE:            |   CODIGO   |   DURACAO   |  CALORIAS   ");
     sleep(1);
     gotoxy(1,2);
     printf(" N  |                                  |            |  (minutos)  |             ");
     sleep(1);
     fazMolduraListagemSeries(linha);
     gotoxy(2,5+linha);
     textcolor(240);
     printf("%d",linha+1);
     sleep(1);
     gotoxy(6,5+linha);
     textcolor(31);
     //printf("%s",pNome);
     printf("%s",pEstrutura->nomeSerie);
     sleep(1);
     gotoxy(45,5+linha);
     textcolor(95);
    // printf("%d",codigo);  
     printf("%d",pEstrutura->codigo);
     sleep(1);
     gotoxy(60,5+linha);
     textcolor(47);
     //printf("%d",duracao);
     printf("%d",pEstrutura->duracao);
     sleep(1);
     gotoxy(71,5+linha);
     textcolor(79);
     //printf("%3.1f",calorias);
     printf("%3.1f",pEstrutura->calorias);
     sleep(1);
}
// Subprograma x
//     Objetivo  : Pedir qual número da lista o usurario deseja alterar.
//     Parâmetro : Contador de linhas.
//     Retorno   : Opção escolhida
int pedeNumeroSerieAlterar(int linha) //PAREIX
{
     int aux=0;
     int opcao;
     textcolor(240);
     for(aux=0;aux<3;aux++)
     {
         gotoxy(1,(linha+6)+aux);
         printf("                                                                                ");
         sleep(1);
     }
     gotoxy(21,linha+7);
     printf("DIGITE O NUMERO DA SERIE QUE DESEJA SELECIONAR!");
     sleep(1);
     gotoxy(36,linha+9);
     textcolor(270);
     printf("             ");
     sleep(1);
     gotoxy(39,linha+6);
     opcao = leValidaNumeroLista(0,linha,4);
     return opcao;
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
char leValidaNumeroLista(int min, int max,int maximo)
{
  int aux=0, contador=0, posicao=27;
  int valorAtoi=10000, apertouEnter=0; 
  char valor[maximo];
  //clrscr();
  textcolor(270);
  do
  {
     do
     {
       if (contador == maximo)
          contador = maximo-1;
       if (((valorAtoi <= min) || (valorAtoi > max) && (apertouEnter == 1)))
       {
              limpaTelaCordenada(41,max+9,4,' ');
              contador = 0;
              apertouEnter = 0;
              gotoxy(26,max+8);
              textcolor(240);
              printf("Valor invalido! informe novamente:");
              textcolor(270);
       }
       for (contador=contador;contador<maximo;contador++)
       {
         gotoxy(41+contador,max+9); 
         valor[contador] = getch();
         aux++;
         if (valor[contador] == 13)
         {
                 apertouEnter = 1;
                 valor[contador] = '\0';
                 break;
         } 
         if (valor[contador] == 27)
         {
                return -1;
         }
         if (valor[contador] == '\b')
         {
                 if (contador > 0)
                 {
                   valor[contador-1] = ' ';
                   contador = contador - 2;
                   gotoxy(41+contador+1,max+9);
                   printf(" ");
                 }else
                      contador = -1;
                      
         }else
               printf("%c",valor[contador]);
       }
       fflush(stdin);
       valorAtoi = atoi(valor);
       if (maximo == 4)
          limpaTelaCordenada(44,max+9,1,' ');
       else
           limpaTelaCordenada(42,max+9,0,' '); 
     }while((valorAtoi <= min) || (valorAtoi > max));
  }while((strlen(valor) >= maximo) || (valor[0] == '\0')); 
  limpaTelaCordenada(41,max+9,4,' ');
  return valorAtoi;
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void fazMolduraListagemSeries(int linha)
{
     gotoxy(1,5+linha);
     textcolor(240);
     printf("    ");
     gotoxy(5,5+linha);
     textcolor(31); 
     printf("                                   ");
     textcolor(95); 
     gotoxy(41,5+linha);
     printf("            ");
     textcolor(47); 
     gotoxy(54,5+linha);
     printf("             ");
     textcolor(79); 
     gotoxy(68,5+linha);
     printf("            "); 
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void nenhumDadoEncontrado()
{
     int aux=0;
     textcolor(79);
     for (aux=0;aux<11;aux++)
     {
          gotoxy(23,10+aux);
          printf("                                  ");
          sleep(15);
     }
     gotoxy(29,15);
     printf("NENHUM DADO ENCONTRADO!");
     gotoxy(27,19);
     printf("Pressione qualquer tecla...");
     textcolor(76);
     gotoxy(56,10);
     printf("X");
     fazMolduraF11();
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void mostraImpossivelDeletarClientes()
{
     char opcao;
     do
     {
          fazMolduraCadastros(49999);
          criaGrandeTelaAzul(256);
          escreveQualquerCoisa("NAO E POSSIVEL DELETAR POIS O CLIENTE",15,22,10);
          gotoxy(22,10);
          escreveQualquerCoisa("JA REALIZOU ATIVIDADES!",15,29,12);
          gotoxy(22,21);
          textcolor(YELLOW);
          printf("<Pressione ENTER para voltar ao menu>"); 
          opcao = getch();
     }while(opcao != 13);
     limpaTelaEfeito();
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void mostraImpossivelDeletar()
{
     char opcao;
     do
     {
          fazMolduraCadastros(49999);
          criaGrandeTelaAzul(256);
          gotoxy(22,10);
          textcolor(WHITE);
          printf("NAO E POSSIVEL DELETAR POIS AO MENOS");
          gotoxy(26,12);
          printf("1 CLIENTE JA FEZ ESTA SERIE!");
          gotoxy(22,21);
          textcolor(YELLOW);
          printf("<Pressione ENTER para voltar ao menu>"); 
          opcao = getch();
     }while(opcao != 13);
     limpaTelaEfeito();
}
// Subprograma x               
//     Objetivo  : Escrever qualquer coisa, em qualquer cor e em qualquer lugar da tela.
//     Parâmetro : Ponteiro da Frase, cor e cordenadas.
//     Retorno   : Nenhum.
void escreveQualquerCoisa(char *pFrase,int cor,int cordenadaX,int cordenadaY)
{
     textcolor(cor);
     gotoxy(cordenadaX,cordenadaY);
     printf("%s",pFrase);
     textcolor(WHITE);
}
// Subprograma x                
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
long obtemTamanhoArquivo(FILE *arq,char *pNomeArquivo)
{
      long tamanhoArquivo;
      arq = abreArquivo(pNomeArquivo,"rb","ERRO AO VERIFICAR TAMANHO DO ARQUIVO");
      fseek(arq,0,2);
      tamanhoArquivo = ftell(arq);
      fclose(arq);
      return tamanhoArquivo;
}
// Subprograma x                
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void mostraDadosFrequentador(char *pCpfDigitado, FILE *arq,char modo)
{
       long tamanhoArquivo, contBytes=0;
       char cpf[MAX_NOME],nome[MAX_NOME],sexo;
       int dia,mes,ano,contador=0;
       float peso;
       tipoFrequentador estrutura;
       tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroClientes.txt");
       arq = abreArquivo("cadastroClientes.txt","rb","ERRO AO TENTAR ABRIR O ARQUIVO DE CLIENTES!");
       while (contBytes < tamanhoArquivo)
      // while (!feof(arq))
       {
             //fread(cpf,sizeof(char)*MAX_NOME,1,arq);
             //fread(&estrutura,sizeof(tipoFrequentador),1,arq);
             if (modo == 'A')
             {
               fread(&estrutura,sizeof(tipoFrequentador),1,arq);
              // if (strcmp(cpf,pCpfDigitado)==0)
               if (strcmp(estrutura.cpf,pCpfDigitado)==0)
               {
                   //fseek(arq,sizeof(tipoFrequentador)-(sizeof(tipoFrequentador)-MAX_CPF),1);
                   /*fread(nome,sizeof(char)*MAX_NOME,1,arq);
                   fread(&peso,sizeof(float),1,arq);
                   fread(&sexo,sizeof(char),1,arq);
                   fread(&dia,sizeof(int),1,arq);
                   fread(&mes,sizeof(int),1,arq);
                   fread(&ano,sizeof(int),1,arq);*/
                   //fazListagemClientes(cpf,nome,peso,sexo,dia,mes,ano,contador);
                   fazListagemClientes(&estrutura,contador);
                   contador++;
                   break;
               }
               //else
               //{
                 //fseek(arq,101-(sizeof(char)*MAX_NOME),1);
                 //fseek(arq,sizeof(tipoFrequentador)-(sizeof(char)*MAX_NOME),1);
                //   fseek(arq,sizeof(tipoFrequentador),1);
               //}
             }
             if (modo == 'B')
             {
                   fread(&estrutura,sizeof(tipoFrequentador),1,arq);
                   fazListagemClientes(&estrutura,contador);
                   /*fread(nome,sizeof(char)*MAX_NOME,1,arq);
                   fread(&peso,sizeof(float),1,arq);
                   fread(&sexo,sizeof(char),1,arq);
                   fread(&dia,sizeof(int),1,arq);
                   fread(&mes,sizeof(int),1,arq);
                   fread(&ano,sizeof(int),1,arq);*/
                   //fread(&estrutura,sizeof(tipoFrequentador),1,arq);
                   //fazListagemClientes(cpf,nome,peso,sexo,dia,mes,ano,contador); 
                   contador++;
             }
             contBytes = ftell(arq);
       }
       if (contador == 0)
       {
               nenhumDadoEncontrado();
       }
       fclose(arq);
       
}
// Subprograma x               
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
//void fazListagemClientes(char *pCpf,char *pNome,float peso,char sexo,int dia,int mes,int ano, int linha)
void fazListagemClientes(struct cliente *pEstrutura,int linha)
{
     escreveQualquerCoisa("   |          CPF          |       NOME       |  PESO  |    SEXO    |   DATA    ",240,1,1);
     escreveQualquerCoisa(" N |                       |                  |  (kg)  |            | inscricao ",240,1,2);                                                                     
     fazMolduraListagemClientes(linha);
     gotoxy(2,5+linha);
     textcolor(240);
     printf("%d",linha+1);
     sleep(1);
//----------CPF------------ 
     gotoxy(6,5+linha);
     textcolor(31);
     //printf("%s",pCpf);
     printf("%s",pEstrutura->cpf);
     sleep(1);
//----------NOME------------ 
     textcolor(47);
     //if (strlen(pNome) >= 15)
     if (strlen(pEstrutura->nome) >= 15)
     {
        gotoxy(44,5+linha);
        printf("...");
     }     
     gotoxy(30,5+linha);
     //printf("%0.14s",pNome); 
     printf("%0.14s",pEstrutura->nome);  
     sleep(1);
//----------PESO------------        
     gotoxy(50,5+linha);
     textcolor(63);
    // printf("%3.1f",peso);
     printf("%3.1f",pEstrutura->peso);
     sleep(1);
//----------SEXO------------        
     gotoxy(59,5+linha);
     textcolor(79);
    // switch(sexo)
     switch(pEstrutura->sexo)
     {
                 case 'M':
                 {
                      printf("Masculino");
                      break;
                 }
                 case 'F':
                 {
                      printf("Feminino");
                      break;
                 }
     }
     sleep(1);
//----------DATA------------      
     gotoxy(71,5+linha);
     textcolor(95);
     //printf("%d/%d/%d",dia,mes,ano);
     printf("%d/%d/%d",pEstrutura->dia,pEstrutura->mes,pEstrutura->ano);
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void fazMolduraListagemClientes(int linha)
{
     gotoxy(1,5+linha);
     textcolor(240);
     printf("    ");
     gotoxy(5,5+linha);
     textcolor(31); 
     printf("                       "); //CPF
     textcolor(47); 
     gotoxy(29,5+linha);
     printf("                  ");//           NOME
     textcolor(63); 
     gotoxy(48,5+linha);
     printf("        ");
     textcolor(79); 
     gotoxy(57,5+linha);
     printf("            "); 
     
     textcolor(95); 
     gotoxy(70,5+linha);
     printf("           ");
}
//--------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------APRESENTAÇÃO DE SERIES------------------------------------------------------------
// Subprograma x              
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void mostraDadosSeries(int *pCodigoDigitado, FILE *arq,char modo)  
{
       int contador=0;
       long tamanhoArquivo, contBytes=0;
       char nomeSerie[MAX_NOME], frase[MAX_FRASE];
       int codigoLido,duracaoLida;
       float caloriasLida;
       tipoSerie estrutura;
       tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroSeries.txt");
       arq = abreArquivo("cadastroSeries.txt","rb","ERRO AO TENTAR ABRIR O ARQUIVO DE SERIES!");
       rewind(arq);
       while (contBytes < tamanhoArquivo)
       {
            // fread(nomeSerie,sizeof(char)*MAX_NOME,1,arq);
            // fread(&codigoLido,sizeof(int),1,arq);
             if (modo == 'A')
             {
               fread(&estrutura,sizeof(tipoSerie),1,arq);
             //  if (*pCodigoDigitado == codigoLido)
               if (*pCodigoDigitado == estrutura.codigo)
               {
                  // fread(&duracaoLida,sizeof(int),1,arq);
                   //fread(&caloriasLida,sizeof(float),1,arq);
                  // fread(frase,sizeof(char)*MAX_FRASE,1,arq);
                   //apresentaDadosSeries(&codigoLido,&duracaoLida,frase,nomeSerie,&caloriasLida);
                   apresentaDadosSeries(&estrutura);
                   contador++;
                   fclose(arq);
                   return;
               }
              // else
              // {
              //   fseek(arq,256-MAX_NOME-sizeof(int),1);
              // }
             }
             if (modo == 'B')
             {
                      fread(&estrutura,sizeof(tipoSerie),1,arq);
                      //fread(&duracaoLida,sizeof(int),1,arq); ss1
                      //fread(&caloriasLida,sizeof(float),1,arq);
                      //fread(frase,sizeof(char)*MAX_FRASE,1,arq);
                     // fazListagemSeries(nomeSerie,codigoLido,duracaoLida,caloriasLida,frase,contador);
                      fazListagemSeries(&estrutura,contador);
                      contador++;
             }
             contBytes = ftell(arq);
       }
       if (contador == 0)
       {
               nenhumDadoEncontrado();
       }
       fclose(arq);
       textcolor(WHITE);    
}
// Subprograma x               
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
int leValidaOpcao1Relatorio(int contador)
{
    char opcao;
    do
    {
       fazMoldura();
       mostraVoltarAoMenu();
       escreveQualquerCoisa("                     ",31,29,7);
       escreveQualquerCoisa("    MENU CONSULTAS   ",31,29,8);
       escreveQualquerCoisa("                     ",31,29,9);
       if (contador == 1)
          textcolor(32);
       gotoxy(29,11);
       printf("   REGISTRO UNICO    ");
       textcolor(WHITE);
       if (contador == 2)
          textcolor(63);
       gotoxy(29,12);
       printf("  TODOS OS REGISTROS ");
       textcolor(WHITE);
       opcao = getch();
       if (opcao == 27)
       {
          return 0;
       }
       contador = quantidadeSetasMenu(opcao,2,contador);
    }while(opcao != 13);
    return contador;
}   
// Subprograma x              
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
int menuEscolhaTipoPesquisa()
{
    int contador=1;
    char opcao;
    do
    {
       fazMoldura();
       mostraVoltarAoMenu();
       textcolor(WHITE);
       if (contador == 1)
          textcolor(224);
       gotoxy(29,13);
       printf("   FREQUENTADORES    ");
       textcolor(WHITE);
       if (contador == 2)
          textcolor(224);
       gotoxy(29,14);
       printf("       SERIES        ");
       textcolor(WHITE);
       if (contador == 3)
          textcolor(224);
       gotoxy(29,15);
       printf("     ATIVIDADES      ");
       textcolor(WHITE);
       opcao = getch();
       if (opcao == 27)
       {
          return 0;
       }
       contador = quantidadeSetasMenu(opcao,3,contador);
    }while(opcao != 13);
    return contador;
}   
// Subprograma x              
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void mostraDadosAtividades(char *pCpfDigitado, FILE *arq,char modo)  // XX4
{
       int contador=0;
       long tamanhoArquivo, contBytes=0;
       char cpfLido[MAX_CPF],horaLida[MAXHORA];
       int dia,mes,ano,codigoLido;
       tipoAtividade estrutura;
       tamanhoArquivo = obtemTamanhoArquivo(arq,"Atividades.txt");
       arq = abreArquivo("Atividades.txt","rb","ERRO AO TENTAR ABRIR O ARQUIVO DE ATIVIDADES!");
       rewind(arq);
       while (contBytes < tamanhoArquivo)
       {
           //  fread(cpfLido,sizeof(char)*MAX_CPF,1,arq);
             if (modo == 'A')
             {
               fread(&estrutura,sizeof(tipoAtividade),1,arq);
             //  if (strcmp(pCpfDigitado,cpfLido) == 0)
               if (strcmp(pCpfDigitado,estrutura.cpf) == 0)
               {
                   //fread(&codigoLido,sizeof(int),1,arq); 
                   //fread(&dia,sizeof(int),1,arq);
                   //fread(&mes,sizeof(int),1,arq);
                   //fread(&ano,sizeof(int),1,arq);
                   //fread(horaLida,sizeof(char)*MAXHORA,1,arq);
                  // fazListagemAtividades(cpfLido,codigoLido,dia,mes,ano,horaLida,contador);
                   fazListagemAtividades(&estrutura,contador);
                   contador++;
       
               }
               //else
               //{
               //  fseek(arq,(sizeof(int)*4)+(sizeof(char)*MAXHORA),1);
               //}
             }
             if (modo == 'B')
             {
                   fread(&estrutura,sizeof(tipoAtividade),1,arq);
                   //fread(&codigoLido,sizeof(int),1,arq); 
                   //fread(&dia,sizeof(int),1,arq);
                   //fread(&mes,sizeof(int),1,arq);
                   //fread(&ano,sizeof(int),1,arq);
                   //fread(horaLida,sizeof(char)*MAXHORA,1,arq);
                //   fazListagemAtividades(cpfLido,codigoLido,dia,mes,ano,horaLida,contador);  
                   fazListagemAtividades(&estrutura,contador);   
                   contador++;
             }
             contBytes = ftell(arq);
       }
       if (contador == 0)
       {
               nenhumDadoEncontrado();
               getch();
       }
       fclose(arq);
       textcolor(WHITE);    
}
// Subprograma x              
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
//void fazListagemAtividades(char *pCpf,int codigo,int dia,int mes,int ano,char *pHora, int linha)
void fazListagemAtividades(tipoAtividade *estrutura,int linha)
{
     escreveQualquerCoisa("   |          CPF          |  CODIGO   |     DATA     |          HORA           ",240,1,1);
     escreveQualquerCoisa(" N |                       |           |              |      da realizacao      ",240,1,2);                                                                     
     fazMolduraListagemAtividades(linha);
     gotoxy(2,5+linha);
     textcolor(240);
     printf("%d",linha+1);
     sleep(1);
//----------CPF------------ 
     gotoxy(6,5+linha);
     textcolor(31);
     //printf("%s",pCpf);
     printf("%s",estrutura->cpf);
     sleep(1);
//----------CODIGO------------ 
     textcolor(47);
     gotoxy(32,5+linha);
     //printf("%d",codigo);  
     printf("%d",estrutura->codigo);
     sleep(1);
//----------DATA------------      
     gotoxy(43,5+linha);
     textcolor(95);
    // printf("%d/%d/%d",dia,mes,ano);
      printf("%d/%d/%d",estrutura->dia,estrutura->mes,estrutura->ano);
     textcolor(WHITE);
//----------HORA------------        
     gotoxy(63,5+linha);
     textcolor(79);
     //printf("%s",pHora);
     printf("%s",estrutura->hora);
     sleep(1);
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void fazMolduraListagemAtividades(int linha)
{
//---------NUMERO-----------
     gotoxy(1,5+linha);
     textcolor(240);
     printf("    ");
//---------CPF-----------     
     gotoxy(5,5+linha);
     textcolor(31); 
     printf("                       "); 
//---------CODIGO-----------  
     textcolor(47); 
     gotoxy(29,5+linha);
     printf("           ");
//---------CODIGO-----------      
     textcolor(95); 
     gotoxy(41,5+linha);
     printf("              ");
//----------HORA------------       
     textcolor(79); 
     gotoxy(56,5+linha);
     printf("                        "); 
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void apontaParaEscolhaLista(int contador)
{
     if (contador > 0)
     {
        gotoxy(1,4+contador);
        textcolor(207);
        printf("    ");
        gotoxy(1,4+contador);
        printf(" %d",contador);
        textcolor(WHITE);
     }
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void abreTodosOsArquivos(FILE *arqSerie,FILE *arqCliente,FILE *arqAtividade)
{
     arqSerie=abreArquivo("cadastroSeries.txt","a+b","ERRO AO CRIAR O ARQUIVO DE SERIES!");
     arqCliente=abreArquivo("cadastroClientes.txt","a+b","ERRO AO CRIAR O ARQUIVO DE CLIENTES");
     arqAtividade=abreArquivo("Atividades.txt","a+b","ERRO AO CRIAR O ARQUIVO DE ATIVIDADES");
     fclose(arqSerie);
     fclose(arqCliente);
     fclose(arqAtividade);
}
// Subprograma x
//     Objetivo  : Encontrar o CPF do cliente que realizou uma determinada Série e chamar as funções para apresentar-los.
//     Parâmetro : Endereço dos arquivos de Series e Clientes, endereço do código da série digitado.
//     Retorno   : Nenhum.   
void achaClientesComSerie(FILE *arqAtividades, FILE *arqCliente,int *pCodigoDigitado)
{
     //Declarações
     char cpf[MAX_CPF],nome[MAX_NOME],sexo;
     int dia,mes,ano;
     float peso;
     long contBytes=0,tamanhoArquivoAtividades,contBytes2=0,tamanhoArquivoFrequentador;
     int codigoLido,contador=0;
     char cpfLido[MAX_CPF];
     tipoFrequentador estrutura;
     tipoAtividade estruturaAtividade;
     //Instruções
     clrscr();
     arqAtividades=abreArquivo("Atividades.txt","rb","ERRO AO ABRIR O ARQUIVO DE ATIVIDADES!");
     arqCliente=abreArquivo("cadastroClientes.txt","rb","ERRO AO ABRIR O ARQUIVO DE CLIENTES!");
     tamanhoArquivoAtividades = obtemTamanhoArquivo(arqAtividades,"Atividades.txt");
     tamanhoArquivoFrequentador = obtemTamanhoArquivo(arqCliente,"cadastroClientes.txt");
     while(contBytes < tamanhoArquivoAtividades)
     {
                    // fseek(arqAtividades,sizeof(char)*MAX_CPF,1);
                     //fread(&codigoLido,sizeof(int),1,arqAtividades);
                     fread(&estruturaAtividade,sizeof(tipoAtividade),1,arqAtividades);
                  //   if (codigoLido == *pCodigoDigitado)
                     if (estruturaAtividade.codigo == *pCodigoDigitado)
                     {
                           rewind(arqCliente);
                           fread(&estrutura,sizeof(tipoFrequentador),1,arqCliente);
                           while(contBytes2 < tamanhoArquivoFrequentador)
                           {
                                   if (estruturaAtividade.cpf == estrutura.cpf)
                                   {
                                            fazListagemClientes(&estrutura,contador);   
                                            contador++;               
                                   }
                                   contBytes2 = ftell(arqCliente);
                           }
                           /*fseek(arqAtividades,-1*(sizeof(int)+MAX_CPF),1);
                           fread(cpfLido,sizeof(char)*MAX_CPF,1,arqAtividades);*/
                         //  leUmaStructClientesCpf(cpfLido,arqCliente,cpf,nome,&peso,&sexo,&dia,&mes,&ano);
                          //void leUmaStructClientesCpf(char *pCpfDigitado,FILE *arqClientes,tipoFrequentador estrutura);
                          // fazListagemClientes(cpf,nome,peso,sexo,dia,mes,ano,contador);
                          // fazListagemClientes(&estrutura,contador);
                         //  fseek(arqAtividades,(sizeof(int)*4)+(sizeof(char)*MAXHORA),1);
                        //   contador++;
                     }
                     else
                     {
                         fseek(arqAtividades,(sizeof(int)*3)+(sizeof(char)*MAXHORA),1);
                     }
                     contBytes = ftell(arqAtividades);
     }
     if (contador == 0)
     {
                  nenhumDadoEncontrado();
     }
     fclose(arqAtividades);
     fclose(arqCliente);
}
// Subprograma x cc1
//     Objetivo  : Ler uma estrutura inteira de clientes atrevéz de um cpf.
//     Parâmetro : Estrutura de clientes toda, endereço do cpf digitado e do arquivo de clientes.
//     Retorno   : Nenhum.
/*void leUmaStructClientesCpf(char *pCpfDigitado,FILE *arqClientes,char *pCpfLido,char *pNomeLido,float *pPesoLido,char *pSexoLido,int *pDiaLido,int *pMesLido,int *pAnoLido)
{  
     long contBytes=0,tamanhoArquivo;
     arqClientes=abreArquivo("cadastroClientes.txt","rb","ERRO AO ABRIR O ARQUIVO DE CLIENTES");
     tamanhoArquivo = obtemTamanhoArquivo(arqClientes,"cadastroClientes.txt");
     while (contBytes < tamanhoArquivo)
     {
           fread(pCpfLido,sizeof(char)*MAX_CPF,1,arqClientes);
           if (strcmp(pCpfLido,pCpfDigitado)==0)
           {
                  fread(pNomeLido,sizeof(char)*TAM_NOME,1,arqClientes);
                  fread(pPesoLido,sizeof(float),1,arqClientes);
                  fread(pSexoLido,sizeof(char),1,arqClientes);
                  fread(pDiaLido,sizeof(int),1,arqClientes);
                  fread(pMesLido,sizeof(int),1,arqClientes);
                  fread(pAnoLido,sizeof(int),1,arqClientes);
                  fclose(arqClientes);
                  return;
           }
           else
           {
               fseek(arqClientes,101 - MAX_CPF,1);
           }
           contBytes = ftell(arqClientes);
     }
     fclose(arqClientes);
  //   nenhumDadoEncontrado();
  //   getch();
     return;   
}*/
 //cc1
// Subprograma x
//     Objetivo  : Ler uma estrutura inteira de clientes atrevéz de um cpf.
//     Parâmetro : Estrutura de clientes toda, endereço do cpf digitado e do arquivo de clientes.
//     Retorno   : Nenhum.
void leUmaStructClientesCpf(char *pCpfDigitado,FILE *arqClientes,tipoFrequentador *estrutura)
{  
     long contBytes=0,tamanhoArquivo;
     arqClientes=abreArquivo("cadastroClientes.txt","rb","ERRO AO ABRIR O ARQUIVO DE CLIENTES");
     tamanhoArquivo = obtemTamanhoArquivo(arqClientes,"cadastroClientes.txt");
     while (contBytes < tamanhoArquivo)
     {
          // fread(pCpfLido,sizeof(char)*MAX_CPF,1,arqClientes);
           fread(estrutura,sizeof(tipoFrequentador),1,arqClientes);
           if (strcmp(estrutura->cpf,pCpfDigitado)==0)
           {
                  //fread(pNomeLido,sizeof(char)*TAM_NOME,1,arqClientes);
                  //fread(pPesoLido,sizeof(float),1,arqClientes);
                  //fread(pSexoLido,sizeof(char),1,arqClientes);
                  //fread(pDiaLido,sizeof(int),1,arqClientes);
                  //fread(pMesLido,sizeof(int),1,arqClientes);
                  //fread(pAnoLido,sizeof(int),1,arqClientes);
                  fclose(arqClientes);
                  return;
           }
           else
           {
               fseek(arqClientes,101 - MAX_CPF,1);
           }
           contBytes = ftell(arqClientes);
     }
     fclose(arqClientes);
  //   nenhumDadoEncontrado();
  //   getch();
     return;   
}
// Subprograma x
//     Objetivo  : Fazer uma moldura para inserir data nela
//     Parâmetro : Nenhum.
//     Retorno   : Nenhum.
void fazMolduraData()
{
     fazMolduraCadastros(49999);
     fazMolduraEscolha(31,9,15);
     escreveQualquerCoisa("    /    /   ",15,33,10);
     fazMolduraEscolha(31,12,15);
     escreveQualquerCoisa("    /    /   ",15,33,13);
     escreveQualquerCoisa("DE:",15,27,10);
     escreveQualquerCoisa("ATE:",15,26,13);
     
}
// Subprograma x
//     Objetivo  :  
//     Parâmetro :  
//     Retorno   :  
int leValidaAno(int *pAno)
{
     *pAno = leValidaNumeros(2011,4000,5);
     if (*pAno == -1)
        return 0;
     return 1;
}
// Subprograma x
//     Objetivo  :  
//     Parâmetro :  
//     Retorno   :  
int leValidaMes(int *pMes)
{
     *pMes = leValidaNumeros(0,12,4);
     if (*pMes == -1)
        return 0;
     return 1;
}
// Subprograma x
//     Objetivo  :  
//     Parâmetro :  
//     Retorno   :  
int leValidaDia(int *pAno, int *pMes, int *pDia)
{
     *pDia = leValidaNumeros(0,31,4);
     if (*pDia == -1)
        return 0;
     return 1;
}
// Subprograma x
//     Objetivo  :  
//     Parâmetro :  
//     Retorno   :  
int leValidaDataDeAte(int *pAno, int *pMes, int *pDia)
{
    int bisexto=0;
    int diaValido=0;
    fazMolduraData();
    escreveQualquerCoisa("         DIGITE O PRIMEIRO ANO DA PESQUISA       ",31,16,15);
    leValidaAno(&pAno[0]);
    if (pAno[0] == -1)
       return 0;
    escreveQualquerInteiro(&pAno[0],10,44,10);
    bisexto = verificaAnoBisexto(pAno[0]);
    escreveQualquerCoisa("         DIGITE O PRIMEIRO MES DA PESQUISA       ",31,16,15);
    leValidaMes(&pMes[0]);
    if (pMes[0] == -1)
       return 0;
    escreveQualquerInteiro(&pMes[0],10,40,10);
    escreveQualquerCoisa("         DIGITE O PRIMEIRO DIA DA PESQUISA!      ",31,16,15);
    do
    {
       leValidaDia(&pAno[0],&pMes[0],&pDia[0]);
       diaValido = validaDia(pDia[0],pMes[0],bisexto);
       if (pDia[0] == -1)
          return 0;
    }while(diaValido==0);
    limpaTelaCordenada(19,19,40,' ');
    escreveQualquerInteiro(&pDia[0],10,34,10);
    escreveQualquerCoisa("         DIGITE O ULTIMO ANO DA PESQUISA         ",79,16,15);
    pAno[1] = leValidaNumeros(pAno[0]-1,4000,5);
    if (pAno[1] == -1)
       return 0;
    escreveQualquerInteiro(&pAno[1],14,44,13);
    bisexto = verificaAnoBisexto(pAno[1]);
    escreveQualquerCoisa("         DIGITE O ULTIMO MES DA PESQUISA         ",79,16,15);
    if (pAno[0] == pAno[1])
       pMes[1] = leValidaNumeros(pMes[0]-1,12,4);
    else
        leValidaMes(&pMes[1]);
    if (pMes[1] == -1)
       return 0;
    escreveQualquerInteiro(&pMes[1],14,40,13);
    escreveQualquerCoisa("         DIGITE O ULTIMO DIA DA PESQUISA!        ",79,16,15);
    do
    {
          if ((pAno[0] == pAno[1]) && (pMes[0] == pMes[1]))
             pDia[1] = leValidaNumeros(pDia[0]-1,31,4);
          else
              leValidaDia(&pAno[1],&pMes[1],&pDia[1]);
          diaValido = validaDia(pDia[1],pMes[1],bisexto);
          if (pDia[1] == -1)
                return 0;
    }while(diaValido==0);
    limpaTelaCordenada(19,19,40,' ');
    escreveQualquerInteiro(&pDia[1],14,34,13);
    return 1;
}
// Subprograma x
//     Objetivo  :  Escrever um valor inteiro em qualquer lugar da tela em qualquer cor!
//     Parâmetro :  Ponteiro do valor, cor e cordenadas.
//     Retorno   :  Nenhum.
void escreveQualquerInteiro(int *pInt,int cor,int cordenadaX,int cordenadaY)
{
     textcolor(cor);
     gotoxy(cordenadaX,cordenadaY);
     printf("%d",*pInt);
     textcolor(WHITE);
}
// Subprograma x
//     Objetivo  : Verificar se um ano é bisexto.
//     Parâmetro : Ano.
//     Retorno   : Resultado lógico.
int verificaAnoBisexto(int ano)
{
     if (((!(ano % 4)) && (ano % 100)) || (!(ano % 400)))
          return 1;
     return 0;
}        
// Subprograma x
//             Objetivo: Validar o dia de nascimento.
//             Parametros: Dia, mês e ano de nascimento.
//             Retorno: Dia validado.
int validaDia(int dia, int mes, int bisexto)
{
                    if ((mes == 1) || (mes == 3) || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12))
                    {
                       if ((dia < 1) || (dia > 31))
                       {
                             escreveQualquerCoisa("Dia invalido! Digite novamente:",10,26,19);
                             return 0;
                       }
                       return 1;
                    }
                    else
                    {
                         if (mes != 2)
                         {
                            if ((dia < 1) || (dia > 30))
                            {
                                  escreveQualquerCoisa("Dia invalido! Digite novamente:",10,26,19);
                                  return 0;
                            }
                            return 1;
                         }
                         else
                          {
                              if (bisexto == 1) 
                              {
                                  if ((dia < 1) || (dia > 29))
                                  {
                                     escreveQualquerCoisa("Dia invalido! Digite novamente:",10,26,19);
                                     return 0;
                                  }
                                  return 1;
                              }
                              else
                              {
                                     if ((dia < 1) || (dia > 28))
                                     {
                                        escreveQualquerCoisa("Dia invalido! Digite novamente:",10,26,19);
                                        return 0;
                                     }
                                     return 1;
                              }
                          }
                    }
                    return 1;
}
// Subprograma x
//             Objetivo   :  Escrever qualquer string, em qualquer cor e em qualquer lugar da tela.
//             Parametros :  Ponteiro da string, cor e cordenadas.
//             Retorno    :  Nenhum.
void escreveQualquerString(char *pString,int cor,int cordenadaX,int cordenadaY)
{
     textcolor(cor);
     gotoxy(cordenadaX,cordenadaY);
     printf("%s",pString);
     textcolor(WHITE);
}
// Subprograma x
//             Objetivo   :  Encontrar e escrever o nome de um cliente atravéz de seu CPF
//             Parametros :  cpf válido, cordenadas e cor do nome.
//             Retorno    :  Nenhum.
void escreveNomeCliente(FILE *arq,char *pCpfDigitado,int cor,int cordenadaX,int cordenadaY)
{
       long contBytes=0,tamanhoArquivo;
       char cpfLido[MAX_CPF],nome[MAX_NOME];
       tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroClientes.txt");
       arq = abreArquivo("cadastroClientes.txt","rb","ERRO AO ABRIR O ARQUIVO DE CLIENTES");
       while (contBytes < tamanhoArquivo)
       {
             fread(cpfLido,sizeof(char)*MAX_CPF,1,arq);
             if (strcmp(cpfLido,pCpfDigitado)==0)
             {
                fread(nome,sizeof(char)*MAX_NOME,1,arq);
                fclose(arq);
                escreveQualquerString(nome,cor,cordenadaX,cordenadaY);
                return;
             }
             else
             {
                 fseek(arq,101 - (sizeof(char)*MAX_CPF),1);
             }
             contBytes = ftell(arq);
       }
       fclose(arq);
}
// Subprograma x
//             Objetivo   : Verificar se um cliente ja realizou uma atividade.
//             Parametros : Ponteiro do cpf digitado e endereço do arquivo de Atividades.
//             Retorno    : Resultado lógico do objetivo.
int verificaCpfFezAtividade(char *pCpfDigitado,FILE *arqAtividades)
{
     long contBytes=0, tamanhoArquivo;
     char cpfLido[MAX_CPF];
     tamanhoArquivo = obtemTamanhoArquivo(arqAtividades,"Atividades.txt");
     arqAtividades = abreArquivo("Atividades.txt","rb","ERRO AO TENTAR ABRIR O ARQUIVO DE ATIVIDADES!");
     while (contBytes < tamanhoArquivo)
     {
           fread(cpfLido,sizeof(char)*MAX_CPF,1,arqAtividades);
           if (strcmp(cpfLido,pCpfDigitado)==0)
           {
                   fclose(arqAtividades);
                   return 1;   
           }
           else
           {
                      fseek(arqAtividades,67 - (sizeof(char)*MAX_CPF),1);
           }
           contBytes = ftell(arqAtividades);
     }
     fclose(arqAtividades);
     return 0;
}
// Subprograma x           YY1
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
void achaMostraAtividadesData(char *pCpfDigitado, FILE *arqAtividades,FILE *arqSeries,int *pDia,int *pMes,int *pAno)
{
     FILE *temp;
     long contBytes=0,tamanhoArquivo;
     char cpfLido[MAX_CPF],horaLida[MAXHORA];
     int codigoLido,diaLido,mesLido,anoLido,contador=0,aux=0;
     int tempoLido;
     float caloriasLida;
     tipoAtividade estrutura;
     tamanhoArquivo = obtemTamanhoArquivo(arqAtividades,"Atividades.txt");
     arqAtividades = abreArquivo("Atividades.txt","rb","ERRO AO ABRIR O ARQUIVO DE ATIVIDADES");
     while (contBytes < tamanhoArquivo)
     {
           /*fread(cpfLido,sizeof(char)*MAX_CPF,1,arqAtividades);
           fread(&codigoLido,sizeof(int),1,arqAtividades);
           fread(&diaLido,sizeof(int),1,arqAtividades);
           fread(&mesLido,sizeof(int),1,arqAtividades);
           fread(&anoLido,sizeof(int),1,arqAtividades);
           fread(horaLida,sizeof(char)*MAXHORA,1,arqAtividades);*/
           fread(&estrutura,sizeof(tipoAtividade),1,arqAtividades);
         //  if (strcmp(cpfLido,pCpfDigitado) == 0)
           if (strcmp(estrutura.cpf,pCpfDigitado) == 0)
           {
              aux = verificaEntreDatas(anoLido,mesLido,diaLido,&pAno[0],&pMes[0],&pDia[0]);
              if (aux)
              {
                  // fazListagemAtividades(cpfLido,codigoLido,diaLido,mesLido,anoLido,horaLida,contador);
                   fazListagemAtividades(&estrutura,contador);
                   contador++;
                   achaTempoEcalorias(arqSeries,&tempoLido,&caloriasLida,codigoLido);
                   criaTempComResumo(temp,tempoLido,caloriasLida,diaLido,mesLido,anoLido); 
              }
              aux=0;
           }
           contBytes = ftell(arqAtividades);
     }
     textcolor(WHITE);
     fclose(arqAtividades);
     if (!contador)
     {
                   nenhumDadoEncontrado();
     }
     else
     {
         getch();
         limpaTelaEfeito();
         chamaListagemTemp(temp);
     }
     textcolor(WHITE);
}
// Subprograma x         
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
void chamaListagemTemp(FILE *temp)
{
          long contBytes=0,tamanhoArquivo;
          float caloriasLida;
          int diaLido,mesLido,anoLido,tempoLido,contador=0;
          tamanhoArquivo = obtemTamanhoArquivo(temp,"temp.txt");
          temp = abreArquivo("temp.txt","rb","ERRO AO ABRIR O ARQUIVO TEMPORARIO");
          rewind(temp);
          while (contBytes < tamanhoArquivo)
          {
                fread(&diaLido,sizeof(int),1,temp);
                fread(&mesLido,sizeof(int),1,temp);
                fread(&anoLido,sizeof(int),1,temp);
                fread(&caloriasLida,sizeof(float),1,temp);
                fread(&tempoLido,sizeof(int),1,temp);
                listaTempResumo(&diaLido,&mesLido,&anoLido,&caloriasLida,&tempoLido,contador);
                contBytes = ftell(temp);
                contador++;
          }
          fclose(temp);
          remove("temp.txt");
}
// Subprograma x         
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
void criaTempComResumo(FILE *temp,int tempo,float calorias,int dia,int mes,int ano)
{
          long contBytes=0,tamanhoArquivo;
          float caloriasLida,totalCalorias=0;
          int diaLido,mesLido,anoLido,tempoLido,totalTempo=0;
          temp = abreArquivo("temp.txt","a+b","ERRO AO ABRIR O ARQUIVO TEMPORARIO");
          fclose(temp);
          temp = abreArquivo("temp.txt","r+b","ERRO AO ABRIR O ARQUIVO TEMPORARIO");
          fseek(temp,0,2);
          tamanhoArquivo = ftell(temp);
          rewind(temp);
          while (contBytes < tamanhoArquivo)
          {
                fread(&diaLido,sizeof(int),1,temp);
                fread(&mesLido,sizeof(int),1,temp);
                fread(&anoLido,sizeof(int),1,temp);
                fread(&caloriasLida,sizeof(float),1,temp);
                fread(&tempoLido,sizeof(int),1,temp);
                if (((diaLido == dia) && (mesLido == mes) && (anoLido == ano)))
                {
                           fseek(temp,-1*(sizeof(int)+sizeof(float)),1);
                           totalCalorias = calorias + caloriasLida;
                           totalTempo = tempo + tempoLido;
                           fwrite(&totalCalorias,sizeof(float),1,temp);
                           fwrite(&totalTempo,sizeof(int),1,temp);
                           fclose(temp);
                           return;
                              
                }
                else
                {
                   fseek(temp,sizeof(float)+sizeof(int),1);
                   contBytes = ftell(temp);    
                }
          }
          if (tamanhoArquivo == 0)
          {
                fwrite(&dia,sizeof(int),1,temp);
                fwrite(&mes,sizeof(int),1,temp);
                fwrite(&ano,sizeof(int),1,temp);
                fwrite(&calorias,sizeof(float),1,temp);
                fwrite(&tempo,sizeof(int),1,temp);
                fclose(temp);
                return;   
          }     
          fseek(temp,0,2);
          fwrite(&dia,sizeof(int),1,temp);
          fwrite(&mes,sizeof(int),1,temp);
          fwrite(&ano,sizeof(int),1,temp);
          fwrite(&calorias,sizeof(float),1,temp);
          fwrite(&tempo,sizeof(int),1,temp);
          fclose(temp);
          return; 
}
// Subprograma x          YY5
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
void listaTempResumo(int *pDia,int *pMes, int *pAno, float *pCalorias,int *pTempo,int linha)
{
     escreveQualquerCoisa("   |       DATA        |    TOTAL DE CALORIAS      |      TOTAL DE TEMPO        ",240,1,1);
     escreveQualquerCoisa(" N |                   |                           |                            ",240,1,2);  
     escreveQualquerCoisa("RESUMO DE CALORIAS E TEMPO POR DIA",14,22,3);                                                                   
     fazMolduraListagemResumo(linha);
     gotoxy(2,5+linha);
     textcolor(240);
     printf("%d",linha+1);
     sleep(1);
//----------DATA------------ 
     gotoxy(10,5+linha);
     textcolor(31);
     printf("%d/%d%/%d",*pDia,*pMes,*pAno);
     sleep(1);
//----------TOTAL DE CALORIAS------------ 
     textcolor(47);
     gotoxy(35,5+linha);
     printf("%3.2f",*pCalorias);  
     sleep(1);
//----------TOTAL DE TEMPO------------        
     gotoxy(64,5+linha);
     textcolor(63);
     printf("%d minutos",*pTempo);
     sleep(1);
}
// Subprograma x
//     Objetivo  : 
//     Parâmetro : 
//     Retorno   : 
void fazMolduraListagemResumo(int linha)
{
     gotoxy(1,5+linha);
     textcolor(240);
     printf("    ");
     gotoxy(5,5+linha);
     textcolor(31); 
     printf("                   "); 
     textcolor(47); 
     gotoxy(25,5+linha);
     printf("                           ");
     textcolor(63); 
     gotoxy(53,5+linha);
     printf("                           ");
     textcolor(79); 
}
// Subprograma x        YY3 
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
void achaTempoEcalorias(FILE *arqSeries,int *pTempo, float *pCalorias,int codigo)
{
     //Declarações
     long contBytes=0,tamanhoArquivo;
     int codigoLido;
     //instruções:
     tamanhoArquivo = obtemTamanhoArquivo(arqSeries,"cadastroSeries.txt");
     arqSeries = abreArquivo("cadastroSeries.txt","rb","ERRO AO ABRIR O ARQUIVO DE SERIES");
     while (contBytes < tamanhoArquivo)
     {
           fseek(arqSeries,sizeof(char)*MAX_NOME,1);
           fread(&codigoLido,sizeof(int),1,arqSeries);
           if (codigoLido == codigo)
           {
                          fread(pTempo,sizeof(int),1,arqSeries);
                          fread(pCalorias,sizeof(float),1,arqSeries);
                          fclose(arqSeries);
                          return;
           }
           fseek(arqSeries,sizeof(int)+sizeof(float)+ (sizeof(char)*MAX_FRASE),1);
     }
     fclose(arqSeries);
}
//                                  SEQUENCIA STRUCT SERIES
// NOME (42)
// CODIGO (4)
// DURACAO (4)                    TAMANHO = 256 bytes
// CALORIAS (4)
// FRASE (NAX_FRASE)



// Subprograma x         
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
int verificaEntreDatas(int anoLido,int mesLido,int diaLido,int *pAno,int *pMes, int *pDia)
{
    if ((anoLido >= pAno[0]) && (anoLido <= pAno[1]))
    {
               if ((anoLido > pAno[0]) && (anoLido < pAno[1]))
               {
                            return 1;
               }  
               else
               {
                   if (pAno[0] == pAno[1])
                   {
                               if ((mesLido > pMes[0]) && (mesLido < pMes[1]))
                               {
                                            return 1;           
                               }
                               else
                               {
                                   if ((mesLido == pMes[0]) && (mesLido == pMes[1]))
                                   {
                                                if ((diaLido >= pDia[0]) && (diaLido <= pDia[1]))
                                                {
                                                             return 1;
                                                }
                                   }
                                   else
                                   {
                                      if (mesLido == pMes[0])
                                      {
                                               if (diaLido >= pDia[0])
                                               {
                                                           return 1;
                                               }
                                      }
                                      else
                                      {
                                         if (mesLido == pMes[1])
                                         {
                                                   if (diaLido <= pDia[1])
                                                   {
                                                           return 1;    
                                                   }
                                         }
                                      }
                                   }
                               }
                   }
                   else
                   {
                       if (anoLido == pAno[0])
                       {
                                   if (mesLido > pMes[0])
                                   {
                                              return 1;
                                   }
                                   else
                                   {
                                       if (mesLido == pMes[0])
                                       {
                                                   if (diaLido >= pDia[0])
                                                   {
                                                               return 1;
                                                   }
                                       }
                                   }
                       }
                       else
                       {
                           if (anoLido == pAno[1])
                           {
                                       if (mesLido < pMes[1])
                                       {
                                                   return 1;
                                       }
                                       else
                                       {
                                           if (mesLido == pMes[1])
                                           {
                                                       if (diaLido <= pDia[1])
                                                       {
                                                                   return 1;
                                                       }
                                           }
                                       }
                           }
                       }
                   }
               }  
    }
    return 0;
}
// Subprograma x           YY1
//             Objetivo   : 
//             Parametros : 
//             Retorno    :
void achaMostraClientesData(int *pAno,int *pMes,int *pDia,FILE *arqAtividades,FILE *arqClientes)
{
     char cpf[MAX_CPF],nome[MAX_NOME],sexo;
     int dia,mes,ano;
     float peso;
     long contBytes=0,tamanhoArquivo;
     char cpfLido[MAX_CPF],horaLida[MAXHORA];
     int codigoLido,diaLido,mesLido,anoLido,contador=0,aux=0;
     tipoFrequentador estrutura;
     tamanhoArquivo = obtemTamanhoArquivo(arqAtividades,"Atividades.txt");
     arqAtividades = abreArquivo("Atividades.txt","rb","ERRO AO ABRIR O ARQUIVO DE ATIVIDADES");
     while (contBytes < tamanhoArquivo)
     {
           /*fread(cpfLido,sizeof(char)*MAX_CPF,1,arqAtividades);
           fread(&codigoLido,sizeof(int),1,arqAtividades);
           fread(&diaLido,sizeof(int),1,arqAtividades);
           fread(&mesLido,sizeof(int),1,arqAtividades);
           fread(&anoLido,sizeof(int),1,arqAtividades);
           fread(horaLida,sizeof(char)*MAXHORA,1,arqAtividades);*/
           fread(&estrutura,sizeof(tipoAtividade),1,arqAtividades);
        //   aux = verificaEntreDatas(anoLido,mesLido,diaLido,&pAno[0],&pMes[0],&pDia[0]);
           aux = verificaEntreDatas(estrutura.ano,estrutura.mes,estrutura.dia,&pAno[0],&pMes[0],&pDia[0]);
           if (aux)
           {
                 //  leUmaStructClientesCpf(cpfLido,arqClientes,cpf,nome,&peso,&sexo,&dia,&mes,&ano);
                   leUmaStructClientesCpf(cpfLido,arqClientes,&estrutura);
                  // fazListagemClientes(cpf,nome,peso,sexo,dia,mes,ano,contador);
                   fazListagemClientes(&estrutura,contador);
                   contador++;
           }
           aux=0;
           contBytes = ftell(arqAtividades);
     }
     textcolor(WHITE);
     fclose(arqAtividades);
     if (!contador)
     {
                   nenhumDadoEncontrado();
     }
}
// Subprograma x           
//             Objetivo   : Comparar duas strings para ver qual é a maior.
//             Parametros : Duas strings.
//             Retorno    : -1,0 ou 1.
int comparaString(const void *estruturaA,const void *estruturaB)
{
    tipoFrequentador *pChar1 = (tipoFrequentador *)estruturaA;
    tipoFrequentador *pChar2 = (tipoFrequentador *)estruturaB;
    return strcmp(pChar1->nome,pChar2->nome);
}
// Subprograma x      YY6     
//             Objetivo   :
//             Parametros : 
//             Retorno    :
int achaClientePorCpf(FILE *arqCliente,char *cpfComparar,int contador2)
{
     long tamanhoArquivo,contBytes=0;
     char cpfLido[MAX_CPF],sexoLido,nomeLido[TAM_NOME];
     float pesoLido;
     int diaLido,mesLido,anoLido,contador=0;
     tipoFrequentador estrutura;
     tamanhoArquivo = obtemTamanhoArquivo(arqCliente,"cadastroClientes.txt");
     arqCliente = abreArquivo("cadastroClientes.txt","rb","ERRO AO TENTAR ABRIR O ARQUIVO DE CLIENTES!");
     while(contBytes < tamanhoArquivo)
     {
                   fread(cpfLido,sizeof(char)*MAX_CPF,1,arqCliente);
                   fread(nomeLido,sizeof(char)*MAX_NOME,1,arqCliente);
                   fread(&pesoLido,sizeof(float),1,arqCliente);
                   fread(&sexoLido,sizeof(char),1,arqCliente);
                   fread(&diaLido,sizeof(int),1,arqCliente);
                   fread(&mesLido,sizeof(int),1,arqCliente);
                   fread(&anoLido,sizeof(int),1,arqCliente);
                   if (strcmp(cpfComparar,cpfLido) == 0)
                   {
                        //  fazListagemClientes(cpfLido,nomeLido,pesoLido,sexoLido,diaLido,mesLido,anoLido,contador2);
                          fazListagemClientes(&estrutura,contador2);
                          contador2++;      
                   }
                   
                   contBytes = ftell(arqCliente);
                   
     }
     fclose(arqCliente);
     return contador2;
}
// Subprograma x           
//             Objetivo   : Encontrar clientes Ausentes.
//             Parametros : Arquivo de Atividades, ponteiro de dia, mes e ano e quantidade de dias ausente.
//             Retorno    :
void achaClientesAusentes(FILE *arq,int *pDia,int *pMes,int *pAno,int diasAusente,FILE *arqCliente)
{
     FILE *temp;
     long tamanhoArquivo,contBytes=0;
     char cpfLido[MAX_CPF], horaLida[MAXHORA];
     int codigoLido,diaLido,mesLido,anoLido,aux=0,contador=0,contador2=0;
     tamanhoArquivo = obtemTamanhoArquivo(arq,"Atividades.txt");
     arq = abreArquivo("Atividades.txt","rb","ERRO AO TENTAR ABRIR O ARQUIVO DE ATIVIDADES!"); 
     while (contBytes < tamanhoArquivo)
     {
           fread(cpfLido,sizeof(char)*MAX_CPF,1,arq);
           fread(&codigoLido,sizeof(int),1,arq);
           fread(&diaLido,sizeof(int),1,arq);
           fread(&mesLido,sizeof(int),1,arq);
           fread(&anoLido,sizeof(int),1,arq);
           fread(horaLida,sizeof(char)*MAXHORA,1,arq);
           aux = verificaEntreDatas(anoLido,mesLido,diaLido,&pAno[0],&pMes[0],&pDia[0]);
           if (!aux)
           {
                   criaTempCpf(temp,cpfLido); 
                   contador++;
           }
           aux=0;
           contBytes = ftell(arq);
     }
     if (!contador)
     {
                   nenhumDadoEncontrado();
                   fclose(arq);
                   return;
     }
     fclose(arq);
     tamanhoArquivo = obtemTamanhoArquivo(temp,"temp.txt");
     contBytes=0;
     temp = abreArquivo("temp.txt","rb","ERRO AO TENTAR ABRIR O TEMPORARIO!");  
     while (contBytes < tamanhoArquivo)
     {
           fread(cpfLido,sizeof(char)*MAX_CPF,1,temp);
           contador2 = achaClientePorCpf(arqCliente,cpfLido,contador2);
           contBytes = ftell(temp);
     }
     fclose(temp);
     remove("temp.txt");  
}
// Subprograma x           
//             Objetivo   : Criar um arquivo temporario.
//             Parametros : Endereço e ponteiro do cpf.
//             Retorno    : nenum.
void criaTempCpf(FILE *temp, char *pCpfAchado)
{
     long tamanhoArquivo,contBytes=0;
     char cpfLido[MAX_CPF];
     temp = abreArquivo("temp.txt","a+b","ERRO AO TENTAR ABRIR O TEMPORARIO!"); 
     fclose(temp);
     tamanhoArquivo = obtemTamanhoArquivo(temp,"temp.txt");
     temp = abreArquivo("temp.txt","r+b","ERRO AO TENTAR ABRIR O TEMPORARIO!"); 
     rewind(temp);
     while (contBytes < tamanhoArquivo)
     {
           fread(cpfLido,sizeof(char)*MAX_CPF,1,temp);
           if (strcmp(cpfLido,pCpfAchado)==0)
           {
                  fclose(temp);
                  return;
           }
           contBytes = ftell(temp);
     }
     fseek(temp,0,2);
     fwrite(pCpfAchado,sizeof(char)*MAX_CPF,1,temp);
     fclose(temp);
     return;
     
}
// Subprograma x           
//             Objetivo   : Subtrair uma data[COMPLETAR!]
//             Parametros : Ponteiro de Dia, Mes e Ano
//             Retorno    : Quantidade de dias.
void subtraiData(int *pDia,int *pMes,int *pAno,int qntDias)
{
     // Declarações
     int resultado,aux=0;
     // Instruções
     resultado = (pDia[1] - qntDias);
     if (resultado > 0)
     {
                   pDia[0] = resultado;
                   pMes[0] = pMes[1];
                   pAno[0] = pAno[1];
                   return;
     }
     if (resultado == 0)
     {
                    if (pMes[1] > 1)
                    {
                          pDia[0] = retornaMaxDiasMes(pMes[1]-1,pAno[1]);
                          pMes[0] = pMes[1]-1;
                          pAno[0] = pAno[1];
                          return;
                    }
                    if (pMes[1] == 1)
                    {
                                pDia[0] = retornaMaxDiasMes(12,pAno[1]-1);
                                pMes[0] = 12;
                                pAno[0] = pAno[1]-1;
                                return;
                    }
     }
}
// Subprograma x           
//             Objetivo   : Retornar o maximo de dias de um mês.
//             Parametros : Mes e ano.
//             Retorno    : Maximo de dias.
int retornaMaxDiasMes(int mes,int ano)  
{
    int bisexto=0;
    int meses[] = {31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
    bisexto = verificaAnoBisexto(ano);
    if (bisexto)
       meses[1] = 29;
    return meses[mes];
}
// Subprograma x           
//             Objetivo   : Ler todos os registros do arquivo e ordenar apenas os que batem com a condição.
//             Parametros : Endereço do aquivo de clientes e nome digitado.
//             Retorno    : Nenhum.
void ordenaPorNome(FILE *arq,char *pNomeDigitado)
{
     tipoFrequentador *pNomes = NULL,*pAux=NULL;
     long tamanhoArquivo,contBytes=0;
     int contador=0,dia,aux=0; 
     char nomeLido[TAM_NOME],nomeMaiusculo[TAM_NOME];
     tipoFrequentador estrutura;
     capsLock(pNomeDigitado);
     tamanhoArquivo = obtemTamanhoArquivo(arq,"cadastroClientes.txt");
    // pNomes = malloc((tamanhoArquivo/101)*101);
     pNomes = (tipoFrequentador*)malloc(tamanhoArquivo);
     arq = abreArquivo("cadastroClientes.txt","rb","ERRO AO TENTAR ODENAR O NOME DOS CLIENTES");
     while (contBytes < tamanhoArquivo)
     {
           //fseek(arq,sizeof(char)*MAX_CPF,1);
           //fread(nomeLido,sizeof(char)*TAM_NOME,1,arq);
           //capsLock(nomeLido);
           fread(&estrutura,sizeof(tipoFrequentador),1,arq);
           capsLock(estrutura.nome);
           if (strstr(estrutura.nome,pNomeDigitado))
           {
              fseek(arq,-1*sizeof(tipoFrequentador),1);
              /*fseek(arq,-1*((sizeof(char)*TAM_NOME)+(sizeof(char)*MAX_CPF)),1); //voltando ...
              fread(pNomes,sizeof(tipoFrequentador)-3,1,arq);
              fseek(arq,-1*(sizeof(int)*3),1);
              fread(&(*pNomes).dia,sizeof(int),1,arq);
              fread(&(*pNomes).mes,sizeof(int),1,arq);
              fread(&(*pNomes).ano,sizeof(int),1,arq);*/
              fread(pNomes,sizeof(tipoFrequentador),1,arq);
              contador++;
              pNomes++;
           }
           /*else
           {
                fseek(arq,sizeof(float)+sizeof(char)+sizeof(int)+sizeof(int)+sizeof(int),1);
           }*/                                            
           contBytes = ftell(arq);
     }  
     pNomes = pNomes - contador; 
     qsort(pNomes,contador,sizeof(tipoFrequentador),comparaString); 
     for(aux = 0;aux<contador;aux++)
     {
           //  fazListagemClientes(pNomes[aux].cpf,pNomes[aux].nome,pNomes[aux].peso,pNomes[aux].sexo,pNomes[aux].dia,pNomes[aux].mes,pNomes[aux].ano,aux);
           fazListagemClientes(pNomes,aux);
           pNomes++;
     }
     if (!contador)
     {
           nenhumDadoEncontrado();
     }
     getch();
}
// fim... xD
