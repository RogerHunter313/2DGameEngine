#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"
#include <SDL_ttf.h>

class AssetManager {
	public:
		AssetManager(EntityManager* manager);
		void ClearData();

		void AddTexture(std::string textureId, const char* filePath);
		void AddFont(std::string fontId, const char* filePath, int fontSize);

		SDL_Texture* GetTexture(std::string textureId);
		TTF_Font* GetFont(std::string fontId);

	private:
		EntityManager* manager;
		std::map<std::string, SDL_Texture*> textures;
		std::map<std::string, TTF_Font*> fonts;
};

#endif
