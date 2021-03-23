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
	int opc;
	// todo caminho do arquivo
	Sistema *sistema = new Sistema("");

	while (1) {
		system("cls");
		cout << "1 - Adicionar filtro" << endl;
		cout << "2 - Limpar filtros" << endl;
		cout << "3 - Visualizar filtros" << endl;
		cout << "4 - Visualizar dados" << endl;
		cout << "5 - Exportar dados" << endl;
		cin >> opc;

		switch (opc) {
			case 1:
				cout << "Adicionar filtro" << endl;
				system("pause");
				break;
			case 2:
				cout << "Limpar filtros" << endl;
				system("pause");
				break;
			case 3:
				cout << "Visualizar filtros" << endl;
				system("pause");
				break;
			case 4:
				cout << "Visualizar dados" << endl;
				system("pause");
				break;
			case 5:
				cout << "Exportar dados" << endl;
				system("pause");
				break;
			default:
				cout << "Invalida" << endl;
				system("pause");
				break;

		}

	}




	system("pause");
	return 0;
}