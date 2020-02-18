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

using namespace NCL;
using namespace CSC3223;


Matrix4 CameraMovement(Matrix4 c) {
	Matrix4 cam = c;
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

void DrawPlane(Renderer* r, Vector3 position, Vector2 size, Vector4 colour) {
	OGLMesh* plane = new OGLMesh();
	plane->SetVertexPositions({ Vector3(-(size.x/2),0,-(size.y/2)),Vector3((size.x / 2),0,-(size.y / 2)), Vector3(-(size.x / 2),0,(size.y / 2)), Vector3((size.x / 2),0,(size.y / 2)) });
	plane->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	plane->SetVertexColours({ colour,colour,colour,colour });
	plane->UploadToGPU();
	r->AddRenderObject(new RenderObject(plane, Matrix4::Translation(position)));
}

int main() {
	Window*w = Window::CreateGameWindow("Dynamic Weather Test Window");
	Matrix4 cam;
	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	Snow* s = new Snow(renderer,Vector3(0,0,0),Vector3(50,40,50),10000,700);
	DrawPlane(renderer,Vector3(0,-20,0),Vector2(50,50),Vector4(0.5,0.3,0.2,1));

	float time = 0;
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		time += w->GetTimer()->GetTimeDelta();
		s->Update();	


		cam = CameraMovement(cam);
		renderer->SetViewMatrix(cam);
		renderer->Render();
	}

	delete renderer;
	Window::DestroyGameWindow();
}