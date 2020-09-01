#ifndef DATA_H
#define DATA_H

#include <QString>
#include "edge.h"

namespace GraphCore
{
    /*!
     * \brief Сериализованные данные вершины.
     */
    struct VertexData
    {
        /*!
         * \brief Идентификатор вершины.
         */
        unsigned int id;
        /*!
         * \brief Центр вершины по OX.
         */
        qreal x;
        /*!
         * \brief Центр вершины по OY.
         */
        qreal y;
    };

    /*!
     * \brief Сериализованные данные ребра.
     */
    struct EdgeData
    {
        /*!
         * \brief Идентификатор первой вершины.
         */
        unsigned int firstID;
        /*!
         * \brief Идентификатор второй вершины.
         */
        unsigned int secondID;
        /*!
         * \brief Направление ребра.
         */
        EdgeDirection direction;
    };

    /*!
     * \brief Сериализованные данные графа.
     */
    struct GraphData
    {
        /*!
         * \brief Магическое значение.
        */
        char magic[3] = {'G', 'R', 'D'};
        /*!
         * \brief Указывает, является ли граф ориентированным.
         */
        bool isOriented = true;
        /*!
         * \brief Количество сериализованных данных о вершинах.
        */
        unsigned int vertexiesCount = 0;
        /*!
         * \brief Массив сериализованных данных о вершинах.
        */
        VertexData* vertexiesData = nullptr;
        /*!
         * \brief Количество сериализованных данных о ребрах.
        */
        unsigned int edgesCount = 0;
        /*!
         * \brief Массив сериализованных данных о ребрах.
        */
        EdgeData* edgesData = nullptr;
        /*!
         * Уничтожает cериализованные данные графа.
         */
        ~GraphData();
    };

    /*!
     * \brief Возращает true, если сохранение сериализованных данных о графе в файл выполнено успешно.
     * \param data Сериализованные данные о графе.
     * \param filename Имя файла.
     */
    bool saveGraphData(GraphData& data, QString filename);

    /*!
     * \brief Создает в памяти сериализованные данные из файла и возвращает указатель на них. Возвращает NULL, если произошла ошибка.
     * \param filename Имя файла.
     */
    GraphData* restoreGraphData(QString filename);

}

#endif // DATA_H
