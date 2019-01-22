#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string palavraSecreta = "melancia";
map<char, bool> chutou;
vector<char> chutesErrados;

void mostraCabecalho()
{
    cout << "************************" << endl;
    cout << "**** JOGO DA FORCA! ****" << endl;
    cout << "************************" << endl
         << endl;
}

void mostraChutesErrados()
{
    cout << "Chutes errados: ";
    for (char letraErrada : chutesErrados)
    {
        cout << letraErrada << " ";
    }
    cout << endl;
}

void mostraLetrasAcertadas()
{
    for (char letra : palavraSecreta)
    {
        if (chutou[letra])
        {
            cout << letra << " ";
        }
        else
        {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool letraExiste(char chute)
{
    for (char letra : palavraSecreta)
    {
        if (chute == letra)
        {
            return true;
        }
    }
    return false;
}

void testaChute()
{
    char chute;
    cout << "Chute: ";
    cin >> chute;

    chutou[chute] = true;

    if (letraExiste(chute))
    {
        cout << "Você acertou! Essa letra está na palavra!" << endl;
    }
    else
    {
        cout << "Você errou! Não tem essa letra na palavra." << endl;
        chutesErrados.push_back(chute);
    }
    cout << endl;
}

bool nao_acertou()
{
    for (char letra : palavraSecreta)
    {
        if (!chutou[letra])
        {
            return true;
        }
    }
    return false;
}

bool nao_inforcou()
{
    return chutesErrados.size() < 5;
}

vector<string> leArquivo()
{
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if (arquivo.is_open()) {
        int quantidadePalavras;
        arquivo >> quantidadePalavras;
        string palavraLida;
        vector <string> palavrasDoArquivo;
        for (int i = 0; i < quantidadePalavras; i++) {
            arquivo >> palavraLida;
            palavrasDoArquivo.push_back(palavraLida);
        }
        arquivo.close();
        return palavrasDoArquivo;
    } else {
        cout << "Não foi possível acessar o banco de palavras";
        exit(0);
    }

    
}

void sortePalavraSecreta() {
    vector <string> palavras = leArquivo();
    
    srand(time(NULL));
    int indiceSorteado = rand() % palavras.size();
    palavraSecreta = palavras[indiceSorteado];
}

void salvaPalavrasNoArquivo(vector <string> novaLista){
    ofstream arquivo;
    arquivo.open("palavras.txt");
    if (arquivo.is_open()) {
        arquivo << novaLista.size() << endl;
        for (string palavra : novaLista) {
            arquivo << palavra << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir arquivo" << endl;
        exit(0);
    }

}

void adicionaPalavraNoArquivo() {
    cout << "Digite a nova palavra: " << endl;
    string palavraNova;
    cin >> palavraNova;

    vector <string> lista_palavras = leArquivo();
    lista_palavras.push_back(palavraNova);

    
    salvaPalavrasNoArquivo(lista_palavras);

}

int main()
{
    mostraCabecalho();

    leArquivo();

    sortePalavraSecreta();

    while (nao_acertou() && nao_inforcou())
    {

        mostraChutesErrados();

        mostraLetrasAcertadas();

        testaChute();
    }
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << palavraSecreta << endl;
    if (nao_acertou())
    {
        cout << "Você perdeu! Sorte na próxima vez." << endl;
    
    }
    else
    {
        cout << "Parabéns! Você acertou a palavra secreta" << endl;
        cout << "Adicionar uma palavra nova? (S/N)";
        char resposta;
        cin >> resposta;
        if (resposta == 'S') {
            adicionaPalavraNoArquivo();
        }
    }
}