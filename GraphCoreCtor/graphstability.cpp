#include <algorithm>
#include <QtMath>
#include "graphstability.h"

namespace GraphCore
{

    CoreFinderThread::CoreFinderThread(Graph& graph)
        :QThread()
    {
        this->graph = &graph;
        this->progress = new CoreFinderProgress();
        this->gexternal = new GraphExternalStability(graph);
        this->ginternal = new GraphInternalStability(graph);
        this->result_ex = nullptr;
        this->result_in = nullptr;
        this->result_c = nullptr;
    }

    CoreFinderThread::~CoreFinderThread()
    {
        delete progress;
        delete gexternal;
        delete ginternal;
        delete result_ex;
        delete result_in;
        delete result_c;
    }

    void CoreFinderThread::run()
    {
        QStringList* temp;

        unsigned int length;
        bool** matrix;

        gexternal->createAdjacencyMatrix(matrix, length);

        if(length > 0){
            auto conjunctions_in = ginternal->generateConjunctions(matrix, length);
            auto conjunctions_ex = gexternal->generateConjunctions(matrix, length);

            for(auto i = 0u; i < length; ++i)
                delete[] matrix[i];
            delete[] matrix;

            auto sdnf_in = ginternal->generateSdnf(*conjunctions_in);
            delete conjunctions_in;
            auto sdnf_ex = gexternal->generateSdnf(*conjunctions_ex);
            delete conjunctions_ex;

            auto sdnfPermutations_ex = gexternal->generateSdnfPermutations(*sdnf_ex);
            delete sdnf_ex;

            auto msdnf_in = ginternal->generateMsdnf(*sdnf_in);
            delete sdnf_in;

            result_ex = gexternal->generateMsdnf(*sdnfPermutations_ex);
            delete sdnfPermutations_ex;
            temp = vectorOfVectorToStringList(*result_ex);
            emit externalFounded(temp);

            result_in = ginternal->generateBooleanMsdnf(*msdnf_in);
            temp = vectorOfVectorToStringList(*result_in);
            delete msdnf_in;
            emit internalFounded(temp);

            result_c = findCores(*result_in, *result_ex);
            temp = vectorOfVectorToStringList(*result_c);
            emit coreFounded(temp);
        } else {
            for(auto i = 0u; i < length; ++i)
                delete[] matrix[i];
            delete[] matrix;

            emit externalFounded(nullptr);
            emit internalFounded(nullptr);
            emit coreFounded(nullptr);
        }
    }

    QStringList* CoreFinderThread::vectorOfVectorToStringList(QVector<QVector<unsigned int>>& vectorOfVertexies)
    {
        auto result = new QStringList;
        for(auto i = 0; i < vectorOfVertexies.size(); ++i){
            QString temp;
            for(auto j = 0; j < vectorOfVertexies[i].size() - 1; ++j){
                temp += QString::number(vectorOfVertexies[i][j] + 1) + ", ";
            }
            if(vectorOfVertexies[i].size() > 0)
                temp += QString::number(vectorOfVertexies[i][vectorOfVertexies[i].size() - 1] + 1);
            result->append(temp);
        }

        return result;
    }

    QVector<QVector<unsigned int>>* CoreFinderThread::findCores(QVector<QVector<unsigned int>>& instab, QVector<QVector<unsigned int>>& exstab){
        auto cores = new QVector<QVector<unsigned int>>;
        QVector<unsigned int> numerousSuitable(exstab.size());

        for(QVector<unsigned int>& vector : instab){
            for(auto i = 0; i < numerousSuitable.size(); ++i){
                if (numerousSuitable[i])
                    continue;
                numerousSuitable[i] = equals(exstab[i], vector);
                if(numerousSuitable[i]){
                    cores->push_back(vector);
                }
            }
        }

        return cores;
    }

    template<class Collection>
    bool CoreFinderThread::equals(Collection& first, Collection& second)
    {
        if (first.size() != second.size())
            return false;

         for (auto it1 = first.begin(); it1 != first.end(); ++it1) {
             bool founded = false;

             for (auto it2 = second.begin(); it2 != second.end(); ++it2)
                 if (*it1 == *it2) {
                     founded = true;
                     break;
                 }

             if (founded == false)
                 return false;
        }
        return true;
    }

    GraphStability::GraphStability(Graph& graph)
    {
        this->graphData = &graph.serialize();
    }

    GraphStability::GraphStability(GraphData& graphData)
    {
        this->graphData = new GraphData();
        *this->graphData = graphData;

        this->graphData->vertexiesData = new VertexData[graphData.vertexiesCount];
        memcpy(this->graphData->vertexiesData,
            graphData.vertexiesData,
            sizeof(*graphData.vertexiesData) * graphData.vertexiesCount);

        this->graphData->edgesData = new EdgeData[graphData.edgesCount];
        memcpy(this->graphData->edgesData,
            graphData.edgesData,
            sizeof(*graphData.edgesData) * graphData.edgesCount);
    }

    GraphStability::~GraphStability()
    {
        delete graphData;
    }

