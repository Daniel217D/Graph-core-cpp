#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include "edge.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

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
         * \brief Создает ребро и добавляет его на граф.
         * \param first Вершина 1.
         * \param second Вершина 2.
         * \param style Стиль ребра.
         * \return Ссылку на созданное ребро.
         */
        Edge& createEdge(Vertex* first, Vertex* second, EdgeStyle* style);
        /*!
         * \brief Уничтожает граф.
         */
        ~Graph();

    protected:
      /*!
       * \brief Действие при нажатии кнопки мыши.
       * \param event Информация о событии.
       */
      void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
      /*!
       * \brief Список вершин.
       */
      QList<Vertex*> vertexies;
      /*!
       * \brief Список ребер.
       */
      QList<Edge*> edges;

      /*!
       * \brief Возвращает true, если вершина находится в радиусе других вершин.
       * \param vertex Вершина.
       */
      bool hasAnotherVertex(const Vertex* vertex);
    };

}

#endif // GRAPHCORE_H
