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

    string data;
    string data_Estenco;

    bool validarData(Data data, bool atual);
    int idade();
};

Data gera_data(bool atual);

struct Horario
{
    string horario;
    double preco;
};

struct Data_hora_Viagem
{
    int hora;
    Data data;
};

struct Viagem
{
    int id;
    vector<int> poltronas;
    string origem;
    string destino;
    Data_hora_Viagem dataHora;
    bool Vazio = true;

    Viagem gera_viagem(int &, vector<Horario>);
    void static imprime_viagem(Viagem viagem, vector<Horario>);
    bool poltronas_disponivel(int, Viagem);
};

bool verificaViagem(Viagem, vector<Viagem>);

struct Passagem
{
    int id_viagem;
    Data_hora_Viagem dataHora;
    int assento;
    string nome;
    string cpf;
    int idade;
    double preco;
    bool Vazio = true;

    Passagem gera_passagem(vector<Viagem> viagens, vector<Horario> horarios, vector<Passagem> passagens);
    void static imprime_passagem(Passagem p, vector<Horario> horarios);
};

int Menu();
int MenuViagem();
int MenuPassagem();
int MenuHorario(vector<Horario> horarios);

void limpaTela_palse();
void palse();
void limpaTela();

void ImprimirOnibus(vector<Passagem> passagens, Viagem viagem);
void ImprimirPoltronas();
double total_arrecadado_Viagem(vector<Passagem> passagens, Viagem viagem);
double total_arrecadadoMes(vector<Passagem> passagens, vector<Viagem> viagens, int mes);
Passagem busca_passageiro_poltrona(vector<Passagem> passagens, int poltrona, Viagem viagem);
string nome_passageiro_poltrona(vector<Passagem> passagens, Viagem viagem, int poltrona);
double media_idade(vector<Passagem> passagens);
void HorarioMaisRentavel(vector<Horario> horarios, vector<Viagem> viagens, vector<Passagem> passagens);

