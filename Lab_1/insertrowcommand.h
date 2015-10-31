#ifndef INSERTROWCOMMAND_H
#define INSERTROWCOMMAND_H

#include <statstablemodel.h>
#include <QUndoCommand>

class InsertRowCommand : public QUndoCommand
{
public:
    explicit InsertRowCommand(StatsTableModel &tableModel, QString text, int value, QUndoCommand *parent = 0);

    void undo();
    void redo();

private:
    StatsTableModel &m_tableModel;
    QString m_text;
    int m_value;
};

#endif // INSERTROWCOMMAND_H
