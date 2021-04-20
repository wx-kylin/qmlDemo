#include "outline.h"
#include <QDebug>
#include <QQuickWindow>

namespace tmp {

// BaseOutline
BaseOutline::BaseOutline(): m_active(false)
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
    m_active = true;
    m_outline->show();

    qDebug() << "m_active is true";
    emit activeChanged();
}

void BaseOutline::hide()
{
    if (!m_active) {
        return;
    }
    m_active = false;
    qDebug() << "m_active is false";
    emit activeChanged();
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
    /*
    A QQmlComponent instance can be created from a QML file.一个QQmlComponent实例对应一个qml文件，
    并使用create创建一个实例化的对象，如QQuickWindow。

    Contexts allow data to be exposed to the QML components instantiated by the QML engine.如outline();
    Each QQmlContext contains a set of properties, distinct from its QObject properties,
    that allow data to be explicitly bound to a context by name.
    The context properties are defined and updated by calling QQmlContext::setContextProperty().
    The following example shows a Qt model being bound to a context and then accessed from a QML file.
    当数据被绑定到context的属性上之后，就可以在qml文件中访问了。

    Each QML component is instantiated in a QQmlContext.
    component是在engine的context中实例化的。
    QQmlContext's are essential for passing data to QML components.
    为了向component中传递数据，context是必要的。
    In QML, contexts are arranged hierarchically and this hierarchy is managed by the QQmlEngine.
    context是被分层组织的，并由engine管理。
    */
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
//        w->setProperty("__outline", true);
//        w->lower();
        w->showMaximized();
    }

}

}
