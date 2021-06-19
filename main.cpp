#include <iostream>
#include <string>
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

	time_t getTimeT() {
		string data = this->toISO();
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
	 * e seta um tamanho fixo para a coluna ser exibida
	 * */
	string toString() {
		string content = "";

		content += dataHora->toISO();
		content += "\t";
		content += codigo;
		if (codigo.length() < 10) {
			for (int i = 0; i < (10 - codigo.length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += this->mensagem.substr(0, 30);
		if (mensagem.length() < 30) {
			for (int i = 0; i < (30 - mensagem.length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += classificacao;
		if (classificacao.length() < 30) {
			for (int i = 0; i < (30 - classificacao.length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += to_string(prioridade); // int
		if (to_string(prioridade).length() < 10) {
			for (int i = 0; i < (10 - to_string(prioridade).length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += protocolo;
		if (protocolo.length() < 10) {
			for (int i = 0; i < (10 - protocolo.length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += origemIP;
		if (origemIP.length() < 20) {
			for (int i = 0; i < (20 - origemIP.length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += to_string(origemPorta); // int
		if (to_string(origemPorta).length() < 20) {
			for (int i = 0; i < (20 - to_string(origemPorta).length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += destinoIP;
		if (destinoIP.length() < 20) {
			for (int i = 0; i < (20 - destinoIP.length()); i++) {
				content += " ";
			}
		}
		content += "\t";
		content += to_string(destinoPorta); // int
		if (to_string(destinoPorta).length() < 20) {
			for (int i = 0; i < (20 - to_string(destinoPorta).length()); i++) {
				content += " ";
			}
		}

		return content;

	}

};


template<class T>
class Node {
private:
	T element;
	Node *next;
	Node *previous;
public:
	Node(T element) {
		this->element = element;
		this->next = NULL;
	}

	T getElement() {
		return this->element;
	}

	void setElement(T element) {
		this->element = element;
	}

	Node *getNext() {
		return this->next;
	}

	void setNext(Node *next) {
		this->next = next;
	}

	Node *getPrevious() {
		return this->previous;
	}

	void setPrevious(Node *previous) {
		this->previous = previous;
	}
};

template<class T>
class LinkedList {
private:
	Node<T> *head;
	Node<T> *tail;
	Node<T> *sorted;
	int length;
public:
	LinkedList() {
		head = tail = 0;
		length = 0;
	}

	bool isEmpty() {
		return head == 0;
	}

	int size() {
		return this->length;
	}

	void insert(T element) {
		bool empty = this->isEmpty();

		Node<T> *node = new Node<T>(element);

		node->setPrevious(this->tail);
		node->setNext(NULL);

		if (empty) {
			this->tail = this->head = node;
		} else {
			this->tail->setNext(node);
			this->tail = node;
		}
		this->length++;
	}

	Node<T> *getHead() {
		return this->head;
	}

	Node<T> *getTail() {
		return this->tail;
	}

	void insertionSort(int atributo) {
		sorted = NULL;
		Node<T> *current = this->getHead();
		while (current != NULL) {
			Node<T> *next = current->getNext();
			sortedInsert(current, atributo);
			current = next;
		}
		head = sorted;
	}

	void sortedInsert(Node<T> *newNode, int atributo) {
		if (sorted == NULL || this->testAtribute(atributo, ">", sorted->getElement(), newNode->getElement())) {
			newNode->setNext(sorted);
			sorted = newNode;
		}
		else {
			Node<T> *current = sorted;
			while (current->getNext() != NULL && this->testAtribute(atributo, "<=", current->getNext()->getElement(), newNode->getElement())) {
				if (this->testAtribute(atributo, "==", current->getNext()->getElement(), newNode->getElement())) {
					if (this->testAtribute(atributo, ">", current->getNext()->getElement(), newNode->getElement())) {
						break;
					}
				}
				current = current->getNext();
			}
			newNode->setNext(current->getNext());
			current->setNext(newNode);
		}
	}

	/**
	 * Esse metodo e o mais confuso, ele visa comparar 2 elementos para realizar a ordenacao.
	 * Para o funcionamento dele precisa passar o id do atributo, o tipo de comparacao desejada e os dois elementos,
	 * com isso o metodo pega o tipo do atributo e a devidada comparcao. No caso de string eh passada prara um valor
	 * inteiro com base no tamanho da menor string e no caso de DataHora o TimeT que eh comparado.
	 * Certamente tem um jeito mais facil de fazer isso, mas eu nao sei... ainda.
	 * */
	bool testAtribute(int atributo, string testType, T element1, T element2) {
		int tam, valor1, valor2;
		switch (atributo) {
			case 1:
				// DataHora
				valor1 = element1->getDataHora()->getTimeT();
				valor2 = element2->getDataHora()->getTimeT();
				break;
			case 2:
				// Codigo
				tam = element1->getCodigo().size() < element2->getCodigo().size() ? element1->getCodigo().size() : element2->getCodigo().size();
				valor1 = this->stringToIntValue(element1->getCodigo(), tam);
				valor2 = this->stringToIntValue(element2->getCodigo(), tam);
				break;
			case 3:
				// Mensagem
				tam = element1->getMensagem().size() < element2->getMensagem().size() ? element1->getMensagem().size() : element2->getMensagem().size();
				valor1 = this->stringToIntValue(element1->getMensagem(), tam);
				valor2 = this->stringToIntValue(element2->getMensagem(), tam);
				break;
			case 4:
				// Classificacao
				tam = element1->getClassificacao().size() < element2->getClassificacao().size() ? element1->getClassificacao().size() : element2->getClassificacao().size();
				valor1 = this->stringToIntValue(element1->getClassificacao(), tam);
				valor2 = this->stringToIntValue(element2->getClassificacao(), tam);
				break;
			case 5:
				// Prioridade
				valor1 = element1->getPrioridade();
				valor2 = element2->getPrioridade();
				break;
			case 6:
				// Protocolo
				tam = element1->getProtocolo().size() < element2->getProtocolo().size() ? element1->getProtocolo().size() : element2->getProtocolo().size();
				valor1 = this->stringToIntValue(element1->getProtocolo(), tam);
				valor2 = this->stringToIntValue(element2->getProtocolo(), tam);
				break;
			case 7:
				// OrigemIP
				tam = element1->getOrigemIP().size() < element2->getOrigemIP().size() ? element1->getOrigemIP().size() : element2->getOrigemIP().size();
				valor1 = this->stringToIntValue(element1->getOrigemIP(), tam);
				valor2 = this->stringToIntValue(element2->getOrigemIP(), tam);
				break;
			case 8:
				// OrigemPorta
				valor1 = element1->getOrigemPorta();
				valor2 = element2->getOrigemPorta();
				break;
			case 9:
				// DestinoIP
				tam = element1->getDestinoIP().size() < element2->getDestinoIP().size() ? element1->getDestinoIP().size() : element2->getDestinoIP().size();
				valor1 = this->stringToIntValue(element1->getDestinoIP(), tam);
				valor2 = this->stringToIntValue(element2->getDestinoIP(), tam);
				break;
			case 10:
				// DestinoPorta
				valor1 = element1->getDestinoPorta();
				valor2 = element2->getDestinoPorta();
				break;
		}

		if (testType == ">") {
			return valor1 > valor2;
		} else if (testType == "<") {
			return valor1 < valor2;
		} else if (testType == "==") {
			return valor1 == valor2;
		} else if (testType == ">=") {
			return valor1 >= valor2;
		} else if (testType == "<=") {
			return valor1 <= valor2;
		}
	}

	Node<T> *getMidNode(Node<T> *start, Node<T> *last) {
		if (start == NULL) {
			return NULL;
		}
		Node<T> *atual = start;
		Node<T> *proximo = start->getNext();
		while (proximo != last) {
			proximo = proximo->getNext();
			if (proximo != last) {
				atual = atual->getNext();
				proximo = proximo->getNext();
			}
		}
		return atual;
	}

	Node<T> *binarySearch(int atributo, string value) {
		struct Node<T> *start = this->head;
		struct Node<T> *last = NULL;
		do {
			Node<T> *mid = getMidNode(start, last);
			if (mid == NULL) {
				return NULL;
			}
			int atributoIntMid = NULL;
			string atributoString = "";
			int tam = NULL;
			switch(atributo) {
				case 1:
					// DataHora
					atributoIntMid = mid->getElement()->getDataHora()->getTimeT();
					break;
				case 2:
					// Codigo
					tam = mid->getElement()->getCodigo().size() < value.size() ? mid->getElement()->getCodigo().size() : value.size();
					atributoString = mid->getElement()->getCodigo();
					break;
				case 3:
					// Mensagem
					tam = mid->getElement()->getMensagem().size() < value.size() ? mid->getElement()->getMensagem().size() : value.size();
					atributoString = mid->getElement()->getMensagem();
					break;
				case 4:
					// Classificacao
					tam = mid->getElement()->getClassificacao().size() < value.size() ? mid->getElement()->getClassificacao().size() : value.size();
					atributoString = mid->getElement()->getClassificacao();
					break;
				case 5:
					// Prioridade
					atributoIntMid = mid->getElement()->getPrioridade();
					break;
				case 6:
					// Protocolo
					tam = mid->getElement()->getProtocolo().size() < value.size() ? mid->getElement()->getProtocolo().size() : value.size();
					atributoString = mid->getElement()->getProtocolo();
					break;
				case 7:
					// OrigemIP
					tam = mid->getElement()->getOrigemIP().size() < value.size() ? mid->getElement()->getOrigemIP().size() : value.size();
					atributoString = mid->getElement()->getOrigemIP();
					break;
				case 8:
					// OrigemPorta
					atributoIntMid = mid->getElement()->getOrigemPorta();
					break;
				case 9:
					// DestinoIP
					tam = mid->getElement()->getDestinoIP().size() < value.size() ? mid->getElement()->getDestinoIP().size() : value.size();
					atributoString = mid->getElement()->getDestinoIP();
					break;
				case 10:
					// DestinoPorta
					atributoIntMid = mid->getElement()->getDestinoPorta();
					break;
			}
			if (atributoString != "") {
				mid = NULL;
//				if (this->stringToIntValue(atributoString, tam) == this->stringToIntValue(value, tam)) {
//					return mid;
//				} else if (this->stringToIntValue(atributoString, tam) < this->stringToIntValue(value, tam)) {
//					start = mid->getNext();
//				} else {
//					last = mid;
//				}
			} else {
				if (atributoIntMid == atoi(value.c_str())) {
					return mid;
				} else if (atributoIntMid < atoi(value.c_str())) {
					start = mid->getNext();
				} else {
					last = mid;
				}
			}
		} while (last == NULL || last != start);
		return NULL;
	}

	void printlist() {
		Node<Registro *> *current = head;
		cout
				<< "DataHora         \t" // 20
				<< "Codigo    \t"//10
	   			<< "Mensagem                      \t" //30
		  		<< "Classificacao                 \t"
		 		<< "Prioridade\t"
				<< "Protocolo \t"
	   			<< "OrigemIP            \t"
		  		<< "OrigemPorta         \t"
		 		<< "DestinoIP           \t"
				<< "DestinoPorta"
				<< endl;
		while (current != NULL) {
			cout << current->getElement()->toString() << endl;
			current = current->getNext();
		}
	}

	int stringToIntValue(string s1, int byte) {
		s1 = this->toUpper(s1);
		int size = 0;
		for (int i = 0; i < byte; i++) {
			size += s1[i];
		}
		return size;
	}

	/**
	 * Necessario replicar para testes de filtro de strings
	 * */
	string toUpper(string param) {
		string up = "";
		for (int i = 0; i < param.size(); i++) {
			up += toupper(param[i]);
		}
		return up;
	}

};

class Sistema {
	LinkedList<Registro *> *logs;
	LinkedList<Registro *> *ordenados;
	string dataInicial = "", dataFinal = "", horaInicial = "", horaFinal = "", codigo = "", mensagem = "", classificacao = "", protocolo = "", origemIP = "", destinoIP = "";
	int prioridadeIni = -1, prioridadeFin = -1, portaOrigemIni = -1, portaOrigemFin = -1, portaDestinoIni = -1, portaDestinoFin = -1;
public:
	Sistema(string nomeArquivo) {
		fstream arq;
		string line;
		arq.open(nomeArquivo.c_str(), fstream::in);
		logs = new LinkedList<Registro *>();
		ordenados = new LinkedList<Registro *>();
		if (arq.is_open()) {
			while (!arq.eof()) {
				getline(arq, line, '\n');
				if (line != "") {
					Registro *record = new Registro(line);
					logs->insert(record);
				}
			}
		} else {
			cout << "Erro ao abrir o arquivo!" << endl;
		}
	}

	/**
	 * Metodo responsavel por buscar todos os registros validos, ou seja, com o atributo filtro igual a true
	 * */
	LinkedList<Registro *> *getLogsValidos() {
		LinkedList<Registro *> *logsValidos = new LinkedList<Registro *>();
		Node<Registro *> *current = this->logs->getHead();
		while (current != NULL) {
			if (current->getElement()->getFiltro()) {
				logsValidos->insert(current->getElement());
			}
			current = current->getNext();
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
			LinkedList<Registro *> *logsValidos = this->getLogsValidos();
			Node<Registro *> *current = logsValidos->getHead();
			while (current != NULL) {
				if (current->getElement()->getDataHora()->getTimeTData() < dataHora1->getTimeTData() ||
					current->getElement()->getDataHora()->getTimeTData() > dataHora2->getTimeTData()) {
					current->getElement()->setFiltro(false);
				}
				current = current->getNext();
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
			LinkedList<Registro *> *logsValidos = this->getLogsValidos();
			Node<Registro *> *current = logsValidos->getHead();
			while (current != NULL) {
				if (current->getElement()->getDataHora()->getTimeTHora() < dataHora1->getTimeTHora() ||
					current->getElement()->getDataHora()->getTimeTHora() > dataHora2->getTimeTHora()) {
					current->getElement()->setFiltro(false);
				}
				current = current->getNext();
			}
		}
	}

	/**
	 * Metodo responsavel por validar se o codigo informado e diferente do codigo do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroCodigo(string codigo) {
		codigo = this->toUpper(codigo);
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (this->toUpper(current->getElement()->getCodigo()) != codigo) {
				current->getElement()->setFiltro(false);
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se a mensagem informada e diferente da mensagem do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroMensagem(string mensagem) {
		mensagem = this->toUpper(mensagem);
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (this->toUpper(current->getElement()->getMensagem()) != mensagem) {
				current->getElement()->setFiltro(false);
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se a classificacao informado e diferente a classificacao do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroClassificacao(string classificacao) {
		classificacao = this->toUpper(classificacao);
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (this->toUpper(current->getElement()->getClassificacao()) != classificacao) {
				current->getElement()->setFiltro(false);
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se a prioridade informada e diferente da prioridade do registro.
	 * Se a prioridadeFin for -1 (valor default)
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroPrioridade(int prioridadeIni, int prioridadeFin) {
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (prioridadeFin == -1) {
				if (current->getElement()->getPrioridade() != prioridadeIni) {
					current->getElement()->setFiltro(false);
				}
			} else {
				if (current->getElement()->getPrioridade() < prioridadeIni ||
					current->getElement()->getPrioridade() > prioridadeFin) {
					current->getElement()->setFiltro(false);
				}
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se a porta de origem informada e diferente da prioridade do registro.
	 * Se a portaOrigemFin for -1 (valor default)
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroPortaOrigem(int portaOrigemIni, int portaOrigemFin) {
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (portaOrigemFin == -1) {
				if (current->getElement()->getOrigemPorta() != portaOrigemIni) {
					current->getElement()->setFiltro(false);
				}
			} else {
				if (current->getElement()->getOrigemPorta() < portaOrigemIni ||
					current->getElement()->getOrigemPorta() > portaOrigemFin) {
					current->getElement()->setFiltro(false);
				}
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se a porta de destino informada e diferente da prioridade do registro.
	 * Se a portaDestinoIni for -1 (valor default)
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroPortaDestino(int portaDestinoIni, int portaDestinoFin) {
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (portaDestinoFin == -1) {
				if (current->getElement()->getDestinoPorta() != portaDestinoIni) {
					current->getElement()->setFiltro(false);
				}
			} else {
				if (current->getElement()->getDestinoPorta() < portaDestinoIni ||
					current->getElement()->getDestinoPorta() > portaDestinoFin) {
					current->getElement()->setFiltro(false);
				}
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se o protocolo informado e diferente o protocolo do registro.
	 * Aplicando o valor false no atributo filtro
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroProtocolo(string protocolo) {
		protocolo = this->toUpper(protocolo);
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (this->toUpper(current->getElement()->getProtocolo()) != protocolo) {
				current->getElement()->setFiltro(false);
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se o endereco IP de origem informado e diferente o endereco IP de origem do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroOrigemIP(string origemIP) {
		origemIP = this->toUpper(origemIP);
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (this->toUpper(current->getElement()->getOrigemIP()) != origemIP) {
				current->getElement()->setFiltro(false);
			}
			current = current->getNext();
		}
	}

	/**
	 * Metodo responsavel por validar se o endereco IP de destino informado e diferente o endereco IP de destino do registro.
	 * Aplicando o valor false no atributo filtro
	 * */
	void filtroDestinoIP(string destinoIP) {
		destinoIP = this->toUpper(destinoIP);
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		Node<Registro *> *current = logsValidos->getHead();
		while (current != NULL) {
			if (this->toUpper(current->getElement()->getDestinoIP()) != destinoIP) {
				current->getElement()->setFiltro(false);
			}
			current = current->getNext();
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
		LinkedList<Registro *> *logsValidos = this->getLogsValidos();
		logsValidos->printlist();
		cout << endl;
		cout << "Filtros:" << endl;
		this->visualizarFiltros();
		cout << endl;
		cout << "Total de registros selecionados: " << logsValidos->size() << endl;
	}

	/**
	 * Metodo responsavel por limpar os filtros passando para o valor inicial e setando o atributo filtro como true
	 * */
	void limpaFiltros() {
		Node<Registro *> *current = this->logs->getHead();
		while (current != NULL) {
			current->getElement()->setFiltro(true);
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
		if (this->ordenados->isEmpty()) {
			cout << "Lista nao ordenada. Necessario ordenar primeiro. Selecione abaixo um algoritmo de ordenacao. " << endl;
			this->ordenarDadosFiltrados();
			cout << "Agora pode ser feita a exportacao de dados." << endl;
			cout << endl;
		}

		string nomeArquivo;
		fstream arquivo;
		cout << "Insira o nome do arquivo onde deseja salvar os registros filtrados: ";
		cin >> nomeArquivo;
		nomeArquivo += ".txt";

		arquivo.open(nomeArquivo.c_str(), fstream::out);

		Node<Registro *> *current = this->ordenados->getHead();

		if (arquivo.is_open()) {
			cout << "Exportando..." << endl;
			arquivo
					<< "DataHora\tCodigo\tMensagem\tClassificacao\tPrioridade\tProtocolo\tOrigemIP\tOrigemPorta\tDestinoIP\tDestinoPorta";
			arquivo << endl;
			while (current != NULL) {
				arquivo << current->getElement()->getDataHora()->toISO() << "\t";
				arquivo << current->getElement()->getCodigo() << "\t";
				arquivo << current->getElement()->getMensagem() << "\t";
				arquivo << current->getElement()->getClassificacao() << "\t";
				if (current->getElement()->getPrioridade() != NULL) {
					arquivo << current->getElement()->getPrioridade() << "\t";
				} else {
					arquivo << "\t";
				}
				arquivo << current->getElement()->getProtocolo() << "\t";
				arquivo << current->getElement()->getOrigemIP() << "\t";
				if (current->getElement()->getOrigemPorta() != NULL) {
					arquivo << current->getElement()->getOrigemPorta() << "\t";
				} else {
					arquivo << "\t";
				}
				arquivo << current->getElement()->getDestinoIP() << "\t";
				if (current->getElement()->getDestinoPorta() != NULL) {
					arquivo << current->getElement()->getDestinoPorta() << "\t";
				} else {
					arquivo << "\t";
				}
				arquivo << endl;
				current = current->getNext();
			}
			arquivo.close();
		}
		cout << "Exportacao finalizada com sucesso." << endl;
	}

	void pesquisaBinaria() {
		if (this->ordenados->isEmpty()) {
			cout << "Lista nao ordenada. Necessario ordenar primeiro. Selecione abaixo um algoritmo de ordenacao. " << endl;
			this->ordenarDadosFiltrados();
			cout << "Agora pode ser feita a pesquisa binaria. " << endl;
			cout << endl;
		}
		string filtro;
		cout << "Informe um filtro: " << endl;
		cin >> filtro;
		Node<Registro *> *node = NULL;
		for (int i = 1; i <= 10; i++) {
			node = this->ordenados->binarySearch(i, filtro);
			if (node != NULL) {
				break;
			}
		}
		if (node != NULL) {
			cout << node->getElement()->toString() << endl;
		} else {
			cout << "Nenhum registro encontrado" << endl;
		}
	}

	void ordenarDadosFiltrados() {
		this->ordenados = this->getLogsValidos();
		int tipoOrder, atributo;
		cout << "1 - Metodo simples   - InsertionSort" << endl;
		cout << "2 - Metodo eficiente - QuickSort" << endl;
		cin >> tipoOrder;
		switch (tipoOrder) {
			case 1:
				do {
					cout << " 1 - Ordernar por dataHora" << endl;
					cout << " 2 - Ordernar por codigo" << endl;
					cout << " 3 - Ordernar por mensagem" << endl;
					cout << " 4 - Ordernar por classificacao" << endl;
					cout << " 5 - Ordernar por prioridade" << endl;
					cout << " 6 - Ordernar por protocolo" << endl;
					cout << " 7 - Ordernar por origemIP" << endl;
					cout << " 8 - Ordernar por origemPorta" << endl;
					cout << " 9 - Ordernar por destinoIP" << endl;
					cout << "10 - Ordernar por destinoPorta" << endl;
					cin >> atributo;
				} while (atributo < 1 || atributo > 10);
				this->ordenados->insertionSort(atributo);
				this->ordenados->printlist();
				break;
			case 2:
				do {
					cout << " 1 - Ordernar por dataHora" << endl;
					cout << " 2 - Ordernar por codigo" << endl;
					cout << " 3 - Ordernar por mensagem" << endl;
					cout << " 4 - Ordernar por classificacao" << endl;
					cout << " 5 - Ordernar por prioridade" << endl;
					cout << " 6 - Ordernar por protocolo" << endl;
					cout << " 7 - Ordernar por origemIP" << endl;
					cout << " 8 - Ordernar por origemPorta" << endl;
					cout << " 9 - Ordernar por destinoIP" << endl;
					cout << "10 - Ordernar por destinoPorta" << endl;
					cin >> atributo;
				} while (atributo < 1 || atributo > 10);
//				this->ordenados->quickSort(atributo);
				this->ordenados->printlist();
				break;
			default:
				cout << "Opcao invalida" << endl;
				break;
		}
	}

	~Sistema() {};

};

int main() {
	int opc;
//	Sistema *sistema = new Sistema("snortsyslog-completo");
//	Sistema *sistema = new Sistema("snortsyslog");
	Sistema *sistema = new Sistema("snortsyslog-2");

	do {
		system("cls");
		cout << "1 - Adicionar filtro" << endl;
		cout << "2 - Limpar filtros" << endl;
		cout << "3 - Visualizar filtros" << endl;
		cout << "4 - Visualizar dados" << endl;
		cout << "5 - Ordenar dados filtrados" << endl;
		cout << "6 - Pesquisa binaria" << endl;
		cout << "7 - Exportar dados" << endl;
		cout << "8 - Sair" << endl;
		cin >> opc;

		switch (opc) {
			case 1:
				sistema->aplicaFiltros();
				system("pause");
				break;
			case 2:
				sistema->limpaFiltros();
				system("pause");
				break;
			case 3:
				sistema->visualizarFiltros();
				system("pause");
				break;
			case 4:
				sistema->visualizarDados();
				system("pause");
				break;
			case 5:
				sistema->ordenarDadosFiltrados();
				system("pause");
				break;
			case 6:
				sistema->pesquisaBinaria();
				system("pause");
				break;
			case 7:
				sistema->exportar();
				system("pause");
				break;
			case 8:
				cout << "Saindo..." << endl;
				break;
			default:
				cout << "Invalida" << endl;
				system("pause");
				break;

		}
	} while (opc != 8);

	return 0;
}