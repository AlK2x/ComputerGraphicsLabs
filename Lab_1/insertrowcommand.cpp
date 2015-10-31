#include "insertrowcommand.h"


InsertRowCommand::InsertRowCommand(StatsTableModel &tableModel, QString text, int value, QUndoCommand *parent)
    :QUndoCommand(parent), m_text(text), m_value(value), m_tableModel(tableModel)
{
}

void InsertRowCommand::redo()
{
    auto model = m_tableModel.statsModel();
    model.append(m_text, m_value);
    m_tableModel.setStatsModel(model);
}

void InsertRowCommand::undo()
{
    auto model = m_tableModel.statsModel();
    StatsKeyValueModel newModel;
    for (int i = 0; i < model.size() - 1; ++i)
    {
        newModel.append(model.key(i), model.value(i));
    }
    m_tableModel.setStatsModel(newModel);
}

