#include <stdio.h>
#include <stdlib.h>
#include "criador.h"

Animal *CriarAnimal()
{
    return NULL;
}
Animal *AdicionarAnimal(Animal *lista, int id)
{
    Animal *novoAnimal = PreencherAnimal(id);
    lista = InserirAnimalNoFinal(lista, novoAnimal);
    return lista;
}
Animal *InserirAnimalNoFinal(Animal *lista, Animal *novoAnimal)
{
    if(lista == NULL)
    {
        lista = novoAnimal;
        lista->next = NULL;
    }
    else
    {
        Animal *aux_animal = lista;
        while (aux_animal->next != NULL)
        {
            aux_animal = aux_animal->next;
        }
        aux_animal->next = novoAnimal;
        novoAnimal->next = NULL;
    }
    return lista;
}
Animal *PreencherAnimal(int id)
{
    Animal *novoAnimal = AlocarAnimal(id);
    printf("Peso do animal: "); scanf("%f", &novoAnimal->peso);
    printf("Sexo do animal (M ou F): "); scanf(" %c", &novoAnimal->sexo);
    novoAnimal->status = StatusdoAnimal();
    return novoAnimal;
}
int StatusdoAnimal()
{
    int opcao;
    printf("--------------STATUS--------------\n0 - EM_CRIACAO\n1 - PARA_VENDA\n2 - VENDIDO\n3 - TROCA\n4 - NASCIMENTO\n"); 
    printf("Selecione a opcao: "); scanf("%d", &opcao);
    return opcao;
}
Animal *AlocarAnimal(int id)
{
    Animal *no = (Animal *) malloc(sizeof(Animal));
    if(no == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    no->id = id;
    return no;
}
Animal *BuscarAnimal(Animal *lista, int id)
{
    if(lista == NULL)
    {
        printf("Fazenda sem animais!\n\n");
    }
    else
    {
        Animal *aux = lista;
        while(aux != NULL)
        {
            if(aux->id == id)
            {
                return aux;
            }
            aux = aux->next;
        }
    }
    return NULL;
}
Animal *RemoverAnimal(Animal *lista, Animal *animal, int remover)
{
    if(animal == lista)
    {
        lista = animal->next;
    }
    else
    {
        Animal *aux = lista;
        while(aux->next != animal)
        {
            aux = aux->next;
        }
        aux->next = animal->next;
    }
    if(remover == 1)
    {
        free(animal);
    }
    return lista;
}
Animal *RealocarAnimal(Animal *listaDestino, Animal *animal)
{
    listaDestino = InserirAnimalNoFinal(listaDestino, animal);//Insere o animal removido da fazenda para a lista de destino
    return listaDestino;
}
int BuscarIdAnimal(Animal *lista, int id)
{
    int busca = 0;
    if (lista == NULL)
    {
        return busca;
    }
    else
    {
        Animal *aux = lista;
        while(aux != NULL)
        {
            if (aux->id == id) 
            {
                busca = 1;
                break;
            }
            aux = aux->next;
        }
    }
    return busca; 
}
int Filtros()//Função de filtragem de animais a partir de status, sexo ou peso
{
    int opcao;
    printf("--------------FILTROS--------------\n1 - Filtrar por status\n2 - Filtrar por sexo\n3 - Filtrar por intervalo de peso\n4 - Mostrar todos os animais\nDigite a opcao: "); scanf("%d", &opcao);
    return opcao;
}
void AtualizarStatusAnimal(Animal *animal)
{
    int novoStatus = StatusdoAnimal();
    int opcao;
    animal->status = novoStatus;
    printf("Deseja atualizar o peso do animal (0 - SIM 1 - NAO): "); scanf("%d", &opcao);
    if(opcao != 1)
    {
        printf("\nPeso atual do animal %d: %.2f\n", animal->id, animal->peso);
        printf("Digite o novo peso do animal: "); scanf("%f", &animal->peso);
        printf("\n");
    }
}
void MostrarAnimais(Animal *lista)// Lista os animais
{
    if (lista == NULL) 
    {
        printf("Lista vazia.\n");
        return;
    }
    int filtro = Filtros();
    Animal *aux = lista;
    printf("\n--------------ANIMAIS--------------\n");
    switch (filtro) 
    {
        case 1:
            int status;
            printf("Selecione o status para filtrar: "); scanf("%d", &status);
            while (aux != NULL) 
            {
                if (aux->status == status) 
                {
                    printf("ID do animal: %d\n", aux->id);
                    printf("Peso do animal: %.2f\n", aux->peso);
                    printf("Sexo do animal: %c\n", aux->sexo);
                    printf("Status do animal: %d\n", aux->status);
                    printf("\n");
                }
                aux = aux->next;
            }
            break;
        case 2: 
            char sexo;
            printf("Selecione o sexo para filtrar (M/F): "); scanf(" %c", &sexo);
            while (aux != NULL) 
            {
                if (aux->sexo == sexo) 
                {
                    printf("ID do animal: %d\n", aux->id);
                    printf("Peso do animal: %.2f\n", aux->peso);
                    printf("Sexo do animal: %c\n", aux->sexo);
                    printf("Status do animal: %d\n", aux->status);
                    printf("\n");
                }
                aux = aux->next;
            }
            break;
        case 3:
            float pesoMin, pesoMax;
            printf("Digite o peso minimo: ");scanf("%f", &pesoMin);
            printf("Digite o peso maximo: ");scanf("%f", &pesoMax);
            while (aux != NULL) 
            {
                if (aux->peso >= pesoMin && aux->peso <= pesoMax) 
                {
                    printf("ID do animal: %d\n", aux->id);
                    printf("Peso do animal: %.2f\n", aux->peso);
                    printf("Sexo do animal: %c\n", aux->sexo);
                    printf("Status do animal: %d\n", aux->status);
                    printf("\n");
                }
                aux = aux->next;
            }
            break;
        case 4:
            while (aux != NULL) 
            {
                printf("ID do animal: %d\n", aux->id);
                printf("Peso do animal: %.2f\n", aux->peso);
                printf("Sexo do animal: %c\n", aux->sexo);
                printf("Status do animal: %d\n", aux->status);
                printf("\n");
                aux = aux->next;
            }
            break;
        default:
            printf("Opcao invalida.\n");
    }
}
void LiberarAnimais(Animal *lista)
{
    Animal *aux;
    while(lista != NULL)
    {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}