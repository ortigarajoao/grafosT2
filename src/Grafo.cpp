#include <fstream>
#include <iostream>
#include <limits>

#include "../include/Grafo.h"

Grafo::Grafo(std::string arquivo){
  std::ifstream _arquivo(arquivo);

  if(_arquivo.is_open()){
    std::string strAux;
    int pos;
    std::getline (_arquivo, strAux);
    if(strAux.compare(0,9, "*vertices") == 0){
      int nVertices = std::stoi(strAux.substr(10));
      if(nVertices){
        _vertices = new std::vector<Vertice*>(nVertices);
        for(int i = 1; i <= nVertices; i++){
          std::getline(_arquivo, strAux);
          pos = strAux.find_first_of(" ");
          if(pos != std::string::npos){
            (*_vertices)[i] = new Vertice(i,strAux.substr(pos+1));
          } else {
            std::cout << "Erro na formatacao da linha: " << i << std::endl;
          }
        }
        std::getline(_arquivo, strAux);
        if(strAux.compare("*edges") == 0){
          std::getline(_arquivo, strAux);
          while(_arquivo.good()){
            _qtdArestas++;
            pos = strAux.find_first_of(" ");
            int vertice1 = std::stoi(strAux.substr(0,pos));
            int pos2 = strAux.find_first_of(" ",pos+1);
            int vertice2 = std::stoi(strAux.substr(pos+1,pos2-pos-1));
            double peso = std::stod(strAux.substr(pos2+1));
            (*_vertices)[vertice1]->adicionaAresta((*_vertices)[vertice2], peso);
            (*_vertices)[vertice2]->adicionaAresta((*_vertices)[vertice1], peso);
            std::getline(_arquivo, strAux);
          }
        } else {
          std::cout << "Erro de formatacao de *edges" << std::endl;
        }
      } else {
          std::cout << "Erro de transformacao de valor numerico da linha: 1" << std::endl;
      }
    } else {
      std::cout << "Erro na formatacao da linha: 1" << std::endl;
    }
  } else {
    std::cout << "Erro ao abir arquivo" << std::endl;
  }
}

Grafo::~Grafo(){
  delete _vertices;
}

int Grafo::qtdVertices(){
  return _vertices->size();
}

int Grafo::qtdArestas(){
  return _qtdArestas;
}

int Grafo::grau(int vertice){
  return (*_vertices)[vertice]->grau();
}

std::string Grafo::rotulo(int vertice){
  return (*_vertices)[vertice]->rotulo();
}

std::unordered_set<Vertice*>* Grafo::adjacentes(int vertice){
  return (*_vertices)[vertice]->adjacentes();
}

bool Grafo::haAresta(int vertice1, int vertice2){
  return (*_vertices)[vertice1]->haAresta((*_vertices)[vertice2]);
}

double Grafo::peso(int vertice1, int vertice2){
  if(this->haAresta(vertice1,vertice2)){
    return (*_vertices)[vertice1]->peso((*_vertices)[vertice2]);
  } else {
    return std::numeric_limits<double>::max();
  }
}

void Grafo::imprimirVertices(){
  for (int i = 1; i <= (*_vertices).size(); i++){
    std::cout << "Vertice: " << (*_vertices)[i]->indice() << ", Rotulo: " << (*_vertices)[i]->rotulo() << '\n';
  }
}

void Grafo::imprimirArestas(int vertice){
  std::unordered_set<Vertice*>* adj = (*_vertices)[vertice]->adjacentes();
  for (auto it = adj->begin(); it != adj->end(); ++it){
    std::cout << (*it)->indice() << ", ";
  }
  std::cout << '\n';
}

Vertice* Grafo::vertice(int v){
  return (*_vertices)[v];
}

void Grafo::buscaLargura(int v){
  std::vector<bool> visitados(this->qtdVertices());
  std::queue<Vertice*> fila;
  fila.push((*_vertices)[v]);
  visitados[v] = true;
  int nivel = 0;
  std::vector<unordered_set<Vertice*>> niveis;
  while(!fila.empty()){
    Vertice* atual = fila.pop();
    niveis[nivel] =
    std::unordered_set<Vertice*>* adj = atual->adjacentes;
    for (auto it = adj->begin(); it != adj->end(); ++it){
      if(!visitados[(*it)->indice()]){
        visitados[(*it)->indice()] = true;

      }
    }
  }
}

void Grafo::floydWarshall(){
  int qtd = this->qtdVertices();
  std::vector<double[qtd][qtd]> d;
  double temp[qtd][qtd];
  for(int i = 1; i <= qtd; i++){
    for(int j = 1; j < qtd; j++){
      if(i != j){
        if(this->haAresta(i,j)){
          temp[i][j] = this->peso(i,j);
        } else {
          temp[i][j] = std::numeric_limits<double>::max();
        }
      } else {
        temp[i][j] = 0;
      }
    }
  }
  d[0] = temp;
}


void Grafo::dfsOrdenacaoTopologica(){
  std::vector<bool> visitados(this->qtdVertices(), false);
  std::vector<int> t(this->qtdVertices(), std::numeric_limits<int>::max());
  std::vector<int> f(this->qtdVertices(), std::numeric_limits<int>::max());
  std::vector<int> antecessores(this->qtdVertices, -1);

  int tempo = 0;
  std::list<int> O
}
