typedef enum 
{
    EM_CRIACAO,
    PARA_VENDA,
    VENDIDO,
    TROCA,
    NASCIMENTO
} StatusAnimal;
typedef struct animal Animal;
struct animal
{
    int id;
    float peso;
    char sexo;
    StatusAnimal status;
    Animal *next; 
};
Animal *CriarAnimal();
Animal *AdicionarAnimal(Animal *lista, int id);
Animal *InserirAnimalNoFinal(Animal *lista, Animal *novoAnimal);
Animal *PreencherAnimal(int id);
Animal *AlocarAnimal(int id);
Animal *BuscarAnimal(Animal *lista, int id);
Animal *RemoverAnimal(Animal *lista, Animal *animal, int remover);
Animal *RealocarAnimal(Animal *listaDestino, Animal *animal);
int BuscarIdAnimal(Animal *lista, int id);
int StatusdoAnimal();
int Filtros();
void AtualizarStatusAnimal(Animal *animal);
void MostrarAnimais(Animal *lista);
void LiberarAnimais(Animal *lista);