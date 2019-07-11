#include "geometryplayground.h"
#include "thickline.h"
#include "thicklinemesh.h"
#include "thicklinegeometry.h"

#include "vhapi/2dentities/pointentity.hpp"
#include "vhapi/2dentities/lineentity.hpp"
#include "vhapi/2dentities/markerentity.hpp"
#include "vhapi/2dentities/polylineentity.h"

#include <QDebug>

GeometryPlayground::GeometryPlayground(QObject *parent) : QObject(parent)
{

}

void GeometryPlayground::setTargetThickLine(ThickLine *line)
{
    ThickLineMesh *mesh = line->findChild<ThickLineMesh *>("");
    if (mesh) {
        qDebug() << "found mesh" << mesh;
        m_geometry = mesh->geometry();
    }
}

void GeometryPlayground::onDrawSmthClicked()
{
    qDebug() << "Drawing smth";

    m_geometry->clear();

    m_geometry->addPoint(-0.5, 0, 0, 0xcc, 0xcc, 0xcc, 2);
    m_geometry->addPoint(0.5, 0.0, 0, 0xcc, 0xcc, 0xcc, 2);
    m_geometry->breakStrip();

    m_geometry->addPoint(0, -0.5, 0, 0xcc, 0xcc, 0xcc, 2);
    m_geometry->addPoint(0, 0.5, 0, 0xcc, 0xcc, 0xcc, 2);
    m_geometry->breakStrip();

    m_geometry->flush();
}

void GeometryPlayground::onDrawPlusClicked()
{
    QVariantHash meta;
    meta["source"] = "playground";
    QVariant entity;
    entity.setValue<MarkerEntity>(MarkerEntity(meta));
    emit rxport->substreamItemReceived(entity);

    LineEntity l = LineEntity(PointEntity(0, 0, 0, 255, 0, 0), PointEntity(300, 0.0, 0.0), 3);
    entity.setValue<LineEntity>(l);
    emit rxport->substreamItemReceived(entity);
//    PolylineEntity pl;
//    pl.m_points.append( { PointEntity(0, 0, 0, 255, 0, 0), 3 } );
//    pl.m_points.append( { PointEntity(0.1, 0, 0, 255, 0, 0), 3 } );
//    pl.m_points.append( { PointEntity(0.101, 0, 0, 255, 0, 0), 10 } );
//    pl.m_points.append( { PointEntity(0.11, 0, 0, 255, 0, 0), 1 } );
//    emit rxport->substreamItemReceived(pl);
    l = LineEntity(PointEntity(0, 0, 0, 0, 255, 0), PointEntity(0.0, 300, 0), 3);
    entity.setValue<LineEntity>(l);
    emit rxport->substreamItemReceived(entity);

    l = LineEntity(PointEntity(0, 0, 0, 0, 0, 255), PointEntity(0.0, 0.0, 300), 3);
    entity.setValue<LineEntity>(l);
    emit rxport->substreamItemReceived(entity);
}
