#include <QtMath>
#include "vertex.h"

namespace GraphCore{

    VertexCircuit::VertexCircuit(double percent, Qt::GlobalColor color){
        this->percent = percent;
        this->color = color;
    }

    VertexCircuit::~VertexCircuit(){

    }

    double VertexCircuit::getPercent(){
        return this->percent;
    }

    void VertexCircuit::setPercent(double value){
        this->percent = value;
    }

    Qt::GlobalColor VertexCircuit::getColor(){
        return this->color;
    }

    void VertexCircuit::setColor(Qt::GlobalColor& value){
        this->color = value;
    }

    Vertex::Vertex(int x, int y, int radius, VertexCircuit circuit, Qt::GlobalColor textColor, QObject *parent)
        : QObject(parent), QGraphicsItem(){
        this->x = x;
        this->y = y;
        this->radius = radius;
        this->circuit = circuit;
        this->textColor = textColor;
    }

    Vertex::~Vertex(){

    }

    QString Vertex::getName(){ //FIXME
        return "1";
    }

    QRectF Vertex::generateDescribedSquare(double centerX, double centerY, double radius){
        double diameter = 2 * radius;
        double x = centerX - radius;
        double y = centerY - radius;
        return QRectF(x, y, diameter, diameter);
    }

    QRectF Vertex::boundingRect() const {
        return generateDescribedSquare(this->x, this->y, this->radius);
    }

    void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        const double EPSILON = 0.000001;
        Q_UNUSED(option);
        Q_UNUSED(widget);

        double inside_radius;
        if(this->circuit.getPercent() >= EPSILON){
            //Рисуем точку с контуром
            painter->setBrush(this->circuit.getColor());
            painter->drawEllipse(this->boundingRect());
            inside_radius = this->radius * (100. - this->circuit.getPercent()) / 100.;
        } else inside_radius = this->radius;

        auto inside_size = generateDescribedSquare(this->x, this->y, inside_radius);
        painter->setBrush(Qt::white);
        painter->drawEllipse(inside_size);
        painter->setPen(this->textColor);
        painter->setFont(QFont("Arial", inside_radius));
        painter->drawText(inside_size, Qt::AlignCenter, this->getName());
    }
}
