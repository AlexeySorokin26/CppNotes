#include <QApplication>
#include <QAbstractListModel>
#include <QListView>
#include <QStringList>

// MODEL: хранит данные, отвечает на роли, шлёт dataChanged при изменении.
class CheckListModel : public QAbstractListModel
{
public:
    CheckListModel(QStringList names) : names(names), checked(names.size(), false) {}

    int rowCount(const QModelIndex & = {}) const override { return names.size(); }

    QVariant data(const QModelIndex &i, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole)
            return names.at(i.row());
        if (role == Qt::CheckStateRole)
            return checked.at(i.row()) ? Qt::Checked : Qt::Unchecked;
        return {};
    }

    bool setData(const QModelIndex &i, const QVariant &v, int role) override
    {
        if (role != Qt::CheckStateRole)
            return false;
        checked[i.row()] = (v == Qt::Checked);
        Q_EMIT dataChanged(i, i); // "ячейка протухла, перерисуй"
        return true;
    }

    Qt::ItemFlags flags(const QModelIndex &i) const override
    {
        return QAbstractListModel::flags(i) | Qt::ItemIsUserCheckable;
    }

private:
    QStringList names;
    QList<bool> checked;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CheckListModel model({"Liver", "Kidney", "Heart", "Tumor"});

    QListView view; // VIEW: рисует сам, мы только даём ему модель
    view.setModel(&model);
    view.show();

    return app.exec();
}