/**
 * @file src/cpdetect/compiler_detector/pe_compiler.cpp
 * @brief Methods of PeCompiler class.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#include "retdec/cpdetect/compiler_detector/heuristics/pe_heuristics.h"
#include "retdec/cpdetect/compiler_detector/pe_compiler.h"
#include "retdec/cpdetect/settings.h"
#include "retdec/cpdetect/signatures/yara/database/database.h"

using namespace retdec::fileformat;

namespace retdec {
namespace cpdetect {

/**
 * Constructor
 */
PeCompiler::PeCompiler(retdec::fileformat::PeFormat &parser, DetectParams &params, ToolInformation &tools) : CompilerDetector(parser, params, tools)
{
	heuristics = new PeHeuristics(parser, *search, toolInfo);
	externalSuffixes = EXTERNAL_DATABASE_SUFFIXES;
	switch(targetArchitecture)
	{
		case Architecture::X86:
		case Architecture::X86_64:
			internalDatabase = getX86PeDatabase();
			break;
		case Architecture::ARM:
			internalDatabase = getArmPeDatabase();
			break;
		case Architecture::POWERPC:
			internalDatabase = getPowerPcPeDatabase();
			break;
		case Architecture::MIPS:
			internalDatabase = getMipsPeDatabase();
			break;
		default:
			internalDatabase = nullptr;
	}
}

} // namespace cpdetect
} // namespace retdec
