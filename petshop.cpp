#include <iostream>  //inclui ferramentas para entrada e saída
#include <string>    //inclui a biblioteca para lidar com o tipo string
#include <vector>    //inclui a estrutura de lista dinâmica (vector)
#include <iomanip>   //feramenta para formatar números, como definir casas decimais

class Pet {          //classe pet - molde para os animais do sistema
private:             //atributos privados: só podem ser alterados por funções da própria classe
    std::string nome;    //guarda o nome do pet
    std::string especie; //guarda a espécie (se é cachorro, gato...)
    std::string responsavel; //guarda o nome do dono/responsável
    double idade;            //guarda a idade aceitando números decimais
    std::vector<std::string> servicosRecebidos; //lista de serviços que este pet ja recebeu

public:              //métodos públicos - podem ser acessados de qualquer lugar do código
    Pet(std::string n, std::string e, double i, std::string r) { //construtor - função q prepara o objeto assim que ele é criado
        nome = n; especie = e; idade = i; responsavel = r; //atribui os valores iniciais
    }
    
    void exibirFichaCompleta() const {    //método const - mostra os dados. O 'const' garante que esta função não altere o pet
        std::cout << "Pet: " << nome << " | Especie: " << especie 
                  << " | Idade: " << idade << " anos | Responsavel: " << responsavel; //vai imprimir dados básicos
        
        if (servicosRecebidos.empty()) { //se a lista de serviços estiver vazia
            std::cout << "\n   [!] Nenhum servico recebido ate o momento."; //mostra aviso
        } else {
            std::cout << "\n   [*] Servicos realizados: "; //se houver, começa a listar
            
            for (size_t i = 0; i < servicosRecebidos.size(); i++) {
                std::cout << servicosRecebidos[i] << (i == servicosRecebidos.size() - 1 ? "" : ", "); //imprime o serviço e coloca vírgula se não for o último da lista
            }
        }
        std::cout << "\n------------------------------------";
    }

    void adicionarServico(std::string s) {   //método - adiciona um novo serviço à lista desse animal específico
        servicosRecebidos.push_back(s);      //insere o nome do serviço no vetor
    }

    std::string getNome() const { return nome; }  //método get const - permite que outras partes do código leiam o nome do pet sem alterá-lo
};

class Servico {   //classe serviço - molde para os tipos de serviços da loja
private:
    std::string nomeServico;
    double preco;            

public:
    Servico(std::string n, double p) : nomeServico(n), preco(p) {}  //construtor - define o nome e o preço do serviço

    void exibirServico() const {            //método const - exibe o serviço formatado na tela
        std::cout << nomeServico << " - R$ " << std::fixed << std::setprecision(2) << preco << std::endl; //fixed e setprecision(2) vai garantir wue o preço apareça com duas casas decimais
    }

    double getPreco() const { return preco; }   //métodos get const - retornam valores para o sistema (vão ser essenciais para evitar erro de "const")
    std::string getNome() const { return nomeServico; }
};

//prototipagem - avisa o compilador que estas funcoes existem abaixo
void exibirMenu(); 
void exibirRelatorio(const std::vector<std::string>& historico, const double& faturamento);

