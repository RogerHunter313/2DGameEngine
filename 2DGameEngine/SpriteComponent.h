#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H   // leaving out the S here messed me up for a good 10 minutes..

#include <SDL.h>
#include "TextureManager.h"
#include "AssetManager.h"
#include "Animation.h"

class SpriteComponent : public Component { //inherits from component
	public:
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

		SpriteComponent(std::string assetTextureId) {
			isAnimated = false;
			isFixed = false;
			SetTexture(assetTextureId);
		}

		SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
			this->isAnimated = true;  // this-> is this line is for consistency
			this->numFrames = numFrames;
			this->animationSpeed = animationSpeed;
			this->isFixed = isFixed;

			if (hasDirections) {
				Animation downAnimation(0, numFrames, animationSpeed);
				Animation rightAnimation(1, numFrames, animationSpeed);
				Animation leftAnimation(2, numFrames, animationSpeed);
				Animation upAnimation(3, numFrames, animationSpeed);

				animations.emplace("DownAnimation", downAnimation);
				animations.emplace("RightAnimation", rightAnimation);
				animations.emplace("LeftAnimation", leftAnimation);
				animations.emplace("UpAnimation", upAnimation);

				this->animationIndex = 0;
				this->currentAnimationName = "DownAnimation";  // for simplicity, starting animations with down
			}
			else {
				Animation singleAnimation = Animation(0, numFrames, animationSpeed);
				animations.emplace("SingleAnimation", singleAnimation);
				this->animationIndex = 0;
				this->currentAnimationName = "SingleAnimation";
			}

			Play(this->currentAnimationName);
			SetTexture(id);

		}

		void Play(std::string animationName) {
			numFrames = animations[animationName].numFrames;
			animationIndex = animations[animationName].index;
			animationSpeed = animations[animationName].animationSpeed;
			currentAnimationName = animationName;
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
			if (isAnimated) {
				sourceRectangle.x = (sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames));  //shifts the panel across the spritesheet, thinking sourceRectangle is the sprite sheet
			}
			sourceRectangle.y = animationIndex * transform->height;

			destinationRectangle.x = static_cast<int> (transform->position.x) - (isFixed ? 0 : Game::camera.x); //TODO:: review stat_cast
			destinationRectangle.y = static_cast<int> (transform->position.y) - (isFixed ? 0 : Game::camera.y);
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
		bool isAnimated;
		int numFrames;
		int animationSpeed;
		bool isFixed;	//for a possible user interface
		std::map<std::string, Animation> animations;
		std::string currentAnimationName;
		unsigned int animationIndex = 0;

};

#endif