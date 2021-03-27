#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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

	DataHora(string &mes, string &dia, string &horario) {
//		this->ano = atoi(ano.c_str());
		this->mes = this->stringMonthToIntMonth(mes);
		this->dia = atoi(dia.c_str());
		this->hora = atoi(horario.substr(0, 2).c_str());
		this->minuto = atoi(horario.substr(3, 5).c_str());
		this->segundo = atoi(horario.substr(6).c_str());
	}

	string toISO() {
		return "";
	}

	int stringMonthToIntMonth(string &mes) {
		if (mes == "Jan") {
			return 1;
		} else if (mes == "Feb") {
			return 2;
		} else if (mes == "Mar") {
			return 3;
		} else if (mes == "Apr") {
			return 4;
		} else if (mes == "Mai") {
			return 5;
		} else if (mes == "Jun") {
			return 6;
		} else if (mes == "Jul") {
			return 7;
		} else if (mes == "Aug") {
			return 8;
		} else if (mes == "Sep") {
			return 9;
		} else if (mes == "Oct") {
			return 10;
		} else if (mes == "Nov") {
			return 11;
		} else {
			return 12;
		}
	}


	//todo sobrecarga operadores
};


class Registro {
private:
	DataHora *dataHora;
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
	Registro(string linha) {
		bool containsClassification = linha.find("Classification") != string::npos;
		bool containsPriority = linha.find("Priority") != string::npos;
		string mes, dia, horario, temp, issPriority;
		istringstream issLinha(linha);

		getline(issLinha, mes, ' ');
		getline(issLinha, dia, ' ');
		getline(issLinha, horario, ' ');
		this->dataHora = new DataHora(mes, dia, horario);
		getline(issLinha, temp, '[');
		getline(issLinha, this->codigo, ']');
		getline(issLinha, temp, ' ');

		/**
		 * Se houver classificacao ou prioridade busca ate o '[',
		 * ja se nao existir nenhum busca ate o '{' do Protocolo que e obrigatorio
		 * */
		if (containsClassification || containsPriority) {
			getline(issLinha, this->mensagem, '[');
		} else {
			getline(issLinha, this->mensagem, '{');
		}
		this->mensagem = this->trim(this->mensagem);

		/**
		 * IFs para manter o processo de pegar a classificacao e prioridade somente quando existir
		 * */
		if (containsClassification) {
			getline(issLinha, temp, ':');
			getline(issLinha, this->classificacao, ']');
			this->classificacao = this->trim(this->classificacao);
		}
		if (containsPriority) {
			getline(issLinha, temp, ':');
			getline(issLinha, issPriority, ']');
			this->prioridade = atoi(issPriority.c_str());
		}

		if (containsClassification || containsPriority) {
			getline(issLinha, temp, '{');
		}

		getline(issLinha, this->protocolo, '}');
		getline(issLinha, temp, ' ');
		getline(issLinha, temp, ' ');
		this->origemIP = this->getIPFromLine(temp);
		if (temp.find(':') != string::npos) {
			this->origemPorta = this->getPortFromLine(temp);
		}
		getline(issLinha, temp, ' ');
		getline(issLinha, temp, ' ');
		this->destinoIP = this->getIPFromLine(temp);
		if (temp.find(':') != string::npos) {
			this->destinoPorta = this->getPortFromLine(temp);
		}
		cout << "end" << endl;
	}

	/**
	 * Metodo responsavel por remover os espaços em branco no inicio e fim da string.
	 * */
	string trim(string &var) {
		while (var.back() == ' ') {
			var = var.substr(0, var.size() - 1);
		}
		while (var.front() == ' ') {
			var = var.substr(1, var.size());
		}
		return var;
	}

	/**
	 * Metodo responsavel por pegar o endereco ip da linha do arquvio.
	 * */
	string getIPFromLine(string &line) {
		string ip;
		if (line.find(':') != string::npos) {
			ip = line.substr(0, line.find(':'));
		} else {
			ip = line;
		}
		return ip;
	}

	/**
	 * Metodo responsavel por pegar o a porta de endereco ip da linha do arquvio.
	 * */
	int getPortFromLine(string &line) {
		return atoi(line.substr(line.find(':') + 1).c_str());
	}

};

class Sistema {
	vector<Registro *> logs;
public:
	Sistema(string nomeArquivo) {
		fstream arq;
		string line;
		arq.open(nomeArquivo.c_str(), fstream::in);
		if (arq.is_open()) {
			while (!arq.eof()) {
				getline(arq, line, '\n');
				if (line != "") {
					Registro *record = new Registro(line);
					logs.push_back(record);
				}
			}
		} else {
			cout << "Erro ao abrir o arquivo!" << endl;
		}
	}

	~Sistema() {};

	int getTotal() {
		return this->logs.size();
	}

};

int main() {
	int opc;
	Sistema *sistema = new Sistema("snortsyslog");
	cout << sistema->getTotal() << endl;
	system("pause");

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