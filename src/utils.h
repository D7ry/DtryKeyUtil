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

	inline void saeToPlayer(RE::BSFixedString ae) {
		auto pc = RE::PlayerCharacter::GetSingleton();
		if (pc) {
			pc->NotifyAnimationGraph(ae);
		}
	}

	inline void flipGraphVariableBoolForPlayer(RE::BSFixedString& gvb) {
		auto pc = RE::PlayerCharacter::GetSingleton();
		if (pc) {
			bool b;
			if (pc->GetGraphVariableBool(gvb, b)) {
				pc->SetGraphVariableBool(gvb, !b);
			}
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


}

class simpleIniUtils
{
public:
	static bool readSimpleIni(CSimpleIniA& a_ini, const char* a_iniAddress) {
		if (std::filesystem::exists(a_iniAddress)) {
			a_ini.LoadFile(a_iniAddress);
			return true;
		}
		else {
			ERROR("Error: {} is not a valid .ini address.", a_iniAddress);
			return false;
		}
	}
	/// <summary>
	/// Run the function with every entry in the designated section as parameters.
	/// </summary>
	/// <param name="a_ini">ini to be loaded</param>
	/// <param name="a_section">section to be loaded</param>
	/// <param name="func">function that will take every entry in the section as a parameter</param>
	static void apply(CSimpleIniA& a_ini, const char* a_section, void (*func) (std::string a_string)) {
		std::list<CSimpleIniA::Entry> keys;
		a_ini.GetAllKeys(a_section, keys);
		for (auto& one_key : keys) {
			std::list<CSimpleIniA::Entry> values;
			a_ini.GetAllValues(a_section, one_key.pItem, values);
			for (auto& one_value : values) {
				logger::info(one_value.pItem);
				func(one_value.pItem);
			}
		}
	}
};

class gameDataUilts
{
public:
	template<class formType> 
	static void loadForm(RE::TESDataHandler* a_TESDataHandler, formType*& a_form, std::string a_formID, std::string a_plugin) {
		int raw_form = 0;
		utils::ToInt(a_formID, raw_form);
		auto read = a_TESDataHandler->LookupForm<formType>(raw_form, a_plugin);
		if (!read) {
			logger::info("Invalid form. formID: {}, plugin: {}", a_formID, a_plugin);
			return;
		}
		a_form = read;
	}
	template<class formType>
	static formType* getForm(RE::TESDataHandler* a_TESDataHandler, std::string a_formID, std::string a_plugin) {
		int raw_form = 0;
		utils::ToInt(a_formID, raw_form);
		formType* form = a_TESDataHandler->LookupForm<formType>(raw_form, a_plugin);
		if (!form) {
			logger::info("Error: invalid form. formID: {}, plugin: {}", a_formID, a_plugin);
			return nullptr;
		}
		return form;
	}

	/*Load a tesForm object to a_form.
	@param a_TESDataHandler: reference to dataHandler singleton.
	@param a_form: reference to the pointer to the form.
	@param a_iniLine: an ini line in the format of "0x0123|PluginName.esp"*/
	template<class formType> static void loadForm(RE::TESDataHandler* a_TESDataHandler, formType*& a_form, std::string a_iniLine) {
		auto configV = utils::tokenize(a_iniLine);
		auto formID = configV[0];
		auto plugin = configV[1];
		loadForm(a_TESDataHandler, a_form, formID, plugin);
	}
};
