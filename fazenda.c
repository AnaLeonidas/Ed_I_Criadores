#include <stdio.h>
#include <stdlib.h>
#include "criador.h"

Fazenda *criarFazenda()
{
    return NULL;
}
Fazenda *InserirFazenda(Fazenda *lista, int id)
{
    Animal *lista_animais = CriarAnimal();
    if(lista == NULL)
    {
        lista = PreencherFazenda(lista_animais, id);
        lista->next = lista;
    }
    else
    {
        Fazenda *aux_fazenda = lista;
        Fazenda *novaFazenda = PreencherFazenda(lista_animais, id);
        do
        {
            aux_fazenda = aux_fazenda->next;
        } while (aux_fazenda->next != lista);
        aux_fazenda->next = novaFazenda;
        novaFazenda->next = lista;
    }
    return lista;
}
Fazenda *PreencherFazenda(Animal *lista, int id)
{
    Fazenda *novaFazenda = AlocarFazenda(id);
    printf("Nome da fazenda: "); scanf(" %[^\n]", novaFazenda->nome);
    printf("Localizacao da fazenda: "); scanf(" %[^\n]", novaFazenda->localizacao);
    novaFazenda->rebanho = lista;
    return novaFazenda;
}
Fazenda *AlocarFazenda(int id)
{
    Fazenda *no = (Fazenda *) malloc(sizeof(Fazenda));
    if(no == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    no->id = id;
    return no;
}
Fazenda *BuscarFazenda(Fazenda *fazendas, int id)
{
    if(fazendas == NULL)
    {
        printf("Criador sem fazendas!\n\n");
    }
    else
    {
        Fazenda *aux = fazendas;
        do
        {
            if(aux->id == id)
            {
                return aux;
            }
            aux = aux->next;
        } while (aux != fazendas);
    }
    return NULL;
}
Fazenda *RemoverFazenda(Fazenda *fazendas, Fazenda *fazenda)
{
    Fazenda *aux = fazendas;
    int opcao;
    while (aux->next != fazenda)
    {
        aux = aux->next;
    }
    if(fazenda == fazendas)
    {
        if(fazenda->next == fazendas)
        {
            fazendas = NULL;
        }
        else
        {
            fazendas = fazenda->next;
            aux->next = fazendas;
        }
    }
    else
    {
        aux->next = fazenda->next;
    }
    GerenciarAnimaisFazenda(fazendas, fazenda);
    free(fazenda);
    return fazendas;
}
int BuscarId(Fazenda *lista, int id)
{
    int busca = 0;
    if (lista == NULL)
    {
        return busca;
    }
    else
    {
        Fazenda *aux = lista;
        do
        {
            if (aux->id == id) 
            {
                busca = 1;
                break;
            }
            aux = aux->next;
        }while (aux != lista); 
    }
    return busca; 
}
void GerenciarAnimaisFazenda(Fazenda *fazendas, Fazenda *fazendaRemovida)// Função para remover ou realocar o rebanho de uma fazenda removida para outra fazenda do criador
{
    int opcao;
    printf("Deseja remover ou realocar os animais da fazenda %d? (0 - REMOVER 1 - REALOCAR): ", fazendaRemovida->id); scanf("%d", &opcao);
    if (opcao == 0)
    {
        LiberarAnimais(fazendaRemovida->rebanho);
        fazendaRemovida->rebanho = NULL;
    } 
    else
    {
        int idFazenda;
        printf("Digite o ID da fazenda para realocar os animais: "); scanf("%d", &idFazenda);
        Fazenda *fazendaDestino = BuscarFazenda(fazendas, idFazenda);
        if (fazendaDestino != NULL)
        {
            Animal *animalAtual = fazendaRemovida->rebanho;
            while (animalAtual != NULL)// Percorre a lista de animais para remover e realocar cada um na fazenda de destino
            {
                Animal *proximoAnimal = animalAtual->next;
                fazendaRemovida->rebanho = RemoverAnimal(fazendaRemovida->rebanho, animalAtual, 0);
                fazendaDestino->rebanho = RealocarAnimal(fazendaDestino->rebanho, animalAtual);
                animalAtual = proximoAnimal;
            }
        } 
        else 
        {
            printf("Fazenda de destino nao encontrada.\n\n");
            LiberarAnimais(fazendaRemovida->rebanho);
            fazendaRemovida->rebanho = NULL;
        }
    }
}
void GerenciarFazenda(Fazenda *lista, Fazenda *fazenda)
{
    int opcao, IdAnimal, IdFazenda, busca;
    Animal *animal;
    Fazenda *destino;
    do
    {
        MenuFazenda(fazenda);
        printf("Selecione uma opcao: "); scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
            case 1:
                printf("Digite o ID do animal: "); scanf("%d", &IdAnimal);
                busca = BuscarIdAnimal(fazenda->rebanho, IdAnimal);
                if(busca != 1)
                {
                    fazenda->rebanho = AdicionarAnimal(fazenda->rebanho, IdAnimal);
                    printf("Animal cadastrado com sucesso!\n\n");
                }
                else
                {
                    printf("Esse ID ja esta cadastrado!\n\n");
                }
                break;
            case 2:
                printf("Digite o ID do animal para realocar: "); scanf("%d", &IdAnimal);
                printf("Digite o ID da fazenda de destino: "); scanf("%d", &IdFazenda);
                destino = BuscarFazenda(lista, IdFazenda);
                animal = BuscarAnimal(fazenda->rebanho, IdAnimal);
                if(animal != NULL && destino != NULL)
                {
                    if(animal->status == 3)
                    {
                        fazenda->rebanho = RemoverAnimal(fazenda->rebanho, animal, 0);
                        destino->rebanho = RealocarAnimal(destino->rebanho, animal);
                        animal->status = 0;
                        printf("Animal realocado com sucesso!\n\n");
                    }
                    else
                    {
                        printf("Animal nao pode ser realocado!\n\n");
                    }
                }
                else
                {
                    printf("Acesso negado, ID invalido\n\n");
                }
                break;
            case 3:
                printf("Digite o ID do animal para atualizar o status: "); scanf("%d", &IdAnimal);
                animal = BuscarAnimal(fazenda->rebanho, IdAnimal);
                if(animal != NULL)
                {
                    AtualizarStatusAnimal(animal);
                    printf("Status atualizado com sucesso!\n\n");
                }
                else
                {
                    printf("Acesso negado, ID invalido\n\n");
                }
                break;
            case 4:
                MostrarAnimais(fazenda->rebanho);
                break;
            case 5:
                printf("Digite o ID do animal para remover: "); scanf("%d", &IdAnimal);
                animal = BuscarAnimal(fazenda->rebanho, IdAnimal);
                if(animal != NULL)
                {
                    fazenda->rebanho = RemoverAnimal(fazenda->rebanho, animal, 1);
                    printf("Animal removido com sucesso!\n\n");
                }
                else
                {
                    printf("Acesso negado, ID invalido\n\n");
                }
                break;
            case 6:
                AtualizarFazenda(fazenda);
                printf("Fazenda atualizada!\n\n");
                break;
            case 7:
                printf("\nFechando fazenda...\n\n");
                break;
            default:
                break;
        } 
    } while (opcao != 7);
}
void MenuFazenda(Fazenda *fazenda)
{
    printf("--------------FAZENDA %d--------------\n1 - Adicionar Animal\n2 - Realocar Animal\n3 - Atualizar Status do Animal\n4 - Mostrar Animais\n5 - Remover Animal\n6 - Atualizar Fazenda\n7 - Fechar Fazenda\n", fazenda->id);
}
void AtualizarFazenda(Fazenda *fazenda)
{
    printf("\nNome atual da fazenda: %s\n", fazenda->nome);
    printf("Digite o novo nome da fazenda: ");scanf(" %[^\n]", fazenda->nome);
    printf("\n");
    printf("Localizacao atual da fazenda: %s\n", fazenda->localizacao);
    printf("Digite a nova localizacao da fazenda: ");scanf(" %[^\n]", fazenda->localizacao);
}
void MostrarFazendas(Fazenda *lista)//Lista as fazendas
{
    if (lista == NULL) 
    {
        printf("Lista vazia.\n");
        return;
    }
    Fazenda *aux = lista;
    printf("\n--------------FAZENDAS--------------\n");
    do 
    {
        printf("ID da fazenda: %d\n", aux->id);
        printf("Nome da fazenda: %s\n", aux->nome);
        printf("Localizacao da fazenda: %s\n", aux->localizacao);
        printf("\n");
        aux = aux->next;
    } while (aux != lista);
}
void LiberarFazendas(Fazenda *lista) 
{
    if (lista == NULL) return; 
    Fazenda *atual = lista;
    do {
        LiberarAnimais(atual->rebanho);
        Fazenda *prox = atual->next;
        free(atual);                
        atual = prox;                
    } while (atual != lista); 
}