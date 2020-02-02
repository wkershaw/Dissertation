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

using namespace NCL;
using namespace CSC3223;

int main() {
	Window*w = Window::CreateGameWindow("Dynamic Weather Test Window");
	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	Particle* sp = new Particle(0, 0, -5);
	renderer->AddRenderObject(sp->getObject());

	float time = 0;
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		time += w->GetTimer()->GetTimeDelta();
		sp->DisplaceBy(0,-0.1f,0);
		renderer->Render();
	}

	delete renderer;
	Window::DestroyGameWindow();
}