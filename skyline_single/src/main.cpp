#include "ofMain.h"
#include "storeApp.h"
#include "ofAppGlutWindow.h"
#include "ofxXmlSettings.h"
//========================================================================
int main( ){
    ofAppGlutWindow window;
	ofSetDataPathRoot("data/");
	string _fileString = ofToDataPath("config.xml", true);
	cout << ("Loading OSC settings from file " + _fileString);
    ofSetDataPathRoot("../../../data/");
	ofxXmlSettings xmlReader;
    if (!xmlReader.loadFile(_fileString)) 
        cerr << ("ERROR loading XML file!");
	
	int port = xmlReader.getValue("settings:osc:port", 13000, 0);
	int width = xmlReader.getValue("settings:screen:width", 720, 0);
	int height = xmlReader.getValue("settings:screen:height", 1280, 0);
	
	
	ofSetupOpenGL(&window, width, height, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new storeApp(port));

}

