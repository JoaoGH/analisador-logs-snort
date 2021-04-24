#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <iomanip>

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

	DataHora(int dia, int mes) {
		this->ano = 2021;
		this->mes = mes;
		this->dia = dia;
		this->hora = NULL;
		this->minuto = NULL;
		this->segundo = NULL;
	}

	DataHora(string &horario) {
		this->ano = NULL;
		this->mes = NULL;
		this->dia = NULL;
		this->hora = atoi(horario.substr(0, 2).c_str());
		this->minuto = atoi(horario.substr(3, 5).c_str());
		this->segundo = atoi(horario.substr(6).c_str());
	}

	DataHora(string &dia, string &mes, string &horario) {
		this->ano = 2021;
		this->mes = this->stringMonthToIntMonth(mes);
		this->dia = atoi(dia.c_str());
		this->hora = atoi(horario.substr(0, 2).c_str());
		this->minuto = atoi(horario.substr(3, 5).c_str());
		this->segundo = atoi(horario.substr(6).c_str());
	}

	string toISO() {
		string content = "";

		content += this->getDataISO();
		content += "T";
		content += this->getHoraISO();

		return content;
	}

	string getDataISO() {
		string content = "";
		content += to_string(ano);
		content += "-";
		if (mes < 10) {
			content += "0";
		}
		content += to_string(mes);
		content += "-";
		if (dia < 10) {
			content += "0";
		}
		content += to_string(dia);
		return content;
	}

	string getHoraISO() {
		string content = "";
		if (hora < 10) {
			content += "0";
		}
		content += to_string(hora);
		content += ":";
		if (minuto < 10) {
			content += "0";
		}
		content += to_string(minuto);
		content += ":";
		if (segundo < 10) {
			content += "0";
		}
		content += to_string(segundo);
		return content;
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

//	bool operator==(const DataHora &dados) const {
//		// se houver data
//		if (this->mes != NULL) {
//			// se houver hora
//			if (this->hora != NULL) {
//				return (this->getTimeT() == dados.getTimeT());
//			} else {
//				// se for so data
//				return (this->getTimeTData() == dados.getTimeTData());
//			}
//		} else {
//			// se for so hora
//			return (this->getTimeTHora() == dados.getTimeTHora());
//		}
//	}
//
//	bool operator>(const DataHora &dados) const {
//		// se houver data
//		if (this->mes != NULL) {
//			// se houver hora
//			if (this->hora != NULL) {
//				return (this->getTimeT() > dados.getTimeT());
//			} else {
//				// se for so data
//				return (this->getTimeTData() > dados.getTimeTData());
//			}
//		} else {
//			// se for so hora
//			return (this->getTimeTHora() > dados.getTimeTHora());
//		}
//	}
//
//	bool operator<(const DataHora &dados) const {
//		// se houver data
//		if (this->mes != NULL) {
//			// se houver hora
//			if (this->hora != NULL) {
//				return (this->getTimeT() < dados.getTimeT());
//			} else {
//				// se for so data
//				return (this->getTimeTData() < dados.getTimeTData());
//			}
//		} else {
//			// se for so hora
//			return (this->getTimeTHora() < dados.getTimeTHora());
//		}
//	}
//
//	bool operator>=(const DataHora &dados) const {
//		// se houver data
//		if (this->mes != NULL) {
//			// se houver hora
//			if (this->hora != NULL) {
//				return (this->getTimeT() >= dados.getTimeT());
//			} else {
//				// se for so data
//				return (this->getTimeTData() >= dados.getTimeTData());
//			}
//		} else {
//			// se for so hora
//			return (this->getTimeTHora() >= dados.getTimeTHora());
//		}
//	}
//
//	bool operator<=(const DataHora &dados) const {
//		// se houver data
//		if (this->mes != NULL) {
//			// se houver hora
//			if (this->hora != NULL) {
//				return (this->getTimeT() <= dados.getTimeT());
//			} else {
//				// se for so data
//				return (this->getTimeTData() <= dados.getTimeTData());
//			}
//		} else {
//			// se for so hora
//			return (this->getTimeTHora() <= dados.getTimeTHora());
//		}
//	}

	time_t getTimeTData() {
		string data = "";
		data += this->getDataISO();
		data += "T00:00:00";
		struct tm date = {};
		stringstream issData(data);
		time_t dt = NULL;
		if (issData >> get_time(&date, "%Y-%m-%dT%H:%M:%S")) {
			dt = mktime(&date);
		}
		return dt;
	}

	time_t getTimeTHora() {
		string data = "2021-01-01T";
		data += this->getHoraISO();
		struct tm date = {};
		stringstream issData(data);
		time_t dt = NULL;
		if (issData >> get_time(&date, "%Y-%m-%dT%H:%M:%S")) {
			dt = mktime(&date);
		}
		return dt;
	}

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
		if (dia == "") {
			getline(issLinha, dia, ' ');
		}
		getline(issLinha, horario, ' ');
		this->dataHora = new DataHora(dia, mes, horario);
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
		} else {
			this->prioridade = NULL;
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
		} else {
			this->origemPorta = NULL;
		}
		getline(issLinha, temp, ' ');
		getline(issLinha, temp, ' ');
		this->destinoIP = this->getIPFromLine(temp);
		if (temp.find(':') != string::npos) {
			this->destinoPorta = this->getPortFromLine(temp);
		} else {
			this->destinoPorta = NULL;
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

	void setDataHora(DataHora *dataHora) {
		this->dataHora = dataHora;
	}

	void setCodigo(const string &codigo) {
		this->codigo = codigo;
	}

	void setMensagem(const string &mensagem) {
		this->mensagem = mensagem;
	}

	void setClassificacao(const string &classificacao) {
		this->classificacao = classificacao;
	}

	void setPrioridade(int prioridade) {
		this->prioridade = prioridade;
	}

	void setProtocolo(const string &protocolo) {
		this->protocolo = protocolo;
	}

	void setOrigemIp(const string &origemIp) {
		this->origemIP = origemIp;
	}

	void setOrigemPorta(int origemPorta) {
		this->origemPorta = origemPorta;
	}

	void setDestinoIp(const string &destinoIp) {
		this->destinoIP = destinoIp;
	}

	void setDestinoPorta(int destinoPorta) {
		this->destinoPorta = destinoPorta;
	}

	/**
	 * Metodo responsavel por transformar o Registro em uma string para ser exibida na tela.
	 * O metodo ainda deixa a mensagem com um tamanho maximo de 30 caracteres
	 * */
	string toString() {
		string content = "";

		content += dataHora->toISO();
		content += "\t";
		content += codigo;
		content += "\t";
		content += this->mensagem.substr(0, 30);;
		content += "\t";
		content += classificacao;
		content += "\t";
		content += to_string(prioridade); // int
		content += "\t";
		content += protocolo;
		content += "\t";
		content += origemIP;
		content += "\t";
		content += to_string(origemPorta); // int
		content += "\t";
		content += destinoIP;
		content += "\t";
		content += to_string(destinoPorta); // int

		return content;
	}

};

