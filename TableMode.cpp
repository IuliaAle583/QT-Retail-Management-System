#include <QFont>
#include <QBrush>
#include "TableMode.h"
#include <QPixmap>
#include <QPainter>

TableMode::TableMode(Repository& repository, QObject* parent) : repository{ repository }, QAbstractTableModel{ parent } {
    this->coatsCount = this->repository.getArray().size();
}

TableMode::~TableMode() {

}

int TableMode::rowCount(const QModelIndex& parent) const {
    int coatsNumber = this->repository.GetSize();
    return coatsNumber;
}

int TableMode::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant TableMode::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        vector<TrenchCoat> coats = this->repository.getArray();
        TrenchCoat c = coats[row];
        switch (column)
        {
        case 0:
            return QString::fromStdString(c.GetSize());

        case 1:
            return QString::fromStdString(c.GetColor());

        case 2:
            return QString::fromStdString(to_string(c.GetPrice()));

        case 3:
            return QString::fromStdString(to_string(c.GetQuantity()));

        case 4:
            return QString::fromStdString(c.GetPhotograph());

        default:
            break;

        }
    }

    if (role == Qt::FontRole) {

        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};

};

QVariant TableMode::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section) {
            case 0:
                return QString{ "Size" };

            case 1:
                return QString{ "Color" };

            case 2:
                return QString{ "Price" };

            case 3:
                return QString{ "Quantity" };

            case 4:
                return QString{ "Photograph" };

            default:
                break;
            }
        }
    }

    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}


Qt::ItemFlags TableMode::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void TableMode::updateInternalData() {
    endResetModel();

}


