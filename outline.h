#ifndef OUTLINE_H
#define OUTLINE_H
#include <QObject>
#include <QQmlContext>
#include <QQmlComponent>
#include <QScopedPointer>
#include <QQmlEngine>
#include <QStandardPaths>

class QQmlContext;
class QQmlComponent;

namespace tmp {

class Outline;

class BaseOutline : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)
public:
    BaseOutline();
    ~BaseOutline();
    static BaseOutline *self();
    void show();
    void hide();
    bool isActive() const;

Q_SIGNALS:
    void activeChanged();

private:
    QScopedPointer<Outline> m_outline;
    static BaseOutline *s_self;
    bool m_active;
};

class Outline : public BaseOutline
{
    Q_OBJECT
public:
    Outline(BaseOutline *baseOutline);
    ~Outline();
    void show();
    void hide();

//protected:
//    BaseOutline *outline();
//    const BaseOutline *outline() const;

private:
    BaseOutline *m_baseOutline;
    QScopedPointer<QQmlContext> m_qmlContext;
    QScopedPointer<QQmlComponent> m_qmlComponent;
    QScopedPointer<QObject> m_mainItem;
};

inline
BaseOutline *outline()
{
    return BaseOutline::self();
}

inline
bool BaseOutline::isActive() const
{
    return m_active;
}

//inline
//BaseOutline *Outline::outline()
//{
//    return m_baseOutline;
//}
//inline
//const BaseOutline *Outline::outline() const
//{
//    return m_baseOutline;
//}

}
#endif // OUTLINE_H