int main()
{
    vector<Horario> horarios = {
        {"10:00", 80.0},
        {"12:00", 80.0},
        {"14:00", 80.0},
        {"17:00", 80.0},
        {"20:00", 80.0}};
    vector<Passagem> passagens;
    Passagem aux_passagem;
    Viagem aux_viagem;
    vector<Viagem> viagens;
    int id_viagem = 0, opc, opc_m2, aux_int, aux_int2;
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
                    do
                    {
                        limpaTela();
                        int(viagens.size()) == 0 ? id_viagem = 0 : id_viagem = int(viagens.size());
                        aux_viagem = aux_viagem.gera_viagem(id_viagem, horarios);
                        if (verificaViagem(aux_viagem, viagens))
                        {
                            viagens.push_back(aux_viagem);
                            cout << "Viagem cadastrada com sucesso !" << endl;
                            palse();
                        }
                        else
                        {
                            cout << "Viagem não cadastrada !\nLimite de viagens atingido para esse dia e horário " << endl;
                            palse();
                        }

                        cout << "Deseja cadastrar outra viagem? [S/N]: ";
                        cin >> resp;
                    } while (resp != 'n' && resp != 'N');

                    break;
                case 2:
                    limpaTela();
                    if (!viagens.empty())
                    {
                        for (Viagem viagem : viagens)
                        {
                            Viagem::imprime_viagem(viagem, horarios);
                        }
                    }
                    else
                    {
                        cout << "Não ha viagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 3:
                    limpaTela();
                    if (!viagens.empty())
                    {
                        if (!passagens.empty())
                        {
                            for (Viagem viagem : viagens)
                            {
                                Viagem::imprime_viagem(viagem, horarios);
                            }
                            cout << "\nInforme o ID da viagem: ";
                            cin >> aux_int;
                            aux_int >= 0 && aux_int < int(viagens.size()) ? cout << "Total arrecadado: " << total_arrecadado_Viagem(passagens, viagens[aux_int]) << endl : cout << "Viagem não consta na lista ! \nPor favor, informe os dados corretos !" << endl;
                        }
                        else
                        {
                            cout << "Não ha passagens cadastradas" << endl;
                        }
                    }
                    else
                    {
                        cout << "Não ha viagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 4:
                    limpaTela();
                    if (!viagens.empty())
                    {
                        if (!passagens.empty())
                        {
                            cout << "\nInforme o mes da viagem: ";
                            cin >> aux_int;
                            if (aux_int > 0 && aux_int <= 12)
                            {
                                cout << "Total arrecadado: " << total_arrecadadoMes(passagens, viagens, aux_int) << endl;
                            }
                            else
                            {
                                cout << "Mes invalido" << endl;
                            }
                        }
                        else
                        {
                            cout << "Não ha passagens cadastradas" << endl;
                        }
                    }
                    else
                    {
                        cout << "Não ha viagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 5:
                    limpaTela();
                    if (!viagens.empty())
                    {
                        if (!passagens.empty())
                        {
                            for (Viagem viagem : viagens)
                            {
                                Viagem::imprime_viagem(viagem, horarios);
                            }
                            cout << "\nInforme o ID da viagem: ";
                            cin >> aux_int;
                            cout << "Informe a poltrona: ";
                            cin >> aux_int2;
                            aux_int2 > 0 && aux_int2 <= ASSENTOS &&aux_int >= 0 && aux_int < int(viagens.size()) ? cout << "Nome do passageiro: " << nome_passageiro_poltrona(passagens, viagens[aux_int], aux_int2) << endl : cout << "Poltrona ou viagem invalida ! \nPor favor, informe os dados corretos !" << endl;
                        }
                        else
                        {
                            cout << "Não ha passagens cadastradas" << endl;
                        }
                    }
                    else
                    {
                        cout << "Não ha viagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 6:
                    limpaTela();
                    if (!viagens.empty())
                    {
                        if (!passagens.empty())
                        {
                            HorarioMaisRentavel(horarios, viagens, passagens);
                        }
                        else
                        {
                            cout << "Não ha passagens cadastradas" << endl;
                        }
                    }
                    else
                    {
                        cout << "Não ha viagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 7:
                    limpaTela();
                    if (!passagens.empty())
                    {
                        cout << "\nMedia de idade dos passageiros: " << media_idade(passagens) << endl;
                    }
                    else
                    {
                        cout << "Não ha passagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 0:
                    break;
                default:
                    limpaTela();
                    cout << "Opcao invalida !" << endl;
                    cout << "Por favor, informe uma opcao valida !" << endl;
                    palse();
                }

            } while (opc_m2 != 0);
            break;
        case 2:
            limpaTela();
            if (viagens.empty())
            {
                cout << "Não ha viagens cadastradas" << endl;
                cout << "Por favor, É necessário no minimo uma viagem antes de cadastrar uma passagem !" << endl;
                palse();
                break;
            }
            do
            {
                limpaTela();
                opc_m2 = MenuPassagem();
                switch (opc_m2)
                {
                case 1:
                    do{
                        limpaTela();
                        aux_passagem = aux_passagem.gera_passagem(viagens, horarios, passagens);
                        if(aux_passagem.Vazio == false){
                            passagens.push_back(aux_passagem);
                            cout << "Passagem registrada com sucesso !" << endl;
                        }else{
                            cout << "Nao foi possivel realizar o registro da passagem !" << endl;
                        }

                        cout << "Deseja cadastrar outra passagem? [S/N]: ";
                        cin >> resp;
                    }while(resp != 'n' && resp != 'N');
                    palse();
                    break;
                case 2:
                    limpaTela();
                    if (!passagens.empty())
                    {
                        for (Passagem passagem : passagens)
                        {
                            Passagem::imprime_passagem(passagem, horarios);
                        }
                    }
                    else
                    {
                        cout << "Não ha passagens cadastradas" << endl;
                    }
                    palse();
                    break;
                case 0:
                    break;
                default:
                    limpaTela();
                    cout << "Opcao invalida !" << endl;
                    cout << "Por favor, informe uma opcao valida !" << endl;
                    palse();
                }
            } while (opc_m2 != 0);
            break;
        case 0:
            break;
        default:
            limpaTela();
            cout << "Opcao invalida !" << endl;
            cout << "Por favor, informe uma opcao valida !" << endl;
            palse();
        }

    } while (opc != 0);

    return 0;
}

void palse()
{
    cin.ignore();
    cout << "\nPressione a tecla Enter para continuar...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void limpaTela()
{
    cin.clear();

    // Verifica se a variável de ambiente WINDIR está definida (ambiente Windows)
    const char *windir = getenv("WINDIR");

    if (windir != nullptr && strlen(windir) > 0)
    {
        // Se estiver definida, estamos no Windows, então use "cls"
        system("cls");
    }
    else
    {
        // Caso contrário, estamos em um ambiente Unix/Linux, use "clear"
        system("clear");
    }
}

void limpaTela_palse()
{
    palse();
    limpaTela();
}

void limparBuffers()
{
    // Limpa o buffer de entrada do cin
    cin.clear();
    // Limpa o buffer de saída do cout
    cout.flush();
}

bool Data::validarData(Data data, bool atual)
{
    // Obter o tempo atual
    time_t tempoAtual = time(nullptr);

    // Converter o tempo atual para uma estrutura tm
    tm *infoTempo = localtime(&tempoAtual);

    // Obter o ano atual (adicione 1900 ao campo tm_year)
    int anoAtual = infoTempo->tm_year + 1900;

    // Verifica se o ano é válido (entre 1900 e o ano atual)
    if (atual)
    {
        if (data.ano < 1900 || data.ano > anoAtual)
        {
            return false;
        }
    }
    else
    {
        if (data.ano < 1800)
        {
            return false;
        }
    }

    // Verifica se o mês está dentro do intervalo de 1 a 12
    if (data.mes < 1 || data.mes > 12)
    {
        return false;
    }

    // Verifica o número de dias com base no mês (considerando anos bissextos)
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Verifica se é um ano bissexto
    if ((data.ano % 4 == 0 && data.ano % 100 != 0) || (data.ano % 400 == 0))
    {
        diasNoMes[2] = 29; // Fevereiro tem 29 dias em anos bissextos
    }

    // Verifica se o dia está dentro do intervalo válido para o mês
    if (data.dia < 1 || data.dia > diasNoMes[data.mes])
    {
        return false;
    }

    // Se passou por todas as verificações, a data é válida
    return true;
}

Data gera_data(bool atual)
{
    Data data;
    bool valido;
    string meses[] = {
        "janeiro", "fevereiro", "março", "abril",
        "maio", "junho", "julho", "agosto",
        "setembro", "outubro", "novembro", "dezembro"};

    do
    {
        cout << "Digite a data no formato(dd/mm/aaaa): ";
        cin >> data.dia;
        cin.ignore();
        cin >> data.mes;
        cin.ignore();
        cin >> data.ano;

        valido = data.validarData(data, atual);

        if (!valido)
        {
            limpaTela();
            cout << "Data inválida !!" << endl;
            cout << "Por favor, digite uma data valida!" << endl;
            limparBuffers();
        }
    } while (!valido);
    data.data = to_string(data.dia) + "/" + to_string(data.mes) + "/" + to_string(data.ano);
    data.data_Estenco = to_string(data.dia) + " de " + meses[data.mes - 1] + " de " + to_string(data.ano);
    return data;
}

int Data::idade()
{
    time_t tempo_atual = time(nullptr);
    tm *infoTempo = localtime(&tempo_atual);
    int ano_atual = infoTempo->tm_year + 1900;
    return ano_atual - ano;
}

int MenuHorario(vector<Horario> horarios)
{
    int opc;
    cout << "########## HORÁRIOS DISPONÍVEIS ##########" << endl;
    for (size_t i = 0; i < horarios.size(); i++)
    {
        cout << i + 1 << " = às " << horarios[i].horario << " - Preço: R$" << horarios[i].preco << endl;
    }
    cout << "Escolha uma opção: ";
    cin >> opc;

    return opc;
}

bool verificaViagem(Viagem viagem, vector<Viagem> viagens)
{
    // Verifica se a viagem é valida para ser cadastrada
    int contIda = 0, contVolta = 0, qtd_ida = 5, qtd_volta = 5;

    for (size_t i = 0; i < viagens.size(); i++)
    {
        if (viagem.dataHora.data.data == viagens[i].dataHora.data.data)
        {
            if (viagem.origem == viagens[i].origem)
            {
                if (viagem.destino == viagens[i].destino)
                {
                    if (viagem.dataHora.hora == viagens[i].dataHora.hora)
                    {
                        return false;
                    }
                    contIda++;
                }
            }
            else if (viagem.origem == viagens[i].destino)
            {
                if (viagem.destino == viagens[i].origem)
                {
                    if (viagem.dataHora.hora == viagens[i].dataHora.hora)
                    {
                        return false;
                    }
                    contVolta++;
                }
            }
        }
    }
    if (contIda >= qtd_ida || contVolta >= qtd_volta)
    {
        return false;
    }

    return true;
}

Viagem Viagem::gera_viagem(int &id_viagem, vector<Horario> horarios)
{
    cout.clear();
    int opcao;
    Viagem viagem;
    viagem.id = id_viagem;
    cout << "Digite a origem da viagem: ";
    cin.ignore();
    getline(cin, viagem.origem);
    cout << "Digite o destino da viagem: ";
    getline(cin, viagem.destino);
    viagem.dataHora.data = gera_data(true);
    do
    {
        opcao = MenuHorario(horarios);
        switch (opcao)
        {
        case 1:
            viagem.dataHora.hora = 0;
            break;
        case 2:
            viagem.dataHora.hora = 1;
            break;
        case 3:
            viagem.dataHora.hora = 2;
            break;
        case 4:
            viagem.dataHora.hora = 3;
            break;
        case 5:
            viagem.dataHora.hora = 4;
            break;
        default:
            cout << "Horario indisponível !" << endl;
            cout << "Por favor, informe uma opcao valida !" << endl;
            palse();
        }
    } while (opcao < 0 || opcao > 5);
    viagem.Vazio = false;
    return viagem;
}

void Viagem::imprime_viagem(Viagem viagem, vector<Horario> Horarios)
{
    cout.clear();
    cout << "ID: " << viagem.id << endl;
    cout << "Origem: " << viagem.origem << endl;
    cout << "Destino: " << viagem.destino << endl;
    cout << "Data: " << viagem.dataHora.data.data_Estenco << endl;
    cout << "Horario: " << Horarios[viagem.dataHora.hora].horario << endl;
    cout << "Preco: R$" << Horarios[viagem.dataHora.hora].preco << endl;
    cout << "---------------------" << endl;
}

void ImprimirOnibus(vector<Passagem> passagens, Viagem viagem)
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
            if (passagem.id_viagem == viagem.id && passagem.assento == poltrona)
            {
                ocupada = true;
                break;
            }
        }

        if (ocupada)
        {
            if (poltrona < 10)
            {
                cout << '0' << poltrona << " [X] "; // Poltrona Ocupada
            }
            else
            {
                cout << poltrona << " [X] "; // Poltrona Ocupada
            }
        }
        else
        {
            if (poltrona < 10)
            {
                cout << '0' << poltrona << " [ ] "; // Poltrona vazia
            }
            else
            {
                cout << poltrona << " [ ] "; // Poltrona vazia
            }
        }

        // Verifique se é necessário inserir o corredor
        if (poltrona % poltronasPorFileira == 0 && poltrona < ASSENTOS)
        {
            for (int i = 0; i < corredor; ++i)
            {
                cout << "  "; // Espaço do corredor
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
        if (poltrona < 10)
        {
            cout << '0' << poltrona << " [ ] "; // Poltrona vazia
        }
        else
        {
            cout << poltrona << " [ ] "; // Poltrona vazia
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

Passagem Passagem::gera_passagem(vector<Viagem> viagens, vector<Horario> horarios, vector<Passagem> passagens)
{
    Passagem passagem, aux_passagem;
    int aux_int, aux_int2;
    bool aux_bool = true;

    for (Viagem viagem : viagens)
    {
        Viagem::imprime_viagem(viagem, horarios);
    }
    cout << "\nInforme o ID da viagem: ";
    cin >> aux_int;
    limpaTela();
    if (aux_int >= 0 && aux_int < int(viagens.size()))
    {
        if (int(viagens[aux_int].poltronas.size()) < ASSENTOS)
        {
            do{
                aux_bool = true;
                if (int(passagens.size()) > 0)
                    ImprimirOnibus(passagens, viagens[aux_int]);
                else
                    ImprimirPoltronas();
                
                cout << "\nInforme o assento: ";
                cin >> aux_int2;
                if(aux_int2 > 0 && aux_int2 <= ASSENTOS){
                    for(Passagem p : passagens){
                        if(p.assento == aux_int2 && p.id_viagem == viagens[aux_int].id){
                            aux_bool = false;
                            break;
                        }
                    }
                    if(aux_bool){
                        passagem.assento = aux_int2;
                    }else{
                        cout << "Assento Ocupado ! \nPor favor, informe um assento livre !" << endl;
                        aux_int2 = -1;
                        palse();
                    }
                }
                else{
                    cout << "Assento invalido ! \nPor favor, informe um assento valido !" << endl;
                    palse();
                }
                limpaTela();
            }while(aux_int2 < 0 || aux_int2 > ASSENTOS);
            passagem.id_viagem = viagens[aux_int].id;
            passagem.preco = horarios[viagens[aux_int].dataHora.hora].preco;
            passagem.dataHora = viagens[aux_int].dataHora;
            cout << "Nome do passageiro: ";
            cin >> passagem.nome;
            cout << "CPF do passageiro: ";
            cin >> passagem.cpf;
            cout << "Idade do passageiro: ";
            cin >> passagem.idade;
            passagem.Vazio = false;
            return passagem;
        }
        else
        {
            cout << "Poltronas nao disponivel" << endl;
        }
    }
    else
    {
        cout << "Viagem invalida ! \nPor favor, informe os dados corretos !" << endl;
    }
    
    return passagem;
}

void Passagem::imprime_passagem(Passagem p, vector<Horario> horarios)
{
    cout << "ID da Viagem: " << p.id_viagem << endl;
    cout << "Data da Viagem: " << p.dataHora.data.data_Estenco << endl;
    cout << "Hora da Viagem: " << horarios[p.dataHora.hora].horario << endl;
    cout << "Nome do Passageiro: " << p.nome << endl;
    cout << "CPF do Passageiro: " << p.cpf << endl;
    cout << "Idade do Passageiro: " << p.idade << endl;
    cout << "Assento: " << p.assento << endl;
    cout << "Preco: " << p.preco << endl;
    cout << "----------------------------------------------------------------" << endl;
}

double total_arrecadado_Viagem(vector<Passagem> passagens, Viagem viagem)
{
    int tam = passagens.size();
    if (tam == 0)
    {
        return 0.0;
    }
    double total = 0.0;
    for (Passagem p : passagens)
    {
        if (p.id_viagem == viagem.id)
        {
            total += p.preco;
        }
    }
    return total;
}

string nome_passageiro_poltrona(vector<Passagem> passagens, Viagem viagem, int poltrona)
{
    for (Passagem p : passagens)
    {
        if (p.id_viagem == viagem.id && p.assento == poltrona)
        {
            return p.nome;
        }
    }
    return "";
}

double total_arrecadadoMes(vector<Passagem> passagens, vector<Viagem> viagens, int mes)
{
    int tam = passagens.size();
    if (tam == 0)
    {
        return 0.0;
    }
    double total = 0.0;
    for (Viagem v : viagens)
    {
        if (v.dataHora.data.mes == mes)
        {
            for (Passagem p : passagens)
            {
                if (v.id == p.id_viagem)
                {
                    total += p.preco;
                }
            }
        }
    }
    return total;
}
double media_idade(vector<Passagem> passagens)
{
    int tam = passagens.size();
    if (tam == 0)
    {
        return 0.0;
    }
    double media = 0.0;
    for (Passagem p : passagens)
    {
        media += p.idade;
    }
    return media / tam;
}

void HorarioMaisRentavel(vector<Horario> horarios, vector<Viagem> viagens, vector<Passagem> passagens)
{
    string horarioMaisRentavel;
    double somaPreco;
    double precoMaisRentavel;
    int i = 0;
    for (Horario h : horarios)
    {
        for (Viagem v : viagens)
        {
            somaPreco = 0.0;
            if (horarios[v.dataHora.hora].horario == h.horario)
            {
                for (Passagem p : passagens)
                {
                    if (v.id == p.id_viagem)
                    {
                        somaPreco += p.preco;
                    }
                }
                if (i == 0)
                {
                    horarioMaisRentavel = h.horario;
                    precoMaisRentavel = somaPreco;
                    i++;
                }
                else
                {
                    if (somaPreco > precoMaisRentavel)
                    {
                        horarioMaisRentavel = h.horario;
                        precoMaisRentavel = somaPreco;
                    }
                }
            }
        }
    }
    cout << "\nHorario mais rentavel: " << horarioMaisRentavel << endl;
    cout << "Valor arrecadado: R$" << precoMaisRentavel << endl;
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
    cout << "3 - Total arrecadado para uma determinada viagem" << endl;
    cout << "4 - Total arrecadado para um determinado mes" << endl;
    cout << "5 - Passageiro em uma determinada poltrona de uma determinada viagem" << endl;
    cout << "6 - Horario mais rentavel" << endl;
    cout << "7 - Media de idade dos passageiros" << endl;
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