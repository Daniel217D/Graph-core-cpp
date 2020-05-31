#include "vertextable.h"

namespace GraphCore{

VertexTable* VertexTable::p_instance = 0;
VertexTableDestroyer VertexTable::destroyer;

VertexTableDestroyer::~VertexTableDestroyer() {
    delete p_instance;
}

void VertexTableDestroyer::initialize( VertexTable* p ) {
    p_instance = p;
}

VertexTable& VertexTable::getInstance() {
    if(!p_instance)     {
        p_instance = new VertexTable();
        destroyer.initialize( p_instance);
    }
    return *p_instance;
}

}
