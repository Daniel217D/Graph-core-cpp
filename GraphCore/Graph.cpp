#include "pch.h"
#include "Graph.h"

namespace graph_tools {

	vertex::vertex() {
		CoCreateGuid(&this->id);
		this->x = 0.;
		this->y = 0.;
	}

	vertex::vertex(const double x, const double y) {
		CoCreateGuid(&this->id);
		this->x = x;
		this->y = y;
	}

	vertex::vertex(const double x, const double y, std::vector<vertex*>& adjacency) {
		CoCreateGuid(&this->id);
		this->x = x;
		this->y = y;
		this->adjacency = adjacency;
	}

	double vertex::get_x() {
		return this->x;
	}

	void vertex::set_x(const double value) {
		this->x = value;
	}

	double vertex::get_y() {
		return this->y;
	}

	void vertex::set_y(const double value) {
		this->y = value;
	}
	
	std::vector<vertex*>::iterator vertex::find_adjacency(const vertex& vertex) {
		for (auto it = this->adjacency.begin(); it != this->adjacency.end(); it++) {
			if (vertex == **it) {
				return it;
			}
		}
		return this->adjacency.end();
	}

	bool vertex::is_adjacency(vertex& vertex) {
		auto find_result = find_adjacency(vertex);
		if (find_result != this->adjacency.end())
			return true;
		return false;
	}

	bool vertex::add_adjacency(vertex& vertex) {
		if (!is_adjacency(vertex)) {
			this->adjacency.push_back(&vertex);
			return true;
		}
		else return false;
	}

	bool vertex::remove_adjacency(vertex& vertex) {
		auto result = find_adjacency(vertex);
		if (result != this->adjacency.end()) {
			this->adjacency.erase(result);
			return true;
		}
		else return false;
	}

	vertex& vertex::get_adjacency_vertex(const int index) {
		return *(this->adjacency[index]);
	}

	vertex& vertex::set_adjacency_vertex(const int index, vertex& value) {
		*(this->adjacency[index]) = value;
		return *(this->adjacency[index]);
	}

	int vertex::get_adjacency_index(vertex& vertex) {
		for (int i = 0; i < this->adjacency.size(); i++) {
			if (vertex == *(this->adjacency[i])) {
				return i;
			}
		}
		return -1;
	}
	
	int vertex::size() {
		return this->adjacency.size();
	}

	bool operator==(const vertex& first, const vertex& second) {
		if (first.id == second.id)
			return true;
		else return false;
	}

	bool operator!=(const vertex& first, const vertex& second) {
		return !(first == second);
	}

	graph::graph() {}

	graph::graph(std::vector<vertex>& vertexes) {
		this->vertexes = vertexes;
	}

	std::vector<vertex>::iterator graph::find_vertex(vertex& vertex) {
		return std::find(this->vertexes.begin(), this->vertexes.end(), vertex);
	}

	bool graph::contains(vertex& vertex) {
		auto find_result = find_vertex(vertex);
		if (find_result != this->vertexes.end())
			return true;
		return false;
	}

	bool graph::add_vertex(vertex& vertex) {
		if (!contains(vertex)) {
			this->vertexes.push_back(vertex);
			return true;
		}
		else return false;
	}

	bool graph::remove_vertex(vertex& vertex) {
		auto result = find_vertex(vertex);
		if (result != this->vertexes.end()) {
			this->vertexes.erase(result);
			return true;
		}
		else return false;
	}

	vertex& graph::get_vertex(const int index) {
		return this->vertexes[index];
	}

	vertex& graph::set_vertex(const int index, vertex& vertex) {
		this->vertexes[index] = vertex;
		return this->vertexes[index];
	}

	int graph::get_vertex_index(vertex& vertex) {
		for (int i = 0; i < this->vertexes.size(); i++) {
			if (vertex == this->vertexes[i]) {
				return i;
			}
		}
		return -1;
	}

	int graph::size() {
		return this->vertexes.size();
	}
}