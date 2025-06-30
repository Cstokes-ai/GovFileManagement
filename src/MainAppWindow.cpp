#include "MainAppWindow.hpp"
#include <QMenuBar>
#include <QStatusBar>
#include <QWidget>

MainAppWindow::MainAppWindow(Login* loginSystem, file_manager* fm, ACL* acl, QWidget* parent)
    : QMainWindow(parent), m_loginSystem(loginSystem), m_fileManager(fm), m_acl(acl) {

    setWindowTitle("GovFileManagement - Main Application");
    resize(1024, 768);

    // Example: Setup main application UI
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Add menus and actions
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &MainAppWindow::close);
}

MainAppWindow::~MainAppWindow() {}
