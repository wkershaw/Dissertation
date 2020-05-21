#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {

		class Renderer : public OGLRenderer
		{
		public:
			Renderer(Window& w);
			~Renderer();

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}
			
			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}

			void SetSnowSpeed(float snowSpeed) {
				this->snowSpeed = snowSpeed;
			};

			float GetSnowSpeed() {
				return snowSpeed;
			};

			void SetFogDensity(float fogDensity) {
				this->fogDensity = fogDensity;
			};

			float GetFogDensity() {
				return fogDensity;
			};

			void SetFogGradient(float fogGradient) {
				this->fogGradient = fogGradient;
			};

			float GetFogGradient() {
				return fogGradient;
			};

		protected:
			void RenderNode(RenderObject* root);
	
			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;

			GameTimer frameTimer;
			float fogDensity = 0.03f;
			float fogGradient = 1.5f;
			float snowSpeed = 0.1f;

		};
	}
}

