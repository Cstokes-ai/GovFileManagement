#include "LoginWindow.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginWindow::LoginWindow(Login* loginSystem, file_manager* fm, ACL* acl, QWidget* parent)
    : QDialog(parent), m_loginSystem(loginSystem), m_fileManager(fm), m_acl(acl) {

    setWindowTitle("Login");
    setModal(true);

    // Example UI setup
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLineEdit* usernameField = new QLineEdit(this);
    usernameField->setPlaceholderText("Username");
    layout->addWidget(usernameField);

    QLineEdit* passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordField);

    QPushButton* loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    QPushButton* cancelButton = new QPushButton("Cancel", this);
    layout->addWidget(cancelButton);

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        // Validate login credentials
        if (m_loginSystem->validateCredentials(usernameField->text().toStdString(), passwordField->text().toStdString())) {
            accept(); // Close dialog with QDialog::Accepted
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        }
    });

    connect(cancelButton, &QPushButton::clicked, this, &LoginWindow::reject);
}

LoginWindow::~LoginWindow() {}
