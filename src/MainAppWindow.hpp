#ifndef MAINAPPWINDOW_HPP
#define MAINAPPWINDOW_HPP

#include <QMainWindow>
#include "login.hpp"
#include "file_manager.hpp"
#include "acl.hpp"

class MainAppWindow : public QMainWindow {
    Q_OBJECT

public:
    MainAppWindow(Login* loginSystem, file_manager* fm, ACL* acl, QWidget* parent = nullptr);
    ~MainAppWindow();

private:
    Login* m_loginSystem;
    file_manager* m_fileManager;
    ACL* m_acl;

    // Add UI elements and methods for main application functionality
};

#endif // MAINAPPWINDOW_HPP
