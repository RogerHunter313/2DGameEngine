#ifndef SPRITECOMPONENT_H
#define PRITECOMPONENT_H

#include <SDL.h>
#include "Component.h"
#include "TextureManager.h"
#include "AssetManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component { //inherits from component
	public:
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

		SpriteComponent(const char* filePath) {
			SetTexture(filePath);
		}

		void SetTexture(std::string assetTextureId) {
			texture = Game::assetManager->GetTexture(assetTextureId);
		}

		void Initialize() override {
			transform = owner->GetComponent<TransformComponent>();
			sourceRectangle.x = 0;
			sourceRectangle.y = 0;
			sourceRectangle.w = transform->width;
			sourceRectangle.h = transform->height;
		}

		void Update(float deltaTime) override {
			destinationRectangle.x = (int) transform->position.x;
			destinationRectangle.y = (int) transform->position.x;
			destinationRectangle.w = transform->width * transform->scale;
			destinationRectangle.h = transform->height * transform->scale;
		}

		void Render() override {
			TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
		}

	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;

};

#endif