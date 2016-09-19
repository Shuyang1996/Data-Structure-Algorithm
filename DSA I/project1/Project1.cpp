#include <iostream>
#include <fstream>
#include <cstring>
#include <list>
#include <vector>
#include <sstream>
using namespace std;

template <typename type>
class Simplelist {
	class Node {
		public:
			type data;
			Node * next; //node for next element
		
			Node(): next(0) {data = type();}

			void setData(type newdata){
				data = newdata;
			}

			void setNext(Node * newnext){
				next = newnext;
			}
	}; //closing tag for Node class

	private:
		Node * top;
		Node * back;
		int count;
		string Lname;

	protected:
		Simplelist(string nm): top(0), back(0), count(0), Lname(nm){};
		void inserts(type data);
		void inserte(type data);
		type removes();
	
		public:
		
		string listname(){
			return Lname;
		};

		int size(){
			return count;
		};

		virtual void push(type adata) = 0;
		virtual type pop() = 0;

};

template<typename type>
void Simplelist<type>:: inserts(type data){
	Node * temp =  new Node();
	temp->setData(data);

	if( top == NULL){
		temp->setNext(NULL);
		back = top = temp; //temp now is the head of the list
	}else{
		temp->setNext(top);
		top = temp;	
	}
	count++;
};

template<typename type>
void Simplelist<type>::inserte(type data){
	Node * temp = new Node();
	temp->setData(data);
	if(top == NULL){
		temp->setNext(NULL);
		back = top = temp;
	} else {
		back->setNext(temp);
		temp->setNext(NULL);
		back = temp;
	}
	count++;
};

template <typename type>
type Simplelist<type>::removes(){
	Node * temp = top->next;
	type popout = top->data;
	delete top;
	top = temp;
	count--;
	return popout;
}

template <typename type>
class stack : public Simplelist<type> {
	public:
		void push(type pdata){
			this->inserts(pdata);
		};
		type pop(){
			return this->removes();
		};
		stack(string nm):Simplelist<type>::Simplelist(nm){};
};

template <typename type>
class queue : public Simplelist<type>	{//enqueue
	public:
		void push(type adata){
			this->inserte(adata);
		};
		type pop(){//dequeue
			return this->removes();
		};
		queue(string nm):Simplelist<type>::Simplelist(nm){};
		
};

//this function searches through list to find list has name "name"
//if the list found, it returns the pointer of this list
//if not, it will return NULL as default. 
template<typename type>
Simplelist<type>* searchList(list<Simplelist<type>*> &listPtr, vector<string> &processed){
	string name = processed[1];

	for(auto &item : listPtr){ // NOTE: this is C++ 11 iterator style. auto makes things easier
		
		if(item->listname() == name){
			return item;
		}
	}
	return NULL; //default
};

template<typename type>
void createStackQueue(list<Simplelist<type>*> &listPtr, vector<string> &processed){
	string listname = processed[1];
	if(processed[2] == "stack"){
		listPtr.insert(listPtr.begin(), new stack<type>(listname));
		
	}else if(processed[2] == "queue"){
		listPtr.insert(listPtr.end(), new queue<type>(listname));
	}
	
};

template<typename type>
void executePush(Simplelist<type> *listPtr, vector<string> &processed){
	type element;
	stringstream converter;
	//stringstream as a converter
	converter << processed[2];
	converter >> element;
	listPtr->push(element);
};

template<typename type>
void executePop(Simplelist<type> *listPtr, vector<string> &processed, ofstream &outputfile){
	if(listPtr->size() == 0){
		outputfile<<"ERROR: This list is empty!"<<endl; 
	}else{
		type element = listPtr->pop();
		outputfile<<"Value popped: "<<element<<endl;
	}
};

//large process function as promised
template <typename type>
void largeProcess(list<Simplelist<type>*> &listPtr, vector<string>processed, ofstream &outputfile){
	Simplelist<type>* listCurrent = searchList(listPtr, processed);
	if(processed[0] == "create" && listCurrent == NULL){
		createStackQueue(listPtr, processed);

	}else if(processed[0] == "create" && listCurrent != NULL){
		outputfile<<"ERROR: This name already exists!"<<endl;

	}else if(processed[0] == "push" && listCurrent == NULL){
		outputfile<<"ERROR: This name does not exist!"<<endl;

	}else if(processed[0] == "push" && listCurrent != NULL){
		executePush(listCurrent, processed);

	}else if(processed[0] == "pop" && listCurrent == NULL && processed[2] == ""){
		outputfile<<"ERROR: This name does not exist!"<<endl;

	}else if(processed[0] == "pop" && listCurrent != NULL && processed[2] == ""){
		executePop(listCurrent, processed, outputfile);
	}
};

int main (){
	list<Simplelist<int>*> listSLi;
	list<Simplelist<double>*> listSLd;
	list<Simplelist<string>*> listSLs;

	string inputName;
	string outputName;

	cout << "Enter name of input file: ";
	cin >> inputName;
	ifstream inputFile (inputName.c_str());

	cout << "Enter name of output file: ";
	cin >> outputName;
	ofstream outputFile (outputName.c_str());

	string buffer;
	string line;
	
	while(getline(inputFile,line)){

		vector<string> parsedCommands;
		stringstream stringInput(line); 

		while(stringInput >> buffer ){
			parsedCommands.push_back(buffer);
		}

		if(parsedCommands.size() == 2){
			parsedCommands.push_back("");
		}

		outputFile << "PROCESSING COMMAND: "<<line<<endl;

		switch((parsedCommands[1])[0]){ //(parsedCommands[1])[0] is the first character
			case 'i':
			largeProcess(listSLi, parsedCommands, outputFile);
			break;

			case 'd':
			largeProcess(listSLd, parsedCommands, outputFile);
			break;

			default:
			largeProcess(listSLs, parsedCommands, outputFile);
			break;	
		}		
	}

	inputFile.close();
	outputFile.close();

	return 0;
}