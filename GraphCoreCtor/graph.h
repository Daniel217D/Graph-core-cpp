#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include "theme.h"

namespace GraphCore
{
    /*!
     * \brief Граф.
     */
    class Graph : public QGraphicsScene
    {

    public:
        /*!
         * \brief Инициализирует граф.
         * \param parent Объект родителя.
         */
        explicit Graph(Theme& theme, bool isOriented = true, QWidget *parent = nullptr);
        /*!
         * \brief Уничтожает граф.
         */
        ~Graph();
        /*!
         * \brief Создает вершину и добавляет ее на граф.
         * \param x Координата x.
         * \param y Координата y.
         * \return Ссылку на созданную вершину.
         */
        Vertex& createVertex(int x, int y);
        /*!
         * \brief Удаляет вершину и все зависящие от нее ребра на графа.
         * \param vertex Вершина.
         */
        void removeVertex(Vertex& vertex);
        /*!
         * \brief Создает ребро и добавляет его на граф.
         * \param first Вершина 1.
         * \param second Вершина 2.
         * \param direction Направление стрелок ребра.
         * \return Ссылку на созданное ребро.
         */
        Edge& createEdge(Vertex* first, Vertex* second, EdgeDirection direction);
        /*!
         * \brief Удаляет ребро на граф.
         * \param edge Ребро.
         */
        void removeEdge(Edge& edge);
        /*!
         * \brief Удаляет все вершины и ребра графа.
         */
        void removeAll();
        /*!
         * \brief Возвращает тему графа
         * \return Тема графа.
         */
        Theme* getTheme() const;
        /*!
         * \brief Устанавливает тему графа.
         * \param value Тема графа.
         */
        void setTheme(Theme* value);
        /*!
         * \brief Получает вершину по имени.
         * \param name Имя вершины.
         * \return Вершина.
         */
        Vertex* getVertexByName(QString name);
        /*!
         * \brief Выбирает вершины с заданными именами.
         * \param names Имена вершин.
         */
        void selectVertex(QStringList* names = nullptr);
        /*!
         * \brief Убирает выделение с заданных именами вершин.
         * \param names Имена вершин.
         */
        void deselectVertex(QStringList* names = nullptr);
        /*!
         * \brief Возвращает ориентацию графа.
         * \return Ориентация графа.
         */
        bool getOriented() const;
        /*!
         * \brief Устанавливает ориентацию графа.
         * \param value Ориентация графа.
         */
        void setOriented(bool value);
        /*!
         * \brief Выполняет сериализацию текущего состояния графа и возвращает ссылку на них.
         * \return Сериализованные данные графы.
         */
        GraphData& serialize() const;
        /*!
         * \brief Восстанавливает состояние графа из сериализованных данных графа.
         * \param data Сериализованные данные графы
         */
        void deserialize(GraphData& data);

    protected:
        /*!
       * \brief Действие при двойном нажатии кнопки мыши.
       * \param event Информация о событии.
       */
      void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    private:
      /*!
       * \brief Указывает, является ли граф ориентированным.
       */
      bool isOriented;
      /*!
       * \brief Список вершин.
       */
      QList<Vertex*> vertexies;
      /*!
       * \brief Список ребер.
       */
      QList<Edge*> edges;
      /*!
       * \brief Линия (конструктор ребра).
       */
      Line* line;
      /*!
       * \brief Тема.
       */
      Theme* theme;

      /*!
       * \brief Возвращает указатель на первую рядом лежащую веришну, если vertex находится в ее радиусе. Либо NULL, если в радиусе нет ни одной такой вершины.
       * \param vertex Вершина.
       */
      Vertex* getAnotherVertex(const Vertex* vertex);
      /*!
       * \brief Возвращает указатель на первую вершину, для которой координаты x, y вписаны в радиус.
       * \param x Координата x.
       * \param y Координата y.
       */
      Vertex* getVertex(const int x, const int y);
      /*!
       * \brief Возвращает указатель на первое ребро, для которого координаты edge(x), y отличаются не более чем на diameter.
       * \param x Координата x.
       * \param y Координата y.
       * \param diameter Диаметр.
       */
      Edge* getEdge(const int x, const int y, const qreal diameter);
      /*!
       * \brief Возвращает указатели на все ребра, соединенные с вершиной.
       * \param vertex Вершина.
       * \return Список указателей на ребра.
       */
      QList<Edge*> findOwnedEdges(Vertex& vertex);
      /*!
       * \brief Переименовывает все вершины графа.
       */
      void updateVertexNames();
      /*!
       * \brief Возвращает true, если существует ребро соединяющее 2 вершины (не учитывает направление).
       * \param first Первая вершина.
       * \param second Вторая вершина.
       */
      bool edgeExist(Vertex& first, Vertex& second);
    };

}

#endif // GRAPHCORE_H
