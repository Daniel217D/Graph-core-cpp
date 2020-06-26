#ifndef GRAPHEXTERNALSTABILITY_H
#define GRAPHEXTERNALSTABILITY_H

#include <QThread>
#include <set>
#include "graph.h"

namespace GraphCore
{

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
         * \brief Инициализирует множества устойчивости графа.
         * \param graphData Сериализованные данные о графе.
         */
        GraphStability(GraphData& graphData);
        /*!
         * \brief Уничтожает множества устойчивости графа.
         */
        virtual ~GraphStability();
        /*!
         * \brief Создает квадратную матрицу смежности в динамической памяти.
         * \param matrix Квадратная матрица смежности.
         * \param length Длина квадратной матрицы.
         */
        void createAdjacencyMatrix(bool**& matrix, unsigned int& length);
        /*!
         * \brief Возвращает сериализованные данные о графе.
         */
        GraphData* getGraphData() const;
        /*!
         * \brief Запускает синхронное вычисление множества и возвращает результат.
         */
        virtual QVector<QVector<unsigned int>>* calculate() = 0;
        /*!
         * \brief Преобразует объект SetOfSet к типу VectorOfVector.
         * \param obj Объект.
         */
        QVector<QVector<unsigned int>>* toVectorOfVector(std::set<std::set<unsigned int>>& obj);

    protected:
        /*!
         * \brief Возвращает true, если коллекция first содержится в second.
         * \param first Коллекция 1.
         * \param second Коллекция 2.
         */
        template<class Collection> bool contains(const Collection& first, const Collection& second);
        /*!
         * \brief Сортирует вектор по возрастанию размера вложенных коллекций. Удаляет коллекции, которые являются составными.
         * \param arr Вектор коллекций.
         */
        template<class Collection> void sortAndDeleteSame(QVector<Collection>& arr);

