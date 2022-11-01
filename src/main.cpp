#pragma once

#include "inputEventHandler.h"
#include "inputHandler/movementInputTracer.h"
#include "inputHandler/inputTracer.h"
#include "hooks.h"
#include "settings.h"


#include <SKSE/SKSE.h>
#include <stddef.h>

using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;



void InitializeLogging() {
	auto path = log_directory();
	if (!path) {
		report_and_fail("Unable to lookup SKSE logs directory.");
}
	*path /= PluginDeclaration::GetSingleton()->GetName();
	*path += L".log";

	std::shared_ptr<spdlog::logger> log;
	if (IsDebuggerPresent()) {
		log = std::make_shared<spdlog::logger>(
			"Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
	}
	else {
		log = std::make_shared<spdlog::logger>(
			"Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
	}
	log->set_level({ spdlog::level::level_enum::info });
	log->flush_on({ spdlog::level::level_enum::trace });

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] [%s:%#] %v");
}

void InitializeMessaging() {
	if (!GetMessagingInterface()->RegisterListener([](MessagingInterface::Message* message) {
		switch (message->type) {
			// Skyrim lifecycle events.
		case MessagingInterface::kPostLoad: // Called after all plugins have finished running SKSEPlugin_Load.
			// It is now safe to do multithreaded operations, or operations against other plugins.
		case MessagingInterface::kPostPostLoad: // Called after all kPostLoad message handlers have run.
		case MessagingInterface::kInputLoaded: // Called when all game data has been found.
			break;
		case MessagingInterface::kDataLoaded: // All ESM/ESL/ESP plugins have loaded, main menu is now active.
			// It is now safe to access form data.
			logger::info("SKSEMsgInterface: dataLoaded");
			inputEventHandler::Register();
			settings::readSettings();
			if (settings::bToggleMovementInputTrace) {
				movementInputTracer::GetSingleton()->loadMovementTraceSpells();
			}
			inputTracer::GetSingleton()->loadInputTraceConfigs();
			hooks::install();
			break;

			// Skyrim game events.
		case MessagingInterface::kNewGame: // Player starts a new game from main menu.
		case MessagingInterface::kPreLoadGame: // Player selected a game to load, but it hasn't loaded yet.
			// Data will be the name of the loaded save.
		case MessagingInterface::kPostLoadGame: // Player's selected save game has finished loading.
			// Data will be a boolean indicating whether the load was successful.
		case MessagingInterface::kSaveGame: // The player has saved a game.
			// Data will be the save name.
		case MessagingInterface::kDeleteGame: // The player deleted a saved game from within the load menu.
			break;
		}
		})) {
		stl::report_and_fail("Unable to register message listener.");
	}
}


SKSEPluginLoad(const LoadInterface* skse) {
	InitializeLogging();

	auto* plugin = PluginDeclaration::GetSingleton();
	auto version = plugin->GetVersion();
	log::info("{} {} is loading...", plugin->GetName(), version);


	Init(skse);
	InitializeMessaging();

	log::info("{} has finished loading.", plugin->GetName());
	return true;
}
