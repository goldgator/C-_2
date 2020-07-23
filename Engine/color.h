#pragma once
#include <Windows.h>
#include <algorithm>
#include <string>
using std::string;

namespace nc {
	struct Color {
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {};
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {};

		float& operator [] (size_t index) { return (&r)[index]; };
		const float& operator [] (size_t index) const { return (&r)[index]; };

		void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; };

		Color operator + (const Color& c) const { return Color(r + c.r, g + c.g, b + c.b); };
		Color operator - (const Color& c) const { return Color(r - c.r, g - c.g, b - c.b); };
		Color operator * (const Color& c) const { return Color(r * c.r, g * c.g, b * c.b); };
		Color operator / (const Color& c) const { return Color(r / c.r, g / c.g, b / c.b); };

		Color operator + (float s) const { return Color(r + s, g + s, b + s); };
		Color operator - (float s) const { return Color(r - s, g - s, b - s); };
		Color operator * (float s) const { return Color(r * s, g * s, b * s); };
		Color operator / (float s) const { return Color(r / s, g / s, b / s); };

		Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }

		Color& operator += (float s) { r += s; g += s; b += s; return *this; }
		Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
		Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
		Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

		friend std::istream& operator >> (std::istream& stream, Color& c) { // stream >> c
			string line;
			std::getline(stream, line);

			//Format {X,Y}
			string strip = line.substr(line.find("{") + 1, line.find("}")-1);
			std::replace(strip.begin(), strip.end(), ',', ' ');
			size_t sz;
			float cr = stof(strip, &sz);
			strip = strip.substr(sz);
			float cg = stof(strip, &sz);
			float cb = stof(strip.substr(sz));

			c.r = cr;
			c.g = cg;
			c.b = cb;

			return stream;

		};

		COLORREF pack888() const {
			COLORREF c = RGB(r, g, b);
			return c;
		}

		operator COLORREF() const {
			COLORREF c = RGB(r, g, b);
			return c;
		}

	};
}