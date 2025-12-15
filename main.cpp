#include <iostream>
#include <ctime>
using namespace std;

int main(){

    srand(time(NULL));

    int menu;

    // MATRIZ PRINCIPAL
    int principal[9][9] = {
        {4,9,5,2,8,7,3,6,1},
        {7,2,8,6,1,3,4,9,5},
        {3,6,1,9,5,4,7,2,8},
        {6,5,3,8,4,9,2,1,7},
        {9,8,4,1,7,2,6,5,3},
        {2,1,7,5,3,6,9,8,4},
        {1,3,2,4,6,5,8,7,9},
        {5,4,6,7,9,8,1,3,2},
        {8,7,9,3,2,1,5,4,6}
    };

    int gabarito[9][9];
    int jogo[9][9];

    do {
        cout << "\033c";
        cout << "=========== SUDOKU ===========" << endl;
        cout << "1 - Jogar" << endl;
        cout << "2 - Sobre" << endl;
        cout << "3 - Sair" << endl;
        cout << "Escolha: ";
        cin >> menu;

        switch(menu) {

            case 1: {
                // Gera a matriz gabarito, com um sorteio de 4 opções
                // De acordo com o resultado do sorteio, transforma a matriz principal em matriz gabarito na forma direta, transposta, inverte por linhas, inverte por colunas.
                int op = rand() % 4;
    
                for (int i=0; i<9; i++){
                    for (int j=0; j<9; j++){
                        gabarito[i][j] = 0;
                    }
                }
    
                if (op == 0) { // cópia direta
                    for (int i=0; i<9; i++){
                        for (int j=0; j<9; j++){
                            gabarito[i][j] = principal[i][j];
                        }
                    }
                }
                else if (op == 1) { // transposta
                    for (int i=0; i<9; i++){
                        for (int j=0; j<9; j++){
                            gabarito[i][j] = principal[j][i];
                        }
                    }
                }
                else if (op == 2) { // inverter por linhas
                    for (int i=0; i<9; i++){
                        for (int j=0; j<9; j++){
                            gabarito[i][j] = principal[8-i][j];
                        }
                    }
                }
                else { // inverter por colunas
                    for (int i=0; i<9; i++){
                        for (int j=0; j<9; j++){
                            gabarito[i][j] = principal[i][8-j];
                        }
                    }
                }
    
                // Gera a matriz com 41 posições
                // inicia todas as posições preenchidas com 0
                int usado[9][9];
                for (int i=0; i<9; i++)
                    for (int j=0; j<9; j++)
                        usado[i][j] = 0;
    
                for (int i=0; i<9; i++)
                    for (int j=0; j<9; j++)
                        jogo[i][j] = 0;
    
                int qtd = 41;
    
                // Gera aleatóriamente as posições que serão reveladas na matriz que será exibida para o jogador.
                // A matriz "usado" utiliza "0" como posição não revelada e "1" para posição já revelada.
                while (qtd > 0) {
                    int r = rand() % 9;
                    int c = rand() % 9;
    
                    if (usado[r][c] == 0) {
                        usado[r][c] = 1;
                        jogo[r][c] = gabarito[r][c];
                        qtd--;
                    }
                }
    
                // Começa o loop do jogo
                int tentativas = 0;
    
                while (true) {
    
                    cout << "\033c";
    
                    // Exibe o tabuleiro para o jogador.
                    cout << "    ";
                    for (int c=1;c<=9;c++) { // O loop inicia com c=1, para que o não fique apresentado as colunas de forma 0 1 2 3 4 5 6 7 8.
                        cout << c << " ";
                        if (c % 3 == 0 && c != 9) { // Faz uma verificação para ficar alinhado o número da coluna com o resto da matriz
                            cout << "  ";
                        }
                    }
                    cout << "\n   ----------------------\n";
    
                    for (int i=0;i<9;i++) {
                        cout << i+1 << " | ";
                        for (int j=0;j<9;j++) {
                            if (jogo[i][j] == 0) {
                                cout << ". ";
                            } else {
                                cout << jogo[i][j] << " ";
                            } if ((j+1) % 3 == 0 && j != 8){ // Esse if verifica o valor do j, para ver se completou um bloco de 3 colunas e faz a separação visual. (ex: j=2,5,8 significa que fechou 3 colunas.)
                                cout << "| ";
                            }
                        }
                        cout << "\n";
                        
                        if ((i+1) % 3 == 0 && i != 8){ // Esse if verifica o valor de i, para ver se completou 3 linhas, caso sim, faz a separação visual.
                            cout << "   ----------------------\n";
                        }
                    }
    
                    // Verifica se venceu, se todos os números estiverem preenchidos (!= 0), o jogador vence.
                    int zeros = 0;
                    for (int i=0;i<9;i++){
                        for (int j=0;j<9;j++){
                            if (jogo[i][j] == 0) {
                                zeros++;
                            }
                        }
                    }
    
                    if (zeros == 0) { // Verifica a quantidade de "0" (ou " . ") no jogo, se não tiver nenhum, significa que todas as posições foram preenchidas e o jogador vence o jogo.
                        cout << "\nParabéns! Você completou o Sudoku!" << endl;
                        cout << "Tentativas: " << tentativas << endl;
                        cout << "\nPressione ENTER...";
                        cin.ignore();
                        cin.ignore();
                        break;
                    }
    
                    // Input para jogador realizar a ação.
                    int li, co, num;
                    cout << "\nDigite (linha coluna numero) ou 0 0 0 para sair: ";
                    cin >> li >> co >> num;
    
                    if (li==0 && co==0 && num==0) {
                        cout << "Voltando ao menu..." << endl;
                        break;
                    }
    
                    if (li<1 || li>9 || co<1 || co>9 || num<1 || num>9) { // Verifica se a linha, coluna ou número digitado estão entre 1 e 9.
                        cout << "Entrada inválida!" << endl;
                        cout << "ENTER para continuar...";
                        cin.ignore();
                        cin.ignore();
                    } else {
                        
                        // Aqui é feito li-- e co-- para acessar a posição correta da matriz, por exemplo, se digitar linha 5 e coluna 4, vai acessar: exemplo[4][3]
                        li--; 
                        co--;
        
                        // Verifica se a posição já foi preenchida, caso não, aumenta a tentativa e verifica se o número digitado está correto
                        if (jogo[li][co] != 0) { 
                            cout << "Posição já preenchida!" << endl;
                            cout << "ENTER para continuar...";
                            cin.ignore();
                            cin.ignore();
                        } else {
                            tentativas++;
        
                            if (num == gabarito[li][co]) {
                                jogo[li][co] = num;
                            } else {
                                cout << "Número incorreto!" << endl;
                                cout << "ENTER para continuar...";
                                cin.ignore();
                                cin.ignore();
                            }
                        }
                    } 

                }
            } 
            break;
    
    
            case 2:
                cout << "\033c";
                cout << "\n- Gabriel Debiasi" << endl;
                cout << "\nMes/Ano: Novembro/2025" << endl;
                cout << "\nPressione ENTER para voltar ao menu...";
                cin.ignore();
                cin.ignore();
                break;
    
            
            case 3:
                cout << "\033c";
                cout << "Saindo... Até a proxima!\n";
                break;
    
            
            default:
                cout << "\033c";
                cout << "Opção inválida!\n(Pressione ENTER...)";
                cin.ignore();
                cin.ignore();
                break;
            }

        } while (menu != 3);
    
    return 0;
}
    
