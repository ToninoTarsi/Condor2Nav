//
// This file is part of Condor2Nav file formats translator.
//
// Copyright (C) 2009 Mateusz Pusz
//
// Condor2Nav is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Condor2Nav is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Condor2Nav. If not, see <http://www.gnu.org/licenses/>.
//
// Visit the project webpage (http://sf.net/projects/condor2nav) for more info.
//

/**
 * @file targetLK8000.cpp
 *
 * @brief Implements the condor2nav::CTargetLK8000 class. 
**/

#include "targetLK8000.h"


const char *condor2nav::CTargetLK8000::AIRSPACES_SUBDIR       = "_Airspaces";
const char *condor2nav::CTargetLK8000::CONFIG_SUBDIR          = "_Configuration";
const char *condor2nav::CTargetLK8000::MAPS_SUBDIR            = "_Maps";
const char *condor2nav::CTargetLK8000::POLARS_SUBDIR          = "_Polars";
const char *condor2nav::CTargetLK8000::TASKS_SUBDIR           = "_Tasks";

const char *condor2nav::CTargetLK8000::LK8000_PROFILE_NAME    = "DEFAULT_PROFILE.prf";


/**
 * @brief Class constructor.
 *
 * condor2nav::CTargetLK8000 class constructor.
 *
 * @param translator Configuration INI file parser.
**/
condor2nav::CTargetLK8000::CTargetLK8000(const CTranslator &translator):
CTargetXCSoarCommon(translator),
_profileParser(CTranslator::DATA_PATH + std::string("\\") + LK8000_PROFILE_NAME),
_outputLK8000DataPath(OutputPath() + "\\LK8000")
{
  std::string subDir = "\\condor2nav";
  _condor2navDataPath = ConfigParser().Value("LK8000", "LK8000Path");

  _outputAirspacesSubDir = std::string("\\") + AIRSPACES_SUBDIR + subDir;
  _outputConfigSubDir = std::string("\\") + CONFIG_SUBDIR + subDir;
  _outputMapsSubDir = std::string("\\") + MAPS_SUBDIR + subDir;
  _outputPolarsSubDir = std::string("\\") + POLARS_SUBDIR + subDir;

  DirectoryCreate(_outputLK8000DataPath + _outputAirspacesSubDir);
  DirectoryCreate(_outputLK8000DataPath + _outputConfigSubDir);
  DirectoryCreate(_outputLK8000DataPath + _outputMapsSubDir);
  DirectoryCreate(_outputLK8000DataPath + _outputPolarsSubDir);
  DirectoryCreate(_outputLK8000DataPath + _outputPolarsSubDir);

  std::string outputTaskDir;
  if(Convert<unsigned>(ConfigParser().Value("LK8000", "DefaultTaskOverwrite"))) {
    outputTaskDir = _outputLK8000DataPath + std::string("\\") + TASKS_SUBDIR;
    _outputTaskFilePath = outputTaskDir + std::string("\\") + DEFAULT_TASK_FILE_NAME;
  }
  else {
    outputTaskDir = _outputLK8000DataPath + std::string("\\") + TASKS_SUBDIR + subDir;
    _outputTaskFilePath = outputTaskDir + std::string("\\") + TASK_FILE_NAME;
  }
  DirectoryCreate(outputTaskDir);
}


/**
 * @brief Class destructor.
 *
 * condor2nav::CTargetLK8000 class destructor.
**/
condor2nav::CTargetLK8000::~CTargetLK8000()
{
  _profileParser.Dump(_outputLK8000DataPath + _outputConfigSubDir + std::string("\\") + OUTPUT_PROFILE_NAME);
}


/**
* @brief Sets scenery map. 
*
* Method sets scenery map XCM data file according to the Condor landscape name. 
*
* @param sceneryData Information describing the scenery. 
**/
void condor2nav::CTargetLK8000::SceneryMap(const CFileParserCSV::CStringArray &sceneryData)
{
  SceneryMapProcess(_profileParser, sceneryData, _condor2navDataPath + _outputMapsSubDir);
}


/**
* @brief Sets time for scenery time zone. 
*
* Method sets UTC time offset for selected scenery and forces time synchronization to the GPS source.
**/
void condor2nav::CTargetLK8000::SceneryTime()
{
  SceneryTimeProcess(_profileParser);
}


/**
* @brief Set glider data. 
*
* Method created and sets glider polar file, handicap, safety speed, the time to empty the water
* ballast and glider name for the logger.
*
* @param gliderData Information describing the glider. 
**/
void condor2nav::CTargetLK8000::Glider(const CFileParserCSV::CStringArray &gliderData)
{
  GliderProcess(_profileParser, gliderData, _condor2navDataPath + _outputPolarsSubDir, _outputLK8000DataPath + _outputPolarsSubDir);
}


/**
* @brief Sets task information. 
*
* Method sets task information.
*
* @param taskParser Condor task parser. 
* @param coordConv  Condor coordinates converter.
**/
void condor2nav::CTargetLK8000::Task(const CFileParserINI &taskParser, const CCondor::CCoordConverter &coordConv)
{
  TaskProcess(_profileParser, taskParser, coordConv, _outputTaskFilePath);
}
 

/**
* @brief Sets task penalty zones. 
*
* Method sets penalty zones used in the task.
*
* @param taskParser Condor task parser. 
* @param coordConv  Condor coordinates converter.
**/
void condor2nav::CTargetLK8000::PenaltyZones(const CFileParserINI &taskParser, const CCondor::CCoordConverter &coordConv)
{
  PenaltyZonesProcess(_profileParser, taskParser, coordConv, _condor2navDataPath + _outputAirspacesSubDir, _outputLK8000DataPath + _outputAirspacesSubDir);
}


/**
* @brief Sets weather data. 
*
* Method sets the wind data.
*
* @param taskParser Condor task parser. 
**/
void condor2nav::CTargetLK8000::Weather(const CFileParserINI &taskParser)
{
  WeatherProcess(_profileParser, taskParser);
}