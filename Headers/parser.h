#pragma once
#include <sstream>
#include "info.h"
#include "tinyxml2.h"

struct Layer
{
    std::vector<sf::Sprite> tiles;
};

class Level {

public:
    bool LoadFromFile(const std::string& filename);
    const Object* GetObject(const Object_type type_);
    const std::vector<Object> GetObjects(const Object_type& type_);
    const std::vector<Object>& GetAllObjects();

    void Draw(sf::RenderWindow& window) const;
    sf::Vector2i GetTileSize() const;
    void Cout_objects() const;
private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};