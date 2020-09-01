#include<vector>
#include<windows.h>

#pragma once
//����������� ��� ������ � �������.
namespace graph_tools {

	//������������ ������� �����.
	class vertex {
	private:
		//���������� ������������� �����.
		GUID id;
		//���������� X.
		double x;
		//���������� Y.
		double y;
		//������ ������� ������ (������, � ������� ����� ��������� �� ����).
		std::vector<vertex*> adjacency;

		//���������� �������� �� ��������� ������� � ������ ��������� ��� adjacency.end(), ���� ����� �� ������.
		std::vector<vertex*>::iterator find_adjacency(const vertex& vertex);
		//������������� ������� � ������ ���������.
		vertex& set_adjacency_vertex(const int index, vertex& value);
	public:
		//�������������� ����� vertex.
		vertex();
		//�������������� ����� vertex.
		vertex(const double x, const double y);
		//�������������� ����� vertex.
		vertex(const double x, const double y, std::vector<vertex*>& adjacency);
		//�������� ���������� X.
		double get_x();
		//������������� ���������� X.
		void set_x(const double value);
		//�������� ���������� Y.
		double get_y();
		//������������� ���������� Y.
		void set_y(const double value);
		//���������� true, ���� ������ ������� ������ � ������ ��������� (adjacency �������� vertex).
		bool is_adjacency(vertex& vertex);
		//��������� ������� � ������ ��������� � ������. ���������� true, ���� ���������� �������.
		bool add_adjacency(vertex& vertex);
		//�������� ������� �� ������ ��������� � ������. ���������� true, ���� �������� �������.
		bool remove_adjacency(vertex& vertex);
		//�������� ������� �� ������ ���������.
		vertex& get_adjacency_vertex(const int index);
		//�������� ������ ������� ������� � ������ ��������� ��� -1, ���� ������ ������� ��� �� ����������.
		int get_adjacency_index(vertex& vertex);
		//���������� ���������� ������� ������.
		int size();
		//���������� true, ���� ������� �������� �������������� (����� �� id).
		friend bool operator== (const vertex& first, const vertex& second);
		//���������� true, ���� ������� �� �������� �������������� (����� �� id).
		friend bool operator!= (const vertex& first, const vertex& second);
	};

	//������������ ����.
	class graph
	{
	private:
		//������� �����.
		std::vector<vertex> vertexes;

		//���������� �������� �� ��������� ������� ��� vertexes.end(), ���� ����� �� ������.
		std::vector<vertex>::iterator find_vertex(vertex& vertex);
		//������������� ������� �����.
		vertex& set_vertex(const int index, vertex& vertex);
	public:
		//�������������� ����� graph.
		graph();
		//�������������� ����� graph.
		graph(std::vector<vertex>& vertexes);
		//��������� ������� � ����. ���������� true, ���� ���������� �������.
		bool add_vertex(vertex& vertex);
		//������� ������� �� �����. ���������� true, ���� ���������� �������.
		bool remove_vertex(vertex& vertex);
		//���������� true, ���� ��������� ������� ���������� � �����.
		bool contains(vertex& vertex);
		//�������� ������� �����.
		vertex& get_vertex(const int index);
		//�������� ������ ������� � ����� ��� -1, ���� ������ ������� ��� �� ����������.
		int get_vertex_index(vertex& vertex);
		//���������� ���������� ������.
		int size();
		//���������� ������������ ��������� ������ ���������� ������������.
		std::vector<vertex*> get_max_int_stab_vertex();
		//���������� ����������� ��������� ������ ������� ������������.
		std::vector<vertex*> get_min_ext_stab_vertex();
		//���������� ���� �����.
		std::vector<vertex*> get_cores();
	};
}