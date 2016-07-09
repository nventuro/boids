#include "ofMain.h"
#include "Settings.h"
#include "ofApp.h"

int main(void)
{
    Settings::load();

	ofSetupOpenGL(Settings::width, Settings::height, OF_WINDOW);

	ofRunApp(new ofApp());
}
