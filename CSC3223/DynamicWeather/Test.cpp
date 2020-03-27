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
#include "TextureManager.h"

using namespace NCL;
using namespace CSC3223;

Matrix4 CameraMovment(Matrix4 cam) {
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_W)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 0, 1));
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_S)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 0, -1));
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_D)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(-1, 0, 0));
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_A)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(1, 0, 0));
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_SHIFT)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, 1, 0));
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_SPACE)) {
		cam.SetPositionVector(cam.GetPositionVector() + Vector3(0, -1, 0));
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_LEFT)) {
		cam = Matrix4::Rotation(-1, Vector3(0, 1, 0)) * cam;
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_RIGHT)) {
		cam = Matrix4::Rotation(1, Vector3(0, 1, 0)) * cam;
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_UP)) {
		cam = Matrix4::Rotation(-1, Vector3(1, 0, 0)) * cam;
	}
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_DOWN)) {
		cam = Matrix4::Rotation(1, Vector3(1, 0, 0)) * cam;
	}

	return cam;
}

void DrawPlane(Renderer* renderer) {
	OGLMesh* floor = new OGLMesh();
	floor->SetVertexPositions({ Vector3(-20,0,-10),Vector3(20,0,-10), Vector3(-20,0,10), Vector3(20,0,10) });
	floor->SetVertexTextureCoords({ Vector2(0,0),Vector2(1,0), Vector2(0,1), Vector2(1,1), });
	floor->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	Vector4 floorColour = Vector4(0.3f, 0.3f, 0.3f, 1);
	floor->SetVertexColours({ floorColour,floorColour,floorColour,floorColour });
	floor->UploadToGPU();
	RenderObject* o = new RenderObject(floor, Matrix4::Translation(Vector3(0, -10, -20)));
	renderer->AddRenderObject(o);
}


vector<Particle*>* DrawCloud(Renderer* renderer, float x, float y, float z) {
	OGLShader* shader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "cloudShader.glsl");
	TextureBase* texture = OGLTexture::RGBATextureFromFilename("snowflake.png");
	vector<Particle*>* particles = new vector<Particle*>();

	OGLMesh* cloudPoint = new OGLMesh();
	cloudPoint->SetVertexPositions({ Vector3(0,0,0) });
	cloudPoint->SetPrimitiveType(GeometryPrimitive::Points);
	cloudPoint->SetVertexColours({ Vector4(1,1,1,1) });
	cloudPoint->UploadToGPU();


	for (int i = 0; i < 10; i++) {
		Vector3 position = Vector3(
			(rand() % 60) / 10.0f + x,
			(rand() % 20) / 10.0f + y,
			z+(i*0.1f)
		);
		Particle* p = new Particle(position,cloudPoint,shader,texture,renderer);
		particles->push_back(p);
	}


	return particles;
}

int main() {
	Window*w = Window::CreateGameWindow("Dynamic Weather Test Window");
	if (!w->HasInitialised()) {
		return -1;
	}
	Renderer* renderer = new Renderer(*w);
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.45, 0.55, 0.65, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	float time = 0;
	Matrix4 cam;

	DrawCloud(renderer, 5, 5, -20);
	DrawCloud(renderer, -10, 5, -20);

	//DrawPlane(renderer);
	Snow* s = new Snow(renderer);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		
		time = w->GetTimer()->GetTimeDelta();
		renderer->Update(time);
		s->Update();	

		int pCount = s->getParticleCount() - (s->getParticleCount() % 10);

		w->SetTitle("P count: " + std::to_string(pCount));

		cam = CameraMovment(cam);
		renderer->SetViewMatrix(cam);
		renderer->Render();
	}

	delete renderer;
	Window::DestroyGameWindow();
}