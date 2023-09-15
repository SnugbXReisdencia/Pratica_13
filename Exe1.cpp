# include <iostream>
# include <string>
# include <vector>

# define ASSENTOS 40

using namespace std;

struct Passagem
{
    int id;
    int assento;
    string nome;
    double preco;
    string cpf;
    int idade;

    void gera_passagem(Viagem viagem);
    void imprime_passagem();
};

struct Viagem
{
    int id;
    vector<int> poltronas;
    string origem;
    string destino;
    int dia;
    int mes;
    int ano;

    Viagem gera_viagem();
    void imprime_viagem();
    bool poltronas_disponivel(int, Viagem);
};

int main(){
    return 0;
}

Viagem Viagem::gera_viagem(){
    Viagem viagem;

    cout << "Digite o id da viagem: ";
    cin >> viagem.id;
    cout << "Digite a origem da viagem: ";
    cin >> viagem.origem;
    cout << "Digite o destino da viagem: ";
    cin >> viagem.destino;
    cout << "Digite o dia da viagem: ";
    cin >> viagem.dia;
    cout << "Digite o mes da viagem: ";
    cin >> viagem.mes;
    cout << "Digite o ano da viagem: ";
    cin >> viagem.ano;

    return viagem;
}

void Viagem::imprime_viagem(){
    
}

bool Viagem::poltronas_disponivel(int assento, Viagem viagem){
    if (assento > viagem.poltronas.size())
    {
        return false;

    }else{
    
        if (viagem.poltronas[assento] == -1)
        {
            return true;
        }else{
            return false;
        }
    }
}
void Passagem::gera_passagem(Viagem viagem){
    
    Passagem passagem;
    int escolha_poltrona;
    
    if (viagem.poltronas.size() < ASSENTOS)
    {

    }
    
}

void Passagem::imprime_passagem(){
    
}