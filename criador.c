#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "criador.h"

Criador *CriarCriador()
{
    return NULL;
}
Criador *InserirCriador(Criador *lista, const char *cpf)
{
    Criador *aux = lista;
    Fazenda *lista_fazendas = criarFazenda();
    if(lista == NULL)
    {
        lista = PreencherCriador(cpf, lista_fazendas);
        lista->next = lista;
        lista->prev = lista;
    }
    else
    {
        do
        {
            aux = aux->next;
        } while (aux != lista);
        Criador *novoCriador;
        novoCriador = PreencherCriador(cpf, lista_fazendas);
        novoCriador->next = lista;
        novoCriador->prev = lista->prev;
        lista->prev->next = novoCriador;
        lista->prev = novoCriador;
    }
    return lista;
}
Criador *PreencherCriador(const char *cpf, Fazenda *lista_fazendas)
{
    Criador *novoCriador = Alocar(cpf);
    printf("Nome: "); scanf(" %[^\n]", novoCriador->nome);
    novoCriador->patrimonio = 0;
    novoCriador->fazendas = lista_fazendas;
    return novoCriador;
}
Criador *Alocar(const char *cpf)
{
    Criador *no = (Criador *) malloc(sizeof(Criador));
    if (no == NULL) 
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(no->cpf, cpf);
    return no;
}
Criador *BuscarCriador(Criador *lista, const char *cpf)
{
    if (lista == NULL) 
    {
        printf("Lista vazia.\n\n");
    }
    else
    {
        Criador *aux = lista;
        do
        {
            if (strcmp(aux->cpf, cpf) == 0) 
            {
                return aux;
            }
            aux = aux->next; 
        }while (aux != lista); 
    }
    return NULL; 
}
Criador *RemoverCriador(Criador *lista, Criador *criador)
{
    if (lista->next == lista)
    {
        LiberarFazendas(criador->fazendas);
        free(criador);
        return NULL; 
    }
    else if(criador == lista)
    {
        lista->prev->next = criador->next;
        criador->next->prev = lista->prev;
        lista = criador->next;
    }
    else 
    {
        criador->prev->next = criador->next;
        criador->next->prev = criador->prev;
    }
    LiberarFazendas(criador->fazendas);
    free(criador);
    return lista;
}
float AtualizarPatrimonio(Fazenda *fazendas)//Função para atualizar o patrimônio do criador através da multiplicação da contagem de animais pelo valor
{
    int quantidade = ContarAnimais(fazendas);
    return 500 * quantidade;
}
int BuscarCPF(Criador *lista, const char *cpf)
{
    int busca = 0;
    if (lista == NULL)
    {
        return busca;
    }
    else
    {
        Criador *aux = lista;
        do
        {
            if (strcmp(aux->cpf, cpf) == 0) 
            {
                busca = 1;
                break;
            }
            aux = aux->next;
        }while (aux != lista); 
    }
    return busca; 
}
int ContarAnimais(Fazenda *fazendas) //Função para contar os animais de todas as fazendas de um criador
{
    int totalAnimais = 0;
    Fazenda *fazendaAtual = fazendas;
    if (fazendas != NULL) 
    {
        do 
        {
            Animal *animalAtual = fazendaAtual->rebanho;
            while (animalAtual != NULL) //Percorre todos os animais
            {
                totalAnimais++;
                animalAtual = animalAtual->next;
            }
            fazendaAtual = fazendaAtual->next;
        } while (fazendaAtual != fazendas); //Percorre todas as fazendas
    }
    return totalAnimais;
}
void AcessarCriador(Criador *lista, Criador *criador)
{
    int opcao, idFazenda, idFazendaDestino, idAnimal, busca;
    char cpf[15];
    Criador *comprador;
    Fazenda *fazenda, *fazendaDestino;
    Animal *animal;
    do
    {
        MenuCriador(criador);
        printf("Selecione uma opcao: "); scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
            case 1:
                printf("Digite o ID da fazenda: "); scanf("%d", &idFazenda);
                busca = BuscarId(criador->fazendas, idFazenda);//Função para verificar a existência do cadastro pelo ID
                if(busca != 1)
                {
                    criador->fazendas = InserirFazenda(criador->fazendas, idFazenda);
                    printf("Fazenda cadastrada com sucesso!\n\n");
                }
                else
                {
                    printf("Esse ID ja esta cadastrado!\n\n");
                }
                break;
            case 2:
                printf("Digite o ID da fazenda: "); scanf("%d", &idFazenda);
                fazenda = BuscarFazenda(criador->fazendas, idFazenda);//Função para retornar a fazenda para gerenciar.
                if(fazenda != NULL)
                {
                    GerenciarFazenda(criador->fazendas, fazenda);//Função para manusear operações da fazenda individualmente
                    criador->patrimonio = AtualizarPatrimonio(criador->fazendas); 
                }
                else
                {
                    printf("Acesso negado, ID invalido\n\n");
                }
                break;
            case 3:
                MostrarFazendas(criador->fazendas);
                break;
            case 4:
                printf("Digite o ID da fazenda: "); scanf("%d", &idFazenda);
                fazenda = BuscarFazenda(criador->fazendas, idFazenda);
                if(fazenda != NULL)
                {
                    criador->fazendas = RemoverFazenda(criador->fazendas, fazenda);
                    printf("Fazenda removida com sucesso!\n\n");
                    criador->patrimonio = AtualizarPatrimonio(criador->fazendas);
                }
                else
                {
                    printf("Acesso negado, ID invalido\n\n");
                }
                break;
            case 5:
                printf("Digite o ID da fazenda de origem: "); scanf("%d", &idFazenda);
                fazenda = BuscarFazenda(criador->fazendas, idFazenda);
                if(fazenda != NULL)
                {
                    printf("Digite o ID do animal para venda: "); scanf("%d", &idAnimal);
                    animal = BuscarAnimal(fazenda->rebanho, idAnimal);//Função para retornar o animal para gerenciar.
                    if (animal != NULL && animal->status == 1)
                    {
                        printf("Digite o cpf do criador de destino: "); scanf(" %[^\n]", cpf);
                        comprador = BuscarCriador(lista, cpf);
                        if(comprador != NULL)
                        {
                            printf("Digite o ID da fazenda de destino: "); scanf("%d", &idFazendaDestino);
                            fazendaDestino = BuscarFazenda(comprador->fazendas, idFazendaDestino);
                            if(fazendaDestino != NULL)
                            {
                                fazenda->rebanho = RemoverAnimal(fazenda->rebanho, animal, 0);
                                fazendaDestino->rebanho = RealocarAnimal(fazendaDestino->rebanho, animal);
                                animal->status = 2;
                                printf("\nVenda realizada com sucesso!\n\n");
                                criador->patrimonio = AtualizarPatrimonio(criador->fazendas);
                                comprador->patrimonio = AtualizarPatrimonio(comprador->fazendas);
                            }
                        }
                    }
                }
                else 
                {
                    printf("Venda nao realizada devido a falha nas verificacoes.\n\n");
                }
                break;
            case 6:
                Patrimonio(criador);
                break;
            case 7:
                printf("Fechando criador...\n\n");
                break;
            default:
                break;
            }
        } while (opcao != 7);
}
void MenuCriador(Criador *criador)
{
    printf("--------------CRIADOR %s--------------\n1 - Adicionar Fazenda\n2 - Gerenciar Fazenda\n3 - Mostrar Fazendas\n4 - Remover Fazenda\n5 - Vender Animal\n6 - Patrimonio\n7 - Fechar Criador\n", criador->nome);
}
void Patrimonio(Criador *criador)//Apresenta o patrimonio do criador especifico
{
    int quantidade = ContarAnimais(criador->fazendas);
    printf("Nome do criador: %s\n", criador->nome);
    printf("CPF do criador: %s\n", criador->cpf);
    printf("Patrimonio do criador: %.2f\n", criador->patrimonio);
    printf("Quantidade de animais: %d\n", quantidade);
    printf("\n");
}
void MostrarCriadores(Criador *lista)//Lista os criadores
{
    if (lista == NULL) 
    {
        printf("Lista vazia.\n");
        return;
    }
    Criador *aux = lista;
    printf("\n--------------CRIADORES--------------\n");
    do 
    {
        printf("Nome do criador: %s\n", aux->nome);
        printf("CPF do criador: %s\n", aux->cpf);
        printf("Patrimonio do criador: %.2f\n", aux->patrimonio);
        printf("\n");
        aux = aux->next;
    } while (aux != lista);
}
void LiberarCriadores(Criador *lista) 
{
    if(lista == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }
    Criador *atual = lista;
    do
    {
        Criador *prox = atual->next; 
        LiberarFazendas(atual->fazendas); 
        free(atual);                      
        atual = prox;                     
    } while (atual != lista); 
}