    void GraphStability::createAdjacencyMatrix(bool**& matrix, unsigned int& length)
    {
        length = graphData->vertexiesCount;
        matrix = new bool* [length];
        for (auto i = 0u; i < length; ++i) {
            matrix[i] = new bool[length];
            memset(matrix[i], 0, length * sizeof(bool));
        }

        for (auto i = 0u; i < graphData->edgesCount; ++i) {
            if (!graphData->isOriented || graphData->edgesData[i].direction == EdgeDirection::All) {
                matrix[graphData->edgesData[i].firstID][graphData->edgesData[i].secondID] = true;
                matrix[graphData->edgesData[i].secondID][graphData->edgesData[i].firstID] = true;
            }
            else if (graphData->edgesData[i].direction == EdgeDirection::ToSecond) {
                matrix[graphData->edgesData[i].firstID][graphData->edgesData[i].secondID] = true;
            }
            else if (graphData->edgesData[i].direction == EdgeDirection::ToFirst) {
                matrix[graphData->edgesData[i].secondID][graphData->edgesData[i].firstID] = true;
            }
        }
    }

    GraphData* GraphStability::getGraphData() const
    {
        return graphData;
    }

    GraphExternalStability::GraphExternalStability(Graph &graph)
        :GraphStability(graph)
    {

    }

    GraphExternalStability::GraphExternalStability(GraphData& graph)
        : GraphStability(graph)
    {

    }

    GraphExternalStability::~GraphExternalStability()
    {

    }

    std::set<QVector<unsigned int>>* GraphExternalStability::generateConjunctions(bool**const matrix, const unsigned int length)
    {
        auto conjunctions = new std::set<QVector<unsigned int>>;

        for (size_t i = 0; i < length; ++i) {
            QVector<unsigned int> temp;
            temp.push_back(getGraphData()->vertexiesData[i].id);
            for (size_t j = 0; j < length; ++j)
                if (matrix[i][j])
                    temp.push_back(getGraphData()->vertexiesData[j].id);

            conjunctions->insert(temp);
        }

        return conjunctions;
    }

    std::set<QVector<unsigned int>>* GraphExternalStability::generateConjunctions()
    {
        unsigned int length;
        bool** matrix;
        createAdjacencyMatrix(matrix, length);

        auto conjunctions = generateConjunctions(matrix, length);

        for (auto i = 0u; i < length; ++i)
            delete[] matrix[i];
        delete[] matrix;

        return conjunctions;
    }

    QVector<QVector<unsigned int>>* GraphExternalStability::generateSdnf(std::set<QVector<unsigned int>>& conjunctions)
    {
        auto sdnf = new QVector<QVector<unsigned int>>(conjunctions.begin(), conjunctions.end());

        sortAndDeleteSame(*sdnf);

        return sdnf;
    }

    std::set<std::set<unsigned int>>* GraphExternalStability::generateSdnfPermutations(QVector<QVector<unsigned int>>& sdnf)
    {
        int k = sdnf.size();
        QVector<unsigned int> indexes(k, 0);

        bool hasEnd = false;
        auto result = new std::set<std::set<unsigned int>>();
        do {
            std::set<unsigned int> temp;
            for (int i = k - 1; i >= 0; --i)
            {
                temp.insert(sdnf[i][indexes[i]]);
            }
            result->insert(temp);

            for (int i = k - 1; i >= 0; --i)
            {
                ++indexes[i];
                if (indexes[i] == (unsigned int)sdnf[i].size())
                {
                    indexes[i] = 0;
                    hasEnd = i - 1 < 0;
                }
                else break;
            }
        } while (!hasEnd);

        return result;
    }

    QVector<QVector<unsigned int>>* GraphExternalStability::generateMsdnf(std::set<std::set<unsigned int>>& sdnfPermutations)
    {
        auto result = toVectorOfVector(sdnfPermutations);
        sortAndDeleteSame(*result);
        return result;
    }

    QVector<QVector<unsigned int>>* GraphExternalStability::calculate()
    {
        auto conjunctions = generateConjunctions();

        auto sdnf = generateSdnf(*conjunctions);
        delete conjunctions;

        auto sdnfPermutations = generateSdnfPermutations(*sdnf);
        delete sdnf;

        auto msdnf = generateMsdnf(*sdnfPermutations);
        delete sdnfPermutations;

        return msdnf;
    }

    QVector<QPair<unsigned int, unsigned int>>* GraphInternalStability::generateConjunctions(bool**const matrix, const unsigned int length)
    {
        auto conjunctions = new QVector<QPair<unsigned int, unsigned int>>;

        for (auto i = 0u; i < length - 1; ++i)
            for (auto j = i + 1; j < length; ++j)
                if (matrix[i][j] || matrix[j][i]) {
                    conjunctions->push_back(QPair<unsigned int, unsigned int>(
                        this->getGraphData()->vertexiesData[i].id,
                        this->getGraphData()->vertexiesData[j].id));
                }

        return conjunctions;
    }

