#include "TexturasSDL.h"
#include "Error.h"

using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 
//------------------------------------------------------------------------------------------------------------------------------

TexturasSDL::TexturasSDL()
{
	pTexture = nullptr;
}


TexturasSDL::~TexturasSDL()
{
	SDL_DestroyTexture(pTexture);
}
//---------------------------------------------------------------------------------------------------------------------------
int TexturasSDL::getH(){
	return h;
}
int TexturasSDL::getW(){
	return w;
}
//---------------------------------------------------------------------------------------------------------------------------

void TexturasSDL::load(SDL_Renderer* pRenderer, string const& nombArch){

	//Load image
	SDL_Surface* pSurface;
	pSurface = IMG_Load(nombArch.c_str());  // si usamos string: bmpName.c_str() 
	if (pSurface == nullptr) {
		cout << "Unable to load image " << nombArch.c_str() << "! \nSDL Error: " << SDL_GetError() << '\n';
		throw ELoadTexture("Unable to load textures. Game will be closed ");
	}
	else {
		//std::cout << h << w;

		SDL_DestroyTexture(pTexture);
		pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
		SDL_FreeSurface(pSurface);
		if (pTexture == nullptr) {
			cout << "Unable to load image " << nombArch.c_str() << "! \nSDL Error: " << SDL_GetError() << '\n';
			throw ELoadTexture("Unable to load textures. Game will be closed ");
		}
		w = pSurface->w;
		h = pSurface->h;
		pTexSurface=  pSurface;
	}
}
//-------------------------------------------------------------------------------------------------------
void TexturasSDL::draw(SDL_Renderer* prenderer, SDL_Rect const& rect, Uint8 alpha){
	SDL_SetTextureAlphaMod(pTexture, alpha);
	SDL_RenderCopy(prenderer, pTexture, nullptr, &rect);  // nullptr, nullptr -> toda la textura en toda la ventana
}
void TexturasSDL::draw(SDL_Renderer* prenderer, SDL_Rect const& rectAnim, SDL_Rect& rect, Uint8 alpha){
	SDL_SetTextureAlphaMod(pTexture, alpha);
	SDL_RenderCopy(prenderer, pTexture, &rectAnim, &rect);  // nullptr, nullptr -> toda la textura en toda la ventana
}
void TexturasSDL::draw(SDL_Renderer* prenderer){
	SDL_RenderCopy(prenderer, pTexture, nullptr, nullptr);
}
//-----------------------------------------------------------------------------------------------------
void  TexturasSDL::loadFromText(SDL_Renderer* pRenderer, const string text, SDL_Color color){
	SDL_Surface* pSurface;
	SDL_DestroyTexture(pTexture);
	pSurface = font.textSolid(text, color);
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	SDL_FreeSurface(pSurface);

	if (!pTexture)throw ELoadFont("Font could not be loaded!");
}
//-----------------------------------------------------------------------------------------------------------------------
void TexturasSDL::loadFuente(std::string nombre, int tamano){

	font.load(nombre, tamano);
}
void TexturasSDL::setBlendMode(SDL_Renderer* prenderer, SDL_BlendMode blending)
{
	//Set blending function
	//SDL_SetRenderDrawBlendMode(prenderer, blending);
	SDL_SetTextureBlendMode(pTexture, blending);
}