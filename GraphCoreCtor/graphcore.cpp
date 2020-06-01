#include "graphcore.h"

namespace GraphCore{

VertexStyle::VertexStyle(double radius, Qt::GlobalColor backgroundColor, double circuitPercent, Qt::GlobalColor circuitColor, Qt::GlobalColor textColor){
    this->radius = radius;
    this->backgroundColor = backgroundColor;
    this->circuitPercent = circuitPercent;
    this->circuitColor = circuitColor;
    this->textColor = textColor;
}

VertexStyle::~VertexStyle(){

}

double VertexStyle::getCircuitPercent() const{
    return this->circuitPercent;
}

Qt::GlobalColor VertexStyle::getCircuitColor() const{
    return this->circuitColor;
}

Qt::GlobalColor VertexStyle::getTextColor() const
{
    return this->textColor;
}

Qt::GlobalColor VertexStyle::getBackgroundColor() const
{
    return this->backgroundColor;
}

double VertexStyle::getRadius() const
{
    return this->radius;
}

Vertex::Vertex(Graph& owner, int x, int y, QObject *parent)
    : QObject(parent), QGraphicsItem(), graph(owner){
    this->x = x;
    this->y = y;
}

Vertex::~Vertex(){

}

const QString Vertex::getName(){
    int id = this->graph.getVertexID(this);
    return QString::number(id);
}

int Vertex::getX() const
{
    return this->x;
}

void Vertex::setX(int value)
{
    this->x = value;
}

int Vertex::getY() const
{
    return this->y;
}

void Vertex::setY(int value)
{
    this->y = value;
}

const VertexStyle& Vertex::getStyle() const {
    return this->graph.getVertexStyle(this);
}

QRectF Vertex::generateDescribedSquare(double centerX, double centerY, double radius){
    double diameter = 2 * radius;
    double x = centerX - radius;
    double y = centerY - radius;
    return QRectF(x, y, diameter, diameter);
}

QRectF Vertex::boundingRect() const {
    return generateDescribedSquare(this->x, this->y, this->getStyle().getRadius());
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    const double EPSILON = 0.000001;
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const VertexStyle& style = this->getStyle();
    painter->setRenderHint(QPainter::Antialiasing, true);

    double inside_radius;
    if(style.getCircuitPercent() >= EPSILON){
        //Рисуем точку с контуром
        painter->setBrush(style.getCircuitColor());
        painter->drawEllipse(this->boundingRect());
        inside_radius = style.getRadius() * (100. - style.getCircuitPercent()) / 100.;
    } else inside_radius = style.getRadius();

    auto inside_size = generateDescribedSquare(this->x, this->y, inside_radius);
    painter->setBrush(style.getBackgroundColor());
    painter->drawEllipse(inside_size);
    painter->setPen(style.getTextColor());
    painter->setFont(QFont("Arial", inside_radius));
    painter->drawText(inside_size, Qt::AlignCenter, this->getName());
}

Graph::Graph(QWidget *parent)
    :QGraphicsView(parent)
{
    scene = new QGraphicsScene();

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    int width = this->width();
    int height = this->height();
    scene->setSceneRect(0, 0, width, height);

    //DEBUG
    Vertex* vertex = new Vertex(*this, 0, 0);
    scene->addItem(vertex);
    //Vertex* vertex2 = new Vertex(*this, 30, 30);
    //scene->addItem(vertex2);

    this->setScene(scene);
}

Graph::~Graph(){
    delete scene;
}

int Graph::getVertexID(const Vertex* vertex)
{
    return 1;
}

const VertexStyle& Graph::getVertexStyle(const Vertex *vertex)
{
    return this->DEFAULT_STYLE;
}

Edge::Edge(Graph &owner, Vertex &vertex, QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

Edge::Edge(Graph &owner, Vertex &first, Vertex &second, QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

EdgeDirection Edge::getDirection() const
{
    return this->direction;
}

void Edge::setDirection(const EdgeDirection &value)
{
    this->direction = value;
}

QRectF Edge::boundingRect() const
{

}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

}
