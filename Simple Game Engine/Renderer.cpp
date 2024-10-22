#include "Renderer.h"
#include "Log.h"
#include "Texture.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include <SDL_image.h>
#include "Camera.h"

Renderer::Renderer() : SDLRenderer(nullptr) {

}

bool Renderer::initialize(Window& window) {
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer) {
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		Log::error(LogCategory::Video, "Unable to initialize SDL_Image");
		return false;
	}
	return true;
}

void Renderer::beginDraw() {
	SDL_SetRenderDrawColor(SDLRenderer, 62, 53, 70, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::draw()
{
	drawSprites();
}

void Renderer::endDraw() {
	SDL_RenderPresent(SDLRenderer);
}

void Renderer::drawRect(Rectangle& rect) {
	SDL_SetRenderDrawColor(SDLRenderer,255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::addSprite(SpriteComponent* sprite)
{
	int spriteDrawOrder = sprite->getDrawOrder();
	auto iter = std::begin(sprites);
	for (; iter != end(sprites); ++iter) {
		if (spriteDrawOrder < (*iter)->getDrawOrder()) break;
	}
	sprites.insert(iter, sprite);
}

void Renderer::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}

void Renderer::drawSprites()
{
	for (auto sprite : sprites) {
		sprite->draw(*this);
	}
}

void Renderer::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
	Vector2 position = actor.getPosition();
	float rotation = actor.getRotation();
	Vector2 scale = actor.getScale();
	drawSprite(position, rotation, scale, tex, srcRect, origin, flip);
}

void Renderer::drawSprite(Vector2 position, float rotation,Vector2 scale, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const
{
	SDL_Rect dstRect;

	Vector2 camPos = Vector2::zero;
	float camZoom = 1;


	if (Camera::mainCam != nullptr) {
		camZoom = Camera::mainCam->getZoom() -0.2;
		camPos = Camera::mainCam->getPos() * camZoom;
	}

	dstRect.w = static_cast<int>(tex.getWidth() * scale.x * camZoom) + 1 ;
	dstRect.h = static_cast<int>(tex.getHeight() * scale.y * camZoom) + 1;

	dstRect.x = static_cast<int>(((position.x - origin.x) * camZoom) - camPos.x + (WINDOW_WIDTH/2));
	dstRect.y = static_cast<int>(((position.y  - origin.y) * camZoom) - camPos.y + (WINDOW_HEIGHT / 2));

	SDL_Rect* srcSDL = nullptr;
	if (srcRect != Rectangle::nullRect) {
		srcSDL = new SDL_Rect{
			Maths::round(srcRect.x),
			Maths::round(srcRect.y),
			Maths::round(srcRect.width),
			Maths::round(srcRect.height)
		};
	}

	SDL_RenderCopyEx(
		SDLRenderer,
		tex.toSDLTexture(),
		srcSDL,
		&dstRect,
		-Maths::toDegrees(rotation),
		nullptr,
		SDL_FLIP_NONE
	);

	delete srcSDL;

}

void Renderer::close() {
	SDL_DestroyRenderer(SDLRenderer);
}