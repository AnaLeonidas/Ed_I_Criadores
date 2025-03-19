#include "animal.h"
typedef struct fazenda Fazenda;
struct fazenda 
{
    int id;
    char nome[100];
    char localizacao[100];
    Animal *rebanho; 
    Fazenda *next;   
};
Fazenda *criarFazenda();
Fazenda *InserirFazenda(Fazenda *fazendas, int id);
Fazenda *PreencherFazenda(Animal *lista, int id);
Fazenda *AlocarFazenda(int id);
Fazenda *BuscarFazenda(Fazenda *fazendas, int id);
Fazenda *RemoverFazenda(Fazenda *fazendas, Fazenda *fazenda);
int BuscarId(Fazenda *lista, int id);
void GerenciarAnimaisFazenda(Fazenda *fazendas, Fazenda *fazendaRemovida);
void GerenciarFazenda(Fazenda *lista, Fazenda *fazenda);
void MenuFazenda(Fazenda *fazenda);
void AtualizarFazenda(Fazenda *fazenda);
void MostrarFazendas(Fazenda *lista);
void LiberarFazendas(Fazenda *lista);