#include "outline.h"
#include <QDebug>
#include <QQuickWindow>

namespace tmp {

// BaseOutline
BaseOutline::BaseOutline()
{
}

BaseOutline::~BaseOutline()
{
}

BaseOutline *BaseOutline::s_self = nullptr;

BaseOutline *BaseOutline::self()
{
    if (s_self) {
        return s_self;
    }
    s_self = new BaseOutline();
    return s_self;
}

void BaseOutline::show()
{
    if (m_outline.isNull()) {
        m_outline.reset(new Outline(this));
    }
    if (m_outline.isNull()) {
        qDebug() << "Fail to init Outline";
        return;
    }
    m_outline->show();
//    m_active = true;
//    emit activeChanged();
}

void BaseOutline::hide()
{
//    if (!m_active) {
//        return;
//    }
//    m_active = false;
//    emit activeChanged();
    if (m_outline.isNull()) {
        return;
    }
    m_outline->hide();
}

// Outline
Outline::Outline(BaseOutline *baseOutline)
    : m_baseOutline(baseOutline)
    , m_qmlContext()
    , m_qmlComponent()
    , m_mainItem()
{
}

Outline::~Outline()
{
}

void Outline::hide()
{
    if (QQuickWindow *w = qobject_cast<QQuickWindow*>(m_mainItem.data())) {
        w->hide();
        w->destroy();
    }
}

void Outline::show()
{
    QQmlEngine engine;
    if (m_qmlContext.isNull()) {
        m_qmlContext.reset(new QQmlContext(&engine));
        m_qmlContext->setContextProperty(QStringLiteral("outline"), outline());
    }
    if (m_qmlComponent.isNull()) {
        m_qmlComponent.reset(new QQmlComponent(&engine));
        const QString fileName = QStandardPaths::locate(QStandardPaths::GenericConfigLocation,
                                                 "/outline.qml");
        if (fileName.isEmpty()) {
            qDebug() << "Could not locate outline.qml, filename is " << fileName;
            return;
        }
        m_qmlComponent->loadUrl(QUrl::fromLocalFile(fileName));
        if (m_qmlComponent->isError()) {
            qDebug() << "Component failed to load: " << m_qmlComponent->errors();
        } else {
            m_mainItem.reset(m_qmlComponent->create(m_qmlContext.data()));
        }

    }
    if (auto w = qobject_cast<QQuickWindow *>(m_mainItem.data())) {
        qDebug() << "in";
        w->setProperty("__outline", true);
        w->show();
    }
}

}
