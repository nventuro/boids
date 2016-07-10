#include "ofMain.h"
#include "Config.h"

#include "App.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"

int main(void)
{
    Config::load();

    ofGLFWWindowSettings app_window_settings;
    app_window_settings.width = Config::width;
    app_window_settings.height = Config::height;
    app_window_settings.setPosition(ofVec2f(100, 100));
    app_window_settings.resizable = false;

    std::shared_ptr<ofAppBaseWindow> app_window = ofCreateWindow(app_window_settings);

    ofGLFWWindowSettings gui_window_settings;
    gui_window_settings.width = 400;
    gui_window_settings.height = 400;
    gui_window_settings.setPosition(ofVec2f(100 + Config::width + 50, 100));
    gui_window_settings.resizable = true;

    std::shared_ptr<ofAppBaseWindow> gui_window = ofCreateWindow(gui_window_settings);

    std::shared_ptr<GuiApp> gui_app(new GuiApp);
    std::shared_ptr<App> app(new App(gui_app));

    ofRunApp(app_window, app);
    ofRunApp(gui_window, gui_app);

    ofRunMainLoop();
}
