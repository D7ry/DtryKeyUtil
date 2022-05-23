#pragma once
#include "lib/SimpleIni.h"
namespace utils
{
	inline void addSpellToPlayer(RE::SpellItem* a_spell) {
		auto pc = RE::PlayerCharacter::GetSingleton();
		if (pc) {
			pc->AddSpell(a_spell);
		}
	}

	inline void removeSpellFromPlayer(RE::SpellItem* a_spell) {
		auto pc = RE::PlayerCharacter::GetSingleton();
		if (pc) {
			pc->RemoveSpell(a_spell);
		}
	}

	inline bool readSimpleIni(CSimpleIniA& a_ini, const char* a_iniAddress) {
		if (std::filesystem::exists(a_iniAddress)) {
			a_ini.LoadFile(a_iniAddress);
			return true;
		}
		else {
			ERROR("Error: {} is not a valid .ini address.", a_iniAddress);
			return false;
		}
	}

	/*Tokenize a string into vectors, separated by a common delimiter.
   @param s: string to be tokenized.
   @param delimiter: the delimiter based on which to tokenize the string.
   @return a vector containing all tokens.*/
	static std::vector<std::string> tokenize(std::string s, const char delimiter = '|')
	{
		size_t start = 0;
		size_t end = s.find_first_of(delimiter);

		std::vector<std::string> output;

		while (end <= std::string::npos)
		{
			std::string ss = s.substr(start, end - start);

			if (ss.size() != 0) { //if token has 0 size, skip it.
				output.emplace_back(ss);
			}


			if (end == std::string::npos)
				break;

			start = end + 1;
			end = s.find_first_of(delimiter, start);
		}

		return output;
	}

	static bool ToInt(std::string str, int& value)
	{
		const char* strVal = str.c_str();
		char* endVal = NULL;
		long ret = strtol(strVal, &endVal, 0);
		if (ret == LONG_MAX || ret == LONG_MIN || (int)endVal != (int)strVal + strlen(strVal))
			return false;
		value = ret;
		return true;
	}
	namespace gameDataLoader
	{
		inline void loadSpellItem(RE::SpellItem*& a_spellItem, RE::TESDataHandler& a_TESDataHandler, std::string a_formID, std::string a_plugin) {
			int raw_form = 0;
			ToInt(a_formID, raw_form);
			auto read = a_TESDataHandler.LookupForm<RE::SpellItem>(raw_form, a_plugin);
			if (!read) {
				ERROR("Error: invalid spell item. formID: {}, plugin: {}", a_formID, a_plugin);
				return;
			}
			a_spellItem = read;
		}
	}
}
