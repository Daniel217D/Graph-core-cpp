#include "data.h"
#include <QFile>

namespace GraphCore
{

    GraphData::~GraphData(){
        delete[] vertexiesData;
        delete[] edgesData;
    }

    bool saveGraphData(GraphData& data, QString filename)
    {
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        if (file.isOpen()){
            file.write(data.magic, sizeof(data.magic));

            file.write((char*)&data.isOriented, sizeof(data.isOriented));

            file.write((char*)&data.vertexiesCount, sizeof(data.vertexiesCount));

            for(auto i = 0u; i < data.vertexiesCount; ++i){
                file.write((char*)&data.vertexiesData[i].id, sizeof(data.vertexiesData[i].id));
                file.write((char*)&data.vertexiesData[i].x, sizeof(data.vertexiesData[i].x));
                file.write((char*)&data.vertexiesData[i].y, sizeof(data.vertexiesData[i].y));
            }

            file.write((char*)&data.edgesCount, sizeof(data.edgesCount));

            for(auto i = 0u; i < data.edgesCount; ++i){
                file.write((char*)&data.edgesData[i].firstID, sizeof(data.edgesData[i].firstID));
                file.write((char*)&data.edgesData[i].secondID, sizeof(data.edgesData[i].secondID));
                file.write((char*)&data.edgesData[i].direction, sizeof(data.edgesData[i].direction));
            }

            file.close();
            return true;
        }
        return false;
    }

    GraphData* restoreGraphData(QString filename)
    {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        if (file.isOpen()){
            GraphData* data = new GraphData();

            char magic[sizeof(data->magic)];
            file.read(magic, sizeof(magic));
            for(auto i = 0u; i < sizeof(magic); ++i){
                if (magic[i] != data->magic[i]){
                    delete data;
                    return nullptr;
                }
            }

            file.read((char*)&data->isOriented, sizeof(data->isOriented));

            file.read((char*)&data->vertexiesCount, sizeof(data->vertexiesCount));

            data->vertexiesData = new VertexData[data->vertexiesCount];
            for(auto i = 0u; i < data->vertexiesCount; ++i){
                file.read((char*)&data->vertexiesData[i].id, sizeof(data->vertexiesData[i].id));
                file.read((char*)&data->vertexiesData[i].x, sizeof(data->vertexiesData[i].x));
                file.read((char*)&data->vertexiesData[i].y, sizeof(data->vertexiesData[i].y));
            }

            file.read((char*)&data->edgesCount, sizeof(data->edgesCount));

            data->edgesData = new EdgeData[data->edgesCount];
            for(auto i = 0u; i < data->edgesCount; ++i){
                file.read((char*)&data->edgesData[i].firstID, sizeof(data->edgesData[i].firstID));
                file.read((char*)&data->edgesData[i].secondID, sizeof(data->edgesData[i].secondID));
                file.read((char*)&data->edgesData[i].direction, sizeof(data->edgesData[i].direction));
            }

            file.close();
            return data;
        }

        return nullptr;
    }

}
