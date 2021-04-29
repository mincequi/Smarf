#ifndef THEMEMODEL_H
#define THEMEMODEL_H

#include <QColor>
#include <QObject>

class ThemeModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QColor primaryColor MEMBER m_primaryColor NOTIFY primaryColorChanged)
    Q_PROPERTY(QColor secondaryColor MEMBER m_secondaryColor NOTIFY secondaryColorChanged)

public:
    explicit ThemeModel(QObject *parent = nullptr);

signals:
    void primaryColorChanged();
    void secondaryColorChanged();

private:
    QColor m_primaryColor;
    QColor m_secondaryColor;
};

#endif // THEMEMODEL_H
