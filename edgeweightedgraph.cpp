#include "edgeweightedgraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

EdgeWeightedGraph::EdgeWeightedGraph() {
}

EdgeWeightedGraph::EdgeWeightedGraph(string filename) {
	ifstream file;
	file.open(filename);
	string line, v, w;
  float weight;
	if(file.is_open()) {
		while(getline(file, line)) {
			stringstream ss(line);
			getline(ss, v, ' ');
			getline(ss, w, ' ');
			ss >> weight;
  	  addEdge(v, w, weight);
    }
    file.close();
	}
}

vector<Edge> EdgeWeightedGraph::getAdj(string v) {
	return graph[v];
}

vector<string> EdgeWeightedGraph::getVerts() {
	vector<string> keys;
	for(auto const& element : graph)
		keys.push_back(element.first);
	return keys;
}

void EdgeWeightedGraph::addEdge(string v, string w, float weight) {
  Edge e(v,w,weight);
	addToList(v, e);
	addToList(w, e);
}

string EdgeWeightedGraph::toDot() {
    // Usa um conjunto de arestas para evitar duplicatas
	set<string> edges;
	const string NEWLINE = "\n";
  ostringstream ss;
    ss << "graph {" << NEWLINE;
    ss << "rankdir = LR;" << NEWLINE;
    ss << "node [shape = circle];" << NEWLINE;
    for(auto const& v: getVerts()) {
      for (auto const& e: getAdj(v)) {
        string edge = e.v + "-" + e.w;
        if(edges.find(edge) == edges.end()) {
          ss << e.v << " -- " << e.w << " [label=\"" << e.weight << "\"]" << NEWLINE;
          edges.insert(edge);
        }
      }
    }
    ss << "}" << NEWLINE;
    return ss.str();
}

void EdgeWeightedGraph::addToList(string v, Edge e) {
	vector<Edge>& list = graph[v];
	list.push_back(e);
}