    QVector<QPair<unsigned int, unsigned int>>* GraphInternalStability::generateConjunctions()
    {
        unsigned int length;
        bool** matrix;
        createAdjacencyMatrix(matrix, length);

        auto conjunctions = generateConjunctions(matrix, length);

        for (auto i = 0u; i < length; ++i)
            delete[] matrix[i];
        delete[] matrix;

        return conjunctions;
    }

    std::set<std::set<unsigned int>>* GraphInternalStability::generateSdnf(QVector<QPair<unsigned int, unsigned int>>& conjunctions)
    {
        auto sdnf = new std::set<std::set<unsigned int>>;

        for (auto i = 0; i < pow(2, conjunctions.size()); ++i) {
            auto permutation = i;
            std::set<unsigned int> temp;
            for (auto bit = 0u; bit < (unsigned int)conjunctions.size(); ++bit) {
                temp.insert(permutation & 1 ? conjunctions[bit].first : conjunctions[bit].second);
                permutation >>= 1;
            }
            sdnf->insert(temp);
        }

        return sdnf;
    }

    QVector<std::set<unsigned int>>* GraphInternalStability::generateMsdnf(std::set<std::set<unsigned int>>& sdnf)
    {
        auto msdnf = new QVector<std::set<unsigned int>>(sdnf.begin(), sdnf.end());

        sortAndDeleteSame(*msdnf);

        return msdnf;
    }

    QVector<QVector<unsigned int>>* GraphInternalStability::generateBooleanMsdnf(QVector<std::set<unsigned int>>& msdnf)
    {
        for (size_t i = 0; i < (unsigned int)msdnf.size(); ++i) {
            msdnf[i] = invertVertexSet(msdnf[i]);
        }

        std::set<std::set<unsigned int>> result;
        for (size_t current = 0; current < (unsigned int)msdnf.size(); ++current) {
            for (auto permutation = 1; permutation < pow(2, msdnf[current].size()); ++permutation) {
                std::set<unsigned int> temp;
                int number = permutation;
                for (auto it = msdnf[current].begin(); it != msdnf[current].end(); ++it) {
                    if (number & 1)
                        temp.insert(*it);
                    number >>= 1;
                }
                result.insert(temp);
            }
        }

        return toVectorOfVector(result);
    }

    QVector<QVector<unsigned int>>* GraphInternalStability::calculate()
    {
        auto conjunctions = generateConjunctions();

        auto sdnf = generateSdnf(*conjunctions);
        delete conjunctions;

        auto msdnf = generateMsdnf(*sdnf);
        delete sdnf;

        auto booleanMsdnf = generateBooleanMsdnf(*msdnf);
        delete msdnf;

        return booleanMsdnf;
    }

    GraphInternalStability::GraphInternalStability(Graph &graph)
        :GraphStability(graph)
    {
        for (auto i = 0u; i < getGraphData()->vertexiesCount; ++i) {
            vertexies.insert(getGraphData()->vertexiesData[i].id);
        }
    }

    GraphInternalStability::GraphInternalStability(GraphData& graph)
        : GraphStability(graph)
    {
        for (auto i = 0u; i < getGraphData()->vertexiesCount; ++i) {
            vertexies.insert(getGraphData()->vertexiesData[i].id);
        }
    }

    GraphInternalStability::~GraphInternalStability()
    {

    }

    template<class Collection>
    bool GraphStability::contains(const Collection& first, const Collection& second)
    {
        for (auto it1 = first.begin(); it1 != first.end(); ++it1) {
            bool founded = false;

            for (auto it2 = second.begin(); it2 != second.end(); ++it2)
                if (*it1 == *it2) {
                    founded = true;
                    break;
                }

            if (founded == false)
                return false;
        }

        return true;
    }

    template<class Collection>
    void GraphStability::sortAndDeleteSame(QVector<Collection>& arr)
    {
        std::sort(arr.begin(), arr.end(), [](const Collection& first, const Collection& second) {
            return first.size() < second.size();
        });

        QVector<bool> removedElements(arr.size(), false);

        for (size_t i = 0; i < (unsigned int)arr.size() - 1; ++i) {
            if (removedElements[i])
                continue;

            for (size_t j = i + 1; j < (unsigned int)arr.size(); ++j) {
                if (removedElements[j])
                    continue;

                removedElements[j] = contains(arr[i], arr[j]);
            }
        }

        for (int i = removedElements.size() - 1; i >= 0; --i)
            if (removedElements[i])
                 arr.remove(i);
    }

    std::set<unsigned int> GraphInternalStability::invertVertexSet(std::set<unsigned int>& set)
    {
        std::set<unsigned int> result;
        for (auto it = vertexies.begin(); it != vertexies.end(); ++it)
            if (set.find(*it) == set.end())
                result.insert(*it);
        return result;
    }

    QVector<QVector<unsigned int>>* GraphStability::toVectorOfVector(std::set<std::set<unsigned int>>& obj)
    {
        auto result = new QVector<QVector<unsigned int>>(obj.size());

        int index = -1;
        for (auto it_ex = obj.begin(); it_ex != obj.end(); ++it_ex) {
            QVector<unsigned int> temp(it_ex->begin(), it_ex->end());
            (*result)[++index] = temp;
        }

        return result;
    }

}
