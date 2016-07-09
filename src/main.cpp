#include "ofMain.h"
#include "Settings.h"

#include "App.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"

int main(void)
{
    Settings::load();

    ofGLFWWindowSettings gui_window_settings;
    gui_window_settings.width = 400;
    gui_window_settings.height = 400;
    gui_window_settings.setPosition(ofVec2f(0, 0));
    gui_window_settings.resizable = true;

    std::shared_ptr<ofAppBaseWindow> gui_window = ofCreateWindow(gui_window_settings);

    ofGLFWWindowSettings app_window_settings;
    app_window_settings.width = Settings::width;
    app_window_settings.height = Settings::height;
    app_window_settings.setPosition(ofVec2f(500, 0));
    app_window_settings.resizable = false;

    std::shared_ptr<ofAppBaseWindow> app_window = ofCreateWindow(app_window_settings);

    std::shared_ptr<App> app(new App);
    std::shared_ptr<GuiApp> gui_app(new GuiApp);

    app->gui = gui_app;

    ofRunApp(gui_window, gui_app);
    ofRunApp(app_window, app);
    ofRunMainLoop();
}
