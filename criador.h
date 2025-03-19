#include "fazenda.h"
typedef struct criador Criador;
struct criador 
{
    char nome[100];
    char cpf[15];
    float patrimonio;
    Fazenda *fazendas;
    Criador *prev;
    Criador *next;
};
Criador *CriarCriador();
Criador *InserirCriador(Criador *lista, const char *cpf);
Criador *PreencherCriador(const char *cpf, Fazenda *lista_fazendas);
Criador *Alocar(const char *cpf);
Criador *BuscarCriador(Criador *lista, const char *cpf);
Criador *RemoverCriador(Criador *lista, Criador *criador);
float AtualizarPatrimonio(Fazenda *fazendas);
int BuscarCPF(Criador *lista, const char *cpf);
int ContarAnimais(Fazenda *fazendas);
void AcessarCriador(Criador *lista, Criador *criador);
void MenuCriador(Criador *criador);
void Patrimonio(Criador *criador);
void MostrarCriadores(Criador *lista);
void LiberarCriadores(Criador *lista);