#include "stdafx.h"
#include "AnimationClip.h"
#include "Includes/rapidcsv.h"

bool AnimationClip::loadFromFile(const std::string& filePath)
{
	frames.clear();

	rapidcsv::Document doc(filePath);

	id = doc.GetCell<std::string>(0, 0);
	fps = doc.GetCell<int>(1, 0);
	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	for (int i = 3; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		AnimationFrame frame;
		frame.texId = row[0];
		frame.texCoord = { std::stoi(row[1]), std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]) };
		frame.flipX = (bool)std::stoi(row[5]);
		frame.scale = { std::stof(row[6]) ,std::stof(row[7]) };
		frame.color = { (sf::Uint8)std::stoi(row[8]),(sf::Uint8)std::stoi(row[9]),(sf::Uint8)std::stoi(row[10]),(sf::Uint8)std::stoi(row[11]) } ;
		frame.displacement = { std::stof(row[12]) ,std::stof(row[13]) };
		frame.rotation = std::stof(row[14]);
		frames.push_back(frame);
	}

	return true;
}
