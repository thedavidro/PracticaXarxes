#pragma once
#include "XML_Includes.hpp"

using namespace rapidxml;

static void CreateNewNode(string name, int score, string achievements) {
	string s_score = to_string(score);
	cout << s_score;

	//Opens/Creates file with the name "name". This way I have for each player 1 single file.
	ofstream playerFile;
	playerFile.open(RESOURCE_FILE(name));
	playerFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	playerFile.close();

	file<> xmlPlayerFile(RESOURCE_FILE(name));
	xml_document<> doc;	
	//doc.parse<0>(xmlPlayerFile.data());
	doc.parse < rapidxml::parse_no_data_nodes >(xmlPlayerFile.data());

	xml_node<> *encode = doc.allocate_node(node_declaration);
	encode->append_attribute(doc.allocate_attribute("version", "1.0"));
	encode->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(encode);

	xml_node<> *root_node = doc.allocate_node(node_element, "User", 0);			//Sets default User node
	root_node->name(name.c_str());												//Sets Name
	doc.append_node(root_node);													//Appends the node to the doc as the root node
	
	xml_node<> *node_score = doc.allocate_node(node_element, "Score", 0);			//Sets default Score node
	node_score->value(s_score.c_str());												//Sets the value as the score.
	root_node->append_node(node_score);												//Appends the node to the doc as a child node of root_node
	
	xml_node<> *achievement_node = doc.allocate_node(node_element, "Achievement", 0);	//Sets default Achievements node.
	achievement_node->value(achievements.c_str());										//
	root_node->append_node(achievement_node);

	playerFile.open(RESOURCE_FILE(name));
	playerFile << doc;
	playerFile.close();
	doc.clear();

	//playerFile.close();
}