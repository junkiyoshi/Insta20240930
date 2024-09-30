#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);

	ofNoFill();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotateZ(ofGetFrameNum() * -0.77);

	ofColor color;
	float radius = 250;
	for (int i = 0; i < 2; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		color.setHsb(ofMap(i, 0, 1, 140, 255), 255, 255);

		for (int k = 0; k < 1300; k++) {

			float deg = ofGetFrameNum() * 1.44 + k * 0.25 + i * 180;

			auto location = glm::vec2(
				radius * cos(deg * DEG_TO_RAD),
				radius * sin(deg * DEG_TO_RAD));
			auto next = glm::vec2(
				radius * cos((deg + 1) * DEG_TO_RAD),
				radius * sin((deg + 1) * DEG_TO_RAD));

			auto velocity = next - location;

			float rotate_x = ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + k) * 0.003), 0, 1, -360, 360);
			float rotate_y = ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + k) * 0.003), 0, 1, -360, 360);

			ofSetColor(ofColor(color, ofMap(k, 0, 1300, 32, 64)));

			ofPushMatrix();
			ofTranslate(location);

			ofRotateY(rotate_y);
			ofRotateX(rotate_x);

			float len = ofMap(k, 0, 1300, 5, 60);
			ofBeginShape();
			for (int m = 0; m < 360; m += 60) {

				ofVertex(glm::vec2(len * cos(m * DEG_TO_RAD), len * sin(m * DEG_TO_RAD)));
			}
			ofEndShape(true);

			ofPopMatrix();
		}

	}

	/*
	int start = 200;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}