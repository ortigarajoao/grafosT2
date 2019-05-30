#ifndef GRAFO_H
#define GRAFO_H

#include "../include/Vertice.h"

#include <vector>
#include <string>

class Grafo{

public:
  Grafo();
  ~Grafo();
  Grafo(std::string arquivo);
  bool ler(std::string arquivo);

  int qtdVertices();
  int qtdArestas();
  int grau(int vertice);
  std::string rotulo(int vertice);
  std::unordered_set<Vertice*>* adjacentes(int vertice);
  bool haAresta(int vertice1, int vertice2);
  double peso(int vertice1, int vertice2);
  void imprimirVertices();
  void imprimirArestas(int vertice);
  Vertice* vertice(int v);

  void buscaLargura(int v);
  void floydWarshall();

  void fortementeConexa();
  void dfsCormen();
  void dfsVisit(int v, int tempo);

  void dfsOrdenacaoTopologica();
private:
  std::vector<Vertice*>* _vertices;
  int _qtdArestas = 0; //Para diminuir procuras

};

#endif //GRAFO_H
