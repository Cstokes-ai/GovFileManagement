#include <QApplication>
#include <QMainWindow>
#include "login.hpp"
#include "file_manager.hpp"
#include "acl.hpp"
#include "crypto.hpp"
#include "auth.hpp"


// If you have custom GUI windows, include them here
// #include "LoginWindow.hpp"
// #include "MainAppWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Initialize your backend logic
    Login loginSystem;
    file_manager fm;
    ACL acl;

    // Example: Create a main window (replace with your custom window if you have one)
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("GovFileManagement");
    mainWindow.resize(800, 600);
    mainWindow.show();

    // Example: If you have a custom login window, you could do:
    // LoginWindow loginWindow(&loginSystem, &fm, &acl);
    // loginWindow.show();

    // Example: After successful login, show your main application window
    // MainAppWindow mainAppWindow(&loginSystem, &fm, &acl);
    // mainAppWindow.show();

    return app.exec(); // Start the Qt event loop
}
