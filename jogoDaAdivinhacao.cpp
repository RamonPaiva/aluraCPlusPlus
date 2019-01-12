#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    cout << "************************" << endl;
    cout << "* JOGO DA ADIVINHAÇÃO! *" << endl;
    cout << "************************" << endl;

    cout << "Escolha o nível de dificuldade: " << endl;
    cout << "Fácil (F), Médio (M) ou Difícil(D)" << endl;

    char dificuldade;
    cin >> dificuldade;

    int numeroTentativas;

    if (dificuldade == 'F') {
        numeroTentativas = 15;
    } else if (dificuldade == 'M') {
        numeroTentativas = 10;
    } else if (dificuldade == 'D') {
        numeroTentativas = 5;
    }

    //srand(time(NULL)); 
    srand(time(0));
    const int NUMERO_SECRETO = rand() % 100;

    bool nao_acertou = true;
    int tentativas = 0;

    double pontos = 1000;

    for (tentativas = 1; tentativas <= numeroTentativas; tentativas++) {

        cout << "Tentativa: " << tentativas << endl;
        int chute;
        cout << "Chute um número: " << endl;
        cin >> chute;

        double pontosPerdidos =(double) (abs(chute - NUMERO_SECRETO))/2;
        pontos -= pontosPerdidos;

        cout << "Chute: " << chute << endl;

        bool acertou = chute == NUMERO_SECRETO;
        bool maior = chute > NUMERO_SECRETO;

        if (acertou) {
          cout << "Você acertou!" << endl;
          nao_acertou = false;
          break;
        } else if (maior) {
            cout << "Chute MAIOR que o número secreto!" << endl;
        } else {
           cout << "Chute MENOR que o número secreto!" << endl;
        }
        
    }
    if (nao_acertou) {
        cout << "Você perdeu!" << endl;
        cout << "O número era: " << NUMERO_SECRETO << endl;
    } else {
        cout << "Você acertou o número secreto em " << tentativas << " tentativas!" << endl;
        cout.precision(2);
        cout << fixed;
        cout << "Pontuação: " << pontos << "!" << endl;
        cout << "Fim de Jogo!" << endl;
    }
}