#include <iostream>
#include <cstring>
#include <vector>
#include <limits>

#define ASSENTOS 40

using namespace std;

struct Data
{
    int dia;
    int mes;
    int ano;
    string data = "";
    string gera_data(Data);
};
struct Viagem
{
    int id;
    vector<int> poltronas;
    string origem;
    string destino;
    Data data;
    int hora; // vai ser numerado de 1 a 5 quando atingir 5 não vai mais poder cadastrar viagem
    // para a mesma hora e origem e destino
    bool Vazio = false;

    Viagem gera_viagem(int &);
    void imprime_viagem(Viagem viagem);
    bool poltronas_disponivel(int, Viagem);
};

struct Passagem
{
    int id_viagem;
    int assento;
    string nome;
    double preco;
    string cpf;
    int idade;

    void gera_passagem(Viagem viagem);
    void imprime_passagem();
};

int Menu();
int MenuViagem();
int MenuPassagem();

void limpaTela_palse();
void palse();
void limpaTela();
void ImprimirOnibus(vector<Passagem> passagens);
void ImprimirPoltronas();

int main()
{
    // Verifica o sistema operacional para não dar erro
    if (system("echo ''") != 0)
    {
        locale::global(locale(""));
        system("clear");
    }
    else
    {
        setlocale(LC_ALL, "Portuguese");
        system("cls");
    }
    vector<Passagem> passagens;
    Passagem aux_passagem;
    Viagem aux_viagem;
    vector<Viagem> viagens;
    int id_viagem = 0, opc, opc_m2;
    char resp;
    do
    {
        limpaTela();
        opc = Menu();
        switch (opc)
        {
        case 1:
            do
            {
                limpaTela();
                opc_m2 = MenuViagem();
                switch (opc_m2)
                {
                case 1:
                    do{
                        aux_viagem = aux_viagem.gera_viagem(id_viagem);
                        viagens.push_back(aux_viagem);
                        cout << "Viagem cadastrada com sucesso !" << endl;
                        cout << "Deseja cadastrar outra viagem? [S/N]: ";
                        cin >> resp;
                    } while (resp != 'n' && resp != 'N');
                    palse();
                    break;
                case 2:
                    if (!viagens.empty())
                    {
                        for (Viagem viagem : viagens)
                        {
                            aux_viagem.imprime_viagem(viagem);
                        }
                    }
                    else
                    {
                        cout << "Não ha viagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 0:
                    break;
                default:
                    cout << "Opcao invalida !" << endl;
                    cout << "Por favor, informe uma opcao valida !" << endl;
                    palse();
                }
                
            } while (opc_m2 != 0);
            break;
        case 0:
            break;
        default:
            cout << "Opcao invalida !" << endl;
            cout << "Por favor, informe uma opcao valida !" << endl;
            palse();
        }
        
    } while (opc != 0);

    return 0;
}

void palse()
{
    cout << "\nPressione a tecla Enter para continuar...\n";
    cin.sync();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void limpaTela()
{
    // Obtém o valor da variável de ambiente SHELL
    const char *shell = getenv("SHELL");

    if (shell != nullptr && strstr(shell, "bash") != nullptr)
    {
        // Se o shell for bash, use "clear"
        system("clear");
    }
    else
    {
        // Caso contrário, use "cls" (assumindo Windows)
        system("cls");
    }
}

void limpaTela_palse()
{
    palse();
    limpaTela();
}
Viagem Viagem::gera_viagem(int &id_viagem)
{
    cout.clear();
    Viagem viagem;
    viagem.id = id_viagem++;
    cout << "Digite a origem da viagem: ";
    cin >> viagem.origem;
    cout << "Digite o destino da viagem: ";
    cin >> viagem.destino;
    cout << "Digite o dia da viagem: ";
    cin >> viagem.data.dia;
    cout << "Digite o mes da viagem: ";
    cin >> viagem.data.mes;
    cout << "Digite o ano da viagem: ";
    cin >> viagem.data.ano;

    viagem.data.data = viagem.data.gera_data(viagem.data);

    return viagem;
}

void Viagem::imprime_viagem(Viagem viagem)
{
    cout.clear();
    cout << "ID: " << viagem.id << endl;
    cout << "Origem: " << viagem.origem << endl;
    cout << "Destino: " << viagem.destino << endl;
    cout << "Data: " << viagem.data.data << endl;
    cout << "---------------------" << endl;
}

void ImprimirOnibus(vector<Passagem> passagens)
{
    const int poltronasPorFileira = 2; // Número de poltronas por fileira
    const int corredor = 2;            // Largura do corredor entre as fileiras

    cout << "---------------------" << endl;
    cout << "       POLTRONAS       " << endl;
    cout << "---------------------" << endl;

    for (int poltrona = 1; poltrona <= ASSENTOS; ++poltrona)
    {
        bool ocupada = false;
        for (Passagem &passagem : passagens)
        {
            if (passagem.assento == poltrona)
            {
                ocupada = true;
                break;
            }
        }

        if (ocupada)
        {
            cout << "[X] "; // Poltrona ocupada
        }
        else
        {
            cout << "[ ] "; // Poltrona vazia
        }

        // Verifique se é necessário inserir o corredor
        if (poltrona % poltronasPorFileira == 0 && poltrona < ASSENTOS)
        {
            for (int i = 0; i < corredor; ++i)
            {
                cout << "   "; // Espaço do corredor
            }
        }

        // Quebra de linha a cada 4 poltronas para melhor visualização
        if (poltrona % (poltronasPorFileira * corredor) == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}

void ImprimirPoltronas()
{
    const int poltronasPorFileira = 2; // Número de poltronas por fileira
    const int corredor = 2;            // Largura do corredor entre as fileiras

    cout << "---------------------" << endl;
    cout << "       POLTRONAS       " << endl;
    cout << "---------------------" << endl;

    for (int poltrona = 1; poltrona <= ASSENTOS; ++poltrona)
    {

        cout << "[ ] "; // Poltrona vazia

        // Verifique se é necessário inserir o corredor
        if (poltrona % poltronasPorFileira == 0 && poltrona < ASSENTOS)
        {
            for (int i = 0; i < corredor; ++i)
            {
                cout << "   "; // Espaço do corredor
            }
        }

        // Quebra de linha a cada 4 poltronas para melhor visualização
        if (poltrona % (poltronasPorFileira * corredor) == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}

void Passagem::gera_passagem(Viagem viagem)
{

    Passagem passagem;
    int escolha_poltrona;
    cin >> escolha_poltrona;
    if (viagem.poltronas.size() < ASSENTOS)
    {
        cout << "Passagem nao disponivel" << endl;
    }
}

void Passagem::imprime_passagem()
{
}

string Data::gera_data(Data d)
{
    string s_data = to_string(d.dia) + "/" + to_string(d.mes) + "/" + to_string(d.ano);
    return s_data;
}

int Menu()
{
    int opc;
    cout << "########## MENU PRINCIPAL ##########" << endl;
    cout << "1 - Geremciar Viagem" << endl;
    cout << "2 - Gerenciar Passagem" << endl;
    cout << "0 - Sair" << endl;

    cout << "Escolha uma opcao: ";
    cin >> opc;

    return opc;
}

int MenuViagem()
{
    int opc;
    cout << "########## MENU VIAGEM ##########" << endl;
    cout << "1 - Cadastrar Viagem" << endl;
    cout << "2 - Listar Viagens" << endl;
    cout << "3 - Total arrecadado" << endl;
    cout << "4 - Total arrecadado por mes" << endl;
    cout << "5 - Horario mais rentavel" << endl;
    cout << "6 - Media de idade dos passageiros" << endl;
    cout << "0 - Voltar ao Menu Principal" << endl;

    cout << "Escolha uma opcao: ";
    cin >> opc;

    return opc;
}

int MenuPassagem()
{
    int opc;
    cout << "########## MENU PASSAGEM ##########" << endl;
    cout << "1 - Cadastrar Passagem" << endl;
    cout << "2 - Listar Passagem" << endl;
    cout << "0 - Voltar ao Menu Principal" << endl;

    cout << "Escolha uma opcao: ";
    cin >> opc;

    return opc;
}