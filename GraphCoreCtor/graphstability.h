#ifndef GRAPHEXTERNALSTABILITY_H
#define GRAPHEXTERNALSTABILITY_H

#include <QThread>
#include "graph.h"

namespace GraphCore
{
    class CoreFinderProgress
    {

    };

    class CoreFinderThread : public QThread
    {
        Q_OBJECT

    public:
        CoreFinderThread();
        ~CoreFinderThread();

    signals:
        void progressChanged(CoreFinderProgress& progress);

    private:
        CoreFinderProgress* progress;

        void run() override;
    };

    /*!
     * \brief Множество устойчивости.
     */
    class GraphStability
    {

    public:
        /*!
         * \brief Инициализирует множества устойчивости графа.
         * \param graph Граф.
         */
        GraphStability(Graph& graph);
        /*!
         * \brief Уничтожает множества устойчивости графа.
         */
        ~GraphStability();
        /*!
         * \brief Вовзвращает квадратную матрицу смежности.
         * \return Квадратная матрица смежности.
         */
        bool **getAdjacencyMatrix() const;
        /*!
         * \brief Вовзвращает длину квадратной матрицы.
         * \return Длина квадратной матрицы.
         */
        int getLength() const;

   private:
        /*!
         * \brief Квадратную матрица смежности.
         */
        bool** adjacencyMatrix;
        /*!
         * \brief Длина квадратной матрицы.
         */
        int length;
    };

    /*!
     * \brief Множества внешней устойчивости графа.
     */
    class GraphExternalStability : public GraphStability
    {
        /*!
         * \brief Инициализирует множества внешней устойчивости графа.
         * \param graph Граф.
         */
        GraphExternalStability(Graph& graph);
        /*!
         * \brief Уничтожает множества внешней устойчивости графа.
         */
        ~GraphExternalStability();
    };

    /*!
     * \brief Множества внутренней устойчивости графа.
     */
    class GraphInternalStability : public GraphStability
    {
        /*!
         * \brief Инициализирует множества внутренней устойчивости графа.
         * \param graph Граф.
         */
        GraphInternalStability(Graph& graph);
        /*!
         * \brief Уничтожает множества внутренней устойчивости графа.
         */
        ~GraphInternalStability();
    };
}

#endif // GRAPHEXTERNALSTABILITY_H
