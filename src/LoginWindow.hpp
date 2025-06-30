#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QDialog>
#include "login.hpp"
#include "file_manager.hpp"
#include "acl.hpp"

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    LoginWindow(Login* loginSystem, file_manager* fm, ACL* acl, QWidget* parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginButtonClicked();
    void onCancelButtonClicked();

private:
    Login* m_loginSystem;
    file_manager* m_fileManager;
    ACL* m_acl;

    // Add UI elements like QLineEdit for username/password and QPushButton for login/cancel
};

#endif // LOGINWINDOW_HPP
