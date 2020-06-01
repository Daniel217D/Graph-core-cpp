#include "vertex.h"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

namespace GraphCore
{

    VertexStyle::VertexStyle(qreal radius, Qt::GlobalColor backgroundColor, double circuitPercent, Qt::GlobalColor circuitColor, Qt::GlobalColor textColor)
    {
        this->radius = radius;
        this->backgroundColor = backgroundColor;
        this->circuitPercent = circuitPercent;
        this->circuitColor = circuitColor;
        this->textColor = textColor;
    }

    VertexStyle::~VertexStyle()
    {

    }

    inline qreal VertexStyle::getCircuitPercent() const
    {
        return circuitPercent;
    }

    inline Qt::GlobalColor VertexStyle::getCircuitColor() const
    {
        return circuitColor;
    }

    inline Qt::GlobalColor VertexStyle::getTextColor() const
    {
        return textColor;
    }

    inline Qt::GlobalColor VertexStyle::getBackgroundColor() const
    {
        return backgroundColor;
    }

    inline qreal VertexStyle::getRadius() const
    {
        return radius;
    }

    Vertex::Vertex(int centerX, int centerY, VertexStyle* style, QObject *parent)
        : QObject(parent), QGraphicsItem() //FIXME
    {
        setPos(centerX, centerY);
        this->style = new VertexStyle(20., Qt::white, 10., Qt::blue, Qt::black);
    }

    Vertex::~Vertex()
    {

    }

    VertexStyle* Vertex::getStyle() const
    {
        return style;
    }

    void Vertex::setStyle(VertexStyle *value)
    {
        style = value;
    }

    QString Vertex::getName() const //FIXME
    {
        return QString::number(1);
    }

    QRectF Vertex::boundingRect() const
    {
        auto style_ptr = getStyle();
        if (style_ptr != nullptr){
            VertexStyle style = *style_ptr;
            qreal diameter = 2 * style.getRadius();
            return QRectF(-style.getRadius(), -style.getRadius(), diameter, diameter);
        }
        return QRectF(0, 0, 0, 0);
    }

    void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        VertexStyle* style_ptr = getStyle();
        if (style_ptr != nullptr){
            VertexStyle style = *style_ptr;
            painter->setRenderHint(QPainter::Antialiasing, true);

            qreal inside_radius;
            if(style.getCircuitPercent() > 0){
                //Рисуем точку с контуром
                painter->setBrush(style.getCircuitColor());
                painter->drawEllipse(boundingRect());
                inside_radius = style.getRadius() * (100. - style.getCircuitPercent()) / 100.;
            } else inside_radius = style.getRadius();

            auto inside_diameter = 2 * inside_radius;
            auto inside_size = QRectF(-inside_radius, -inside_radius, inside_diameter, inside_diameter);
            painter->setBrush(style.getBackgroundColor());
            painter->drawEllipse(inside_size);
            painter->setPen(style.getTextColor());
            painter->setFont(QFont("Arial", inside_radius));
            painter->drawText(inside_size, Qt::AlignCenter, this->getName());
        }
    }

    void Vertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        this->setPos(mapToScene(event->pos()));
    }

    void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
    }

    void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
        Q_UNUSED(event);
    }

}