//função main:
int main() {
    const std::string NOME_UNIDADE = "PET SHOP PATAS DE OURO"; //nome da loja que não muda
    int opcao = 0;             //variavel para guardar a escolha do menu
    int* ptrOpcao = &opcao;    //ponteiro: aponta para a memória da variável 'opcao'
    bool rodando = true;       //variavel booleana para manter o loop funcionando
    double faturamentoTotal = 0.0; //vai acumular o dinheiro das vendas

    std::vector<Pet> listaPets;             //vetor que guarda todos os objetos do tipo Pet
    std::vector<std::string> historicoVendas; //vetor de textos para o histórico geral
    std::vector<Servico> catalogo;          //vetor que guarda os serviços oferecidos

    //inicialização do catálogo de serviços
    catalogo.push_back(Servico("Banho Simples", 45.00));
    catalogo.push_back(Servico("Tosa Higienica", 60.00));
    catalogo.push_back(Servico("Hidratacao de Pelagem", 35.00));
    catalogo.push_back(Servico("Daycare (Creche)", 80.00));
    catalogo.push_back(Servico("Hotel (Pernoite)", 120.00));
    catalogo.push_back(Servico("Adestramento", 150.00));

    //loop que mantém o PetShop aberto enquanto 'rodando' for verdadeiro
    while (rodando) {
        exibirMenu(); //chama a funcao que desenha o menu visual
        std::cout << "Unidade: " << NOME_UNIDADE << "\nEscolha uma opcao: ";
        
        //verifica se o usuário digitou um número; se digitar letra, o sistema limpa o erro
        if (!(std::cin >> *ptrOpcao)) {
            std::cin.clear(); //limpa o estado de erro do cin
            std::cin.ignore(10000, '\n'); //descarta o que foi digitado incorretamente
            continue; //recomeça o loop
        }

        if (*ptrOpcao == 1) { //1. cadastrar pet
            std::string n, e, r; 
            double i; 
            std::cout << "Nome do Pet: "; std::cin.ignore(); //limpa o Enter do buffer
            std::getline(std::cin, n); //lê o nome completo
            std::cout << "Especie: "; std::getline(std::cin, e); //lê a espécie
            std::cout << "Idade: "; std::cin >> i; //lê a idade decimal
            std::cout << "Nome do Responsavel: "; std::cin.ignore(); 
            std::getline(std::cin, r); //lê o nome do dono ou responsavel
            
            listaPets.push_back(Pet(n, e, i, r)); //adiciona o pet cadastrado na lista
            std::cout << "Cadastro realizado com sucesso!\n";

        } else if (*ptrOpcao == 2) { //2. contratar servoço
            if (listaPets.empty()) { //verifica se há animais cadastrados
                std::cout << "ALERTA: Voce precisa cadastrar um Pet primeiro!\n";
            } else {
                std::cout << "\n--- ESCOLHA O SERVICO ---\n";
                for (size_t i = 0; i < catalogo.size(); i++) { //mostra as opções do catálogo
                    std::cout << i + 1 << ". "; catalogo[i].exibirServico(); 
                }
                
                int escolhaS, escolhaP, formaPgto; 
                std::cout << "Numero do servico: "; std::cin >> escolhaS;
                
                std::cout << "ID do Pet:\n";
                for(size_t i = 0; i < listaPets.size(); i++) { //mostra os pets registrados e seus IDs
                    std::cout << "[" << i << "] " << listaPets[i].getNome() << " ";
                }
                std::cout << "\nID: "; std::cin >> escolhaP; //seleciona o pet pelo número

                std::cout << "Forma de Pagamento (1-4): "; std::cin >> formaPgto;

                //segurança: garante que as escolhas existam nos vetores
                if (escolhaS > 0 && escolhaS <= (int)catalogo.size() && escolhaP >= 0 && escolhaP < (int)listaPets.size()) {
                    double precoS = catalogo[escolhaS - 1].getPreco(); //pega o preço
                    faturamentoTotal += precoS; //soma ao caixa

                    std::string nomeS = catalogo[escolhaS-1].getNome(); //nome do serviço
                    listaPets[escolhaP].adicionarServico(nomeS); //guarda na ficha do pet
                    
                    //cria uma frase formatada para o histórico
                    std::string registro = "Pet: " + listaPets[escolhaP].getNome() + " | Servico: " + nomeS;
                    historicoVendas.push_back(registro); // Guarda na lista de vendas
                    std::cout << "Servico registrado com sucesso!\n";
                }
            }

        } else if (*ptrOpcao == 3) { //3. relatório financeiro
            exibirRelatorio(historicoVendas, faturamentoTotal); 

        } else if (*ptrOpcao == 4) { //4. listar pets cadastrados
            std::cout << "\n======= LISTAGEM DE PETS =======\n";
            if (listaPets.empty()) { 
                std::cout << "Nenhum pet cadastrado no sistema.\n";
            } else {
                //loop tradicional para percorrer todos os pets e mostrar a ficha de cada um
                for (size_t i = 0; i < listaPets.size(); i++) {
                    listaPets[i].exibirFichaCompleta();
                    std::cout << std::endl;
                }
            }

        } else if (*ptrOpcao == 5) { //5. sair
            rodando = false; //altera para falso para sair do loop while
            std::cout << "Encerrando sistema...\n";
        } else { 
            std::cout << "Opcao invalida!\n";
        }
    }
    return 0;
}


void exibirMenu() {
    std::cout << "\n====================================\n";
    std::cout << "        SISTEMA PET SHOP         \n";
    std::cout << "====================================\n";
    std::cout << "1. Cadastrar Pet e Responsavel\n";
    std::cout << "2. Contratar Servico e Pagar\n";
    std::cout << "3. Relatorio Financeiro\n";
    std::cout << "4. Listar Pets Cadastrados\n";
    std::cout << "5. Sair do Sistema\n";
    std::cout << "------------------------------------\n";
}

// Gera o resumo financeiro final
void exibirRelatorio(const std::vector<std::string>& historico, const double& faturamento) {
    std::cout << "\n======= RESUMO DE VENDAS =======\n";
    // Loop tradicional para listar os registros guardados
    for (size_t i = 0; i < historico.size(); i++) { 
        std::cout << " > " << historico[i] << std::endl;
    }
    // Exibe o faturamento total com 2 casas decimais
    std::cout << "FATURAMENTO TOTAL: R$ " << std::fixed << std::setprecision(2) << faturamento << std::endl;
}