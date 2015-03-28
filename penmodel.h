#ifndef PENMODEL_H
#define PENMODEL_H

#include <QAbstractTableModel>
#include <QBrush>
#include <QPair>
#include <QPen>
#include <QMap>
#include <QSet>

class PenModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PenModel(QObject *parent = 0);
    enum Columns {
        Glyph,
        PenColor,
        BrushColor,
        NumColumns
    };

    QPair<QPen, QBrush> glyphConfig(char glyph) const;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void setVisibleGlyphs(QSet<char> glyphs);
private:
    QMap<char, QPair<QPen,QBrush> > glyphData;
    QList<char> glyphList;
};

#endif // PENMODEL_H
