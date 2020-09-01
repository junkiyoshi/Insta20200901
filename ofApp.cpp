#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> location_list;

	int span = 36;
	for(int x = span * 0.5; x < ofGetWidth(); x += span){

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			location_list.push_back(glm::vec2(
				x + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, span * -0.4, span * 0.4),
				y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, span * -0.4, span * 0.4)));
		}
	}

	for (int i = 0; i < location_list.size(); i++) {

		float max_alpha = 0;
		for (int k = 0; k < location_list.size(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < span * 0.85) {

				vector<glm::vec2> vertices;
				auto direction_rad = std::atan2(location_list[k].y - location_list[i].y, location_list[k].x - location_list[i].x);
				auto direction_deg = direction_rad * RAD_TO_DEG + 90;

				int radius = 8;
				for (int deg = direction_deg; deg <= direction_deg + 180; deg += 3) {

					vertices.push_back(location_list[i] + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
				}

				for (int deg = direction_deg + 180; deg <= direction_deg + 360; deg += 3) {

					vertices.push_back(location_list[k] + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
				}

				auto alpha = distance < span * 0.6 ? 255 : ofMap(distance, span * 0.6, span * 0.85, 255, 0);
				ofSetColor(39, alpha);
				ofNoFill();
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				if (alpha > max_alpha) { max_alpha = alpha; }
			}
		}

		ofFill();
		ofSetColor(39, max_alpha);
		ofDrawCircle(location_list[i], 4);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}