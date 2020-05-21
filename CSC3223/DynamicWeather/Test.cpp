#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"
#include "Particle.h"
#include "Snow.h"
#include "Cloud.h"
#include "draw.h"

#include <iostream>
#include <fstream>
#include "windows.h"
#include "psapi.h"

using namespace NCL;
using namespace CSC3223;

Matrix4 CameraMovment(Matrix4 cam) {
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_W)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 0, 1));
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_S)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 0, -1));
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_D)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(-1, 0, 0));
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_A)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(1, 0, 0));
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_SHIFT)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 1, 0));
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_SPACE)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, -1, 0));
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_LEFT)) {
		cam = Matrix4::Rotation(-1, Vector3(0, 1, 0)) * cam;
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_RIGHT)) {
		cam = Matrix4::Rotation(1, Vector3(0, 1, 0)) * cam;
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_UP)) {
		cam = Matrix4::Rotation(-1, Vector3(1, 0, 0)) * cam;
	}
	else if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_DOWN)) {
		cam = Matrix4::Rotation(1, Vector3(1, 0, 0)) * cam;
	}

	return cam;
}

void gatherResults(std::ofstream& file, int& frameCount, int& pCount, float& dt) {

	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	SIZE_T virtMemUsedByMe = pmc.PrivateUsage;
	file << frameCount << "," << pCount << "," << dt << "," << physMemUsedByMe << "," << virtMemUsedByMe << "\n";
}

int main() {
	std::ofstream resultsFile;
	resultsFile.open("results_p_limit_v2.csv");
	resultsFile << "frame,particles,delta,physMem,virtMem\n";

	Window*w = Window::CreateGameWindow("Dynamic Weather Test Window");
	if (!w->HasInitialised()) {
		return -1;
	}
	Renderer* renderer = new Renderer(*w);
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));
	Draw drawer = Draw(renderer);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.45, 0.55, 0.65, 1);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	float time = 0;
	int frameCounter = 0;
	int pCount = 0;
	Matrix4 cam;
	cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 0, -20));

	RenderObject* cube = drawer.DrawCuboid(Vector3(-10,-9,-20),Vector3(1,1,1),Vector4(1,0.3,0.3,1));
	RenderObject* plane = drawer.DrawPlane(Vector3(0,-10,-10),Vector2(30,30),Vector4(0.2,0.2,0.2,1));
	Snow* s = new Snow(Vector3(0,0,-10),Vector3(30,20,30),renderer);
	
	Cloud* cloud = new Cloud(Vector3(-25, 10, -30), Vector3(5, 2, 2), renderer);
	Cloud* cloud1 = new Cloud(Vector3(-14, 12, -35), Vector3(5, 2, 2), renderer);
	Cloud* cloud2 = new Cloud(Vector3(-8, 15, -40), Vector3(5, 2, 2), renderer);
	Cloud* cloud3 = new Cloud(Vector3(5, 8, -50), Vector3(5, 2, 2), renderer);
	Cloud* cloud4 = new Cloud(Vector3(10, 11, -30), Vector3(5, 2, 2), renderer);
	Cloud* cloud5 = new Cloud(Vector3(13, 9, -25), Vector3(5, 2, 2), renderer);
	Cloud* cloud6 = new Cloud(Vector3(19, 5, -35), Vector3(5, 2, 2), renderer);

	
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		time = w->GetTimer()->GetTimeDelta();
		renderer->Update(time);
		s->Update();	

		frameCounter++;
		//w->SetTitle("Frame: " + std::to_string(frameCounter));
		//pCount = s->getParticleCount();
		//gatherResults(resultsFile, frameCounter, pCount,time);


		cam = CameraMovment(cam);
		renderer->SetViewMatrix(cam);
		renderer->Render();
	}
	resultsFile.close();
	delete renderer;
	Window::DestroyGameWindow();
}