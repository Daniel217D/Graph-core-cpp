#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include "edge.h"

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
        explicit Graph(QWidget *parent = nullptr);
        /*!
         * \brief Создает вершину и добавляет ее на граф.
         * \param x Координата x.
         * \param y Координата y.
         * \param style Стиль вершины.
         * \return Ссылку на созданную вершину.
         */
        Vertex& createVertex(int x, int y, VertexStyle* style);
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
         * \param style Стиль ребра.
         * \return Ссылку на созданное ребро.
         */
        Edge& createEdge(Vertex* first, Vertex* second, EdgeDirection direction, EdgeStyle* style);
        /*!
         * \brief Удаляет ребро на граф.
         * \param edge Ребро.
         */
        void removeEdge(Edge& edge);
        /*!
         * \brief Уничтожает граф.
         */
        ~Graph();

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
       * \brief Возвращает указатели на все ребра, соединенные с вершиной.
       * \param vertex Вершина.
       * \return Список указателей на ребра.
       */
      QList<Edge*> findOwnedEdges(Vertex& vertex);
      /*!
       * \brief Переименовывает все вершины графа.
       */
      void updateVertexNames();
    };

}

#endif // GRAPHCORE_H
