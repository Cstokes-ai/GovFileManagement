#include <QApplication>
#include <QMainWindow>
#include "login.hpp"
#include "file_manager.hpp"
#include "acl.hpp"
#include "crypto.hpp"
#include "auth.hpp"
#include "Login.hpp" // Include your custom login window
#include "MainAppWindow.hpp" // Include your main application window
#include "LoginWindow.hpp"
#include "MainAppWindow.hpp"

// If you have custom GUI windows, include them here
// #include "LoginWindow.hpp"
// #include "MainAppWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize your backend logic
    Login loginSystem;
    file_manager fm;
    ACL acl;

    // Create and show the login window
    LoginWindow loginWindow(&loginSystem, &fm, &acl);
    if (loginWindow.exec() == QDialog::Accepted) {
        // If login is successful, show the main application window
        MainAppWindow mainAppWindow(&loginSystem, &fm, &acl);
        mainAppWindow.show();

        return app.exec(); // Start the Qt event loop
    }

    return 0; // Exit if login is not successful
}
