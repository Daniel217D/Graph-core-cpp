#include<vector>
#include<windows.h>

#pragma once
//Инструменты для работы с графами.
namespace graph_tools {

	//Представляет вершину графа.
	class vertex {
	private:
		//Уникальный идентификатор точки.
		GUID id;
		//Координата X.
		double x;
		//Координата Y.
		double y;
		//Список смежных вершин (вершин, в которые можно добраться из этой).
		std::vector<vertex*> adjacency;

		//Возвращает итератор на найденную вершину в списке смежности или adjacency.end(), если такой не найден.
		std::vector<vertex*>::iterator find_adjacency(const vertex& vertex);
		//Устанавливает вершину в список смежности.
		vertex& set_adjacency_vertex(const int index, vertex& value);
	public:
		//Инициализирует класс vertex.
		vertex();
		//Инициализирует класс vertex.
		vertex(const double x, const double y);
		//Инициализирует класс vertex.
		vertex(const double x, const double y, std::vector<vertex*>& adjacency);
		//Получает координату X.
		double get_x();
		//Устанавливает координату X.
		void set_x(const double value);
		//Получает координату Y.
		double get_y();
		//Устанавливает координату Y.
		void set_y(const double value);
		//Возвращает true, если данная вершина входит в список смежности (adjacency содержит vertex).
		bool is_adjacency(vertex& vertex);
		//Добавляет вершину в список смежности с данной. Возвращает true, если добавление успешно.
		bool add_adjacency(vertex& vertex);
		//Удалаяет вершину из списка смежности с данной. Возвращает true, если удаление успешно.
		bool remove_adjacency(vertex& vertex);
		//Получает вершину из списка смежности.
		vertex& get_adjacency_vertex(const int index);
		//Получает индекс текущей вершины в списке смежности или -1, если данная вершина там не содержится.
		int get_adjacency_index(vertex& vertex);
		//Возвращает количество смежных вершин.
		int size();
		//Возвращает true, если вершины являются эквивалентными (равны их id).
		friend bool operator== (const vertex& first, const vertex& second);
		//Возвращает true, если вершины не являются эквивалентными (равны их id).
		friend bool operator!= (const vertex& first, const vertex& second);
	};

	//Представляет граф.
	class graph
	{
	private:
		//Вершины графа.
		std::vector<vertex> vertexes;

		//Возвращает итератор на найденную вершину или vertexes.end(), если такой не найден.
		std::vector<vertex>::iterator find_vertex(vertex& vertex);
		//Устанавливает вершину графа.
		vertex& set_vertex(const int index, vertex& vertex);
	public:
		//Инициализирует класс graph.
		graph();
		//Инициализирует класс graph.
		graph(std::vector<vertex>& vertexes);
		//Добавляет вершину в граф. Возвращает true, если добавление успешно.
		bool add_vertex(vertex& vertex);
		//Удаляет вершину из графа. Возвращает true, если добавление успешно.
		bool remove_vertex(vertex& vertex);
		//Возвращает true, если указанная вершина содержится в графе.
		bool contains(vertex& vertex);
		//Получает вершину графа.
		vertex& get_vertex(const int index);
		//Получает индекс вершины в графе или -1, если данная вершина там не содержится.
		int get_vertex_index(vertex& vertex);
		//Возвращает количество вершин.
		int size();
		//Возвращает максимальное множество вершин внутренней стабильности.
		std::vector<vertex*> get_max_int_stab_vertex();
		//Возвращает минимальное множество вершин внешней стабильности.
		std::vector<vertex*> get_min_ext_stab_vertex();
		//Возвращает ядра графа.
		std::vector<vertex*> get_cores();
	};
}