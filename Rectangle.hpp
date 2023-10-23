#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <string>
#include <memory>
#include "IObject.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
namespace Engine {
	/// <summary>
	/// A simple static text object.
	/// </summary>
	class Rectangle : public IObject {
	protected:
		// Smart pointer to font.
		//std::shared_ptr<ALLEGRO_PRIMITIVES> primitives;
	public:
		// Text to draw.
		// Text's color.
		ALLEGRO_COLOR Color;
		/// <summary>
		/// Construct a label object.
		/// </summary>
		/// <param name="text">Text to draw.</param>
		/// <param name="font">Font to draw in.</param>
		/// <param name="fontSize">Text's font size.</param>
		/// <param name="x">X-coordinate.</param>
		/// <param name="y">Y-coordinate.</param>
		/// <param name="r">Color's red value.</param>
		/// <param name="g">Color's green value.</param>
		/// <param name="b">Color's blue value.</param>
		/// <param name="a">Color's alpha value.</param>
		/// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
		/// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
		explicit Rectangle(float x, float y, unsigned char r, unsigned char g, unsigned char b , float anchorX = 0, float anchorY = 0);
		/// <summary>
		/// Draw text with loaded font.
		/// </summary>
		void Draw() const override;
		/// <summary>
		/// Return text width.
		/// </summary>
		/// <returns>Width of the text.</returns>

		/// <summary>
		/// Return text height.
		/// </summary>
		/// <returns>Height of the text.</returns>

	};
}

#endif // LABEL_HPP
