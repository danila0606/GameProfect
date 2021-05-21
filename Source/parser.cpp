#include "../Headers/parser.h"



bool Level::LoadFromFile(const std::string& filename)
{

    tinyxml2::XMLDocument levelFile;

    if (levelFile.LoadFile(filename.c_str()))
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    
    tinyxml2::XMLElement* map;
    map = levelFile.FirstChildElement("map");
    
    width = map->Int64Attribute("width");
    height = map->Int64Attribute("height");
    tileWidth = map->Int64Attribute("tilewidth");
    tileHeight = map->Int64Attribute("tileheight");

   
    tinyxml2::XMLElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = tilesetElement->Int64Attribute("firstgid");

   
    tinyxml2::XMLElement* image;
    image = tilesetElement->FirstChildElement("image_");
    std::string imagepath = image->Attribute("source");

    sf::Image img;

    if (!img.loadFromFile("Images//" + imagepath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }


    img.createMaskFromColor(sf::Color(255, 255, 255));
    tilesetImage.loadFromImage(img);
  

    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

   
    std::vector<sf::Rect<int> > subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

   
    tinyxml2::XMLElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;

     
 
        tinyxml2::XMLElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        int x = 0;
        int y = 0;

        const char* tiles_str = layerDataElement->GetText();
        std::istringstream tiles_stream(tiles_str);
        while (y < height)
        {
             int tileGID = 0;
             tiles_stream >> tileGID;
          
             if (tiles_stream.peek() == ',')
                 tiles_stream.ignore();
             else if (x != width - 1 && y!= height - 1) {
                std::cout << "Wrong file format. Use cvs" << std::endl;
                return false;
             }
             int subRectToUse = tileGID - firstTileID;

  
             if (subRectToUse >= 0)
             {
                 sf::Sprite sprite;
                 sprite.setTexture(tilesetImage);
                 sprite.setTextureRect(subRects[subRectToUse]);
                 sprite.setPosition(x * tileWidth, y * tileHeight);

                 layer.tiles.push_back(sprite);
             }

             x++;
             if (x >= width)
             {
                 x = 0;
                 y++;
             }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    tinyxml2::XMLElement* objectGroupElement;

    objectGroupElement = map->FirstChildElement("objectgroup");
    if (objectGroupElement != NULL)
    {
        while (objectGroupElement)
        {
        
            tinyxml2::XMLElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                Object object;
                
                if (objectElement->Attribute("id") != NULL)
                {
                    object.id = objectElement->Int64Attribute("id");
                }
                else object.id = 0;

                if (!std::strcmp(objectElement->Attribute("type_"),"solid"))
                {
                    object.type = Object_type::solid;
                }
                else if (!std::strcmp(objectElement->Attribute("type_"),"jump"))
                {
                    object.type = Object_type::jumper;
                }
                else if (!std::strcmp(objectElement->Attribute("type_"),"tp"))
                {
                    object.type = Object_type::tp;
                }
                else if (!std::strcmp(objectElement->Attribute("type_"),"player"))
                {
                    
                    object.type = Object_type::player;
                }
                else if (!std::strcmp(objectElement->Attribute("type_"),"Coca"))
                {
                    object.type = Object_type::Coca;
                }
                else if (!std::strcmp(objectElement->Attribute("type_"),"Ghost"))
                {
                    object.type = Object_type::Ghost;
                }
                else object.type = Object_type::unknown;

                
                if (objectElement->Attribute("name") != NULL)
                {
                    object.name = objectElement->Attribute("name");
                }
                else object.name = "noname";

                int x = objectElement->Int64Attribute("x_");
                int y = objectElement->Int64Attribute("y_");

                object.sprite.setTexture(tilesetImage);
                object.sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                object.sprite.setPosition(x, y);

                if ((objectElement->Attribute("width") != NULL) && 
                    (objectElement->Attribute("height") != NULL))
                {
                    object.rect.left = x;
                    object.rect.top = y;
                    object.rect.width = objectElement->Int64Attribute("width");
                    object.rect.height = objectElement->Int64Attribute("height");
                
                    
                }
                else
                {
                    std::cout << "No information about width and height from " 
                        << object.name << " " << std::endl;
                }                                  

                objects.push_back(object);
                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

const Object* Level::GetObject(Object_type type_)
{
    Object *obj;
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].type == type_) {

            Object* obj = &objects[i];
            return obj;
        }
    }
    return nullptr;
}


const std::vector<Object> Level::GetObjects(const Object_type& type_)
{
    std::vector<Object> vec;
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].type == type_)
            vec.push_back(objects[i]);

    return vec;
}
void Level::Cout_objects() const {
    for (int i = 0; i < objects.size(); i++)
    	std::cout << objects[i].name << std::endl;
}

const std::vector<Object>& Level::GetAllObjects()
{
    return objects;
};


sf::Vector2i Level::GetTileSize() const {
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow& window) const {
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
            window.draw(layers[layer].tiles[tile]);
}
