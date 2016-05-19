#include "Sprite.h"

std::map<std::string, sf::Texture*> Sprite::textures;

Sprite::Sprite(std::string filename, float texScale) {
	if (Sprite::textures.find(filename) == Sprite::textures.end()) {
		Sprite::textures[filename] = new sf::Texture;
		Sprite::textures[filename]->loadFromFile(filename);
	}		
	this->tex = textures[filename];
	if (!(texScale < 0.000001f && texScale > -0.000001f)) {
		tex->setRepeated(1);
		tex->setSmooth(1);
	}
}

void Sprite::DrawScreenspace(sf::RenderWindow *wnd, std::vector<Vector2f> positions) {
	size_t count = positions.size();
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
		vertices[i].position = sf::Vector2f(positions[i].x, positions[i].y);
	};

	(*wnd).draw(vertices, count, sf::TrianglesFan, tex);

	delete[] vertices;
}

void Sprite::DrawWorldspace(sf::RenderWindow *wnd, std::vector<Particle*> particles, Camera cam) {
	float pi = 3.1415926f;
	Vector2f xVector = Vector2f(cam.ang);
	Vector2f yVector = Vector2f(cam.ang + pi / 2.0f);

	float fovx = cam.fieldOfView;
	float fovy = fovx * wnd->getSize().y / wnd->getSize().x;
	
	std::vector<Vector2f> positions;

	for (int i = 0; i < particles.size(); i++) {
		Vector2f delta = particles[i]->pos - cam.pos;
		Vector2f localPos = Vector2f(xVector * delta + fovx / 2.0f, yVector * delta + fovy / 2.0f);

		Vector2f screenPos;
		positions.push_back(localPos * (float(wnd->getSize().x) / fovx));
	}

	this->DrawScreenspace(wnd, positions);
}







void Sprite::DrawScreenspace(sf::RenderWindow *wnd, Vector2f screenPos, float screenAng, Vector2f screenSize, float texScale) {
	sf::Vertex vertices[4];
	Vector2f vertexPos;


	Vector2f xVector = Vector2f(cosf(screenAng), sinf(screenAng));
	Vector2f yVector = xVector.GetPerp();

	vertexPos = screenPos - xVector * screenSize.x *0.5f - yVector * screenSize.y *0.5f;
	vertices[0] = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = screenPos + xVector * screenSize.x *0.5f - yVector * screenSize.y *0.5f;
	vertices[1] = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = screenPos + xVector * screenSize.x *0.5f + yVector * screenSize.y *0.5f;
	vertices[2] = sf::Vector2f(vertexPos.x, vertexPos.y);
	
	vertexPos = screenPos - xVector * screenSize.x *0.5f + yVector * screenSize.y *0.5f;
	vertices[3] = sf::Vector2f(vertexPos.x, vertexPos.y);

	if (texScale < 0.000001f && texScale > -0.000001f) {
		vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
		vertices[1].texCoords = sf::Vector2f((float)tex->getSize().x, 0.0f);
		vertices[2].texCoords = sf::Vector2f((float)tex->getSize().x, (float)tex->getSize().y);
		vertices[3].texCoords = sf::Vector2f(0.0f, (float)tex->getSize().y);
	}
	else {
		vertices[0].texCoords = sf::Vector2f(0.0f, 0.0f);
		vertices[1].texCoords = sf::Vector2f(screenSize.x * texScale, 0.0f);
		vertices[2].texCoords = sf::Vector2f(screenSize.x * texScale, screenSize.y * texScale);
		vertices[3].texCoords = sf::Vector2f(0.0f, screenSize.y * texScale);
	}

	for (int i = 0; i < 4; i++) {
		vertices[i].color = sf::Color::White;
	}

	(*wnd).draw(vertices, 4, sf::Quads, tex);
}

void Sprite::DrawWorldspace(sf::RenderWindow *wnd, Vector2f pos, float ang, Vector2f size, Camera cam, float texScale) {
	float pi = 3.1415926f;
	Vector2f xVector = Vector2f(cam.ang);
	Vector2f yVector = Vector2f(cam.ang + pi / 2.0f);

	float fovx = cam.fieldOfView;
	float fovy = fovx * wnd->getSize().y / wnd->getSize().x;
	Vector2f delta = pos - cam.pos;
	Vector2f localPos = Vector2f(xVector * delta + fovx / 2.0f, yVector * delta + fovy / 2.0f);

	Vector2f screenPos;
	screenPos = localPos * (float(wnd->getSize().x) / fovx);

	float screenAng = ang - cam.ang;

	Vector2f screenSize = size * (float(wnd->getSize().x) / fovx);

	this->DrawScreenspace(wnd, screenPos, screenAng, screenSize, texScale * fovx / wnd->getSize().x);
}

void Sprite::DrawBackground(sf::RenderWindow *wnd, Camera cam, float paralax) {
	tex->setRepeated(1);
	tex->setSmooth(1);

	sf::Vertex vertices[4];
	Vector2f vertexPos;

	vertices[0] = sf::Vector2f(0.0f, 0.0f);
	vertices[1] = sf::Vector2f(wnd->getSize().x, 0.0f);
	vertices[2] = sf::Vector2f(wnd->getSize().x, wnd->getSize().y);
	vertices[3] = sf::Vector2f(0.0f, wnd->getSize().y);

	float pi = 3.1415926f;
	Vector2f xVector = Vector2f(cam.ang);
	Vector2f yVector = Vector2f(cam.ang + pi / 2.0f);

	float fovx = cam.fieldOfView;
	float fovy = fovx * wnd->getSize().y / wnd->getSize().x;

	Vector2f camPos = cam.pos * paralax;

	vertexPos = camPos - xVector * fovx * 0.5f - yVector * fovy * 0.5f;
	//vertexPos = vertexPos * 2.0f;
	vertices[0].texCoords = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = camPos + xVector * fovx * 0.5f - yVector * fovy * 0.5f;
	//vertexPos = vertexPos * 2.0f;
	vertices[1].texCoords = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = camPos + xVector * fovx * 0.5f + yVector * fovy * 0.5f;
	//vertexPos = vertexPos * 2.0f;
	vertices[2].texCoords = sf::Vector2f(vertexPos.x, vertexPos.y);

	vertexPos = camPos - xVector * fovx * 0.5f + yVector * fovy * 0.5f;
	//vertexPos = vertexPos * 2.0f;
	vertices[3].texCoords = sf::Vector2f(vertexPos.x, vertexPos.y);

	for (int i = 0; i < 4; i++) {
		vertices[i].color = sf::Color::White;
	}

	(*wnd).draw(vertices, 4, sf::Quads, tex);
}