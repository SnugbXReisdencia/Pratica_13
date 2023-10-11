# include <iostream>
# include <limits>
# include <cstring>
# include <iomanip>
# include <vector>
# include <algorithm>

using namespace std;

struct Produto
{
    string codigo;
    string nome;
    float preco;

};

Produto gera_produto(vector<Produto> );
bool valida_codigo(string, vector<Produto> );
bool valida_nome(string, vector<Produto> );
bool excluir_Produto(vector<Produto> &, string);
bool consulta_Produto(vector<Produto> , string);
void lista_Produtos(vector<Produto> );

int MenuProdutos();

void pause();
void limpaTela();

int main(){
    int qtdProdutosMax = 300, op;   
    vector<Produto> produtos;
    Produto produto;
    string aux;

    do{
        limpaTela();
        op = MenuProdutos();
        switch(op){
            case 1:
                if(int(produtos.size()) < qtdProdutosMax){
                    produto = gera_produto(produtos);
                    produtos.push_back(produto);
                }else
                    cout << "Limite de produtos atingido!\n";

                pause();
                break;
            case 2:
                limpaTela();
                if(int(produtos.size()) > 0){
                    cout << "==========Exclusao de Produtos==========\n\n";
                    cout << "Digite o código do produto que deseja excluir: ";
                    cin >> aux;
                    if(excluir_Produto(produtos, aux)){
                        cout << "Produto excluido com sucesso!\n";
                    }else
                        cout << "Produto inexistente!\n";    
                }else
                    cout << "Nenhum produto cadastrado!\n";
                pause();
                break;
            case 3:
                limpaTela();
                if(int(produtos.size()) > 0){
                    lista_Produtos(produtos);
                }else
                    cout << "Nenhum produto cadastrado!\n";
                
                pause();
                break;
            case 4:
                limpaTela();
                if(int(produtos.size()) > 0){
                    cout << "==========Consultar Produto==========\n\n";
                    cout << "Digite o código do produto que deseja buscar: ";
                    cin >> aux;
                    if(consulta_Produto(produtos, aux)){
                        cout << "\nProduto encontrado!\n";
                    }else
                        cout << "Produto inexistente!\n";
                }else
                    cout << "Nenhum produto cadastrado!\n";
                
                pause();
                break;
            case 0:
                limpaTela();
                cout << "Saindo...\n";
                break;
            default:
                limpaTela();
                cout << "Opcao invalida!\n";
                pause();
        }
    }while(op != 0 );
    return 0;
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

int MenuProdutos(){
    int op;
    cout << "========== Menu de Produtos==========\n\n";
    cout << "1 - Inserir um novo produto\n";
    cout << "2 - Excluir um produto\n";
    cout << "3 - Listar todos os produtos\n";
    cout << "4 - Consultar o preco de um produto (Pelo seu código)\n";
    cout << "0 - Sair\n";

    cout << "\nEscolha uma opcao: ";
    cin >> op;
    return op;
}

bool valida_codigo(string codigo, vector<Produto> produtos){
    for (Produto p : produtos)
    {
        if (p.codigo == codigo)
        {
            return false;
        }
    }
    if(codigo.length() != 13){
        return false;
    }

    for (int i = 0; i < 13; i++){
        if(codigo[i] < '0' || codigo[i] > '9'){
            return false;
        }
    }

    return true;
}

bool valida_nome(string nome, vector<Produto> produtos){
    if(nome.length() > 20){
        return false;
    }
    transform(nome.begin(), nome.end(), nome.begin(), ::tolower);
    for (Produto p : produtos)
    {
        transform(p.nome.begin(), p.nome.end(), p.nome.begin(), ::tolower);
        if (p.nome == nome)
        {
            return false;
        }
    }

    return true;
}

Produto gera_produto(vector<Produto> produtos){
    Produto p;
    limpaTela();
    cout << "\n==========Cadastro de Produtos==========\n\n";
    cout << "Digite o codigo do produto: ";
    cin >> p.codigo;
    if(!valida_codigo(p.codigo, produtos)){
        cout << "Codigo invalido!\n Já cadastrado ou muito grande ou muito pequeno (Tamanho de 13 caracteres exigido)!\n";
        pause();
        return gera_produto(produtos);
    }
    cout << "Digite o nome do produto: ";
    cin >> p.nome;
    if(!valida_nome(p.nome, produtos)){
        cout << "Nome invalido!\n Já cadastrado ou muito grande (Tamanho maximo de 20 caracteres)!\n";
        pause();
        return gera_produto(produtos);
    }
    cout << "Digite o preco do produto: ";
    cin >> p.preco;
    return p;
}

bool excluir_Produto(vector<Produto> &produtos, string codigo){
    for (int i = 0; i < int(produtos.size()); i++)
    {
        if (produtos[i].codigo == codigo)
        {
            produtos.erase(produtos.begin() + i);
            return true;
        }
    }
    return false;
}

bool consulta_Produto(vector<Produto> produtos, string codigo){
    for (Produto p : produtos)
    {
        if (p.codigo == codigo)
        {
            cout << "---------------------------------------------" << endl;
            cout << "Nome do produto: " << p.nome << endl;
            cout << "Preco do produto: R$ " << fixed << setprecision(2) << p.preco << endl;
            cout << "---------------------------------------------" << endl;
            return true;
        }
    }
    return false;
}

void lista_Produtos(vector<Produto> produtos){
    cout << "==========Lista de Produtos==========\n\n";
    int i = 1;
    for (Produto p : produtos)
    {
        cout << "Produto " << i++ << "ª: " <<  endl;
        cout << "---------------------------------------------" << endl;
        cout << "Código do produto: " << p.codigo << endl;
        cout << "Nome do produto: " << p.nome << endl;
        cout << "Preco do produto: R$ " << fixed << setprecision(2) << p.preco << endl;
        cout << "---------------------------------------------" << endl;
    }
}

