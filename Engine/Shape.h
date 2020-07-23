#pragma once
#include "color.h"
#include <vector>
#include "Vector2.h"
#include "core.h"
#include <fstream>
#include "Transform.h"
#include "Matrix22.h"
#include "Matrix33.h"


namespace nc {
	class Shape {
		public:
			Shape() {
				m_points.push_back(Vector2(0, 0));
				m_points.push_back(Vector2(30, 0));
				m_points.push_back(Vector2(30, 30));
				m_points.push_back(Vector2(0, 30));
				m_color = Color(111, 255, 233);
			};
			Shape(const std::vector<Vector2>& points, const Color& color) {
				m_points = points;
				m_color = color;
			};

			bool Load(const std::string& filename) {
				bool success = false;

				std::ifstream stream(filename);
				if (stream.is_open()) {
					success = true;

					//m_color {111, 255, 233};
					//m_points {0,0}\n {30,0}\n {30,30}\n {0,30}...

					stream >> m_color;


					//Get # of points
					string line;
					getline(stream, line);
					size_t size;
					size = stoi(line);
					//Read points
					std::vector<Vector2> newPoints;
					Vector2 point;
					for (size_t i = 0; i < size; i++) {
						stream >> point;
						newPoints.push_back(point);
					}

					m_points = newPoints;
				}

				return success;
			}


			void Draw(Core::Graphics& graphics, Vector2 position, float scale, float angle) {
				graphics.SetColor(GetColor());

				nc::Matrix33 mxs;
				mxs.Scale(scale);
				Matrix33 mxr;
				mxr.Rotate(angle);
				Matrix33 mxt;
				mxt.Translate(position);

				Matrix33 mx = mxs * mxr * mxt;


				Vector2 a, b;
				for (int i = 0; i < m_points.size(); i++) {
					a = m_points[i];
					b = (i == m_points.size() - 1) ? m_points[0] : (m_points[i+1]);

					//transform
					//scale & rotate & translate
					a = a * mx;
					b = b * mx;

					graphics.DrawLine(a.x, a.y, b.x, b.y);
				}
			};



			void Draw(Core::Graphics& graphics, const Transform& transform) { 
				graphics.SetColor(GetColor());
				Vector2 a, b;
				for (int i = 0; i < m_points.size(); i++) {
					a = m_points[i];
					b = (i == m_points.size() - 1) ? m_points[0] : (m_points[i + 1]);

					//transform
					//scale & rotate & translate
					a = a * transform.matrix;
					b = b * transform.matrix;

					graphics.DrawLine(a.x, a.y, b.x, b.y);
				}
			}

			void SetColor(Color color) {
				m_color = color;
			}
			const Color& GetColor() const {
				return m_color;
			}

			float GetRadius() { return radius;  }
		private:
			std::vector<Vector2> m_points;
			Color m_color;
			float radius{ 1 };
	};
}