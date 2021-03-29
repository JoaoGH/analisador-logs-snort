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
	bool filtro;

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

		this->filtro = true;
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

	DataHora *getDataHora() {
		return this->dataHora;
	}

	string getCodigo() {
		return this->codigo;
	}

	string getMensagem() {
		return this->mensagem;
	}

	string getClassificacao() {
		return this->classificacao;
	}

	int getPrioridade() {
		return this->prioridade;
	}

	string getProtocolo() {
		return this->protocolo;
	}

	string getOrigemIP() {
		return this->origemIP;
	}

	int getOrigemPorta() {
		return this->origemPorta;
	}

	string getDestinoIP() {
		return this->destinoIP;
	}

	int getDestinoPorta() {
		return this->destinoPorta;
	}

	void setFiltro(bool status) {
		this->filtro = status;
	}

	bool getFiltro() {
		return this->filtro;
	}

};

class Sistema {
	vector<Registro *> logs;
	// Filtros
	string dataInicial = "", dataFinal = "", horaInicial = "", horaFinal = "", codigo = "", mensagem = "", classificacao = "", protocolo = "", origemIP = "", destinoIP = "";
	// todo filtros inteiros: prioridade, porta origem e porta destino - pode ser valor exato ou intervalo
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

	vector<Registro *> getLogsValidos() {
		vector<Registro *> logsValidos;
		for (vector<Registro *>::iterator it = this->logs.begin(); it != this->logs.end(); ++it) {
			if ((*it)->getFiltro()) {
				logsValidos.push_back(*it);
			}
		}
		return logsValidos;
	}

	void filtroData(string data1, string data2) {
		// todo, corrigir a classe DataHora. ta invalida
	}

	void filtroHora(string hora1, string hora2) {
		// todo, corrigir a classe DataHora. ta invalida
	}

	/**
	 * Metodo responsavel por validar se o codigo informado e diferente do codigo do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroCodigo(string codigo) {
		codigo = this->toUpper(codigo);
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (this->toUpper((*it)->getCodigo()) != codigo) {
				(*it)->setFiltro(false);
			}
		}
	}

	/**
	 * Metodo responsavel por validar se a mensagem informada e diferente da mensagem do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroMensagem(string mensagem) {
		mensagem = this->toUpper(mensagem);
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (this->toUpper((*it)->getMensagem()) != mensagem) {
				(*it)->setFiltro(false);
			}
		}
	}

	/**
	 * Metodo responsavel por validar se a classificacao informado e diferente a classificacao do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroClassificacao(string classificacao) {
		classificacao = this->toUpper(classificacao);
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (this->toUpper((*it)->getClassificacao()) != classificacao) {
				(*it)->setFiltro(false);
			}
		}
	}

	/**
	 * Metodo responsavel por validar se o protocolo informado e diferente o protocolo do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroProtocolo(string protocolo) {
		protocolo = this->toUpper(protocolo);
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (this->toUpper((*it)->getProtocolo()) != protocolo) {
				(*it)->setFiltro(false);
			}
		}
	}

	/**
	 * Metodo responsavel por validar se o endereco IP de origem informado e diferente o endereco IP de origem do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroOrigemIP(string origemIP) {
		origemIP = this->toUpper(origemIP);
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (this->toUpper((*it)->getOrigemIP()) != origemIP) {
				(*it)->setFiltro(false);
			}
		}
	}

	/**
	 * Metodo responsavel por validar se o endereco IP de destino informado e diferente o endereco IP de destino do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroDestinoIP(string destinoIP) {
		destinoIP = this->toUpper(destinoIP);
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (this->toUpper((*it)->getDestinoIP()) != destinoIP) {
				(*it)->setFiltro(false);
			}
		}
	}

	/**
	 * Metodo responsavel por deixar uma string em capslock para facilitar o filtro
	 * */
	string toUpper(string param) {
		string up = "";
		for (int i = 0; i < param.size(); i++) {
			up += toupper(param[i]);
		}
		return up;
	}

	void aplicaFiltros() {
		int filtroOpc;
		cout << "Selecione o filtro: " << endl;
		cout << "  1 - Data" << endl;
		cout << "  2 - Hora" << endl;
		cout << "  3 - Codigo" << endl;
		cout << "  4 - Mensagem" << endl;
		cout << "  5 - Classificacao" << endl;
		cout << "  6 - Prioridade" << endl;
		cout << "  7 - Protocolo" << endl;
		cout << "  8 - Endereço IP de origem" << endl;
		cout << "  9 - Porta de origem" << endl;
		cout << " 10 - Endereço IP de destino" << endl;
		cout << " 11 - Porta de destino" << endl;
		cin >> filtroOpc;
		switch(filtroOpc) {
			case 1:
				cout << "Informe a data inicial " << endl;
				cin.ignore();
				getline(cin, dataInicial);
				cout << "Informe a data final " << endl;
				cin.ignore();
				getline(cin, dataFinal);
				this->filtroData(dataInicial, dataFinal);
				break;
			case 2:
				cout << "Informe a hora inicial " << endl;
				cin.ignore();
				getline(cin, horaInicial);
				cout << "Informe a hora final " << endl;
				cin.ignore();
				getline(cin, horaFinal);
				this->filtroHora(horaInicial, horaFinal);
				break;
			case 3:
				cout << "Informe o codigo " << endl;
				cin.ignore();
				getline(cin, codigo);
				this->filtroCodigo(codigo);
				break;
			case 4:
				cout << "Informe a mensagem " << endl;
				cin.ignore();
				getline(cin, mensagem);
				this->filtroMensagem(mensagem);
				break;
			case 5:
				cout << "Informe a classificacao " << endl;
				cin.ignore();
				getline(cin, classificacao);
				this->filtroClassificacao(classificacao);
				break;
			case 6:
				//todo prioridade
				break;
			case 7:
				cout << "Informe o protocolo " << endl;
				cin.ignore();
				getline(cin, protocolo);
				this->filtroProtocolo(protocolo);
				break;
			case 8:
				cout << "Informe o endereco IP de origem" << endl;
				cin.ignore();
				getline(cin, origemIP);
				this->filtroOrigemIP(origemIP);
				break;
			case 9:
				//todo porta origem
				break;
			case 10:
				cout << "Informe o endereco IP de destino" << endl;
				cin.ignore();
				getline(cin, destinoIP);
				this->filtroDestinoIP(destinoIP);
				break;
			case 11:
				//todo porta destino
				break;
			default:
				break;
		}
	}

	~Sistema() {};

};

int main() {
	int opc;
	Sistema *sistema = new Sistema("snortsyslog");

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
				sistema->aplicaFiltros();
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