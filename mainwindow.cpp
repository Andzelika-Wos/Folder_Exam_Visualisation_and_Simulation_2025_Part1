#include "MainWindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QMenuBar>
#include <QLineEdit>
#include <QInputDialog>
#include "Part1_VWindow.h"
#include "Part1_Renderer.h"

MainWindow::MainWindow(VulkanWindow *vw, QPlainTextEdit *logWidget)
    : mVulkanWindow(vw)
{
    //Wraps the VulkanWindow inside a QWidget so we can place it together with other widgets
    QWidget *vulkanWindowWrapper = QWidget::createWindowContainer(vw);

    mLogWidget = logWidget;
    //Sets the colors in the log window
    mLogWidget->setStyleSheet("color: white ; background-color: #520041 ;");

    QPushButton *quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);


    //connect quit button to quit-function
    connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    quitButton->setStyleSheet(R"(
    QPushButton
    {
        background-color: #d08de3;
        color: #541818;
        border-radius: 8px;
        padding: 10px 20px;
        font-size: 16px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #a46fb3;
    }
    QPushButton:pressed {
        background-color: #a46fb3;
    }
)");

    //connect changes in our logger to trigger scroll to end of log window, using a lambda
    connect(mLogWidget, &QPlainTextEdit::textChanged, [logWidget]()
            { logWidget->moveCursor(QTextCursor::End); });


    //Makes the layout of the program, adding items we have made
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMenuBar(createMenu());
    layout->addWidget(vulkanWindowWrapper, 7);
    mInfoTab = new QTabWidget(this);
    mInfoTab->addTab(mLogWidget, tr("Debug Log"));
    layout->addWidget(mInfoTab, 2);
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(quitButton, 1);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    //sets the keyboard input focus to the RenderWindow when program starts
    //(wrapped inside of this QWidget)
    // - can be deleted, but then you have to click inside the RenderWindow to get the focus
    vulkanWindowWrapper->setFocus();
}

QMenuBar *MainWindow::createMenu()
{
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu(tr("&File"), this);
    openFileAction = fileMenu->addAction(tr("&Open file..."));
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
    menuBar->setVisible(true);
    //
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    return menuBar;
}


void MainWindow::openFile() // slot
{

}

void MainWindow::selectName()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Object name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        mSelectedName = text.toStdString();

    auto rw = dynamic_cast<Renderer*>(mVulkanWindow->getRenderWindow());
    auto map = rw->getMap();
    auto visualObject = map[mSelectedName];
    if (visualObject != nullptr)
        mVulkanWindow->setSelectedObject(visualObject);
    else {
        QMessageBox msgBox;
        msgBox.setText("Finner ikke " + QString(mSelectedName.c_str()));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Close);
    }
}
