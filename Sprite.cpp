#include "Sprite.h"
#include <math.h>

std::map<std::string, sf::Texture*> Sprite::textures;

Sprite::Sprite(std::string filename) {
	if (Sprite::textures.find(filename) == Sprite::textures.end()) {
		Sprite::textures[filename] = new sf::Texture;
		Sprite::textures[filename]->loadFromFile(filename);
	}		
	this->tex = textures[filename];
}

void Sprite::Draw(sf::RenderWindow *wnd, Particle *particle, float ang, Vector2f size) {
	sf::Vertex vertices[4];
	Vector2f vertexPos;
	
	Vector2f xVector = Vector2f(cosf(ang), sinf(ang));
	Vector2f yVector = xVector.GetPerp();

	vertexPos = particle->pos - xVector * size.x - yVector * size.y;
	vertices[0] = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = particle->pos + xVector * size.x - yVector * size.y;
	vertices[1] = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = particle->pos + xVector * size.x + yVector * size.y;
	vertices[2] = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = particle->pos - xVector * size.x + yVector * size.y;
	vertices[3] = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
	vertices[1].texCoords = sf::Vector2f((float)tex->getSize().x, 0.0f);
	vertices[2].texCoords = sf::Vector2f((float)tex->getSize().x, (float)tex->getSize().y);
	vertices[3].texCoords = sf::Vector2f(0.0f, (float)tex->getSize().y);

	for (int i = 0; i < 4; i++) {
		vertices[i].color = sf::Color::White;
	}

	(*wnd).draw(vertices, 4, sf::Quads, tex);
}


void Sprite::Draw(sf::RenderWindow *wnd, std::vector<Particle*> particles) {
	size_t count = particles.size();
	sf::Vertex *vertices = new sf::Vertex[count];
	Vector2f  texSize = Vector2f((float)tex->getSize().x, (float)tex->getSize().y);
	float pi = 3.1415926f;
	Vector2f circleCenter = Vector2f((float)tex->getSize().x, (float)tex->getSize().y) * 0.5f;
	float circleRadius = tex->getSize().x * 0.5f;
	for (int i = 0; i < count; i++) {
		float ang = float(i) / count * (2.0f * pi);
		Vector2f pos = Vector2f(cosf(ang), sinf(ang)) * circleRadius + circleCenter;
		vertices[i].texCoords = sf::Vector2f(pos.x, pos.y);
	}

	for (size_t i = 0; i < count; i++) {
		vertices[i].position = sf::Vector2f(particles[i]->pos.x, particles[i]->pos.y);
	};

	(*wnd).draw(vertices, count, sf::TrianglesFan, tex);

	delete[] vertices;
}