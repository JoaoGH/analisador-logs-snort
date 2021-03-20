#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataHora {
private:
	int ano;
	int mes;
	int dia;
	int hora;
	int minuto;
	int segundo;

public:
	DataHora(string dataHora) {

	}

	string toISO() {
		return "";
	}

	//todo sobrecarga operadores
};


class Registro {
private:
	DataHora dataHora;
	string codigo;
	string mensagem;
	string classificacao;
	int prioridade;
	string protocolo;
	string origemIP;
	int origemPorta;
	string destinoIP;
	int destinoPorta;

public:
	Registro(string linha);
	// métodos adicionais
};

class Sistema {
	vector<Registro *> logs;
public:
	Sistema(string nomeArquivo) {
		// todo abrir programa
		// todo percorrer do inicio ao fim
		// todo cada linha é um novo registro dentro da logs
	}
};

int main() {
	// todo caminho do arquivo
	Sistema *sistema = new Sistema("");
	cout << "teste";
	return 0;
}