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

int main() {
	Window*w = Window::CreateGameWindow("Dynamic Weather Test Window");
	Matrix4 cam;
	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1,0.1,0.1,1);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 3);


	NCL::CSC3222::TextureManager* texMan = new NCL::CSC3222::TextureManager();

	OGLMesh* floor = new OGLMesh();
	floor->SetVertexPositions({ Vector3(-10,0,-10),Vector3(10,0,-10), Vector3(-10,0,10), Vector3(10,0,10) });
	floor->SetVertexTextureCoords({Vector2(0,0),Vector2(1,0), Vector2(0,1), Vector2(1,1), });
	floor->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	Vector4 floorColour = Vector4(1, 1, 1, 1);
	floor->SetVertexColours({floorColour,floorColour,floorColour,floorColour});
	floor->UploadToGPU();
	RenderObject* o = new RenderObject(floor, Matrix4::Translation(Vector3(0, -10, -20)));
	//TextureBase* t = OGLTexture::RGBATextureFromFilename("hm.png");
	TextureBase* t = texMan->GetTexture("snowflake.png");
	o->SetBaseTexture(t);
	renderer->AddRenderObject(o);

	Snow* s = new Snow(renderer);

	float time = 0;
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		time += w->GetTimer()->GetTimeDelta();
		s->Update();	


		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::KEYBOARD_W)) {
			cam.SetPositionVector(cam.GetPositionVector() + Vector3(0,0,1));
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


		//cam =Matrix4::Rotation(Window::GetMouse()->GetRelativePosition().x, Vector3(0, 1, 0)) * Matrix4::Rotation(Window::GetMouse()->GetRelativePosition().y, Vector3(1, 0, 0)) * cam;
		renderer->SetViewMatrix(cam);
		renderer->Render();
	}

	delete renderer;
	Window::DestroyGameWindow();
}