    private:
        /*!
         * \brief Информация о состоянии графа.
         */
        GraphData* graphData;

    };

    /*!
     * \brief Множества внешней устойчивости графа.
     */
    class GraphExternalStability : public GraphStability
    {

    public:
        /*!
         * \brief Инициализирует множества внешней устойчивости графа.
         * \param graph Граф.
         */
        GraphExternalStability(Graph& graph);
        /*!
         * \brief Инициализирует множества внешней устойчивости графа.
         * \param graph Граф.
         */
        GraphExternalStability(GraphData& graph);
        /*!
         * \brief Уничтожает множества внешней устойчивости графа.
         */
        ~GraphExternalStability();
        /*!
         * \brief Создает в памяти хранилище конъюнкторов и возвращает указатель на него.
         * \param matrix Матрица смежности.
         * \param length Длина матрицы смежности.
         */
        std::set<QVector<unsigned int>>* generateConjunctions(bool**const matrix, const unsigned int length);
        /*!
         * \brief Создает в памяти хранилище конъюнкторов и возвращает указатель на него.
         */
        std::set<QVector<unsigned int>>* generateConjunctions();
        /*!
         * \brief Создает в памяти СДНФ и возвращает указатель на нее.
         * \param conjunctions Хранилище конъюнкторов
         */
        QVector<QVector<unsigned int>>* generateSdnf(std::set<QVector<unsigned int>>& conjunctions);
        /*!
         * \brief Создает в памяти перестановки СДНФ и возвращает указатель на них.
         * \param sdnf СДНФ.
         */
        std::set<std::set<unsigned int>>* generateSdnfPermutations(QVector<QVector<unsigned int>>& sdnf);
        /*!
         * \brief Создает в памяти МСДНФ и возвращает указатель на нее.
         * \param sdnfPermutations Перестановки СДНФ.
         */
        QVector<QVector<unsigned int>>* generateMsdnf(std::set<std::set<unsigned int>>& sdnfPermutations);
        /*!
         * \brief Запускает синхронное вычисление множества и возвращает результат.
         */
        virtual QVector<QVector<unsigned int>>* calculate();

    };

    /*!
     * \brief Множества внутренней устойчивости графа.
     */
    class GraphInternalStability : public GraphStability
    {

    public:
        /*!
         * \brief Инициализирует множества внутренней устойчивости графа.
         * \param graph Граф.
         */
        GraphInternalStability(Graph& graph);
        /*!
         * \brief Инициализирует множетсво внутренней устойчивости графа.
         */
        GraphInternalStability(GraphData& graph);
        /*!
         * \brief Уничтожает множества внутренней устойчивости графа.
         */
        ~GraphInternalStability();
        /*!
         * \brief Создает в памяти хранилище конъюнкторов и возвращает указатель на него.
         * \param matrix Матрица смежности.
         * \param length Длина матрицы смежности.
         */
        QVector<QPair<unsigned int, unsigned int>>* generateConjunctions(bool**const matrix, const unsigned int length);
        /*!
         * \brief Создает в памяти хранилище конъюнкторов и возвращает указатель на него.
         */
        QVector<QPair<unsigned int, unsigned int>>* generateConjunctions();
        /*!
         * \brief Создает в памяти СДНФ и возвращает указатель на нее.
         * \param conjunctions Хранилище конъюнкторов
         */
        std::set<std::set<unsigned int>>* generateSdnf(QVector<QPair<unsigned int, unsigned int>>& conjunctions);
        /*!
         * \brief Создает в памяти МСДНФ и возвращает указатель на нее.
         * \param sdnf СДНФ.
         */
        QVector<std::set<unsigned int>>* generateMsdnf(std::set<std::set<unsigned int>>& sdnf);
        /*!
         * \brief Создает в памяти булеан МСДНФ и возвращает указатель на него.
         * \param msdnf МСДНФ.
         */
        QVector<QVector<unsigned int>>* generateBooleanMsdnf(QVector<std::set<unsigned int>>& msdnf);
        /*!
         * \brief Запускает синхронное вычисление множества и возвращает результат.
         */
        virtual QVector<QVector<unsigned int>>* calculate();

    private:
        /*!
         * \brief Сет идентификаторов вершин графа.
         */
        std::set<unsigned int> vertexies;
        /*!
         * \brief Инвертирует сет вершин (отрицание vertexies).
         * \param conjunction
         * \return
         */
        std::set<unsigned int> invertVertexSet(std::set<unsigned int>& set);
    };

    /*!
     * \brief Прогресс нахождения ядра.
     */
    class CoreFinderProgress
    {
    public:
        /*!
         * \brief Инициализирует прогресс нахождения ядра.
         */
        CoreFinderProgress();
        /*!
         * \brief Уничтожает прогресс нахождения ядра.
         */
        ~CoreFinderProgress();
        /*!
         * \brief Преобразует CoreFinderProgress типу QString.
         */
        QString toString() const;
        /*!
         * \brief Устанавливает значение статуса.
         * \param value Статус.
         */
        void setTextStatus(const QString &value);
        /*!
         * \brief Устанавливает значение процента выполнения.
         * \param value Процент выполнения.
         */
        void setPercentage(const qreal &value);

    private:
        /*!
         * \brief Статус.
         */
        QString textStatus;
        /*!
         * \brief Процент выполнения.
         */
        qreal percentage;
    };

    /*!
     * \brief Поток нахождения ядра.
     */
    class CoreFinderThread : public QThread
    {
        Q_OBJECT

    public:
        /*!
         * \brief Инициализирует поток нахождения ядра.
         */
        CoreFinderThread(Graph& graph);
        /*!
         * \brief Уничтожает поток нахождения ядра.
         */
        ~CoreFinderThread();
        /*!
         * \brief Создает в памяти ядра графа и возвращает указатель на них.
         * \param instab Множества внутренней устойчивости.
         * \param exstab Множества внешней устойчивости.
         */
        QVector<QVector<unsigned int>>* findCores(QVector<QVector<unsigned int>>& instab, QVector<QVector<unsigned int>>& exstab);

    signals:
        /*!
         * \brief Возникает, когда произошло ключевое событие в процессе поиска ядра.
         * \param progress Прогресс нахождения ядра.
         */
        void progressChanged(CoreFinderProgress* progress);
        /*!
         * \brief Возникает, когда найдено множество внешней устойчивости найдено.
         * \param progress Прогресс нахождения ядра.
         */
        void externalFounded(QStringList* result);
        /*!
         * \brief Возникает, когда найдено множество внутренней устойчивости найдено.
         * \param progress Прогресс нахождения ядра.
         */
        void internalFounded(QStringList* result);
        /*!
         * \brief Возникает, когда ядро найдено.
         * \param progress Прогресс нахождения ядра.
         */
        void coreFounded(QStringList* result);

    private:
        /*!
         * \brief Граф.
         */
        Graph* graph;
        /*!
         * \brief Возникает, когда произошло ключевое событие в процессе поиска ядра.
         * \param progress Прогресс нахождения ядра.
         */
        CoreFinderProgress* progress;
        /*!
         * \brief Множество внешней устойчивости.
         */
        GraphExternalStability* gexternal;
        /*!
         * \brief Множество внутренней устойчивости.
         */
        GraphInternalStability* ginternal;
        /*!
         * \brief Множества внешней устойчивости.
         */
        QVector<QVector<unsigned int>>* result_ex;
        /*!
         * \brief Множества внутренней устойчивости.
         */
        QVector<QVector<unsigned int>>* result_in;
        /*!
         * \brief Ядра.
         */
        QVector<QVector<unsigned int>>* result_c;

        /*!
         * \brief Запускает процесс нахождения ядра.
         */
        void run() override;
        /*!
         * \brief Создает запись из вектора вершин и выделяет под нее память.
         * \param vectorOfVertexies Вектор вершин
         */
        QStringList* vectorOfVectorToStringList(QVector<QVector<unsigned int>>& vectorOfVertexies);
        /*!
         * \brief Возвращает true, если коллекция являются одинаковыми.
         * \param first Коллекция 1.
         * \param second Коллекция 2.
         */
        template<class Collection> bool equals(Collection& first, Collection& second);
    };
}

#endif // GRAPHEXTERNALSTABILITY_H
