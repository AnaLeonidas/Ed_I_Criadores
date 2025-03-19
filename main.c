#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "criador.h"

void Menu();
int main() 
{
    Criador *listaCriadores = CriarCriador();
    int opcao, busca;
    char cpf[15];
    do
    {
        Menu();
        printf("Selecione uma opcao: "); scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
            case 1:
                printf("Digite o cpf do criador: "); scanf(" %[^\n]", cpf);
                busca = BuscarCPF(listaCriadores, cpf);//Função para verificar a existência do cadastro pelo CPF
                if(busca != 1)
                {
                    listaCriadores = InserirCriador(listaCriadores, cpf);
                    printf("Criador cadastrado com sucesso!\n\n");
                }
                else
                {
                    printf("Esse CPF ja esta cadastrado!\n\n");
                }
                break;
            case 2:
                printf("Digite o cpf do criador: "); scanf(" %[^\n]", cpf);
                Criador *criador = BuscarCriador(listaCriadores, cpf); //Função para retornar o criador para acesso
                if(criador != NULL)
                {
                    AcessarCriador(listaCriadores, criador);//Função para manusear operações do criador individualmente
                }
                else
                {
                    printf("Acesso negado, CPF invalido!\n\n");
                }
                break;
            case 3:
                MostrarCriadores(listaCriadores);
                break;
            case 4:
                printf("Digite o cpf do criador: "); scanf(" %[^\n]", cpf);
                criador = BuscarCriador(listaCriadores, cpf);
                if(criador != NULL)
                {
                    listaCriadores = RemoverCriador(listaCriadores, criador);
                    printf("Criador removido com sucesso!\n\n");
                }
                else
                {
                    printf("Acesso negado, CPF invalido!\n\n");
                }
                break;
            case 5:
                LiberarCriadores(listaCriadores);
                printf("Saindo...\n");
                break;
            default:
                break;
        }
    }while(opcao != 5);
    return 0;
}
void Menu()
{
	printf("--------------MENU PRINCIPAL--------------\n1 - Cadastrar Criador\n2 - Acessar Criador\n3 - Mostrar Criadores\n4 - Remover Criador\n5 - Sair\n");
}

