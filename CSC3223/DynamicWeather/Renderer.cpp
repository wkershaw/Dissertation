#include "Renderer.h"
#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3223;

Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader	= new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix		= Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

Renderer::~Renderer()
{
	delete defaultShader;
}

float comp(const Matrix4& viewMatrix, const RenderObject& rhs) {
	return (viewMatrix * rhs.GetTransform()).GetPositionVector().z;
};

void Renderer::RenderFrame() {
	OGLShader* activeShader = nullptr;

	int modelLocation	= 0; 
	Matrix4 p = viewMatrix;
	std::sort(renderObjects.begin(), renderObjects.end(), [p](RenderObject* lhs, RenderObject* rhs) {return comp(p, *lhs) < comp(p, *rhs); });

	

	for (const RenderObject* object : renderObjects) {
		OGLShader* objectShader = (OGLShader*)object->GetShader();
		if (!object->GetMesh()) {
			continue;
		}
		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}
		if (objectShader != activeShader) {
			activeShader = objectShader;
			BindShader(activeShader);
			int projLocation	= glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
			int viewLocation	= glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
			modelLocation		= glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");	
			int timeLocation	= glGetUniformLocation(activeShader->GetProgramID(), "time");
			float fogDensityLocation = glGetUniformLocation(activeShader->GetProgramID(), "fogDensity");
			float fogGradientLocation = glGetUniformLocation(activeShader->GetProgramID(), "fogGradient");
			float snowSpeedLocation = glGetUniformLocation(activeShader->GetProgramID(), "snowSpeed");
			float particleSizeLocation = glGetUniformLocation(activeShader->GetProgramID(), "particleSize");

			glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);

			if (timeLocation >= 0) {
				float totalTime = frameTimer.GetTotalTime();
				glUniform1f(timeLocation, totalTime);
			}
			if (fogDensityLocation >= 0) {
				glUniform1f(fogDensityLocation, fogDensity);
			}
			if (fogGradientLocation >= 0) {
				glUniform1f(fogGradientLocation, fogGradient);
			}
			if (snowSpeedLocation >= 0) {
				glUniform1f(snowSpeedLocation, snowSpeed);
			}
			if (particleSizeLocation >= 0) {
				glUniform1f(particleSizeLocation, object->GetParticleSize());
			}
		}

		Matrix4 mat = object->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&mat);

		BindTextureToShader(object->GetBaseTexture(), "mainTex", 0);
		BindMesh(object->GetMesh());
		DrawBoundMesh();
	}
}

void Renderer::OnWindowResize(int w, int h)	{
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}