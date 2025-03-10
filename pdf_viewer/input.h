#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

//#include <SDL.h>

#include "utils.h"

struct Command {
	std::string name;
	bool requires_text;
	bool requires_symbol;
	bool requires_file_name;
	bool pushes_state;
};


class CommandManager {
private:
	std::vector<Command> commands;
public:

	CommandManager();
	const Command* get_command_with_name(std::string name);
};

struct InputParseTreeNode {

	std::vector<InputParseTreeNode*> children;
	//char command;
	int command;
	std::string name = "";
	bool shift_modifier = false;
	bool control_modifier = false;
	bool requires_text = false;
	bool requires_symbol = false;
	bool is_root = false;
	bool is_final = false;

	bool is_same(const InputParseTreeNode* other);
	bool matches(int key, bool shift, bool ctrl);
};



class InputHandler {
private:
	InputParseTreeNode* root = nullptr;
	InputParseTreeNode* current_node = nullptr;
	CommandManager command_manager;
	std::string number_stack;

public:
	//char create_link_sumbol = 0;
	//char create_bookmark_symbol = 0;

	InputHandler(const std::filesystem::path& default_path, const std::filesystem::path& user_path);
	void reload_config_files(const std::filesystem::path& default_path, const std::filesystem::path& user_path);
	const Command* handle_key(int key, bool shift_pressed, bool control_pressed, int* num_repeats);
	void delete_current_parse_tree(InputParseTreeNode* node_to_delete);

};

