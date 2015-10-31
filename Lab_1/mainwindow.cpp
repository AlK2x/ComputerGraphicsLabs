#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statstablemodel.h"
#include "statsdocument.h"
#include "insertrowdialog.h"
#include "aboutdialog.h"
#include <QTableView>
#include <QDebug>
#include <unordered_set>
#include <QMessageBox>
#include <QResizeEvent>
#include <QSortFilterProxyModel>
#include "insertrowcommand.h"
#include "deleterowcommand.h"
#include "editcommand.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_undoStack = new QUndoStack(this);

    m_tableModel = std::make_shared<StatsTableModel>();

    QSortFilterProxyModel * proxySort = new QSortFilterProxyModel();
    proxySort->setSourceModel(m_tableModel.get());

    m_ui->tableData->setAlternatingRowColors(true);
    m_ui->tableData->setSortingEnabled(true);

    m_ui->tableData->setModel(proxySort);
    proxySort->setSortCaseSensitivity(Qt::CaseInsensitive);


    m_ui->newDocument->setShortcut(QKeySequence(QKeySequence::New));
    m_ui->openDocument->setShortcut(QKeySequence(QKeySequence::Open));
    m_ui->saveDocument->setShortcut(QKeySequence(QKeySequence::Save));
    m_ui->saveDocumentAs->setShortcut(QKeySequence(QKeySequence::SaveAs));
    m_ui->actionInsertRow->setShortcut(QKeySequence(QKeySequence(Qt::Key_Insert)));
    m_ui->actionDeleteRow->setShortcut(QKeySequence(QKeySequence::Delete));

    m_undoAction = m_undoStack->createUndoAction(this, tr("&Undo"));
    m_undoAction->setShortcuts(QKeySequence::Undo);

    m_redoAction = m_undoStack->createRedoAction(this, tr("&Redo"));
    m_redoAction->setShortcuts(QKeySequence::Redo);

    m_ui->menu->addAction(m_undoAction);
    m_ui->menu->addAction(m_redoAction);

    connect(m_tableModel.get(), SIGNAL(editRow(int, QString, int)), this, SLOT(onEditRow(int, QString, int)));

    m_document.reset(new StatsDocument(this, *m_tableModel));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_newDocument_triggered()
{
    m_document->createNew();
}

void MainWindow::on_saveDocument_triggered()
{
    m_document->save();
}

void MainWindow::on_openDocument_triggered()
{
    m_document->open();
}

void MainWindow::on_saveDocumentAs_triggered()
{
    m_document->saveAs();
}

void MainWindow::on_showTable_triggered()
{
}

void MainWindow::on_showDiagram_triggered()
{
}

void MainWindow::on_actionAbout_triggered()
{
    std::unique_ptr<AboutDialog> dialog(new AboutDialog(this));
    dialog->exec();
}

void MainWindow::on_actionInsertRow_triggered()
{
    std::unique_ptr<InsertRowDialog> dialog(new InsertRowDialog(this));
    connect(dialog.get(), SIGNAL(rowReady(QString, int)), this, SLOT(onRowReady(QString, int)));
    dialog->exec();
}

void MainWindow::onRowReady(QString text, int value)
{
    m_undoStack->push(new InsertRowCommand(*m_tableModel, text, value));
}

void MainWindow::onEditRow(int row, QString text, int value)
{
    m_undoStack->push(new EditCommand(*m_tableModel, row, text, value));
}

void MainWindow::on_actionDeleteRow_triggered()
{
    std::set<int> deletedRows = m_ui->tableData->selectedRows();
    if (deletedRows.size() == 0)
    {
        return;
    }

    auto statsModel = m_tableModel->statsModel();
    m_undoStack->push(new DeleteRowCommand(*m_tableModel, deletedRows));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect tableArea = QRect(QPoint(0, 0), event->size());
    m_ui->tableData->setGeometry(tableArea);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_undoStack->canUndo())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            bool docSaved = m_document->save();
            if (!docSaved)
            {
                event->ignore();
            }
        }
        else if (ret == QMessageBox::Cancel)
            event->ignore();
    }
}
