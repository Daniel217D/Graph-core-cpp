#include "vertex.h"

namespace GraphCore
{

    VertexStyle::VertexStyle(qreal radius, QColor backgroundColor, double circuitPercent, QColor circuitColor, QColor textColor)
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

    inline QColor VertexStyle::getCircuitColor() const
    {
        return circuitColor;
    }

    inline QColor VertexStyle::getTextColor() const
    {
        return textColor;
    }

    inline QColor VertexStyle::getBackgroundColor() const
    {
        return backgroundColor;
    }

    qreal VertexStyle::getRadius() const
    {
        return radius;
    }

    Vertex::Vertex(int centerX, int centerY, VertexStyle* style, QString name, QObject *parent)
        : QObject(parent), QGraphicsItem()
    {
        setZValue(1);
        setPos(centerX, centerY);
        oldPosition = nullptr;
        this->style = style;
        this->name = name;
        inArrowMode = false;
    }

    Vertex::~Vertex()
    {
        delete oldPosition;
    }

    VertexStyle* Vertex::getStyle() const
    {
        return style;
    }

    void Vertex::setStyle(VertexStyle *value)
    {
        style = value;
        update();
    }

    QString Vertex::getName() const
    {
        return name;
    }

    void Vertex::setName(const QString& value)
    {
        name = value;
        update();
    }

    void Vertex::changePositionWithSignal(const int x, const int y){
        setPos(x, y);
        positionChangedByMouse(this, x, y);
    }

    bool Vertex::returnPositionIfExist()
    {
        if (oldPosition != nullptr){
            changePositionWithSignal(oldPosition->x(),oldPosition->y());
            return true;
        } else return false;
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

    QPainterPath Vertex::shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
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
        Q_UNUSED(event);
        if (oldPosition){
            auto new_pos = mapToScene(event->pos());
            changePositionWithSignal(new_pos.x(), new_pos.y());
        } else if (inArrowMode){
            auto realCords = mapToScene(event->pos());
            lineChanged(this, realCords.x(), realCords.y());
        }
    }

    void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        Q_UNUSED(event);
        if(event->button() == Qt::LeftButton){
            if(inArrowMode)
                mouseReleaseEvent(event);
            oldPosition = new QPointF(x(), y());
            startPositionChangedByMouse(this);
            return;
        } if(event->button() == Qt::RightButton){
            if (oldPosition)
                mouseReleaseEvent(event);
            inArrowMode = true;
            startDrawingArrow(this);
            return;
        }

        delete oldPosition;
        oldPosition = nullptr;
        inArrowMode = false;
    }

    void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        Q_UNUSED(event);
        if(oldPosition){
            endPositionChangedByMouse(this);
            delete oldPosition;
            oldPosition = nullptr;
        } else if (inArrowMode){
            endDrawingArrow(this);
            inArrowMode = false;
        }
    }

}
