#include <string>
#include <memory>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include "IObject.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Rectangle.hpp"

namespace Engine {
	Rectangle::Rectangle(float x, float y, unsigned char r, unsigned char g, unsigned char b, float anchorX, float anchorY) :
		IObject(x, y, 0, 0, anchorX, anchorY), Color(al_map_rgb(r, g, b)) {
	}
	void Rectangle::Draw() const {
		al_draw_filled_rectangle(Position.x - Anchor.x , Position.y - Anchor.y , Position.x - Anchor.x+20,Position.y - Anchor.y+3 ,Color);
	}

}