class Sistema {
	vector<Registro *> logs;
	string dataInicial = "", dataFinal = "", horaInicial = "", horaFinal = "", codigo = "", mensagem = "", classificacao = "", protocolo = "", origemIP = "", destinoIP = "";
	int prioridadeIni = -1, prioridadeFin = -1, portaOrigemIni = -1, portaOrigemFin = -1, portaDestinoIni = -1, portaDestinoFin = -1;
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

	/**
	 * Metodo responsavel por buscar todos os registros validos, ou seja, com o atributo filtro igual a true
	 * */
	vector<Registro *> getLogsValidos() {
		vector<Registro *> logsValidos;
		for (vector<Registro *>::iterator it = this->logs.begin(); it != this->logs.end(); ++it) {
			if ((*it)->getFiltro()) {
				logsValidos.push_back(*it);
			}
		}
		return logsValidos;
	}

	/**
	 * Metodo responsavel por fazer o filtro de data.
	 * Foi tentado usar sobrecarga de operadores mas o trecho de codigo nao era executado, ainda se encontra na classe DataHora, mas comentado
	 * */
	void filtroData(string data1, string data2) {
		int dia1, mes1, dia2, mes2;
		dia1 = atoi(data1.substr(0, 2).c_str());
		mes1 = atoi(data1.substr(3, 5).c_str());
		dia2 = atoi(data2.substr(0, 2).c_str());
		mes2 = atoi(data2.substr(3, 5).c_str());
		DataHora *dataHora1 = new DataHora(dia1, mes1);
		DataHora *dataHora2 = new DataHora(dia2, mes2);

		if (dataHora1->getTimeTData() == dataHora2->getTimeTData()) {
			cout << "Datas iguais, filtro nao aplicado" << endl;
			this->dataInicial = "";
			this->dataFinal = "";
		} else if (dataHora1->getTimeTData() > dataHora2->getTimeTData()) {
			cout << "Datas inicial maior que data final, filtro nao aplicado" << endl;
			this->dataInicial = "";
			this->dataFinal = "";
		} else {
			vector<Registro *> logsValidos = this->getLogsValidos();
			for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
				if ((*it)->getDataHora()->getTimeTData() < dataHora1->getTimeTData() ||
					(*it)->getDataHora()->getTimeTData() > dataHora2->getTimeTData()) {
					(*it)->setFiltro(false);
				}
			}
		}
	}

	/**
	 * Metodo responsavel por fazer o filtro de hora.
	 * Foi tentado usar sobrecarga de operadores mas o trecho de codigo nao era executado, ainda se encontra na classe DataHora, mas comentado
	 * */
	void filtroHora(string hora1, string hora2) {
		DataHora *dataHora1 = new DataHora(hora1);
		DataHora *dataHora2 = new DataHora(hora2);

		if (dataHora1->getTimeTHora() == dataHora2->getTimeTHora()) {
			cout << "Horas iguais, filtro nao aplicado" << endl;
			this->horaInicial = "";
			this->horaFinal = "";
		} else if (dataHora1->getTimeTHora() > dataHora2->getTimeTHora()) {
			cout << "Horas inicial maior que hora final, filtro nao aplicado" << endl;
			this->horaInicial = "";
			this->horaFinal = "";
		} else {
			vector<Registro *> logsValidos = this->getLogsValidos();
			for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
				if ((*it)->getDataHora()->getTimeTHora() < dataHora1->getTimeTHora() ||
					(*it)->getDataHora()->getTimeTHora() > dataHora2->getTimeTHora()) {
					(*it)->setFiltro(false);
				}
			}
		}
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
	 * Metodo responsavel por validar se a prioridade informada e diferente da prioridade do registro.
	 * Se a prioridadeFin for -1 (valor default)
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroPrioridade(int prioridadeIni, int prioridadeFin) {
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (prioridadeFin == -1) {
				if ((*it)->getPrioridade() != prioridadeIni) {
					(*it)->setFiltro(false);
				}
			} else {
				if ((*it)->getPrioridade() < prioridadeIni || (*it)->getPrioridade() > prioridadeFin) {
					(*it)->setFiltro(false);
				}
			}
		}
	}

	/**
	 * Metodo responsavel por validar se a porta de origem informada e diferente da prioridade do registro.
	 * Se a portaOrigemFin for -1 (valor default)
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroPortaOrigem(int portaOrigemIni, int portaOrigemFin) {
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (portaOrigemFin == -1) {
				if ((*it)->getOrigemPorta() != portaOrigemIni) {
					(*it)->setFiltro(false);
				}
			} else {
				if ((*it)->getOrigemPorta() < portaOrigemIni || (*it)->getOrigemPorta() > portaOrigemFin) {
					(*it)->setFiltro(false);
				}
			}
		}
	}

	/**
	 * Metodo responsavel por validar se a porta de destino informada e diferente da prioridade do registro.
	 * Se a portaDestinoIni for -1 (valor default)
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroPortaDestino(int portaDestinoIni, int portaDestinoFin) {
		vector<Registro *> logsValidos = this->getLogsValidos();
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			if (portaDestinoFin == -1) {
				if ((*it)->getDestinoPorta() != portaDestinoIni) {
					(*it)->setFiltro(false);
				}
			} else {
				if ((*it)->getDestinoPorta() < portaDestinoIni || (*it)->getDestinoPorta() > portaDestinoFin) {
					(*it)->setFiltro(false);
				}
			}
		}
	}

	/**
	 * Metodo responsavel por validar se o protocolo informado e diferente o protocolo do registro.
	 * Aplicando o valor false no atributo filtro
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

	/**
	 * Método responsavel por exibir um menu onde o usuário seleciona o filtros que será aplicado sobres os registros
	 * carregados na classe Sistema.
	 * */
	void aplicaFiltros() {
		int filtroOpc;
		string intervalo;
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
		switch (filtroOpc) {
			case 1:
				cout << "Informe a data inicial " << endl;
				cin >> dataInicial;
				cout << "Informe a data final " << endl;
				cin >> dataFinal;
				this->filtroData(dataInicial, dataFinal);
				break;
			case 2:
				cout << "Informe a hora inicial " << endl;
				cin >> horaInicial;
				cout << "Informe a hora final " << endl;
				cin >> horaFinal;
				this->filtroHora(horaInicial, horaFinal);
				break;
			case 3:
				do {
					cout << "Informe o codigo " << endl;
					cin.ignore();
					getline(cin, codigo);
					if (codigo == "") {
						cout << "Valor invalido, informe novamente!" << endl;
					}
				} while (codigo == "");
				this->filtroCodigo(codigo);
				break;
			case 4:
				do {
					cout << "Informe a mensagem " << endl;
					cin.ignore();
					getline(cin, mensagem);
					if (mensagem == "") {
						cout << "Valor invalido, informe novamente!" << endl;
					}
				} while (mensagem == "");
				this->filtroMensagem(mensagem);
				break;
			case 5:
				do {
					cout << "Informe a classificacao " << endl;
					cin.ignore();
					getline(cin, classificacao);
					if (classificacao == "") {
						cout << "Valor invalido, informe novamente!" << endl;
					}
				} while (classificacao == "");
				this->filtroClassificacao(classificacao);
				break;
			case 6:
				do {
					cout << "Informe a prioridade" << endl;
					cin >> prioridadeIni;
					if (prioridadeIni < 1) {
						cout << "Valor invalido, informe novamente!" << endl;
					} else {
						cout << "Deseja informar uma prioridade final? ('S' ou 'N')" << endl;
						cin >> intervalo;
						if (toUpper(intervalo) == "S") {
							cout << "Informe a prioridade final " << endl;
							cin >> prioridadeFin;
							if (prioridadeFin < 1 || prioridadeFin < prioridadeIni) {
								cout << "Valor invalido, informe novamente!" << endl;
							}
						}
					}
				} while (prioridadeIni < 1 || (prioridadeFin < prioridadeIni && toUpper(intervalo) == "S"));
				this->filtroPrioridade(prioridadeIni, prioridadeFin);
				break;
			case 7:
				do {
					cout << "Informe o protocolo " << endl;
					cin.ignore();
					getline(cin, protocolo);
					if (protocolo == "") {
						cout << "Valor invalido, informe novamente!" << endl;
					}
				} while (protocolo == "");
				this->filtroProtocolo(protocolo);
				break;
			case 8:
				do {
					cout << "Informe o endereco IP de origem" << endl;
					cin.ignore();
					getline(cin, origemIP);
					if (origemIP == "") {
						cout << "Valor invalido, informe novamente!" << endl;
					}
				} while (origemIP == "");
				this->filtroOrigemIP(origemIP);
				break;
			case 9:
				do {
					cout << "Informe a porta de origem" << endl;
					cin >> portaOrigemIni;
					if (portaOrigemIni < 1) {
						cout << "Valor invalido, informe novamente!" << endl;
					} else {
						cout << "Deseja informar uma porta de origem final? ('S' ou 'N')" << endl;
						cin >> intervalo;
						if (toUpper(intervalo) == "S") {
							cout << "Informe a porta de origem final " << endl;
							cin >> portaOrigemFin;
							if (portaOrigemFin < 1 || portaOrigemFin < portaOrigemIni) {
								cout << "Valor invalido, informe novamente!" << endl;
							}
						}
					}
				} while (portaOrigemIni < 1 || (portaOrigemFin < portaOrigemIni && toUpper(intervalo) == "S"));
				this->filtroPortaOrigem(portaOrigemIni, portaOrigemFin);
				break;
			case 10:
				do {
					cout << "Informe o endereco IP de destino" << endl;
					cin.ignore();
					getline(cin, destinoIP);
					if (destinoIP == "") {
						cout << "Valor invalido, informe novamente!" << endl;
					}
				} while (destinoIP == "");
				this->filtroDestinoIP(destinoIP);
				break;
			case 11:
				do {
					cout << "Informe a porta de destino" << endl;
					cin >> portaDestinoIni;
					if (portaDestinoIni < 1) {
						cout << "Valor invalido, informe novamente!" << endl;
					} else {
						cout << "Deseja informar uma porta de destino final? ('S' ou 'N')" << endl;
						cin >> intervalo;
						if (toUpper(intervalo) == "S") {
							cout << "Informe a porta de destino final " << endl;
							cin >> portaDestinoFin;
							if (portaDestinoFin < 1 || portaDestinoFin < portaDestinoIni) {
								cout << "Valor invalido, informe novamente!" << endl;
							}
						}
					}
				} while (portaDestinoIni < 1 || (portaDestinoFin < portaDestinoIni && toUpper(intervalo) == "S"));
				this->filtroPortaDestino(portaDestinoIni, portaDestinoFin);
				break;
			default:
				break;
		}
	}

	/**
	 * Método responsavel por exibir os filtros que estão populados.
	 * */
	void visualizarFiltros() {
		if (this->dataInicial == "" && this->dataFinal == "" && this->horaInicial == "" && this->horaFinal == "" &&
			this->codigo == "" && this->mensagem == "" && this->classificacao == "" && this->protocolo == "" &&
			this->origemIP == "" && this->destinoIP == "" &&
			this->prioridadeIni == -1 && this->prioridadeFin == -1 && this->portaOrigemIni == -1 &&
			this->portaOrigemFin == -1 && this->portaDestinoIni == -1 && this->portaDestinoFin == -1) {
			cout << "Sem filtros aplicados" << endl;
		} else {
			if (this->dataInicial != "") {
				cout << "Data inicial: " << this->dataInicial << endl;
				cout << "Data final: " << this->dataFinal << endl;
			}

			if (this->horaInicial != "") {
				cout << "Hora inicial: " << this->horaInicial << endl;
				cout << "Hora final:   " << this->horaFinal << endl;
			}

			if (this->codigo != "") {
				cout << "Codigo: " << this->codigo << endl;
			}

			if (this->mensagem != "") {
				cout << "Mensagem: " << this->mensagem << endl;
			}

			if (this->classificacao != "") {
				cout << "Classificacao: " << this->classificacao << endl;
			}

			if (this->protocolo != "") {
				cout << "Protocolo: " << this->protocolo << endl;
			}

			if (this->origemIP != "") {
				cout << "IP de Origem: " << this->origemIP << endl;
			}

			if (this->destinoIP != "") {
				cout << "IP de Destino: " << this->destinoIP << endl;
			}

			if (this->portaOrigemIni != -1 && this->portaOrigemFin == -1) {
				cout << "Porta Origem: " << this->portaOrigemIni << endl;
			} else if (this->portaOrigemIni != -1 && this->portaOrigemFin != -1) {
				cout << "Porta Origem Inicial: " << this->portaOrigemIni << endl;
				cout << "Porta Origem Final: " << this->portaOrigemFin << endl;
			}

			if (this->portaDestinoIni != -1 && this->portaDestinoFin == -1) {
				cout << "Porta Destino: " << this->portaDestinoIni << endl;
			} else if (this->portaDestinoIni != -1 && this->portaDestinoFin != -1) {
				cout << "Porta Destino Inicial: " << this->portaDestinoIni << endl;
				cout << "Porta Destino Final: " << this->portaDestinoFin << endl;
			}

			if (this->prioridadeIni != -1 && this->prioridadeFin == -1) {
				cout << "Prioridade: " << this->prioridadeIni << endl;
			} else if (this->prioridadeIni != -1 && this->prioridadeFin != -1) {
				cout << "Prioridade Inicial: " << this->prioridadeIni << endl;
				cout << "Prioridade Final: " << this->prioridadeFin << endl;
			}
		}
	}

	/**
	 * Metodo responsavel por exibir todos os registros filtrados (com o atributo filtro igual a true), exibir os filtros
	 * que foram usados e a quantidade total de registros que se encaixam nos filtros
	 * */
	void visualizarDados() {
		vector<Registro *> logsValidos = this->getLogsValidos();
		cout
				<< "DataHora\tCodigo\tMensagem\tClassificacao\tPrioridade\tProtocolo\tOrigemIP\tOrigemPorta\tDestinoIP\tDestinoPorta"
				<< endl;
		for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
			cout << (*it)->toString() << endl;
		}
		cout << endl;
		cout << "Filtros:" << endl;
		this->visualizarFiltros();
		cout << endl;
		cout << "Total de registros selecionados: " << logsValidos.size() << endl;
	}

	/**
	 * Metodo responsavel por limpar os filtros passando para o valor inicial e setando o atributo filtro como true
	 * */
	void limpaFiltros() {
		for (vector<Registro *>::iterator it = this->logs.begin(); it != this->logs.end(); ++it) {
			(*it)->setFiltro(true);
		}

		this->dataInicial = "";
		this->dataFinal = "";
		this->horaInicial = "";
		this->horaFinal = "";
		this->codigo = "";
		this->mensagem = "";
		this->classificacao = "";
		this->protocolo = "";
		this->origemIP = "";
		this->destinoIP = "";
		this->prioridadeIni = -1;
		this->prioridadeFin = -1;
		this->portaOrigemIni = -1;
		this->portaOrigemFin = -1;
		this->portaDestinoIni = -1;
		this->portaDestinoFin = -1;
	}

	/**
	 * Metodo responsavel por realizar a exportacao dos registros que estao com o atributo filtro igual a true.
	 * */
	void exportar() {
		string nomeArquivo;
		fstream arquivo;
		cout << "Insira o nome do arquivo onde deseja salvar os registros filtrados: ";
		cin >> nomeArquivo;
		nomeArquivo += ".txt";

		arquivo.open(nomeArquivo.c_str(), fstream::out);

		vector<Registro *> logsValidos = this->getLogsValidos();

		if (arquivo.is_open()) {
			cout << "Exportando..." << endl;
			arquivo
					<< "DataHora\tCodigo\tMensagem\tClassificacao\tPrioridade\tProtocolo\tOrigemIP\tOrigemPorta\tDestinoIP\tDestinoPorta";
			for (vector<Registro *>::iterator it = logsValidos.begin(); it != logsValidos.end(); ++it) {
				arquivo << (*it)->getDataHora()->toISO() << "\t";
				arquivo << (*it)->getCodigo() << "\t";
				arquivo << (*it)->getMensagem() << "\t";
				arquivo << (*it)->getClassificacao() << "\t";
				if ((*it)->getPrioridade() != NULL) {
					arquivo << (*it)->getPrioridade() << "\t";
				} else {
					arquivo << "\t";
				}
				arquivo << (*it)->getProtocolo() << "\t";
				arquivo << (*it)->getOrigemIP() << "\t";
				if ((*it)->getOrigemPorta() != NULL) {
					arquivo << (*it)->getOrigemPorta() << "\t";
				} else {
					arquivo << "\t";
				}
				arquivo << (*it)->getDestinoIP() << "\t";
				if ((*it)->getDestinoPorta() != NULL) {
					arquivo << (*it)->getDestinoPorta() << "\t";
				} else {
					arquivo << "\t";
				}
				arquivo << endl;
			}
			arquivo.close();
		}
		cout << "Exportacao finalizada com sucesso." << endl;
	}

	~Sistema() {};

};

int main() {
	int opc;
//	Sistema *sistema = new Sistema("snortsyslog");
	Sistema *sistema = new Sistema("snortsyslog-completo");

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
				break;
			case 2:
				sistema->limpaFiltros();
				break;
			case 3:
				sistema->visualizarFiltros();
				break;
			case 4:
				sistema->visualizarDados();
				break;
			case 5:
				sistema->exportar();
				break;
			default:
				cout << "Invalida" << endl;
				system("pause");
				break;

		}
	}

	return 0;
}