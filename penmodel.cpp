#include "penmodel.h"
#include <QDebug>
PenModel::PenModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    for (char c: std::string("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")) {
        glyphList << c;
    }
    for (char glyph: glyphList) {
        if (!glyphData.contains(glyph)) {
            glyphData[glyph] = qMakePair(QPen(), QBrush(Qt::transparent));
        }
    }
}

QPair<QPen, QBrush> PenModel::glyphConfig(char glyph) const {
    return glyphData.value(glyph);
}

int PenModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : glyphList.size();
}

int PenModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : NumColumns;
}

QVariant PenModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && index.row() < glyphList.size()) {
        switch (index.column()) {
        case Glyph:
            switch (role) {
            case Qt::DisplayRole:
                return QChar::fromLatin1(glyphList[index.row()]);
            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
            }
            break;
        case PenColor:
            switch (role) {
            case Qt::DecorationRole:
                return glyphData[glyphList[index.row()]].first.color();
            case Qt::DisplayRole:
            case Qt::EditRole:
                return glyphData[glyphList[index.row()]].first.color().name(QColor::HexArgb);
            }
            break;
        case BrushColor:
            switch (role) {
            case Qt::DecorationRole:
                return glyphData[glyphList[index.row()]].second.color();
            case Qt::DisplayRole:
            case Qt::EditRole:
                return glyphData[glyphList[index.row()]].second.color().name(QColor::HexArgb);
            }
            break;
        }
    }

    return QVariant();
}

QVariant PenModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case Glyph:
            return tr("Glyph");
        case PenColor:
            return tr("Pen");
        case BrushColor:
            return tr("Brush");
        }
    }
    return QVariant();
}

bool PenModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && index.row() < glyphList.size()) {
        switch (index.column()) {
        case PenColor:
            switch (role) {
            case Qt::EditRole:
                QColor c(value.toString());
                if (c.isValid()) {
                    glyphData[glyphList[index.row()]].first.setColor(c);
                    emit dataChanged(index, index);
                    return true;
                }
            }
            break;
        case BrushColor:
            switch (role) {
            case Qt::EditRole:
                QColor c(value.toString());
                if (c.isValid()) {
                    glyphData[glyphList[index.row()]].second.setColor(c);;
                    emit dataChanged(index, index);
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

Qt::ItemFlags PenModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags f = QAbstractTableModel::flags(index);
    if (index.column() != Glyph)
        f |= Qt::ItemIsEditable;
    return f;
}

