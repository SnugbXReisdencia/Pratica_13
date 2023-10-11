# include <iostream>
# include <limits>
# include <cstring>
# include <vector>
#include <regex>

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

struct Empregado
{
    string nome;
    string sobrenome;
    string rg;
    Data dt_nascimento;
    Data dt_admissao;
    double salario;
};

void reajusta_dez_porcento(vector<Empregado> &);
void ListaEmpregados(vector<Empregado> &empregados);

int Menu();

bool validarRG(const string& rg);

void pause();
void limpaTela();
void limparBuffers();


int main(){
    int qtdEmpregadosMax = 50, op;
    vector<Empregado> empregados;
    Empregado empregado;
    
    
    do{
        limpaTela();
        op = Menu();
        switch(op){
            case 1:
                limpaTela();
                if(int(empregados.size()) < qtdEmpregadosMax){
                    cout << "==========Cadastro de Empregados==========\n\n";
                    cout << "Nome: ";
                    cin >> empregado.nome;
                    cout << "Sobrenome: ";
                    cin >> empregado.sobrenome;
                    cout << "RG: ";
                    cin >> empregado.rg;
                    while(!validarRG(empregado.rg)){
                        cout << "RG invalido, digite novamente: ";
                        cin >> empregado.rg;
                    }
                    cout << " Data de Nascimento ";
                    empregado.dt_nascimento = gera_data(true);
                    cout << " Data de Admissão ";
                    empregado.dt_admissao = gera_data(true);
                    cout << "Salário: ";
                    cin >> empregado.salario;
                    
                    empregados.push_back(empregado);
                }
                else
                    cout << "Nao foi possivel adicionar mais empregados\n Limite de empregados atingido\n";
                pause();
                break;
            case 2:
                limpaTela();
                if(empregados.size() > 0){
                    ListaEmpregados(empregados);
                }else{
                    cout << "Nao foi encontrado nenhum empregado\n";
                    cout << "Faça o cadastro de um empregado\n";
                }
                pause();
                break;
            case 3:
                limpaTela();
                if(empregados.size() > 0){
                    reajusta_dez_porcento(empregados);
                    cout << "Dados reajustados com sucesso !!\n";
                    cout << "Segui a lista de empregados: \n";
                    ListaEmpregados(empregados);
                }else{
                    cout << "Nao foi encontrado nenhum empregado\n";
                    cout << "Faça o cadastro de um empregado\n";
                }
                pause();
                break;
            case 0:
                return 0;
            default:
                cout << "Opcao invalida\n";
                pause();
        }
    }while(op != 0);
    return 0;
}

bool validarRG(const string& rg){
    regex rgRegex("^(\\d{9}|\\d{2}\\.\\d{3}\\.\\d{3}-\\d{1}|\\d{2}\\.\\d{3}\\.\\d{3})$");
    return regex_match(rg, rgRegex);
}

void reajusta_dez_porcento(vector<Empregado> &empregados){
    int tamanho = empregados.size();
    for(int i = 0; i < tamanho; i++){
        empregados[i].salario += (empregados[i].salario * 0.1);
    }
}

void ListaEmpregados(vector<Empregado> &empregados){
    cout << "==========Dados dos Empregados==========\n\n";
    for(size_t i = 0; i < empregados.size(); i++){
        cout << "Empregado: " << i+1 << "ª\n\n";
        cout << "======================================\n";
        cout << "Nome: " << empregados[i].nome << "\n";
        cout << "Sobrenome: " << empregados[i].sobrenome << "\n";
        cout << "RG: " << empregados[i].rg << "\n";
        cout << "Data de Nascimento: " << empregados[i].dt_nascimento.data << "\n";
        cout << "Idade: " << empregados[i].dt_nascimento.idade() << "\n";
        cout << "Data de Admissão: " << empregados[i].dt_admissao.data << "\n";
        cout << "Salário: " << empregados[i].salario << "\n";
        cout << "======================================\n\n";
    }
}

void pause()
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

void limparBuffers()
{
    // Limpa o buffer de entrada do cin
    cin.clear();
    // Limpa o buffer de saída do cout
    cout.flush();
}

bool Data::validarData(Data data, bool atual){
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
        "setembro", "outubro", "novembro", "dezembro"
    };

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

int Data::idade(){
    time_t tempo_atual = time(nullptr);
    tm *infoTempo = localtime(&tempo_atual);
    int ano_atual = infoTempo->tm_year + 1900;
    return ano_atual - ano;
}

int Menu(){
    int opcao;
    cout << "############## Menu Principal ##############\n\n";
    cout << "1 - Cadastrar Empregado" << endl;
    cout << "2 - Listar Empregados" << endl;
    cout << "3 - Reajustar Salários" << endl;
    cout << "0 - Sair" << endl;

    cout << "Escolha uma opcao: ";
    cin >> opcao;

    return opcao;
}